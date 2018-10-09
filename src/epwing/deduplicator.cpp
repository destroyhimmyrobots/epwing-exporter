#include "deduplicator.h"

epwing::Deduplicator::Deduplicator(DeduplicatorReporter &reporter)
    : reporter{reporter} {}

bool operator==(const EB_Position &lhs, const EB_Position &rhs) {
    return lhs.page == rhs.page && lhs.offset == rhs.offset;
}

bool
epwing::Deduplicator::is_duplicate_position(const EB_Position &position) {
    const auto found = positions.find(position) != positions.end();
    if (!found) positions.insert(position);
    return found;
}

bool
epwing::Deduplicator::is_duplicate_heading(std::string_view heading) {
    const std::string h{heading.data(), heading.size()};
    const auto found = headings.find(h) != headings.end();
    if (!found) headings.insert(h);
    return found;
}

bool
epwing::Deduplicator::is_duplicate(const EB_Hit &hit, std::string_view heading) {
    const auto head_pos_dup = is_duplicate_position(hit.heading);
    const auto text_pos_dup = is_duplicate_position(hit.text);
    const auto head_txt_dup = is_duplicate_heading(heading);

    if (head_pos_dup) ++reporter.heading_position_duplicates;
    if (text_pos_dup) ++reporter.text_position_duplicates;
    if (head_txt_dup) ++reporter.heading_text_duplicates;

    if (text_pos_dup && head_pos_dup && head_txt_dup) {
        ++reporter.hit_full_duplicates;
        return true;
    }

    if (text_pos_dup && head_pos_dup) {
        ++reporter.hit_position_duplicates;
        return true;
    }

    if (text_pos_dup && head_txt_dup) {
        ++reporter.hit_position_text_duplicates;
        return true;
    }

    return false;
}
