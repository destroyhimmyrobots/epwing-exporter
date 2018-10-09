#ifndef EPWING_EXPORTER_EPWING_CONVERTER_H
#define EPWING_EXPORTER_EPWING_CONVERTER_H

#include <string>
#include <string_view>

extern "C" {
#include <eb/defs.h>
}

#include "container.h"

namespace epwing {
    class Converter {
    public:
        virtual void book_start() = 0;

        virtual void subbook_start(EB_Subbook_Code) = 0;

        virtual void subbook_title(EB_Subbook_Code, std::string_view) = 0;

        virtual void text_start(EB_Subbook_Code, const EB_Position &) = 0;

        virtual void text_article(EB_Subbook_Code, std::string_view) = 0;

        virtual void text_stop() = 0;

        virtual void search_start(EB_Subbook_Code) = 0;

        virtual void search_article_start(EB_Subbook_Code) = 0;

        virtual void search_article_heading(EB_Subbook_Code, const EB_Position &, std::string_view) = 0;

        virtual void search_article_text(EB_Subbook_Code, const EB_Position &, std::string_view) = 0;

        virtual void search_article_stop() = 0;

        virtual void search_stop() = 0;

        virtual void subbook_stop() = 0;

        virtual void book_stop() = 0;
    };
}

#endif // EPWING_EXPORTER_CONVERTER_H
