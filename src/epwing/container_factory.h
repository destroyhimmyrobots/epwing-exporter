#ifndef EPWING_EXPORTER_CONTAINER_FACTORY_H
#define EPWING_EXPORTER_CONTAINER_FACTORY_H

#include <string_view>
#include "container.h"

namespace epwing {
    class ContainerFactory {
    public:
        ContainerFactory(IConv &euc_jp, IConv &gb2313, IConv &iso_8859_1);

        virtual Container get_instance(EB_Subbook_Code, const Dictionary &, ContainerReporter &) const = 0;

    protected:
        IConv &euc_jp;
        IConv &gb2313;
        IConv &iso_8859_1;
    };

    class HTML5ContainerFactory final : public ContainerFactory {
    public:
        using ContainerFactory::ContainerFactory;

        Container get_instance(EB_Subbook_Code, const Dictionary &, ContainerReporter &) const override;
    };

    class XDXFContainerFactory final : public ContainerFactory {
    public:
        using ContainerFactory::ContainerFactory;

        Container get_instance(EB_Subbook_Code, const Dictionary &, ContainerReporter &) const override;
    };
}

#endif // EPWING_EXPORTER_CONTAINER_FACTORY_H
