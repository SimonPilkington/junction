#pragma once
#include "FileHandle.h"

class Directory
{
private:
	FileHandle m_handle;

public:
	Directory(const TCHAR *pFilename)
		: Directory(pFilename, false)
	{ }

	Directory(const TCHAR *pFilename, bool blCreate);

	const FileHandle &GetHandle() const { return m_handle; }
};