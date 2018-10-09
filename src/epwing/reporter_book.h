#ifndef EPWING_EXPORTER_REPORTER_BOOK_H
#define EPWING_EXPORTER_REPORTER_BOOK_H

#include <vector>

#include "reporter_interface.h"
#include "reporter_gaiji.h"
#include "reporter_sub_book.h"

namespace epwing {
    class BookReporter final : public Reporter {
    public:
        BookReporter(GaijiReporter &gaiji_reporter, std::vector<SubBookReporter> sub_book_reporters);
        using Reporter::report;

        void report(int, std::ostream &) const override;

    private:
        GaijiReporter &gaiji_reporter;
        std::vector<SubBookReporter> sub_books;
    };
}

#endif // EPWING_EXPORTER_REPORTER_BOOK_H
