#ifndef EPWING_EXPORTER_REPORTER_WORD_CODE_H
#define EPWING_EXPORTER_REPORTER_WORD_CODE_H

#include "reporter_interface.h"
#include "reporter_container.h"
#include "reporter_hit_list.h"

namespace epwing {
    struct WordCodeReporter final : public Reporter {
        WordCodeReporter(const ContainerReporter &, const HitListReporter &);

        void report(int, std::ostream &) const override;

        const ContainerReporter container_reporter;
        const HitListReporter hit_list_reporter;
    };
}

#endif // EPWING_EXPORTER_REPORTER_WORD_CODE_H
