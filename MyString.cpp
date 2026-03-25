#include "MyString.h"

MyString::MyString(const char* str)
{
	m_size = strlen(str); 
	m_str = new char[m_size + sizeof('\0')];
	memcpy(m_str, str, m_size + sizeof('\0'));
}

MyString::MyString(const MyString& other) 
{
    std::cout << "Copy constructor is invoked" << std::endl;
	int allocatedMemory = other.m_size + sizeof('\0');
	m_str = new char[allocatedMemory];
	memcpy(m_str, other.m_str, allocatedMemory);
	m_size = other.m_size; 
}

std::strong_ordering MyString::operator<=>(const MyString& other) const
{
	int cmp = std::strcmp(this->m_str, other.m_str);
    if (cmp < 0) return std::strong_ordering::less;
    if (cmp > 0) return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

MyString MyString::operator+(const MyString& other) const
{
	int len1 = size();
	int len2 = other.size();
	char* newString = new char[len1 + len2 + sizeof('\0')];
	memcpy(newString, m_str, len1);
	memcpy(newString + len1, other.m_str, len2 + sizeof('\0'));
	MyString newMyString{newString};
	delete[] newString;
	return newMyString;
}
