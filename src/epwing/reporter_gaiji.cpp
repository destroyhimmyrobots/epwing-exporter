#include "reporter_gaiji.h"

void epwing::GaijiReporter::report(int depth, std::ostream &os) const {
    os << PAD(depth) << REPORT(narrow_found)
       << PAD(depth) << REPORT(narrow_missed)
       << PAD(depth) << REPORT(wide_found)
       << PAD(depth) << REPORT(wide_missed);
}
