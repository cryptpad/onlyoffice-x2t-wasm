#include "CNode.h"

#include <utility>

#ifdef CSS_CALCULATOR_WITH_XHTML
#include "CCompiledStyle.h"
#endif

namespace NSCSS
{
	CNode::CNode()
	#ifdef CSS_CALCULATOR_WITH_XHTML
		: m_pCompiledStyle(new CCompiledStyle())
    #endif
	{}

	CNode::CNode(bool bCreateCompiledStyle)
	#ifdef CSS_CALCULATOR_WITH_XHTML
		: m_pCompiledStyle(bCreateCompiledStyle ? new CCompiledStyle() : nullptr)
	#endif
	{}

	CNode::CNode(const CNode& oNode)
		: m_wsName(oNode.m_wsName), m_wsClass(oNode.m_wsClass), m_wsId(oNode.m_wsId),
	      m_wsStyle(oNode.m_wsStyle), m_mAttributes(oNode.m_mAttributes)
	{
		#ifdef CSS_CALCULATOR_WITH_XHTML
		m_pCompiledStyle = nullptr != oNode.m_pCompiledStyle ? new CCompiledStyle(*oNode.m_pCompiledStyle) : nullptr;
		#endif
	}

	CNode::CNode(CNode&& oNode) noexcept
		: m_wsName(std::move(oNode.m_wsName)), m_wsClass(std::move(oNode.m_wsClass)), m_wsId(std::move(oNode.m_wsId)),
	      m_wsStyle(std::move(oNode.m_wsStyle)), m_mAttributes(std::move(oNode.m_mAttributes))
	{
		#ifdef CSS_CALCULATOR_WITH_XHTML
		m_pCompiledStyle = oNode.m_pCompiledStyle;
		oNode.m_pCompiledStyle = nullptr;
		#endif
	}

	CNode::CNode(const std::wstring& wsName, const std::wstring& wsClass, const std::wstring& wsId, bool bCreateCompiledStyle)
		: m_wsName(wsName), m_wsClass(wsClass), m_wsId(wsId)
	    #ifdef CSS_CALCULATOR_WITH_XHTML
	    , m_pCompiledStyle(bCreateCompiledStyle ? new CCompiledStyle() : nullptr)
		#endif
	{}

	CNode::~CNode()
	{
		#ifdef CSS_CALCULATOR_WITH_XHTML
		if (nullptr != m_pCompiledStyle)
			delete m_pCompiledStyle;
		#endif
	}

	CNode& CNode::operator=(const CNode& oNode)
	{
		if (this == &oNode)
			return *this;

		m_wsName       = oNode.m_wsName;
		m_wsClass      = oNode.m_wsClass;
		m_wsId         = oNode.m_wsId;
		m_wsStyle      = oNode.m_wsStyle;
		m_mAttributes  = oNode.m_mAttributes;

		#ifdef CSS_CALCULATOR_WITH_XHTML
		if (nullptr != m_pCompiledStyle)
			delete m_pCompiledStyle;

		m_pCompiledStyle = nullptr != oNode.m_pCompiledStyle ? new CCompiledStyle(*oNode.m_pCompiledStyle) : nullptr;
		#endif

		return *this;
	}

	CNode& CNode::operator=(CNode&& oNode) noexcept
	{
		if (this == &oNode)
			return *this;

		m_wsName       = std::move(oNode.m_wsName);
		m_wsClass      = std::move(oNode.m_wsClass);
		m_wsId         = std::move(oNode.m_wsId);
		m_wsStyle      = std::move(oNode.m_wsStyle);
		m_mAttributes  = std::move(oNode.m_mAttributes);

		#ifdef CSS_CALCULATOR_WITH_XHTML
		if (nullptr != m_pCompiledStyle)
			delete m_pCompiledStyle;

		m_pCompiledStyle = oNode.m_pCompiledStyle;
		oNode.m_pCompiledStyle = nullptr;
		#endif

		return *this;
	}

	bool CNode::Empty() const
	{
		return m_wsName.empty() && m_wsClass.empty() && m_wsId.empty() && m_wsStyle.empty();
	}

	bool CNode::GetAttributeValue(const std::wstring& wsAttributeName, std::wstring& wsAttributeValue) const
	{
		const std::map<std::wstring, std::wstring>::const_iterator itFound{m_mAttributes.find(wsAttributeName)};

		if (m_mAttributes.cend() == itFound)
			return false;

		wsAttributeValue = itFound->second;
		return true;
	}

	std::wstring CNode::GetAttributeValue(const std::wstring& wsAttributeName) const
	{
		const std::map<std::wstring, std::wstring>::const_iterator itFound{m_mAttributes.find(wsAttributeName)};
		return (m_mAttributes.cend() != itFound) ? itFound->second : std::wstring();
	}

	#ifdef CSS_CALCULATOR_WITH_XHTML
	void CNode::SetCompiledStyle(CCompiledStyle* pCompiledStyle)
	{
		if (nullptr != m_pCompiledStyle)
			delete m_pCompiledStyle;

		if (nullptr == pCompiledStyle)
		{
			m_pCompiledStyle = nullptr;
			return;
		}

		m_pCompiledStyle = new CCompiledStyle(*pCompiledStyle);
	}
	#endif

	void CNode::Clear()
	{
		m_wsName     .clear();
		m_wsClass    .clear();
		m_wsId       .clear();
		m_wsStyle    .clear();
		m_mAttributes.clear();
	}

	std::vector<std::wstring> CNode::GetData() const
	{
		std::vector<std::wstring> arValues;
		if (!m_wsClass.empty())
			arValues.push_back(m_wsClass);
		if (!m_wsName.empty())
			arValues.push_back(m_wsName);
		return arValues;
	}

	bool CNode::operator<(const CNode& oNode) const
	{
		if(m_wsName != oNode.m_wsName)
			return m_wsName < oNode.m_wsName;

		if(m_wsClass != oNode.m_wsClass)
			return m_wsClass < oNode.m_wsClass;

		if(m_wsId != oNode.m_wsId)
			return m_wsId < oNode.m_wsId;

		if(m_wsStyle != oNode.m_wsStyle)
			return m_wsStyle < oNode.m_wsStyle;

		if (m_mAttributes.size() != oNode.m_mAttributes.size())
			return m_mAttributes.size() < oNode.m_mAttributes.size();

		if (m_mAttributes != oNode.m_mAttributes)
			return m_mAttributes < oNode.m_mAttributes;

		return false;
	}

	bool CNode::operator==(const CNode& oNode) const
	{
		return((m_wsName == oNode.m_wsName)   &&
		       (m_wsClass == oNode.m_wsClass) &&
		       (m_wsStyle == oNode.m_wsStyle) &&
		       (m_mAttributes == oNode.m_mAttributes));
	}
}
