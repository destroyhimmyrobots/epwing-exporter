#include <sstream>

#include "printer_xdxf.h"

using namespace std::literals::string_literals;

epwing::XDXFPrinter::XDXFPrinter(EB_Subbook_Code subbook_code)
    : subbook_code{subbook_code} {}

const std::string
epwing::XDXFPrinter::begin_subscript() const {
    return "<sub>";
}

const std::string
epwing::XDXFPrinter::end_subscript() const {
    return "</sub>";
}

const std::string
epwing::XDXFPrinter::set_indent(unsigned int indent_level) const {
    std::ostringstream os;
    for(unsigned int i = 0; i < indent_level; ++i)
        os << "\xC2\xA0"s; // UTF-8 No-Break Space
    return os.str();
}

const std::string
epwing::XDXFPrinter::newline() const {
    return "<br/>";
}

const std::string
epwing::XDXFPrinter::begin_superscript() const {
    return "<sup>";
}

const std::string
epwing::XDXFPrinter::end_superscript() const {
    return "</sup>";
}

const std::string
epwing::XDXFPrinter::begin_emphasis() const {
    return "<i>";
}

const std::string
epwing::XDXFPrinter::end_emphasis() const {
    return "</i>";
}

const std::string
epwing::XDXFPrinter::begin_candidate() const {
    return "<kref>";
}

const std::string
epwing::XDXFPrinter::end_candidate_group(unsigned int page, unsigned int offset) const {
    std::ostringstream os;
    os << "</kref>"
       << "<kref " << idref_tag(page, offset) << ">"
       << "[ref]"
       << "</kref>\n";
    return os.str();
}

const std::string
epwing::XDXFPrinter::end_candidate_leaf() const {
    return "</kref>";
}

const std::string
epwing::XDXFPrinter::begin_reference() const {
    return "<kref>";
}

const std::string
epwing::XDXFPrinter::end_reference(unsigned int page, unsigned int offset) const {
    std::ostringstream os;
    os << "</kref>"
       << "<kref " << idref_tag(page, offset) << ">"
       << "[ref]"
       << "</kref>\n";
    return os.str();
}

const std::string
epwing::XDXFPrinter::idref_tag(unsigned int page, unsigned int offset) const {
    std::ostringstream os;
    os << R"(idref=")" << subbook_code << ':' << page << ':' << offset << '"';
    return os.str();
}
