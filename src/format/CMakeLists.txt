include_guard()

add_library(
    format
    # PRIVATE
    tidy.cpp
    # PUBLIC
    tidy.h
    # INTERFACE
    path.h
)

set_property(
    SOURCE tidy.cpp APPEND
    PROPERTY COMPILE_OPTIONS
    -Wno-error=ignored-qualifiers
)

target_link_libraries(format PRIVATE libtidy)
