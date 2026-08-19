cmake_minimum_required(VERSION 3.15)
project(hunspell_wrapper LANGUAGES CXX)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../..")

include(${CORE_ROOT_DIR}/common.cmake)

# 2. Define wrapper library
add_library(hunspell_wrapper INTERFACE)

# 4. Include internal headers
target_include_directories(hunspell_wrapper INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/../wasm/src"
)

# 5. Link to the official Hunspell
# This automatically handles the include paths and compiler flags for Hunspell
target_link_libraries(hunspell_wrapper INTERFACE 
    ${HUNSPELL_LIB}
)

# 6. macros
target_compile_definitions(hunspell_wrapper INTERFACE BUILDING_LIBHUNSPELL)