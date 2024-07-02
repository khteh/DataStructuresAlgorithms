#include "pch.h"
using namespace std;
TEST(LargestNumberCompositionProductWithDPTests, LargestNumberCompositionProductWithDPTest)
{
	ASSERT_EQ(1, LargestNumberCompositionProductWithDynamicProgramming(2));
	ASSERT_EQ(36, LargestNumberCompositionProductWithDynamicProgramming(10));
}
class EggDropsDPTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_eggs = get<1>(GetParam());
		_floors = get<2>(GetParam());
	}
	size_t EggDropsTest()
	{
		return EggDrops(_eggs, _floors);
	}

protected:
	size_t _expected, _eggs, _floors;
};
TEST_P(EggDropsDPTestFixture, EggDropsTests)
{
	ASSERT_EQ(this->_expected, this->EggDropsTest());
}
INSTANTIATE_TEST_SUITE_P(
	EggDropsTests,
	EggDropsDPTestFixture,
	::testing::Values(make_tuple(0, 123, 0), make_tuple(1, 123, 1),
					  make_tuple(123, 1, 123), make_tuple(2, 2, 2),
					  make_tuple(3, 3, 6)));

class WordBreakDPTestFixture : public testing::TestWithParam<tuple<bool, string, set<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_strs = get<2>(GetParam());
	}
	bool WordBreakDPTest()
	{
		return WordBreakDynamicProgramming(_str1, _strs);
	}

protected:
	string _str1;
	set<string> _strs;
	bool _expected;
};
TEST_P(WordBreakDPTestFixture, WordBreakDPTests)
{
	ASSERT_EQ(this->_expected, this->WordBreakDPTest());
}
INSTANTIATE_TEST_SUITE_P(
	WordBreakDPTests,
	WordBreakDPTestFixture,
	::testing::Values(make_tuple(true, "HelloWorld", set<string>{"Hello", "World"}), make_tuple(false, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(true, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}), make_tuple(true, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(true, "applepenapple", set<string>{"apple", "pen"}), make_tuple(true, "aaaaaaa", set<string>{"aaaa", "aaa"})));
class WordBreak2DPTestFixture : public testing::TestWithParam<tuple<vector<string>, string, set<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_strs = get<2>(GetParam());
	}
	vector<string> WordBreakDPTest()
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
TEST_P(WordBreak2DPTestFixture, WordBreak2DPTests)
{
	ASSERT_EQ(this->_expected, this->WordBreakDPTest());
}
INSTANTIATE_TEST_SUITE_P(
	WordBreak2DPTests,
	WordBreak2DPTestFixture,
	::testing::Values(make_tuple(vector<string>{"Hello World"}, "HelloWorld", set<string>{"Hello", "World"}),
					  make_tuple(vector<string>{}, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"cat sand dog", "cats and dog"}, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"cat and dog"}, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"apple pen apple"}, "applepenapple", set<string>{"apple", "pen"}),
					  make_tuple(vector<string>{"aaa aaaa", "aaaa aaa"}, "aaaaaaa", set<string>{"aaaa", "aaa"})));

class AbbreviationDPTestFixture : public testing::TestWithParam<tuple<bool, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_str2 = get<2>(GetParam());
	}
	bool AbbreviationDPTest()
	{
		return Abbreviation(_str1, _str2);
	}

protected:
	string _str1, _str2;
	bool _expected;
};
TEST_P(AbbreviationDPTestFixture, AbbreviationDPTests)
{
	ASSERT_EQ(this->_expected, this->AbbreviationDPTest());
}
INSTANTIATE_TEST_SUITE_P(
	AbbreviationDPTests,
	AbbreviationDPTestFixture,
	::testing::Values(make_tuple(true, "AbcDE", "ABDE"), make_tuple(false, "AbcDE", "AFDE"), make_tuple(true, "AbcDE", "ACDE"), make_tuple(true, "AbcDE", "ADE"),
					  make_tuple(false, "AbcDE", "ADDE"), make_tuple(true, "aaaa", "A"), make_tuple(true, "abcdef", "A"), make_tuple(false, "bbbbb", "A"),
					  make_tuple(true, "aaBaa", "B"), make_tuple(true, "daBcd", "ABC"), make_tuple(true, "bBccC", "BBC"), make_tuple(false, "KXzQ", "K"),
					  make_tuple(false, "beFgH", "EFG"), make_tuple(false, "ababbaAbAB", "AABABB"), make_tuple(true, "aAbAb", "ABAB"), make_tuple(false, "baaBa", "BAAA"),
					  make_tuple(true, "abAAb", "AAA"), make_tuple(false, "babaABbbAb", "ABAA")));
class FindSubsequenceTestFixture : public testing::TestWithParam<tuple<size_t, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_str2 = get<2>(GetParam());
	}
	size_t FindSubsequenceDPTest()
	{
		return FindSubsequenceDynamicProgramming(_str1, _str2);
	}

protected:
	string _str1, _str2;
	size_t _expected;
};
TEST_P(FindSubsequenceTestFixture, FindSubsequenceDPTests)
{
	ASSERT_EQ(this->_expected, this->FindSubsequenceDPTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindSubsequenceDPTests,
	FindSubsequenceTestFixture,
	::testing::Values(make_tuple(2, "1221", "12"), make_tuple(0, "1234", "56"), make_tuple(15, "kkkkkkz", "kkkk"), make_tuple(6, "kkkkkkz", "kkkkk"), make_tuple(1, "kkkkkkz", "kkkkkk"), make_tuple(0, "DeadBeef", "FeedBeef"), make_tuple(1, "DeadBeef", "Beef"), make_tuple(1, "DeadBeef", "dBeef"), make_tuple(0, "DeadBeef", "eedBeef"), make_tuple(1, "DeadBeef", "edBeef")));
class FibonacciDPTestFixture : public testing::TestWithParam<tuple<long double, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long double FibonacciDPTest()
	{
		return FibonacciDynamicProgramming(_data);
	}

protected:
	long _data;
	long double _expected;
};
TEST_P(FibonacciDPTestFixture, FibonacciDPTests)
{
	ASSERT_EQ(this->_expected, this->FibonacciDPTest());
}
// long double is 128-bit on Linux but only 64-bit on Windows
#if defined(__GNUC__) || defined(__GNUG__)
INSTANTIATE_TEST_SUITE_P(
	FibonacciDPTests,
	FibonacciDPTestFixture,
	::testing::Values(make_tuple(-1, -1), make_tuple(0, 0), make_tuple(1, 1), make_tuple(1, 2), make_tuple(2, 3), make_tuple(3, 4), make_tuple(5, 5), make_tuple(8, 6), make_tuple(13, 7), make_tuple(21, 8), make_tuple(34, 9), make_tuple(2880067194370816120ULL, 90)));
#else
INSTANTIATE_TEST_SUITE_P(
	FibonacciDPTests,
	FibonacciDPTestFixture,
	::testing::Values(make_tuple(-1, -1), make_tuple(0, 0), make_tuple(1, 1), make_tuple(1, 2), make_tuple(2, 3), make_tuple(3, 4), make_tuple(5, 5), make_tuple(8, 6), make_tuple(13, 7), make_tuple(21, 8), make_tuple(34, 9)));
#endif
class FibonacciModifiedDPTesFixture : public testing::TestWithParam<tuple<string, long, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_t1 = get<1>(GetParam());
		_t2 = get<2>(GetParam());
		_n = get<3>(GetParam());
	}
	string FibonacciModifiedDPTest()
	{
		return FibonacciModifiedDynamicProgramming(_t1, _t2, _n);
	}

protected:
	long _t1, _t2, _n;
	string _expected;
};
TEST_P(FibonacciModifiedDPTesFixture, FibonacciModifiedDPTests)
{
	ASSERT_EQ(this->_expected, this->FibonacciModifiedDPTest());
}
INSTANTIATE_TEST_SUITE_P(
	FibonacciModifiedDPTests,
	FibonacciModifiedDPTesFixture,
	::testing::Values(make_tuple("5", 0, 1, 4), make_tuple("27", 0, 1, 5), make_tuple("734", 0, 1, 6), make_tuple("538783", 0, 1, 7), make_tuple("290287121823", 0, 1, 8), make_tuple("2", 2, 0, 0), make_tuple("0", 2, 0, 1), make_tuple("2", 2, 0, 2), make_tuple("4", 2, 0, 3), make_tuple("18", 2, 0, 4), make_tuple("328", 2, 0, 5), make_tuple("107602", 2, 0, 6), make_tuple("11578190732", 2, 0, 7), make_tuple("104292047421056066715537698951727494083004264929891558279344228228718658019003171882044298756195662458280101226593033166933803327203745068186400974453022429724308", 2, 0, 11)));

class FactorialDPTestFixture : public testing::TestWithParam<tuple<long double, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long double FactorialDPTest()
	{
		return FactorialDynamicProgramming(_data);
	}

protected:
	long double _expected;
	long _data;
};
TEST_P(FactorialDPTestFixture, FactorialDPTests)
{
	ASSERT_EQ(this->_expected, this->FactorialDPTest());
}
INSTANTIATE_TEST_SUITE_P(
	FactorialDPTests,
	FactorialDPTestFixture,
	::testing::Values(make_tuple(1, 1), make_tuple(2, 2), make_tuple(6, 3), make_tuple(24, 4), make_tuple(120, 5), make_tuple(2432902008176640000, 20)));

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
	NumberSolitaireTests,
	NumberSolitaireFixture,
	::testing::Values(make_tuple(8, vector<long>{1, -2, 0, 9, -1, -2}), make_tuple(3, vector<long>{1, -2, 4, 3, -1, -3, -7, 4, -9}),
					  make_tuple(-12, vector<long>{0, -4, -5, -2, -7, -9, -3, -10}), make_tuple(-13, vector<long>{-1, -4, -5, -2, -7, -9, -3, -10})));