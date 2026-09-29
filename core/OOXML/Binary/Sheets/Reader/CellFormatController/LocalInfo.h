/*
 * (c) Copyright Ascensio System SIA 2010-2024
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
#include <vector>

namespace lcInfo
{

/// @brief class containing information about the locale and the standards used in it
class LocalInfo
{
public:

    /// @brief collect short date format from template
    /// @return a pattern of numbers that determine the order of date elements where 0-1 days 2-3 months 4-5 years
    std::wstring GetShortDateFormat();

    /// @brief get the month names in this locale
    /// @param index number from the list of months
    /// @param shortName whether a short name is requested
    /// @return vector of names of months starting with January
    std::vector<std::wstring> GetMonthNames(const _INT16 &index, const bool isShortName = false);

    /// @brief collect short date format from template
    /// @return month number starting from zero if successful, negative number if unsuccessful
    _INT16 GetMonthNumber(const std::wstring &monthName,  const bool isShortName = false);

    /// @brief get the string name of the month in this locale
    /// @param index number of the requested month
    /// @param shortName whether a short name is requested
    /// @return month name
    std::wstring GetLocMonthName(const _INT16 &index, bool shortName = false);

    /// @brief id of locale
    _INT32 lcid;

    /// @brief locale name
    std::wstring Name;

    /// @brief date separator
    std::wstring DateSeparator;

    /// @brief abbreviated date
    std::wstring ShortDatePattern;

    /// @brief local month names
    _INT16 MonthNamesIndex;

    /// @brief maximum characters in shortened month length
    _INT16 MonthAbrvLen;
};

/// @brief getting information about a locale by its id
LocalInfo getLocalInfo(const _INT32 lcid);

}
