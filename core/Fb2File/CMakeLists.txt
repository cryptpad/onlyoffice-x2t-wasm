cmake_minimum_required(VERSION 3.10)

project(Fb2File)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include(${CORE_ROOT_DIR}/common.cmake)

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

set(HTML_3RDPARTY_DIR "${CORE_ROOT_DIR}/Common/3dParty/html")
set(KATANA_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/html/katana-parser")
set(GUMBO_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/html/gumbo-parser")
get_filename_component(KATANA_INSTALL_DIR_ABS "${KATANA_INSTALL_DIR}" ABSOLUTE)
get_filename_component(GUMBO_INSTALL_DIR_ABS "${GUMBO_INSTALL_DIR}" ABSOLUTE)

add_library(Fb2File SHARED
    Fb2File.cpp
    Fb2File.h
    template/template.h

    # gumbo.pri
    ${GUMBO_INSTALL_DIR}/src/attribute.c
    ${GUMBO_INSTALL_DIR}/src/char_ref.c
    ${GUMBO_INSTALL_DIR}/src/error.c
    ${GUMBO_INSTALL_DIR}/src/parser.c
    ${GUMBO_INSTALL_DIR}/src/string_buffer.c
    ${GUMBO_INSTALL_DIR}/src/string_piece.c
    ${GUMBO_INSTALL_DIR}/src/tag.c
    ${GUMBO_INSTALL_DIR}/src/tokenizer.c
    ${GUMBO_INSTALL_DIR}/src/utf8.c
    ${GUMBO_INSTALL_DIR}/src/util.c
    ${GUMBO_INSTALL_DIR}/src/vector.c
    
    ${HTML_3RDPARTY_DIR}/htmltoxhtml.cpp

    ${GUMBO_INSTALL_DIR}/src/attribute.h
    ${GUMBO_INSTALL_DIR}/src/char_ref.h
    ${GUMBO_INSTALL_DIR}/src/error.h
    ${GUMBO_INSTALL_DIR}/src/gumbo.h
    ${GUMBO_INSTALL_DIR}/src/insertion_mode.h
    ${GUMBO_INSTALL_DIR}/src/parser.h
    ${GUMBO_INSTALL_DIR}/src/string_buffer.h
    ${GUMBO_INSTALL_DIR}/src/string_piece.h
    ${GUMBO_INSTALL_DIR}/src/tag_enum.h
    ${GUMBO_INSTALL_DIR}/src/tag_gperf.h
    ${GUMBO_INSTALL_DIR}/src/tag_sizes.h
    ${GUMBO_INSTALL_DIR}/src/tag_strings.h
    ${GUMBO_INSTALL_DIR}/src/token_type.h
    ${GUMBO_INSTALL_DIR}/src/tokenizer_states.h
    ${GUMBO_INSTALL_DIR}/src/tokenizer.h
    ${GUMBO_INSTALL_DIR}/src/utf8.h
    ${GUMBO_INSTALL_DIR}/src/util.h
    ${GUMBO_INSTALL_DIR}/src/vector.h

    ${HTML_3RDPARTY_DIR}/htmltoxhtml.h
)

if( MSVC )
    target_include_directories(Fb2File PRIVATE
        ${GUMBO_INSTALL_DIR}/visualc/include
    )
endif()

set_default_options(Fb2File)

target_compile_definitions(Fb2File PRIVATE
    FB2FILE_USE_DYNAMIC_LIBRARY
)

target_include_directories(Fb2File PRIVATE
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}
    ${HTML_3RDPARTY_DIR_ABS}
    ${GUMBO_INSTALL_DIR_ABS}/src
    ${Boost_INCLUDE_DIRS} 
)

if(UNIX)
    target_compile_options(Fb2File PRIVATE $<$<COMPILE_LANGUAGE:C>:-std=c99>)
endif()

# dynamic libs
target_link_libraries(Fb2File PUBLIC
    kernel
    UnicodeConverter
    graphics
)

copy_artifacts_to_folder("Fb2File" "${EO_CORE_OUTPUT_DIR}")

declare_victory( Fb2File )
