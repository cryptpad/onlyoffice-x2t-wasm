/*
 * Browser x2t-wasm builds do not currently embed the JavaScript runtime that
 * real doctrenderer requires. Keep this explicit so unsupported doctrenderer
 * routes fail at conversion time instead of linking Emscripten missing-function
 * stubs that later produce corrupt downloads.
 */

#include "doctrenderer.h"

namespace NSDoctRenderer
{
	class CDoctRenderer_Private
	{
	};

	CDoctrenderer::CDoctrenderer(const std::wstring&)
		: m_pInternal(new CDoctRenderer_Private())
	{
	}

	void CDoctrenderer::LoadConfig(const std::wstring&, const std::wstring&)
	{
	}

	CDoctrenderer::~CDoctrenderer()
	{
		delete m_pInternal;
		m_pInternal = nullptr;
	}

	bool CDoctrenderer::Execute(const std::wstring&, std::wstring& strError)
	{
		strError = L"<result><error code=\"wasm_doctrenderer_unavailable\" /></result>";
		return false;
	}

	std::vector<std::wstring> CDoctrenderer::GetImagesInChanges()
	{
		return std::vector<std::wstring>();
	}

	void CDoctrenderer::CreateCache(const std::wstring&, const std::wstring&)
	{
	}

	void CDoctrenderer::CreateSnapshots()
	{
	}

	void CDoctrenderer::SetAdditionalParam(const AdditionalParamType&, void*)
	{
	}
}
