#include <Windows.h>
#include <tchar.h>

#include "DirectoryIterator.h"
#include "WinApiException.h"

DirectoryIterator::DirectoryIterator(const TCHAR *pattern)
	: m_searchHandle(::FindFirstFileEx(pattern, ::FindExInfoBasic, &m_findData, ::FindExSearchLimitToDirectories, nullptr, 0))
{
	if (m_searchHandle != INVALID_HANDLE_VALUE)
	{
		if (IsValid())
			m_value = m_findData.cFileName;
		else
			GetNext();
	}
	else
	{
		if (::GetLastError() == ERROR_FILE_NOT_FOUND)
			Close();
		else
			throw WinApiException::FromLastError();
	}
}

DirectoryIterator::~DirectoryIterator()
{
	Close();
}

void DirectoryIterator::Close()
{
	if (m_closed)
		return;

	if (m_searchHandle != INVALID_HANDLE_VALUE)
		::FindClose(m_searchHandle);

	m_closed = true;
}

void DirectoryIterator::GetNext()
{
	while (true)
	{
		if (::FindNextFile(m_searchHandle, &m_findData))
		{
			if (IsValid())
			{
				m_value = m_findData.cFileName;
				return;
			}
		}
		else
		{
			if (::GetLastError() == ERROR_NO_MORE_FILES)
			{
				Close();
				return;
			}
			else
				throw WinApiException::FromLastError();
		}
	} 
}

bool DirectoryIterator::IsValid()
{
	static const std::wstring current = _T(".");
	static const std::wstring parent = _T("..");

	return (m_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
		m_findData.cFileName != current &&
		m_findData.cFileName != parent;
}
