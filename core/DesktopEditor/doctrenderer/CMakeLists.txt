cmake_minimum_required(VERSION 3.10)

project(doctrenderer)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")

include(${CORE_ROOT_DIR}/common.cmake)

# As far as I can tell, this should be set to 1 when building on mac.
if(NOT DEFINED USE_JAVASCRIPT_CORE)
    set(USE_JAVASCRIPT_CORE 0)
endif()

if(NOT DEFINED DRAWINGFILE_SUPPORT)
    set(DRAWINGFILE_SUPPORT 1)
endif()

if(NOT DEFINED V8_USE_INSPECTOR)
    set(V8_USE_INSPECTOR 1)
endif()

set(DESKTOP_EDITOR_ROOT "..")
set(COMMON_3RDPARTY_ROOT "${CORE_ROOT_DIR}/Common/3dParty")

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET kernel_network)
    add_subdirectory(${CORE_ROOT_DIR}/Common/Network kernel_network)
endif()

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

if(DRAWINGFILE_SUPPORT)
    if(NOT TARGET PdfFile)
        add_subdirectory(${CORE_ROOT_DIR}/PdfFile PdfFile)
    endif()

    if(NOT TARGET XpsFile)
        add_subdirectory(${CORE_ROOT_DIR}/XpsFile XpsFile)
    endif()

    if(NOT TARGET DjVuFile)
        add_subdirectory(${CORE_ROOT_DIR}/DjVuFile DjVuFile)
    endif()

    if(NOT TARGET DocxRenderer)
        add_subdirectory(${CORE_ROOT_DIR}/DocxRenderer DocxRenderer)
    endif()
endif()

add_library(doctrenderer SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/docbuilder_p.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/docbuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/doctrenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/editors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/Default.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/GraphicsEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/HashEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/MemoryStreamEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/NativeBuilderDocumentEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/NativeBuilderEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/NativeControlEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/PointerEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/TextMeasurerEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/ZipEmbed.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/js_base.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/js_logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hash.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nativecontrol.cpp
    ${CORE_ROOT_DIR}/Common/3dParty/pole/pole.cpp
    ${CORE_ROOT_DIR}/Common/OfficeFileFormatChecker2.cpp
    ${CORE_ROOT_DIR}/OOXML/Base/unicode_util.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/docbuilder_p.h
    ${CMAKE_CURRENT_SOURCE_DIR}/docbuilder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/doctrenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/editors.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/Default.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/GraphicsEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/HashEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/MemoryStreamEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/NativeBuilderDocumentEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/NativeBuilderEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/NativeControlEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/PointerEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/TextMeasurerEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/embed/ZipEmbed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics.h
    ${CMAKE_CURRENT_SOURCE_DIR}/hash.h
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/js_base.h
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/js_base_p.h
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/js_embed.h
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/js_logger.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nativecontrol.h
    ${CMAKE_CURRENT_SOURCE_DIR}/server.h

    # Serialize objects to JS
    ${CMAKE_CURRENT_SOURCE_DIR}/json/json.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/json/json_values.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/json/json.h
    ${CMAKE_CURRENT_SOURCE_DIR}/json/json_p.h
    ${CMAKE_CURRENT_SOURCE_DIR}/json/json_values.h
    ${CMAKE_CURRENT_SOURCE_DIR}/json/serialization.h
)

set_default_options(doctrenderer)

if( MSVC )
    target_compile_definitions( doctrenderer PRIVATE
        _UNICODE
        UNICODE
    )

    target_precompile_headers(doctrenderer PRIVATE
        ${CORE_ROOT_DIR}/msvc_fix.h
    )
endif()

if(USE_JAVASCRIPT_CORE)
    target_sources(doctrenderer PRIVATE
        ${DESKTOP_EDITOR_ROOT}/common/Mac/NSString+StringUtils.mm
        ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/jsc/jsc_base.mm

        ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/jsc/jsc_base.h
    )
else()
    target_sources(doctrenderer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/v8_base.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/v8_base.h
    )

    if(V8_USE_INSPECTOR)
        target_sources(doctrenderer PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/inspector_pool.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/inspector.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/utils.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/v8_inspector_channel.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/v8_inspector_client.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/websocket_server.cpp

            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/inspector_pool.h
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/inspector.h
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/utils.h
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/v8_inspector_channel.h
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/v8_inspector_client.h
            ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector/websocket_server.h
        )
    endif()
endif()

if(DRAWINGFILE_SUPPORT)
    target_sources(doctrenderer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/embed/DrawingFileEmbed.cpp
        ${DESKTOP_EDITOR_ROOT}/graphics/pro/js/wasm/src/HTMLRendererText.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/drawingfile.h
        ${CMAKE_CURRENT_SOURCE_DIR}/embed/DrawingFileEmbed.h
    )
endif()

# BEGIN HACK
# See "files for embedded classes" section in doctrenderer.pri
# What it intends to do:
# We have a bunch of headers in the embed directory. For each
# header we have a corresponding source file in embed/jsc, or
# embed/v8 depending on the platform we use (mac or not).
# This hack attempts to match the headers with the corresponding
# source files.
set(EMBED_HEADERS
    GraphicsEmbed
    HashEmbed
    MemoryStreamEmbed
    NativeBuilderEmbed
    NativeBuilderDocumentEmbed
    NativeControlEmbed
    PointerEmbed
    TextMeasurerEmbed
    ZipEmbed
)
if(DRAWINGFILE_SUPPORT)
    list(APPEND EMBED_HEADERS DrawingFileEmbed)
endif()

foreach(name ${EMBED_HEADERS})
    list(APPEND EMBED_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/embed/${name}.h")

    if(USE_JAVASCRIPT_CORE)
        list(APPEND EMBED_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/embed/jsc/jsc_${name}.mm")
    else()
        list(APPEND EMBED_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/embed/v8/v8_${name}.cpp")
    endif()
endforeach()

target_sources(doctrenderer PRIVATE
    ${EMBED_HEADER_FILES}
    ${EMBED_SRC_FILES}
)
# END HACK

target_include_directories(doctrenderer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/addon
    ${CMAKE_CURRENT_SOURCE_DIR}/js_internal # js_base_embed.pri
    ${OPENSSL_INSTALL_DIR_ABS}/include
    ${V8_INSTALL_DIR_ABS}/v8
    ${V8_INSTALL_DIR_ABS}/v8/include
)

if(V8_USE_INSPECTOR)
    target_include_directories(doctrenderer PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/js_internal/v8/inspector
    )
endif()

target_compile_definitions(doctrenderer PRIVATE
    DOCTRENDERER_USE_DYNAMIC_LIBRARY_BUILDING
    JSBASE_USE_DYNAMIC_LIBRARY_BUILDING
    BUIDLER_OPEN_DOWNLOAD_ENABLED
    BUIDLER_OPEN_BASE64_ENABLED
    SUPPORT_HARFBUZZ_SHAPER # textshaper.pri
    V8_VERSION_89_PLUS # v8.pri
    V8_SUPPORT_SNAPSHOTS  # v8.pri
    V8_COMPRESS_POINTERS # v8.pri
)

if(USE_JAVASCRIPT_CORE)
    target_compile_definitions(doctrenderer PRIVATE
        JS_ENGINE_JAVASCRIPTCORE
    )
endif()

if(V8_USE_INSPECTOR)
    target_compile_definitions(doctrenderer PRIVATE
        V8_INSPECTOR
    )
endif()

if(ANDROID)
    target_compile_definitions(doctrenderer PRIVATE
        DISABLE_MEMORY_LIMITATION
    )
endif()

if(DRAWINGFILE_SUPPORT)
    target_compile_definitions(doctrenderer PRIVATE
        WASM_SERIALIZER_USE_ALLOCATOR
    )
endif()

if(APPLE)
    target_compile_options(doctrenderer
        $<$<COMPILE_LANGUAGE:OBJC>:-fobjc-arc -fobjc-weak -framework Foundation -framework JavaScriptCore>
        $<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc -fobjc-weak -framework Foundation -framework JavaScriptCore>
    )
endif()

target_link_libraries(doctrenderer INTERFACE 
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
)

target_link_libraries(doctrenderer PRIVATE
    ${OPENSSL_LIBSSL}
    ${OPENSSL_LIBCRYPTO}
    ${V8_MONOLITH}
)

target_link_libraries(doctrenderer PUBLIC
    graphics
    kernel
    UnicodeConverter
    kernel_network
)

if( MSVC )
    target_link_libraries(doctrenderer PUBLIC
        Rpcrt4
        Winmm
        Dbghelp
    )
endif()

if(DRAWINGFILE_SUPPORT)
    target_link_libraries(doctrenderer PUBLIC
        PdfFile
        XpsFile
        DjVuFile
        DocxRenderer
    )
endif()

if( UNIX )
    target_link_libraries(doctrenderer PUBLIC
        pthread
    )
endif()

copy_artifacts_to_folder("doctrenderer" "${EO_CORE_OUTPUT_DIR}")

declare_victory( doctrenderer )
