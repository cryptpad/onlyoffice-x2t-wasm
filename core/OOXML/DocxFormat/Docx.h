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

#include "IFileContainer.h"
#include "../../DesktopEditor/common/Directory.h"

#if !defined(_WIN32) && !defined (_WIN64)
#include <sys/stat.h>
#endif

namespace PPTX
{
	class Theme;
}
namespace OOX
{
	class CApp;
	class CCore;
	class CDocument;
	class CFontTable;
	class CNumbering;
	class CStyles;
	class CFootnotes;
	class CEndnotes;
	class CSettings;
	class CComments;
	class CCommentsExt;
	class CCommentsExtensible;
	class CCommentsUserData;
	class CCommentsIds;
	class CPeople;
	class CDocumentComments;
	class CDocumentCommentsExt;
	class CDocumentCommentsExtensible;
	class CDocumentPeople;
	class CDocumentCommentsIds;
	class VbaProject;
	class JsaProject;
	class CHdrFtr;

	class CDocx : public OOX::Document, public OOX::IFileContainer
	{
	public:
		struct _part_summary
		{
			OOX::CDocument		*document = NULL;					// Main/document.xml
			OOX::CFontTable		*fontTable = NULL;					// Font table /fonttable.xml
			OOX::CNumbering		*numbering = NULL;					// Numbering /numbering.xml
			OOX::CStyles		*styles = NULL;						// Styles/styles.xml
			OOX::CFootnotes		*footnotes = NULL;					// Footnotes /footnotes.xml
			OOX::CEndnotes		*endnotes = NULL;					// Endnotes/endnotes.xml
			OOX::CSettings		*settings = NULL;					// Settings/settings.xml
			OOX::CComments		*comments = NULL;					// Comments/comments.xml

			void init();
		};

		CDocx();
		CDocx(const CPath& oFilePath);
		virtual ~CDocx();

        bool Read(const CPath& oFilePath);
		void FixAfterRead();
		bool Write(const CPath& oFilePath);

		OOX::CHdrFtr *GetHeaderOrFooter(const OOX::RId& rId, bool glossary = false) const;
		const std::wstring GetCustomSettings() const;
		
		OOX::CApp			*m_pApp;
		OOX::CCore			*m_pCore;

		_part_summary		m_oMain;			// Main document word/
		_part_summary		m_oGlossary;		// Glossary Document word/glossary/

		// TODO make a structural object - the main document and subordinates - as soon as something other than glossary appears
		bool m_bGlossaryRead;

		OOX::CCommentsExt	*m_pCommentsExt;				// word/commentsExtended.xml
		OOX::CCommentsExtensible	*m_pCommentsExtensible;	// word/commentsExtensible.xml
		OOX::CCommentsUserData		*m_pCommentsUserData;	// word/commentsUserData.xml
		OOX::CCommentsIds			*m_pCommentsIds;		// word/commentsIds.xml
		OOX::CPeople				*m_pPeople;				// word/people.xml
		OOX::CDocumentComments		*m_pDocumentComments;   // word/documentComments.xml
		OOX::CDocumentCommentsExt	*m_pDocumentCommentsExt;// word/documentCommentsExtended.xml
		OOX::CDocumentCommentsExtensible	*m_pDocumentCommentsExtensible;//	word/documentCommentsExtensible.xml
		OOX::CDocumentPeople		*m_pDocumentPeople;		// word/documentPeople.xml
		OOX::CDocumentCommentsIds	*m_pDocumentCommentsIds;// word/documentCommentsIds.xml
		
		OOX::VbaProject		*m_pVbaProject;
		OOX::JsaProject		*m_pJsaProject;
		
		PPTX::Theme			*m_pTheme;

private:
		void init();
	};
} // OOX
