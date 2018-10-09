#ifndef EPWING_EXPORTER_EPWING_ICONV_H
#define EPWING_EXPORTER_EPWING_ICONV_H

#include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

extern "C" {
#include <eb/defs.h>
#include <iconv.h>
}

// https://www.gnu.org/software/libc/manual/html_node/iconv-Examples.html

namespace epwing {
    class IConv final {
    public:
        ~IConv() noexcept;

        const std::string to_utf8(std::string_view src);

        static IConv from_character_code(EB_Character_Code character_code);

        static IConv FromISO8859_1();

        static IConv FromEucJp();

        static IConv FromGb2312();

    private:
        iconv_t cd;
        std::vector<char> input_buf, output_buf;
        char *input_ptr;

        explicit IConv(iconv_t cd);
    };
}

#endif // EPWING_EXPORTER_EPWING_ICONV_H
