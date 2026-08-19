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

#include <string>

#include "CPSharedPtr.h"
#include "xml/nodetype.h"

namespace cpdoccore { 

	namespace xml {

		class sax;
		class attributes;

		typedef attributes attributes_wc;
		typedef shared_ptr< attributes_wc >::Type attributes_wc_ptr;

	}
	namespace common 
	{

	// Base class for an element that can be read by sax-reader
	// Methods will be called for each element
	// add_attributes, add_child_element, add_text as callbacks for reading the corresponding data

	class read_doc_element 
	{
	public:
		bool read_sax( xml::sax * Reader);
		virtual ~read_doc_element() = 0; 

		virtual void add_child_element	( xml::sax * Reader, const std::wstring & Ns, const std::wstring & Name) = 0;
		virtual void add_attributes		(const xml::attributes_wc_ptr & Attributes) = 0;
	private:
		virtual void add_text			(const std::wstring & Text) = 0;
		virtual void add_space			(const std::wstring & Text) = 0;
	};

	inline read_doc_element::~read_doc_element()
	{
	}

	}
}
