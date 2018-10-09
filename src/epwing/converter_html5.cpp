#include "converter_html5.h"

using namespace std::literals::string_literals;

epwing::HTML5Converter::HTML5Converter(std::ostream &os) : os{os} {}

void
epwing::HTML5Converter::book_start() {
    os << "<!DOCTYPE html>"s << '\n'
       << "<html>"s << '\n'
       << "<head>"s << '\n'
       << R"(<meta charset="UTF-8">)"s << '\n'
       << R"(<style type="text/css">)"s << '\n'
       << ".indent-0 { text-indent: 0em; };"s << '\n'
       << ".indent-1 { text-indent: 2em; };"s << '\n'
       << ".indent-2 { text-indent: 4em; };"s << '\n'
       << ".indent-3 { text-indent: 6em; };"s << '\n'
       << ".indent-4 { text-indent: 8em; };"s << '\n'
       << ".search { };"s << '\n'
       << ".complex-search-candidate { };"s << '\n'
       << ".subbook-title { };"s << '\n'
       << ".keyword { };"s << '\n'
       << ".reference { };"s << '\n'
       << ".wide-external-character { background-color: red; };"s << '\n'
       << ".narrow-external-character { background-color: red; };"s << '\n'
       << ".subbook { };"s << '\n'
       << ".subbook-title { };"s << '\n'
       << ".text { };"s << '\n'
       << "</style>"s << '\n'
       << "<title>"s << '\n'
       << "EPWING HTML5 Conversion"s << '\n'
       << "</title>"s << '\n'
       << "</head>"s << '\n'
       << "<body>"s;
}

void
epwing::HTML5Converter::subbook_start(EB_Subbook_Code subbook_code) {
    os << R"(<section class="subbook")"s
       << R"( id="eb-subbook-)"s << subbook_code << R"(">)"s
       << '\n';
}

void
epwing::HTML5Converter::subbook_title(EB_Subbook_Code subbook_code, std::string_view subbook_title) {
    os << R"(<header class="subbook-title")"s
       << R"( id="eb-subbook-title-)"s << subbook_code << '"' << '>' << '\n'
       << R"(<h2>)"s << subbook_title << R"(</h2>)"s << '\n'
       << R"(</header>)"s << '\n';
}

void
epwing::HTML5Converter::text_start(EB_Subbook_Code subbook_code, const EB_Position &position) {
    os << R"(<section class="text")"s
       << R"( id="eb-)"s << subbook_code
       << ':' << position.page
       << ':' << position.offset
       << '"' << '>' << '\n';
}

void
epwing::HTML5Converter::text_article(EB_Subbook_Code, std::string_view text) {
    os << "<article>"s << '\n'
       << "<p>"s << text << "</p>"s << '\n'
       << "</article>"s << '\n';
}

void
epwing::HTML5Converter::text_stop() {
    os << "</section>"s << '\n';
}

void
epwing::HTML5Converter::search_start(EB_Subbook_Code) {
    os << R"(<section class="search">)"s << '\n';
}

void
epwing::HTML5Converter::search_article_start(EB_Subbook_Code) {
    os << R"(<article class="entry">)"s << '\n';

}

void
epwing::HTML5Converter::search_article_heading(EB_Subbook_Code subbook_code,
                                      const EB_Position &position,
                                      std::string_view heading) {
    os << "<header"s;
    sp_id_tag(subbook_code, position);
    os << '>' << '\n'
       << "<h3>"s << heading << "</h3>"s << '\n'
       << "</header>"s << '\n';
}

void
epwing::HTML5Converter::search_article_text(EB_Subbook_Code subbook_code,
                                   const EB_Position &position,
                                   std::string_view text) {
    os << "<p"s;
    sp_id_tag(subbook_code, position);
    os << '>' << text << "</p>"s << '\n';
}

void
epwing::HTML5Converter::search_article_stop() {
    os << "</article>"s << '\n';
}

void
epwing::HTML5Converter::search_stop() {
    os << "</section>"s << '\n';
}

void
epwing::HTML5Converter::subbook_stop() {
    os << "</section>"s << '\n';
}

void
epwing::HTML5Converter::book_stop() {
    os << "</body>"s << '\n'
       << "</html>"s << '\n';
}

inline void
epwing::HTML5Converter::sp_id_tag(EB_Subbook_Code subbook_code,
                         const EB_Position &position) {
    os << R"( id="eb-)"s << subbook_code
       << ':' << position.page
       << ':' << position.offset << '"';
}
