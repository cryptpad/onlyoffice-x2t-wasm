cmake_minimum_required(VERSION 3.10)

project(XlsFormatLib)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../../..")
include(${CORE_ROOT_DIR}/common.cmake)

set(XLS_FILE_SOURCES_DIR "${CORE_ROOT_DIR}/MsBinaryFile/XlsFile")
set(COMMON_SOURCES_DIR "${CORE_ROOT_DIR}/MsBinaryFile/Common")

add_library(XlsFormatLib STATIC
    ${XLS_FILE_SOURCES_DIR}/Format/Auxiliary/HelpFunc.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFRecord.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFRecordType.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFStream.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFStreamCacheReader.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFStreamCacheWriter.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CompoundFile.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/rtl/cipher.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/rtl/digest.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/BiffDecoder_RCF.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/BinaryCodec_RCF.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/Decryptor.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/RC4Crypt.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/XORCrypt.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Logging/Log.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Logging/Logger.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/ConvertXls2Xlsx.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/external_items.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/mediaitems_utils.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/namespaces.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/oox_content_type.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/oox_package.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/oox_rels.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/XlsConverter.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_conversion_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_drawing_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_drawings.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_hyperlinks.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_output_xml.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_package.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_protection.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_tablecontext.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_textcontext.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_chart_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_pivots_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_sheet_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_external_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_activeX_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_comments.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_comments_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xls_writer.cpp
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/pri/xls_format_logic.cpp

    ${COMMON_SOURCES_DIR}/Utils/OptPtr.h
    ${COMMON_SOURCES_DIR}/Utils/simple_xml_writer.h
    ${XLS_FILE_SOURCES_DIR}/Converter/ConvertXls2Xlsx.h
    ${XLS_FILE_SOURCES_DIR}/Converter/external_items.h
    ${XLS_FILE_SOURCES_DIR}/Converter/mediaitems_utils.h
    ${XLS_FILE_SOURCES_DIR}/Converter/namespaces.h
    ${XLS_FILE_SOURCES_DIR}/Converter/oox_content_type.h
    ${XLS_FILE_SOURCES_DIR}/Converter/oox_package.h
    ${XLS_FILE_SOURCES_DIR}/Converter/oox_rels.h
    ${XLS_FILE_SOURCES_DIR}/Converter/progressCallback.h
    ${XLS_FILE_SOURCES_DIR}/Converter/ShapeType.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xls_writer.h
    ${XLS_FILE_SOURCES_DIR}/Converter/XlsConverter.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_activeX_context.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_chart_context.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_conversion_context.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_drawing_context.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_drawings.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_external_context.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_hyperlinks.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_output_xml.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_package.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_pivots_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_protection.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_sheet_context.cpp
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_tablecontext.h
    ${XLS_FILE_SOURCES_DIR}/Converter/xlsx_textcontext.h
    ${XLS_FILE_SOURCES_DIR}/Format/Auxiliary/HelpFunc.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/BinSmartPointers.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFRecord.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFRecordType.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFStream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFStreamCacheReader.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CFStreamCacheWriter.h
    ${XLS_FILE_SOURCES_DIR}/Format/Binary/CompoundFile.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/BiffDecoder_RCF.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/BinaryCodec_RCF.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/Crypt.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/Decryptor.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/RC4Crypt.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/rtl/cipher.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/rtl/digest.h
    ${XLS_FILE_SOURCES_DIR}/Format/Crypt/XORCrypt.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logging/Log.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logging/Logger.h    
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/BinProcessor.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/ChartSheetSubstream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/CommonSubstream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/CompositeObject.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/EncryptionStream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/GlobalsSubstream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/GlobalWorkbookInfo.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/MacroSheetSubstream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/WorkbookStreamObject.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/WorksheetSubstream.h
    ${XLS_FILE_SOURCES_DIR}/Format/Logic/XlsElementsType.h
)

target_precompile_headers(XlsFormatLib PRIVATE
    ../precompiled.h
)

set_default_options(XlsFormatLib)

if( MSVC )
    target_compile_definitions( XlsFormatLib PRIVATE
        _UNICODE
        UNICODE
    )
endif()

target_include_directories(XlsFormatLib PRIVATE
    ${XLS_FILE_SOURCES_DIR}/Format
    ${XLS_FILE_SOURCES_DIR}/Format/Logic
    ${COMMON_SOURCES_DIR}
    ${CORE_ROOT_DIR}/OOXML/XlsbFormat
)

target_link_libraries(XlsFormatLib PRIVATE 
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
)

if( MSVC )
    target_compile_options( XlsFormatLib PRIVATE /bigobj )
endif()

set_property(TARGET XlsFormatLib PROPERTY POSITION_INDEPENDENT_CODE ON)

declare_victory( XlsFormatLib )
