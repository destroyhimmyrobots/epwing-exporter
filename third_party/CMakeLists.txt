include_guard()

string(REPLACE "-Werror" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
string(REPLACE "-Werror" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

if (APPLE)
    # Policy CMP0042 is not set: MACOSX_RPATH is enabled by default.
    # https://blog.kitware.com/upcoming-in-cmake-2-8-12-osx-rpath-support/
    set(CMAKE_MACOSX_RPATH ON)
endif ()

include(eb.cmake)
include(iconv.cmake)
include(gflags.cmake)
include(googletest.cmake)
include(gsl.cmake)
include(tidy.cmake)
include(zlib.cmake)
