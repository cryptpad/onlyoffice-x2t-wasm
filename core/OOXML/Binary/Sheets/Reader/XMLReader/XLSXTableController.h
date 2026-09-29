/*
 * (c) Copyright Ascensio System SIA 2010-2023
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#pragma once

#include "../CellFormatController/CellFormatController.h"

#include "../../../../Base/Base.h"
#include "../../../../XlsxFormat/Worksheets/Worksheet.h"
#include "../../../../XlsxFormat/Xlsx.h"

#include <string>
#include <vector>

/// @brief is a wrapper class that allows adding cells to a table and creating a document from the created cells
class XLSXTableController
{

public:
    /// @brief initialization of object fields
    /// @param book an object that will be filled with data using the FormBook method
    /// @param lcid local ID
    XLSXTableController(OOX::Spreadsheet::CXlsx &book, _INT32 lcid);

    /// @brief adding a cell
    /// @param sText inserted text
    /// @param nRow row number
    /// @param nCol column number
    /// @param bIsWrap sign of wrapping
    void AddCell(const std::wstring &sText, INT nRow, INT nCol);

    /// @brief getting xlsx document
    void FormBook();

private:
    /// @brief adding a row
    /// @param pRow pointer to row
    /// @param pWorkSheet pointer to worksheet
    /// @param nRow row number
    _UINT32 addRow(OOX::Spreadsheet::CRow *pRow, OOX::Spreadsheet::CWorksheet *pWorkSheet,  INT nRow);

    /// @brief adding a page
    /// @param page pointer to sheet
    /// @param pageNumber page number
    void addPage(OOX::Spreadsheet::CWorksheet *page, INT pageNumber);

    /// @brief xlsx document
    OOX::Spreadsheet::CXlsx *book_;

    /// @brief vector with table rows
    std::vector<OOX::Spreadsheet::CRow*> tableRows_;

    /// @brief format controller
    std::shared_ptr<CellFormatController> formates_;
};
