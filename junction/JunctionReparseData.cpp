#include <memory>

#include "JunctionReparseData.h"
#include "WinApiException.h"

JunctionReparseData::JunctionReparseData(const WCHAR *pSubstitute)
{
	const WCHAR *pPerUserDevicePrefix = L"\\??\\";
	std::wstring strSubstituteName = pPerUserDevicePrefix + GetFullPath(pSubstitute);

	std::copy(std::begin(strSubstituteName), std::end(strSubstituteName), m_pathBuffer);

	m_substituteNameOffset = 0;
	m_substituteNameLength = static_cast<__int16>(strSubstituteName.length() * sizeof(WCHAR));

	// print name is not set; powershell and mklink also don't do it

	m_printNameOffset = m_substituteNameLength + 1 * sizeof(WCHAR);
	m_printNameLength = 0;

	m_reparseDataLength = (m_printNameOffset + m_printNameLength) + 1 * sizeof(WCHAR) + REPARSE_MOUNTPOINT_HEADER_SIZE;
}

std::wstring JunctionReparseData::GetFullPath(const TCHAR *pPath)
{
	size_t szPath = ::GetFullPathName(pPath, 0, nullptr, nullptr);
	if (!szPath)
		throw WinApiException::FromLastError();

	std::unique_ptr<TCHAR> buffer(new TCHAR[szPath]);
	::GetFullPathName(pPath, szPath, buffer.get(), nullptr);

	auto result = std::wstring(buffer.get());
	return result;
}
