cmake_minimum_required(VERSION 3.10)

project(x2ttester)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../..")

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

add_executable(x2ttester
    ${CORE_ROOT_DIR}/Common/3dParty/pole/pole.cpp
    ${CORE_ROOT_DIR}/Common/OfficeFileFormatChecker2.cpp
    ${CORE_ROOT_DIR}/OOXML/Base/unicode_util.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/x2tTester.cpp
    ${CMAKE_CURRENT_LIST_DIR}/x2tTester.h
)

set_default_options(x2ttester)

if( MSVC )
    target_compile_definitions( x2ttester PRIVATE
        _UNICODE
        UNICODE
    )
endif()

target_link_libraries(x2ttester PUBLIC
	kernel
	graphics
	UnicodeConverter
)

copy_artifacts_to_folder("x2ttester" "${EO_CORE_TOOLS_DIR}")

# Modify rpath so test binary can run properly

# register_test_target(x2t_test)

declare_victory( x2ttester )
