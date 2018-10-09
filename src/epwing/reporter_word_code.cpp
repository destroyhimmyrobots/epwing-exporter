#include "reporter_word_code.h"

void
epwing::WordCodeReporter::report(int depth, std::ostream &os) const {
    os << PAD(depth) << "container:" << '\n';
    container_reporter.report(depth + 1, os);
    os << PAD(depth) << "hit_list_reporter:" << '\n';
    hit_list_reporter.report(depth + 1, os);
}

epwing::WordCodeReporter::WordCodeReporter(const ContainerReporter &container_reporter,
                                           const HitListReporter &hit_list_reporter)
    : container_reporter{container_reporter}, hit_list_reporter{hit_list_reporter} {}
