
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
	MyString(const char* str = "");
	MyString(const MyString& other); 
	MyString(MyString &&other){ swap(other); other.m_str = nullptr; other.m_size = 0 ; }
	
	/* OPERATORS */
	const char operator[](const int index) const { if(index < 0) throw std::out_of_range("Index out of range.\n"); return *(m_str + index) ; }
	auto operator<=>(const MyString& other) const;
	bool operator==(const MyString& other) const { return std::strcmp(m_str, other.m_str) == 0; }
	MyString operator+(const MyString& other) const;
	MyString& operator+=(const MyString& other) { return *this = *this + other ; }
    friend std::ostream& operator<<(std::ostream& os, const MyString& s) { os << s.m_str; return os ; }
	MyString& operator=(MyString other) { swap(other); return *this ; }

	// Extra functions.
	void swap(MyString &other) { using std::swap; swap(m_str, other.m_str); swap(m_size, other.m_size) ; }
	bool isEmpty() const { return m_size == 0 ; }
	int size() const { return m_size ; } 

	~MyString() { delete[] m_str; m_str = nullptr; m_size = 0 ; }	

private:
	char* m_str;
	int m_size = 0;
};
 

 
