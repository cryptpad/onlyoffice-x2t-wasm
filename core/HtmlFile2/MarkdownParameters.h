#ifndef MARKDOWNPARAMETERS_H
#define MARKDOWNPARAMETERS_H

namespace HTML
{
struct TMarkdownParameters
{
	bool m_bUseAlternativeHTMLTags = false; //Use html tags where there is no standard implementation in md (for example, for underlines)
	wchar_t m_wchUnorderedList     = L'-'; // Possible options in md: -, +, *
	wchar_t m_wchOrderedList       = L'.'; // Possible options in md: ., )
};
}

#endif // MARKDOWNPARAMETERS_H
