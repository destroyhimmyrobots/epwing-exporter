#ifndef EPWING_EXPORTER_HOOKSET_INTERFACE_H
#define EPWING_EXPORTER_HOOKSET_INTERFACE_H

#include <string>
#include <string_view>

namespace epwing {
    class HookSet {
    public:
        virtual const std::string begin_subscript() const = 0;

        virtual const std::string end_subscript() const = 0;

        virtual const std::string set_indent(unsigned int indent_level) const = 0;

        virtual const std::string newline() const = 0;

        virtual const std::string begin_superscript() const = 0;

        virtual const std::string end_superscript() const = 0;

        virtual const std::string begin_emphasis() const = 0;

        virtual const std::string end_emphasis() const = 0;

        virtual const std::string begin_candidate() const = 0;

        virtual const std::string end_candidate_group(unsigned int page, unsigned int offset) const = 0;

        virtual const std::string end_candidate_leaf() const = 0;

        virtual const std::string begin_reference() const = 0;

        virtual const std::string end_reference(unsigned int page, unsigned int offset) const = 0;

/*
        virtual const std::string narrow_font(unsigned int) const = 0;

        virtual const std::string wide_font(unsigned int) const = 0;

        virtual const std::string narrow_JISX0208(std::string_view) const = 0;

        virtual const std::string wide_JISX0208(std::string_view) const = 0;

        virtual const std::string gb2313(std::string_view) const = 0;

        virtual const std::string iso8859_1(std::string_view) const = 0;

        virtual const std::string begin_keyword() const = 0;

        virtual const std::string end_keyword() const = 0;
*/
    };
}

#endif // EPWING_EXPORTER_HOOKSET_INTERFACE_H
