cmake_minimum_required(VERSION 3.10)

project(starmath_smconverter_test)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../..")

include(${CORE_ROOT_DIR}/common.cmake)

# Dependencies (mirror ADD_DEPENDENCY in TestSMConverter.pro).
if(NOT TARGET StarMathConverter)
    add_subdirectory(${CORE_ROOT_DIR}/OdfFile/Reader/Converter/StarMath2OOXML StarMathConverter)
endif()

add_core_gtest(
    NAME    starmath_smconverter_test
    SOURCES main.cpp
    LIBS    StarMathConverter
    GTEST_MAIN
)
