﻿/*
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
 * You can contact Ascensio System SIA at 20A-6 Ernesta Birznieka-Upish
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "Sxvd.h"

namespace XLS
{

Sxvd::Sxvd()
{
	cchName = 0;
}


Sxvd::~Sxvd()
{
}

BaseObjectPtr Sxvd::clone()
{
	return BaseObjectPtr(new Sxvd(*this));
}

void Sxvd::readFields(CFRecord& record)
{
	short flags;
	record >> sxaxis >> cSub >> flags;
	
	fDefault	= GETBIT(flags, 0);
	fSum		= GETBIT(flags, 1);
	fCounta		= GETBIT(flags, 2);
	fAverage	= GETBIT(flags, 3);
	fMax		= GETBIT(flags, 4);
	fMin		= GETBIT(flags, 5);
	fProduct	= GETBIT(flags, 6);
	fCount		= GETBIT(flags, 7);
	fStdev		= GETBIT(flags, 8);
	fStdevp		= GETBIT(flags, 9);
	fVariance	= GETBIT(flags, 10);
	fVariancep	= GETBIT(flags, 11);

	record >> cItm >> cchName;

	if(cchName && cchName != 0xffff)
	{
		stName.setSize(cchName);
		record >> stName;
	}
	int skip = record.getDataSize() - record.getRdPtr();
	record.skipNunBytes(skip);}

} // namespace XLS
