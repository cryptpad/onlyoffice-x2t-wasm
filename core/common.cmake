include_guard(GLOBAL)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_path( APPEND DEFAULT_EO_CORE_OUTPUT_DIR "${CMAKE_BINARY_DIR}" "package" )
cmake_path( APPEND DEFAULT_EO_CORE_TOOLS_DIR "${CMAKE_BINARY_DIR}" "package" )

cmake_path( APPEND DEFAULT_EO_CORE_3RD_PARTY_DIR "${CMAKE_BINARY_DIR}" "third_party" )

if( NOT DEFINED EO_CORE_OUTPUT_DIR )
    set(EO_CORE_OUTPUT_DIR "${DEFAULT_EO_CORE_OUTPUT_DIR}" CACHE PATH "Where to place output files (absolute path recommended)")
endif()

if( NOT DEFINED EO_CORE_TOOLS_DIR )
    set(EO_CORE_TOOLS_DIR  "${DEFAULT_EO_CORE_TOOLS_DIR}" CACHE PATH "Where to place tools output files (absolute path recommended)")
endif()

file(TO_CMAKE_PATH "${EO_CORE_OUTPUT_DIR}" EO_CORE_OUTPUT_DIR)
file(TO_CMAKE_PATH "${EO_CORE_TOOLS_DIR}"  EO_CORE_TOOLS_DIR)
if(NOT IS_ABSOLUTE "${EO_CORE_OUTPUT_DIR}")
    cmake_path(ABSOLUTE_PATH EO_CORE_OUTPUT_DIR BASE_DIRECTORY "${CMAKE_BINARY_DIR}" NORMALIZE)
endif()
if(NOT IS_ABSOLUTE "${EO_CORE_TOOLS_DIR}")
    cmake_path(ABSOLUTE_PATH EO_CORE_TOOLS_DIR BASE_DIRECTORY "${CMAKE_BINARY_DIR}" NORMALIZE)
endif()

if( NOT DEFINED EO_CORE_3RD_PARTY_DIR )
    set(EO_CORE_3RD_PARTY_DIR "${DEFAULT_EO_CORE_3RD_PARTY_DIR}" CACHE PATH "Where to place and build 3rd party projects (absolute path recommended)")
endif()

if( NOT DEFINED EO_CORE_3RD_PARTY_WORK_DIR )
    cmake_path( APPEND DEFAULT_EO_CORE_3RD_PARTY_WORK_DIR "${EO_CORE_3RD_PARTY_DIR}" "work" )
    set(EO_CORE_3RD_PARTY_WORK_DIR "${DEFAULT_EO_CORE_3RD_PARTY_WORK_DIR}" CACHE PATH "3rd party work dir for clone and build.")
endif()

if( NOT DEFINED EO_CORE_3RD_PARTY_INSTALL_DIR )
    cmake_path( APPEND DEFAULT_EO_CORE_3RD_PARTY_INSTALL_DIR "${EO_CORE_3RD_PARTY_DIR}" "install" )
    set(EO_CORE_3RD_PARTY_INSTALL_DIR "${DEFAULT_EO_CORE_3RD_PARTY_INSTALL_DIR}" CACHE PATH "3rd party install dir.")
endif()

if( NOT DEFINED VCPKG_BINARY_REMOTE )
    set(VCPKG_BINARY_REMOTE "https://cloud.nextcloud.com/public.php/dav/files/n9KYBcFYyLLCgEw" CACHE STRING "Base URL for vcpkg binary package remote")
endif()

if( NOT DEFINED PYTHON_BIN )
    find_package(Python3 REQUIRED)
    set(PYTHON_BIN "${Python3_EXECUTABLE}" CACHE FILEPATH "Python binary to use.")
endif()

if(NOT DEFINED LINUX AND CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LINUX TRUE)
endif()

message("3rdparty dir: " ${EO_CORE_3RD_PARTY_DIR})
message("workdir: " ${EO_CORE_3RD_PARTY_WORK_DIR})
message("install: " ${EO_CORE_3RD_PARTY_INSTALL_DIR})

if( EMSCRIPTEN )

    if(NOT THIRD_PARTY_PREPARED)
        cmake_path( APPEND BUILDER_PATH "${CMAKE_CURRENT_LIST_DIR}" "Common" "3dParty" "build_3rdparty.py" )
        execute_process(
            COMMAND_ECHO STDOUT
            COMMAND "${PYTHON_BIN}"
            "${BUILDER_PATH}"
            "--only=openssl-hash,hunspell,brotli,harfbuzz,hyphen,icu-wasm"
            "${EO_CORE_3RD_PARTY_WORK_DIR}" "${EO_CORE_3RD_PARTY_INSTALL_DIR}"
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error
        )

        if(result) # on error
            message(STATUS "Python script output: ${output}")
            message(STATUS "Python script error: ${error}")
            message(FATAL_ERROR "Common/3dParty/build_3rdparty.py failed!")
        else()
            message(STATUS "Python script output: ${output}")
            set(THIRD_PARTY_PREPARED TRUE CACHE INTERNAL "Third party prepared")
        endif()
    endif()

    # Setup openssl
    set(OPENSSL_WASM_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/openssl-hash")
    get_filename_component(OPENSSL_WASM_INSTALL_DIR_ABS "${OPENSSL_WASM_INSTALL_DIR}" ABSOLUTE)
    set(OPENSSL_WASM_LIBSSL "${OPENSSL_WASM_INSTALL_DIR_ABS}/lib/libssl.a")
    set(OPENSSL_WASM_LIBCRYPTO "${OPENSSL_WASM_INSTALL_DIR_ABS}/lib/libcrypto.a")

else()

    if(NOT THIRD_PARTY_PREPARED)
        cmake_path( APPEND BUILDER_PATH "${CMAKE_CURRENT_LIST_DIR}" "Common" "3dParty" "build_3rdparty.py" )
        execute_process(
            COMMAND_ECHO STDOUT
            COMMAND "${PYTHON_BIN}"
            "${BUILDER_PATH}"
            "--except=openssl-hash,icu-wasm"
            "${EO_CORE_3RD_PARTY_WORK_DIR}" "${EO_CORE_3RD_PARTY_INSTALL_DIR}"
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error
        )

        if(result) # on error
            message(STATUS "Python script output: ${output}")
            message(STATUS "Python script error: ${error}")
            message(FATAL_ERROR "Common/3dParty/build_3rdparty.py failed!")
        else()
            message(STATUS "Python script output: ${output}")
            set(THIRD_PARTY_PREPARED TRUE CACHE INTERNAL "Third party prepared")
        endif()
    endif()

    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "" FORCE)
        foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_RELEASE CMAKE_C_FLAGS CMAKE_C_FLAGS_RELEASE)
            string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endforeach()
    endif()

    # Setup icu
    # These version numbers don't affect what build_3rdparty.py builds. They just have to match.
    set(ICU_MAJOR_VER "74")
    set(ICU_MINOR_VER "2")
    set(ICU_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu")
    get_filename_component(ICU_INSTALL_DIR_ABS "${ICU_INSTALL_DIR}" ABSOLUTE)
    if( MSVC )
        set(LIBICUUC "${ICU_INSTALL_DIR_ABS}/lib/icuuc.lib")
        set(LIBICUDATA "${ICU_INSTALL_DIR_ABS}/lib/icudt.lib")
    else()
        set(LIBICUUC "${ICU_INSTALL_DIR_ABS}/lib/libicuuc.so.${ICU_MAJOR_VER}")
        set(LIBICUDATA "${ICU_INSTALL_DIR_ABS}/lib/libicudata.so.${ICU_MAJOR_VER}")
    endif()

    # Setup boost
    set( BOOST_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/boost" )
    get_filename_component(BOOST_INSTALL_DIR_ABS "${BOOST_INSTALL_DIR}" ABSOLUTE)
    set( CMAKE_PREFIX_PATH "${BOOST_INSTALL_DIR_ABS}" )
    include_directories( "${BOOST_INSTALL_DIR_ABS}/include" )
    set(Boost_USE_STATIC_LIBS ON)
    find_package( Boost REQUIRED COMPONENTS system filesystem regex date_time )

    # Setup v8
    set(V8_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/v8")
    get_filename_component(V8_INSTALL_DIR_ABS "${V8_INSTALL_DIR}" ABSOLUTE)
    if( MSVC )
        set(V8_MONOLITH "${V8_INSTALL_DIR_ABS}/v8_monolith.lib")
    else()
        set(V8_MONOLITH "${V8_INSTALL_DIR_ABS}/libv8_monolith.a")
    endif()

    # Setup openssl
    set(OPENSSL_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/openssl")
    get_filename_component(OPENSSL_INSTALL_DIR_ABS "${OPENSSL_INSTALL_DIR}" ABSOLUTE)
    if( MSVC )
        set(OPENSSL_LIBSSL "${OPENSSL_INSTALL_DIR_ABS}/lib/libssl.lib")
        set(OPENSSL_LIBCRYPTO "${OPENSSL_INSTALL_DIR_ABS}/lib/libcrypto.lib")
    else()
        set(OPENSSL_LIBSSL "${OPENSSL_INSTALL_DIR_ABS}/lib/libssl.a")
        set(OPENSSL_LIBCRYPTO "${OPENSSL_INSTALL_DIR_ABS}/lib/libcrypto.a")
    endif()

endif()

# Do NOT auto-add absolute link directories to RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# Use INSTALL_RPATH even for build-tree binaries
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Enable color diagnostics but only in interactive terminals
if(CMAKE_GENERATOR MATCHES "Ninja|Unix Makefiles")
    if(DEFINED ENV{TERM})
        # Simple check for common interactive terminals
        if(NOT "$ENV{TERM}" STREQUAL "dumb")
            message(STATUS "Enabling colored diagnostics for interactive terminal")
            set(CMAKE_COLOR_DIAGNOSTICS ON CACHE BOOL "Enable colored compiler output" FORCE)
        endif()
    endif()
endif()

set(COMMON_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}")
file(READ "${COMMON_CMAKE_DIR}/Common/version.txt" VERSION_TXT_CONTENT)

if( LINUX )
    set(COMMON_DEFINES
        _LINUX
        _REENTRANT
        CRYPTOPP_DISABLE_ASM
        INTVER=${VERSION_TXT_CONTENT}
        LINUX

        # Not sure about these:
        _UNICODE
        DONT_WRITE_EMBEDDED_FONTS
        UNICODE
    )
else() # Assume win+msvc
    set(COMMON_DEFINES
        _REENTRANT
        CRYPTOPP_DISABLE_ASM
        INTVER=${VERSION_TXT_CONTENT}
        NOMINMAX

        # Not sure about these:
        DONT_WRITE_EMBEDDED_FONTS
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND COMMON_DEFINES
        _DEBUG
    )
endif()

if( MSVC )

    set(COMMON_CXX_FLAGS
        /W4
        /wd4100 # unreferenced formal parameter
        /wd4101 # unreferenced local variable
        /wd4505 # unreferenced local function removed
        /O2
        /EHsc
        /permissive
    )

    set(COMMON_C_FLAGS
        /W4
        /wd4100
        /wd4101
        /wd4505
        /wd4996 # optional: CRT deprecation spam
        /O2
    )

    set(COMMON_LINK_OPTIONS
    )
    

else()

    set(COMMON_CXX_FLAGS
        -fvisibility=hidden
        -fvisibility-inlines-hidden
        -Wall
        -Wextra
        -Wno-ignored-qualifiers
        -Wno-register
        -Wno-unused-variable # TODO remove later; These are just here to reduce the clutter
        -Wno-unused-function # TODO remove later; These are just here to reduce the clutter
        -Wno-unused-parameter # TODO remove later; These are just here to reduce the clutter
        -O2 # Remove for debugging
    )

    set(COMMON_C_FLAGS
        -fvisibility=hidden
        # -fvisibility-inlines-hidden
        -Wall
        -Wextra
        -Wno-ignored-qualifiers
        # -Wno-register
        -Wno-implicit-function-declaration
        -Wno-unused-variable # TODO remove later; These are just here to reduce the clutter
        -Wno-unused-function # TODO remove later; These are just here to reduce the clutter
        -Wno-unused-parameter # TODO remove later; These are just here to reduce the clutter
        -O2 #Remove for debugging
    )

    set(COMMON_LINK_OPTIONS
        "-Wl,--disable-new-dtags"
    )

endif()


function(set_default_options target)
    if(NOT TARGET "${target}")
        message(FATAL_ERROR "set_default_options(): Target '${target}' does not exist yet.")
    endif()

    if( NOT MSVC )
        # Base RPATHs
        set_property(TARGET ${target} PROPERTY BUILD_RPATH "\$ORIGIN;\$ORIGIN/system")
        set_property(TARGET ${target} PROPERTY INSTALL_RPATH "\$ORIGIN;\$ORIGIN/system")

        # Optional: additional runtime paths from env variable RUN_PATH_ADDON
        if(DEFINED ENV{RUN_PATH_ADDON})
            set(RUN_PATH_ADDON "$ENV{RUN_PATH_ADDON}")
            string(REPLACE ";;" ";" RUN_PATH_ADDON_LIST "${RUN_PATH_ADDON}")

            set_property(TARGET ${target} APPEND PROPERTY INSTALL_RPATH "${RUN_PATH_ADDON_LIST}")
        endif()
    endif()

    # C++ flags
    target_compile_options(${target} PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${COMMON_CXX_FLAGS}>
    )

    # C flags
    target_compile_options(${target} PRIVATE
        $<$<COMPILE_LANGUAGE:C>:${COMMON_C_FLAGS}>
    )

    target_compile_definitions(${target} PRIVATE
        ${COMMON_DEFINES}
    )

    target_link_options(${target} PRIVATE
        ${COMMON_LINK_OPTIONS}
    )

    if( MSVC )
        target_link_libraries(${target} PRIVATE
            Rpcrt4
        )
    endif()
endfunction()

# ---------------------------------------------------------------------------
# Unit-test helper (CTest + GoogleTest from vcpkg)
# ---------------------------------------------------------------------------
# add_core_gtest(
#     NAME    <target name>
#     SOURCES <source files...>
#     LIBS    <core libraries to link...>
#     [GTEST_MAIN]               # provide a default main() (suite has none of its own)
#     [USE_GMOCK]                # also link GTest::gmock
#     [WORKING_DIRECTORY <dir>]  # CTest working dir (default: the test binary's dir)
# )
#
# Builds a GoogleTest executable, links it against the vcpkg-provided GTest and
# the requested core libraries, and registers it as a CTest test. The shared core
# libraries are collected into EO_CORE_OUTPUT_DIR (build/package) and depend on
# each other (and on icu) being co-located there; the test is run with
# LD_LIBRARY_PATH pointing at that directory so the loader can resolve them.
function(add_core_gtest)
    set(options GTEST_MAIN USE_GMOCK)
    set(oneValueArgs NAME WORKING_DIRECTORY GTEST_FILTER)
    set(multiValueArgs SOURCES LIBS)
    cmake_parse_arguments(T "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT T_NAME)
        message(FATAL_ERROR "add_core_gtest(): NAME is required")
    endif()
    if(NOT T_SOURCES)
        message(FATAL_ERROR "add_core_gtest(${T_NAME}): SOURCES is required")
    endif()

    if(NOT TARGET GTest::gtest)
        find_package(GTest CONFIG REQUIRED)
    endif()

    add_executable(${T_NAME} ${T_SOURCES})
    target_link_libraries(${T_NAME} PRIVATE GTest::gtest ${T_LIBS})
    if(T_USE_GMOCK)
        target_link_libraries(${T_NAME} PRIVATE GTest::gmock)
    endif()
    if(T_GTEST_MAIN)
        # Compile a bundled GoogleTest entry point instead of linking the vcpkg
        # gtest_main library, whose versioned soname is not reliably resolvable
        # on the runtime library path.
        set(_eo_gtest_main "${CMAKE_CURRENT_BINARY_DIR}/${T_NAME}_gtest_main.cpp")
        file(WRITE "${_eo_gtest_main}"
            "#include \"gtest/gtest.h\"\n"
            "int main(int argc, char** argv) {\n"
            "    ::testing::InitGoogleTest(&argc, argv);\n"
            "    return RUN_ALL_TESTS();\n"
            "}\n")
        target_sources(${T_NAME} PRIVATE "${_eo_gtest_main}")
    endif()

    set_default_options(${T_NAME})

    if(NOT T_WORKING_DIRECTORY)
        set(T_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${T_NAME}>")
    endif()
    set(_eo_test_args "")
    if(T_GTEST_FILTER)
        set(_eo_test_args "--gtest_filter=${T_GTEST_FILTER}")
    endif()
    add_test(NAME ${T_NAME} COMMAND ${T_NAME} ${_eo_test_args} WORKING_DIRECTORY "${T_WORKING_DIRECTORY}")

    # Resolve shared libraries at run time: the core libraries (and their icu
    # deps) from the collected output directory the shipped binaries load from,
    # plus the vcpkg lib dir when GTest is built as shared libraries.
    set(_eo_test_libpath "${EO_CORE_OUTPUT_DIR}")
    if(DEFINED VCPKG_INSTALLED_DIR AND DEFINED VCPKG_TARGET_TRIPLET)
        set(_eo_test_libpath "${_eo_test_libpath}:${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib")
    endif()
    set_tests_properties(${T_NAME} PROPERTIES
        ENVIRONMENT "LD_LIBRARY_PATH=${_eo_test_libpath}:$ENV{LD_LIBRARY_PATH}")
endfunction()

function(copy_artifacts_to_folder artifacts dest_dir)
    foreach(artifact ${artifacts})
        add_custom_command(TARGET ${artifact} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${dest_dir}"
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${artifact}> "${dest_dir}/"
            COMMENT "Copying ${artifact} to ${dest_dir}"
        )
    endforeach()
endfunction()

function(copy_icu_libs artifact)
    if( MSVC )

        file(GLOB ICU_DLLS
            "${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu/lib/icu*74.dll"
        )

        add_custom_command(TARGET ${artifact} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EO_CORE_OUTPUT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${ICU_DLLS}
                "${EO_CORE_OUTPUT_DIR}"
            COMMENT "Copying ICU DLLs to ${EO_CORE_OUTPUT_DIR}"
        )
    else()
        add_custom_command(TARGET ${artifact} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EO_CORE_OUTPUT_DIR}"
            COMMAND /bin/sh -c "cp -P \"${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu/lib\"/*.so* \"${EO_CORE_OUTPUT_DIR}/\""
            COMMENT "Copying ICU libs to ${EO_CORE_OUTPUT_DIR}"
        )
    endif()
endfunction()

function(declare_victory build_target)
    add_custom_command(TARGET ${build_target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "-------------------------------------------------------------"
        COMMAND ${CMAKE_COMMAND} -E echo "🎉  Success! [$<TARGET_FILE_NAME:${build_target}>] is ready!  🎉"
        COMMAND ${CMAKE_COMMAND} -E echo "-------------------------------------------------------------"
        COMMAND ${CMAKE_COMMAND} -E echo ""
    )
endfunction()

# Javascript bundler for wasm builds
function(inject_script TARGET_NAME TEMPLATE_FILE OUTPUT_FILE)
    cmake_parse_arguments(ARG "" "MODE" "REPLACEMENTS" ${ARGN})

    if(NOT ARG_MODE)
        set(ARG_MODE "POST_BUILD")
    endif()

    set(_helper "${CMAKE_CURRENT_BINARY_DIR}/inject_script.cmake")
    file(WRITE "${_helper}" [[
        file(READ "${T}" content)
        math(EXPR last "${COUNT} - 1")
        foreach(i RANGE ${last})
            file(READ "${S${i}}" s_data)
            string(REPLACE "${P${i}}" "${s_data}" content "${content}")
        endforeach()
        file(WRITE "${O}" "${content}")
    ]])

    set(_defs)
    set(_count 0)
    set(_pairs ${ARG_REPLACEMENTS})
    set(_script_files)
    while(_pairs)
        list(POP_FRONT _pairs _placeholder _script_file)
        list(APPEND _defs "-D" "P${_count}=${_placeholder}" "-D" "S${_count}=${_script_file}")
        list(APPEND _script_files "${_script_file}")
        math(EXPR _count "${_count} + 1")
    endwhile()

    set(_cmd
        COMMAND ${CMAKE_COMMAND}
            -D "T=${TEMPLATE_FILE}"
            -D "O=${OUTPUT_FILE}"
            -D "COUNT=${_count}"
            ${_defs}
            -P "${_helper}"
        COMMENT "Injecting scripts into ${TEMPLATE_FILE}"
        VERBATIM
    )

    if(ARG_MODE STREQUAL "PRE_BUILD")
        get_filename_component(_out_name "${OUTPUT_FILE}" NAME_WE)

        add_custom_command(
            OUTPUT "${OUTPUT_FILE}"
            ${_cmd}
            DEPENDS "${TEMPLATE_FILE}" ${_script_files}
        )
        add_custom_target(${TARGET_NAME}_inject_${_out_name} DEPENDS "${OUTPUT_FILE}")
        add_dependencies(${TARGET_NAME} ${TARGET_NAME}_inject_${_out_name})
    else()
        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            ${_cmd}
        )
    endif()
endfunction()

function( add_cpp_sources_from_dir_recurive TARGET DIR )
    file(GLOB_RECURSE DIR_SOURCES CONFIGURE_DEPENDS
        "${DIR}/*.cpp"
        "${DIR}/*.cxx"
        "${DIR}/*.h"
        "${DIR}/*.hpp"
        "${DIR}/*.hxx"
    )

    target_sources( ${TARGET} PRIVATE
        ${DIR_SOURCES}
    )

    target_include_directories( ${TARGET} PRIVATE
        ${DIR}
    )
endfunction()
