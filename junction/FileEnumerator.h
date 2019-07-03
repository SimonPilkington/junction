#pragma once

#include <tchar.h>
#include <string>
#include "FileIterator.h"

class FileEnumerator
{
private:
	std::wstring _pattern;

public:
	FileEnumerator(const TCHAR *pattern)
		: _pattern(pattern)
	{ }

	DirectoryIterator begin() { return DirectoryIterator(_pattern.c_str()); }
	DirectoryIterator end() { return DirectoryIterator::Closed(); }
};