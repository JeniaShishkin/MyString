#include "MyString.h"

MyString::MyString(const char* str)
{
	size_t length = strlen(str);
    if (length <= SHORT_STR_LENGTH) // String is SSO
    {
        std::memcpy(m_data.shortString, str, length);  
        m_data.shortString[SHORT_STR_LENGTH] = length | SSO_MASK;
    } 
	else // String is a long string.
	{ 
        m_data.longString.longStringPtr = new char[length + 1];
        std::memcpy(m_data.longString.longStringPtr, str, length + 1);
        m_data.longString.size = length; // MSB 0 = heap
    }
}

MyString::MyString(const MyString& other)
{
	size_t length = other.m_data.longString.size;
    if (other.isSSO())
	{
        std::memcpy(m_data.shortString, other.m_data.shortString, length + 1);
    }
	else
	{
        m_data.longString.longStringPtr = new char[length + 1];
        std::memcpy(m_data.longString.longStringPtr, other.m_data.longString.longStringPtr, length + 1);
        m_data.longString.size = length;
    }
}

MyString::MyString(MyString&& other) noexcept 
{
    if (other.isSSO()) 
	{
        std::memcpy(m_data.shortString, other.m_data.shortString, 16);
    }
	else
	{
        m_data.longString = other.m_data.longString;
        other.m_data.longString.longStringPtr = nullptr;
        other.m_data.longString.size = 0;
    }
}

std::strong_ordering MyString::operator<=>(const MyString& other) const noexcept 
{
    size_t length = std::min(size(), other.size());
    int cmp = std::memcmp(data(), other.data(), length);
    if (cmp != 0) return cmp < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
    return size() <=> other.size();
}

MyString MyString::operator+(const MyString& other) const {
    size_t totalLen = size() + other.size();
    MyString result;
    if (totalLen <= 15) // SSO
	{
        std::memcpy(result.m_data.shortString, data(), size());
        std::memcpy(result.m_data.shortString + size(), other.data(), other.size());
        result.m_data.shortString[totalLen] = '\0';
        result.m_data.shortString[15] = totalLen | SSO_MASK;
    }
	else  // Long string
	{ 
        char* newString = new char[totalLen + 1];
        std::memcpy(newString, data(), size());
        std::memcpy(newString + size(), other.data(), other.size());
        // buf[totalLen] = '\0';
        result.m_data.longString.longStringPtr = newString;
        result.m_data.longString.size = totalLen;
    }

    return result;
}


bool MyString::operator==(const MyString& other) const noexcept 
{
    if (size() != other.size()) return false;
    return std::memcmp(data(), other.data(), size()) == 0;
}
