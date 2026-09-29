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
#ifndef _ASC_FONTCONVERTER_STRING_EXT_H_
#define _ASC_FONTCONVERTER_STRING_EXT_H_

#include <stdarg.h>

namespace NSFontConverter
{
    //---------------------------------------------------------------------------------------
    // class StringExt - analogue of CString
    //---------------------------------------------------------------------------------------

    class StringExt
    {
    public:

        // Create an empty string.
        StringExt();

        // Create a string from a C-string.
        StringExt(const char *sString);

        // Create a string of <nLength> characters in <sString>. This string
        // may contain null characters.
        StringExt(const char *sString, int nLength);

        // Create a string of <nLength> characters, starting with <nIndex>, string <seString>.
        StringExt(StringExt *seString, int nIndex, int nLength);

        // Copy the string.
        StringExt(StringExt *seString);
        StringExt *Copy()
        {
            return new StringExt(this);
        }

        // Concatenate two strings.
        StringExt(StringExt *seString1, StringExt *seString2);

        // Convert the integer value to a string.
        static StringExt *FromInt(int nValue);

        // Create a formatted string. Function similar to printf, but without the problems
        // with buffer overflow. The format looks like this:
        //     {<nArg>:[<nWidth>][.<precision>]<type>}
        // where:
        // - <nArg> argument number (numbering starts from 0).
        // -- PS: the arguments themselves must be in order, but they can be used
        //    repeatedly and in any order.
        // - <nWidth> field width, if it is negative then the alignment will
        //   be reversed, and the empty spaces will be filled with zeros.
        // - <nPrecision> number of decimal places
        // - <nType> type is one of the following:
        //     d, x, o, b -- integer (int) in decimal, hexadecimal, octal
        //                   and binary systems
        //     ud, ux, uo, ub -- the same thing, only unsigned integer (uint)
        //     ld, lx, lo, lb, uld, ulx, ulo, ulb -- similar to long and ulong
        //     f, g -- double
        //     c -- char
        //     s -- string (char *)
        //     t -- StringExt *
        //     w -- Spaces; the value argument specifies the number of spaces
        // To output curly braces, use {{ and }}.
        static StringExt *Format (char *sFormat, ...);
        static StringExt *FormatV(char *sFormat, va_list sArgList);

        // Destructor.
        ~StringExt();

        int GetLength()
        {
            return m_nLength;
        }

        // Return a string as char*.
        char *GetBuffer()
        {
            return m_sData;
        }

        char GetAt(int nIndex)
        {
            return m_sData[ nIndex ];
        }
        void SetAt(int nIndex, char nChar)
        {
            m_sData[ nIndex ] = nChar;
        }

        // Clear the string.
        StringExt *Clear();

        // Add a character or string.
        StringExt *Append(char nChar);
        StringExt *Append(StringExt *seString);
        StringExt *Append(const char *sString);
        StringExt *Append(const char *sString, int nLength);

        // Add a formatted string.
        StringExt *AppendFormat (char *sFormat, ...);
        StringExt *AppendFormatV(char *sFormat, va_list sArgList);

        // Insert a character or string.
        StringExt *Insert(int nIndex, char nChar);
        StringExt *Insert(int nIndex, StringExt  *seString);
        StringExt *Insert(int nIndex, const char *sString);
        StringExt *Insert(int nIndex, const char *sString, int nLength);

        // Delete one character or an array of characters.
        StringExt *Delete(int nIndex, int nCount = 1);

        // Make all the characters in the string in uppercase/lowercase.
        StringExt *MakeUpper();
        StringExt *MakeLower();

        // Comparing two strings: -1:< 0:= +1:>
        int Compare (StringExt *seString);
        int CompareN(StringExt *seString, int nCount);
        int Compare (const char *sString);
        int CompareN(const char *sString, int nCount);

    private:

        void Resize(int nLength);

        static void FormatInt   (         long nValue, char *sBuffer, int nBufferSize, bool bZeroFill, int nWidth, int nBase, char **ppData, int *nLen);
        static void FormatUInt  (unsigned long nValue, char *sBuffer, int nBufferSize, bool bZeroFill, int nWidth, int nBase, char **ppData, int *nLen);
        static void FormatDouble(       double nValue, char *sBuffer, int nBufferSize, int nPrecision, bool bTrim,            char **ppData, int *nLen);

    private:

        int   m_nLength;
        char *m_sData;

    };
}

#endif /* _ASC_FONTCONVERTER_STRING_EXT_H_ */
