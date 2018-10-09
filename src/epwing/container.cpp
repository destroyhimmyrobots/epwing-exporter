#include "container.h"

epwing::Container::Container(epwing::IConv &euc_jp,
                             epwing::IConv &gb2313,
                             epwing::IConv &iso_8859_1,
                             const epwing::Dictionary &dictionary,
                             const epwing::HookSet &hook_set,
                             epwing::ContainerReporter &reporter)
    : euc_jp{euc_jp}, gb2313_{gb2313}, iso_8859_1{iso_8859_1},
      dictionary{dictionary}, hook_set{hook_set}, reporter{reporter} {}

bool
epwing::Container::should_open_reference() noexcept {
    return reference_open ? false : (reference_open = true);
}

bool
epwing::Container::should_close_reference() noexcept {
    return reference_open ? !(reference_open = false) : false;
}

// HookSet

const std::string
epwing::Container::begin_subscript() {
    ++reporter.begin_subscript;
    return hook_set.begin_subscript();
}

const std::string
epwing::Container::end_subscript() {
    ++reporter.end_subscript;
    return hook_set.end_subscript();
}

const std::string
epwing::Container::set_indent(unsigned int indent_level) {
    ++reporter.set_indent;
    return hook_set.set_indent(indent_level);
}

const std::string
epwing::Container::newline() {
    ++reporter.newline;
    return hook_set.newline();
}

const std::string
epwing::Container::begin_superscript() {
    ++reporter.begin_superscript;
    return hook_set.begin_superscript();
}

const std::string
epwing::Container::end_superscript() {
    ++reporter.end_superscript;
    return hook_set.end_superscript();
}

const std::string
epwing::Container::begin_emphasis() {
    ++reporter.begin_emphasis;
    return hook_set.begin_emphasis();
}

const std::string
epwing::Container::end_emphasis() {
    ++reporter.end_emphasis;
    return hook_set.end_emphasis();
}

const std::string
epwing::Container::begin_candidate() {
    ++reporter.begin_candidate;
    return hook_set.begin_candidate();
}

const std::string
epwing::Container::end_candidate_group(unsigned int page, unsigned int offset) {
    ++reporter.end_candidate_group;
    return hook_set.end_candidate_group(page, offset);
}

const std::string
epwing::Container::end_candidate_leaf() {
    ++reporter.end_candidate_leaf;
    return hook_set.end_candidate_leaf();
}

const std::string
epwing::Container::begin_reference() {
    ++reporter.begin_reference;
    if (should_open_reference()) return hook_set.begin_reference();
    return {};
}

const std::string
epwing::Container::end_reference(unsigned int page, unsigned int offset) {
    ++reporter.end_reference;
    // TODO: separate text & reference tag closure state?
    if (should_close_reference()) return hook_set.end_reference(page, offset);
    return {};
}

const std::string
epwing::Container::narrow_font(unsigned int gaiji_code) {
    ++reporter.narrow_font;
    return dictionary.narrow_utf8_replacement(gaiji_code);
}

const std::string
epwing::Container::wide_font(unsigned int gaiji_code) {
    ++reporter.wide_font;
    return dictionary.wide_utf8_replacement(gaiji_code);
}

const std::string
epwing::Container::narrow_JISX0208(std::string_view view) {
    ++reporter.narrow_JISX0208;
    return euc_jp.to_utf8(view);
}

const std::string
epwing::Container::wide_JISX0208(std::string_view view) {
    ++reporter.wide_JISX0208;
    return euc_jp.to_utf8(view);
}

const std::string
epwing::Container::gb2313(std::string_view view) {
    ++reporter.gb2313;
    return gb2313_.to_utf8(view);
}

const std::string
epwing::Container::iso8859_1(std::string_view view) {
    ++reporter.iso8859_1;
    return iso_8859_1.to_utf8(view);
}

/*
const std::string
epwing::Container::begin_keyword() {
    ++reporter.begin_keyword;
    return hook_set.begin_keyword();
}

const std::string
epwing::Container::end_keyword() {
    ++reporter.end_keyword;
    return hook_set.end_keyword();
}
*/
