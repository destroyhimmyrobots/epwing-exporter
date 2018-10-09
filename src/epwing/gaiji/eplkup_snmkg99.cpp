#include "eplkup_snmkg99.h"

const epwing::gaiji::LookupTable &
epwing::gaiji::eplkup::snmkg99::narrow() {
    static const LookupTable narrow{};
    return narrow;
}

const epwing::gaiji::LookupTable &
epwing::gaiji::eplkup::snmkg99::wide() {
    static const LookupTable wide{
        {0xB467, u8"⇒"s},
        {0xB468, u8"⇔"s},
        {0xB55F, u8"⁎"s},
        {0xB560, u8"⁑"s},
    };
    return wide;
}
