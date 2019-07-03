#include <Windows.h>
#include <tchar.h>
#include "DirectoryIterator.h"

DirectoryIterator::DirectoryIterator(const TCHAR *pattern)
	: _searchHandle(FindFirstFileEx(pattern, ::FindExInfoBasic, &_findData, ::FindExSearchLimitToDirectories, nullptr, 0))
{
	if (_searchHandle != INVALID_HANDLE_VALUE)
		_value = _findData.cFileName;
	else
		Close();
}

DirectoryIterator::~DirectoryIterator()
{
	Close();
}

void DirectoryIterator::Close()
{
	if (_searchHandle != INVALID_HANDLE_VALUE)
		FindClose(_searchHandle);

	_closed = true;
}

void DirectoryIterator::GetNextFile()
{
	do
	{
		if (FindNextFile(_searchHandle, &_findData))
			_value = _findData.cFileName;
	} while (!(_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));


	{
		_value.clear();
		Close();
	}
}

bool DirectoryIterator::IsValid(WIN32_FIND_DATA *data)
{
	const TCHAR *current = _T(".");
	const TCHAR *parent = _T("..");

	return (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && _value != current && _value != parent;
}
