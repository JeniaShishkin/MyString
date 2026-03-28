#include "MyString.h"

MyString::MyString(const char* str)
{
	size_t length = strlen(str);
    if (length <= SHORT_STR_LENGTH) // String is SSO
    {
        std::memcpy(m_data.shortString, str, length);  
        m_data.shortString[SHORT_STR_LENGTH] = static_cast<unsigned char>(length) | SSO_MASK; // SSO_MASK is unsigned char, therefore we cast the length to same type.
    } 
	else // String is a long string.
	{ 
        m_data.longString.longStringPtr = new char[length + 1];
        std::memcpy(m_data.longString.longStringPtr, str, length + 1);
        m_data.longString.size = length; // Assumed MSB will always be zero, unless strlen > 2^54 which is absurd.
    }
}

MyString::MyString(const MyString& other)
{
	size_t length = other.size();
	if (other.isSSO())
	{
		std::memcpy(m_data.shortString, other.m_data.shortString, sizeof(SSO));
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
        std::memcpy(m_data.shortString, other.m_data.shortString, sizeof(SSO)); // moving the entire 16 bytes, including metadata.
		other.m_data.shortString[0] = '\0';
		other.m_data.shortString[SHORT_STR_LENGTH] = SSO_MASK; // isSSO = true, size = 0.
    }
	else
	{
        m_data.longString = other.m_data.longString; // default assignment operator of struct, which is what we want.
        other.m_data.longString.longStringPtr = nullptr; // stealing resources and leaving other with nothing.
        other.m_data.longString.size = 0;
    }
}

std::strong_ordering MyString::operator<=>(const MyString& other) const noexcept 
{
    int cmp = strcmp(data(), other.data());
	if (cmp != 0) return cmp < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
	return std::strong_ordering::equal;
}

MyString MyString::operator+(const MyString& other) const {
    size_t totalLen = size() + other.size();
    MyString result;
    if (totalLen <= SHORT_STR_LENGTH) // SSO
	{
        std::memcpy(result.m_data.shortString, data(), size());
        std::memcpy(result.m_data.shortString + size(), other.data(), other.size());
        result.m_data.shortString[SHORT_STR_LENGTH] = static_cast<unsigned char>(totalLen) | SSO_MASK; // cast TotalLen to same type as SSO_MASK.
    }
	else  // Long string
	{ 
        char* newString = new char[totalLen + 1];
        std::memcpy(newString, data(), size());
        std::memcpy(newString + size(), other.data(), other.size());
        result.m_data.longString.longStringPtr = newString;
        result.m_data.longString.size = totalLen;
    }

    return result;
}


bool MyString::operator==(const MyString& other) const noexcept 
{
    if (size() != other.size()) return false;
    return strcmp(data(), other.data()) == 0;
}


std::ostream& operator<<(std::ostream& os, const MyString& s) 
{
	if(s.isSSO()) { os << s.m_data.shortString; }

	else { os << s.m_data.longString.longStringPtr; }

	return os;  
}