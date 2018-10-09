#include "iconv.h"

#include <algorithm>
#include <iostream>
#include <string>

#include <cerrno>
#include <cstddef>
#include <cstring>

using namespace std::literals::string_literals;

static constexpr std::vector<char>::size_type buf_initial_size{32768};
static constexpr size_t iconv_failure{static_cast<size_t>(-1)};

epwing::IConv::IConv(iconv_t cd) : cd{cd}, input_buf{}, output_buf{}, input_ptr{input_buf.data()} {
    if (this->cd == (iconv_t) -1) {
        switch (errno) {
            case EINVAL:
                throw std::runtime_error("IConv: iconv_open: conversion not available"s);
            default:
                throw std::runtime_error("IConv: iconv_open"s);
        }
    }
    input_buf.reserve(buf_initial_size);
    output_buf.reserve(buf_initial_size);
}

epwing::IConv::~IConv() noexcept {
    if (iconv_close(cd) == -1) {
        std::cerr << "iconv_close"s << '\n';
    }
}

epwing::IConv epwing::IConv::FromISO8859_1() {
    return IConv{iconv_open("UTF-8//IGNORE", "ISO-8859-1")};
}

epwing::IConv epwing::IConv::FromEucJp() {
    return IConv{iconv_open("UTF-8//IGNORE", "EUC-JP")};
}

epwing::IConv epwing::IConv::FromGb2312() {
    return IConv{iconv_open("UTF-8//IGNORE", "GB2312")};
}

static const std::string replacement = u8"�"s;

// http://www.gnu.org/software/libc/manual/html_node/iconv-Examples.html
const std::string epwing::IConv::to_utf8(std::string_view src) {
    size_t ret = 0;

    auto input_start = input_buf.data();
    auto output_start = output_buf.data();

    auto input_ptr = input_start;
    auto output_ptr = output_start;

    size_t out_available = output_buf.capacity() - 1;

    if (input_buf.empty()) {
        if (ret = iconv(cd, nullptr, nullptr, nullptr, nullptr); ret == iconv_failure)
            throw std::runtime_error("to_utf8: cd initial conversion state"s);

        if (ret = ::iconv(cd, nullptr, nullptr, &output_ptr, &out_available); ret == iconv_failure)
            switch (errno) {
                case E2BIG:
                    throw std::runtime_error("IConv: output buffer too small"s);
                default:
                    throw std::runtime_error("IConv: initialize output shift state"s);
            }
    }

    input_buf.insert(input_buf.end(), src.begin(), src.end());
    size_t src_remaining = input_buf.size();

    std::ptrdiff_t input_converted = 0;
    std::ptrdiff_t output_converted = 0;
    while (src_remaining > 0 && out_available > 0) {
        errno = 0;
        ret = ::iconv(cd, &input_ptr, &src_remaining, &output_ptr, &out_available);
        input_converted = input_ptr - input_start;
        output_converted = output_ptr - output_start;
        if (ret == iconv_failure) {
            switch (errno) {
                case EINVAL:
                    input_buf.erase(input_buf.begin(), input_buf.begin() + input_converted);
//                    input_ptr = reinterpret_cast<char *>(std::memmove(input_start, input_ptr, src_remaining));
                    return {output_start, output_start + output_converted};
                case EILSEQ:
                    input_buf.clear();
                    return std::string{output_start, output_start + output_converted} + replacement;
                case E2BIG:
                    output_buf.resize(output_buf.size() * 2);
                    output_start = output_buf.data();
                    output_ptr = output_start + output_converted;
                    out_available = output_buf.size() - output_converted - 1;
                    continue;
                default:
                    throw std::runtime_error("to_utf8: unhandled errno"s);
            }
        }
    }

    if (out_available < sizeof(char))
        throw std::runtime_error("to_utf8: no space for null terminator"s);

    input_buf.clear();

    *output_ptr = '\0';
    return {output_start, output_start + output_converted};
}

epwing::IConv
epwing::IConv::from_character_code(EB_Character_Code character_code) {
    switch (character_code) {
        case EB_CHARCODE_ISO8859_1:
            return FromISO8859_1();
        case EB_CHARCODE_JISX0208:
        case EB_CHARCODE_JISX0208_GB2312:
            return FromEucJp();
        case EB_CHARCODE_INVALID:
            throw std::runtime_error("character code invalid"s);
        default:
            throw std::runtime_error("unrecognized book character code"s);
    }
}
