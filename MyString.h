
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
	MyString() : m_str(nullptr), m_size(0) { }
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
	int size() const noexcept { return m_size ; } 

	~MyString() { delete[] m_str; m_str = nullptr; m_size = 0 ; }	

private:
	char* m_str;
	int m_size = 0;
};
 

 
