cmake_minimum_required(VERSION 3.10)

project(PdfFile)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include(${CORE_ROOT_DIR}/common.cmake)

set(OPENJPEG_ROOT_DIR "${CORE_ROOT_DIR}/DesktopEditor/raster/Jp2/openjpeg")
set(OPENJPEG_VERSION "2.4.0")
set(OPENJPEG_PATH "${OPENJPEG_ROOT_DIR}/openjpeg-${OPENJPEG_VERSION}")
set(OPENJPEG_LIB_JP2 "${OPENJPEG_PATH}/src/lib/openjp2")

set(DESKTOP_EDITOR_ROOT_DIR "../DesktopEditor")
set(FREETYPE_VERSION_TO_USE "2.10.4")
set(FREETYPE_SOURCES_DIR "${DESKTOP_EDITOR_ROOT_DIR}/freetype-${FREETYPE_VERSION_TO_USE}")
set(FONT_ENGINE_SOURCES_DIR "${DESKTOP_EDITOR_ROOT_DIR}/fontengine")
set(OFFICE_UTILS_ROOT_DIR "../OfficeUtils")

set(BROTLI_IN_TREE_LOCATION "${CORE_ROOT_DIR}/Common/3dParty/brotli/brotli")

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

# Note:
# The NOMINMAX define might make a difference. If there are problems,
# create a different version of cryptopplib by making the project name
# configurable with a variable.
if(NOT TARGET CryptoPPLib)
    add_subdirectory(${CORE_ROOT_DIR}/Common/3dParty/cryptopp/project CryptoPPLib)
endif()

# Note:
# This needs brotli and freetype, but thos are already included in
# graphics, so I'll just take the include paths and defines.

add_library(PdfFile SHARED
    lib/aconf.h
    lib/fofi/FoFiBase.cc
    lib/fofi/FoFiBase.h
    lib/fofi/FoFiEncodings.cc
    lib/fofi/FoFiEncodings.h
    lib/fofi/FoFiIdentifier.cc
    lib/fofi/FoFiIdentifier.h
    lib/fofi/FoFiTrueType.cc
    lib/fofi/FoFiTrueType.h
    lib/fofi/FoFiType1.cc
    lib/fofi/FoFiType1.h
    lib/fofi/FoFiType1C.cc
    lib/fofi/FoFiType1C.h
    lib/goo/FixedPoint.cc
    lib/goo/FixedPoint.h
    lib/goo/gfile.cc
    lib/goo/gfile.h
    lib/goo/GHash.cc
    lib/goo/GHash.h
    lib/goo/GList.cc
    lib/goo/GList.h
    lib/goo/gmem.cc
    lib/goo/gmem.h
    lib/goo/gmempp.cc
    lib/goo/gmempp.h
    lib/goo/GMutex.h
    lib/goo/GString.cc
    lib/goo/GString.h
    lib/goo/gtypes.h
    lib/goo/parseargs.c
    lib/goo/parseargs.h
    lib/goo/Trace.cc
    lib/goo/Trace.h
    lib/splash/Splash.cc
    lib/splash/Splash.h
    lib/splash/SplashBitmap.cc
    lib/splash/SplashBitmap.h
    lib/splash/SplashClip.cc
    lib/splash/SplashClip.h
    lib/splash/SplashErrorCodes.h
    lib/splash/SplashFont.cc
    lib/splash/SplashFont.h
    lib/splash/SplashFontEngine.cc
    lib/splash/SplashFontEngine.h
    lib/splash/SplashFontFile.cc
    lib/splash/SplashFontFile.h
    lib/splash/SplashFontFileID.cc
    lib/splash/SplashFontFileID.h
    lib/splash/SplashFTFont.cc
    lib/splash/SplashFTFont.h
    lib/splash/SplashFTFontEngine.cc
    lib/splash/SplashFTFontEngine.h
    lib/splash/SplashFTFontFile.cc
    lib/splash/SplashFTFontFile.h
    lib/splash/SplashGlyphBitmap.h
    lib/splash/SplashMath.h
    lib/splash/SplashPath.cc
    lib/splash/SplashPath.h
    lib/splash/SplashPattern.cc
    lib/splash/SplashPattern.h
    lib/splash/SplashScreen.cc
    lib/splash/SplashScreen.h
    lib/splash/SplashState.cc
    lib/splash/SplashState.h
    lib/splash/SplashTypes.h
    lib/splash/SplashXPath.cc
    lib/splash/SplashXPath.h
    lib/splash/SplashXPathScanner.cc
    lib/splash/SplashXPathScanner.h
    lib/xpdf/AcroForm.cc
    lib/xpdf/AcroForm.h
    lib/xpdf/Annot.cc
    lib/xpdf/Annot.h
    lib/xpdf/Array.cc
    lib/xpdf/Array.h
    lib/xpdf/BuiltinFont.cc
    lib/xpdf/BuiltinFont.h
    lib/xpdf/BuiltinFontTables.cc
    lib/xpdf/BuiltinFontTables.h
    lib/xpdf/Catalog.cc
    lib/xpdf/Catalog.h
    lib/xpdf/CharCodeToUnicode.cc
    lib/xpdf/CharCodeToUnicode.h
    lib/xpdf/CharTypes.h
    lib/xpdf/CMap.cc
    lib/xpdf/CMap.h
    lib/xpdf/CompactFontTables.h
    lib/xpdf/config.h
    lib/xpdf/Decrypt.cc
    lib/xpdf/Decrypt.h
    lib/xpdf/Dict.cc
    lib/xpdf/Dict.h
    lib/xpdf/DisplayState.cc
    lib/xpdf/DisplayState.h
    lib/xpdf/Error.cc
    lib/xpdf/Error.h
    lib/xpdf/ErrorCodes.h
    lib/xpdf/FontEncodingTables.cc
    lib/xpdf/FontEncodingTables.h
    lib/xpdf/Function.cc
    lib/xpdf/Function.h
    lib/xpdf/Gfx.cc
    lib/xpdf/Gfx.h
    lib/xpdf/GfxFont.cc
    lib/xpdf/GfxFont.h
    lib/xpdf/GfxState.cc
    lib/xpdf/GfxState.h
    lib/xpdf/GlobalParams.cc
    lib/xpdf/GlobalParams.h
    # lib/xpdf/HTMLGen.cc
    lib/xpdf/HTMLGen.h
    lib/xpdf/ImageOutputDev.cc
    lib/xpdf/ImageOutputDev.h
    lib/xpdf/JArithmeticDecoder.cc
    lib/xpdf/JArithmeticDecoder.h
    lib/xpdf/JBIG2Stream.cc
    lib/xpdf/JBIG2Stream.h
    lib/xpdf/JPXStream.cc
    lib/xpdf/JPXStream.h
    lib/xpdf/Lexer.cc
    lib/xpdf/Lexer.h
    lib/xpdf/Link.cc
    lib/xpdf/Link.h
    lib/xpdf/NameToCharCode.cc
    lib/xpdf/NameToCharCode.h
    lib/xpdf/NameToUnicodeTable.h
    lib/xpdf/Object.cc
    lib/xpdf/Object.h
    lib/xpdf/OptionalContent.cc
    lib/xpdf/OptionalContent.h
    lib/xpdf/Outline.cc
    lib/xpdf/Outline.h
    lib/xpdf/OutputDev.cc
    lib/xpdf/OutputDev.h
    lib/xpdf/Page.cc
    lib/xpdf/Page.h
    lib/xpdf/Parser.cc
    lib/xpdf/Parser.h
    lib/xpdf/PDF417Barcode.cc
    lib/xpdf/PDF417Barcode.h
    lib/xpdf/PDFCore.cc
    lib/xpdf/PDFCore.h
    # lib/xpdf/pdfdetach.cc
    lib/xpdf/PDFDoc.cc
    lib/xpdf/PDFDoc.h
    lib/xpdf/PDFDocEncoding.cc
    lib/xpdf/PDFDocEncoding.h
    # lib/xpdf/pdffonts.cc
    # lib/xpdf/pdfimages.cc
    # lib/xpdf/pdfinfo.cc
    # lib/xpdf/pdftohtml.cc
    # lib/xpdf/pdftopng.cc
    # lib/xpdf/pdftoppm.cc
    # lib/xpdf/pdftops.cc
    # lib/xpdf/pdftotext.cc
    lib/xpdf/PreScanOutputDev.cc
    lib/xpdf/PreScanOutputDev.h
    lib/xpdf/PSOutputDev.cc
    lib/xpdf/PSOutputDev.h
    lib/xpdf/PSTokenizer.cc
    lib/xpdf/PSTokenizer.h
    lib/xpdf/SecurityHandler.cc
    lib/xpdf/SecurityHandler.h
    lib/xpdf/ShadingImage.cc
    lib/xpdf/ShadingImage.h
    lib/xpdf/SplashOutputDev.cc
    lib/xpdf/SplashOutputDev.h
    lib/xpdf/Stream-CCITT.h
    lib/xpdf/Stream.cc
    lib/xpdf/Stream.h
    lib/xpdf/TextOutputDev.cc
    lib/xpdf/TextOutputDev.h
    lib/xpdf/TextString.cc
    lib/xpdf/TextString.h
    lib/xpdf/TileCache.cc
    lib/xpdf/TileCache.h
    lib/xpdf/TileCompositor.cc
    lib/xpdf/TileCompositor.h
    lib/xpdf/TileMap.cc
    lib/xpdf/TileMap.h
    lib/xpdf/UnicodeMap.cc
    lib/xpdf/UnicodeMap.h
    lib/xpdf/UnicodeMapTables.h
    lib/xpdf/UnicodeRemapping.cc
    lib/xpdf/UnicodeRemapping.h
    lib/xpdf/UnicodeTypeTable.cc
    lib/xpdf/UnicodeTypeTable.h
    lib/xpdf/UTF8.cc
    lib/xpdf/UTF8.h
    lib/xpdf/WebFont.cc
    lib/xpdf/WebFont.h
    lib/xpdf/XFAScanner.cc
    lib/xpdf/XFAScanner.h
    lib/xpdf/XRef.cc
    lib/xpdf/XRef.h
    lib/xpdf/Zoox.cc
    lib/xpdf/Zoox.h
    
    SrcReader/RendererOutputDev.cpp
    SrcReader/Adaptors.cpp
    SrcReader/PdfAnnot.cpp
    SrcReader/PdfFont.cpp
    SrcReader/GfxClip.cpp

    SrcReader/RendererOutputDev.h
    SrcReader/Adaptors.h
    SrcReader/MemoryUtils.h
    SrcReader/PdfAnnot.h
    SrcReader/PdfFont.h
    SrcReader/GfxClip.h

    # Base fonts
    Resources/CMapMemory/cmap_memory.cpp
    Resources/BaseFonts.cpp

    Resources/Fontd050000l.h
    Resources/Fontn019003l.h
    Resources/Fontn019004l.h
    Resources/Fontn019023l.h
    Resources/Fontn019024l.h
    Resources/Fontn021003l.h
    Resources/Fontn021004l.h
    Resources/Fontn021023l.h
    Resources/Fontn021024l.h
    Resources/Fontn022003l.h
    Resources/Fontn022004l.h
    Resources/Fontn022023l.h
    Resources/Fontn022024l.h
    Resources/Fonts050000l.h
    Resources/CMapMemory/cmap_memory.h
    Resources/BaseFonts.h

    SrcReader/JPXStream2.h
    SrcReader/JPXStream2.cpp

    SrcWriter/AcroForm.h
    SrcWriter/Annotation.h
    SrcWriter/Catalog.h
    SrcWriter/Consts.h
    SrcWriter/Destination.h
    SrcWriter/Document.h
    SrcWriter/Encodings.h
    SrcWriter/Encrypt.h
    SrcWriter/EncryptDictionary.h
    SrcWriter/Field.h
    SrcWriter/Font.h
    SrcWriter/Font14.h
    SrcWriter/FontCidTT.h
    SrcWriter/FontTT.h
    SrcWriter/FontTTWriter.h
    SrcWriter/GState.h
    SrcWriter/ICCProfile.h
    SrcWriter/Image.h
    SrcWriter/Info.h
    SrcWriter/Metadata.h
    SrcWriter/Objects.h
    SrcWriter/Outline.h
    SrcWriter/Pages.h
    SrcWriter/Pattern.h
    SrcWriter/RedactOutputDev.h
    SrcWriter/ResourcesDictionary.h
    SrcWriter/Shading.h
    SrcWriter/States.h
    SrcWriter/Streams.h
    SrcWriter/Types.h
    SrcWriter/Utils.h

    SrcWriter/AcroForm.cpp
    SrcWriter/Annotation.cpp
    SrcWriter/Catalog.cpp
    SrcWriter/Destination.cpp
    SrcWriter/Document.cpp
    SrcWriter/Encrypt.cpp
    SrcWriter/EncryptDictionary.cpp
    SrcWriter/Field.cpp
    SrcWriter/Font.cpp
    SrcWriter/Font14.cpp
    SrcWriter/FontCidTT.cpp
    SrcWriter/FontOTWriter.cpp
    SrcWriter/FontTT.cpp
    SrcWriter/FontTTWriter.cpp
    SrcWriter/GState.cpp
    SrcWriter/Image.cpp
    SrcWriter/Info.cpp
    SrcWriter/Metadata.cpp
    SrcWriter/Objects.cpp
    SrcWriter/Outline.cpp
    SrcWriter/Pages.cpp
    SrcWriter/Pattern.cpp
    SrcWriter/RedactOutputDev.cpp
    SrcWriter/ResourcesDictionary.cpp
    SrcWriter/Shading.cpp
    SrcWriter/States.cpp
    SrcWriter/Streams.cpp
    SrcWriter/Utils.cpp

    PdfFile.h
    PdfWriter.h
    PdfReader.h
    PdfEditor.h
    OnlineOfficeBinToPdf.h

    PdfFile.cpp
    PdfWriter.cpp
    PdfReader.cpp
    PdfEditor.cpp
    OnlineOfficeBinToPdf.cpp

    # openjpeg.pri
    # ${OPENJPEG_LIB_JP2}/bench_dwt.c
    ${OPENJPEG_LIB_JP2}/bio.c
    ${OPENJPEG_LIB_JP2}/cidx_manager.c
    ${OPENJPEG_LIB_JP2}/cio.c
    ${OPENJPEG_LIB_JP2}/dwt.c
    ${OPENJPEG_LIB_JP2}/event.c
    ${OPENJPEG_LIB_JP2}/function_list.c
    ${OPENJPEG_LIB_JP2}/image.c
    ${OPENJPEG_LIB_JP2}/invert.c
    ${OPENJPEG_LIB_JP2}/j2k.c
    ${OPENJPEG_LIB_JP2}/jp2.c
    ${OPENJPEG_LIB_JP2}/mct.c
    ${OPENJPEG_LIB_JP2}/mqc.c
    ${OPENJPEG_LIB_JP2}/openjpeg.c
    ${OPENJPEG_LIB_JP2}/opj_clock.c
    ${OPENJPEG_LIB_JP2}/opj_malloc.c
    ${OPENJPEG_LIB_JP2}/phix_manager.c
    ${OPENJPEG_LIB_JP2}/pi.c
    ${OPENJPEG_LIB_JP2}/ppix_manager.c
    ${OPENJPEG_LIB_JP2}/sparse_array.c
    # ${OPENJPEG_LIB_JP2}/t1_generate_luts.c
    ${OPENJPEG_LIB_JP2}/t1.c
    ${OPENJPEG_LIB_JP2}/t2.c
    ${OPENJPEG_LIB_JP2}/tcd.c
    # ${OPENJPEG_LIB_JP2}/test_sparse_array.c
    ${OPENJPEG_LIB_JP2}/tgt.c
    ${OPENJPEG_LIB_JP2}/thix_manager.c
    ${OPENJPEG_LIB_JP2}/thread.c
    ${OPENJPEG_LIB_JP2}/tpix_manager.c

    ${OPENJPEG_ROOT_DIR}/opj_bgraframe.cpp


    ${OPENJPEG_LIB_JP2}/bio.h
    ${OPENJPEG_LIB_JP2}/cidx_manager.h
    ${OPENJPEG_LIB_JP2}/cio.h
    ${OPENJPEG_LIB_JP2}/dwt.h
    ${OPENJPEG_LIB_JP2}/event.h
    ${OPENJPEG_LIB_JP2}/function_list.h
    ${OPENJPEG_LIB_JP2}/image.h
    ${OPENJPEG_LIB_JP2}/indexbox_manager.h
    ${OPENJPEG_LIB_JP2}/invert.h
    ${OPENJPEG_LIB_JP2}/j2k.h
    ${OPENJPEG_LIB_JP2}/jp2.h
    ${OPENJPEG_LIB_JP2}/mct.h
    ${OPENJPEG_LIB_JP2}/mqc_inl.h
    ${OPENJPEG_LIB_JP2}/mqc.h
    ${OPENJPEG_LIB_JP2}/openjpeg.h
    ${OPENJPEG_LIB_JP2}/opj_clock.h
    ${OPENJPEG_LIB_JP2}/opj_codec.h
    ${OPENJPEG_LIB_JP2}/opj_common.h
    ${OPENJPEG_LIB_JP2}/opj_includes.h
    ${OPENJPEG_LIB_JP2}/opj_intmath.h
    ${OPENJPEG_LIB_JP2}/opj_inttypes.h
    ${OPENJPEG_LIB_JP2}/opj_malloc.h
    ${OPENJPEG_LIB_JP2}/opj_stdint.h
    ${OPENJPEG_LIB_JP2}/pi.h
    ${OPENJPEG_LIB_JP2}/sparse_array.h
    ${OPENJPEG_LIB_JP2}/t1_luts.h
    ${OPENJPEG_LIB_JP2}/t1.h
    ${OPENJPEG_LIB_JP2}/t2.h
    ${OPENJPEG_LIB_JP2}/tcd.h
    ${OPENJPEG_LIB_JP2}/tgt.h
    ${OPENJPEG_LIB_JP2}/thread.h
    ${OPENJPEG_LIB_JP2}/tls_keys.h

    ${OPENJPEG_ROOT_DIR}/opj_config.h
    ${OPENJPEG_ROOT_DIR}/opj_config_private.h
    ${OPENJPEG_ROOT_DIR}/opj_apps_config.h
    ${OPENJPEG_ROOT_DIR}/opj_bgraframe.h
)

set_default_options(PdfFile)

target_compile_definitions(PdfFile PRIVATE
    _hypot=hypot
    PDFFILE_USE_DYNAMIC_LIBRARY
    # ANDROID # Android
    USE_EXTERNAL_JPEG2000

    # openjpeg.pri
    USE_JPIP
    OPJ_STATIC

    # PdfWriter
    CRYPTOPP_DISABLE_ASM
    NOMINMAX

    # brotli.pri
    FT_CONFIG_OPTION_USE_BROTLI
)

if( UNIX )
    target_compile_definitions(PdfFile PRIVATE
        HAVE_UNISTD_H # Linux and mac
        HAVE_FCNTL_H # Linux and mac
    )
endif()

target_include_directories(PdfFile PRIVATE
    lib/goo
    lib/fofi
    lib/splash
    lib

    # openjpeg.pri
    ${OPENJPEG_LIB_JP2}
    ${OPENJPEG_ROOT_DIR}

    # freetype.pri
    ${FREETYPE_SOURCES_DIR}/include
    ${FREETYPE_SOURCES_DIR}/include/freetype
    # !config_zlip_image {
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11
        ${OFFICE_UTILS_ROOT_DIR}/src
    # }

    # brotli.pri
    ${BROTLI_IN_TREE_LOCATION}/c/include
)

if( UNIX )
    target_compile_options(PdfFile PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-include limits>
    )
endif()

if(UNIX AND NOT APPLE)
    target_compile_options(PdfFile PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-narrowing>
    )
endif()

if(ANDROID)
    target_compile_options(PdfFile PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-narrowing>
    )
endif()

target_link_libraries(PdfFile PUBLIC
    CryptoPPLib
    graphics
    kernel
    UnicodeConverter
    kernel_network
)

copy_artifacts_to_folder("PdfFile" "${EO_CORE_OUTPUT_DIR}")

declare_victory( PdfFile )

