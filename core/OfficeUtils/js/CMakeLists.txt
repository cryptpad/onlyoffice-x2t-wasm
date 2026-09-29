cmake_minimum_required(VERSION 3.10)
project(zlib)

# -------------------------------------------------
# Ensure Emscripten toolchain
# -------------------------------------------------
if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "This project must be built with Emscripten (use emcmake).")
endif()


# -------------------------------------------------
# Source files (compile_files_array)
# -------------------------------------------------
set(CORE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(${CORE_ROOT}/common.cmake)

set(SRC
    # ---- minizip ----
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/unzip.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/ioapi.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/zip.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/ioapibuf.c


    # ---- zlib core ----
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/inflate.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/zutil.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/adler32.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/crc32.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/inftrees.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/inffast.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/deflate.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/trees.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/uncompr.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/compress.c

    # ---- project glue ----
    ${CORE_ROOT}/OfficeUtils/src/ZipBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/base.cpp
    ${CORE_ROOT}/OfficeUtils/src/zlib_addon.c

    # ---- raster ----
    ${CORE_ROOT}/DesktopEditor/graphics/Image.cpp
    ${CORE_ROOT}/DesktopEditor/graphics/Matrix.cpp
    ${CORE_ROOT}/DesktopEditor/graphics/GraphicsPath.cpp
    ${CORE_ROOT}/DesktopEditor/raster/BgraFrame.cpp
    ${CORE_ROOT}/DesktopEditor/raster/ImageFileFormatChecker.cpp

    ${CORE_ROOT}/DesktopEditor/graphics/pro/js/qt/raster/pro_Fonts_empty.cpp
    ${CORE_ROOT}/DesktopEditor/graphics/pro/js/qt/raster/pro_Graphics_empty.cpp
    ${CORE_ROOT}/DesktopEditor/graphics/pro/js/qt/raster/raster.cpp

    # ---- ci ----
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximaenc.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximaexif.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximage.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximainfo.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximajpg.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximalpha.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximapal.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximasel.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/xmemfile.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximapng.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximabmp.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximatran.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximatif.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/tif_xfile.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximajas.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximagif.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximaico.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximatga.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximapcx.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximawbmp.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximamng.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximapsd.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximaska.cpp
    ${CORE_ROOT}/DesktopEditor/cximage/CxImage/ximaraw.cpp

    # ---- jpeg ----
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jerror.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdmarker.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdapimin.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdmaster.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdapistd.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcomapi.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jutils.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdinput.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdmainct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jmemmgr.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jquant1.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jquant2.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdmerge.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdcolor.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdsample.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdpostct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jddctmgr.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdarith.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdhuff.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jdcoefct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jmemnobs.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jidctint.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jidctfst.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jidctflt.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jaricom.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcapimin.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcparam.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcapistd.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcinit.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcmaster.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jccolor.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcmarker.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcsample.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcprepct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcdctmgr.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcarith.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jchuff.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jccoefct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jcmainct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jfdctint.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jfdctfst.c
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg/jfdctflt.c

    # ---- png ----
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngread.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngmem.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngerror.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/png.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngrio.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngtrans.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngget.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngrutil.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngrtran.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngset.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngwrite.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngwio.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngwutil.c
    ${CORE_ROOT}/DesktopEditor/cximage/png/pngwtran.c

    # ---- tiff ----
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_close.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_dir.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_aux.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_getimage.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_strip.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_open.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_tile.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_error.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_read.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_flush.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_dirinfo.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_compress.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_warning.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_swab.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_color.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_dirread.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_write.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_codec.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_luv.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_dirwrite.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_dumpmode.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_fax3.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_ojpeg.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_jpeg.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_next.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_thunder.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_packbits.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_lzw.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_zip.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_fax3sm.c
    ${CORE_ROOT}/DesktopEditor/cximage/tiff/tif_predict.c

    # ---- Metafile ----
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/MetaFile.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Common/CClip.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Common/MetaFileTypes.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Common/MetaFileUtils.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Common/CPathConverter.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Common/CPath.cpp
    ${CORE_ROOT}/DesktopEditor/raster/PICT/PICFile.cpp

    # ---- Emf ----
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfInterpretator/CEmfInterpretator.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfInterpretator/CEmfInterpretatorArray.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfInterpretator/CEmfInterpretatorRender.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfInterpretator/CEmfInterpretatorSvg.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfParser/CEmfParser.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfParser/CEmfParserBase.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfParser/CEmfPlusParser.cpp
    #../../DesktopEditor/raster/Metafile/Emf/EmfClip.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfObjects.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfPlusObjects.cpp
    #../../DesktopEditor/raster/Metafile/Emf/EmfPath.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfPlayer.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Emf/EmfFile.cpp

    # ---- wmf ----
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfInterpretator/CWmfInterpretatorSvg.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfInterpretator/CInterpretatorSvgBase.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfInterpretator/CWmfInterpretatorRender.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfInterpretator/cwmfinterpretator.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfParser/CWmfParser.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfParser/CWmfParserBase.cpp
    #../../DesktopEditor/raster/Metafile/Wmf/WmfClip.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfObjects.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Metafile/Wmf/WmfPlayer.cpp

    # ---- common ----
    ${CORE_ROOT}/DesktopEditor/common/File.cpp
    ${CORE_ROOT}/DesktopEditor/common/Base64.cpp
    ${CORE_ROOT}/DesktopEditor/common/StringExt.cpp
    ${CORE_ROOT}/DesktopEditor/common/StringBuilder.cpp
    ${CORE_ROOT}/DesktopEditor/common/../xml/src/xmlwriter.cpp
    #../../DesktopEditor/common/../xml/src/xmllight.cpp

    # ---- agg ----
    ${CORE_ROOT}/DesktopEditor/agg-2.4/src/agg_trans_affine.cpp
    ${CORE_ROOT}/DesktopEditor/agg-2.4/src/agg_bezier_arc.cpp


    ### These are part of full build    
    # ---- jasper ----
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_init.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_stream.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_malloc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_image.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_cm.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_seq.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_string.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_icc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_debug.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_iccdata.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_tvp.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/base/jas_version.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/mif/mif_cod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/pnm/pnm_dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/pnm/pnm_enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/pnm/pnm_cod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/bmp/bmp_dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/bmp/bmp_enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/bmp/bmp_cod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/ras/ras_dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/ras/ras_enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jp2/jp2_dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jp2/jp2_enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jp2/jp2_cod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_cs.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_t1cod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_math.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_util.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_tsfb.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_mct.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_t1enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_t1dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_bs.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_t2cod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_t2enc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_t2dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_tagtree.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_mqenc.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_mqdec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_mqcod.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpc/jpc_qmfb.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpg/jpg_val.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/jpg/jpg_dummy.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/pgx/pgx_dec.c
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/pgx/pgx_enc.c

    # ---- jp2 ----
    ${CORE_ROOT}/DesktopEditor/raster/Jp2/J2kFile.cpp
    ${CORE_ROOT}/DesktopEditor/raster/Jp2/Reader.cpp

    # ---- mng ----
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_hlapi.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_callback_xs.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_prop_xs.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_object_prc.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_zlib.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_jpeg.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_pixels.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_read.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_error.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_display.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_write.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_chunk_io.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_cms.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_filter.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_chunk_prc.c
    ${CORE_ROOT}/DesktopEditor/cximage/mng/libmng_chunk_xs.c

    # ---- libpsd ----
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/psd.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/file_header.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/color_mode.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/image_resource.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/blend.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/layer_mask.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/image_data.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/stream.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/psd_system.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/color.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/pattern_fill.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/color_balance.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/channel_image.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/gradient_fill.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/invert.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/posterize.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/brightness_contrast.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/solid_color.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/threshold.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/effects.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/selective_color.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/channel_mixer.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/photo_filter.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/type_tool.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/gradient_map.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/hue_saturation.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/levels.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/curves.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/pattern.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/psd_zip.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/descriptor.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/drop_shadow.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/inner_shadow.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/color_overlay.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/outer_glow.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/inner_glow.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/bevel_emboss.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/satin.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/gradient_overlay.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/stroke.c
    ${CORE_ROOT}/DesktopEditor/cximage/libpsd/pattern_overlay.c

    # ---- raw ----
    ${CORE_ROOT}/DesktopEditor/cximage/raw/libdcr.c

    # ---- jbig ----
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/JBig2File.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/Encoder/jbig2enc.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/Encoder/jbig2arith.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/Encoder/jbig2sym.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pixconv.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/writefile.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/scale.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pix1.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pix2.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pix3.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pix4.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pix5.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/grayquant.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/grayquantlow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/seedfill.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/jbclass.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pixabasic.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/numabasic.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/morphseq.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/binexpandlow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/ptabasic.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/rop.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/colormap.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pngiostub.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/lepton_utils.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/scalelow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/enhance.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/jpegio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/jpegiostub.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/spixio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/webpio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/webpiostub.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/psio2.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/gifio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/gifiostub.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pnmio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/tiffio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/tiffiostub.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/bmpio.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/binexpand.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/compare.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/boxbasic.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/conncomp.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pixafunc1.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/boxfunc1.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/ptafunc1.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/binreduce.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/seedfilllow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/sel1.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/morphapp.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/correlscore.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/sarray.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/morph.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/roplow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/fpix1.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/stack.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pixacc.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/pixarith.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/convolve.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/binreducelow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/convolvelow.cpp
    ${CORE_ROOT}/DesktopEditor/raster/JBig2/source/LeptonLib/arithlow.cpp

)


# -------------------------------------------------
# Executable (WASM module)
# -------------------------------------------------
add_executable(${PROJECT_NAME} ${SRC})

# -------------------------------------------------
# Output folder
# -------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}/engine
)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11
    ${CORE_ROOT}/OfficeUtils/src
    ${CORE_ROOT}/DesktopEditor/cximage/jasper/include
    ${CORE_ROOT}/DesktopEditor/cximage/jpeg
    ${CORE_ROOT}/DesktopEditor/cximage/png
    ${CORE_ROOT}/DesktopEditor/xml/libxml2/include
    ${CORE_ROOT}/DesktopEditor/agg-2.4/include
)

# -------------------------------------------------
# Defines
# -------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
    __linux__ _LINUX UNIX _QT
    EXCLUDE_JPG_SUPPORT
    METAFILE_SUPPORT_WMF_EMF
    MNG_SUPPORT_DISPLAY
    MNG_SUPPORT_READ
    MNG_SUPPORT_WRITE
    MNG_ACCESS_CHUNKS
    MNG_STORE_CHUNKS
    MNG_ERROR_TELLTALE
    HAVE_UNISTD_H HAVE_FCNTL_H _ARM_ALIGN_
    CXIMAGE_DISABLE_SUPPORT_MNG
    CXIMAGE_DISABLE_SUPPORT_ADDITIONS
    IMAGE_CHECKER_DISABLE_XML
    _tcsnicmp=strncmp
    _lseek=lseek
    _getcwd=getcwd
    NO_CONSOLE_IO
    BUILD_ZLIB_AS_SOURCES
)

# -------------------------------------------------
# Compiler flags (non -s ones)
# -------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    -O3
    -Wno-unused-command-line-argument
    -Wno-register
)


# -------------------------------------------------
# Linker flags (Emscripten -s options)
# -------------------------------------------------
target_link_options(${PROJECT_NAME} PRIVATE
    "-sALLOW_MEMORY_GROWTH=1"
    "-sFILESYSTEM=0"
    "-sENVIRONMENT=web,worker"
    "-sEXPORTED_FUNCTIONS=['_malloc','_free','_Zlib_Malloc','_Zlib_Free','_Zlib_Create','_Zlib_Open','_Zlib_Close','_Zlib_AddFile','_Zlib_RemoveFile','_Zlib_GetPaths','_Zlib_GetFile','_Zlib_Save','_Raster_DecodeFile','_Raster_GetDecodedBuffer','_Raster_GetHeight','_Raster_GetWidth','_Raster_GetStride','_Raster_Destroy','_Raster_EncodeImageData','_Raster_Encode','_Raster_GetEncodedBuffer','_Raster_GetEncodedSize','_Raster_DestroyEncodedData','_Image_GetFormat']"
    "-sEXPORTED_RUNTIME_METHODS=['HEAP8']"
    "-sLEGACY_VM_SUPPORT=1"
    "SHELL:--pre-js ${CORE_ROOT}/Common/js/string_utf8.js"
    "SHELL:--pre-js ${CORE_ROOT}/Common/js/desktop_fetch_new.js"
)

# Create final .js for Wasm
inject_script(
    ${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/zlib.js"
    "${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}/engine/${PROJECT_NAME}.js"
    MODE POST_BUILD
    REPLACEMENTS
        "{{{ MODULE }}}"  "${EO_CORE_OUTPUT_DIR}/${PROJECT_NAME}/engine/${PROJECT_NAME}.js"
)

add_custom_target(${PROJECT_NAME}_copy_extra_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/index.html"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../index.html"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/code.js"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../code.js"
    COMMENT "Copying extra files to output"
    VERBATIM
)

declare_victory( ${PROJECT_NAME})
