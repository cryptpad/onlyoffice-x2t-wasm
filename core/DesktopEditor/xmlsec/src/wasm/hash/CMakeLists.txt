cmake_minimum_required(VERSION 3.16)
project(engine)

# -------------------------------------------------
# Ensure Emscripten toolchain
# -------------------------------------------------
if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "This project must be built with Emscripten (use emcmake).")
endif()

set(CORE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../../..)

include(${CORE_ROOT}/common.cmake)

# -------------------------------------------------
# Source files (compile_files_array)
# -------------------------------------------------

set(SRC
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/sha/keccak1600.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/sha/sha1_one.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/sha/sha1dgst.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/sha/sha256.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/sha/sha512.c

    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/md2/md2_dgst.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/md2/md2_one.c

    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/md4/md4_dgst.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/md4/md4_one.c

    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/md5/md5_dgst.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/md5/md5_one.c

    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/ripemd/rmd_dgst.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/ripemd/rmd_one.c

    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/whrlpool/wp_block.c
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/whrlpool/wp_dgst.c

    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/crypto/mem_clr.c
)

set_source_files_properties(${SRC} PROPERTIES GENERATED TRUE)

# -------------------------------------------------
# Executable (WASM module)
# -------------------------------------------------
add_executable(${PROJECT_NAME} ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# -------------------------------------------------
# Output settings
# -------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EO_CORE_OUTPUT_DIR}/hash/hash
    SUFFIX ".js"
)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/include
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/openssl-hash/include
)

# -------------------------------------------------
# link libraries
# -------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OPENSSL_WASM_LIBCRYPTO}
    ${OPENSSL_WASM_LIBSSL}
)

# -------------------------------------------------
# Defines
# -------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN32
    NDEBUG
    OPENSSL_MD2_ENABLED
)

# -------------------------------------------------
# Compiler flags (non -s ones)
# -------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    -O3
    -fno-exceptions
    -fno-rtti
    -Wno-unused-command-line-argument
)

# -------------------------------------------------
# Linker flags (Emscripten -s options)
# -------------------------------------------------
target_link_options(${PROJECT_NAME} PRIVATE
    "-sALLOW_MEMORY_GROWTH=1"
    "-sFILESYSTEM=0"
    "-sENVIRONMENT=worker"
    "-sTOTAL_STACK=1MB"
    "-sINITIAL_MEMORY=2MB"
    "-sEXPORTED_FUNCTIONS=['_malloc','_free','_hash','_hash2']"
    "-sEXPORTED_RUNTIME_METHODS=['HEAPU8']"
    "-sLEGACY_VM_SUPPORT=1"
    "SHELL:--pre-js ${CORE_ROOT}/../sdkjs/common/stringserialize.js"
    "SHELL:--pre-js ${CMAKE_CURRENT_SOURCE_DIR}/hash_base_pre.js"
    "SHELL:--pre-js ${CORE_ROOT}/Common/js/string_utf8.js"
    "SHELL:--post-js ${CORE_ROOT}/Common/js/desktop_fetch_new.js"
    "SHELL:--post-js ${CMAKE_CURRENT_SOURCE_DIR}/hash_base_post.js"
)

declare_victory( ${PROJECT_NAME} )

