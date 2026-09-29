cmake_minimum_required(VERSION 3.20)
project(drawingfile)

# -------------------------------------------------
# Ensure Emscripten
# -------------------------------------------------
if(NOT EMSCRIPTEN)
    message(FATAL_ERROR "This project must be built with Emscripten (use emcmake).")
endif()

set(CORE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)
set(DESKTOP_ROOT ${CORE_ROOT}/DesktopEditor)

include(${CORE_ROOT}/common.cmake)

# -------------------------------------------------
# Source files
# (generated from compile_files_array)
# -------------------------------------------------
set(SOURCES

    ${DESKTOP_ROOT}/raster/BgraFrame.cpp
    ${DESKTOP_ROOT}/raster/ImageFileFormatChecker.cpp
    ${DESKTOP_ROOT}/raster/PICT/PICFile.cpp

    ${DESKTOP_ROOT}/cximage/CxImage/ximaenc.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximaexif.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximage.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximainfo.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximajpg.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximalpha.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximapal.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximasel.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/xmemfile.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximapng.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximabmp.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximatran.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximatif.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/tif_xfile.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximajas.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximagif.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximaico.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximatga.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximapcx.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximawbmp.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximamng.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximapsd.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximaska.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximaraw.cpp
    ${DESKTOP_ROOT}/cximage/CxImage/ximaint.cpp

    ${DESKTOP_ROOT}/cximage/jpeg/jerror.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdmarker.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdapimin.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdmaster.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdapistd.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcomapi.c
    ${DESKTOP_ROOT}/cximage/jpeg/jutils.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdinput.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdmainct.c
    ${DESKTOP_ROOT}/cximage/jpeg/jmemmgr.c
    ${DESKTOP_ROOT}/cximage/jpeg/jquant1.c
    ${DESKTOP_ROOT}/cximage/jpeg/jquant2.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdmerge.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdcolor.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdsample.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdpostct.c
    ${DESKTOP_ROOT}/cximage/jpeg/jddctmgr.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdarith.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdhuff.c
    ${DESKTOP_ROOT}/cximage/jpeg/jdcoefct.c
    ${DESKTOP_ROOT}/cximage/jpeg/jmemnobs.c
    ${DESKTOP_ROOT}/cximage/jpeg/jidctint.c
    ${DESKTOP_ROOT}/cximage/jpeg/jidctfst.c
    ${DESKTOP_ROOT}/cximage/jpeg/jidctflt.c
    ${DESKTOP_ROOT}/cximage/jpeg/jaricom.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcapimin.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcparam.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcapistd.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcinit.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcmaster.c
    ${DESKTOP_ROOT}/cximage/jpeg/jccolor.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcmarker.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcsample.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcprepct.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcdctmgr.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcarith.c
    ${DESKTOP_ROOT}/cximage/jpeg/jchuff.c
    ${DESKTOP_ROOT}/cximage/jpeg/jccoefct.c
    ${DESKTOP_ROOT}/cximage/jpeg/jcmainct.c
    ${DESKTOP_ROOT}/cximage/jpeg/jfdctint.c
    ${DESKTOP_ROOT}/cximage/jpeg/jfdctfst.c
    ${DESKTOP_ROOT}/cximage/jpeg/jfdctflt.c

    ${DESKTOP_ROOT}/cximage/png/pngread.c
    ${DESKTOP_ROOT}/cximage/png/pngmem.c
    ${DESKTOP_ROOT}/cximage/png/pngerror.c
    ${DESKTOP_ROOT}/cximage/png/png.c
    ${DESKTOP_ROOT}/cximage/png/pngrio.c
    ${DESKTOP_ROOT}/cximage/png/pngtrans.c
    ${DESKTOP_ROOT}/cximage/png/pngget.c
    ${DESKTOP_ROOT}/cximage/png/pngrutil.c
    ${DESKTOP_ROOT}/cximage/png/pngrtran.c
    ${DESKTOP_ROOT}/cximage/png/pngset.c
    ${DESKTOP_ROOT}/cximage/png/pngwrite.c
    ${DESKTOP_ROOT}/cximage/png/pngwio.c
    ${DESKTOP_ROOT}/cximage/png/pngwutil.c
    ${DESKTOP_ROOT}/cximage/png/pngwtran.c

    ${DESKTOP_ROOT}/cximage/tiff/tif_close.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_dir.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_aux.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_getimage.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_strip.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_open.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_tile.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_error.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_read.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_flush.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_dirinfo.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_compress.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_warning.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_swab.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_color.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_dirread.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_write.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_codec.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_luv.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_dirwrite.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_dumpmode.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_fax3.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_ojpeg.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_jpeg.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_next.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_thunder.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_packbits.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_lzw.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_zip.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_fax3sm.c
    ${DESKTOP_ROOT}/cximage/tiff/tif_predict.c

    ${DESKTOP_ROOT}/cximage/jasper/base/jas_init.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_stream.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_malloc.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_image.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_cm.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_seq.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_string.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_icc.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_debug.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_iccdata.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_tvp.c
    ${DESKTOP_ROOT}/cximage/jasper/base/jas_version.c
    ${DESKTOP_ROOT}/cximage/jasper/mif/mif_cod.c
    ${DESKTOP_ROOT}/cximage/jasper/pnm/pnm_dec.c
    ${DESKTOP_ROOT}/cximage/jasper/pnm/pnm_enc.c
    ${DESKTOP_ROOT}/cximage/jasper/pnm/pnm_cod.c
    ${DESKTOP_ROOT}/cximage/jasper/bmp/bmp_dec.c
    ${DESKTOP_ROOT}/cximage/jasper/bmp/bmp_enc.c
    ${DESKTOP_ROOT}/cximage/jasper/bmp/bmp_cod.c
    ${DESKTOP_ROOT}/cximage/jasper/ras/ras_dec.c
    ${DESKTOP_ROOT}/cximage/jasper/ras/ras_enc.c
    ${DESKTOP_ROOT}/cximage/jasper/jp2/jp2_dec.c
    ${DESKTOP_ROOT}/cximage/jasper/jp2/jp2_enc.c
    ${DESKTOP_ROOT}/cximage/jasper/jp2/jp2_cod.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_cs.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_enc.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_dec.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_t1cod.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_math.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_util.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_tsfb.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_mct.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_t1enc.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_t1dec.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_bs.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_t2cod.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_t2enc.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_t2dec.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_tagtree.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_mqenc.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_mqdec.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_mqcod.c
    ${DESKTOP_ROOT}/cximage/jasper/jpc/jpc_qmfb.c
    ${DESKTOP_ROOT}/cximage/jasper/jpg/jpg_val.c
    ${DESKTOP_ROOT}/cximage/jasper/jpg/jpg_dummy.c
    ${DESKTOP_ROOT}/cximage/jasper/pgx/pgx_dec.c
    ${DESKTOP_ROOT}/cximage/jasper/pgx/pgx_enc.c

    ${DESKTOP_ROOT}/raster/Jp2/J2kFile.cpp
    ${DESKTOP_ROOT}/raster/Jp2/Reader.cpp

    ${DESKTOP_ROOT}/cximage/mng/libmng_hlapi.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_callback_xs.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_prop_xs.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_object_prc.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_zlib.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_jpeg.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_pixels.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_read.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_error.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_display.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_write.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_chunk_io.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_cms.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_filter.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_chunk_prc.c
    ${DESKTOP_ROOT}/cximage/mng/libmng_chunk_xs.c

    ${DESKTOP_ROOT}/cximage/libpsd/psd.c
    ${DESKTOP_ROOT}/cximage/libpsd/file_header.c
    ${DESKTOP_ROOT}/cximage/libpsd/color_mode.c
    ${DESKTOP_ROOT}/cximage/libpsd/image_resource.c
    ${DESKTOP_ROOT}/cximage/libpsd/blend.c
    ${DESKTOP_ROOT}/cximage/libpsd/layer_mask.c
    ${DESKTOP_ROOT}/cximage/libpsd/image_data.c
    ${DESKTOP_ROOT}/cximage/libpsd/stream.c
    ${DESKTOP_ROOT}/cximage/libpsd/psd_system.c
    ${DESKTOP_ROOT}/cximage/libpsd/color.c
    ${DESKTOP_ROOT}/cximage/libpsd/pattern_fill.c
    ${DESKTOP_ROOT}/cximage/libpsd/color_balance.c
    ${DESKTOP_ROOT}/cximage/libpsd/channel_image.c
    ${DESKTOP_ROOT}/cximage/libpsd/gradient_fill.c
    ${DESKTOP_ROOT}/cximage/libpsd/invert.c
    ${DESKTOP_ROOT}/cximage/libpsd/posterize.c
    ${DESKTOP_ROOT}/cximage/libpsd/brightness_contrast.c
    ${DESKTOP_ROOT}/cximage/libpsd/solid_color.c
    ${DESKTOP_ROOT}/cximage/libpsd/threshold.c
    ${DESKTOP_ROOT}/cximage/libpsd/effects.c
    ${DESKTOP_ROOT}/cximage/libpsd/selective_color.c
    ${DESKTOP_ROOT}/cximage/libpsd/channel_mixer.c
    ${DESKTOP_ROOT}/cximage/libpsd/photo_filter.c
    ${DESKTOP_ROOT}/cximage/libpsd/type_tool.c
    ${DESKTOP_ROOT}/cximage/libpsd/gradient_map.c
    ${DESKTOP_ROOT}/cximage/libpsd/hue_saturation.c
    ${DESKTOP_ROOT}/cximage/libpsd/levels.c
    ${DESKTOP_ROOT}/cximage/libpsd/curves.c
    ${DESKTOP_ROOT}/cximage/libpsd/pattern.c
    ${DESKTOP_ROOT}/cximage/libpsd/psd_zip.c
    ${DESKTOP_ROOT}/cximage/libpsd/descriptor.c
    ${DESKTOP_ROOT}/cximage/libpsd/drop_shadow.c
    ${DESKTOP_ROOT}/cximage/libpsd/inner_shadow.c
    ${DESKTOP_ROOT}/cximage/libpsd/color_overlay.c
    ${DESKTOP_ROOT}/cximage/libpsd/outer_glow.c
    ${DESKTOP_ROOT}/cximage/libpsd/inner_glow.c
    ${DESKTOP_ROOT}/cximage/libpsd/bevel_emboss.c
    ${DESKTOP_ROOT}/cximage/libpsd/satin.c
    ${DESKTOP_ROOT}/cximage/libpsd/gradient_overlay.c
    ${DESKTOP_ROOT}/cximage/libpsd/stroke.c
    ${DESKTOP_ROOT}/cximage/libpsd/pattern_overlay.c

    ${DESKTOP_ROOT}/cximage/raw/libdcr.c

    ${DESKTOP_ROOT}/raster/JBig2/source/JBig2File.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/Encoder/jbig2enc.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/Encoder/jbig2arith.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/Encoder/jbig2sym.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pixconv.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/writefile.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/scale.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pix1.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pix2.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pix3.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pix4.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pix5.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/grayquant.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/grayquantlow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/seedfill.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/jbclass.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pixabasic.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/numabasic.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/morphseq.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/binexpandlow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/ptabasic.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/rop.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/colormap.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pngiostub.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/lepton_utils.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/scalelow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/enhance.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/jpegio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/jpegiostub.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/spixio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/webpio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/webpiostub.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/psio2.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/gifio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/gifiostub.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pnmio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/tiffio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/tiffiostub.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/bmpio.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/binexpand.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/compare.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/boxbasic.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/conncomp.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pixafunc1.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/boxfunc1.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/ptafunc1.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/binreduce.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/seedfilllow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/sel1.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/morphapp.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/correlscore.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/sarray.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/morph.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/roplow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/fpix1.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/stack.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pixacc.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/pixarith.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/convolve.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/binreducelow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/convolvelow.cpp
    ${DESKTOP_ROOT}/raster/JBig2/source/LeptonLib/arithlow.cpp

    ${DESKTOP_ROOT}/graphics/GraphicsRenderer.cpp
    ${DESKTOP_ROOT}/graphics/pro/pro_Graphics.cpp
    ${DESKTOP_ROOT}/graphics/pro/pro_Fonts.cpp
    ${DESKTOP_ROOT}/graphics/pro/pro_Image.cpp
    ${DESKTOP_ROOT}/graphics/Graphics.cpp
    ${DESKTOP_ROOT}/graphics/Brush.cpp
    ${DESKTOP_ROOT}/graphics/BaseThread.cpp
    ${DESKTOP_ROOT}/graphics/GraphicsPath.cpp
    ${DESKTOP_ROOT}/graphics/BooleanOperations.cpp
    ${DESKTOP_ROOT}/graphics/Image.cpp
    ${DESKTOP_ROOT}/graphics/Matrix.cpp
    ${DESKTOP_ROOT}/graphics/Clip.cpp
    ${DESKTOP_ROOT}/graphics/TemporaryCS.cpp
    ${DESKTOP_ROOT}/graphics/AlphaMask.cpp
    ${DESKTOP_ROOT}/graphics/GraphicsLayer.cpp
    ${DESKTOP_ROOT}/graphics/commands/DocInfo.cpp
    ${DESKTOP_ROOT}/graphics/commands/AnnotField.cpp
    ${DESKTOP_ROOT}/graphics/commands/FormField.cpp
    ${DESKTOP_ROOT}/graphics/MetafileToRenderer.cpp
    ${DESKTOP_ROOT}/graphics/MetafileToRendererReader.cpp

    ${DESKTOP_ROOT}/fontengine/GlyphString.cpp
    ${DESKTOP_ROOT}/fontengine/FontManager.cpp
    ${DESKTOP_ROOT}/fontengine/FontFile.cpp
    ${DESKTOP_ROOT}/fontengine/FontPath.cpp
    ${DESKTOP_ROOT}/fontengine/ApplicationFonts.cpp

    ${DESKTOP_ROOT}/agg-2.4/src/agg_arc.cpp
    ${DESKTOP_ROOT}/agg-2.4/src/agg_vcgen_stroke.cpp
    ${DESKTOP_ROOT}/agg-2.4/src/agg_vcgen_dash.cpp
    ${DESKTOP_ROOT}/agg-2.4/src/agg_trans_affine.cpp
    ${DESKTOP_ROOT}/agg-2.4/src/agg_curves.cpp
    ${DESKTOP_ROOT}/agg-2.4/src/agg_image_filters.cpp
    ${DESKTOP_ROOT}/agg-2.4/src/agg_bezier_arc.cpp

    ${DESKTOP_ROOT}/common/File.cpp
    ${DESKTOP_ROOT}/common/Directory.cpp
    ${DESKTOP_ROOT}/common/ByteBuilder.cpp
    ${DESKTOP_ROOT}/common/Base64.cpp
    ${DESKTOP_ROOT}/common/StringExt.cpp
    ${DESKTOP_ROOT}/common/Path.cpp
    ${DESKTOP_ROOT}/common/SystemUtils.cpp
    ${DESKTOP_ROOT}/common/StringUTF32.cpp
    ${DESKTOP_ROOT}/common/StringBuilder.cpp

    ${CORE_ROOT}/Common/3dParty/cryptopp/cryptlib.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/cpu.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/integer.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/3way.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/adler32.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/algebra.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/algparam.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/allocate.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/arc4.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/aria.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/aria_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/ariatab.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/asn.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/authenc.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/base32.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/base64.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/basecode.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/bfinit.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/blake2.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/blake2s_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/blake2b_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/blowfish.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/blumshub.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/camellia.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/cast.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/casts.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/cbcmac.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/ccm.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/chacha.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/chacha_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/chacha_avx.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/chachapoly.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/cham.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/cham_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/channels.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/cmac.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/crc.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/crc_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/darn.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/default.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/des.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/dessp.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/dh.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/dh2.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/dll.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/donna_32.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/donna_64.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/donna_sse.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/dsa.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/eax.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/ec2n.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/ecp.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/eccrypto.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/eprecomp.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/elgamal.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/emsa2.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/esign.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/files.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/filters.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/fips140.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gcm.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gcm_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gf256.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gf2_32.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gf2n.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gf2n_simd.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gfpcrypt.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gost.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/gzip.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/hc128.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/hc256.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/hex.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/hight.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/hmac.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/hrtimer.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/ida.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/idea.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/iterhash.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/kalyna.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/md5.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/randpool.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/osrng.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/rijndael.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/modes.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/misc.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/rdtables.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/sha.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/mqueue.cpp
    ${CORE_ROOT}/Common/3dParty/cryptopp/queue.cpp

    ${CORE_ROOT}/OfficeUtils/src/OfficeUtils.cpp
    ${CORE_ROOT}/OfficeUtils/src/ZipBuffer.cpp
    ${CORE_ROOT}/OfficeUtils/src/ZipUtilsCP.cpp
    ${CORE_ROOT}/OfficeUtils/src/zlib_addon.c

    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/ioapi.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/miniunz.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/minizip.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/mztools.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/unzip.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/zip.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip/ioapibuf.c

    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/adler32.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/crc32.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/deflate.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/infback.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/inffast.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/inflate.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/inftrees.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/trees.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/zutil.c
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/compress.c

    ${CORE_ROOT}/PdfFile/PdfFile.cpp
    ${CORE_ROOT}/PdfFile/PdfReader.cpp
    ${CORE_ROOT}/PdfFile/PdfWriter.cpp
    ${CORE_ROOT}/PdfFile/PdfEditor.cpp
    ${CORE_ROOT}/PdfFile/OnlineOfficeBinToPdf.cpp

    ${CORE_ROOT}/PdfFile/SrcReader/Adaptors.cpp
    ${CORE_ROOT}/PdfFile/SrcReader/GfxClip.cpp
    ${CORE_ROOT}/PdfFile/SrcReader/RendererOutputDev.cpp
    ${CORE_ROOT}/PdfFile/SrcReader/JPXStream2.cpp
    ${CORE_ROOT}/PdfFile/SrcReader/PdfAnnot.cpp
    ${CORE_ROOT}/PdfFile/SrcReader/PdfFont.cpp

    ${CORE_ROOT}/PdfFile/SrcWriter/AcroForm.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Annotation.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Catalog.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Destination.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Document.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Encrypt.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/EncryptDictionary.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Field.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Font.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Font14.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/FontCidTT.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/FontOTWriter.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/FontTT.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/FontTTWriter.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/GState.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Image.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Info.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Metadata.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Objects.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Outline.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Pages.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Pattern.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/ResourcesDictionary.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Shading.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/States.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Streams.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/Utils.cpp
    ${CORE_ROOT}/PdfFile/SrcWriter/RedactOutputDev.cpp

    ${CORE_ROOT}/PdfFile/Resources/BaseFonts.cpp
    ${CORE_ROOT}/PdfFile/Resources/CMapMemory/cmap_memory.cpp

    ${CORE_ROOT}/PdfFile/lib/fofi/FoFiBase.cc
    ${CORE_ROOT}/PdfFile/lib/fofi/FoFiEncodings.cc
    ${CORE_ROOT}/PdfFile/lib/fofi/FoFiIdentifier.cc
    ${CORE_ROOT}/PdfFile/lib/fofi/FoFiTrueType.cc
    ${CORE_ROOT}/PdfFile/lib/fofi/FoFiType1.cc
    ${CORE_ROOT}/PdfFile/lib/fofi/FoFiType1C.cc
    ${CORE_ROOT}/PdfFile/lib/goo/FixedPoint.cc
    ${CORE_ROOT}/PdfFile/lib/goo/gfile.cc
    ${CORE_ROOT}/PdfFile/lib/goo/GHash.cc
    ${CORE_ROOT}/PdfFile/lib/goo/GList.cc
    ${CORE_ROOT}/PdfFile/lib/goo/gmem.cc
    ${CORE_ROOT}/PdfFile/lib/goo/gmempp.cc
    ${CORE_ROOT}/PdfFile/lib/goo/GString.cc
    ${CORE_ROOT}/PdfFile/lib/goo/parseargs.c
    ${CORE_ROOT}/PdfFile/lib/goo/Trace.cc
    ${CORE_ROOT}/PdfFile/lib/splash/Splash.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashBitmap.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashClip.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFont.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFontEngine.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFontFile.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFontFileID.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFTFont.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFTFontEngine.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashFTFontFile.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashPath.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashPattern.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashScreen.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashState.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashXPath.cc
    ${CORE_ROOT}/PdfFile/lib/splash/SplashXPathScanner.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/AcroForm.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Annot.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Array.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/BuiltinFont.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/BuiltinFontTables.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Catalog.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/CharCodeToUnicode.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/CMap.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Decrypt.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Dict.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/DisplayState.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Error.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/FontEncodingTables.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Function.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Gfx.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/GfxFont.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/GfxState.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/GlobalParams.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/ImageOutputDev.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/JArithmeticDecoder.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/JBIG2Stream.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/JPXStream.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Lexer.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Link.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/NameToCharCode.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Object.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/OptionalContent.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Outline.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/OutputDev.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Page.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Parser.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PDF417Barcode.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PDFCore.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PDFDoc.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PDFDocEncoding.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PreScanOutputDev.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PSOutputDev.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/PSTokenizer.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/SecurityHandler.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/ShadingImage.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/SplashOutputDev.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Stream.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/TextOutputDev.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/TextString.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/TileCache.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/TileCompositor.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/TileMap.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/UnicodeMap.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/UnicodeRemapping.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/UnicodeTypeTable.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/UTF8.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/WebFont.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/XFAScanner.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/XRef.cc
    ${CORE_ROOT}/PdfFile/lib/xpdf/Zoox.cc

    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/bio.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/cidx_manager.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/cio.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/dwt.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/event.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/function_list.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/image.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/invert.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/j2k.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/jp2.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/mct.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/mqc.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/openjpeg.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/opj_clock.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/opj_malloc.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/phix_manager.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/pi.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/ppix_manager.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/sparse_array.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/t1.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/t2.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/tcd.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/tgt.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/thix_manager.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/thread.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/tpix_manager.c
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2/../../../../opj_bgraframe.cpp

    ${CORE_ROOT}/XpsFile/XpsFile.cpp
    ${CORE_ROOT}/XpsFile/XpsLib/Document.cpp
    ${CORE_ROOT}/XpsFile/XpsLib/XpsPage.cpp
    ${CORE_ROOT}/XpsFile/XpsLib/StaticResources.cpp
    ${CORE_ROOT}/XpsFile/XpsLib/Utils.cpp
    ${CORE_ROOT}/XpsFile/XpsLib/WString.cpp
    ${CORE_ROOT}/XpsFile/XpsLib/ContextState.cpp

    ${CORE_ROOT}/DjVuFile/libdjvu/../DjVu.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/../DjVuFileImplementation.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/Arrays.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/BSByteStream.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/BSEncodeByteStream.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/ByteStream.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DataPool.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/debug.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVmDir.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVmDir0.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVmDoc.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVmNav.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuAnno.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuDocEditor.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuDocument.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuDumpHelper.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuErrorList.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuFile.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuFileCache.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuGlobal.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuGlobalMemory.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuImage.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuInfo.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuMessageLite.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuNavDir.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuPalette.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuPort.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuText.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/DjVuToPS.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GBitmap.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GContainer.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GException.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GIFFManager.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GMapAreas.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GPixmap.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GRect.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GScaler.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GSmartPointer.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GString.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GThreads.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/GUnicode.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/IFFByteStream.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/IW44EncodeCodec.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/IW44Image.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/JB2EncodeCodec.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/JB2Image.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/JPEGDecoder.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/MMRDecoder.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/MMX.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/UnicodeByteStream.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/XMLParser.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/XMLTags.cpp
    ${CORE_ROOT}/DjVuFile/libdjvu/ZPCodec.cpp

    ${CORE_ROOT}/DjVuFile/wasm/libdjvu/atomic.cpp
    ${CORE_ROOT}/DjVuFile/wasm/libdjvu/DjVuMessage.cpp
    ${CORE_ROOT}/DjVuFile/wasm/libdjvu/GOS.cpp
    ${CORE_ROOT}/DjVuFile/wasm/libdjvu/GURL.cpp

    ${DESKTOP_ROOT}/graphics/pro/officedrawingfile.cpp

    ${CORE_ROOT}/UnicodeConverter/UnicodeConverter.cpp

    ${CORE_ROOT}/DocxRenderer/DocxRenderer.cpp
    ${CORE_ROOT}/DocxRenderer/src/resources/VectorGraphics.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/styles/FontStyle.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/styles/ParagraphStyle.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/Page.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/Document.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/managers/FontManager.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/managers/FontStyleManager.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/managers/ImageManager.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/managers/ParagraphStyleManager.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/elements/BaseItem.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/elements/ContText.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/elements/Paragraph.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/elements/Shape.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/elements/TextLine.cpp
    ${CORE_ROOT}/DocxRenderer/src/logic/elements/Table.cpp

    ${CORE_ROOT}/OdfFile/Common/logging.cpp

    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ustr_wcs.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ustrtrns.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/udata.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_io.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ustring.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/umutex.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/putil.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ustr_cnv.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnvmbcs.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucln_cmn.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv2022.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnvbocu.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/stringpiece.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/charstr.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_ext.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uobject.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/usprep.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/unistr.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uniset_props.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/loadednormalizer2impl.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/filterednormalizer2.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/utrie2.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/normalizer2.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/normalizer2impl.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/utrie.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucase.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uniset.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ruleiter.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/parsepos.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/util.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uprops.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uvector.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/unames.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/propname.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/utrie2_builder.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/unifunct.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/bmpset.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/unisetspan.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/unifilt.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/patternprops.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ustrcase.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/bytestrie.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/utf_impl.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/cmemory.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uhash.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/udatamem.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/umapfile.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uinvchar.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uchar.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ubidi_props.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/characterproperties.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucptrie.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/edits.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/umutablecptrie.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/bytesinkutil.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/emojiprops.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/cstring.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucmndata.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_u7.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_u8.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_u16.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_u32.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_err.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_cnv.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_lmb.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_cb.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_ct.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucharstrieiterator.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnvlat1.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/uvectr32.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnvhz.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnvscsu.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnv_bld.cpp
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common/ucnvisci.cpp

    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftdebug.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/autofit/autofit.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/bdf/bdf.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/cff/cff.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftbase.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftbitmap.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftfstype.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftgasp.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/cache/ftcache.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftglyph.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/gzip/ftgzip.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftinit.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/lzw/ftlzw.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftstroke.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftsystem.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/smooth/smooth.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftbbox.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftbdf.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftcid.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftmm.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftpfr.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftsynth.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/fttype1.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftwinfnt.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftgxval.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftotval.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/base/ftpatent.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/pcf/pcf.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/pfr/pfr.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/psaux/psaux.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/pshinter/pshinter.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/psnames/psmodule.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/raster/raster.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/sfnt/sfnt.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/truetype/truetype.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/type1/type1.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/cid/type1cid.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/type42/type42.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/winfonts/winfnt.c

    ${DESKTOP_ROOT}/xml/src/xmllight.cpp
    ${DESKTOP_ROOT}/xml/src/xmldom.cpp
    ${DESKTOP_ROOT}/xml/build/qt/libxml2_all.c
    ${DESKTOP_ROOT}/xml/build/qt/libxml2_all2.c

    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/lib/wasm_jmp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/drawingfile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/metafile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/HTMLRendererText.cpp
)

set_source_files_properties(${SOURCES} PROPERTIES GENERATED TRUE)

set_source_files_properties(
    ${DESKTOP_ROOT}/freetype-2.10.4/src/smooth/smooth.c
    #${DESKTOP_ROOT}/freetype-2.10.4/src/smooth/ftgrays.c
    ${DESKTOP_ROOT}/freetype-2.10.4/src/sfnt/sfnt.c
    #${DESKTOP_ROOT}/freetype-2.10.4/src/sfnt/ttcmap.c
    PROPERTIES LANGUAGE CXX
)

# -------------------------------------------------
# Library target
# -------------------------------------------------
add_executable(${PROJECT_NAME} 
    ${SOURCES}
)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/src/lib
    ${DESKTOP_ROOT}/agg-2.4/include
    ${DESKTOP_ROOT}/cximage/jasper/include
    ${DESKTOP_ROOT}/cximage/jpeg
    ${DESKTOP_ROOT}/cximage/png
    ${DESKTOP_ROOT}/freetype-2.10.4/include
    ${DESKTOP_ROOT}/freetype-2.10.4/include/freetype
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11
    ${CORE_ROOT}/OfficeUtils/src/zlib-1.2.11/contrib/minizip
    ${CORE_ROOT}/OfficeUtils/src
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/icu-wasm/icu/source/common
    ${DESKTOP_ROOT}/xml/libxml2/include
    ${DESKTOP_ROOT}/xml/build/qt
    ${CORE_ROOT}/PdfFile/lib/goo
    ${CORE_ROOT}/PdfFile/lib/fofi
    ${CORE_ROOT}/PdfFile/lib/splash
    ${CORE_ROOT}/PdfFile/lib
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg
    ${DESKTOP_ROOT}/raster/Jp2/openjpeg/openjpeg-2.4.0/src/lib/openjp2
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash/include
    ${EO_CORE_3RD_PARTY_INSTALL_DIR}/openssl-hash/include
    ${EO_CORE_3RD_PARTY_WORK_DIR}/openssl-hash
    ${CORE_ROOT}/DocxRenderer
)

# -------------------------------------------------
# Defines
# -------------------------------------------------
target_compile_definitions(${PROJECT_NAME} PRIVATE
__linux__ _LINUX UNIX
FT2_BUILD_LIBRARY HAVE_FCNTL_H
FT_CONFIG_OPTION_SYSTEM_ZLIB
BUILDING_WASM_MODULE
U_COMMON_IMPLEMENTATION
errno=0 THREADMODEL=0 DEBUGLVL=0
HAVE_MBSTATE_T HAVE_STDINCLUDES HAS_WCHAR HAVE_VA_COPY
LIBXML_READER_ENABLED LIBXML_PUSH_ENABLED LIBXML_HTML_ENABLED
LIBXML_XPATH_ENABLED LIBXML_OUTPUT_ENABLED LIBXML_C14N_ENABLED
LIBXML_SAX1_ENABLED LIBXML_TREE_ENABLED LIBXML_XPTR_ENABLED
XML_ERROR_DISABLE_MODE IN_LIBXML LIBXML_STATIC BUILD_ZLIB_AS_SOURCES
_ARM_ALIGN_
_tcsnicmp=strncmp _lseek=lseek _getcwd=getcwd
NO_CONSOLE_IO USE_EXTERNAL_JPEG2000 USE_JPIP OPJ_STATIC
FONT_ENGINE_DISABLE_FILESYSTEM IMAGE_CHECKER_DISABLE_XML
USE_OPENSSL_HASH DISABLE_FULL_DOCUMENT_CREATION DISABLE_FILESYSTEM
CRYPTOPP_DISABLE_ASM DISABLE_TYPE_MISMATCH
)

# -------------------------------------------------
# Compile flags
# -------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
-O3
-fexceptions
-Wno-unused-command-line-argument
-Wno-register
)

# -------------------------------------------------
# Emscripten linker flags
# -------------------------------------------------
set(EXPORTED_FUNCS
    _malloc
    _free
    _GetType
    _Open
    _Close
    _GetErrorCode
    _GetInfo
    _GetPixmap
    _GetGlyphs
    _GetLinks
    _GetStructure
    _GetInteractiveFormsInfo
    _GetInteractiveFormsFonts
    _GetInteractiveFormsAP
    _GetButtonIcons
    _GetAnnotationsInfo
    _GetAnnotationsAP
    _InitializeFontsBin
    _InitializeFontsBase64
    _InitializeFontsRanges
    _SetFontBinary
    _GetFontBinary
    _GetGIDByUnicode
    _IsFontBinaryExist
    _DestroyTextInfo
    _IsNeedCMap
    _SetCMapData
    _SetScanPageFonts
    _ScanPage
    _SplitPages
    _MergePages
    _UnmergePages
    _RedactPage
    _UndoRedact
    _CheckOwnerPassword
    _CheckPerm
    _GetImageBase64
    _GetImageBase64Len
    _GetImageBase64Ptr
    _GetImageBase64Free
)

# Create Wasm Script
inject_script(
    ${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/drawingfile.js"
    "${CMAKE_CURRENT_BINARY_DIR}/drawingfile_wasm.js"
    MODE PRE_BUILD
    REPLACEMENTS
        "{{{ DRAWINGFILE }}}"  "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/drawingfile_wasm.js"
)

# Create Native Script
inject_script(
    ${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/drawingfile.js"
    "${CMAKE_CURRENT_BINARY_DIR}/drawingfile_native.js"
    MODE PRE_BUILD
    REPLACEMENTS
        "{{{ DRAWINGFILE }}}"  "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/drawingfile_native.js"
)

#string(REPLACE ";" "," EXPORTED_FUNCS_STR "${EXPORTED_FUNCS}")
list(JOIN EXPORTED_FUNCS "," EXPORTED_FUNCS_STR)

target_link_options(${PROJECT_NAME} PRIVATE
-sALLOW_MEMORY_GROWTH=1
-sFILESYSTEM=0
-sENVIRONMENT=web
-sLLD_REPORT_UNDEFINED
-sWASM=1
-sASSERTIONS=0
-sNO_DISABLE_EXCEPTION_CATCHING
-fexceptions
-sEXPORTED_FUNCTIONS=[${EXPORTED_FUNCS_STR}]
-sEXPORTED_RUNTIME_METHODS=HEAP8,HEAPU8,HEAP32,noExitRuntime,print,printErr
"-sLEGACY_VM_SUPPORT=1"
"SHELL:--pre-js ${CORE_ROOT}/Common/js/string_utf8.js"
"SHELL:--pre-js ${CORE_ROOT}/Common/js/desktop_fetch_new.js"
"SHELL:--post-js ${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/stream.js"
"SHELL:--post-js ${CMAKE_CURRENT_BINARY_DIR}/drawingfile_wasm.js"
)

# -------------------------------------------------
# Output location
# -------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${EO_CORE_OUTPUT_DIR}/engine
SUFFIX ".js"
)

# Create final .js for Wasm
inject_script(
    ${PROJECT_NAME}
    "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/drawingfile_base.js"
    "${EO_CORE_OUTPUT_DIR}/engine/${PROJECT_NAME}.js"
    MODE POST_BUILD
    REPLACEMENTS
        "{{{ MODULE }}}"  "${EO_CORE_OUTPUT_DIR}/engine/${PROJECT_NAME}.js"
)


add_custom_command(
  OUTPUT "${EO_CORE_OUTPUT_DIR}/engine/drawingfile_native.js"
  COMMAND cat
    ${CORE_ROOT}/Common/js/string_utf8.js
    ${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/stream.js
    ${CMAKE_CURRENT_BINARY_DIR}/drawingfile_native.js
    > ${EO_CORE_OUTPUT_DIR}/engine/drawingfile_native.js
  DEPENDS
    "${CORE_ROOT}/Common/js/string_utf8.js"
    "${CMAKE_CURRENT_SOURCE_DIR}/wasm/js/stream.js"
    "${CMAKE_CURRENT_BINARY_DIR}/drawingfile_native.js"
  COMMENT "Concatenating native JS files"
  VERBATIM
)

add_custom_target(web_bundle ALL DEPENDS "${EO_CORE_OUTPUT_DIR}/engine/drawingfile_native.js")

declare_victory( ${PROJECT_NAME} )

