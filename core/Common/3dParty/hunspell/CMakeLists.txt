cmake_minimum_required(VERSION 3.16)
project(spell)

# -------------------------------------------------
# Ensure Emscripten toolchain
# -------------------------------------------------
if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "This project must be built with Emscripten (use emcmake).")
endif()

set(CORE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../..)

include(${CORE_ROOT}/common.cmake)

# -------------------------------------------------
# Source files (compile_files_array)
# -------------------------------------------------
set(HUNSPELL_SRC
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/affentry.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/affixmgr.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/csutil.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/hashmgr.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/hunspell.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/hunzip.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/phonet.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/replist.cxx
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell/suggestmgr.cxx
)

set_source_files_properties(${HUNSPELL_SRC} PROPERTIES GENERATED TRUE)

# -------------------------------------------------
# Wrapper Source files
# -------------------------------------------------
set(WRAPPER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/filemgr_wrapper_new.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/base.cpp
)

# -------------------------------------------------
# Executable (WASM module)
# -------------------------------------------------
add_executable(${PROJECT_NAME}
    ${HUNSPELL_SRC}
    ${WRAPPER_SRC}
)

# -------------------------------------------------
# Output folder
# -------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}/spell
)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/hunspell/hunspell-wasm/src/hunspell
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src
)

# -------------------------------------------------
# Defines
# -------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32
    NDEBUG
    HUNSPELL_STATIC
    BUILDING_LIBHUNSPELL
    HUNSPELL_WASM_MODULE
)

# -------------------------------------------------
# Compiler flags (non -s ones)
# -------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    -O3
    -fno-exceptions
    #-fno-rtti
    -Wno-unused-command-line-argument
)

# -------------------------------------------------
# Linker flags (Emscripten -s options)
# -------------------------------------------------
target_link_options(${PROJECT_NAME} PRIVATE
    "-sALLOW_MEMORY_GROWTH=1"
    "-sSTACK_SIZE=10MB"
    "-sFILESYSTEM=0"
    "-sENVIRONMENT=web,worker"
    "-sEXPORTED_FUNCTIONS=['_malloc','_free','_Spellchecker_Malloc','_Spellchecker_Free','_Spellchecker_Create','_Spellchecker_Destroy','_Spellchecker_AddDictionary','_Spellchecker_RemoveDicrionary','_Spellchecker_Load','_Spellchecker_Spell','_Spellchecker_Suggest','_Spellchecker_RemoveEngine','_Spellchecker_TotalAllocatedMemory']"
    "-sEXPORTED_RUNTIME_METHODS=['HEAP8']"
    "-sLEGACY_VM_SUPPORT=1"
    "SHELL:--pre-js ${CORE_ROOT}/Common/js/desktop_fetch_new.js"
    "SHELL:--post-js ${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/spell.js"
)

add_custom_target(${PROJECT_NAME}_copy_extra_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/code.js"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../spell.js"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/index.html"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../index.html"
    COMMENT "Copying extra files to output"
    VERBATIM
)

declare_victory( ${PROJECT_NAME} )

