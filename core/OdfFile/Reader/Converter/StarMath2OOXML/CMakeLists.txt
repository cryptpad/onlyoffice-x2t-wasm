cmake_minimum_required(VERSION 3.10)
project(StarMathConverter VERSION 1)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../..")

include(${CORE_ROOT_DIR}/common.cmake)

add_library(StarMathConverter SHARED)

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

# Set target version
set_target_properties(StarMathConverter PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# HEADERS and SOURCES
target_sources(StarMathConverter PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/conversionmathformula.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/cconversionsmtoooxml.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cstarmathpars.cpp
    
	${CMAKE_CURRENT_SOURCE_DIR}/conversionmathformula.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cconversionsmtoooxml.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cstarmathpars.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fontType.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TextDirection.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TFormulaSize.h
    ${CMAKE_CURRENT_SOURCE_DIR}/typeConversion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/typeselements.h

    ${CORE_ROOT_DIR}/OOXML/Base/Unit.cpp

    ${CORE_ROOT_DIR}/OOXML/Base/Unit.h
)

target_link_libraries(StarMathConverter PRIVATE 
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
    kernel
)

target_compile_definitions(StarMathConverter PRIVATE
    STARMATH_USE_DYNAMIC_LIBRARY
)

if( UNIX )
    # Remove UNICODE definition if it was inherited from directory properties
    remove_definitions(-DUNICODE -D_UNICODE)
endif()

copy_artifacts_to_folder("StarMathConverter" "${EO_CORE_OUTPUT_DIR}")

declare_victory( StarMathConverter )
