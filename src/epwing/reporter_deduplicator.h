#ifndef EPWING_EXPORTER_REPORTER_DEDUPLICATOR_H
#define EPWING_EXPORTER_REPORTER_DEDUPLICATOR_H

#include "reporter_interface.h"

namespace epwing {
    struct DeduplicatorReporter final : public Reporter {
        void report(int, std::ostream &) const override;

        size_type heading_position_duplicates = 0;
        size_type text_position_duplicates = 0;
        size_type heading_text_duplicates = 0;

        size_type hit_full_duplicates = 0;
        size_type hit_position_duplicates = 0;
        size_type hit_position_text_duplicates = 0;
    };
}

#endif // EPWING_EXPORTER_REPORTER_DEDUPLICATOR_H
