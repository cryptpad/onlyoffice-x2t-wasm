﻿/*
 * (c) Copyright Ascensio System SIA 2010-2019
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
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
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

#include "math_elementaries.h"

#include <xml/xmlchar.h>
#include <xml/attributes.h>


namespace cpdoccore { 

	using namespace odf_types;

namespace odf_writer {

//----------------------------------------------------------------------------------------------------
const wchar_t * math_mstack::ns	= L"math";
const wchar_t * math_mstack::name	= L"mstack";
//----------------------------------------------------------------------------------------------------

void math_mstack::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_mstack::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_mstack::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}



//----------------------------------------------------------------------------------------------------
const wchar_t * math_msrow::ns	= L"math";
const wchar_t * math_msrow::name	= L"msrow";
//----------------------------------------------------------------------------------------------------

void math_msrow::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_msrow::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_msrow::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------
const wchar_t * math_msline::ns	= L"math";
const wchar_t * math_msline::name	= L"msline";
//----------------------------------------------------------------------------------------------------

void math_msline::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_msline::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_msline::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}

//---------------------------------------------------------------
const wchar_t * math_msgroup::ns	= L"math";
const wchar_t * math_msgroup::name	= L"msgroup";
//----------------------------------------------------------------------------------------------------

void math_msgroup::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_msgroup::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_msgroup::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}



//---------------------------------------------------------------
const wchar_t * math_mlongdiv::ns	= L"math";
const wchar_t * math_mlongdiv::name	= L"mlongdiv";
//----------------------------------------------------------------------------------------------------

void math_mlongdiv::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_mlongdiv::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_mlongdiv::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}

//---------------------------------------------------------------
const wchar_t * math_mscarry::ns	= L"math";
const wchar_t * math_mscarry::name	= L"mscarry";
//----------------------------------------------------------------------------------------------------

void math_mscarry::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_mscarry::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_mscarry::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}


//---------------------------------------------------------------
const wchar_t * math_mscarries::ns		= L"math";
const wchar_t * math_mscarries::name	= L"mscarries";
//----------------------------------------------------------------------------------------------------

void math_mscarries::create_child_element(const std::wstring & Ns, const std::wstring & Name)
{
	CP_CREATE_ELEMENT(content_);
}

void math_mscarries::add_child_element(const office_element_ptr & child_element)
{
	content_.push_back(child_element);
}

void math_mscarries::serialize(std::wostream & _Wostream)
{
	CP_XML_WRITER(_Wostream)
	{
		CP_XML_NODE_SIMPLE_NONS()
		{
			for (size_t i = 0; i < content_.size(); i++)
			{
				if (!content_[i]) continue;
				content_[i]->serialize(CP_XML_STREAM());
			}
		}
	}
}

//---------------------------------------------------------------

}
}
