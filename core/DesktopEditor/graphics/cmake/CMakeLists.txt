cmake_minimum_required(VERSION 3.10)

project(graphics)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../..")

include(${CORE_ROOT_DIR}/common.cmake)

set(GRAPHICS_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
set(DESKTOP_EDITOR_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
set(OFFICE_UTILS_ROOT_DIR "${CORE_ROOT_DIR}/OfficeUtils")
set(METAFILE_SOURCER_DIR "${DESKTOP_EDITOR_ROOT_DIR}/raster/Metafile")
set(CSS_ROOT_DIR "${CORE_ROOT_DIR}/Common/3dParty/html/css")

set(FREETYPE_VERSION_TO_USE "2.10.4")
set(FREETYPE_SOURCES_DIR "${DESKTOP_EDITOR_ROOT_DIR}/freetype-${FREETYPE_VERSION_TO_USE}")
set(FONT_ENGINE_SOURCES_DIR "${DESKTOP_EDITOR_ROOT_DIR}/fontengine")

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

set(KATANA_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/html/katana-parser")
set(GUMBO_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/html/gumbo-parser")
get_filename_component(KATANA_INSTALL_DIR_ABS "${KATANA_INSTALL_DIR}" ABSOLUTE)
get_filename_component(GUMBO_INSTALL_DIR_ABS "${GUMBO_INSTALL_DIR}" ABSOLUTE)

set(HARFBUZZ_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/harfbuzz")
get_filename_component(HARFBUZZ_INSTALL_DIR_ABS "${HARFBUZZ_INSTALL_DIR}" ABSOLUTE)

set(BROTLI_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/brotli")
get_filename_component(BROTLI_INSTALL_DIR_ABS "${BROTLI_INSTALL_DIR}" ABSOLUTE)

set(HYPHEN_INSTALL_DIR "${EO_CORE_3RD_PARTY_INSTALL_DIR}/hyphen")
get_filename_component(HYPHEN_INSTALL_DIR_ABS "${HYPHEN_INSTALL_DIR}" ABSOLUTE)

add_library(graphics SHARED
    ${METAFILE_SOURCER_DIR}/MetaFile.h
    ${METAFILE_SOURCER_DIR}/Common/MetaFile.h
    ${METAFILE_SOURCER_DIR}/Common/IOutputDevice.h
    ${METAFILE_SOURCER_DIR}/Common/MetaFileTypes.h
    ${METAFILE_SOURCER_DIR}/Common/MetaFileObjects.h
    ${METAFILE_SOURCER_DIR}/Common/MetaFileRenderer.h
    ${METAFILE_SOURCER_DIR}/Common/MetaFileUtils.h

    ${METAFILE_SOURCER_DIR}/MetaFile.cpp
	${METAFILE_SOURCER_DIR}/Common/MetaFileTypes.cpp
	${METAFILE_SOURCER_DIR}/Common/MetaFileUtils.cpp

    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_arc.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_arrowhead.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_bezier_arc.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_bspline.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_curves.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_image_filters.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_line_aa_basics.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_line_profile_aa.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_trans_affine.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_vcgen_bspline.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_vcgen_contour.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_vcgen_dash.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_vcgen_markers_term.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_vcgen_smooth_poly1.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/src/agg_vcgen_stroke.cpp

    ${GRAPHICS_ROOT_DIR}/AlphaMask.cpp
    ${GRAPHICS_ROOT_DIR}/ArrowHead.cpp
    ${GRAPHICS_ROOT_DIR}/BooleanOperations.cpp
    ${GRAPHICS_ROOT_DIR}/Brush.cpp
    ${GRAPHICS_ROOT_DIR}/Clip.cpp
    ${GRAPHICS_ROOT_DIR}/commands/AnnotField.cpp
    ${GRAPHICS_ROOT_DIR}/commands/DocInfo.cpp
    ${GRAPHICS_ROOT_DIR}/commands/FormField.cpp
    ${GRAPHICS_ROOT_DIR}/Graphics.cpp
    ${GRAPHICS_ROOT_DIR}/GraphicsLayer.cpp
    ${GRAPHICS_ROOT_DIR}/GraphicsPath.cpp
    ${GRAPHICS_ROOT_DIR}/GraphicsRenderer.cpp
    ${GRAPHICS_ROOT_DIR}/Matrix.cpp
    ${GRAPHICS_ROOT_DIR}/MetafileToGraphicsRenderer.cpp
    ${GRAPHICS_ROOT_DIR}/MetafileToRenderer.cpp
    ${GRAPHICS_ROOT_DIR}/MetafileToRendererReader.cpp
    ${GRAPHICS_ROOT_DIR}/pro/officedrawingfile.cpp
    ${GRAPHICS_ROOT_DIR}/pro/pro_Graphics.cpp
    ${GRAPHICS_ROOT_DIR}/pro/pro_Image.cpp

    ${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/include/test_grads/custom_gradients.h

    ${GRAPHICS_ROOT_DIR}/AlphaMask_p.h
    ${GRAPHICS_ROOT_DIR}/AlphaMask.h
    ${GRAPHICS_ROOT_DIR}/ArrowHead.h
    ${GRAPHICS_ROOT_DIR}/boolean_operations_math.h
    ${GRAPHICS_ROOT_DIR}/BooleanOperations.h
    ${GRAPHICS_ROOT_DIR}/Brush.h
    ${GRAPHICS_ROOT_DIR}/Clip.h
    ${GRAPHICS_ROOT_DIR}/Color.h
    ${GRAPHICS_ROOT_DIR}/commands/AnnotField.h
    ${GRAPHICS_ROOT_DIR}/commands/DocInfo.h
    ${GRAPHICS_ROOT_DIR}/commands/FormField.h
    ${GRAPHICS_ROOT_DIR}/config.h
    ${GRAPHICS_ROOT_DIR}/Defines.h
    ${GRAPHICS_ROOT_DIR}/Graphics.h
    ${GRAPHICS_ROOT_DIR}/Graphics.h
    ${GRAPHICS_ROOT_DIR}/GraphicsLayer.h
    ${GRAPHICS_ROOT_DIR}/GraphicsLayerBlend.h
    ${GRAPHICS_ROOT_DIR}/GraphicsPath_private.h
    ${GRAPHICS_ROOT_DIR}/GraphicsPath.h
    ${GRAPHICS_ROOT_DIR}/GraphicsRenderer.h
    ${GRAPHICS_ROOT_DIR}/ImageFilesCache.h
    ${GRAPHICS_ROOT_DIR}/Matrix_private.h
    ${GRAPHICS_ROOT_DIR}/Matrix.h
    ${GRAPHICS_ROOT_DIR}/MetafileToGraphicsRenderer.h
    ${GRAPHICS_ROOT_DIR}/MetafileToRenderer.h
    ${GRAPHICS_ROOT_DIR}/MetafileToRendererCheck.h
    ${GRAPHICS_ROOT_DIR}/MetafileToRendererReader.h
    ${GRAPHICS_ROOT_DIR}/pro/Graphics.h
    ${GRAPHICS_ROOT_DIR}/pro/Image.h
    ${GRAPHICS_ROOT_DIR}/pro/officedrawingfile.h
    ${GRAPHICS_ROOT_DIR}/shading_info.h
    ${GRAPHICS_ROOT_DIR}/structures.h

    # raster.pri
    ${DESKTOP_EDITOR_ROOT_DIR}/graphics/Image.cpp
	${DESKTOP_EDITOR_ROOT_DIR}/raster/BgraFrame.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/raster/ImageFileFormatChecker.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/wrtarga.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/wrrle.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/wrppm.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/wrjpgcom.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/wrgif.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/wrbmp.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/transupp.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdtarga.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdswitch.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdrle.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdppm.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdjpgcom.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdgif.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdcolmap.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/rdbmp.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jutils.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jpegtran.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jquant1.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jquant2.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdpostct.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdsample.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdtrans.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jerror.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jfdctflt.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jfdctfst.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jfdctint.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jidctflt.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jidctfst.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jidctint.c
    #${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jmemansi.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jmemmgr.c
    #${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jmemname.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jmemnobs.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jaricom.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcapimin.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcapistd.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcarith.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jccoefct.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jccolor.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcdctmgr.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jchuff.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcinit.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcmainct.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcmarker.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcmaster.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcomapi.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcparam.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcprepct.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jcsample.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jctrans.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdapimin.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdapistd.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdarith.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdatadst.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdatasrc.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdcoefct.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdcolor.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jddctmgr.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdhuff.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdinput.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdmainct.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdmarker.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdmaster.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/jdmerge.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/cdjpeg.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/cjpeg.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/ckconfig.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg/djpeg.c

    # !disable_cximage_mng {
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_callback_xs.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_chunk_descr.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_chunk_io.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_chunk_prc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_chunk_xs.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_cms.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_display.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_dither.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_error.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_filter.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_hlapi.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_jpeg.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_object_prc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_pixels.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_prop_xs.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_read.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_trace.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_write.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/mng/libmng_zlib.c
    # }

    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/png.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngerror.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngget.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngmem.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngpread.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngread.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngrio.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngrtran.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngrutil.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngset.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngtrans.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngwio.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngwrite.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngwtran.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/png/pngwutil.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_stream.cxx
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_aux.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_close.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_codec.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_color.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_compress.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_dir.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_dirinfo.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_dirread.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_dirwrite.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_dumpmode.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_error.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_extension.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_fax3.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_fax3sm.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_flush.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_getimage.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_jbig.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_jpeg.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_luv.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_lzw.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_next.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_ojpeg.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_open.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_packbits.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_pixarlog.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_predict.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_print.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_read.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_strip.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_swab.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_thunder.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_tile.c
    # ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_unix.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_version.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_warning.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_write.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/tiff/tif_zip.c
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/tif_xfile.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximabmp.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximadsp.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximaenc.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximaexif.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximage.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximagif.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximahist.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximaico.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximainfo.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximaint.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximajas.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximajbg.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximajpg.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximalpha.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximalyr.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximamng.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximapal.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximapcx.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximapng.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximapsd.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximaraw.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximasel.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximaska.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximatga.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximath.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximatif.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximatran.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximawbmp.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximawmf.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/ximawnd.cpp
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/CxImage/xmemfile.cpp

    # !disable_cximage_all {
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_cm.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_debug.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_getopt.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_icc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_iccdata.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_image.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_init.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_malloc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_seq.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_stream.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_string.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_tvp.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/base/jas_version.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/bmp/bmp_cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/bmp/bmp_dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/bmp/bmp_enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jp2/jp2_cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jp2/jp2_dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jp2/jp2_enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_bs.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_cs.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_math.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_mct.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_mqcod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_mqdec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_mqenc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_qmfb.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_t1cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_t1dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_t1enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_t2cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_t2dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_t2enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_tagtree.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_tsfb.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpc/jpc_util.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpg/jpg_dummy.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/jpg/jpg_val.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/mif/mif_cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/pgx/pgx_cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/pgx/pgx_dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/pgx/pgx_enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/pnm/pnm_cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/pnm/pnm_dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/pnm/pnm_enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/ras/ras_cod.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/ras/ras_dec.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/ras/ras_enc.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jbig/jbig_tab.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jbig/jbig.c
        ${DESKTOP_EDITOR_ROOT_DIR}/cximage/raw/libdcr.c
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/Encoder/jbig2arith.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/Encoder/jbig2enc.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/Encoder/jbig2sym.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/JBig2File.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/boxbasic.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/ccbord.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/dwacomb.2.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/dwacomblow.2.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/fhmtgen.1.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/fliphmtgen.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/fmorphauto.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/fmorphgen.1.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/numabasic.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/pix5.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/pixabasic.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/pixafunc1.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/pixcomp.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/ptabasic.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/ptra.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/ropiplow.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/roplow.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/rotateam.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/rotateshear.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/sarray.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/sel1.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/sel2.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/JBig2/source/LeptonLib/skew.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/Jp2/J2kFile.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/Jp2/Reader.cpp
        ${DESKTOP_EDITOR_ROOT_DIR}/raster/PICT/PICFile.cpp
        ${GRAPHICS_ROOT_DIR}/pro/lepton_lib_all.cpp
        ${GRAPHICS_ROOT_DIR}/pro/libpsd_pri.c
        ${GRAPHICS_ROOT_DIR}/pro/libpsd_pri2.c
        ${GRAPHICS_ROOT_DIR}/pro/libpsd_pri3.c
    #}

    # !config_zlip_image {
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/crc32.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/adler32.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/deflate.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/inffast.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/inflate.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/inftrees.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/trees.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/zutil.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/uncompr.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/compress.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib_addon.c
    # }

    ${DESKTOP_EDITOR_ROOT_DIR}/graphics/Image.h
	${DESKTOP_EDITOR_ROOT_DIR}/raster/BgraFrame.h
	${DESKTOP_EDITOR_ROOT_DIR}/raster/ImageFileFormatChecker.h

    # metafile.pri

    # !metafile_disable_wmf_emf {
        ${METAFILE_SOURCER_DIR}/Common/CPathConverter.cpp
        ${METAFILE_SOURCER_DIR}/Common/CPath.cpp
        ${METAFILE_SOURCER_DIR}/Common/CClip.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretator.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorArray.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorRender.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorSvg.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfParser.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfParserBase.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfPlusParser.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfObjects.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfPlusObjects.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfPlayer.cpp
        ${METAFILE_SOURCER_DIR}/Emf/EmfFile.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfObjects.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfPlayer.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CInterpretatorSvgBase.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretatorSvg.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretatorRender.cpp
        # ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretator.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/cwmfinterpretator.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfParser/CWmfParser.cpp
        ${METAFILE_SOURCER_DIR}/Wmf/WmfParser/CWmfParserBase.cpp

        ${METAFILE_SOURCER_DIR}/Common/CPathConverter.h
        ${METAFILE_SOURCER_DIR}/Common/CPath.h
        ${METAFILE_SOURCER_DIR}/Common/CClip.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretator.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorArray.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorBase.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorRender.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorSvg.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfParser.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfParserBase.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfPlusParser.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfTypes.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfObjects.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfPlusObjects.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfPlayer.h
        ${METAFILE_SOURCER_DIR}/Emf/EmfFile.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfObjects.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfPlayer.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfTypes.h
        # ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretator.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/cwmfinterpretator.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretatorBase.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CInterpretatorSvgBase.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretatorSvg.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfInterpretator/CWmfInterpretatorRender.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfParser/CWmfParser.h
        ${METAFILE_SOURCER_DIR}/Wmf/WmfParser/CWmfParserBase.h

        # !metafile_disable_wmf_emf_xml {
            ${METAFILE_SOURCER_DIR}/CXmlOutput.cpp
            ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorXml.cpp
            ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfxParser.cpp

            ${METAFILE_SOURCER_DIR}/CXmlOutput.h
            ${METAFILE_SOURCER_DIR}/Emf/EmfInterpretator/CEmfInterpretatorXml.h
            ${METAFILE_SOURCER_DIR}/Emf/EmfParser/CEmfxParser.h
        # }
    # }

    # !metafile_disable_svg {
        ${METAFILE_SOURCER_DIR}/svg/CSvgFile.cpp
        ${METAFILE_SOURCER_DIR}/svg/CSvgParser.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgReader.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CContainer.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CGradient.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CClipPath.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CMask.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CMarker.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CPattern.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CSymbol.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CSwitch.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CImage.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CLine.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CRect.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CCircle.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CEllipse.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CPath.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CText.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CUse.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CPolyline.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CFont.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CObjectBase.cpp
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CStyle.cpp

        ${METAFILE_SOURCER_DIR}/svg/SvgTypes.h
        ${METAFILE_SOURCER_DIR}/svg/CSvgFile.h
        ${METAFILE_SOURCER_DIR}/svg/CSvgParser.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CContainer.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CGradient.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CClipPath.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CMask.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CPattern.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CSymbol.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CSwitch.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CMarker.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CImage.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CLine.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CRect.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CCircle.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CEllipse.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CPath.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CText.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CUse.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CPolyline.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CFont.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CStyle.h
        ${METAFILE_SOURCER_DIR}/svg/SvgObjects/CObjectBase.h
        ${METAFILE_SOURCER_DIR}/svg/SvgReader.h
        ${METAFILE_SOURCER_DIR}/svg/SvgUtils.h
    # }

    # CssCalculator.pri
    # css_calculator_without_xhtml {
        ${CSS_ROOT_DIR}/src/CCssCalculator_Private.cpp
		${CSS_ROOT_DIR}/src/CElement.cpp
		${CSS_ROOT_DIR}/src/CNode.cpp
		${CSS_ROOT_DIR}/src/ConstValues.cpp
		${CSS_ROOT_DIR}/src/StaticFunctions.cpp
		${CSS_ROOT_DIR}/src/StyleProperties.cpp
		${CSS_ROOT_DIR}/src/CUnitMeasureConverter.cpp    

        ${CSS_ROOT_DIR}/src/CCssCalculator_Private.h
		${CSS_ROOT_DIR}/src/CElement.h
		${CSS_ROOT_DIR}/src/CNode.h
		${CSS_ROOT_DIR}/src/ConstValues.h
		${CSS_ROOT_DIR}/src/StaticFunctions.h
		${CSS_ROOT_DIR}/src/StyleProperties.h
		${CSS_ROOT_DIR}/src/CUnitMeasureConverter.h
    # }

    # katana.pri
    ${KATANA_INSTALL_DIR_ABS}/src/foundation.c
    ${KATANA_INSTALL_DIR_ABS}/src/katana.lex.c
    ${KATANA_INSTALL_DIR_ABS}/src/katana.tab.c
    ${KATANA_INSTALL_DIR_ABS}/src/parser.c
    ${KATANA_INSTALL_DIR_ABS}/src/selector.c
    ${KATANA_INSTALL_DIR_ABS}/src/tokenizer.c

    ${KATANA_INSTALL_DIR_ABS}/src/foundation.h
    ${KATANA_INSTALL_DIR_ABS}/src/katana.h
    ${KATANA_INSTALL_DIR_ABS}/src/katana.lex.h
    ${KATANA_INSTALL_DIR_ABS}/src/katana.tab.h
    ${KATANA_INSTALL_DIR_ABS}/src/parser.h
    ${KATANA_INSTALL_DIR_ABS}/src/selector.h
    ${KATANA_INSTALL_DIR_ABS}/src/tokenizer.h


    # freetype.pri
    # !config_zlip_image {
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib_addon.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/adler32.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/compress.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/crc32.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/deflate.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/inffast.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/inflate.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/inftrees.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/trees.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/uncompr.c
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11/zutil.c
    # }

    ${FREETYPE_SOURCES_DIR}/src/autofit/autofit.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftbase.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftbbox.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftbdf.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftbitmap.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftcid.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftdebug.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftfstype.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftgasp.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftglyph.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftgxval.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftinit.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftmm.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftotval.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftpatent.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftpfr.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftstroke.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftsynth.c
    ${FREETYPE_SOURCES_DIR}/src/base/fttype1.c
    ${FREETYPE_SOURCES_DIR}/src/base/ftwinfnt.c
    ${FREETYPE_SOURCES_DIR}/src/bdf/bdf.c
    ${FREETYPE_SOURCES_DIR}/src/bzip2/ftbzip2.c
    ${FREETYPE_SOURCES_DIR}/src/cache/ftcache.c
    ${FREETYPE_SOURCES_DIR}/src/cff/cff.c
    ${FREETYPE_SOURCES_DIR}/src/cid/type1cid.c
    ${FREETYPE_SOURCES_DIR}/src/gzip/ftgzip.c
    ${FREETYPE_SOURCES_DIR}/src/lzw/ftlzw.c
    ${FREETYPE_SOURCES_DIR}/src/pcf/pcf.c
    ${FREETYPE_SOURCES_DIR}/src/pfr/pfr.c
    ${FREETYPE_SOURCES_DIR}/src/psaux/psaux.c
    ${FREETYPE_SOURCES_DIR}/src/pshinter/pshinter.c
    ${FREETYPE_SOURCES_DIR}/src/psnames/psnames.c
    ${FREETYPE_SOURCES_DIR}/src/raster/raster.c
    ${FREETYPE_SOURCES_DIR}/src/sfnt/sfnt.c
    ${FREETYPE_SOURCES_DIR}/src/smooth/smooth.c
    ${FREETYPE_SOURCES_DIR}/src/truetype/truetype.c
    ${FREETYPE_SOURCES_DIR}/src/type1/type1.c
    ${FREETYPE_SOURCES_DIR}/src/type42/type42.c
    ${FREETYPE_SOURCES_DIR}/src/winfonts/winfnt.c
 
    # fontengine.pri
	${FONT_ENGINE_SOURCES_DIR}/fontconverter/FontConverter.cpp
	${FONT_ENGINE_SOURCES_DIR}/fontconverter/FontFileEncodings.cpp
	${FONT_ENGINE_SOURCES_DIR}/fontconverter/FontFileTrueType.cpp
	${FONT_ENGINE_SOURCES_DIR}/fontconverter/FontFileType1.cpp
	${FONT_ENGINE_SOURCES_DIR}/fontconverter/FontFileType1C.cpp
	${FONT_ENGINE_SOURCES_DIR}/fontconverter/Hash.cpp
    ${FONT_ENGINE_SOURCES_DIR}/ApplicationFonts.cpp
    ${FONT_ENGINE_SOURCES_DIR}/ApplicationFontsWorker.cpp
    ${FONT_ENGINE_SOURCES_DIR}/fontconverter/StringExt.cpp
    ${FONT_ENGINE_SOURCES_DIR}/FontFile.cpp
    ${FONT_ENGINE_SOURCES_DIR}/FontManager.cpp
    ${FONT_ENGINE_SOURCES_DIR}/FontPath.cpp
    ${FONT_ENGINE_SOURCES_DIR}/GlyphString.cpp
    ${FONT_ENGINE_SOURCES_DIR}/TextHyphen.cpp
    ${FONT_ENGINE_SOURCES_DIR}/TextShaper.cpp
    ${GRAPHICS_ROOT_DIR}/pro/pro_Fonts.cpp

    ${FONT_ENGINE_SOURCES_DIR}/ApplicationFonts.h
    ${FONT_ENGINE_SOURCES_DIR}/ApplicationFontsWorker.h
    ${FONT_ENGINE_SOURCES_DIR}/FontConverter.h
    ${FONT_ENGINE_SOURCES_DIR}/FontFile.h
    ${FONT_ENGINE_SOURCES_DIR}/FontManager.h
    ${FONT_ENGINE_SOURCES_DIR}/FontPath.h
    ${FONT_ENGINE_SOURCES_DIR}/GlyphString.h
    ${FONT_ENGINE_SOURCES_DIR}/languages.h
    ${FONT_ENGINE_SOURCES_DIR}/TextHyphen.h
    ${FONT_ENGINE_SOURCES_DIR}/TextShaper.h
    ${GRAPHICS_ROOT_DIR}/pro/Fonts.h

    # deprecated!!! remove after 6.5 ------------------
    # I have doubts, current version is 9.1.0 and it's still here...
    ${FONT_ENGINE_SOURCES_DIR}/FontsAssistant.h
    ${FONT_ENGINE_SOURCES_DIR}/FontsAssistant.cpp

    # harfbuzz.pri
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-map.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-blob.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer-serialize.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer-verify.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cairo-utils.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cairo.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-common.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-coretext.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-directwrite.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-draw.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-face-builder.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-face.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-fallback-shape.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-font.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ft.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-gdi.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-glib.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-gobject-structs.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-graphite2.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-icu.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-map.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-number.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cff1-table.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cff2-table.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-color.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-face.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-font.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-map.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-math.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-meta.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-metrics.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-name.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape-fallback.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape-normalize.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-default.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-hangul.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-hebrew.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-indic-table.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-indic.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-khmer.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-myanmar.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-syllabic.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-thai.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-use.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-vowel-constraints.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-tag.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-outline.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-paint-extents.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-paint.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-set.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shape-plan.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shape.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shaper.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-static.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-style.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-cff-common.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-cff1.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-cff2.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-input.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-instancer-solver.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-plan.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-repacker.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ucd.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-unicode.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-uniscribe.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-shape.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-blob.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cairo.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-common.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-coretext.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-deprecated.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-directwrite.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-draw.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-face.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-font.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ft.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-gdi.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-glib.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-gobject-structs.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-gobject.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-graphite2.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-icu.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-map.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-color.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-deprecated.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-font.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-math.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-meta.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-metrics.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-name.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-paint.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-set.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shape-plan.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shape.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-style.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-repacker.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-unicode.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-uniscribe.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-version.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb.h
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-ankr-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-bsln-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-feat-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-just-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-kerx-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-morx-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-opbd-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout-trak-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-layout.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-ltag-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-aat-map.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-algs.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-array.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-atomic.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-bimap.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-bit-page.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-bit-set-invertible.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-bit-set.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-blob.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer-deserialize-json.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer-deserialize-text-glyphs.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer-deserialize-text-unicode.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-buffer.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cache.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cairo-utils.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cff-interp-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cff-interp-cs-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cff-interp-dict-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cff1-interp-cs.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cff2-interp-cs.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-config.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-cplusplus.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-debug.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-dispatch.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-draw.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-face.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-font.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ft-colr.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-iter.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-kern.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-limits.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-machinery.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-map.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-meta.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ms-feature-ranges.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-multimap.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-mutex.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-null.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-number-parser.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-number.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-object.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-open-file.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-open-type.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cff-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cff1-std-str.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cff1-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cff2-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-cmap-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-face-table-list.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-face.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-gasp-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-glyf-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-hdmx-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-head-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-hhea-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-hmtx-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-kern-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-base-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-gdef-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-gpos-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-gsub-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-gsubgpos.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout-jstf-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-layout.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-map.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-math-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-maxp-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-meta-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-metrics.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-name-language-static.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-name-language.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-name-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-os2-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-os2-unicode-ranges.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-post-macroman.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-post-table-v2subset.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-post-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape-fallback.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape-normalize.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shape.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic-fallback.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic-joining-list.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic-pua.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic-win1256.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-arabic.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-indic-machine.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-indic.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-khmer-machine.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-myanmar-machine.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-syllabic.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-use-machine.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-use-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper-vowel-constraints.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-shaper.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-stat-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-tag-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-avar-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-cvar-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-fvar-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-gvar-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-hvar-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-var-mvar-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ot-vorg-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-outline.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-paint-extents.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-paint.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-pool.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-priority-queue.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-repacker.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-sanitize.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-serialize.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-set-digest.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-set.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shape-plan.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shaper-impl.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shaper-list.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-shaper.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-string-array.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-accelerator.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-cff-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-input.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-instancer-solver.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-plan-member-list.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset-plan.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-subset.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-ucd-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-unicode-emoji-table.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-unicode.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-utf.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-vector.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-blob.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-buffer.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-common.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-face.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-font.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-list.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api-shape.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb-wasm-api.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/hb.hh

    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/gsubgpos-context.cc
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/gsubgpos-context.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/classdef-graph.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/coverage-graph.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/graph.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/gsubgpos-graph.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/markbasepos-graph.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/pairpos-graph.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/serialize.hh
    ${HARFBUZZ_INSTALL_DIR_ABS}/src/graph/split-helpers.hh

    # brotli.pri
    ${BROTLI_INSTALL_DIR_ABS}/c/common/constants.c
    ${BROTLI_INSTALL_DIR_ABS}/c/common/context.c
    ${BROTLI_INSTALL_DIR_ABS}/c/common/dictionary.c
    ${BROTLI_INSTALL_DIR_ABS}/c/common/platform.c
    ${BROTLI_INSTALL_DIR_ABS}/c/common/shared_dictionary.c
    ${BROTLI_INSTALL_DIR_ABS}/c/common/transform.c
    ${BROTLI_INSTALL_DIR_ABS}/c/dec/bit_reader.c
    ${BROTLI_INSTALL_DIR_ABS}/c/dec/decode.c
    ${BROTLI_INSTALL_DIR_ABS}/c/dec/huffman.c
    # ${BROTLI_INSTALL_DIR_ABS}/c/dec/prefix.c
    ${BROTLI_INSTALL_DIR_ABS}/c/dec/state.c
    # ${BROTLI_INSTALL_DIR_ABS}/c/dec/static_init.c
)

set_default_options(graphics)

if (WIN32)
    target_sources(graphics PRIVATE ${FREETYPE_SOURCES_DIR}/src/base/ftsystem.c) # freetype.pri
else()
    target_sources(graphics PRIVATE ${FREETYPE_SOURCES_DIR}/builds/unix/ftsystem.c) # freetype.pri
endif()

target_compile_definitions(graphics PRIVATE
    GRAPHICS_USE_DYNAMIC_LIBRARY_BUILDING
    DISABLE_IMAGE_EXCEPTIONS
    EXCLUDE_JPG_SUPPORT
	MNG_SUPPORT_DISPLAY
	MNG_SUPPORT_READ
	MNG_SUPPORT_WRITE
	MNG_ACCESS_CHUNKS
	MNG_STORE_CHUNKS
	MNG_ERROR_TELLTALE

    # metafile.pri
    METAFILE_SUPPORT_WMF_EMF # !metafile_disable_wmf_emf
    METAFILE_SUPPORT_WMF_EMF_XML # !metafile_disable_wmf_emf_xml
    METAFILE_SUPPORT_SVG # !metafile_disable_svg

    # freetype.pri
    FT_CONFIG_OPTION_SYSTEM_ZLIB
    FT2_BUILD_LIBRARY

    # textshaper.pri
    SUPPORT_HARFBUZZ_SHAPER

    # harfbuzz.pri
    HAVE_FREETYPE
    HB_NO_VISIBILITY

    _lseek=lseek

    # brotli.pri
    FT_CONFIG_OPTION_USE_BROTLI
)

if(LINUX)
    target_compile_definitions(graphics PRIVATE
        HAVE_UNISTD_H
        HAVE_FCNTL_H
        _LINUX
    )
endif()

if( MSVC )
    target_compile_definitions(graphics PRIVATE
        JAS_WIN_MSVC_BUILD
        DLL_EXPORT # freetype dll export
        WIN32_LEAN_AND_MEAN
    )
endif()

target_include_directories(graphics PRIVATE
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}
    ${KATANA_INSTALL_DIR_ABS}/src
	${DESKTOP_EDITOR_ROOT_DIR}/agg-2.4/include
    ${DESKTOP_EDITOR_ROOT_DIR}/cximage/jasper/include
	${DESKTOP_EDITOR_ROOT_DIR}/cximage/jpeg
	${DESKTOP_EDITOR_ROOT_DIR}/cximage/png
    ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11 # !config_zlip_image
    ${OFFICE_UTILS_ROOT_DIR}/src # !config_zlip_image

    # freetype.pri
    ${FREETYPE_SOURCES_DIR}/include
    ${FREETYPE_SOURCES_DIR}/include/freetype
    # !config_zlip_image {
        ${OFFICE_UTILS_ROOT_DIR}/src/zlib-1.2.11
        ${OFFICE_UTILS_ROOT_DIR}/src
    # }

    # harfbuzz.pri
    ${HARFBUZZ_INSTALL_DIR_ABS}
    ${HARFBUZZ_INSTALL_DIR_ABS}/src

    # brotli.pri
    ${BROTLI_INSTALL_DIR_ABS}/c/include
)

if( MSVC )
    target_include_directories(graphics PRIVATE
        ${KATANA_INSTALL_DIR_ABS}/visualc/include
    )
endif()

target_precompile_headers(graphics PRIVATE
    ${CORE_ROOT_DIR}/msvc_fix.h
)

if(LINUX)
    target_compile_options(graphics PRIVATE
        -Wno-narrowing
        -UUNICODE
        -U_UNICODE
        -fpermissive
        -UHAVE_IO_H
    )

    # Re-enable exporting symbols
    target_compile_options(graphics PRIVATE
        -fvisibility=default
        -fvisibility-inlines-hidden
    )
endif()

# dynamic libs
target_link_libraries(graphics PUBLIC
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time    
    kernel
    UnicodeConverter
)

if(WIN32)
    target_link_libraries(graphics PUBLIC
        Advapi32
        Shell32
        User32
    )
endif()

copy_artifacts_to_folder("graphics" "${EO_CORE_OUTPUT_DIR}")

declare_victory( graphics )
