include_guard()

add_library(
    epwing

    # INTERFACE
    converter_interface.h
    exception.h
    hookset_interface.h
    path.h
    reporter_interface.h

    # PUBLIC
    book.h
    container.h
    container_factory.h
    converter_html5.h
    converter_xdxf.h
    deduplicator.h
    dictionary.h
    hooks.h
    iconv.h
    library.h
    printer_html5.h
    printer_xdxf.h
    reporter_book.h
    reporter_container.h
    reporter_deduplicator.h
    reporter_gaiji.h
    reporter_hit_list.h
    reporter_sub_book.h
    reporter_word_code.h

    # PRIVATE
    book.cpp
    container.cpp
    container_factory.cpp
    converter_html5.cpp
    converter_xdxf.cpp
    deduplicator.cpp
    dictionary.cpp
    hooks.cpp
    iconv.cpp
    library.cpp
    printer_html5.cpp
    printer_xdxf.cpp
    reporter_book.cpp
    reporter_container.cpp
    reporter_deduplicator.cpp
    reporter_gaiji.cpp
    reporter_hit_list.cpp
    reporter_sub_book.cpp
    reporter_word_code.cpp
)

add_subdirectory(gaiji)
target_link_libraries(epwing PRIVATE GSL z eb gaiji)

if (APPLE)
    target_link_libraries(epwing PRIVATE iconv)
endif ()

