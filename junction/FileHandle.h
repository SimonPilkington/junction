#include <windows.h>
#include "WinApiException.h"

class FileHandle final
{
private:
	HANDLE m_hFile;

public:
	FileHandle()
	{ 
		m_hFile = INVALID_HANDLE_VALUE;
	}

	// no handle copying
	FileHandle(const FileHandle &other) = delete;

	// swapping from an r-value is ok
	FileHandle(FileHandle &&other) noexcept
	{
		swap(*this, other);
	}

	FileHandle(LPCTSTR pFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		DWORD dwCreationDisposition,
		DWORD dwFlagsAndAttributes,
		HANDLE hTemplateFile
	)
		: m_hFile(::CreateFile(pFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile))
	{
		if (m_hFile == INVALID_HANDLE_VALUE)
			throw WinApiException("Ended up with invalid handle.");
	}

	~FileHandle() noexcept
	{
		if (m_hFile != INVALID_HANDLE_VALUE)
			::CloseHandle(m_hFile);
	}

	FileHandle& operator=(FileHandle other) noexcept
	{
		swap(*this, other);
		return *this;
	}

	HANDLE operator&() const noexcept
	{
		return m_hFile;
	}

	friend void swap(FileHandle& first, FileHandle& second) noexcept
	{
		using std::swap;
		swap(first.m_hFile, second.m_hFile);
	}
};