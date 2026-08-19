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

#include "../../../../Base/Base.h"
#include "../../../../XlsxFormat/Worksheets/Worksheet.h"
#include "../../../../XlsxFormat/Styles/Styles.h"
#include "DateReader.h"
#include "DigitReader.h"


/// @brief class defining and adjusting the type of data placed in table cells
class CellFormatController
{

public:
    /// @brief constructor
    /// @param styles styles from table
    CellFormatController(OOX::Spreadsheet::CStyles *styles, _INT32 lcid);

    /// @brief processes data inserted into a table cell, converting it to the desired type, and filling the cell with it
    /// @param pCell pointer to cell
    /// @param value data inserted into the cell in string type
    int ProcessCellType(OOX::Spreadsheet::CCell *pCell, const std::wstring &value, bool bIsWrap = false);


	/// @brief pointer to a document sheet
	OOX::Spreadsheet::CWorksheet *m_pWorksheet = nullptr;

private:
    bool isFormula(const std::wstring& formula);
    std::wstring ConvertFormulaArguments(const std::wstring& formula);
    /// @brief creating a style for the specified format
    /// @param format value format
    void createFormatStyle(const std::wstring &format);

	/// @brief Adding a custom column width for a cell
	/// @param pCell the cell for which the width will be added
	/// @param width the width value that will be set for the column if it is larger than the current one
	void addCustomColWidth(OOX::Spreadsheet::CCell *pCell, double width);

    /// @brief pointer to the cell being worked on
    OOX::Spreadsheet::CCell *pCell_;

    /// @brief map with data formats
    std::map<std::wstring, unsigned int> mapDataNumber_;

    /// @brief pointer to document styles
	OOX::Spreadsheet::CStyles *m_pStyles;

    /// @brief pointer to the resulting string value
    const std::wstring *value_;

    /// @brief locale identifier
    _INT32 lcid_;

    DigitReader digitReader_;
    DateReader dateReader_;
};
