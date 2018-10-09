#include "reporter_book.h"

using namespace std::literals::string_literals;

epwing::BookReporter::BookReporter(epwing::GaijiReporter &gaiji_reporter,
                                   std::vector<epwing::SubBookReporter> sub_book_reporters)
    : gaiji_reporter{gaiji_reporter}, sub_books{sub_book_reporters} {}

void epwing::BookReporter::report(int depth, std::ostream &os) const {
    os << PAD(depth) << "sub_books:" << '\n';

    for (std::size_t i = 0; i < sub_books.size(); ++i) {
        os << "- "s;
        sub_books[i].report(depth + 1, os);
    }

    os << PAD(depth) << "gaiji:" << '\n';
    gaiji_reporter.report(depth + 1, os);
}
