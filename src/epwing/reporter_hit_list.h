#ifndef EPWING_EXPORTER_REPORTER_HIT_LIST__H
#define EPWING_EXPORTER_REPORTER_HIT_LIST__H

#include "reporter_interface.h"

namespace epwing {
    struct HitListReporter final : public Reporter {
        void report(int, std::ostream &) const override;

        size_type hits = 0;
        size_type duplicates = 0;
        size_type headings_skipped = 0;
    };
}

#endif // EPWING_EXPORTER_REPORTER_HIT_LIST_H
