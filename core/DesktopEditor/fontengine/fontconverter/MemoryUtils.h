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
#ifndef _ASC_FONT_CONVERTER_MEMORY_UTILS_H_
#define _ASC_FONT_CONVERTER_MEMORY_UTILS_H_

#include <stdio.h>
#include <limits>
#include <string>
#include <stdlib.h>

#ifdef __linux__
    #include <string.h>
#endif

namespace NSFontConverter
{
    //------------------------------------------------------------------------
    // Similar to malloc, but with error handling.
    static void *MemUtilsMalloc(int nSize)
    {
        void *pResult;

        if ( nSize <= 0 )
            return NULL;

        if ( !( pResult = malloc( nSize ) ) )
        {
            // TO DO: Throw a memory allocation error
        }
        return pResult;
    }


    // Same as realloc, but with error handling.
    // If <pData> is NULL, malloc is called instead of realloc.
    static void *MemUtilsRealloc(void *pData, int nSize)
    {
        void *pResult;

        if ( nSize <= 0 )
        {
            if ( pData )
                free( pData );
            return NULL;
        }
        if ( pData )
            pResult = realloc( pData, nSize);
        else
            pResult = malloc( nSize );
        if ( !pResult )
        {
            // TO DO: Throw a memory allocation error
        }
        return pResult;
    }


    // Same as MemUtilsMalloc and MemUtilsRelloc, only
    // takes into account the number of elements and the size of the element. As a result
    // Memory of size nObjectsCount * nObjectSize bytes is allocated.
    // In addition, there is error handling and checking that
    // the total size didn't exceed the limit for int.
    static void *MemUtilsMallocArray(int nObjectsCount, int nObjectSize)
    {
        if ( 0 == nObjectsCount )
            return NULL;

        int nSize = nObjectsCount * nObjectSize;
        if ( nObjectSize <= 0 || nObjectsCount < 0 || nObjectsCount >= 0x7fffffff / nObjectSize )
        {
            // TO DO: Throw a memory allocation error
        }
        return MemUtilsMalloc( nSize );
    }

    // Same as free, but checks and ignores NULL pointers.
    static void MemUtilsFree(void *pData)
    {
        if ( pData )
            free( pData );
    }

    static void *MemUtilsReallocArray(void *pData, int nObjectsCount, int nObjectSize)
    {
        if ( 0 == nObjectsCount )
        {
            if ( pData )
                MemUtilsFree( pData );
            return NULL;
        }
        int nSize = nObjectsCount * nObjectSize;

        if ( nObjectSize <= 0 || nObjectsCount < 0 || nObjectsCount >= 0x7fffffff / nObjectSize )
        {
            // TO DO: Throw a memory allocation error
        }
        return MemUtilsRealloc( pData, nSize );
    }

    // Allocate memory and copy the string there.
    static char *CopyString(char *sString)
    {
        char *sResult = (char *)MemUtilsMalloc( strlen( sString ) + 1 );
        strcpy( sResult, sString );
        return sResult;
    }
}

#endif /* _ASC_FONT_CONVERTER_MEMORY_UTILS_H_ */
