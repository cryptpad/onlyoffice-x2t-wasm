cmake_minimum_required(VERSION 3.10)

project(pluginsmanager)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

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

add_executable(pluginsmanager
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp

    ${CMAKE_CURRENT_LIST_DIR}/help.h
)

set_default_options(pluginsmanager)

target_include_directories(pluginsmanager PRIVATE
    ${ICU_INSTALL_DIR_ABS}/include
)

target_compile_definitions(pluginsmanager PRIVATE
    KERNEL_USE_DYNAMIC_LIBRARY
)

target_link_libraries(pluginsmanager PUBLIC
    kernel
    kernel_network
    UnicodeConverter
    ${LIBICUUC}
    ${LIBICUDATA}
)

copy_artifacts_to_folder("pluginsmanager" "${EO_CORE_TOOLS_DIR}")

declare_victory( pluginsmanager )
