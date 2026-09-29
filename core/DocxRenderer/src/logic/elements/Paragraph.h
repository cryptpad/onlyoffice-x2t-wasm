#pragma once
#include "BaseItem.h"
#include "TextLine.h"

namespace NSDocxRenderer
{
	class CParagraph : public CBaseItem, public IOoxmlItem
	{
	public:
		enum TextAlignmentType
		{
			tatUnknown,
			tatByLeft,
			tatByCenter,
			tatByRight,
			tatByWidth
		};

		// text frame properties
		bool                m_bIsNeedFirstLineIndent{false};
		bool                m_bIsShadingPresent     {false};
		LONG                m_lColorOfShadingFill   {c_iWhiteColor}; //BGR
		TextAlignmentType   m_eTextAlignmentType    {tatUnknown};

		// geometry paragraph
		double m_dLeftBorder {0.0}; // shift relative to the left edge of the page/shape/table
		double m_dRightBorder{0.0}; // shift relative to the right edge of the page/shape/table
		double m_dFirstLine  {0.0}; // offset relative to m_dLeftBorder

		double m_dSpaceBefore{0.0}; // the default is 0 if w:before is missing
		double m_dSpaceAfter {0.0}; // shape defaults to 8pt if w:after is missing
		double m_dLineHeight {0.0};

		std::vector<std::shared_ptr<CTextLine>> m_arTextLines;
		std::wstring m_wsStyleId;

	public:
		CParagraph() : CBaseItem() {}
		virtual ~CParagraph();
		virtual void Clear();
		virtual void ToXml(NSStringUtils::CStringBuilder& oWriter) const override final;
		virtual void ToXmlPptx(NSStringUtils::CStringBuilder& oWriter) const override final;
		virtual void ToBin(NSWasm::CData& oWriter) const override final;

		void RemoveHighlightColor();
		void MergeLines();
	};
}
