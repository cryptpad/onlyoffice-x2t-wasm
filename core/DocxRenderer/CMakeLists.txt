cmake_minimum_required(VERSION 3.10)

project(DocxRenderer)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include(${CORE_ROOT_DIR}/common.cmake)

if(NOT DEFINED DISABLE_FULL_DOCUMENT_CREATION)
    set(DISABLE_FULL_DOCUMENT_CREATION 0)
endif()

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

add_library(DocxRenderer SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/DocxRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/Document.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/BaseItem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/ContText.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/Paragraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/Shape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/Table.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/TextLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/FontManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/FontStyleManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/ImageManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/ParagraphStyleManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/Page.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/styles/FontStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/styles/ParagraphStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/VectorGraphics.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/DocxRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/Document.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/BaseItem.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/ContText.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/Paragraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/Shape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/Table.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/elements/TextLine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/ExternalImageStorage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/FontManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/FontStyleManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/ImageManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/managers/ParagraphStyleManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/Page.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/styles/FontStyle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logic/styles/ParagraphStyle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/ColorTable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/Constants.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/ImageInfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/LinesTable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/resources.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/VectorGraphics.h
)

set_default_options(DocxRenderer)

if( NOT DISABLE_FULL_DOCUMENT_CREATION )
    target_sources(DocxRenderer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources/resources.cpp
    )
endif()

target_compile_definitions(DocxRenderer PRIVATE
    DOCXRENDERER_USE_DYNAMIC_LIBRARY
)

if(DISABLE_FULL_DOCUMENT_CREATION)
    target_compile_definitions(DocxRenderer PRIVATE
        DISABLE_FULL_DOCUMENT_CREATION
    )
endif()

target_link_libraries(DocxRenderer PUBLIC
    UnicodeConverter
    kernel
    graphics
)

if(WIN32)
    target_link_libraries(DocxRenderer PUBLIC
        Gdi32
        Advapi32
        User32
        Shell32
    )
endif()

copy_artifacts_to_folder("DocxRenderer" "${EO_CORE_OUTPUT_DIR}")

declare_victory( DocxRenderer )
