#ifndef EPWING_EXPORTER_CONVERTER_XDXF_H
#define EPWING_EXPORTER_CONVERTER_XDXF_H

#include <iostream>
#include <string_view>

#include "converter_interface.h"
#include "path.h"

namespace epwing {
    class XDXFConverter final : public Converter {
    public:
        explicit XDXFConverter(std::string_view lang_from, std::string_view lang_to, std::ostream &os);

        void book_start() override;

        void subbook_start(EB_Subbook_Code code) override;

        void subbook_title(EB_Subbook_Code code, std::string_view view) override;

        void text_start(EB_Subbook_Code code, const EB_Position &position) override;

        void text_article(EB_Subbook_Code code, std::string_view view) override;

        void text_stop() override;

        void search_start(EB_Subbook_Code code) override;

        void search_article_start(EB_Subbook_Code code) override;

        void search_article_heading(EB_Subbook_Code code, const EB_Position &position, std::string_view view) override;

        void search_article_text(EB_Subbook_Code code, const EB_Position &position, std::string_view view) override;

        void search_article_stop() override;

        void search_stop() override;

        void subbook_stop() override;

        void book_stop() override;

    private:
        std::ostream &os;
        std::string lang_from, lang_to;
    };
}

#endif // EPWING_EXPORTER_CONVERTER_XDXF_H
