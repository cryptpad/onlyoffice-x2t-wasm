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

#include "../../../../OOXML/Base/Types_32.h"
#include "../../../../Common/3dParty/pole/pole.h"
#include "Enums.h"

#include <vector>

// this is a class used to transfer properties of objects,
// for example, a pointer to an image... (by PID)

class CProperty
{
public:
    ODRAW::ePropertyId				m_ePID;
    bool							m_bIsBlip;
    bool							m_bComplex;
    _UINT32							m_lValue;
    unsigned char*					m_pOptions;
    // so as not to create classes - this is value when m_bComplex == true
    bool							m_bIsTruncated;

	CProperty();
	~CProperty();

	void FromStream(POLE::Stream* pStream);
	void ComplexFromStream(POLE::Stream* pStream);
};

// And here is the property container
class CProperties
{
public:
    std::vector<CProperty> m_arProperties;
    // in theory this is an instance, but it's more convenient for us,
    // Moreover, this is a class - not related to RecordHeader
    size_t m_lCount;

	CProperties();
	~CProperties();

	void FromStream(POLE::Stream* pStream, long lCount);
	size_t GetLen();
};
