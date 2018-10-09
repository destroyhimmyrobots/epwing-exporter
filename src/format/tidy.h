#ifndef EPWING_EXPORTER_TIDY_FACTORY_H
#define EPWING_EXPORTER_TIDY_FACTORY_H

#include <iostream>
#include <memory>

#include "path.h"

namespace format {
    enum class TidyResult {
        ok = 0,
        warnings = 1,
        errors = 2,
    };

    class Tidy final {
    public:
        static Tidy html(const path&output_file, const path&error_file);
        static Tidy xml(const path &output_file, const path&error_file);

        ~Tidy();

        int format();

        TidyResult report();

    private:
        Tidy();

        Tidy(const path &output_file, const path &error_file, bool enable_xml);

        class TidyDocImpl;

        std::unique_ptr<TidyDocImpl> tidy_doc_impl;
    };
}
#endif // EPWING_EXPORTER_TIDY_FACTORY_H
