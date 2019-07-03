#include <Windows.h>

#include "WinApiException.h"

WinApiException WinApiException::FromLastError()
{
	LPSTR messageBuffer = nullptr;
	size_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, ::GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&messageBuffer), 0, NULL);

	std::string message(messageBuffer, size);

	::LocalFree(messageBuffer);

	return WinApiException(message.c_str());
}
