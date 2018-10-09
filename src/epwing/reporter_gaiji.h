#ifndef EPWING_EXPORTER_REPORTER_GAIJI_H
#define EPWING_EXPORTER_REPORTER_GAIJI_H

#include "reporter_interface.h"

namespace epwing {
    struct GaijiReporter final : public Reporter {
        void report(int, std::ostream &) const override;

        size_type narrow_found = 0;
        size_type narrow_missed = 0;
        size_type wide_found = 0;
        size_type wide_missed = 0;
    };
}

#endif // EPWING_EXPORTER_REPORTER_GAIJI_H
