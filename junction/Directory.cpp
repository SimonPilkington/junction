#include "Directory.h"

Directory::Directory(const TCHAR *pFilename, bool blCreate)
{
	try
	{
		if (blCreate && !::CreateDirectory(pFilename, nullptr))
		{
			if (::GetLastError() != ERROR_ALREADY_EXISTS)
				throw WinApiException::FromLastError();
		}

		m_handle = FileHandle(pFilename, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, nullptr);
	}
	catch (const WinApiException &)
	{
		throw WinApiException::FromLastError();
	}

	BY_HANDLE_FILE_INFORMATION info;
	if (!::GetFileInformationByHandle(&m_handle, &info) || !(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		throw WinApiException("Not a directory.");
}
