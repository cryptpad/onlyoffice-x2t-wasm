cmake_minimum_required(VERSION 3.16)

# 1. Define the library target
add_library(vlc_wrapper STATIC
    vlcinstance.cpp
    vlcplayer.cpp
    vlcmedia.cpp
    vlcinstance.h
    vlcplayer.h
    vlcmedia.h
    libvlc_base.h
)

# 2. Handle Variables
# $$PWD is CMAKE_CURRENT_SOURCE_DIR in CMake
# Ensure CORE_BUILDS_PLATFORM_PREFIX is passed to CMake or defined before this file
if(NOT DEFINED CORE_BUILDS_PLATFORM_PREFIX)
    message(WARNING "CORE_BUILDS_PLATFORM_PREFIX is not defined. Defaulting to empty or handle appropriately.")
    set(CORE_BUILDS_PLATFORM_PREFIX "") 
endif()

set(VLC_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/${CORE_BUILDS_PLATFORM_PREFIX}")
set(VLC_LIB_DIR "${VLC_BUILD_DIR}/lib")

# 3. Include Paths
target_include_directories(vlc_wrapper PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${VLC_BUILD_DIR}/include"
)

# 4. Find and Link Libraries
# Instead of hardcoding -L and -l, we look for the library files explicitly
find_library(LIB_VLC 
    NAMES vlc libvlc
    PATHS "${VLC_LIB_DIR}"
    NO_DEFAULT_PATH
    NO_CMAKE_FIND_ROOT_PATH
)

find_library(LIB_VLCCORE 
    NAMES vlccore libvlccore
    PATHS "${VLC_LIB_DIR}"
    NO_DEFAULT_PATH
    NO_CMAKE_FIND_ROOT_PATH
)

if(LIB_VLC AND LIB_VLCCORE)
    target_link_libraries(vlc_wrapper PRIVATE ${LIB_VLC} ${LIB_VLCCORE})
else()
    message(WARNING "Could not find VLC libraries in ${VLC_LIB_DIR}")
endif()

# 5. Platform Specifics: Windows (MSVC)
if(MSVC)
    # Equivalent to core_windows:vs2019
    # /permissive- enforces standard conformance
    target_compile_options(vlc_wrapper PRIVATE "/permissive-")
endif()

# 6. Platform Specifics: macOS Apple Silicon
# Note: CMAKE_OSX_DEPLOYMENT_TARGET must be set globally before the project() command.
if(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    
    # Check if the global setting is lower than required, or warn the user
    if(CMAKE_OSX_DEPLOYMENT_TARGET VERSION_LESS "10.15")
        message(STATUS "Apple Silicon detected: Suggest setting CMAKE_OSX_DEPLOYMENT_TARGET to 10.15 or higher in your root CMakeLists.txt")
    endif()
endif()