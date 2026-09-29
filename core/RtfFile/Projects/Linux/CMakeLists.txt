cmake_minimum_required(VERSION 3.10)

project(RtfFormatLib)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../..")

include(${CORE_ROOT_DIR}/common.cmake)

set(RTF_FILE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../..")

add_library(RtfFormatLib STATIC
    ${RTF_FILE_ROOT}/Format/ConvertationManager.cpp
    ${RTF_FILE_ROOT}/Format/DestinationCommand.cpp
    ${RTF_FILE_ROOT}/Format/IdGenerator.cpp
    ${RTF_FILE_ROOT}/Format/Ole1FormatReader.cpp
    ${RTF_FILE_ROOT}/Format/RtfBookmark.cpp
    ${RTF_FILE_ROOT}/Format/RtfChar.cpp
    ${RTF_FILE_ROOT}/Format/RtfDocument.cpp
    ${RTF_FILE_ROOT}/Format/RtfField.cpp
    ${RTF_FILE_ROOT}/Format/RtfGlobalTables.cpp
    ${RTF_FILE_ROOT}/Format/RtfLex.cpp
    ${RTF_FILE_ROOT}/Format/RtfMath.cpp
    ${RTF_FILE_ROOT}/Format/RtfOldList.cpp
    ${RTF_FILE_ROOT}/Format/RtfOle.cpp
    ${RTF_FILE_ROOT}/Format/RtfParagraph.cpp
    ${RTF_FILE_ROOT}/Format/RtfPicture.cpp
    ${RTF_FILE_ROOT}/Format/RtfProperty.cpp
    ${RTF_FILE_ROOT}/Format/RtfReader.cpp
    ${RTF_FILE_ROOT}/Format/RtfSection.cpp
    ${RTF_FILE_ROOT}/Format/RtfShape.cpp
    ${RTF_FILE_ROOT}/Format/RtfTable.cpp
    ${RTF_FILE_ROOT}/Format/RtfTableCell.cpp
    ${RTF_FILE_ROOT}/Format/RtfTableRow.cpp
    ${RTF_FILE_ROOT}/Format/RtfToken.cpp
    ${RTF_FILE_ROOT}/Format/RtfWriter.cpp
    ${RTF_FILE_ROOT}/Format/UniversalConverterUtils.cpp
    ${RTF_FILE_ROOT}/Format/Utils.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXAbstractNumReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXAppReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXBorderReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXcnfStyleReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXColorReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXColorReader2.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXColorSchemeReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXCoreReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXDocDefaultsReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXDocumentReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXDrawingGraphicReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFontReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFontSchemeReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFontTableReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFootnotesReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXHeaderReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXLevelReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXMathReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXNumberingMapReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXNumberingReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXParagraphElementReaders.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureAnchorReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureInlineReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXpPrTabReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXShadingReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXShapeReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXStyleReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXStyleTableReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXTableReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtblLookReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtblpPrReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtblPrReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtcPrReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXTextItemReader.cpp
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXThemeReader.cpp	
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXCommentsWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXContentTypesWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXDocumentWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXFontTableWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXFootnoteWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXNumberingWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXRelsWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXSettingsWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXStylesWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXThemeWriter.cpp
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXWriter.cpp

    ${RTF_FILE_ROOT}/Format/Basic.h
    ${RTF_FILE_ROOT}/Format/ConvertationManager.h
    ${RTF_FILE_ROOT}/Format/DestinationCommand.h
    ${RTF_FILE_ROOT}/Format/IdGenerator.h
    ${RTF_FILE_ROOT}/Format/Ole1FormatReader.h
    ${RTF_FILE_ROOT}/Format/RtfBookmark.h
    ${RTF_FILE_ROOT}/Format/RtfChar.h
    ${RTF_FILE_ROOT}/Format/RtfDefine.h
    ${RTF_FILE_ROOT}/Format/RtfDocument.h
    ${RTF_FILE_ROOT}/Format/RtfErrors.h
    ${RTF_FILE_ROOT}/Format/RtfField.h
    ${RTF_FILE_ROOT}/Format/RtfGlobalTables.h
    ${RTF_FILE_ROOT}/Format/RtfLex.h
    ${RTF_FILE_ROOT}/Format/RtfMath.h
    ${RTF_FILE_ROOT}/Format/RtfOle.h
    ${RTF_FILE_ROOT}/Format/RtfParagraph.h
    ${RTF_FILE_ROOT}/Format/RtfPicture.h
    ${RTF_FILE_ROOT}/Format/RtfProperty.h
    ${RTF_FILE_ROOT}/Format/RtfReader.h
    ${RTF_FILE_ROOT}/Format/RtfSection.h
    ${RTF_FILE_ROOT}/Format/RtfShape.h
    ${RTF_FILE_ROOT}/Format/RtfTable.h
    ${RTF_FILE_ROOT}/Format/RtfTableCell.h
    ${RTF_FILE_ROOT}/Format/RtfTableRow.h
    ${RTF_FILE_ROOT}/Format/RtfToken.h
    ${RTF_FILE_ROOT}/Format/RtfWriter.h
    ${RTF_FILE_ROOT}/Format/UniversalConverterUtils.h
    ${RTF_FILE_ROOT}/Format/Utils.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXAbstractNumReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXAppReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXBorderReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXcnfStyleReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXColorReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXColorReader2.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXColorSchemeReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXCoreReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXDocDefaultsReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXDocumentReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFontReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFontSchemeReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFontTableReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXFootnotesReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXHeaderReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXLevelReader.h
    # ${RTF_FILE_ROOT}/OOXml/Reader/OOXMathPropReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXMathReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXNumberingMapReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXNumberingReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXParagraphReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureAnchorReader.h
    # ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureGraphicReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureInlineReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXPictureReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXpPrFrameReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXpPrReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXpPrTabReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXReaderBasic.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXRelsReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXrPrReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXRunReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXSectionPropertyReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXSettingsReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXShadingReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXShapeReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXStyleReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXStyleTableReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXTableCellReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXTableReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXTableRowReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtblLookReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtblpPrReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtblPrReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtcPrReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXTextItemReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXThemeReader.h
    ${RTF_FILE_ROOT}/OOXml/Reader/OOXtrPrReader.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXCommentsWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXContentTypesWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXDocumentWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXFontTableWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXFootnoteWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXNumberingWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXRelsWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXSettingsWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXStylesWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXThemeWriter.h
    ${RTF_FILE_ROOT}/OOXml/Writer/OOXWriter.h
)

set_default_options(RtfFormatLib)

if( MSVC )
    target_compile_definitions( RtfFormatLib PRIVATE
        _UNICODE
        UNICODE
    )
endif()

target_compile_definitions(RtfFormatLib PRIVATE
    AVS_USE_CONVERT_PPTX_TOCUSTOM_VML
)

target_include_directories(RtfFormatLib PRIVATE
	${CORE_ROOT_DIR}/OdfFile/include
)

target_link_libraries(RtfFormatLib PRIVATE 
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
)

set_property(TARGET RtfFormatLib PROPERTY POSITION_INDEPENDENT_CODE ON)

declare_victory( RtfFormatLib )
