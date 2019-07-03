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
	DirectoryIterator(bool closed) : m_closed(closed), m_searchHandle(INVALID_HANDLE_VALUE), m_findData(WIN32_FIND_DATA{ 0 })
	{ }

	HANDLE m_searchHandle;
	WIN32_FIND_DATA m_findData;

	bool m_closed;
	value_type m_value;

	void GetNext();
	bool IsValid();

public:
	static DirectoryIterator Closed()
	{ 
		return DirectoryIterator(true);
	}

	DirectoryIterator(const TCHAR *pattern);
	~DirectoryIterator();

	void Close();

	inline value_type operator*() const { return m_value; }
	
	inline bool operator==(const DirectoryIterator &other) const 
	{ 
		return m_closed == other.m_closed || m_value == other.m_value;
	}

	inline bool operator!=(const DirectoryIterator &other) const
	{ 
		return !operator==(other);
	}
	
	value_type operator++(int)
	{
		value_type ret(m_value);
		++*this;
		return ret;
	}

	DirectoryIterator &operator++()
	{
		GetNext();
		return *this;
	}
};
