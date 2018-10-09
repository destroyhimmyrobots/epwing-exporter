include_guard()

include(FetchContent)

FetchContent_Declare(
    libtidy
    GIT_REPOSITORY https://github.com/htacg/tidy-html5.git
    GIT_TAG 5.6.0
)

FetchContent_GetProperties(libtidy)
if (NOT libtidy_POPULATED)
    FetchContent_Populate(libtidy)
endif ()

add_subdirectory(${libtidy_SOURCE_DIR} ${libtidy_BINARY_DIR})

# https://github.com/htacg/tidy-html5/issues/636
foreach(tidy_target in tidy-static tidy-share tidy)
    if(TARGET ${tidy_target})
        target_compile_definitions(${tidy_target} PRIVATE _GNU_SOURCE)
        target_include_directories(${tidy_target} INTERFACE ${libtidy_SOURCE_DIR}/include)
    endif()
endforeach()

if (BUILD_SHARED_LIBS)
    add_library(libtidy ALIAS tidy-share)
else()
    add_library(libtidy ALIAS tidy-static)
endif()
