#ifndef EPWING_EXPORTER_EPWING_PRINTER_HTML5_H
#define EPWING_EXPORTER_EPWING_PRINTER_HTML5_H

#include <string>
#include <string_view>
#include <sstream>
#include <vector>

#include "hookset_interface.h"

extern "C" {
#include <eb/defs.h>
}

namespace epwing {
    class Html5Printer final : public HookSet {
    public:
        explicit Html5Printer(EB_Subbook_Code subbook_code);

        const std::string begin_subscript() const override;

        const std::string end_subscript() const override;

        const std::string set_indent(unsigned int indent_level) const override;

        const std::string newline() const override;

        const std::string begin_superscript() const override;

        const std::string end_superscript() const override;

        const std::string begin_emphasis() const override;

        const std::string end_emphasis() const override;

        const std::string begin_candidate() const override;

        const std::string end_candidate_group(unsigned int page, unsigned int offset) const override;

        const std::string end_candidate_leaf() const override;

        const std::string begin_reference() const override;

        const std::string end_reference(unsigned int page, unsigned int offset) const override;

/*
        const std::string begin_keyword() const override;

        const std::string end_keyword() const override;
*/

    private:
        EB_Subbook_Code subbook_code;
    };
}

#endif // EPWING_EXPORTER_EPWING_PRINTER_HTML5_H
