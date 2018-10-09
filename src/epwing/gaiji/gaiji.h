#ifndef EPWING_EXPORTER_EPWING_GAIJI_H
#define EPWING_EXPORTER_EPWING_GAIJI_H

#include <string>
#include <unordered_map>

namespace epwing::gaiji {
    using namespace std::literals::string_literals;
    using LookupTable = const std::unordered_map<unsigned int, const std::string>;
}

#endif // EPWING_EXPORTER_EPWING_GAIJI_H
