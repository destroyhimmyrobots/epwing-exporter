#ifndef EPWING_EXPORTER_EPWING_BOOK_H
#define EPWING_EXPORTER_EPWING_BOOK_H

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#include <gsl/gsl>

extern "C" {
#include <eb/defs.h>
#include <eb/error.h>
}

#include "container.h"
#include "path.h"

namespace epwing {
    static inline constexpr size_t max_size_hits = 64;
    static inline constexpr size_t max_size_text = 262144;

    class Book final {
    public:
        explicit Book(const path &path);

        ~Book() noexcept;

        // libeb wrappers

        void set_subbook(EB_Subbook_Code subbook_code);

        std::string_view subbook_title();

        void set_hooks(const EB_Hook *hooks);

        const gsl::span<EB_Subbook_Code> subbook_list();

        EB_Position text();

        void seek_text(const EB_Position &position);

        bool is_text_stopped() noexcept;

        void forward_text();

        std::string_view read_heading(EB_Appendix *appendix, Container &container);

        std::string_view read_text(EB_Appendix *appendix, Container &container);

        const gsl::span<EB_Hit> hit_list();

        void search_word(std::string_view word);

        // accessors

        EB_Character_Code get_character_code() const noexcept;

        EB_Error_Code get_error_code() const noexcept;

    private:
        EB_Book book;
        EB_Error_Code error_code;
        EB_Hookset hookset;

        using SubBookTitle = std::array<char, EB_MAX_TITLE_LENGTH + 1>;
        std::unique_ptr<SubBookTitle> subbook_title_buf;

        using SubBookList = std::array<EB_Subbook_Code, EB_MAX_SUBBOOKS>;
        std::unique_ptr<SubBookList> subbook_list_buf;

        using HitListBuf = std::array<EB_Hit, max_size_hits>;
        std::unique_ptr<HitListBuf> hit_list_buf;

        using TextBuf = std::array<char, max_size_text>;
        std::unique_ptr<TextBuf> text_buf;
    };
}

#endif // EPWING_EXPORTER_EPWING_BOOK_H
