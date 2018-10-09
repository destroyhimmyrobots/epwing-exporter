#ifndef EPWING_EXPORTER_REPORTER_SUB_BOOK_H
#define EPWING_EXPORTER_REPORTER_SUB_BOOK_H

#include "reporter_interface.h"
#include "reporter_container.h"
#include "reporter_gaiji.h"
#include "reporter_word_code.h"

namespace epwing {
    struct SubBookReporter final : public Reporter {
        SubBookReporter(const ContainerReporter &text,
                        const WordCodeReporter &alphabet,
                        const WordCodeReporter &kana,
                        const WordCodeReporter &other);

        void report(int, std::ostream &) const override;

        const ContainerReporter text;
        const WordCodeReporter alphabet, kana, other;
    };
}

#endif // EPWING_EXPORTER_REPORTER_SUB_BOOK_H
