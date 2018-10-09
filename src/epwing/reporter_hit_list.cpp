#include "reporter_hit_list.h"

void
epwing::HitListReporter::report(int depth, std::ostream &os) const {
    os << PAD(depth) << REPORT(hits)
       << PAD(depth) << REPORT(duplicates)
       << PAD(depth) << REPORT(headings_skipped);
}
