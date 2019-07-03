#pragma once

#include <tchar.h>
#include <string>
#include "DirectoryIterator.h"

class DirectoryEnumerator
{
private:
	std::wstring m_pattern;

public:
	DirectoryEnumerator(const TCHAR *pattern)
		: m_pattern(pattern)
	{ }

	DirectoryIterator begin() { return DirectoryIterator(m_pattern.c_str()); }

	const DirectoryIterator &end()
	{
		static DirectoryIterator closed = DirectoryIterator::Closed();
		return closed; 
	}
};