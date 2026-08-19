cmake_minimum_required(VERSION 3.20)
project(oform)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# -------------------------------------------------
# Ensure Emscripten toolchain
# -------------------------------------------------
if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "This project must be built with Emscripten (use emcmake).")
endif()

set(CORE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../..)

include(${CORE_ROOT}/common.cmake)

# -------------------------------------------------
# Pre / Post build scripts
# -------------------------------------------------
set(OPENSSL_ROOT "../../3rdParty")
get_filename_component(OPENSSL_ROOT_ABS "${OPENSSL_ROOT}" ABSOLUTE)
add_custom_target(${PROJECT_NAME}_run_before ALL
    COMMAND bash ${OPENSSL_ROOT_ABS}/nc-build.sh "${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash" "${EO_CORE_3RD_PARTY_INSTALL_DIR}/openssl-hash"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# -------------------------------------------------
# Source files (compile_files_array)
# -------------------------------------------------
set(SOURCES
    ${CORE_ROOT}/DesktopEditor/common/Base64.cpp
    ${CORE_ROOT}/DesktopEditor/common/File.cpp

    ${CORE_ROOT}/Common/3dParty/openssl/common/common_openssl.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# -------------------------------------------------
# Executable (WASM module)
# -------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_run_before)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/include
${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash
#emsdk/node/14.15.5_64bit/include/node/openssl/archs/linux-x86_64/no-asm/include
)

# -------------------------------------------------
# Defines
# -------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
__linux__
_LINUX
DISABLE_XMLSEC
)

# -------------------------------------------------
# Compiler flags (non -s ones)
# -------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
-O3
-Wno-unused-command-line-argument
)

# -------------------------------------------------
# Linker flags (Emscripten -s options)
# -------------------------------------------------
target_link_options(${PROJECT_NAME} PRIVATE
-sALLOW_MEMORY_GROWTH=1
-sFILESYSTEM=0
-sENVIRONMENT=web
-sASSERTIONS
-sLLD_REPORT_UNDEFINED
-sWASM=1
"-sEXPORTED_FUNCTIONS=['_malloc','_free','_Crypto_Malloc','_Crypto_Free', '_Crypto_CreateKeys', '_Crypto_Sign', '_Crypto_ChangePassword']"
"-sEXPORTED_RUNTIME_METHODS=['HEAP8']"
"-sLEGACY_VM_SUPPORT=1"
"SHELL:--pre-js ${CORE_ROOT}/Common/js/desktop_fetch_new.js"
)


inject_script(
    ${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/engine_base.js"
    "${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.js"
    MODE PRE_BUILD
    REPLACEMENTS
        "{{{ STRING_UTF8 }}}"  "${CORE_ROOT}/Common/js/string_utf8.js"
        "{{{ MODULE }}}"  "${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}/${PROJECT_NAME}.js"
)

# -------------------------------------------------
# Link static OpenSSL crypto lib
# -------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/libcrypto.a
)

# -------------------------------------------------
# Output settings
# -------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}
SUFFIX ".js"
)