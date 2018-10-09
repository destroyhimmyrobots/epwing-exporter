#include <cstring>
#include <iostream>

extern "C" {
#include <eb/eb.h>
#include <eb/text.h>
}

#include "book.h"
#include "exception.h"

using namespace std::literals::string_literals;

epwing::Book::Book(const path &path)
    : subbook_title_buf{std::make_unique<SubBookTitle>()},
      subbook_list_buf{std::make_unique<SubBookList>()},
      hit_list_buf{std::make_unique<HitListBuf>()},
      text_buf{std::make_unique<TextBuf>()} {
    eb_initialize_book(&book);
    if (auto error_code = eb_bind(&book, path.c_str()); error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_bind: failed to bind the book"s);

    if (book.disc_code != EB_DISC_EPWING)
        throw ClientError("book disc code invalid or not supported"s);

    eb_initialize_hookset(&hookset);
}

epwing::Book::~Book() noexcept {
    eb_finalize_hookset(&hookset);
    eb_finalize_book(&book);
}

void
epwing::Book::set_subbook(EB_Subbook_Code subbook_code) {
    if (error_code = eb_set_subbook(&book, subbook_code);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_set_subbook: failed to set the current subbook"s);
}

std::string_view
epwing::Book::subbook_title() {
    auto ptr = subbook_title_buf->data();
    if (error_code = eb_subbook_title(&book, ptr);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_subbook_title: failed to get the current subbook title"s);
    return ptr;
}

void
epwing::Book::set_hooks(const EB_Hook *const hooks) {
    if (error_code = eb_set_hooks(&hookset, hooks);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_set_hooks: failed to set hooks"s);
}

EB_Position
epwing::Book::text() {
    EB_Position position{};
    if (error_code = eb_text(&book, &position);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_text: failed to get text information"s);
    return position;
}

void
epwing::Book::seek_text(const EB_Position &position) {
    if (error_code = eb_seek_text(&book, &position);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_seek_text: failed to seek text"s);
}

bool
epwing::Book::is_text_stopped() noexcept {
    return eb_is_text_stopped(&book) != 0;
}

void
epwing::Book::forward_text() {
    if (error_code = eb_forward_text(&book, nullptr);
        error_code != EB_ERR_END_OF_CONTENT &&
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_forward_text: failed to forward text"s);
}

std::string_view
epwing::Book::read_heading(EB_Appendix *appendix, Container &container) {
    auto ptr = text_buf->data();
    ssize_t text_buf_size = 0;
    if (error_code = eb_read_heading(&book, appendix, &hookset, &container,
                                     max_size_text, ptr, &text_buf_size);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_read_heading: failed to read text of hit heading"s);
    return {ptr, static_cast<std::string_view::size_type>(text_buf_size)};
}

std::string_view
epwing::Book::read_text(EB_Appendix *appendix, Container &container) {
    auto ptr = text_buf->data();
    ssize_t text_buf_size = 0;
    if (error_code = eb_read_text(&book, appendix, &hookset, &container,
                                  max_size_text, ptr, &text_buf_size);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_read_heading: failed to read text"s);
    return {ptr, static_cast<std::string_view::size_type>(text_buf_size)};
}

const gsl::span<EB_Hit>
epwing::Book::hit_list() {
    auto ptr = hit_list_buf->data();
    int hit_list_size = 0;
    if (error_code = eb_hit_list(&book, max_size_hits, ptr, &hit_list_size);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_hit_list: failed to get list"s);
    return {ptr, hit_list_size};
}

void
epwing::Book::search_word(std::string_view word) {
    if (error_code = eb_search_word(&book, word.data());
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_search_word: search failed"s);
}

const gsl::span<EB_Subbook_Code>
epwing::Book::subbook_list() {
    int sub_book_count = 0;
    if (error_code = eb_subbook_list(&book, subbook_list_buf->data(), &sub_book_count);
        error_code != EB_SUCCESS)
        throw LibraryError(error_code, "eb_subbook_list: failed to get the subbbook list"s);
    return {subbook_list_buf->begin(), sub_book_count};
}

EB_Character_Code
epwing::Book::get_character_code() const noexcept {
    return book.character_code;
}

EB_Error_Code
epwing::Book::get_error_code() const noexcept {
    return error_code;
}
