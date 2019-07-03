#pragma once

#include <stdexcept>

class WinApiException : public std::runtime_error
{
public:
	WinApiException(const char* message) noexcept
		: std::runtime_error(message)
	{ }

	static WinApiException FromLastError();
};