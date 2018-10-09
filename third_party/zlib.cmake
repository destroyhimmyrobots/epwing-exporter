include_guard()

include(FetchContent)

FetchContent_Declare(
    zlib
    URL https://zlib.net/fossils/zlib-1.2.11.tar.gz
    URL_HASH SHA256=c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1
    TIMEOUT 120
)

FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
    FetchContent_Populate(zlib)
    add_subdirectory(${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})
endif()

if(BUILD_SHARED_LIBRARIES)
    add_library(zlib-alias ALIAS zlib)
else()
    add_library(zlib-alias ALIAS zlibstatic)
endif()
