cmake_minimum_required(VERSION 3.10)

project(allfontsgen)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

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

add_executable(allfontsgen
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

set_default_options(allfontsgen)

target_include_directories(allfontsgen PRIVATE
    ${ICU_INSTALL_DIR_ABS}/include
)

target_link_libraries(allfontsgen PUBLIC
    UnicodeConverter
    kernel
    graphics
    ${LIBICUUC}
    ${LIBICUDATA}
)

copy_artifacts_to_folder("allfontsgen" "${EO_CORE_TOOLS_DIR}")

declare_victory( allfontsgen )
