#ifndef IWRITER_H
#define IWRITER_H

#include "../../Common/3dParty/html/css/src/CNode.h"
#include "../Common.h"

namespace HTML
{
class IWriter
{
public:
	IWriter() = default;
	virtual ~IWriter() = default;

	virtual void Begin(const std::wstring& wsDst) = 0;
	virtual void End(const std::wstring& wsDst) = 0;

	virtual bool WriteText(std::wstring wsText, const std::vector<NSCSS::CNode>& arSelectors) = 0;

	virtual void WriteEmptyParagraph(bool bVahish = false, bool bInP = false) = 0;

	virtual void PageBreak() = 0;

	virtual void BeginBlock() = 0;
	virtual void EndBlock(bool bAddBlock) = 0;

	virtual void SetDataOutput(XmlString* pOutputData) = 0; // Setting the output location for the interpreter
	virtual void RevertDataOutput() = 0; // Returning the output location to the original one

	virtual XmlString* GetCurrentDocument() const = 0;

	//TODO:: move handling of nested tables to conversion after changing the principle of working with tables
	virtual bool SupportNestedTables() const = 0;
};
}

#endif // IWRITER_H
