#include "MyString.h"

MyString::MyString(const char* str)
{

	size_t length = strlen(str);
    if (isSSO(length))
    {
        strcpy_s(m_data.shortString, length, str);
    }
    else
    {
	    m_data.longString.longStringPtr = new char[length + sizeof('\0')];
	    memcpy(m_data.longString.longStringPtr, str, length + sizeof('\0'));
        m_data.longString.size = (length | 80000000) ;
    }
}

MyString::MyString(const MyString& other)
{
    if(!other.m_data) { m_str = nullptr; return; }

	int allocatedMemory = other.m_size + sizeof('\0');
	m_str = new char[allocatedMemory];
	memcpy(m_str, other.m_str, allocatedMemory);
}

std::strong_ordering operator<=>(const MyString& a, const MyString& b)
{
	int cmp = std::strcmp(a.m_str, b.m_str);
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

