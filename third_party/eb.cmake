include_guard()

include(ExternalProject)
include(FetchContent)

FetchContent_Declare(
    eb
    URL ftp://ftp.sra.co.jp/pub/misc/eb/eb-4.4.3.tar.bz2
    URL_HASH SHA256=abe710a77c6fc3588232977bb2f30a2e69ddfbe9fa8d0b05b0d67d95e36f4b5f
    TIMEOUT 120
)

FetchContent_GetProperties(eb)
if (NOT eb_POPULATED)
    FetchContent_Populate(eb)
endif ()

# http://lists.llvm.org/pipermail/llvm-dev/2017-October/118177.html
# libeb is under-linked to zlib: http://goutou.mamagoto.com/wiki/underlinking#%E4%B8%8B%E6%BD%9C%E7%B5%90%E5%90%88%E3%81%A8%E3%81%AF%E4%BD%95%E3%81%8B
# Do not pass --enable-pthread to configure.
# The function eb_is_text_stopped fails to release the lock on its EB_Book argument.
ExternalProject_Add(
    eb
    SOURCE_DIR ${eb_SOURCE_DIR}
    INSTALL_DIR ${eb_BINARY_DIR}
    CONFIGURE_COMMAND CC=${CMAKE_C_COMPILER} <SOURCE_DIR>/configure --with-pic --prefix <INSTALL_DIR> --libdir <INSTALL_DIR>/lib  "CFLAGS=${EB_C_FLAGS}"
    BUILD_COMMAND make -j 4
    PATCH_COMMAND patch -p0 < ${CMAKE_SOURCE_DIR}/third_party/match.c.patch
    UPDATE_COMMAND ""
    INSTALL_COMMAND make install
    TEST_COMMAND ""
    BUILD_IN_SOURCE ON
)

include_directories(${eb_BINARY_DIR}/include/eb)

add_library(eb-static STATIC IMPORTED GLOBAL)
add_library(eb-shared SHARED IMPORTED GLOBAL)

if (APPLE)
    set_target_properties(eb-static PROPERTIES IMPORTED_LOCATION ${eb_BINARY_DIR}/lib/libeb.a)
    set_target_properties(eb-shared PROPERTIES IMPORTED_LOCATION ${eb_BINARY_DIR}/lib/libeb.16.dylib)
elseif (UNIX)
    set_target_properties(eb-static PROPERTIES IMPORTED_LOCATION ${eb_BINARY_DIR}/lib/libeb.a)
    set_target_properties(eb-shared PROPERTIES IMPORTED_LOCATION ${eb_BINARY_DIR}/lib/libeb.so.16)
endif ()

add_dependencies(eb-static eb)
add_dependencies(eb-shared eb)

if (BUILD_SHARED_LIBS)
    add_library(eb ALIAS eb-shared)
else()
    add_library(eb ALIAS eb-static)
endif()
