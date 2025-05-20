#pragma once
#include "pch.h"
#include "Arithmetic.h"
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