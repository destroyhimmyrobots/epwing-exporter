#include <chrono>
#include <ctime>
#include <iomanip>

#include "converter_xdxf.h"

epwing::XDXFConverter::XDXFConverter(std::string_view lang_from, std::string_view lang_to, std::ostream &os)
    : os{os}, lang_from{lang_from}, lang_to{lang_to} {}


void epwing::XDXFConverter::book_start() {
    os << R"(<?xml version="1.0" encoding="UTF-8" ?>)"
       << R"(<!DOCTYPE xdxf SYSTEM "https://raw.github.com/soshial/xdxf_makedict/master/format_standard/xdxf_strict.dtd">)"
       << '\n';
}

void epwing::XDXFConverter::subbook_start(EB_Subbook_Code) {
    os << R"(<xdxf lang_from=")" << lang_from << '"'
       << R"( lang_to=")" << lang_to << '"'
       << R"( format="logical" revision="033">)"
       << '\n';

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto date = std::put_time(std::gmtime(&now), "%F");
    os << "<meta_info>\n"
       << "<file_ver>001</file_ver>\n"
       << "<creation_date>" << date << "</creation_date>\n"
       << "<last_edited_date>" << date << "</last_edited_date>\n";
}

void epwing::XDXFConverter::subbook_title(EB_Subbook_Code, std::string_view view) {
    os << "<title>" << view << "</title>\n"
       << "<full_title>" << view << "</full_title>\n";
}

void epwing::XDXFConverter::text_start(EB_Subbook_Code, const EB_Position &) {
    os << "<description>\n";
}

void epwing::XDXFConverter::text_article(EB_Subbook_Code, std::string_view view) {
    os << view;
}

void epwing::XDXFConverter::text_stop() {
    os << "</description>\n";
}

void epwing::XDXFConverter::search_start(EB_Subbook_Code) {
    os << "<lexicon>\n";
}

void epwing::XDXFConverter::search_article_start(EB_Subbook_Code) {
    os << "<ar>\n";
}

void epwing::XDXFConverter::search_article_heading(EB_Subbook_Code code, const EB_Position &position,
                                                   std::string_view view) {
    os << R"(<k id=")" << code
       << ':' << position.page
       << ':' << position.offset
       << R"(">)" << view << "</k>\n";
}

void epwing::XDXFConverter::search_article_text(EB_Subbook_Code, const EB_Position &, std::string_view view) {
    os << "<def>\n"
       << "<deftext>\n"
       << view
       << "</deftext>\n"
       << "</def>\n";
}

void epwing::XDXFConverter::search_article_stop() {
    os << "</ar>\n";
}

void epwing::XDXFConverter::search_stop() {
    os << "</lexicon>\n";
}

void epwing::XDXFConverter::subbook_stop() {
    os << "</meta_info>"
       << "</xdxf>\n";
}

void epwing::XDXFConverter::book_stop() {
}
