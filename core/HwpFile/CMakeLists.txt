cmake_minimum_required(VERSION 3.10)

project(HWPFile)

set(CORE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include(${CORE_ROOT_DIR}/common.cmake)

if(NOT TARGET CryptoPPLib)
    add_subdirectory(${CORE_ROOT_DIR}/Common/3dParty/cryptopp/project CryptoPPLib)
endif()

if(NOT TARGET kernel)
    add_subdirectory(${CORE_ROOT_DIR}/Common kernel)
endif()

if(NOT TARGET UnicodeConverter)
    add_subdirectory(${CORE_ROOT_DIR}/UnicodeConverter UnicodeConverter)
endif()

if(NOT TARGET graphics)
    add_subdirectory(${CORE_ROOT_DIR}/DesktopEditor/graphics/cmake graphics)
endif()

if(NOT TARGET StarMathConverter)
    add_subdirectory(${CORE_ROOT_DIR}/OdfFile/Reader/Converter/StarMath2OOXML StarMathConverter)
endif()

add_library(HWPFile SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Common/WriterContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Common/XMLReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/Converter2OOXML.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/FootnoteConverter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/NumberingConverter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/OleConverter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/StyleConverter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPDocInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecord.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordBinData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordBorderFill.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordBullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordCharShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordCtrlData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordCtrlHeader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordDocumentProperties.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordFaceName.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordFormObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordIDMaping.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordListHeader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordNumbering.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordParaRangeTag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordParaShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordParaText.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordStyle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HwpRecordTabDef.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HwpFileHeader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPMLFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPSection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPStream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPXFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/OLEdoc/CompoundFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/OLEdoc/DirectoryEntry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CapParagraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CellParagraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CharShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/Ctrl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlAutoNumber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlCharacter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlClick.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlColumnDef.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlCommon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlContainer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlEmpty.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlEqEdit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlField.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlForm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlGeneralShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlHeadFoot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlNewNumber.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlNote.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlObjElement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlPageNumPos.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlSectionDef.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeArc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeConnectLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeCurve.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeEllipse.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeLine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeOle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapePic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapePolygon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeRect.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeTextArt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeVideo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlTable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/HWPPargraph.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/LineSeg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/ParaText.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/TblCell.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Section/NoteShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Section/Page.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Section/PageBorderFill.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HWPFile.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Common/Common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Common/NodeNames.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Common/WriterContext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Common/XMLReader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/ConversionState.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/Converter2OOXML.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/FootnoteConverter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/NumberingConverter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/OleConverter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/StyleConverter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/Transform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Conversion/Types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Errors.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HanType.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPDocInfo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecord.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordBinData.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordBorderFill.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordBullet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordCharShape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordCtrlData.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordCtrlHeader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordDocumentProperties.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordFaceName.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordFormObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordIDMaping.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordListHeader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordNumbering.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordParaRangeTag.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordParaShape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordParaText.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPRecordStyle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HwpRecordTabDef.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HwpRecordTypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPElements/HWPTag.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPFile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HwpFileHeader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPMLFile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPSection.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPStream.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/HWPXFile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/OLEdoc/CompoundFile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/OLEdoc/DirectoryEntry.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/OLEdoc/Sector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/OLEdoc/SectorType.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CapParagraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CellParagraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CharShape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CommonObj.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/Ctrl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlAutoNumber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlCharacter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlClick.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlColumnDef.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlCommon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlContainer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlEmpty.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlEqEdit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlField.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlForm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlGeneralShape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlHeadFoot.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlNewNumber.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlNote.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlObjElement.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlPageNumPos.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlSectionDef.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeArc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeConnectLine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeCurve.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeEllipse.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeLine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeOle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapePic.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapePolygon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeRect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeTextArt.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlShapeVideo.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/CtrlTable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/HWPPargraph.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/LineSeg.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/ParaText.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/Point.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/RangeTag.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Paragraph/TblCell.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Section/NoteShape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Section/Page.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HwpDoc/Section/PageBorderFill.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HWPFile.h
)

set_default_options(HWPFile)

target_include_directories(HWPFile PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(HWPFile PRIVATE
    HWPFILE_USE_DYNAMIC_LIBRARY
    CRYPTOPP_DISABLE_ASM
)

target_link_libraries(HWPFile PUBLIC
    CryptoPPLib
    kernel
    UnicodeConverter
    graphics
    StarMathConverter
)

copy_artifacts_to_folder("HWPFile" "${EO_CORE_OUTPUT_DIR}")

declare_victory( HWPFile )
