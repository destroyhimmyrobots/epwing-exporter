#include "container_factory.h"
#include "printer_xdxf.h"

epwing::ContainerFactory::ContainerFactory(IConv &euc_jp, IConv &gb2313, IConv &iso_8859_1)
    : euc_jp{euc_jp}, gb2313{gb2313}, iso_8859_1{iso_8859_1} {}

epwing::Container
epwing::HTML5ContainerFactory::get_instance(EB_Subbook_Code subbook_code,
                                            const Dictionary &dictionary,
                                            ContainerReporter &container_reporter) const {
    static const Html5Printer hook_set{subbook_code};
    return Container{
        euc_jp,
        gb2313,
        iso_8859_1,
        dictionary,
        hook_set,
        container_reporter,
    };
}

epwing::Container
epwing::XDXFContainerFactory::get_instance(EB_Subbook_Code subbook_code,
                                           const Dictionary &dictionary,
                                           ContainerReporter &container_reporter) const {
    static const XDXFPrinter hook_set{subbook_code};
    return Container{
        euc_jp,
        gb2313,
        iso_8859_1,
        dictionary,
        hook_set,
        container_reporter,
    };
}
