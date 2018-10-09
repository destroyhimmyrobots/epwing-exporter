#ifndef EPWING_EXPORTER_EPWING_COUNTER_H
#define EPWING_EXPORTER_EPWING_COUNTER_H

#include <string>
#include <string_view>
#include <unordered_set>

#include "reporter_interface.h"
#include "reporter_deduplicator.h"

extern "C" {
#include <eb/defs.h>
}

bool operator==(const EB_Position &lhs, const EB_Position &rhs);

// https://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way
// http://szudzik.com/ElegantPairing.pdf

namespace std {
    template<>
    struct hash<EB_Position> {
        std::size_t operator()(const EB_Position &key) const {
            const auto page = static_cast<std::size_t>(key.page);
            const auto offset = static_cast<std::size_t>(key.offset);
            if (page >= offset) {
                return page * page + page + offset;
            } else {
                return page + offset * offset;
            }
        }
    };
}

namespace epwing {
    class Deduplicator final {
    public:
        explicit Deduplicator(DeduplicatorReporter &reporter);

        bool is_duplicate(const EB_Hit &position, std::string_view heading);

    private:
        bool is_duplicate_position(const EB_Position &position);

        bool is_duplicate_heading(std::string_view heading);

        std::unordered_set<std::string> headings;
        std::unordered_set<EB_Position> positions;
        DeduplicatorReporter &reporter;
    };
}

#endif // EPWING_EXPORTER_EPWING_COUNTER_H
