#include "reporter_deduplicator.h"

void
epwing::DeduplicatorReporter::report(int depth, std::ostream &os) const {
    os << PAD(depth) << REPORT(heading_position_duplicates)
       << PAD(depth) << REPORT(text_position_duplicates)
       << PAD(depth) << REPORT(heading_text_duplicates)
       << PAD(depth) << REPORT(hit_full_duplicates)
       << PAD(depth) << REPORT(hit_position_duplicates)
       << PAD(depth) << REPORT(hit_position_text_duplicates);
}
