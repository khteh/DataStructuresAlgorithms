#include "pch.h"
using namespace std;
template <typename T>
class GreedyAlgorithmFixture
{
protected:
	Greedy<T> _greedy;
	vector<T> _dataCollection1, _dataCollection2;
	T _expected, _data1;
};

class MaxNonOverlappingSegmentsTestFixture : public GreedyAlgorithmFixture<size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_dataCollection1 = get<1>(GetParam());
		_dataCollection2 = get<2>(GetParam());
	}
	size_t MaxNonOverlappingSegmentsTest()
	{
		return _greedy.MaxNonOverlappingSegments(_dataCollection1, _dataCollection2);
	}
};
TEST_P(MaxNonOverlappingSegmentsTestFixture, MaxNonOverlappingSegmentsTests)
{
	ASSERT_EQ(this->_expected, this->MaxNonOverlappingSegmentsTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxNonOverlappingSegmentsTests,
	MaxNonOverlappingSegmentsTestFixture,
	::testing::Values(make_tuple(3, vector<size_t>{1, 3, 7, 9, 9}, vector<size_t>{5, 6, 8, 9, 10}),
					  make_tuple(5, vector<size_t>{1, 6, 7, 9, 10}, vector<size_t>{5, 6, 8, 9, 10}),
					  make_tuple(2, ranges::iota_view(1, 7) | ranges::to<vector<size_t>>(), ranges::iota_view(5, 11) | ranges::to<vector<size_t>>())));
class TieRopesTestTestFixture : public GreedyAlgorithmFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_dataCollection1 = get<2>(GetParam());
	}
	size_t TieRopesTestTest()
	{
		return _greedy.TieRopes(_data1, _dataCollection1);
	}
};
TEST_P(TieRopesTestTestFixture, TieRopesTestTests)
{
	ASSERT_EQ(this->_expected, this->TieRopesTestTest());
}
INSTANTIATE_TEST_SUITE_P(
	TieRopesTestTests,
	TieRopesTestTestFixture,
	::testing::Values(make_tuple(3, 4, vector<size_t>{1, 2, 3, 4, 1, 1, 3})));
class GetMinimumCostTestTestFixture : public GreedyAlgorithmFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_dataCollection1 = get<2>(GetParam());
	}
	size_t GetMinimumCostTest()
	{
		return _greedy.GetMinimumCost(_data1, _dataCollection1);
	}
};
TEST_P(GetMinimumCostTestTestFixture, GetMinimumCostTests)
{
	ASSERT_EQ(this->_expected, this->GetMinimumCostTest());
}
INSTANTIATE_TEST_SUITE_P(
	GetMinimumCostTests,
	GetMinimumCostTestTestFixture,
	::testing::Values(make_tuple(15, 2, vector<size_t>{2, 5, 6}), make_tuple(29, 3, vector<size_t>{1, 3, 5, 7, 9}), make_tuple(163578911, 3, vector<size_t>{390225, 426456, 688267, 800389, 990107, 439248, 240638, 15991, 874479, 568754, 729927, 980985, 132244, 488186, 5037, 721765, 251885, 28458, 23710, 281490, 30935, 897665, 768945, 337228, 533277, 959855, 927447, 941485, 24242, 684459, 312855, 716170, 512600, 608266, 779912, 950103, 211756, 665028, 642996, 262173, 789020, 932421, 390745, 433434, 350262, 463568, 668809, 305781, 815771, 550800})));
class MaxMinTestFixture : public GreedyAlgorithmFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_dataCollection1 = get<2>(GetParam());
	}
	size_t MaxMinTest()
	{
		return _greedy.MaxMin(_data1, _dataCollection1);
	}
};
TEST_P(MaxMinTestFixture, MaxMinTests)
{
	ASSERT_EQ(this->_expected, this->MaxMinTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxMinTests,
	MaxMinTestFixture,
	::testing::Values(make_tuple(20, 3, vector<size_t>{10, 100, 300, 200, 1000, 20, 30}), make_tuple(3, 4, vector<size_t>{1, 2, 3, 4, 10, 20, 30, 40, 100, 200}), make_tuple(0, 2, vector<size_t>{1, 2, 1, 2, 1}), make_tuple(2, 3, vector<size_t>{100, 200, 300, 350, 400, 401, 402})));

class EqualDistributionTestFixture : public GreedyAlgorithmFixture<size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_dataCollection1 = get<1>(GetParam());
	}
	size_t EqualDistributionTest()
	{
		return _greedy.EqualDistribution(_dataCollection1);
	}
};
TEST_P(EqualDistributionTestFixture, EqualDistributionTests)
{
	ASSERT_EQ(this->_expected, this->EqualDistributionTest());
}
INSTANTIATE_TEST_SUITE_P(
	EqualDistributionTests,
	EqualDistributionTestFixture,
	::testing::Values(make_tuple(2, vector<size_t>{1, 1, 5}),
					  make_tuple(2, vector<size_t>{2, 2, 3, 7}),
					  make_tuple(3, vector<size_t>{10, 7, 12}),
					  make_tuple(4, ranges::iota_view(1, 5) | ranges::to<vector<size_t>>()),
					  make_tuple(8, vector<size_t>{1, 3, 5, 7, 9}),
					  make_tuple(927, vector<size_t>{851, 183, 48, 473, 610, 678, 725, 87, 95, 50, 311, 258, 854}),
					  make_tuple(1123, vector<size_t>{249, 666, 500, 101, 227, 85, 963, 681, 331, 119, 448, 587, 668, 398, 802}),
					  make_tuple(5104, vector<size_t>{512, 125, 928, 381, 890, 90, 512, 789, 469, 473, 908, 990, 195, 763, 102, 643, 458, 366, 684, 857, 126, 534, 974, 875, 459, 892, 686, 373, 127, 297, 576, 991, 774, 856, 372, 664, 946, 237, 806, 767, 62, 714, 758, 258, 477, 860, 253, 287, 579, 289, 496})));
