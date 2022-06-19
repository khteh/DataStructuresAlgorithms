#include "pch.h"
using namespace std;
TEST(DynamicProgrammingTests, LargestNumberCompositionProductWithDynamicProgrammingTest) {
	ASSERT_EQ(1, LargestNumberCompositionProductWithDynamicProgramming(2));
	ASSERT_EQ(36, LargestNumberCompositionProductWithDynamicProgramming(10));
}
TEST(DynamicProgrammingTests, WordBreakDynamicProgrammingTests) {
	set<string> stringset;
	vector<string> strings;
	stringset = { "Hello", "World" };
	ASSERT_TRUE(WordBreakDynamicProgramming(string("HelloWorld"), stringset));
	WordBreakDynamicProgramming(string("HelloWorld"), stringset, strings);
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(1, strings.size());
	ASSERT_EQ("Hello World", strings[0]);

	stringset.clear();
	stringset = { "cats", "dog", "sand", "and", "cat" };
	ASSERT_FALSE(WordBreakDynamicProgramming(string("catsandog"), stringset));
	ASSERT_TRUE(WordBreakDynamicProgramming(string("catsanddog"), stringset));
	ASSERT_TRUE(WordBreakDynamicProgramming(string("catanddog"), stringset));
	strings.clear();
	WordBreakDynamicProgramming(string("catsandog"), stringset, strings);
	ASSERT_TRUE(strings.empty());
	strings.clear();
	WordBreakDynamicProgramming(string("catsanddog"), stringset, strings);
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(2, strings.size());
	strings.clear();
	WordBreakDynamicProgramming(string("catanddog"), stringset, strings);
	ASSERT_EQ(1, strings.size());
	ASSERT_EQ("cat and dog", strings[0]);

	stringset.clear();
	stringset = { "apple", "pen" };
	ASSERT_TRUE(WordBreakDynamicProgramming(string("applepenapple"), stringset));
	strings.clear();
	WordBreakDynamicProgramming(string("applepenapple"), stringset, strings);
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(1, strings.size());
	ASSERT_EQ("apple pen apple", strings[0]);

	stringset.clear();
	stringset = { "aaaa", "aaa" };
	ASSERT_TRUE(WordBreakDynamicProgramming(string("aaaaaaa"), stringset));
	strings.clear();
	WordBreakDynamicProgramming(string("aaaaaaa"), stringset, strings);
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(2, strings.size());
}
TEST(DynamicProgrammingTests, AbbreviationTests) {
	string line, line1;
	line = "AbcDE";
	line1 = "ABDE";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "AbcDE";
	line1 = "AFDE";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "AbcDE";
	line1 = "ACDE";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "AbcDE";
	line1 = "ADE";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "AbcDE";
	line1 = "ADDE";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "aaaa";
	line1 = "A";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "abcdef";
	line1 = "A";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "bbbbb";
	line1 = "A";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "aaBaa";
	line1 = "B";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "daBcd";
	line1 = "ABC";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "bBccC";
	line1 = "BBC";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "bbBccC";
	line1 = "BBC";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "KXzQ";
	line1 = "K";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "beFgH";
	line1 = "EFG";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "ababbaAbAB";
	line1 = "AABABB";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "aAbAb";
	line1 = "ABAB";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "baaBa";
	line1 = "BAAA";
	ASSERT_FALSE(Abbreviation(line, line1));
	line = "abAAb";
	line1 = "AAA";
	ASSERT_TRUE(Abbreviation(line, line1));
	line = "babaABbbAb";
	line1 = "ABAA";
	ASSERT_FALSE(Abbreviation(line, line1));
}
TEST(DynamicProgrammingTests, FindSubsequenceDynamicProgrammingTests)
{
	ASSERT_EQ(2, FindSubsequenceDynamicProgramming(string("1221"), string("12")));
	ASSERT_EQ(0, FindSubsequenceDynamicProgramming(string("1234"), string("56")));
	ASSERT_EQ(15, FindSubsequenceDynamicProgramming(string("kkkkkkz"), string("kkkk")));
}
TEST(DynamicProgrammingTests, fibonacciDynamicProgrammingTests)
{
	ASSERT_EQ(-1, fibonacciDynamicProgramming(-1));
	ASSERT_EQ(0, fibonacciDynamicProgramming(0));
	ASSERT_EQ(1, fibonacciDynamicProgramming(1));
	ASSERT_EQ(1, fibonacciDynamicProgramming(2));
	ASSERT_EQ(2, fibonacciDynamicProgramming(3));
	ASSERT_EQ(3, fibonacciDynamicProgramming(4));
	ASSERT_EQ(5, fibonacciDynamicProgramming(5));
	ASSERT_EQ(8, fibonacciDynamicProgramming(6));
	ASSERT_EQ(13, fibonacciDynamicProgramming(7));
	ASSERT_EQ(21, fibonacciDynamicProgramming(8));
	ASSERT_EQ(34, fibonacciDynamicProgramming(9));
	ASSERT_EQ(2880067194370816120ULL, fibonacciDynamicProgramming(90));
}
TEST(DynamicProgrammingTests, factorialDynamicProgrammingTests)
{
	ASSERT_EQ(1, factorialDynamicProgramming(1));
	ASSERT_EQ(2, factorialDynamicProgramming(2));
	ASSERT_EQ(6, factorialDynamicProgramming(3));
	ASSERT_EQ(24, factorialDynamicProgramming(4));
	ASSERT_EQ(120, factorialDynamicProgramming(5));
	ASSERT_EQ(2432902008176640000, factorialDynamicProgramming(20));
#if defined(__GNUC__) || defined(__GNUG__)
	ASSERT_EQ(15511210043330985984000000, factorialDynamicProgramming(25)); // Only 64-bit on GNU C++. "constant too big" compilation error on MSVC
#endif
}