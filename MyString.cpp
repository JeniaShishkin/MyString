
#include <cassert>


class MyString

{
	MyString(){}

	// ... you decide what to put here

};
 
int main()
{


	MyString s1{}, s2{"abc"}; // "abc" is really "abc\0"

	s1 == s2;

	s1 == "abc";

	"abc" == s1;

	s1 < s2;

	"abc" < s2;

	s1 < "abc"   // same for the rest of the operators.... support both sides to be const char *

	s1 <= s2;

	s1 > s2;

	s1 >= s2;

	s1 != s2;

	s1 = s2;

	s1 += s2; // also s1 += "abc"

	s1 + s2;

	s1.size();
	 // I want it in O(1): MyString s3{"hello"}; std::cout << s3.size(); // print 5
	return 0;
}
// support move ctor + move assignment

// can use ANY c-function but no functions from std::string or std collection.

// the delete operator to use on arrays is delete[] (in fact "new int[5]" uses operator new[] and not operator new)

 