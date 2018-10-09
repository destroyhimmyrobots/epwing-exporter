#ifndef EPWING_EXPORTER_REPORTER_CONTAINER_H
#define EPWING_EXPORTER_REPORTER_CONTAINER_H

#include "reporter_interface.h"

namespace epwing {
    struct ContainerReporter final : public Reporter {
        void report(int, std::ostream &) const override;

        size_type begin_subscript = 0;
        size_type end_subscript = 0;
        size_type set_indent = 0;
        size_type newline = 0;
        size_type begin_superscript = 0;
        size_type end_superscript = 0;
        size_type begin_emphasis = 0;
        size_type end_emphasis = 0;
        size_type begin_candidate = 0;
        size_type end_candidate_group = 0;
        size_type end_candidate_leaf = 0;
        size_type begin_reference = 0;
        size_type end_reference = 0;
        size_type narrow_font = 0;
        size_type wide_font = 0;
        size_type narrow_JISX0208 = 0;
        size_type wide_JISX0208 = 0;
        size_type gb2313 = 0;
        size_type iso8859_1 = 0;
        size_type begin_keyword = 0;
        size_type end_keyword = 0;
    };
}

#endif // EPWING_EXPORTER_REPORTER_CONTAINER_H
