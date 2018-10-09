#include "reporter_sub_book.h"

epwing::SubBookReporter::SubBookReporter(const ContainerReporter &text,
                                         const WordCodeReporter &alphabet,
                                         const WordCodeReporter &kana,
                                         const WordCodeReporter &other)
    : text{text}, alphabet{alphabet}, kana{kana}, other{other} {}

void
epwing::SubBookReporter::report(int depth, std::ostream &os) const {
    os << "text:" << '\n';
    text.report(depth + 1, os);
    os << PAD(depth) << "alphabet:" << '\n';
    alphabet.report(depth + 1, os);
    os << PAD(depth) << "kana:" << '\n';
    kana.report(depth + 1, os);
    os << PAD(depth) << "other:" << '\n';
    other.report(depth + 1, os);
}
