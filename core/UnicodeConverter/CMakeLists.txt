cmake_minimum_required(VERSION 3.10)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

project(UnicodeConverter)

include(${CORE_ROOT_DIR}/common.cmake)

add_library(UnicodeConverter SHARED
    UnicodeConverter.cpp
    UnicodeConverter.h
)

set_default_options(UnicodeConverter)

target_compile_definitions(UnicodeConverter PRIVATE
    UNICODECONVERTER_USE_DYNAMIC_LIBRARY
)

target_include_directories(UnicodeConverter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ICU_INSTALL_DIR_ABS}/include
)

target_link_libraries(UnicodeConverter PUBLIC
    ${LIBICUUC}
    ${LIBICUDATA}
)

copy_artifacts_to_folder("UnicodeConverter" "${EO_CORE_OUTPUT_DIR}")
copy_icu_libs(UnicodeConverter)

declare_victory( UnicodeConverter )
