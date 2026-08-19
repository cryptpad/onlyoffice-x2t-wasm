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
#include <vector>

class DateReader
{
public:
    /// @brief creating a reader with the specified locale id
    /// @param lcid locale identifier depending on which the date will be read
	DateReader(_INT32 lcid = 9);

    /// @brief getting date as number in excel format
    /// @param date date in string format
    /// @param result result in excel format
    /// @return true if conversion is successful, false otherwise
    bool GetDigitalDate(const std::wstring &date, double &result, bool &Hasdate, bool &Hastime);


    /// @brief parsing a standardized date
    /// @param date date in string format
    /// @param result in tm format
    /// @return true if conversion is successful, false otherwise
    bool parseIsoDate(const std::wstring &date, tm &result);

    /// @brief parse string date with known locale
    /// @param date date in string format
    /// @param result in tm format
    /// @return true if conversion is successful, false otherwise
    bool parseLocalDate(const std::wstring &date, tm &result, bool &Hasdate, bool &Hastime);

private:
    /// @brief getting the date as a number in excel format from dates later than 1900
    /// @param datetime structure with date
    /// @return date in excel format
    _INT32 getStandartDate(tm date);

    /// @brief getting time as decimal part of double
    /// @param datetime structure with date and time
    /// @return time as the decimal part of a double number
    double getStandartTime(tm date);

    /// @brief getting a date as a number in excel format from dates from 1900 to 1970
    /// @param datetime structure with date
    /// @return date in excel format
    _INT32 getNonUnixDate(tm date);

    /// @brief normalization of the year to the excel standard
    /// @param year year either in the format yyyy - 2021 or in the format yy - 21
    /// @return number of years since 1900
    _INT32 normalizeYear(_INT32 year);

    /// @brief parsing am and pm parts of time
    /// @param buffer with characters
    /// @param date structure with date
    /// @return true if the string is part of am or pm
    bool parseAmPm(std::vector<wchar_t> &stringBuf, tm &date);

    /// @brief parsing the month name and putting it into the date
    /// @param buffer with characters
    /// @param date structure with date
    /// @return true if the string is a month name
    bool parseMonthName(std::vector<wchar_t> &stringBuf, tm &date);

    _INT32 lcid_ = 9;

    /// @brief cell counter
    _UINT16 cellCounter_ = 0;

    bool dateFound_ = false;
};

