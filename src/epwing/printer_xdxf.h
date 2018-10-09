#ifndef EPWING_EXPORTER_PRINTER_XDXF_H
#define EPWING_EXPORTER_PRINTER_XDXF_H

#include <string>

extern "C" {
#include <eb/defs.h>
}

#include "hookset_interface.h"

namespace epwing {
    class XDXFPrinter final : public HookSet {
    public:
        explicit XDXFPrinter(EB_Subbook_Code);

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

    private:
        const std::string idref_tag(unsigned int page, unsigned int offset) const;

        EB_Subbook_Code subbook_code;
    };
}

#endif // EPWING_EXPORTER_PRINTER_XDXF_H
