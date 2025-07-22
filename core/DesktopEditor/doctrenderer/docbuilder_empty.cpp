/*
 * TODOCP license?
 */

#include <iostream>
#include <cstdlib>
#include "docbuilder.h"

namespace NSDoctRenderer
{
	CDocBuilder::CDocBuilder()
	{
	}
	CDocBuilder::~CDocBuilder()
	{
	}

	int CDocBuilder::OpenFile(const wchar_t* path, const wchar_t* params)
	{
		std::cerr << "CDocBuilder::OpenFile not implemented" << std::endl;
    exit(1);
	}
	int CDocBuilder::SaveFile(const int& type, const wchar_t* path, const wchar_t* params)
	{
		std::cerr << "CDocBuilder::SaveFile not implemented" << std::endl;
    exit(1);
	}
	int CDocBuilder::SaveFile(const wchar_t* extension, const wchar_t* path, const wchar_t* params)
	{
		std::cerr << "CDocBuilder::SaveFile not implemented" << std::endl;
    exit(1);
	}
	bool CDocBuilder::ExecuteCommand(const wchar_t* command, CDocBuilderValue* retValue)
	{
		std::cerr << "CDocBuilder::ExecuteCommand not implemented" << std::endl;
    exit(1);
	}

	CDocBuilderContext CDocBuilder::GetContext(bool enterContext)
	{
		std::cerr << "CDocBuilder::GetContext not implemented" << std::endl;
    exit(1);
	}
}
