#include "printer_html5.h"

epwing::Html5Printer::Html5Printer(EB_Subbook_Code subbook_code)
    : subbook_code{subbook_code} {}

const std::string
epwing::Html5Printer::begin_subscript() const {
    return "<sub>";
}

const std::string
epwing::Html5Printer::end_subscript() const {
    return "</sub>";
}

const std::string
epwing::Html5Printer::set_indent(unsigned int indent_level) const {
    std::ostringstream os;
    os << R"(<span class=")" << "indent-" << indent_level << R"(">)"
       << "&nbsp;" << "</span>" << '\n';
    return os.str();
}

const std::string
epwing::Html5Printer::newline() const {
    return "<br>";
}

const std::string
epwing::Html5Printer::begin_superscript() const {
    return "<sup>";
}

const std::string
epwing::Html5Printer::end_superscript() const {
    return "</sup>";
}

const std::string
epwing::Html5Printer::begin_emphasis() const {
    return "<mark>";
}

const std::string
epwing::Html5Printer::end_emphasis() const {
    return "</mark>";
}

const std::string
epwing::Html5Printer::begin_candidate() const {
    return R"(<span class="complex-search-candidate">)";
}

const std::string
epwing::Html5Printer::end_candidate_group(unsigned int page, unsigned int offset) const {
    std::ostringstream os;
    os << "</span>" << '\n'
       << R"(<a class="complex-search-candidate")"
       << R"( href="#eb-)" << subbook_code << ":" << page << ':' << offset << '"'
       << R"( data-eb-candidate-type="group")"
       << ">" << '\n'
       << u8"⇒" // A2 CD = EUC-JP encoding of UTF-8 RIGHTWARDS DOUBLE ARROW; "\xA2\xCD";
       << "</a>" << '\n';
    return os.str();
}

const std::string
epwing::Html5Printer::end_candidate_leaf() const {
    return R"(</span><!-- span class="complex-search-candidate" data-eb-candidate-type="leaf" -->)";
}

const std::string
epwing::Html5Printer::begin_reference() const {
    return R"(<span class="reference">)";
}

const std::string
epwing::Html5Printer::end_reference(unsigned int page, unsigned int offset) const {
    std::ostringstream os;
    os << "</span>"
       << R"(<a class="reference")"
       << R"( href="#eb-)" << subbook_code << ":" << page << ':' << offset << '"'
       << '>' << '\n'
       << u8"⇒" // A2 CD = EUC-JP encoding of UTF-8 RIGHTWARDS DOUBLE ARROW; "\xA2\xCD";
       << "</a>" << '\n';
    return os.str();
}

/*
const std::string
epwing::Html5Printer::begin_keyword() const {
    return R"(<span class="keyword">)";
}

const std::string
epwing::Html5Printer::end_keyword() const {
    return R"(</span>)";
}
*/
