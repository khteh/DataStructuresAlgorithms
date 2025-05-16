#pragma once
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <ranges>
#include <sstream>
#include "oneapi/tbb.h"
#include "Arithmetic.h"
using namespace oneapi::tbb;
using namespace std;
class Palindrome
{
public:
    bool IsPalindrome(string const &);
    bool IsPalindrome1(string const &);
    bool IsPalindrome2(string const &);
    string FindBiggestPalindromeSubstring(string const &);
    void FindPalindromeSubstrings(string const &, set<string> &);
    size_t PalindromeAnagramCount(string const &);
    size_t PalindromeAnagramCount1(string const &);
    void HighestValuePalindrome(string &, size_t);
    size_t ShortPalindrome(const string &);
    long MaxSizePalindromeCount(string const &, size_t, size_t);
};