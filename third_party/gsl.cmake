include_guard()

include(FetchContent)

FetchContent_Declare(
    gsl
    GIT_REPOSITORY https://github.com/microsoft/gsl
    GIT_TAG v3.1.0
)

FetchContent_GetProperties(gsl)
if(NOT gsl_POPULATED)
    FetchContent_Populate(gsl)
    add_subdirectory(${gsl_SOURCE_DIR} ${gsl_BINARY_DIR})
endif()
