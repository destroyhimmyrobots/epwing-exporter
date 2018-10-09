#include <exception>
#include <iostream>

#include <gsl/gsl>

#include "container.h"

extern "C" {

#include <eb/text.h>
#include <eb/error.h>

#include "hooks.h"

using namespace std::literals::string_literals;

static_assert(sizeof(char) == 1, "expected type char to have size of 1 byte");

#define EB_UNUSED_HOOK_ARGS() \
    (void)appendix; \
    (void)code; \
    (void)argc; \
    (void)argv

#define CONTAINER \
    static_cast<epwing::Container *>(container)

static constexpr EB_Error_Code error_hook_throw = EB_NUMBER_OF_ERRORS + 1;

#define CATCH_ALL \
    catch (const std::exception &e) { \
        std::cerr << __func__ << ": unhandled exception: "s << e.what() << '\n'; \
        return error_hook_throw; \
    } catch (...) { \
        std::cerr << __func__ << ": unhandled exception\n"s; \
        return error_hook_throw; \
    }

EB_HOOK_FUNC(begin_subscript) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->begin_subscript().data());
} CATCH_ALL

EB_HOOK_FUNC(end_subscript) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->end_subscript().data());
} CATCH_ALL

EB_HOOK_FUNC(set_indent) try {
    (void) appendix;
    (void) argc;
    (void) code;
    return eb_write_text_string(book, CONTAINER->set_indent(argv[1]).data());
} CATCH_ALL

EB_HOOK_FUNC(newline) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->newline().data());
} CATCH_ALL

EB_HOOK_FUNC(begin_superscript) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->begin_superscript().data());
} CATCH_ALL

EB_HOOK_FUNC(end_superscript) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->end_superscript().data());
} CATCH_ALL

EB_HOOK_FUNC(begin_emphasis) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->begin_emphasis().data());
} CATCH_ALL

EB_HOOK_FUNC(end_emphasis) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->end_emphasis().data());
} CATCH_ALL

EB_HOOK_FUNC(begin_candidate) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->begin_candidate().data());
} CATCH_ALL

EB_HOOK_FUNC(end_candidate_group) try {
    (void) appendix;
    (void) argc;
    (void) code;
    return eb_write_text_string(book, CONTAINER->end_candidate_group(argv[1], argv[2]).data());
} CATCH_ALL

EB_HOOK_FUNC(end_candidate_leaf) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->end_candidate_leaf().data());
} CATCH_ALL

EB_HOOK_FUNC(begin_reference) try {
    EB_UNUSED_HOOK_ARGS();
    // TODO: may be empty
    return eb_write_text_string(book, CONTAINER->begin_reference().data());
} CATCH_ALL

EB_HOOK_FUNC(end_reference) try {
    (void) appendix;
    (void) argc;
    (void) code;
    // TODO: may be empty
    return eb_write_text_string(book, CONTAINER->end_reference(argv[1], argv[2]).data());
} CATCH_ALL

EB_HOOK_FUNC(narrow_font) try {
    (void) appendix;
    (void) argc;
    (void) code;
    // TODO: Provide an appendix to eb_hook_narrow_character_text.
    return eb_write_text_string(book, CONTAINER->narrow_font(argv[0]).data());
} CATCH_ALL

EB_HOOK_FUNC(wide_font) try {
    (void) appendix;
    (void) argc;
    (void) code;
    // TODO: Provide an appendix to eb_hook_wide_character_text.
    return eb_write_text_string(book, CONTAINER->wide_font(argv[0]).data());
} CATCH_ALL

// hook.c
/*
 * Hook which converts a character from EUC-JP to ASCII.
 */
static std::string
euc_to_ascii(const unsigned int *argv) {
    /*
     * EUC JP to ASCII conversion table.
     */
    static constexpr int EUC_TO_ASCII_TABLE_START = 0xa0;
    static constexpr int EUC_TO_ASCII_TABLE_END = 0xff;

    static constexpr unsigned char euc_a1_to_ascii_table[] = {
        0x00, 0x20, 0x00, 0x00, 0x2c, 0x2e, 0x00, 0x3a,     /* 0xa0 */
        0x3b, 0x3f, 0x21, 0x00, 0x00, 0x00, 0x60, 0x00,     /* 0xa8 */
        0x5e, 0x7e, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xb0 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x2f,     /* 0xb8 */
        0x5c, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x27,     /* 0xc0 */
        0x00, 0x22, 0x28, 0x29, 0x00, 0x00, 0x5b, 0x5d,     /* 0xc8 */
        0x7b, 0x7d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xd0 */
        0x00, 0x00, 0x00, 0x00, 0x2b, 0x2d, 0x00, 0x00,     /* 0xd8 */
        0x00, 0x3d, 0x00, 0x3c, 0x3e, 0x00, 0x00, 0x00,     /* 0xe0 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c,     /* 0xe8 */
        0x24, 0x00, 0x00, 0x25, 0x23, 0x26, 0x2a, 0x40,     /* 0xf0 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xf8 */
    };

    static constexpr unsigned char euc_a3_to_ascii_table[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xa0 */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xa8 */
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,     /* 0xb0 */
        0x38, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xb8 */
        0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,     /* 0xc0 */
        0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,     /* 0xc8 */
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,     /* 0xd0 */
        0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xd8 */
        0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,     /* 0xe0 */
        0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,     /* 0xe8 */
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,     /* 0xf0 */
        0x78, 0x79, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00,     /* 0xf8 */
    };

    int in_code1, in_code2;
    int out_code = 0;

    in_code1 = argv[0] >> 8;
    in_code2 = argv[0] & 0xff;

    if (in_code2 < EUC_TO_ASCII_TABLE_START || EUC_TO_ASCII_TABLE_END < in_code2) {
        out_code = 0;
    } else if (in_code1 == 0xa1) {
        out_code = euc_a1_to_ascii_table[in_code2 - EUC_TO_ASCII_TABLE_START];
    } else if (in_code1 == 0xa3) {
        out_code = euc_a3_to_ascii_table[in_code2 - EUC_TO_ASCII_TABLE_START];
    }

    if (out_code == 0)
        return {gsl::narrow_cast<char>(in_code1), gsl::narrow_cast<char>(in_code2), '\0'};

    switch (auto ascii = gsl::narrow_cast<char>(out_code); ascii) {
        case '<':
            return "&lt;"s;
        case '>':
            return "&gt;"s;
        case '&':
            return "&amp;"s;
        default:
            return {ascii, '\0'};
    }
}

EB_HOOK_FUNC(narrow_JISX0208) try {
    (void) appendix;
    (void) argc;
    (void) code;
    auto buf = euc_to_ascii(argv);
    return eb_write_text_string(book, CONTAINER->narrow_JISX0208(buf).data());
} CATCH_ALL

EB_HOOK_FUNC(wide_JISX0208) try {
    (void) appendix;
    (void) code;
    (void) argc;
    auto buf = euc_to_ascii(argv);
    return eb_write_text_string(book, CONTAINER->wide_JISX0208(buf).data());
} CATCH_ALL

EB_HOOK_FUNC(gb2313) try {
    (void) appendix;
    (void) code;
    (void) argc;
    std::array<char, 2> buf{
        {
            static_cast<char>((argv[0] >> 8) & 0xFF),
            static_cast<char>(argv[0] & 0xFF),
        },
    };
    return eb_write_text_string(book, CONTAINER->gb2313({buf.data(), buf.size()}).data());
} CATCH_ALL

EB_HOOK_FUNC(iso8859_1) try {
    (void) appendix;
    (void) code;
    (void) argc;
    std::array<char, 1> buf{
        {
            static_cast<char>(argv[0] & 0xFF),
        },
    };
    return eb_write_text_string(book, CONTAINER->iso8859_1({buf.data(), buf.size()}).data());
} CATCH_ALL

/*
EB_HOOK_FUNC(begin_keyword) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->begin_keyword().data());
} CATCH_ALL

EB_HOOK_FUNC(end_keyword) try {
    EB_UNUSED_HOOK_ARGS();
    return eb_write_text_string(book, CONTAINER->end_keyword().data());
} CATCH_ALL
*/

const EB_Hook TEXT_HOOKS[] = {
    {EB_HOOK_BEGIN_SUBSCRIPT,     eb_hook_func_begin_subscript},
    {EB_HOOK_END_SUBSCRIPT,       eb_hook_func_end_subscript},

    {EB_HOOK_SET_INDENT,          eb_hook_func_set_indent},
    {EB_HOOK_NEWLINE,             eb_hook_func_newline},

    {EB_HOOK_BEGIN_SUPERSCRIPT,   eb_hook_func_begin_superscript},
    {EB_HOOK_END_SUPERSCRIPT,     eb_hook_func_end_superscript},

    {EB_HOOK_BEGIN_EMPHASIS,      eb_hook_func_begin_emphasis},
    {EB_HOOK_END_EMPHASIS,        eb_hook_func_end_emphasis},

    {EB_HOOK_BEGIN_CANDIDATE,     eb_hook_func_begin_candidate},
    {EB_HOOK_END_CANDIDATE_GROUP, eb_hook_func_end_candidate_group},
    {EB_HOOK_END_CANDIDATE_LEAF,  eb_hook_func_end_candidate_leaf},

    {EB_HOOK_BEGIN_REFERENCE,     eb_hook_func_begin_reference},
    {EB_HOOK_END_REFERENCE,       eb_hook_func_end_reference},

    //  {EB_HOOK_BEGIN_KEYWORD, eb_hook_func_begin_keyword},
    //  {EB_HOOK_END_KEYWORD, eb_hook_func_end_keyword},

    {EB_HOOK_NARROW_FONT,         eb_hook_func_narrow_font},
    {EB_HOOK_WIDE_FONT,           eb_hook_func_wide_font},

    {EB_HOOK_ISO8859_1,           eb_hook_func_iso8859_1},
    {EB_HOOK_NARROW_JISX0208,     eb_hook_func_narrow_JISX0208},
    {EB_HOOK_WIDE_JISX0208,       eb_hook_func_wide_JISX0208},
    {EB_HOOK_GB2312,              eb_hook_func_gb2313},

    {EB_HOOK_NULL,                nullptr},
};
}
