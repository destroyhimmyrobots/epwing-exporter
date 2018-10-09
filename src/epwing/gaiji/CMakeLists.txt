include_guard()

add_library(
    gaiji

    # INTERFACE
    gaiji.h

    # PUBLIC
    empty.h
    eplkup_chujiten.h
    eplkup_daijirin.h
    eplkup_daijisen.h
    eplkup_genius.h
    eplkup_kojien.h
    eplkup_meikyojj.h
    eplkup_meikyou.h
    eplkup_snmkg99.h
    eplkup_wadai5.h

    # PRIVATE
    empty.cpp
    eplkup_chujiten.cpp
    eplkup_daijirin.cpp
    eplkup_daijisen.cpp
    eplkup_genius.cpp
    eplkup_kojien.cpp
    eplkup_meikyojj.cpp
    eplkup_meikyou.cpp
    eplkup_snmkg99.cpp
    eplkup_wadai5.cpp
)
