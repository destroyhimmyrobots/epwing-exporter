#include "reporter_container.h"

void
epwing::ContainerReporter::report(int depth, std::ostream &os) const {
    os << PAD(depth) << REPORT(begin_subscript)
       << PAD(depth) << REPORT(end_subscript)
       << PAD(depth) << REPORT(set_indent)
       << PAD(depth) << REPORT(newline)
       << PAD(depth) << REPORT(begin_superscript)
       << PAD(depth) << REPORT(end_superscript)
       << PAD(depth) << REPORT(begin_emphasis)
       << PAD(depth) << REPORT(end_emphasis)
       << PAD(depth) << REPORT(begin_candidate)
       << PAD(depth) << REPORT(end_candidate_group)
       << PAD(depth) << REPORT(end_candidate_leaf)
       << PAD(depth) << REPORT(begin_reference)
       << PAD(depth) << REPORT(end_reference)
       << PAD(depth) << REPORT(narrow_font)
       << PAD(depth) << REPORT(wide_font)
       << PAD(depth) << REPORT(narrow_JISX0208)
       << PAD(depth) << REPORT(wide_JISX0208)
       << PAD(depth) << REPORT(gb2313)
       << PAD(depth) << REPORT(iso8859_1)
       << PAD(depth) << REPORT(begin_keyword)
       << PAD(depth) << REPORT(end_keyword);
}
