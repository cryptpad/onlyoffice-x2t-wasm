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

#include <string>
#include <chrono>

class DigitReader
{
public:
    /// @brief reading the number
    /// @param value read text value
    /// @param digit a string with a numeric value
    /// @param format string with number format
    /// @return true the value is converted to a number, otherwise false
    bool ReadDigit(const std::wstring &value, std::wstring &digit, std::wstring &format);

    /// @brief reading a number in scientific format
    /// @param value read text value
    /// @param digit a string with a numeric value
    /// @param format string with number format
    /// @return true the value is converted to a number, otherwise false
    bool ReadScientific(const std::wstring &value, std::wstring &digit, std::wstring &format);

private:
    std::wstring createFractionFormat(const std::wstring &value, const std::wstring &postfix);

    bool checkCommonFractionFormat(const double &numerator, const std::wstring &postfix, double &dvalue, std::wstring &format);

    bool scientificFound_ = false;
    _UINT16 nonscientificCellsCounter_ = 0;
};
