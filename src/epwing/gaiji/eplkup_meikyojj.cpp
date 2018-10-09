#include "eplkup_meikyojj.h"

const epwing::gaiji::LookupTable &
epwing::gaiji::eplkup::meikyojj::narrow() {
    static const LookupTable narrow{
        {0xA36B, u8"Ⅰ"s},
        {0xA36C, u8"Ⅱ"s},
        {0xA36D, u8"Ⅲ"s},
        {0xA36E, u8"Ⅳ"s},
        {0xA36F, u8"Ⅴ"s},
    };
    return narrow;
}

const epwing::gaiji::LookupTable &
epwing::gaiji::eplkup::meikyojj::wide() {
    static const LookupTable wide{
        {0xB027, u8"①"s},
        {0xB028, u8"②"s},
        {0xB029, u8"③"s},
        {0xB02A, u8"④"s},
        {0xB02B, u8"⑤"s},
        {0xB02C, u8"⑥"s},
        {0xB02D, u8"⑦"s},
        {0xB02E, u8"⑧"s},
        {0xB02F, u8"⑨"s},
        {0xB030, u8"⑩"s},
        {0xB031, u8"⑪"s},
        {0xB032, u8"⑫"s},
        {0xB033, u8"⑬"s},
        {0xB034, u8"⑭"s},
        {0xB035, u8"⑮"s},
        {0xB036, u8"⑯"s},
        {0xB037, u8"⑰"s},
        {0xB038, u8"⑱"s},
        {0xB039, u8"⑲"s},
        {0xB03A, u8"⑳"s},
        {0xB03B, u8"⑴"s},
        {0xB03C, u8"⑵"s},
        {0xB03D, u8"⑶"s},
        {0xB03E, u8"〘"s},
        {0xB03F, u8"〙"s},
        {0xB042, u8"㋐"s},
        {0xB043, u8"㋑"s},
        {0xB044, u8"㋒"s},
        {0xB045, u8"㋓"s},
        {0xB046, u8"㋔"s},
        {0xB047, u8"㋕"s},
        {0xB048, u8"㋖"s},
        {0xB049, u8"㋗"s},
        {0xB04A, u8"㋘"s},
        {0xB04B, u8"㋙"s},
        {0xB04C, u8"㋚"s},
        {0xB04D, u8"㋛"s},
        {0xB04E, u8"㋜"s},
        {0xB04F, u8"㋝"s},
        {0xB050, u8"㋞"s},
        {0xB051, u8"㋟"s},
        {0xB052, u8"㋠"s},
        {0xB053, u8"㋡"s},
        {0xB054, u8"㋢"s},
        {0xB055, u8"㋣"s},
        {0xB27B, u8"㊀"s},
        {0xB27C, u8"㊁"s},
        {0xB27D, u8"㊂"s},
        {0xB322, u8"㋤"s},
    };
    return wide;
}
