#pragma once
#include <windows.h>
#include <string>
#include <memory>

class JunctionReparseData
{
	static const size_t REPARSE_DATA_HEADER_SIZE = sizeof(__int32) + 2 * sizeof(__int16);
	static const size_t REPARSE_MOUNTPOINT_HEADER_SIZE = sizeof(__int16) * 4;

	static const size_t PATH_BUFFER_SIZE = (MAXIMUM_REPARSE_DATA_BUFFER_SIZE - (REPARSE_DATA_HEADER_SIZE + REPARSE_MOUNTPOINT_HEADER_SIZE)) / sizeof(WCHAR);

	__int32 m_reparseTag = IO_REPARSE_TAG_MOUNT_POINT;
	__int16 m_reparseDataLength = REPARSE_MOUNTPOINT_HEADER_SIZE + sizeof(WCHAR) * PATH_BUFFER_SIZE;
	const __int16 m_reserved = 0;
	__int16 m_substituteNameOffset = 0;
	__int16 m_substituteNameLength = 0;
	__int16 m_printNameOffset = 0;
	__int16 m_printNameLength = 0;

	WCHAR m_pathBuffer[PATH_BUFFER_SIZE] = { 0 };

	JunctionReparseData() noexcept
	{ }

	JunctionReparseData(const TCHAR *pSubstitute);

public:

	// these are too big for the stack
	static std::unique_ptr<JunctionReparseData> Create()
	{
		return std::unique_ptr<JunctionReparseData>(new JunctionReparseData());
	}

	static std::unique_ptr<JunctionReparseData> Create(const TCHAR *pSubstitute)
	{
		return std::unique_ptr<JunctionReparseData>(new JunctionReparseData(pSubstitute));
	}

	std::wstring GetSubstituteName() const
	{
		return std::wstring(m_pathBuffer + m_substituteNameOffset, m_pathBuffer + m_substituteNameLength).substr(4);
	}

	size_t GetTotalSize() const
	{
		return m_reparseDataLength + REPARSE_DATA_HEADER_SIZE;
	}

private:
	static std::wstring GetFullPath(const TCHAR *pPath);
};