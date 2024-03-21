#include "pch.h"
using namespace std;
TEST(PalindromeTests, PalindromeTest)
{
	set<string> palindromes;
	ASSERT_TRUE(isPalindrome("abcdefghhgfedecba"));
	ASSERT_FALSE(isPalindrome("aabbcd"));
	ASSERT_TRUE(isPalindrome("aabbc"));
	ASSERT_FALSE(isPalindrome("xxxaabbccrry"));
	//	assert(!isPalindrome("aaaabbcc"));
	ASSERT_TRUE(isPalindrome("mmo"));
	ASSERT_TRUE(isPalindrome1("mmo"));
	ASSERT_FALSE(isPalindrome2("mmo"));

	ASSERT_TRUE(isPalindrome("yakak"));
	ASSERT_TRUE(isPalindrome1("yakak"));
	ASSERT_FALSE(isPalindrome2("yakak"));

	ASSERT_FALSE(isPalindrome("travel"));
	ASSERT_FALSE(isPalindrome1("travel"));
	ASSERT_TRUE(isPalindrome("12121"));
	ASSERT_TRUE(isPalindrome("12321"));
	ASSERT_TRUE(isPalindrome("123321"));
	ASSERT_FALSE(isPalindrome("121212"));
	ASSERT_FALSE(isPalindrome("123421"));
	ASSERT_TRUE(isPalindrome1("12121"));
	ASSERT_TRUE(isPalindrome1("12321"));
	ASSERT_TRUE(isPalindrome1("123321"));
	ASSERT_FALSE(isPalindrome1("121212"));
	ASSERT_FALSE(isPalindrome1("123421"));
	ASSERT_TRUE(isPalindrome2("12121"));
	ASSERT_TRUE(isPalindrome2("12321"));
	ASSERT_TRUE(isPalindrome2("123321"));
	ASSERT_FALSE(isPalindrome2("121212"));
	ASSERT_FALSE(isPalindrome2("123421"));
	// https://en.wikipedia.org/wiki/Palindrome
	ASSERT_TRUE(isPalindrome2("A man, a plan, a canal, Panama!"));
	ASSERT_TRUE(isPalindrome2("Amor, Roma"));
	ASSERT_TRUE(isPalindrome2("race car"));
	ASSERT_TRUE(isPalindrome2("stack cats"));
	ASSERT_TRUE(isPalindrome2("step on no pets"));
	ASSERT_TRUE(isPalindrome2("taco cat"));
	ASSERT_TRUE(isPalindrome2("put it up"));
	ASSERT_TRUE(isPalindrome2("Was it a car or a cat I saw?"));
	ASSERT_TRUE(isPalindrome2("No 'x' in Nixon"));
	ASSERT_EQ("ABCDCBA", FindBiggestPalindromeSubstring("AABCDCBA"));
	ASSERT_EQ("ABCDDCBA", FindBiggestPalindromeSubstring("AABCDDCBA"));
	ASSERT_EQ("ABCBA", FindBiggestPalindromeSubstring("DEFABCBAYT"));
	ASSERT_EQ("ABCCBA", FindBiggestPalindromeSubstring("DEFABCCBAYT"));
	ASSERT_EQ(11, PalindromeAnagramCount("02002"));
	ASSERT_EQ(11, PalindromeAnagramCount1("02002"));
	FindPalindromeSubstrings("a", palindromes);
	ASSERT_TRUE(palindromes.empty());
	palindromes.clear();
	FindPalindromeSubstrings("aa", palindromes);
	ASSERT_EQ(1, palindromes.size());
	ASSERT_NE(palindromes.find("aa"), palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aaa", palindromes);
	ASSERT_EQ(2, palindromes.size());
	ASSERT_NE(palindromes.find("aa"), palindromes.end());
	ASSERT_NE(palindromes.find("aaa"), palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aba", palindromes);
	ASSERT_EQ(1, palindromes.size());
	ASSERT_NE(palindromes.find("aba"), palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aaazaaksforskeeggeeks", palindromes);
	ASSERT_NE(palindromes.find("skeeggeeks"), palindromes.end());
	ASSERT_NE(palindromes.find("aazaa"), palindromes.end());
}