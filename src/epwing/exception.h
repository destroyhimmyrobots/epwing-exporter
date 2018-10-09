#ifndef EPWING_EXPORTER_EPWING_EXCEPTION_H
#define EPWING_EXPORTER_EPWING_EXCEPTION_H

#include <string>
#include <stdexcept>

extern "C" {
#include <eb/defs.h>
#include <eb/error.h>
}

using namespace std::literals::string_literals;

namespace epwing {
    class ClientError final : public std::runtime_error {
    public:
        explicit ClientError(const std::string &message)
            : runtime_error(message) {}
    };

    class LibraryError final : public std::runtime_error {
    public:
        LibraryError(EB_Error_Code error_code, const std::string &message)
            : runtime_error(message + ": "s + std::string(eb_error_message(error_code))), error_code{error_code} {}

        EB_Error_Code code() const noexcept { return error_code; }

    private:
        EB_Error_Code error_code;
    };
}

#endif // EPWING_EXPORTER_EPWING_EXCEPTION_H
