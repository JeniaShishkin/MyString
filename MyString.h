
#include "string.h"
#include <cassert>
#include <iostream>
#include <compare>
#include <cstddef>
#include <stdexcept>
#include <cstring>

class MyString
{
public:
	MyString() : m_data{} { }
	MyString(const char* str);
	MyString(const MyString& other); 
	MyString(MyString&& other) noexcept;

	/* OPERATORS */
	const char& operator[](size_t index) const { if (index >= size()) throw std::out_of_range("Index out of range"); return data()[index]; }
	char& operator[](size_t index) { if (index >= size()) throw std::out_of_range("Index out of range"); return data()[index]; }
	std::strong_ordering operator<=>(const MyString& other) const noexcept;
	bool operator==(const MyString& other) const noexcept;
	MyString operator+(const MyString& other) const;
	MyString& operator+=(const MyString& other) { return *this = *this + other ; }
    // friend std::ostream& operator<<(std::ostream& os, const MyString& s) { os << s.m_str; return os ; }

	MyString& operator=(MyString other) { swap(other); return *this; }; // Supposed to be valid for both copy ans move.
	
	// Extra functions.
	void swap(MyString &other) noexcept { using std::swap; swap(m_data, other.m_data); }
	size_t size() const noexcept { return isSSO() ? ssoSize() : m_data.longString.size; }
	size_t ssoSize() const noexcept { return m_data.shortString[sizeof(SSO) - 1] & SIZE_MASK; }

	bool isSSO() const noexcept { return (m_data.shortString[sizeof(SSO) - 1] & SSO_MASK) != 0; }

	
	// Functions to return pointer to data to support index-based access.
	const char* data() const noexcept { return isSSO() ? m_data.shortString : m_data.longString.longStringPtr; }
	char* data() noexcept { return isSSO() ? m_data.shortString : m_data.longString.longStringPtr; }
	
	

	~MyString() { if (!isSSO() && m_data.longString.longStringPtr) delete[] m_data.longString.longStringPtr; }

private:
	static constexpr int SHORT_STR_LENGTH = 15;
	static constexpr unsigned char SSO_MASK = 0x80; // 1000 0000
	static constexpr unsigned char SIZE_MASK = 0x7F; // 0111 1111

	union SSO
	{
		SSO() : shortString{} { }
		SSO(char *s, size_t size) : longString(s, size) { }
		struct {
			char* longStringPtr;
			size_t size;
		} longString;
		char shortString[sizeof(longString)];
	};
	SSO m_data;
};

