cmake_minimum_required(VERSION 3.10)

project(DocxFormatLib)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../..")

include(${CORE_ROOT_DIR}/common.cmake)

set(OOXML_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../..")
set(DOCX_FORMAT_SOURCES_ROOT "${OOXML_ROOT_DIR}/DocxFormat")

add_library(DocxFormatLib STATIC
    ${CORE_ROOT_DIR}/Common/3dParty/pole/pole.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/App.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Bibliography.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Comments.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/ContentTypes.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Core.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/CustomXml.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramColors.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramData.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramDrawing.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramLayout.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramQuickStyle.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Document.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Docx.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/DocxFlat.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Drawing/Drawing.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Drawing/DrawingExt.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Endnote.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/External/External.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/External/ExternalHyperLink.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/File.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/FileFactory.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/FileType.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/FileTypes.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Font.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/FontTable.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Footnote.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/FtnEdn.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/HeaderFooter.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/IFileContainer.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/AlternateContent.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Annotations.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Bdo.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Dir.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/DocParts.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/FldChar.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/FldSimple.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Hyperlink.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Paragraph.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/ParagraphProperty.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Pict.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Run.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/RunContent.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/RunProperty.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Sdt.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/SectionProperty.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Shape.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/SmartTag.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Table.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/TableProperty.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Vml.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/VmlOfficeDrawing.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/VmlWord.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/oMath.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/oMathContent.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/oMathPara.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/ActiveX.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Audio.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Image.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/JsaProject.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Media.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/OleObject.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/VbaProject.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Video.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Numbering.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Rels.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/RId.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Settings/Settings.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Settings/WebSettings.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/Styles.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/UnknowTypeFile.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/VmlDrawing.cpp
    ${DOCX_FORMAT_SOURCES_ROOT}/WritingElement.cpp
    ${OOXML_ROOT_DIR}/Base/codecvt.cpp
    ${OOXML_ROOT_DIR}/Base/DateTime.cpp
    ${OOXML_ROOT_DIR}/Base/unicode_util.cpp
    ${OOXML_ROOT_DIR}/Base/Unit.cpp
    ${OOXML_ROOT_DIR}/Base/WinColor.cpp
    ${OOXML_ROOT_DIR}/Binary/MathEquation/MathEquation.cpp
    ${OOXML_ROOT_DIR}/Common/ComplexTypes.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Base.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Draw.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Drawing.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_OMath.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Rtf.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Shared.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Spreadsheet.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Vml.cpp
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Word.cpp
    ${OOXML_ROOT_DIR}/SystemUtility/FileUtils.cpp
    ${OOXML_ROOT_DIR}/SystemUtility/SystemUtility.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/FileFactory_Draw.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/FileTypes_Draw.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/Shapes.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioConnections.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioDocument.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioOthers.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioPages.cpp
    ${OOXML_ROOT_DIR}/VsdxFormat/Vsdx.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/CalcChain/CalcChain.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/Chart.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartColors.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartDrawing.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartSerialize.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartSerializeEx.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartStyle.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Comments/ThreadedComments.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Comments/XlsxComments.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Common.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/ComplexTypes_Spreadsheet.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Controls/Controls.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/CellAnchor.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/FromTo.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/Pos.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/XlsxDrawing.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/ExternalLinks/ExternalLinkPath.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/ExternalLinks/ExternalLinks.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/FileFactory_Spreadsheet.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/FileTypes_Spreadsheet.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/NamedSheetViews/NamedSheetViews.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Ole/OleObjects.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotCacheChildOther.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotCacheDefinitionExt.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotHierarchies.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/Pivots.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/RichData/RdRichData.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/PhoneticPr.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/SharedStrings.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/Si.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/Text.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/XlsxRun.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Slicer/Slicer.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Slicer/SlicerCache.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Slicer/SlicerCacheExt.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Borders.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/CellStyles.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Colors.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/dxf.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Fills.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Fonts.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/NumFmts.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/rPr.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/TableStyles.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Xfs.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/XlsxStyles.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Autofilter.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Connections.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Tables.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Timelines/Timeline.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/BookViews.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/CalcPr.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/CustomsXml.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/DefinedNames.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/ExternalReferences.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/Metadata.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/Sheets.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/Workbook.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/WorkbookPr.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Cols.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/ConditionalFormatting.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/DataValidation.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/MergeCells.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/SheetData.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Sparkline.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Worksheet.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/WorksheetChildOther.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/XlsxHyperlinks.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/Xlsx.cpp
    ${OOXML_ROOT_DIR}/XlsxFormat/XlsxFlat.cpp
    ${OOXML_ROOT_DIR}/XML/XmlSimple.cpp
    docx_format.cpp

    ${DOCX_FORMAT_SOURCES_ROOT}/App.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Bibliography.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Comments.h
    ${DOCX_FORMAT_SOURCES_ROOT}/ContentTypes.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Core.h
    ${DOCX_FORMAT_SOURCES_ROOT}/CustomXml.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramColors.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramData.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramDrawing.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramLayout.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Diagram/DiagramQuickStyle.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Document.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Docx.h
    ${DOCX_FORMAT_SOURCES_ROOT}/DocxFlat.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Drawing/Drawing.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Drawing/DrawingExt.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Endnote.h
    ${DOCX_FORMAT_SOURCES_ROOT}/External/External.h
    ${DOCX_FORMAT_SOURCES_ROOT}/External/HyperLink.h
    ${DOCX_FORMAT_SOURCES_ROOT}/File.h
    ${DOCX_FORMAT_SOURCES_ROOT}/FileFactory.h
    ${DOCX_FORMAT_SOURCES_ROOT}/FileType.h
    ${DOCX_FORMAT_SOURCES_ROOT}/FileTypes.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Font.h
    ${DOCX_FORMAT_SOURCES_ROOT}/FontTable.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Footnote.h
    ${DOCX_FORMAT_SOURCES_ROOT}/FtnEdn.h
    ${DOCX_FORMAT_SOURCES_ROOT}/HeaderFooter.h
    ${DOCX_FORMAT_SOURCES_ROOT}/IFileBuilder.h
    ${DOCX_FORMAT_SOURCES_ROOT}/IFileContainer.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/AlternateContent.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Annotations.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Bdo.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Dir.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/DocParts.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/FldChar.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/FldSimple.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Hyperlink.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Paragraph.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/ParagraphProperty.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Pict.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Run.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/RunContent.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/RunProperty.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Sdt.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/SectionProperty.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Shape.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/SmartTag.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Table.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/TableProperty.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/Vml.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/VmlOfficeDrawing.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Logic/VmlWord.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/OMath.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/oMathBottomNodes.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/oMathContent.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Math/oMathPara.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/ActiveX.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Audio.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Image.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/JsaProject.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Media.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/OleObject.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/VbaProject.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Media/Video.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Numbering.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Rels.h
    ${DOCX_FORMAT_SOURCES_ROOT}/RId.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Settings/Settings.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Settings/WebSettings.h
    ${DOCX_FORMAT_SOURCES_ROOT}/Styles.h
    # ${DOCX_FORMAT_SOURCES_ROOT}/Unit.h
    ${DOCX_FORMAT_SOURCES_ROOT}/UnknowTypeFile.h
    ${DOCX_FORMAT_SOURCES_ROOT}/VmlDrawing.h
    # ${DOCX_FORMAT_SOURCES_ROOT}/WorkbookComments.h
    ${DOCX_FORMAT_SOURCES_ROOT}/WritingElement.h
    ${OOXML_ROOT_DIR}/Base/Base.h
    ${OOXML_ROOT_DIR}/Base/codecvt.h
    ${OOXML_ROOT_DIR}/Base/DateTime.h
    ${OOXML_ROOT_DIR}/Base/Nullable.h
    ${OOXML_ROOT_DIR}/Base/SmartPtr.h
    ${OOXML_ROOT_DIR}/Base/unicode_util.h
    ${OOXML_ROOT_DIR}/Base/Unit.h
    ${OOXML_ROOT_DIR}/Common/ComplexTypes.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Base.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Draw.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Drawing.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_OMath.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Shared.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Vml.h
    ${OOXML_ROOT_DIR}/Common/SimpleTypes_Word.h
    # ${OOXML_ROOT_DIR}/Common/Size.h
    # ${OOXML_ROOT_DIR}/Common/Unit.h
    # ${OOXML_ROOT_DIR}/Common/Wrap.h
    # ${OOXML_ROOT_DIR}/Common/ZIndex.h
    # ${OOXML_ROOT_DIR}/MathEquation/LEStream.h
    # ${OOXML_ROOT_DIR}/MathEquation/MathEquation.h
    # ${OOXML_ROOT_DIR}/MathEquation/OutputDev.h
    # ${OOXML_ROOT_DIR}/MathEquation/String.h
    # ${OOXML_ROOT_DIR}/MathEquation/StringOutput.h
    # ${OOXML_ROOT_DIR}/MathEquation/Types.h
    ${OOXML_ROOT_DIR}/SystemUtility/SystemUtility.h
    # ${OOXML_ROOT_DIR}/Utility/TxtFile.h
    # ${OOXML_ROOT_DIR}/Utility/Utility.h
    ${OOXML_ROOT_DIR}/VsdxFormat/FileFactory_Draw.h
    ${OOXML_ROOT_DIR}/VsdxFormat/FileTypes_Draw.h
    ${OOXML_ROOT_DIR}/VsdxFormat/Shapes.h
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioConnections.h
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioDocument.h
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioOthers.h
    ${OOXML_ROOT_DIR}/VsdxFormat/VisioPages.h
    ${OOXML_ROOT_DIR}/VsdxFormat/Vsdx.h
    ${OOXML_ROOT_DIR}/XlsxFormat/CalcChain/CalcChain.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/Chart.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartColors.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartDrawing.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartSerialize.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartSerializeEx.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Chart/ChartStyle.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Comments/Comments.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Comments/ThreadedComments.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Common.h
    ${OOXML_ROOT_DIR}/XlsxFormat/CommonInclude.h
    ${OOXML_ROOT_DIR}/XlsxFormat/ComplexTypes_Spreadsheet.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Controls/Controls.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/CellAnchor.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/Drawing.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/FromTo.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Drawing/Pos.h
    ${OOXML_ROOT_DIR}/XlsxFormat/ExternalLinks/ExternalLinkPath.h
    ${OOXML_ROOT_DIR}/XlsxFormat/ExternalLinks/ExternalLinks.h
    ${OOXML_ROOT_DIR}/XlsxFormat/FileFactory_Spreadsheet.h
    ${OOXML_ROOT_DIR}/XlsxFormat/FileTypes_Spreadsheet.h
    ${OOXML_ROOT_DIR}/XlsxFormat/NamedSheetViews/NamedSheetViews.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Ole/OleObjects.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotCacheChildOther.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotCacheDefinition.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotCacheDefinitionExt.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotCacheRecords.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotHierarchies.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Pivot/PivotTable.h
    ${OOXML_ROOT_DIR}/XlsxFormat/RichData/RdRichData.h
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/PhoneticPr.h
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/Run.h
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/SharedStrings.h
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/Si.h
    ${OOXML_ROOT_DIR}/XlsxFormat/SharedStrings/Text.h
    # ${OOXML_ROOT_DIR}/XlsxFormat/SimpleTypes_Spreadsheet.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Slicer/Slicer.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Slicer/SlicerCache.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Slicer/SlicerCacheExt.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Borders.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/CellStyles.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Colors.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/dxf.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Fills.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Fonts.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/NumFmts.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/rPr.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Styles.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/TableStyles.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Styles/Xfs.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Autofilter.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Autofilter.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Connections.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/QueryTable.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Table/Table.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Timelines/Timeline.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/BookViews.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/CalcPr.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/CustomsXml.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/DefinedNames.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/ExternalReferences.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/Metadata.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/Sheets.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/Workbook.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Workbook/WorkbookPr.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Cols.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/ConditionalFormatting.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/DataValidation.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Hyperlinks.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/MergeCells.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/SheetData.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Sparkline.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/Worksheet.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Worksheets/WorksheetChildOther.h
    ${OOXML_ROOT_DIR}/XlsxFormat/WritingElement.h
    ${OOXML_ROOT_DIR}/XlsxFormat/Xlsx.h
    ${OOXML_ROOT_DIR}/XlsxFormat/XlsxFlat.h
    # ${OOXML_ROOT_DIR}/XML/Utils.h
    ${OOXML_ROOT_DIR}/XML/XmlSimple.h
    docx_format.h
)

set_default_options(DocxFormatLib)

if( MSVC )
    target_compile_definitions( DocxFormatLib PRIVATE
        _UNICODE
        UNICODE
    )
endif()

target_precompile_headers(DocxFormatLib PRIVATE
    precompiled.h
)

if(UNIX)
    target_compile_options(DocxFormatLib PRIVATE
        -include cfloat
        # Re-enable exporting symbols
        -fvisibility=default
        -fvisibility-inlines-hidden
    )
endif()

target_link_libraries(DocxFormatLib PRIVATE 
    Boost::system
    Boost::filesystem
    Boost::regex
    Boost::date_time
)


set_property(TARGET DocxFormatLib PROPERTY POSITION_INDEPENDENT_CODE ON)

declare_victory( DocxFormatLib )
