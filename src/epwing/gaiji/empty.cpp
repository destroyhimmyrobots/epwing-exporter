#include "empty.h"

const epwing::gaiji::LookupTable &
epwing::gaiji::empty::narrow() {
    static const LookupTable narrow{};
    return narrow;
}

const epwing::gaiji::LookupTable &
epwing::gaiji::empty::wide() {
    static const LookupTable wide{};
    return wide;
}
