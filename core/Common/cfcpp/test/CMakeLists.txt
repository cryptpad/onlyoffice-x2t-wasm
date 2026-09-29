cmake_minimum_required(VERSION 3.10)

project(cfcpp_test)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../..")

include(${CORE_ROOT_DIR}/common.cmake)

# Dependencies (mirror ADD_DEPENDENCY in test.pro).
if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()
if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()
if(NOT TARGET CompoundFileLib)
    add_subdirectory(${CORE_ROOT_DIR}/Common/cfcpp CompoundFileLib)
endif()

# global.h locates fixtures via the working-dir-relative path "../../../data/".
# Stage the committed fixtures under the binary dir and run the test from a
# directory nested three levels deep, so "../../../data" resolves to the copy.
set(_cfcpp_data_dir "${CMAKE_CURRENT_BINARY_DIR}/data")
set(_cfcpp_run_dir  "${CMAKE_CURRENT_BINARY_DIR}/run/lvl1/lvl2")

add_core_gtest(
    NAME    cfcpp_test
    SOURCES main.cpp
    LIBS    kernel UnicodeConverter CompoundFileLib
    USE_GMOCK
    WORKING_DIRECTORY "${_cfcpp_run_dir}"
)

# test.pro adds "INCLUDEPATH += $$PWD/../" so includes such as
# "../../DesktopEditor/common/File.h" resolve against Common/cfcpp.
target_include_directories(cfcpp_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_custom_command(TARGET cfcpp_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${_cfcpp_run_dir}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/data" "${_cfcpp_data_dir}"
    COMMENT "Staging cfcpp_test fixtures"
)
