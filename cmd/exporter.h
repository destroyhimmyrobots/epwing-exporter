#ifndef EPWING_EXPORTER_CMD_EXPORTER_H
#define EPWING_EXPORTER_CMD_EXPORTER_H

#include <algorithm>
#include <array>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <string_view>
#include <utility>

#include <gflags/gflags.h>
#include <gsl/gsl>

extern "C" {
#include <eb/eb.h>
#include <eb/error.h>
#include <eb/text.h>
}

DECLARE_string(epwing_directory);
DECLARE_string(exporter_errors_file);
DECLARE_string(tidy_errors_file);
DECLARE_string(html5_file);
DECLARE_string(metrics_file);
DECLARE_string(xdxf_file);

#endif // EPWING_EXPORTER_CMD_H
