#include "pch.h"
using namespace std;
class CoinsChangeTestFixture : public testing::TestWithParam<tuple<set<vector<size_t>>, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	set<vector<size_t>> CoinsChangeTest()
	{
		_knapsack.ClearCoinsChangeCache();
		return _knapsack.CoinsChange(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	set<vector<size_t>> _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(CoinsChangeTestFixture, CoinChangeTests)
{
	ASSERT_EQ(this->_expected, this->CoinsChangeTest());
}
INSTANTIATE_TEST_SUITE_P(
	CoinsChangeTests,
	CoinsChangeTestFixture,
	::testing::Values(make_tuple(set<vector<size_t>>{}, 0, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{1}}, 1, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{2}, {1, 1}}, 2, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{3}, {1, 2}, {1, 1, 1}}, 3, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{1, 3}, {2, 2}, {1, 1, 2}, {1, 1, 1, 1}}, 4, vector<size_t>{3, 2, 1}),
					  make_tuple(set<vector<size_t>>{{2, 2, 6}, {5, 5}, {2, 3, 5}, {2, 2, 3, 3}, {2, 2, 2, 2, 2}}, 10, vector<size_t>{6, 5, 3, 2}), make_tuple(set<vector<size_t>>{{3, 3, 4}, {3, 7}, {4, 6}, {5, 5}, {10}}, 10, vector<size_t>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25})));
class CoinsChangeDynamicProgrammingTestFixture : public testing::TestWithParam<tuple<set<vector<size_t>>, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	set<vector<size_t>> CoinsChangeDynamicProgrammingTest()
	{
		_knapsack.ClearCoinsChangeCache();
		return _knapsack.CoinsChangeDynamicProgramming(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	set<vector<size_t>> _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(CoinsChangeDynamicProgrammingTestFixture, CoinsChangeDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->CoinsChangeDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	CoinsChangeDynamicProgrammingTests,
	CoinsChangeDynamicProgrammingTestFixture,
	::testing::Values(make_tuple(set<vector<size_t>>{}, 0, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{}, -1, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{1}}, 1, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{2}, {1, 1}}, 2, vector<size_t>{3, 2, 1}), make_tuple(set<vector<size_t>>{{3}, {1, 2}, {1, 1, 1}}, 3, vector<size_t>{3, 2, 1}),
					  make_tuple(set<vector<size_t>>{{1, 3}, {2, 2}, {1, 1, 2}, {1, 1, 1, 1}}, 4, vector<size_t>{3, 2, 1}),
					  make_tuple(set<vector<size_t>>{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 2}, {1, 1, 1, 1, 1, 1, 1, 3}, {1, 1, 1, 1, 1, 1, 2, 2}, {1, 1, 1, 1, 1, 2, 3}, {1, 1, 1, 1, 2, 2, 2}, {1, 1, 1, 1, 3, 3}, {1, 1, 1, 2, 2, 3}, {1, 1, 2, 2, 2, 2}, {1, 1, 2, 3, 3}, {1, 2, 2, 2, 3}, {1, 3, 3, 3}, {2, 2, 2, 2, 2}, {2, 2, 3, 3}}, 10, vector<size_t>{3, 2, 1}),
					  make_tuple(set<vector<size_t>>{{2, 2, 6}, {5, 5}, {2, 3, 5}, {2, 2, 3, 3}, {2, 2, 2, 2, 2}}, 10, vector<size_t>{6, 5, 3, 2}), make_tuple(set<vector<size_t>>{{3, 3, 4}, {3, 7}, {4, 6}, {5, 5}, {10}}, 10, vector<size_t>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25})));
class CoinsChangeUniqueWaysDynamicProgrammingTestFixture : public testing::TestWithParam<tuple<size_t, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	size_t CoinsChangeUniqueWaysDynamicProgrammingTest()
	{
		_knapsack.ClearCoinsChangeCache();
		return _knapsack.CoinsChangeUniqueWaysDynamicProgramming(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	size_t _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(CoinsChangeUniqueWaysDynamicProgrammingTestFixture, CoinsChangeUniqueWaysDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->CoinsChangeUniqueWaysDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	CoinsChangeUniqueWaysDynamicProgrammingTests,
	CoinsChangeUniqueWaysDynamicProgrammingTestFixture,
	::testing::Values(make_tuple(0, 0, vector<size_t>{3, 2, 1}), make_tuple(1, 1, vector<size_t>{3, 2, 1}), make_tuple(2, 2, vector<size_t>{3, 2, 1}), make_tuple(3, 3, vector<size_t>{3, 2, 1}), make_tuple(4, 4, vector<size_t>{3, 2, 1}), make_tuple(2, 5, vector<size_t>{2, 3, 5}) /*{{2,3}, {5}}*/,
					  make_tuple(2, 6, vector<size_t>{2, 3, 5}) /*{{2,2,2}, {3,3}}*/, make_tuple(5, 10, vector<size_t>{6, 5, 3, 2}), make_tuple(96190959, 166, vector<size_t>{5, 37, 8, 39, 33, 17, 22, 32, 13, 7, 10, 35, 40, 2, 43, 49, 46, 19, 41, 1, 12, 11, 28})));

class CoinsChangeDuplicateWaysDynamicProgrammingTestFixture : public testing::TestWithParam<tuple<size_t, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	size_t CoinsChangeDuplicateWaysDynamicProgrammingTest()
	{
		_knapsack.ClearCoinsChangeCache();
		return _knapsack.CoinsChangeDuplicateWaysDynamicProgramming(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	size_t _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(CoinsChangeDuplicateWaysDynamicProgrammingTestFixture, CoinsChangeDuplicateWaysDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->CoinsChangeDuplicateWaysDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	CoinsChangeDuplicateWaysDynamicProgrammingTests,
	CoinsChangeDuplicateWaysDynamicProgrammingTestFixture,
	::testing::Values(make_tuple(0, 0, vector<size_t>{3, 2, 1}), make_tuple(1, 1, vector<size_t>{3, 2, 1}), make_tuple(2, 2, vector<size_t>{3, 2, 1}), make_tuple(4, 3, vector<size_t>{3, 2, 1}) /*{3},{1,2},{2,1},{1,1,1}*/,
					  make_tuple(7, 4, vector<size_t>{3, 2, 1}) /*{3,1},{3,1},{1,1,2},{1,2,1},{2,1,1},{2,2},{1,1,1,1}*/, make_tuple(17, 10, vector<size_t>{6, 5, 3, 2}), make_tuple(3, 5, vector<size_t>{2, 3, 5}), make_tuple(2, 6, vector<size_t>{2, 3, 5})));
class CoinsChangeFewestCoinsDynamicProgrammingTestFixture : public testing::TestWithParam<tuple<long, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	long CoinsChangeFewestCoinsDynamicProgrammingTest()
	{
		return _knapsack.CoinsChangeFewestCoinsDynamicProgramming(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	long _expected, _amount;
	vector<size_t> _coins;
};
TEST_P(CoinsChangeFewestCoinsDynamicProgrammingTestFixture, CoinsChangeFewestCoinsDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->CoinsChangeFewestCoinsDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	CoinsChangeFewestCoinsDynamicProgrammingTests,
	CoinsChangeFewestCoinsDynamicProgrammingTestFixture,
	::testing::Values(make_tuple(3, 11, vector<size_t>{1, 2, 5}), make_tuple(2, 10, vector<size_t>{1, 2, 5}), make_tuple(-1, 3, vector<size_t>{2}), make_tuple(0, 0, vector<size_t>{1}), make_tuple(1, 1, vector<size_t>{1}), make_tuple(2, 2, vector<size_t>{1})));
class StairsClimbingDynamicProgrammingTestFixture : public testing::TestWithParam<tuple<size_t, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	size_t StairsClimbingDynamicProgrammingTest()
	{
		return _knapsack.StairsClimbingDynamicProgramming(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	size_t _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(StairsClimbingDynamicProgrammingTestFixture, StairsClimbingDynamicProgrammingTests)
{
	ASSERT_EQ(this->_expected, this->StairsClimbingDynamicProgrammingTest());
}
INSTANTIATE_TEST_SUITE_P(
	StairsClimbingDynamicProgrammingTests,
	StairsClimbingDynamicProgrammingTestFixture,
	::testing::Values(make_tuple(13, 6, vector<size_t>{1, 2}), make_tuple(24, 6, vector<size_t>{1, 2, 3})));
class StairsClimbingDynamicProgrammingBottomUpTestFixture : public testing::TestWithParam<tuple<size_t, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	size_t StairsClimbingDynamicProgrammingBottomUpTest()
	{
		return _knapsack.StairsClimbingDynamicProgrammingBottomUp(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	size_t _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(StairsClimbingDynamicProgrammingBottomUpTestFixture, StairsClimbingDynamicProgrammingBottomUpTests)
{
	ASSERT_EQ(this->_expected, this->StairsClimbingDynamicProgrammingBottomUpTest());
}
INSTANTIATE_TEST_SUITE_P(
	StairsClimbingDynamicProgrammingBottomUpTests,
	StairsClimbingDynamicProgrammingBottomUpTestFixture,
	::testing::Values(make_tuple(13, 6, vector<size_t>{1, 2}), make_tuple(24, 6, vector<size_t>{1, 2, 3})));
class UnboundedKnapsackTestFixture : public testing::TestWithParam<tuple<size_t, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	size_t UnboundedKnapsackTest()
	{
		return _knapsack.UnboundedKnapsack(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	size_t _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(UnboundedKnapsackTestFixture, UnboundedKnapsackTests)
{
	ASSERT_EQ(this->_expected, this->UnboundedKnapsackTest());
}
INSTANTIATE_TEST_SUITE_P(
	UnboundedKnapsackTests,
	UnboundedKnapsackTestFixture,
	::testing::Values(make_tuple(9, 9, vector<size_t>{2, 3, 4}) /*[3,3,3]*/, make_tuple(12, 12, vector<size_t>{3, 4, 10}) /*[3,3,3,3] or [4,4,4]*/, make_tuple(13, 13, vector<size_t>{3, 4, 10}), make_tuple(16, 16, vector<size_t>{3, 4, 10}), make_tuple(2000, 2000, vector<size_t>{2000, 2000, 2000}), make_tuple(9, 9, vector<size_t>{9, 9, 9}),
					  make_tuple(0, 8, vector<size_t>{9, 9, 9}), make_tuple(9999, 9999, vector<size_t>{1}), make_tuple(9999, 9999, vector<size_t>{1, 2}), make_tuple(10, 10, vector<size_t>{5, 9}), make_tuple(5, 8, vector<size_t>{5, 9}), make_tuple(9, 10, vector<size_t>{9}), make_tuple(9, 9, vector<size_t>{9}), make_tuple(0, 8, vector<size_t>{9})));
class BoundedKnapsackTestFixture : public testing::TestWithParam<tuple<vector<vector<size_t>>, long, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_amount = get<1>(GetParam());
		_coins = get<2>(GetParam());
	}
	vector<vector<size_t>> BoundedKnapsackTest()
	{
		return _knapsack.BoundedKnapsack(_amount, _coins);
	}

protected:
	Knapsack _knapsack;
	vector<vector<size_t>> _expected;
	long _amount;
	vector<size_t> _coins;
};
TEST_P(BoundedKnapsackTestFixture, BoundedKnapsackTests)
{
	ASSERT_EQ(this->_expected, this->BoundedKnapsackTest());
}
INSTANTIATE_TEST_SUITE_P(
	BoundedKnapsackTests,
	BoundedKnapsackTestFixture,
	::testing::Values(make_tuple(vector<vector<size_t>>{}, 6, vector<size_t>{2, 3, 5}), make_tuple(vector<vector<size_t>>{{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}}, 8, vector<size_t>{10, 1, 2, 7, 6, 1, 5})));
class BoundedKnapsackCombinationSumTestFixture : public testing::TestWithParam<tuple<set<vector<size_t>>, size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_k = get<1>(GetParam());
		_sum = get<2>(GetParam());
		_max = get<3>(GetParam());
	}
	set<vector<size_t>> BoundedKnapsackCombinationSumTest()
	{
		return _knapsack.BoundedKnapsackCombinationSum(_k, _sum, _max);
	}

protected:
	Knapsack _knapsack;
	set<vector<size_t>> _expected;
	size_t _k, _sum, _max;
};
TEST_P(BoundedKnapsackCombinationSumTestFixture, BoundedKnapsackCombinationSumTests)
{
	ASSERT_EQ(this->_expected, this->BoundedKnapsackCombinationSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	BoundedKnapsackCombinationSumTests,
	BoundedKnapsackCombinationSumTestFixture,
	::testing::Values(make_tuple(set<vector<size_t>>{{1, 2, 4}}, 3, 7, 10), make_tuple(set<vector<size_t>>{{1, 2, 6}, {1, 3, 5}, {2, 3, 4}}, 3, 9, 10), make_tuple(set<vector<size_t>>{}, 4, 1, 10), make_tuple(set<vector<size_t>>{}, 3, 2, 10),
					  make_tuple(set<vector<size_t>>{{1, 2, 3, 4, 5, 6, 7, 8, 9}}, 9, 45, 10)));
class BoundedCombinationSumWithMaxElementTestFixture : public testing::TestWithParam<tuple<set<vector<size_t>>, size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_k = get<1>(GetParam());
		_sum = get<2>(GetParam());
		_max = get<3>(GetParam());
	}
	set<vector<size_t>> BoundedCombinationSumWithMaxElementTest()
	{
		return _knapsack.BoundedKnapsackCombinationSum(_k, _sum, _max);
	}

protected:
	Knapsack _knapsack;
	set<vector<size_t>> _expected;
	size_t _k, _sum, _max;
};
TEST_P(BoundedCombinationSumWithMaxElementTestFixture, BoundedCombinationSumWithMaxElementTests)
{
	ASSERT_EQ(this->_expected, this->BoundedCombinationSumWithMaxElementTest());
}
INSTANTIATE_TEST_SUITE_P(
	BoundedCombinationSumWithMaxElementTests,
	BoundedCombinationSumWithMaxElementTestFixture,
	::testing::Values(make_tuple(set<vector<size_t>>{{1, 4, 7}, {1, 5, 6}, {2, 3, 7}, {2, 4, 6}, {3, 4, 5}}, 3, 12, 8), make_tuple(set<vector<size_t>>{}, 3, 10, 3), make_tuple(set<vector<size_t>>{{1, 8}, {2, 7}, {3, 6}, {4, 5}}, 2, 9, 10), make_tuple(set<vector<size_t>>{{5}}, 1, 5, 20), make_tuple(set<vector<size_t>>{{1}}, 1, 1, 20)));