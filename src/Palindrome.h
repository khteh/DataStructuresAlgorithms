#pragma once
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <ranges>
#include <sstream>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include "oneapi/tbb.h"
using namespace oneapi::tbb;
#endif
#include "DataStructuresAlgorithms.h"
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
    long double MaxSizePalindromeCount(string const &, size_t, size_t);
};