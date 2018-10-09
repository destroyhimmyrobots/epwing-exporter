#ifndef EPWING_EXPORTER_EPWING_CONTAINER_H
#define EPWING_EXPORTER_EPWING_CONTAINER_H

#include <string>
#include <string_view>

#include "deduplicator.h"
#include "dictionary.h"
#include "iconv.h"
#include "printer_html5.h"
#include "reporter_interface.h"
#include "reporter_container.h"

namespace epwing {
    class Container final {
    public:
        Container(IConv &euc_jp,
                  IConv &gb2313,
                  IConv &iso_8859_1,
                  const Dictionary &dictionary,
                  const HookSet &hook_set,
                  ContainerReporter &reporter);

        const std::string begin_subscript();

        const std::string end_subscript();

        const std::string set_indent(unsigned int indent_level);

        const std::string newline();

        const std::string begin_superscript();

        const std::string end_superscript();

        const std::string begin_emphasis();

        const std::string end_emphasis();

        const std::string begin_candidate();

        const std::string end_candidate_group(unsigned int page, unsigned int offset);

        const std::string end_candidate_leaf();

        const std::string begin_reference();

        const std::string end_reference(unsigned int page, unsigned int offset);

        const std::string narrow_font(unsigned int gaiji_code);

        const std::string wide_font(unsigned int gaiji_code);

        const std::string narrow_JISX0208(std::string_view view);

        const std::string wide_JISX0208(std::string_view view);

        const std::string gb2313(std::string_view view);

        const std::string iso8859_1(std::string_view view);

/*
        const std::string begin_keyword();

        const std::string end_keyword();
*/

    private:
        // Reference might be triggered once per "spaced character" before closing.
        bool should_open_reference() noexcept;

        bool should_close_reference() noexcept;

        IConv &euc_jp, &gb2313_, &iso_8859_1;
        const Dictionary dictionary;

        const HookSet& hook_set;
        ContainerReporter &reporter;

        bool reference_open = false;
    };
}

#endif // EPWING_EXPORTER_EPWING_CONTAINER_H
