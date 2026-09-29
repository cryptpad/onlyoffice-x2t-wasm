cmake_minimum_required(VERSION 3.10)

project(docbuilder)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../..")

include(${CORE_ROOT_DIR}/common.cmake)

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

if(NOT TARGET doctrenderer)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/doctrenderer doctrenderer)
endif()

if(NOT TARGET PdfFile)
    add_subdirectory(${CORE_ROOT_DIR}/PdfFile PdfFile)
endif()

if(NOT TARGET XpsFile)
    add_subdirectory(${CORE_ROOT_DIR}/XpsFile XpsFile)
endif()

if(NOT TARGET DjVuFile)
    add_subdirectory(${CORE_ROOT_DIR}/DjVuFile DjVuFile)
endif()

if(NOT TARGET DocxRenderer)
    add_subdirectory(${CORE_ROOT_DIR}/DocxRenderer DocxRenderer)
endif()

add_executable(docbuilder
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

set_default_options(docbuilder)

target_link_libraries(docbuilder PUBLIC
    graphics
    kernel
    kernel_network
    UnicodeConverter
    doctrenderer
    PdfFile
    XpsFile
    DjVuFile
    DocxRenderer
    ${LIBICUUC}
    ${LIBICUDATA}
)

if( MSVC )
    target_link_libraries(docbuilder PUBLIC
        Kernel32
    )
elseif( UNIX )
    target_link_libraries(docbuilder PUBLIC
        dl
    )
endif()

copy_artifacts_to_folder("docbuilder" "${EO_CORE_OUTPUT_DIR}")

declare_victory( docbuilder )
