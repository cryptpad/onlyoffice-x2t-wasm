cmake_minimum_required(VERSION 3.16)

project(cmapbin LANGUAGES CXX)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

include(${CORE_ROOT_DIR}/common.cmake)

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

# Define the executable
add_executable(CMapSerialize
    CMapSerialize.cpp
)

set_default_options(CMapSerialize)

target_link_libraries(CMapSerialize PRIVATE 
    UnicodeConverter 
    kernel
)

copy_artifacts_to_folder("CMapSerialize" "${EO_CORE_OUTPUT_DIR}")

set(ARTIFACT_FILE "${EO_CORE_OUTPUT_DIR}/cmap.bin")

add_custom_command(
    OUTPUT "${ARTIFACT_FILE}"
    COMMAND  ${EO_CORE_OUTPUT_DIR}/$<TARGET_FILE_NAME:CMapSerialize> "${CMAKE_CURRENT_SOURCE_DIR}/../CMap/CMap"
    COMMAND ${CMAKE_COMMAND} -E remove ${EO_CORE_OUTPUT_DIR}/$<TARGET_FILE_NAME:CMapSerialize>
    DEPENDS CMapSerialize
    COMMENT "Executing CMapSerialize to create ${ARTIFACT_FILE}"
    WORKING_DIRECTORY "${EO_CORE_OUTPUT_DIR}"
    VERBATIM
)

add_custom_target(cmapbin ALL
    DEPENDS "${ARTIFACT_FILE}"
)
