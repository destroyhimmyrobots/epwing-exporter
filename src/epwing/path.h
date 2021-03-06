#ifndef EPWING_EXPORTER_EPWING_PATH_H
#define EPWING_EXPORTER_EPWING_PATH_H

#ifndef __APPLE__
#include <filesystem>
#else
#include <string>
#endif

namespace epwing {
#ifdef __APPLE__
    using path = std::string;
#else
    using path = std::filesystem::path;
#endif
}

#endif // EPWING_EXPORTER_EPWING_PATH_H
