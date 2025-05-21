#include "pch.h"
using namespace std;
class LargestNumberCompositionProductTestFixture : public testing::TestWithParam<tuple<size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
	}
	size_t LargestNumberCompositionProductTest()
	{
		return _dp.LargestNumberCompositionProduct(_n);
	}

protected:
	DynamicProgramming<size_t> _dp;
	size_t _expected, _n;
};
TEST_P(LargestNumberCompositionProductTestFixture, LargestNumberCompositionProductTests)
{
	ASSERT_EQ(this->_expected, this->LargestNumberCompositionProductTest());
}
INSTANTIATE_TEST_SUITE_P(
	LargestNumberCompositionProductTests,
	LargestNumberCompositionProductTestFixture,
	::testing::Values(make_tuple(1, 2), make_tuple(36, 10)));
class EggDropsTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
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
		return _dp.EggDrops(_eggs, _floors);
	}

protected:
	DynamicProgramming<size_t> _dp;
	size_t _expected, _eggs, _floors;
};
TEST_P(EggDropsTestFixture, EggDropsTests)
{
	ASSERT_EQ(this->_expected, this->EggDropsTest());
}
INSTANTIATE_TEST_SUITE_P(
	EggDropsTests,
	EggDropsTestFixture,
	::testing::Values(make_tuple(0, 123, 0), make_tuple(1, 123, 1),
					  make_tuple(123, 1, 123), make_tuple(2, 2, 2),
					  make_tuple(3, 3, 6)));

class WordBreakTestFixture : public testing::TestWithParam<tuple<bool, string, set<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_strs = get<2>(GetParam());
	}
	bool WordBreakTest()
	{
		return _dp.WordBreak(_str1, _strs);
	}

protected:
	DynamicProgramming<string> _dp;
	string _str1;
	set<string> _strs;
	bool _expected;
};
TEST_P(WordBreakTestFixture, WordBreakTests)
{
	ASSERT_EQ(this->_expected, this->WordBreakTest());
}
INSTANTIATE_TEST_SUITE_P(
	WordBreakTests,
	WordBreakTestFixture,
	::testing::Values(make_tuple(true, "HelloWorld", set<string>{"Hello", "World"}), make_tuple(false, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(true, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}), make_tuple(true, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(true, "applepenapple", set<string>{"apple", "pen"}), make_tuple(true, "aaaaaaa", set<string>{"aaaa", "aaa"})));
class WordBreak2TestFixture : public testing::TestWithParam<tuple<vector<string>, string, set<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_str1 = get<1>(GetParam());
		_strs = get<2>(GetParam());
	}
	vector<string> WordBreak2Test()
	{
		vector<string> result;
		_dp.WordBreak2(_str1, _strs, result);
		return result;
	}

protected:
	DynamicProgramming<string> _dp;
	string _str1;
	set<string> _strs;
	vector<string> _expected;
};
TEST_P(WordBreak2TestFixture, WordBreak2Tests)
{
	ASSERT_EQ(this->_expected, this->WordBreak2Test());
}
INSTANTIATE_TEST_SUITE_P(
	WordBreak2Tests,
	WordBreak2TestFixture,
	::testing::Values(make_tuple(vector<string>{"Hello World"}, "HelloWorld", set<string>{"Hello", "World"}),
					  make_tuple(vector<string>{}, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"cat sand dog", "cats and dog"}, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"cat and dog"}, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
					  make_tuple(vector<string>{"apple pen apple"}, "applepenapple", set<string>{"apple", "pen"}),
					  make_tuple(vector<string>{"aaa aaaa", "aaaa aaa"}, "aaaaaaa", set<string>{"aaaa", "aaa"})));
class AbbreviationTestFixture : public testing::TestWithParam<tuple<bool, string, string>>
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
		return _dp.Abbreviation(_str1, _str2);
	}

protected:
	DynamicProgramming<string> _dp;
	string _str1, _str2;
	bool _expected;
};
TEST_P(AbbreviationTestFixture, AbbreviationTests)
{
	ASSERT_EQ(this->_expected, this->AbbreviationTest());
}
INSTANTIATE_TEST_SUITE_P(
	AbbreviationTests,
	AbbreviationTestFixture,
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
	size_t FindSubsequenceTest()
	{
		return _dp.FindSubsequence(_str1, _str2);
	}

protected:
	DynamicProgramming<string> _dp;
	string _str1, _str2;
	size_t _expected;
};
TEST_P(FindSubsequenceTestFixture, FindSubsequenceTests)
{
	ASSERT_EQ(this->_expected, this->FindSubsequenceTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindSubsequenceTests,
	FindSubsequenceTestFixture,
	::testing::Values(make_tuple(2, "1221", "12"), make_tuple(0, "1234", "56"), make_tuple(15, "kkkkkkz", "kkkk"), make_tuple(6, "kkkkkkz", "kkkkk"), make_tuple(1, "kkkkkkz", "kkkkkk"), make_tuple(0, "DeadBeef", "FeedBeef"), make_tuple(1, "DeadBeef", "Beef"), make_tuple(1, "DeadBeef", "dBeef"), make_tuple(0, "DeadBeef", "eedBeef"), make_tuple(1, "DeadBeef", "edBeef")));
template <typename T>
class FibonacciTestFixtureBase
{
public:
	void SetUp(T expected, long n)
	{
		_expected = expected;
		_n = n;
	}
	T FibonacciTest()
	{
		return _dp.Fibonacci(_n);
	}

protected:
	DynamicProgramming<T> _dp;
	T _expected;
	long _n;
};

class FibonacciTestFixture :
#if defined(__GNUC__) || defined(__GNUG__)
	public FibonacciTestFixtureBase<__int128>,
	public testing::TestWithParam<tuple<__int128, long>>
#else
	public FibonacciTestFixtureBase<long long>,
	public testing::TestWithParam<tuple<long long, long>>
#endif
{
public:
	void SetUp() override
	{
		FibonacciTestFixtureBase::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
};
TEST_P(FibonacciTestFixture, FibonacciTests)
{
	ASSERT_EQ(this->_expected, this->FibonacciTest());
}
INSTANTIATE_TEST_SUITE_P(
	FibonacciTests,
	FibonacciTestFixture,
	::testing::Values(make_tuple(-1, -1), make_tuple(0, 0), make_tuple(1, 1), make_tuple(1, 2), make_tuple(2, 3), make_tuple(3, 4), make_tuple(5, 5), make_tuple(8, 6), make_tuple(13, 7), make_tuple(21, 8), make_tuple(34, 9), make_tuple(2880067194370816120, 90)));
class FibonacciModifiedTestFixture : public testing::TestWithParam<tuple<string, long, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_t1 = get<1>(GetParam());
		_t2 = get<2>(GetParam());
		_n = get<3>(GetParam());
	}
	string FibonacciModifiedTest()
	{
		return _dp.FibonacciModified(_t1, _t2, _n);
	}

protected:
	DynamicProgramming<long> _dp;
	long _t1, _t2, _n;
	string _expected;
};
TEST_P(FibonacciModifiedTestFixture, FibonacciModifiedTests)
{
	ASSERT_EQ(this->_expected, this->FibonacciModifiedTest());
}
INSTANTIATE_TEST_SUITE_P(
	FibonacciModifiedTests,
	FibonacciModifiedTestFixture,
	::testing::Values(make_tuple("5", 0, 1, 4), make_tuple("27", 0, 1, 5), make_tuple("734", 0, 1, 6), make_tuple("538783", 0, 1, 7), make_tuple("290287121823", 0, 1, 8), make_tuple("2", 2, 0, 0), make_tuple("0", 2, 0, 1), make_tuple("2", 2, 0, 2), make_tuple("4", 2, 0, 3), make_tuple("18", 2, 0, 4), make_tuple("328", 2, 0, 5), make_tuple("107602", 2, 0, 6), make_tuple("11578190732", 2, 0, 7), make_tuple("104292047421056066715537698951727494083004264929891558279344228228718658019003171882044298756195662458280101226593033166933803327203745068186400974453022429724308", 2, 0, 11)));

template <typename T>
class FactorialTestFixtureBase
{
public:
	void SetUp(T expected, size_t n, T modulo)
	{
		_expected = expected;
		_n = n;
		_modulo = modulo;
	}
	T FactorialTest()
	{
		return _dp.Factorial(_n, _modulo);
	}

protected:
	DynamicProgramming<T> _dp;
	T _expected, _modulo;
	size_t _n;
};

class FactorialTestFixture :
#if defined(__GNUC__) || defined(__GNUG__)
	public FactorialTestFixtureBase<__int128>,
	public testing::TestWithParam<tuple<__int128, size_t, size_t>>
#else
	public FactorialTestFixtureBase<long long>,
	public testing::TestWithParam<tuple<long long, size_t, size_t>>
#endif

{
public:
	void SetUp() override
	{
		FactorialTestFixtureBase::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
};
TEST_P(FactorialTestFixture, FactorialTests)
{
	ASSERT_EQ(this->_expected, this->FactorialTest());
}
/*
https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
As an extension the integer scalar type __int128 is supported for targets which have an integer mode wide enough to hold 128 bits. Simply write __int128 for a signed 128-bit integer, or unsigned __int128 for an unsigned 128-bit integer.
There is no support in GCC for expressing an integer constant of type __int128 for targets with long long integer less than 128 bits wide.

sizeof(long long): 8 (64-bit) ::max() = 9223372036854775807. So, the max constant is 20!
*/
INSTANTIATE_TEST_SUITE_P(
	FactorialTests,
	FactorialTestFixture,
	::testing::Values(make_tuple(178290591, 14, 1e9 + 7), make_tuple(146326063, 20, 1e9 + 7), make_tuple(440732388, 25, 1e9 + 7), make_tuple(2432902008176640000, 20, 0)));
class NumberSolitaireTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long NumberSolitaireTest()
	{
		return _dp.NumberSolitaire(_data);
	}

protected:
	DynamicProgramming<long> _dp;
	vector<long> _data;
	long _expected;
};
TEST_P(NumberSolitaireTestFixture, NumberSolitaireTests)
{
	ASSERT_EQ(this->_expected, this->NumberSolitaireTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberSolitaireTests,
	NumberSolitaireTestFixture,
	::testing::Values(make_tuple(8, vector<long>{1, -2, 0, 9, -1, -2}), make_tuple(3, vector<long>{1, -2, 4, 3, -1, -3, -7, 4, -9}),
					  make_tuple(-12, vector<long>{0, -4, -5, -2, -7, -9, -3, -10}), make_tuple(-13, vector<long>{-1, -4, -5, -2, -7, -9, -3, -10})));
template <typename T>
class WaysToFillRangeTestFixtureBase
{
public:
	void SetUp(T expected, size_t n, size_t k, size_t x)
	{
		_expected = expected;
		_n = n;
		_k = k;
		_x = x;
	}
	T WaysToFillRangeTest()
	{
		return _dp.WaysToFillRange(_n, _k, _x);
	}

protected:
	DynamicProgramming<T> _dp;
	T _expected;
	size_t _n, _k, _x;
};
class WaysToFillRangeTestFixture :
#if defined(__GNUC__) || defined(__GNUG__)
	public WaysToFillRangeTestFixtureBase<__int128>,
	public testing::TestWithParam<tuple<__int128, size_t, size_t, size_t>>
#else
	public WaysToFillRangeTestFixtureBase<unsigned long long>,
	public testing::TestWithParam<tuple<unsigned long long, size_t, size_t, size_t>>
#endif
{
public:
	void SetUp() override
	{
		WaysToFillRangeTestFixtureBase::SetUp(get<0>(GetParam()),
											  get<1>(GetParam()),
											  get<2>(GetParam()),
											  get<3>(GetParam()));
	}
};
TEST_P(WaysToFillRangeTestFixture, WaysToFillRangeTests)
{
	ASSERT_EQ(this->_expected, this->WaysToFillRangeTest());
}
INSTANTIATE_TEST_SUITE_P(
	WaysToFillRangeTests,
	WaysToFillRangeTestFixture,
	::testing::Values(make_tuple(2, 3, 3, 1), make_tuple(1, 3, 3, 2), make_tuple(3, 4, 3, 2), make_tuple(0, 5, 2, 2), make_tuple(236568308, 761, 99, 1), make_tuple(151337967, 100000, 100000, 1), make_tuple(413130667, 72071, 66860, 44594)));
class FloydWarshallTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<vector<long>>, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
		_edges = get<2>(GetParam());
		_queries = get<3>(GetParam());
	}
	vector<long> FloydWarshallTest()
	{
		vector<long> result;
		vector<vector<long>> distances;
		_dp.FloydWarshall(_n, _edges, distances);
		for (vector<vector<size_t>>::const_iterator it = _queries.begin(); it != _queries.end(); it++)
			result.push_back(distances[(*it)[0]][(*it)[1]] == numeric_limits<long>::max() ? -1 : distances[(*it)[0]][(*it)[1]]);
		return result;
	}

protected:
	DynamicProgramming<long> _dp;
	vector<vector<long>> _edges;
	vector<long> _expected;
	vector<vector<size_t>> _queries;
	size_t _n;
};
TEST_P(FloydWarshallTestFixture, FloydWarshallTests)
{
	ASSERT_EQ(this->_expected, this->FloydWarshallTest());
}
INSTANTIATE_TEST_SUITE_P(
	FloydWarshallTests,
	FloydWarshallTestFixture,
	::testing::Values(make_tuple(vector<long>{70, -1, 130, 40, 70, 20, -1, 20}, 5, vector<vector<long>>{{1, 2, 20}, {1, 3, 50}, {1, 4, 70}, {1, 5, 90}, {2, 3, 30}, {3, 4, 40}, {4, 5, 60}},
								 vector<vector<size_t>>{{1, 4},
														{5, 1},
														{2, 5},
														{3, 4},
														{1, 4},
														{1, 2},
														{3, 1},
														{1, 2}}),
					  make_tuple(vector<long>{150, 1, 99, 1}, 4, vector<vector<long>>{{1, 2, 1}, {3, 2, 150}, {4, 3, 99}, {1, 4, 100}, {3, 1, 200}},
								 vector<vector<size_t>>{{3, 2},
														{1, 2},
														{4, 3},
														{1, 2}}),
					  make_tuple(vector<long>{6, -1, 0, 106}, 4, vector<vector<long>>{{2, 1, 298}, {3, 4, 299}, {2, 4, 200}, {2, 4, 100}, {3, 2, 300}, {3, 2, 6}},
								 vector<vector<size_t>>{{3, 2},
														{4, 1},
														{1, 1},
														{3, 4}}),
					  make_tuple(vector<long>{5, -1, 11}, 4, vector<vector<long>>{{1, 2, 5}, {1, 4, 24}, {2, 4, 6}, {3, 4, 4}, {3, 2, 7}},
								 vector<vector<size_t>>{{1, 2},
														{3, 1},
														{1, 4}})));
class VectorSlicesSumTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long VectorSlicesSumTest()
	{
		return _dp.VectorSlicesSum(_data);
	}

protected:
	DynamicProgramming<long> _dp;
	vector<long> _data;
	long _expected;
};
TEST_P(VectorSlicesSumTestFixture, VectorSlicesSumTests)
{
	ASSERT_EQ(this->_expected, this->VectorSlicesSumTest());
}
#if defined(__GNUC__) || defined(__GNUG__)
INSTANTIATE_TEST_SUITE_P(
	VectorSlicesSumTests,
	VectorSlicesSumTestFixture,
	::testing::Values(make_tuple(44, vector<long>{1, 2, 3}), make_tuple(73, vector<long>{1, 3, 6}), make_tuple(282, vector<long>{1, 3, 6, 7}), make_tuple(971, vector<long>{4, 2, 9, 10, 1}),
					  make_tuple(868784194l, vector<long>{477, 392, 161, 421, 245, 50, 530, 889, 750, 16, 545, 303, 898, 785, 162, 279, 677, 664, 126, 149, 814, 360, 334, 681, 473, 293, 267, 120, 825, 21, 267, 301, 413, 779, 73, 657, 181, 602, 897, 930, 969, 441, 232, 218, 577, 745, 848, 253}),
					  make_tuple(818555228l, vector<long>{695, 14, 706, 200, 379, 690, 991, 128, 60, 998, 730, 381, 301, 559, 192, 686, 608, 907, 256, 584, 177, 319, 843, 87, 446, 37, 520, 464, 483, 685, 894, 177, 50, 952, 376, 781, 641, 718, 908, 700, 715, 989, 432, 367, 547, 624, 52, 507, 530, 659, 90, 58, 978, 932, 497, 423, 321, 16, 238, 803, 52, 484, 979, 101, 435, 706, 881, 427, 423, 141, 126, 489, 129, 909, 207, 28, 884, 610, 534})));
#else
INSTANTIATE_TEST_SUITE_P(
	VectorSlicesSumTests,
	VectorSlicesSumTestFixture,
	::testing::Values(make_tuple(44, vector<long>{1, 2, 3}), make_tuple(73, vector<long>{1, 3, 6}), make_tuple(282, vector<long>{1, 3, 6, 7}), make_tuple(971, vector<long>{4, 2, 9, 10, 1})));
#endif