cmake_minimum_required(VERSION 3.10)

project(HtmlFile2)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include(${CORE_ROOT_DIR}/common.cmake)

set(HTML_3RDPARTY_DIR "${CORE_ROOT_DIR}/Common/3dParty/html")

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET kernel_network)
    add_subdirectory(${CORE_ROOT_DIR}/Common/Network kernel_network)
endif()

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

set(KATANA_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/html/katana-parser")
set(GUMBO_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/html/gumbo-parser")
get_filename_component(KATANA_INSTALL_DIR_ABS "${KATANA_INSTALL_DIR}" ABSOLUTE)
get_filename_component(GUMBO_INSTALL_DIR_ABS "${GUMBO_INSTALL_DIR}" ABSOLUTE)

set(MD_3RDPARTY_DIR "${CORE_ROOT_DIR}/Common/3dParty/md")
set(MD_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/md")
get_filename_component(MD_3RDPARTY_DIR_ABS "${MD_3RDPARTY_DIR}" ABSOLUTE)
get_filename_component(MD_INSTALL_DIR_ABS "${MD_INSTALL_DIR}" ABSOLUTE)

add_library(HtmlFile2 SHARED
    htmlfile2.cpp
    HTMLReader.cpp
    Table.cpp

    Common.h
    htmlfile2.h
    HTMLParameters.h
    HTMLReader.h
    MarkdownParameters.h
    Table.h
    src/StringFinder.h
    src/Languages.h

    # Tags
    Tags/MDTags.cpp
    Tags/OOXMLTags.cpp

    Tags/HTMLTags.h
    Tags/MDTags.h
    Tags/OOXMLTags.h

    # Writers
    Writers/MDWriter.cpp
    Writers/OOXMLWriter.cpp

    Writers/IWriter.h
    Writers/MDWriter.h
    Writers/OOXMLWriter.h

    # katana.pri
    ${KATANA_INSTALL_DIR_ABS}/src/foundation.c
    ${KATANA_INSTALL_DIR_ABS}/src/katana.lex.c
    ${KATANA_INSTALL_DIR_ABS}/src/katana.tab.c
    ${KATANA_INSTALL_DIR_ABS}/src/parser.c
    ${KATANA_INSTALL_DIR_ABS}/src/selector.c
    ${KATANA_INSTALL_DIR_ABS}/src/tokenizer.c

    ${KATANA_INSTALL_DIR_ABS}/src/foundation.h
    ${KATANA_INSTALL_DIR_ABS}/src/katana.h
    ${KATANA_INSTALL_DIR_ABS}/src/katana.lex.h
    ${KATANA_INSTALL_DIR_ABS}/src/katana.tab.h
    ${KATANA_INSTALL_DIR_ABS}/src/parser.h
    ${KATANA_INSTALL_DIR_ABS}/src/selector.h
    ${KATANA_INSTALL_DIR_ABS}/src/tokenizer.h

    # gumbo.pri
    ${GUMBO_INSTALL_DIR_ABS}/src/attribute.c
    ${GUMBO_INSTALL_DIR_ABS}/src/char_ref.c
    ${GUMBO_INSTALL_DIR_ABS}/src/error.c
    ${GUMBO_INSTALL_DIR_ABS}/src/parser.c
    ${GUMBO_INSTALL_DIR_ABS}/src/string_buffer.c
    ${GUMBO_INSTALL_DIR_ABS}/src/string_piece.c
    ${GUMBO_INSTALL_DIR_ABS}/src/tag.c
    ${GUMBO_INSTALL_DIR_ABS}/src/tokenizer.c
    ${GUMBO_INSTALL_DIR_ABS}/src/utf8.c
    ${GUMBO_INSTALL_DIR_ABS}/src/util.c
    ${GUMBO_INSTALL_DIR_ABS}/src/vector.c

    ${HTML_3RDPARTY_DIR}/htmltoxhtml.cpp

    ${GUMBO_INSTALL_DIR_ABS}/src/attribute.h
    ${GUMBO_INSTALL_DIR_ABS}/src/char_ref.h
    ${GUMBO_INSTALL_DIR_ABS}/src/error.h
    ${GUMBO_INSTALL_DIR_ABS}/src/gumbo.h
    ${GUMBO_INSTALL_DIR_ABS}/src/insertion_mode.h
    ${GUMBO_INSTALL_DIR_ABS}/src/parser.h
    ${GUMBO_INSTALL_DIR_ABS}/src/string_buffer.h
    ${GUMBO_INSTALL_DIR_ABS}/src/string_piece.h
    ${GUMBO_INSTALL_DIR_ABS}/src/tag_enum.h
    ${GUMBO_INSTALL_DIR_ABS}/src/tag_gperf.h
    ${GUMBO_INSTALL_DIR_ABS}/src/tag_sizes.h
    ${GUMBO_INSTALL_DIR_ABS}/src/tag_strings.h
    ${GUMBO_INSTALL_DIR_ABS}/src/token_type.h
    ${GUMBO_INSTALL_DIR_ABS}/src/tokenizer_states.h
    ${GUMBO_INSTALL_DIR_ABS}/src/tokenizer.h
    ${GUMBO_INSTALL_DIR_ABS}/src/utf8.h
    ${GUMBO_INSTALL_DIR_ABS}/src/util.h
    ${GUMBO_INSTALL_DIR_ABS}/src/vector.h

    ${HTML_3RDPARTY_DIR}/htmltoxhtml.h

    # CssCalculator.pri
    ${HTML_3RDPARTY_DIR}/css/src/CCompiledStyle.cpp
    ${HTML_3RDPARTY_DIR}/css/src/CCssCalculator_Private.cpp
    ${HTML_3RDPARTY_DIR}/css/src/CCssCalculator.cpp
    ${HTML_3RDPARTY_DIR}/css/src/CElement.cpp
    ${HTML_3RDPARTY_DIR}/css/src/CNode.cpp
    ${HTML_3RDPARTY_DIR}/css/src/ConstValues.cpp
    ${HTML_3RDPARTY_DIR}/css/src/CUnitMeasureConverter.cpp
    ${HTML_3RDPARTY_DIR}/css/src/StaticFunctions.cpp
    ${HTML_3RDPARTY_DIR}/css/src/StyleProperties.cpp
    ${HTML_3RDPARTY_DIR}/css/src/xhtml/CDocumentStyle.cpp
    ${HTML_3RDPARTY_DIR}/css/src/xhtml/CXmlElement.cpp

    ${HTML_3RDPARTY_DIR}/css/src/CCompiledStyle.h
    ${HTML_3RDPARTY_DIR}/css/src/CCssCalculator_Private.h
    ${HTML_3RDPARTY_DIR}/css/src/CCssCalculator.h
    ${HTML_3RDPARTY_DIR}/css/src/CElement.h
    ${HTML_3RDPARTY_DIR}/css/src/CNode.h
    ${HTML_3RDPARTY_DIR}/css/src/ConstValues.h
    ${HTML_3RDPARTY_DIR}/css/src/CssCalculator_global.h
    ${HTML_3RDPARTY_DIR}/css/src/CUnitMeasureConverter.h
    ${HTML_3RDPARTY_DIR}/css/src/StaticFunctions.h
    ${HTML_3RDPARTY_DIR}/css/src/StyleProperties.h
    ${HTML_3RDPARTY_DIR}/css/src/xhtml/CDocumentStyle.h
    ${HTML_3RDPARTY_DIR}/css/src/xhtml/CXmlElement.h


    # md2html.pri
    ${MD_3RDPARTY_DIR_ABS}/md2html.h
    ${MD_INSTALL_DIR_ABS}/src/entity.h
    ${MD_INSTALL_DIR_ABS}/src/md4c-html.h
    ${MD_INSTALL_DIR_ABS}/src/md4c.h

    ${MD_3RDPARTY_DIR_ABS}/md2html.cpp
    ${MD_INSTALL_DIR_ABS}/src/entity.c
    ${MD_INSTALL_DIR_ABS}/src/md4c-html.c
    ${MD_INSTALL_DIR_ABS}/src/md4c.c
)

set_default_options(HtmlFile2)

target_include_directories(HtmlFile2 PRIVATE
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}
    ${HTML_3RDPARTY_DIR}
    ${HTML_3RDPARTY_DIR}/css # CssCalculator.pri
    ${GUMBO_INSTALL_DIR_ABS}/src
    ${KATANA_INSTALL_DIR_ABS}/src
)

if( MSVC )
    target_include_directories(HtmlFile2 PRIVATE
        ${KATANA_INSTALL_DIR_ABS}/visualc/include
        ${GUMBO_INSTALL_DIR}/visualc/include
    )
endif()

target_compile_definitions(HtmlFile2 PRIVATE
    HTMLFILE2_USE_DYNAMIC_LIBRARY
    CSSCALCULATOR_LIBRARY_STATIC
    CSS_CALCULATOR_WITH_XHTML
    DISABLE_RUBY_SUPPORT
    MDCONVERTER_DECL_EXPORT

    # md2html.pri
    MD4C_USE_UTF8
)

# dynamic libs
target_link_libraries(HtmlFile2 PUBLIC
    kernel
    UnicodeConverter
    graphics
    kernel_network
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
)

copy_artifacts_to_folder("HtmlFile2" "${EO_CORE_OUTPUT_DIR}")

declare_victory( HtmlFile2 )
