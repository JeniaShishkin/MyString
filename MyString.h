
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
	MyString(MyString&& other) noexcept : MyString() { swap(other); } // Initialize new instance, then steal information from the other one.

	/* OPERATORS */
	const char& operator[](const int index) const { if(index < 0 || index >= m_size) throw std::out_of_range("Index out of range.\n"); return *(m_str + index) ; }
	friend std::strong_ordering operator<=>(const MyString& a, const MyString& b);
	bool operator==(const MyString& other) const { return std::strcmp(m_str, other.m_str) == 0; }
	MyString operator+(const MyString& other) const;
	MyString& operator+=(const MyString& other) { return *this = *this + other ; }
    friend std::ostream& operator<<(std::ostream& os, const MyString& s) { os << s.m_str; return os ; }

	MyString& operator=(MyString other) { swap(other); return *this; }; // Supposed to be valid for both copy ans move.

	// Old implementation of move/copy assignments.
//	MyString& operator=(const MyString &other) { MyString copy{other}; swap(copy); return *this ; } // Copy assignment.
//	MyString& operator=(MyString &&other) noexcept { swap(other); return *this; } // Move assignment.

	// Extra functions.
	void swap(MyString &other) noexcept { using std::swap; swap(m_str, other.m_str); swap(m_size, other.m_size) ; }
	bool isEmpty() const noexcept { return m_size == 0 ; }
	size_t size() const noexcept { return isSSO(m_data.longString.size) ? strlen(m_data.shortString) : m_data.longString.size & ~MSBIT ; } 

	~MyString() { if (!isSSO(m_data.longString.size)) { delete[] m_data.longString.longStringPtr; }	}

private:

	static constexpr int BITS_IN_BYTE = 8;
	static constexpr int MSBIT_IDX = (sizeof(size_t) * BITS_IN_BYTE);
	static constexpr size_t MSBIT = size_t(1) << (MSBIT_IDX - 1);


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

	static bool isSSO(char* shortString);
	static bool isSSO(size_t length);
	SSO m_data;
};



bool MyString::isSSO(char* shortString)
{
	return (shortString[ sizeof(SSO) - 1 ]  == '\0');
}
 
bool MyString::isSSO(size_t length)
{
	return (length - sizeof('\0') <= sizeof(m_data));
}