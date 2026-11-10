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
					  make_tuple(3, 3, 6), make_tuple(4, 3, 14)));
class EggDropsImprovedTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
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
		return _dp.EggDropsImproved(_eggs, _floors);
	}

protected:
	DynamicProgramming<size_t> _dp;
	size_t _expected, _eggs, _floors;
};
TEST_P(EggDropsImprovedTestFixture, EggDropsImprovedTests)
{
	ASSERT_EQ(this->_expected, this->EggDropsTest());
}
INSTANTIATE_TEST_SUITE_P(
	EggDropsImprovedTests,
	EggDropsImprovedTestFixture,
	::testing::Values(make_tuple(0, 123, 0), make_tuple(1, 123, 1),
					  make_tuple(123, 1, 123), make_tuple(2, 2, 2),
					  make_tuple(3, 3, 6), make_tuple(4, 3, 14), make_tuple(16, 6, 10000), make_tuple(14, 100, 10000)));

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
		return _dp.WordBreak2(_str1, _strs);
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
class WaysToFillRangeTestFixture : public WaysToFillRangeTestFixtureBase<BIG_SIGNED_INT>,
								   public testing::TestWithParam<tuple<BIG_SIGNED_INT, size_t, size_t, size_t>>
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
class VectorSlicesSumTestFixture : public testing::TestWithParam<tuple<int64_t, vector<int64_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	int64_t VectorSlicesSumTest()
	{
		return _dp.VectorSlicesSum(_data);
	}

protected:
	DynamicProgramming<int64_t> _dp;
	vector<int64_t> _data;
	int64_t _expected;
};
TEST_P(VectorSlicesSumTestFixture, VectorSlicesSumTests)
{
	ASSERT_EQ(this->_expected, this->VectorSlicesSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	VectorSlicesSumTests,
	VectorSlicesSumTestFixture,
	::testing::Values(make_tuple(44, vector<int64_t>{1, 2, 3}), make_tuple(73, vector<int64_t>{1, 3, 6}), make_tuple(282, vector<int64_t>{1, 3, 6, 7}), make_tuple(971, vector<int64_t>{4, 2, 9, 10, 1}),
					  make_tuple(868784194l, vector<int64_t>{477, 392, 161, 421, 245, 50, 530, 889, 750, 16, 545, 303, 898, 785, 162, 279, 677, 664, 126, 149, 814, 360, 334, 681, 473, 293, 267, 120, 825, 21, 267, 301, 413, 779, 73, 657, 181, 602, 897, 930, 969, 441, 232, 218, 577, 745, 848, 253}),
					  make_tuple(818555228l, vector<int64_t>{695, 14, 706, 200, 379, 690, 991, 128, 60, 998, 730, 381, 301, 559, 192, 686, 608, 907, 256, 584, 177, 319, 843, 87, 446, 37, 520, 464, 483, 685, 894, 177, 50, 952, 376, 781, 641, 718, 908, 700, 715, 989, 432, 367, 547, 624, 52, 507, 530, 659, 90, 58, 978, 932, 497, 423, 321, 16, 238, 803, 52, 484, 979, 101, 435, 706, 881, 427, 423, 141, 126, 489, 129, 909, 207, 28, 884, 610, 534})));
class UniquePathsTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_rows = get<1>(GetParam());
		_cols = get<2>(GetParam());
	}
	size_t UniquePathsTest()
	{
		return _dp.UniquePaths(_rows, _cols);
	}

protected:
	DynamicProgramming<long> _dp;
	size_t _expected, _rows, _cols;
};
TEST_P(UniquePathsTestFixture, UniquePathsTests)
{
	ASSERT_EQ(this->_expected, this->UniquePathsTest());
}
INSTANTIATE_TEST_SUITE_P(
	UniquePathsTests,
	UniquePathsTestFixture,
	::testing::Values(make_tuple(28, 3, 7), make_tuple(3, 3, 2)));
class MinimumEditDistanceTestFixture : public testing::TestWithParam<tuple<size_t, string, string, size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_word1 = get<1>(GetParam());
		_word2 = get<2>(GetParam());
		_inst_cost = get<3>(GetParam());
		_del_cost = get<3>(GetParam());
		_rep_cost = get<3>(GetParam());
	}
	size_t MinimumEditDistanceTest()
	{
		return _dp.MinimumEditDistance(_word1, _word2, _inst_cost, _del_cost, _rep_cost);
	}

protected:
	DynamicProgramming<long> _dp;
	size_t _expected, _inst_cost, _del_cost, _rep_cost;
	string _word1, _word2;
};
TEST_P(MinimumEditDistanceTestFixture, MinimumEditDistanceTests)
{
	ASSERT_EQ(this->_expected, this->MinimumEditDistanceTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinimumEditDistanceTests,
	MinimumEditDistanceTestFixture,
	::testing::Values(make_tuple(3, "horse", "ros", 1, 1, 1), make_tuple(5, "intention", "execution", 1, 1, 1)));
class NonAdjacentMaxSumTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long NonAdjacentMaxSumTest()
	{
		return _dp.NonAdjacentMaxSum(_data);
	}

protected:
	DynamicProgramming<long> _dp;
	long _expected;
	vector<long> _data;
};
TEST_P(NonAdjacentMaxSumTestFixture, NonAdjacentMaxSumTests)
{
	ASSERT_EQ(this->_expected, this->NonAdjacentMaxSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	NonAdjacentMaxSumTests,
	NonAdjacentMaxSumTestFixture,
	::testing::Values(make_tuple(4, vector<long>{1, 2, 3, 1}), make_tuple(12, vector<long>{2, 7, 9, 3, 1}), make_tuple(12, vector<long>{5, 1, 3, 2, 4})));
class MaxZeroProductTestFixture : public testing::TestWithParam<tuple<size_t, vector<long>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_count = get<2>(GetParam());
	}
	size_t MaxZeroProductTest()
	{
		return _dp.MaxZeroProduct(_data, _count);
	}

protected:
	DynamicProgramming<long> _dp;
	size_t _expected, _count;
	vector<long> _data;
};
TEST_P(MaxZeroProductTestFixture, MaxZeroProductTests)
{
	ASSERT_EQ(this->_expected, this->MaxZeroProductTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxZeroProductTests,
	MaxZeroProductTestFixture,
	::testing::Values(
		// Basic cases
		make_tuple(3, vector<long>{7, 15, 6, 20, 5, 10}, 3),							 // 15 * 20 * 10 = 3000
		make_tuple(4, vector<long>{25, 10, 25, 10, 32}, 3),								 // 25 * 25 * 32 = 20000
		make_tuple(2, vector<long>{1, 1, 100}, 3),										 // 100
		make_tuple(2, vector<long>{1, 4, 25}, 3),										 // 4 * 25 = 100
		make_tuple(6, vector<long>{125, 100, 125, 100, 64}, 3),							 // 125 * 125 * 64 = 1000000
		make_tuple(1, vector<long>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3),						 // e.g. 5 * 8 * 9 = 360
		make_tuple(2, vector<long>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3),					 // e.g. 5 * 8 * 10 = 400
		make_tuple(6, vector<long>{2 * 5 * 5, 2 * 2 * 5 * 5, 2 * 2 * 2 * 5 * 5 * 5}, 3), // 2^6 * 5^7
		// The best triple is not the one with the most 2s or the most 5s
		make_tuple(5, vector<long>{4, 8, 16, 25, 625, 3125}, 3), // 16 * 625 * 3125 = 2^4 * 5^9 -> 4; 8 * 16 * 3125 = 2^7 * 5^5 -> 5
		// No zeros possible
		make_tuple(0, vector<long>{1, 1, 101}, 3),	 // no 2s or 5s
		make_tuple(0, vector<long>{1, 25, 25}, 3),	 // 5s only
		make_tuple(0, vector<long>{2, 4, 8}, 3),	 // 2s only: no element has any 5s
		make_tuple(0, vector<long>{3, 7, 9, 11}, 3), // neither
		// Large values
		make_tuple(21, vector<long>{10, 1000, 1000000000, 1000000000}, 3),
		make_tuple(27, vector<long>{100000000, 1000000000, 1000000000, 2000000000}, 3),
		make_tuple(13, vector<long>{1220703125, 1073741824, 1}, 3), // 5^13 * 2^30: the most 5s / 2s in a positive int
		// Fewer elements than count
		make_tuple(0, vector<long>{}, 3),
		make_tuple(0, vector<long>{10, 100}, 3),
		// Other counts
		make_tuple(3, vector<long>{10, 1000, 7}, 1),
		make_tuple(13, vector<long>{1220703125, 8192}, 2),	   // 5^13 * 2^13
		make_tuple(4, vector<long>{10, 1000, 7, 3}, 2),		   // 10 * 1000
		make_tuple(10, vector<long>{10, 100, 1000, 10000}, 4), // all four
		// Zeros are skipped
		make_tuple(0, vector<long>{0, 0, 0}, 3),
		make_tuple(6, vector<long>{0, 10, 100, 1000}, 3),
		// Negative numbers: the sign doesn't change the trailing zeros
		make_tuple(3, vector<long>{-7, -15, 6, -20, 5, -10}, 3),
		make_tuple(6, vector<long>{-10, -100, -1000}, 3)));