#ifndef EPWING_EXPORTER_EPWING_HTML5_H
#define EPWING_EXPORTER_EPWING_HTML5_H

#include <iostream>
#include <string>
#include <string_view>

extern "C" {
#include <eb/defs.h>
}

#include "converter_interface.h"
#include "hookset_interface.h"
#include "path.h"

namespace epwing {
    class HTML5Converter final : public Converter {
    public:
        explicit HTML5Converter(std::ostream &os);

        void book_start() override;

        void subbook_start(EB_Subbook_Code) override;

        void subbook_title(EB_Subbook_Code, std::string_view subbook_title) override;

        void text_start(EB_Subbook_Code, const EB_Position &position) override;

        void text_article(EB_Subbook_Code, std::string_view text) override;

        void text_stop() override;

        void search_start(EB_Subbook_Code) override;

        void search_article_start(EB_Subbook_Code) override;

        void search_article_heading(EB_Subbook_Code, const EB_Position &, std::string_view) override;

        void search_article_text(EB_Subbook_Code, const EB_Position &, std::string_view) override;

        void search_article_stop() override;

        void search_stop() override;

        void subbook_stop() override;

        void book_stop() override;

    private:
        std::ostream &os;

        inline void sp_id_tag(EB_Subbook_Code, const EB_Position &);
    };
}

#endif // EPWING_EXPORTER_EPWING_HTML5_H
