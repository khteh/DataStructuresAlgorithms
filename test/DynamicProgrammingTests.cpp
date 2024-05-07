#include "pch.h"
using namespace std;
TEST(DynamicProgrammingTests, LargestNumberCompositionProductWithDynamicProgrammingTest)
{
	ASSERT_EQ(1, LargestNumberCompositionProductWithDynamicProgramming(2));
	ASSERT_EQ(36, LargestNumberCompositionProductWithDynamicProgramming(10));
}
class WordBreakFixture : public testing::TestWithParam<tuple<bool, string, set<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_strs = get<2>(GetParam());
	}
	bool WordBreakDynamicProgrammingTest()
	{
		return WordBreakDynamicProgramming(_str1, _strs);
	}

protected:
	string _str1;
	set<string> _strs;
	bool _expected;
};
TEST_P(WordBreakFixture, WordBreakDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->WordBreakDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	DynamicProgrammingTests,
	WordBreakFixture,
	::testing::Values(make_tuple(true, "HelloWorld", set<string>{"Hello", "World"}), make_tuple(false, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(true, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}), make_tuple(true, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(true, "applepenapple", set<string>{"apple", "pen"}), make_tuple(true, "aaaaaaa", set<string>{"aaaa", "aaa"})));
class WordBreak2Fixture : public testing::TestWithParam<tuple<vector<string>, string, set<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_strs = get<2>(GetParam());
	}
	vector<string> WordBreakDynamicProgrammingTest()
	{
		vector<string> result;
		WordBreakDynamicProgramming(_str1, _strs, result);
		return result;
	}

protected:
	string _str1;
	set<string> _strs;
	vector<string> _expected;
};
TEST_P(WordBreak2Fixture, WordBreak2DynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->WordBreakDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	DynamicProgrammingTests,
	WordBreak2Fixture,
	::testing::Values(make_tuple(vector<string>{"Hello World"}, "HelloWorld", set<string>{"Hello", "World"}),
					  make_tuple(vector<string>{}, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"cat sand dog", "cats and dog"}, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"cat and dog"}, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"apple pen apple"}, "applepenapple", set<string>{"apple", "pen"}),
					  make_tuple(vector<string>{"aaa aaaa", "aaaa aaa"}, "aaaaaaa", set<string>{"aaaa", "aaa"})));

class AbbreviationFixture : public testing::TestWithParam<tuple<bool, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_str2 = get<2>(GetParam());
	}
	bool AbbreviationTest()
	{
		return Abbreviation(_str1, _str2);
	}

protected:
	string _str1, _str2;
	bool _expected;
};
TEST_P(AbbreviationFixture, AbbreviationTests)
{
	ASSERT_EQ(this->_expected, this->AbbreviationTest());
}
INSTANTIATE_TEST_SUITE_P(
	DynamicProgrammingTests,
	AbbreviationFixture,
	::testing::Values(make_tuple(true, "AbcDE", "ABDE"), make_tuple(false, "AbcDE", "AFDE"), make_tuple(true, "AbcDE", "ACDE"), make_tuple(true, "AbcDE", "ADE"),
					  make_tuple(false, "AbcDE", "ADDE"), make_tuple(true, "aaaa", "A"), make_tuple(true, "abcdef", "A"), make_tuple(false, "bbbbb", "A"),
					  make_tuple(true, "aaBaa", "B"), make_tuple(true, "daBcd", "ABC"), make_tuple(true, "bBccC", "BBC"), make_tuple(false, "KXzQ", "K"),
					  make_tuple(false, "beFgH", "EFG"), make_tuple(false, "ababbaAbAB", "AABABB"), make_tuple(true, "aAbAb", "ABAB"), make_tuple(false, "baaBa", "BAAA"),
					  make_tuple(true, "abAAb", "AAA"), make_tuple(false, "babaABbbAb", "ABAA")));
class FindSubsequenceFixture : public testing::TestWithParam<tuple<size_t, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_str2 = get<2>(GetParam());
	}
	size_t FindSubsequenceDynamicProgrammingTest()
	{
		return FindSubsequenceDynamicProgramming(_str1, _str2);
	}

protected:
	string _str1, _str2;
	size_t _expected;
};
TEST_P(FindSubsequenceFixture, FindSubsequenceDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->FindSubsequenceDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindSubsequenceDynamicProgrammingTests,
	FindSubsequenceFixture,
	::testing::Values(make_tuple(2, "1221", "12"), make_tuple(0, "1234", "56"), make_tuple(15, "kkkkkkz", "kkkk"), make_tuple(6, "kkkkkkz", "kkkkk"), make_tuple(1, "kkkkkkz", "kkkkkk"), make_tuple(0, "DeadBeef", "FeedBeef"), make_tuple(1, "DeadBeef", "Beef"), make_tuple(1, "DeadBeef", "dBeef"), make_tuple(0, "DeadBeef", "eedBeef"), make_tuple(1, "DeadBeef", "edBeef")));
class FibonacciDynamicProgrammingFixture : public testing::TestWithParam<tuple<long, unsigned long long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	unsigned long long FibonacciDynamicProgrammingTest()
	{
		return FibonacciDynamicProgramming(_data);
	}

protected:
	long _data;
	unsigned long long _expected;
};
TEST_P(FibonacciDynamicProgrammingFixture, FibonacciDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->FibonacciDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	FibonacciDynamicProgrammingTests,
	FibonacciDynamicProgrammingFixture,
	::testing::Values(make_tuple(-1, -1), make_tuple(0, 0), make_tuple(1, 1), make_tuple(1, 2), make_tuple(2, 3), make_tuple(3, 4), make_tuple(5, 5), make_tuple(8, 6), make_tuple(13, 7), make_tuple(21, 8), make_tuple(34, 9), make_tuple(2880067194370816120ULL, 90)));
class FibonacciModifiedDynamicProgrammingFixture : public testing::TestWithParam<tuple<string, long, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_t1 = get<1>(GetParam());
		_t2 = get<2>(GetParam());
		_n = get<3>(GetParam());
	}
	string FibonacciModifiedDynamicProgrammingTest()
	{
		return FibonacciModifiedDynamicProgramming(_t1, _t2, _n);
	}

protected:
	long _t1, _t2, _n;
	string _expected;
};
TEST_P(FibonacciModifiedDynamicProgrammingFixture, FibonacciModifiedDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->FibonacciModifiedDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	FibonacciModifiedDynamicProgrammingTests,
	FibonacciModifiedDynamicProgrammingFixture,
	::testing::Values(make_tuple("5", 0, 1, 4), make_tuple("27", 0, 1, 5), make_tuple("734", 0, 1, 6), make_tuple("538783", 0, 1, 7), make_tuple("290287121823", 0, 1, 8), make_tuple("2", 2, 0, 0), make_tuple("0", 2, 0, 1), make_tuple("2", 2, 0, 2), make_tuple("4", 2, 0, 3), make_tuple("18", 2, 0, 4), make_tuple("328", 2, 0, 5), make_tuple("107602", 2, 0, 6), make_tuple("11578190732", 2, 0, 7), make_tuple("104292047421056066715537698951727494083004264929891558279344228228718658019003171882044298756195662458280101226593033166933803327203745068186400974453022429724308", 2, 0, 11)));

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
class NumberSolitaireFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long NumberSolitaireTest()
	{
		return _rangeObj.NumberSolitaire(_data);
	}

protected:
	Range _rangeObj;
	vector<long> _data;
	long _expected;
};
TEST_P(NumberSolitaireFixture, NumberSolitaireTests)
{
	ASSERT_EQ(this->_expected, this->NumberSolitaireTest());
}
INSTANTIATE_TEST_SUITE_P(
	DynamicProgrammingTests,
	NumberSolitaireFixture,
	::testing::Values(make_tuple(8, vector<long>{1, -2, 0, 9, -1, -2}), make_tuple(3, vector<long>{1, -2, 4, 3, -1, -3, -7, 4, -9}),
					  make_tuple(-12, vector<long>{0, -4, -5, -2, -7, -9, -3, -10}), make_tuple(-13, vector<long>{-1, -4, -5, -2, -7, -9, -3, -10})));