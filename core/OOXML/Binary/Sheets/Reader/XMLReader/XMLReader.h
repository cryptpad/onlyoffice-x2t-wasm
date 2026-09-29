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

#include "../../../../XlsxFormat/Xlsx.h"

/// @brief class that reads xml documents into xlsx
class XMLReader
{
public:

    /// @brief Reading a document
    /// @param FileName name of the xml file that will be read
    /// @param oXlsx Xlsx object of the table into which xml is read
    /// @return code for performing the operation
	_UINT32 Read(const std::wstring &sFileName, OOX::Spreadsheet::CXlsx &oXlsx);

    /// @brief Second version of the reading method
    /// @param FileName name of the xml file that will be read
    /// @param oXlsx Xlsx object of the table into which xml is read
    /// @param locale identifier for defining date formats
    /// @return code for performing the operation
    _UINT32 Read2(const std::wstring &sFileName, OOX::Spreadsheet::CXlsx &oXlsx, _INT32 lcid = -1);
};
