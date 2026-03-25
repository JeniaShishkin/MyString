#include "MyString.h"

// support move ctor + move assignment
// can use ANY c-function but no functions from std::string or std collection.
// the delete operator to use on arrays is delete[] (in fact "new int[5]" uses operator new[] and not operator new)
 
 
// writing auto tests
 
void testSizeAfterDefaultCtor()
{
	MyString s1{};
	assert(s1.size() == 0);
	assert(s1.isEmpty());
}
 
void testSizeAfterCString()
{
	MyString s1{"abc"};
	MyString s2{s1};
	assert(s1.size() == 3);
	assert(!s1.isEmpty());
	assert(s1[0] == 'a');
	assert(s1[1] == 'b');
	assert(s1[2] == 'c');
 
	try
	{
		s1[-1];
		assert(!"did not throw on access to -1");
	}
	catch (const std::out_of_range &)
	{
	}
 
	try
	{
		s1[3];
		assert(!"did not throw on access to -1");
	}
	catch (const std::out_of_range &)
	{
	}
}
 
int main()
{
	MyString s1{"Hello"};
	MyString s2{"goodbye!"};
	s1 = std::move(s2);
	std::cout << s2.size() << std::endl;
//	std::cout << s2.size() << std:: endl; // I want it in O(1): MyString s3{"hello"}; std::cout << s3.size(); // print 5
//	std::cout << ("abc" < s2) << std::endl;
//	std::cout << (s2 < "abc") << std::endl;
//	std::cout << (s1 == s2) << std::endl;
//	std::cout << (s1 == "abc") << std::endl;
//	std::cout << ("abc" == s1) << std::endl;
//	std::cout << (s1 < s2) << std::endl;
//	std::cout << (s1 < "abc" )<< std::endl;  // same for the rest of the operators.... support both sides to be const char *
//	std::cout << (s1 <= s2) << std::endl;
//	std::cout << (s1 > s2) << std::endl;
//	std::cout << (s1 >= s2) << std::endl;
//	std::cout << (s1 != s2) << std::endl;
//	std::cout << (s1 = s2) << std::endl;
//	std::cout << (s1 += s2) << std::endl; // also s1 += "abc"
//	s1[3]; // access the character at idx 3. accessing out of bounds character throws an exception
//	s1.isEmpty();
//	testSizeAfterDefaultCtor();
//	testSizeAfterCString();
	return 0;
}