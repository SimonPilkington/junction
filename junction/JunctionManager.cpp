#include "JunctionManager.h"
#include <iostream>

std::unique_ptr<JunctionReparseData> JunctionManager::GetJunctionData() const
{
	std::unique_ptr<JunctionReparseData> data = JunctionReparseData::Create();

	DWORD bytesReturned;
	if (!::DeviceIoControl(&m_dirTarget.GetHandle(), FSCTL_GET_REPARSE_POINT, nullptr, 0, data.get(), sizeof(JunctionReparseData), &bytesReturned, nullptr))
		return std::unique_ptr<JunctionReparseData>();

	return data;
}

void JunctionManager::CreateJunction(const TCHAR *pTarget) const
{
	const std::unique_ptr<JunctionReparseData> data = JunctionReparseData::Create(pTarget);

	DWORD bytesReturned;
	if (!::DeviceIoControl(&m_dirTarget.GetHandle(), FSCTL_SET_REPARSE_POINT, data.get(), static_cast<DWORD>(data->GetTotalSize()), nullptr, 0, &bytesReturned, nullptr))
		throw WinApiException::FromLastError();
}
