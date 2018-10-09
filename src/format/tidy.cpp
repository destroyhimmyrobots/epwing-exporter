#include "tidy.h"

extern "C" {
#include <tidy.h>
}

/*
static int input_source_get_byte(void *context) {
    return reinterpret_cast<std::istream *>(context)->get();
}

static void input_source_unget_byte(void *context, byte bt) {
    reinterpret_cast<std::istream *>(context)->putback(bt);
}

static Bool input_source_eof_func(void *context) {
    return reinterpret_cast<std::istream *>(context)->eof() ? yes : no;
}
*/

class format::Tidy::TidyDocImpl {
public:
    TidyDocImpl(const path &output_file, const path &error_file, bool enable_xml)
        : tdoc{tidyCreate()} {
        tidyOptSetBool(tdoc, TidyXmlTags, enable_xml ? yes : no);
        tidyOptSetBool(tdoc, TidyQuoteNbsp, no);
        tidyOptSetInt(tdoc, TidyIndentContent, TidyAutoState);
        tidyOptResetToDefault(tdoc, TidyIndentSpaces);
        tidySetCharEncoding(tdoc, "utf8");
        tidyOptSetBool(tdoc, TidyWriteBack, yes);
        tidyOptSetValue(tdoc, TidyOutFile, output_file.c_str());
        tidySetErrorFile(tdoc, error_file.c_str());
        tidyOptSetInt(tdoc, TidyWrapLen, 0U);
    };

    ~TidyDocImpl() {
        tidyRelease(tdoc);
    }

    int format() {
        /*
        auto source = TidyInputSource{
            &is,
            reinterpret_cast<TidyGetByteFunc> (&input_source_get_byte),
            reinterpret_cast<TidyUngetByteFunc> (&input_source_unget_byte),
            reinterpret_cast<TidyEOFFunc> (&input_source_eof_func),
        };
        auto status = tidyParseSource(tdoc, &source);
        */
        auto output_file = tidyOptGetValue(tdoc, TidyOutFile);
        auto status = tidyParseFile(tdoc, output_file);
        if (status >= 0) status = tidyCleanAndRepair(tdoc);
        if (status >= 0) status = tidyRunDiagnostics(tdoc);
        if (status >= 0) status = tidySaveFile(tdoc, output_file);
        return status;
    }

    TidyResult report() {
        auto content_errors = tidyErrorCount(tdoc);
        auto content_warnings = tidyWarningCount(tdoc);
        if (content_errors + content_warnings > 0) tidyErrorSummary(tdoc);
        if (content_errors > 0) return TidyResult::errors;
        if (content_warnings > 0) return TidyResult::warnings;
        return TidyResult::ok;
    }

private:
    TidyDoc tdoc;
};

format::Tidy
format::Tidy::html(const path &output_file, const path &error_file) {
    return Tidy{output_file, error_file, false};
}

format::Tidy
format::Tidy::xml(const path &output_file, const path &error_file) {
    return Tidy{output_file, error_file, true};
}

format::Tidy::Tidy(const path &output_file, const path &error_file, bool enable_xml)
    : tidy_doc_impl{std::make_unique<TidyDocImpl>(output_file, error_file, enable_xml)} {}

int format::Tidy::format() {
    return tidy_doc_impl->format();
}

format::TidyResult format::Tidy::report() {
    return tidy_doc_impl->report();
}

format::Tidy::Tidy() : tidy_doc_impl{nullptr} {}

format::Tidy::~Tidy() = default;
