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

#include "BopPopCustom.h"

namespace XLS
{

BopPopCustom::BopPopCustom()
{
}


BopPopCustom::~BopPopCustom()
{
}


BaseObjectPtr BopPopCustom::clone()
{
	return BaseObjectPtr(new BopPopCustom(*this));
}


void BopPopCustom::readFields(CFRecord& record)
{
	record >> rggrbit;
}

void BopPopCustom::writeFields(CFRecord& record)
{
    record << rggrbit;
}

BiffStructurePtr BopPopCustomPiesIndices::clone()
{
	return BiffStructurePtr(new BopPopCustomPiesIndices(*this));
}


void BopPopCustomPiesIndices::load(CFRecord& record)
{
	record >> cxi;

	const unsigned short padding = 8 - cxi % 8;

	unsigned char bit_data = 0;

	for(unsigned short i = padding; i < cxi - 1 + padding; i++)
	{
		if(0 == i % 8 || padding == i)
		{
			record >> bit_data;
		}

		unsigned char mask = 1 << (7 - i % 8);

		if(0 != (bit_data & mask))
		{
			pie_indices.push_back(i - padding);
		}
	}
}

void BopPopCustomPiesIndices::save(CFRecord& record)
{
   // 1. Save the number of points
    record << cxi;

    const unsigned short padding = (8 - (cxi % 8)) % 8;
    const unsigned short total_bits = padding + cxi + 1; // +1 = final flag bit
    const unsigned short total_bytes = (total_bits + 7) / 8;

    // 2. Create an array of zero bytes
    std::vector<unsigned char> rggrbit(total_bytes, 0);

    // 3. Set the dot bits
    for (unsigned short idx : pie_indices)
    {
        if (idx >= cxi)
            continue; // ignore incorrect indexes

        unsigned short bit_pos = padding + idx;
        unsigned short byte_index = bit_pos / 8;
        unsigned short bit_in_byte = 7 - (bit_pos % 8); // MSB-first

        rggrbit[byte_index] |= (1 << bit_in_byte);
    }

    // 4. Set the final bit (the last bit of the last byte)
    bool no_secondary = pie_indices.empty();
    if (no_secondary)
    {
        rggrbit.back() |= 0x01; // LSB = 1
    }

    // 5. Write all the bytes to the stream
    for (unsigned char b : rggrbit)
    {
        record << b;
    }
}


} // namespace XLS

