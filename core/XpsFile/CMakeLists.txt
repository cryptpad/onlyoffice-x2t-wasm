cmake_minimum_required(VERSION 3.10)

project(XpsFile)

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

if(NOT TARGET PdfFile)
    add_subdirectory(${CORE_ROOT_DIR}/PdfFile PdfFile)
endif()

add_library(XpsFile SHARED
    XpsFile.cpp
    XpsLib/ContextState.cpp
    XpsLib/Document.cpp
    XpsLib/StaticResources.cpp
    XpsLib/Utils.cpp
    XpsLib/WString.cpp
    XpsLib/XpsPage.cpp

    XpsFile.h
    XpsLib/ContextState.h
    XpsLib/Document.h
    XpsLib/FontList.h
    XpsLib/StaticResources.h
    XpsLib/Utils.h
    XpsLib/WString.h
    XpsLib/XpsPage.h
)

set_default_options(XpsFile)

target_include_directories(XpsFile PRIVATE
    ${CORE_ROOT_DIR}/DesktopEditor/freetype-2.10.4/include
    ${CORE_ROOT_DIR}/DesktopEditor/freetype-2.10.4/include/freetype
)

target_compile_definitions(XpsFile PRIVATE
    XPS_USE_DYNAMIC_LIBRARY
)

# dynamic libs
target_link_libraries(XpsFile PUBLIC
    graphics
    kernel
    UnicodeConverter
    PdfFile

    # gdi32 # Windows
    # advapi32 # Windows
    # user32 # Windows
    # shell32 # Windows
    # Ole32 # Windows
)

copy_artifacts_to_folder("XpsFile" "${EO_CORE_OUTPUT_DIR}")

declare_victory( XpsFile )
