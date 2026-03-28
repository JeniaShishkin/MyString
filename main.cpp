#include "MyString.h"
#include <cassert>
#include <iostream>

void testDefaultCtor() {
    MyString s;
    assert(s.size() == 0);
    assert(s.isEmpty());
}

void testCStringCtorAndCopy() {
    MyString s1{"abc"};
    MyString s2{s1}; // copy constructor

    assert(s1.size() == 3);
    assert(s2.size() == 3);
    assert(s1[0] == 'a');
    assert(s2[2] == 'c');
    assert(s1 == s2);
    assert(!(s1 != s2));

    // Out-of-range access
    try { s1[3]; assert(false && "Did not throw"); }
    catch (const std::out_of_range&) {}
    try { s1[-1]; assert(false && "Did not throw"); }
    catch (const std::out_of_range&) {}
}

void testMoveCtorAndAssignment() {
    MyString s1{"abcdef"};
    MyString s2{std::move(s1)};
    assert(s2.size() == 6);
    assert(s1.size() == 0 || s1.isEmpty()); // s1 is in valid but unspecified state

    MyString s3;
    s3 = std::move(s2);
    assert(s3.size() == 6);
    assert(s2.size() == 0 || s2.isEmpty());
}

void testSSOandNonSSO() {
    MyString s1{"short"};                 // SSO
    MyString s2{"this string is definitely longer than 15"}; // non-SSO

    assert(s1.isSSO());
    assert(!s2.isSSO());

    assert(s1.size() == 5);
    assert(s2.size() == std::strlen("this string is definitely longer than 15"));
}

void testOperators() {
    MyString s1{"abc"};
    MyString s2{"xyz"};

    // Comparison
    assert(s1 < s2);
    assert(s1 <= s2);
    assert(!(s1 > s2));
    assert(!(s1 >= s2));
    assert(s1 != s2);
    assert(!(s1 == s2));

    // Concatenation
    MyString s3 = s1 + s2;
    assert(s3.size() == s1.size() + s2.size());
    assert(s3[0] == 'a');
    assert(s3[4] == 'y');

    s1 += s2;
    assert(s1.size() == s3.size());
    assert(s1 == s3);
}

void testCharAccess() {
    MyString s{"hello"};
    assert(s[0] == 'h');
    assert(s[4] == 'o');
    try { s[5]; assert(false && "Out of bounds did not throw"); }
    catch (const std::out_of_range&) {}
}

void testAll() {
    testDefaultCtor();
    testCStringCtorAndCopy();
    testMoveCtorAndAssignment();
    testSSOandNonSSO();
    testOperators();
    testCharAccess();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    testAll();

    // Additional interactive tests
    MyString s1{"hello"};
    MyString s2{"world"};
    std::cout << s1 << " + " << s2 << " = " << (s1 + s2) << std::endl;

    s1 += "abc";
    std::cout << "After += 'abc': " << s1 << std::endl;

    return 0;
}