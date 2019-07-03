#pragma once

#include <windef.h>
#include <iterator>

class DirectoryIterator final
{
public:
	typedef std::wstring value_type;
	typedef std::ptrdiff_t difference_type;
	typedef value_type *pointer;
	typedef value_type &reference;
	typedef std::input_iterator_tag iterator_category;

private:
	DirectoryIterator(bool closed) : _closed(closed), _searchHandle(INVALID_HANDLE_VALUE)
	{ }

	HANDLE _searchHandle;
	WIN32_FIND_DATA _findData;

	bool _closed;
	value_type _value;

	void GetNextFile();
	bool IsValid(WIN32_FIND_DATA *data);

public:
	static DirectoryIterator Closed()
	{ 
		static DirectoryIterator closed(true); 
		return closed;
	}

	DirectoryIterator(const TCHAR *pattern);
	~DirectoryIterator();

	void Close();

	inline value_type operator*() const { return _value; }
	
	inline bool operator==(const DirectoryIterator &other) const { return _closed == other._closed && _value == other._value; }
	inline bool operator!=(const DirectoryIterator &other) const { return !(*this == other); }
	
	value_type operator++(int)
	{
		value_type ret(_value);
		++*this;
		return ret;
	}

	DirectoryIterator &operator++()
	{
		GetNextFile();
		return *this;
	}
};
