﻿#include "pch.h"
using namespace std;
TEST(RangeTests, ConsecutiveLargestSumTest)
{
	vector<long> a = {2, 3, -6}, b;
	long lResult = ConsecutiveLargestSum(a, b);
	ASSERT_EQ(5, lResult);
	a = {2, 3};
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = {2, 3, -6, 4, 5, 6, -20};
	lResult = ConsecutiveLargestSum(a, b);
	ASSERT_EQ(15, lResult);
	a = {4, 5, 6};
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = {0, -1, 0, 0, 1, 0, -1, -1}, b;
	ASSERT_EQ(1, ConsecutiveLargestSum(a, b));
	a = {0, 0, 1};
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = {-1, -1, -1, -1, -1, -1, 1, 1};
	ASSERT_EQ(2, ConsecutiveLargestSum(a, b));
	a = {1, 1};
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = {-2, -3, 4, -1, -2, 1, 5, -3};
	ASSERT_EQ(7, ConsecutiveLargestSum(a, b));
	a = {4, -1, -2, 1, 5};
	ASSERT_EQ(a, b);
}
TEST(RangeTests, ConsecutiveLargestProductTest)
{
	vector<long> a = {2, 3, -2, 4};
	ASSERT_EQ(6, ConsecutiveLargestProduct(a));
	a.clear();
	a = {-2, 0, -1};
	ASSERT_EQ(0, ConsecutiveLargestProduct(a));
	a.clear();
	a = {-2, -1, 0};
	ASSERT_EQ(2, ConsecutiveLargestProduct(a));
	a.clear();
	a = {-3, -1, -1};
	ASSERT_EQ(3, ConsecutiveLargestProduct(a));
	a.clear();
	a = {0, 2};
	ASSERT_EQ(2, ConsecutiveLargestProduct(a));
	a.clear();
	a = {3, -1, 4};
	ASSERT_EQ(4, ConsecutiveLargestProduct(a));
	a.clear();
	a = {-1, -1};
	ASSERT_EQ(1, ConsecutiveLargestProduct(a));
	a.clear();
	a = {0, -2, -3};
	ASSERT_EQ(6, ConsecutiveLargestProduct(a));
	a.clear();
	a = {2, -5, -2, -4, 3};
	ASSERT_EQ(24, ConsecutiveLargestProduct(a));
	a.clear();
	a = {2, 0, -3, 2, 1, 0, 1, -2};
	ASSERT_EQ(2, ConsecutiveLargestProduct(a));
}
TEST(RangeTests, ConsecutiveSumMinCountTest)
{
	vector<long> a = {2, 3, 1, 2, 4, 3};
	ASSERT_EQ(2, ConsecutiveSumMinCount(7, a));
	a.clear();
	ASSERT_EQ(-1, ConsecutiveSumMinCount(1, a));
	a.clear();
	a = {1, 4, 4};
	ASSERT_EQ(2, ConsecutiveSumMinCount(5, a));
	ASSERT_EQ(1, ConsecutiveSumMinCount(4, a));
}
TEST(RangeTests, LongestNonNegativeSumSliceTest)
{
	vector<long> a = {-1, -1, 1, -1, 1, 0, 1, -1, -1};
	ASSERT_EQ(7, LongestNonNegativeSumSlice(a));
	a.clear();
	//  [1, 1, −1, −1, −1, −1, −1, 1, 1]: first or last 4
	a = {1, 1, -1, -1, -1, -1, -1, 1, 1};
	ASSERT_EQ(4, LongestNonNegativeSumSlice(a));
	a.clear();
	a = {0, -1, 0, 0, 1, 0, -1, -1};
	ASSERT_EQ(6, LongestNonNegativeSumSlice(a));
	a.clear();
	a = {-1, -1, -1, -1, -1, -1, 1, 1};
	ASSERT_EQ(4, LongestNonNegativeSumSlice(a));
}
TEST(RangeTests, LongestUpDownAlternatingSubSequenceTest)
{
	vector<long> a = {1, 2, 51, 50, 60, 55, 70, 68, 80, 76, 75, 12, 45}, b;
	size_t count = LongestUpDownAlternatingSubSequence(a, b);
	a = {2, 51, 50, 60, 55, 70, 68, 80, 76};
	ASSERT_EQ(9, count);
	ASSERT_EQ(9, b.size());
	ASSERT_EQ(a, b);
}
TEST(RangeTests, SumPairsTest)
{
	vector<long> a = {1, 2, 3, 4, 5, 6, 5};
	// 1, 2, 3, 4, 5, 6, 5
	//    6  5  4
	ASSERT_EQ(2, sumpairs(a, 8));

	a.clear();
	a = {5, 7, 9, 13, 11, 6, 6, 3, 3};
	ASSERT_EQ(3, sumpairs(a, 12));

	// long testData[] = { 92,407,1152,403,1419,689,1029,108,128,1307,300,775,622,730,978,526,943,127,566,869,715,983,820,1394,901,606,497,98,1222,843,600,1153,302,1450,1457,973,1431,217,936,958,1258,970,1155,1061,1341,657,333,1151,790,101,588,263,101,534,747,405,585,111,849,695,1256,1508,139,336,1430,615,1295,550,783,575,992,709,828,1447,1457,738,1024,529,406,164,994,1008,50,811,564,580,952,768,863,1225,251,1032,1460,1558 };
	// vector<int> testDataVector(testData, testData + sizeof(testData) / sizeof(testData[0]));
	// assert(sumpairs(a, 8) == 2);
	a.clear();
	a.resize(10);
	iota(a.begin(), a.end(), 0);
	ASSERT_EQ(4, sumpairs(a, 10));
}
TEST(RangeTests, ThreeSumTest)
{
	vector<long> a = {-1, 0, 1, 2, -1, -4};
	vector<vector<long>> grid = {{-1, -1, 2}, {-1, 0, 1}}, grid1;
	grid1 = threeSum(a);
	ASSERT_EQ(grid, grid1);
	a.clear();
	a = {0, 0, 0};
	grid = {{0, 0, 0}};
	grid1 = threeSum(a);
	ASSERT_EQ(grid, grid1);
}
TEST(RangeTests, FourSumTest)
{
	vector<long> a = {1, 0, -1, 0, -2, 2};
	vector<vector<long>> grid = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}}, grid1;
	grid1 = fourSum(a, 0);
	ASSERT_EQ(grid, grid1);

	a = {-3, -1, 0, 2, 4, 5};
	grid = {{-3, -1, 2, 4}};
	grid1 = fourSum(a, 2);
	ASSERT_EQ(grid, grid1);
}
TEST(RangeTests, DiffPairsTest)
{
	set<long> lSet{1, 2, 3, 5, 6, 8, 9, 11, 12, 13};
	ASSERT_EQ(6, diffpairs(lSet, 3));
	lSet.clear();
	lSet = {1, 5, 3, 4, 2};
	ASSERT_EQ(3, diffpairs(lSet, 2));
	lSet.clear();
	lSet = {1, 3, 5, 8, 6, 4, 2};
	ASSERT_EQ(5, diffpairs(lSet, 2));

	vector<long> a = {1, 5, 3, 4, 2};
	ASSERT_EQ(3, diffpairs(a, 2));
	a.clear();
	a = {1, 3, 5, 8, 6, 4, 2};
	ASSERT_EQ(5, diffpairs(a, 2));
}
TEST(RangeTests, StockMaxTest)
{
	vector<long> a = {5, 3, 2};
	ASSERT_EQ(0, StockMax(a));
	a.clear();
	a = {1, 2, 100};
	ASSERT_EQ(197, StockMax(a)); // (100 - 1 = 99) + (100 - 2 = 98) = 197
	a.clear();
	a = {1, 3, 1, 2};
	ASSERT_EQ(3, StockMax(a));
}
TEST(RangeTests, MaxProfitTest)
{
	vector<long> a = {23171, 21011, 21123, 21366, 21013, 21367};
	ASSERT_EQ(356, MaxProfit(a));
}
TEST(RangeTests, StockMaxProfitTest)
{
	vector<long> a = {1, 2, 3, 0, 2, 5};
	ASSERT_EQ(6, StockMaxProfit(a));
	a.clear();
	a = {1, 2, 3, 0, 1, 5};
	ASSERT_EQ(6, StockMaxProfit(a));
	a.clear();
	a = {1, 2, 6, 0, 1, 5};
	ASSERT_EQ(9, StockMaxProfit(a));
}
TEST(RangeTests, SherlockAndCostTests)
{
	vector<size_t> data = {1, 2, 3};
	ASSERT_EQ(2, sherlockAndCost(data));
	data.clear();
	data = {4, 7, 9};
	ASSERT_EQ(12, sherlockAndCost(data));
	data.clear();
	data = {10, 1, 10, 1, 10};
	ASSERT_EQ(36, sherlockAndCost(data));
}
TEST(RangeTests, ClimbLeaderboardTest)
{
	vector<long> a = {100, 100, 50, 40, 40, 20, 10};
	vector<long> b = {5, 25, 50, 120};
	vector<size_t> expected = {6, 4, 2, 1};
	ASSERT_EQ(expected, ClimbLeaderBoard(a, b));
}
TEST(RangeTests, WiggleMaxLengthTest)
{
	vector<long> a = {1, 7, 4, 9, 2, 5}, b;
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(6, b.size());
	ASSERT_EQ(a, b);
	a.clear();
	a = {0};
	b.clear();
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(1, b.size());
	ASSERT_EQ(0, b.back());
	a.clear();
	a = {0, 0};
	b.clear();
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(1, b.size());
	ASSERT_EQ(0, b.back());
	a.clear();
	b.clear();
	a = {3, 3, 3, 2, 5};
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(3, b.size());
	a.clear();
	a = {3, 2, 5};
	ASSERT_EQ(b, a);
	a.clear();
	a = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
	b.clear();
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(7, b.size());
	a.clear();
	a = {1, 17, 5, 15, 5, 16, 8};
	ASSERT_EQ(a, b);
	a.clear();
	a = {1, 17, 5, 10, 13, 15, 12, 5, 16, 8};
	b.clear();
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(7, b.size());
	a.clear();
	a = {1, 17, 5, 15, 5, 16, 8};
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = {1, 17, 5, 10, 13, 11, 12, 5, 16, 8};
	WiggleMaxLength(a, b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(9, b.size());
}
TEST(RangeTests, ContainsNearbyAlmostDuplicateTests)
{
	vector<long> a;
	a = {1, 2, 3, 1};
	assert(ContainsNearbyAlmostDuplicate(a, 3, 0));
	a.clear();
	a = {1, 0, 1, 1};
	assert(ContainsNearbyAlmostDuplicate(a, 1, 2));
	a.clear();
	a = {1, 5, 9, 1, 5, 9};
	assert(!ContainsNearbyAlmostDuplicate(a, 2, 3));
	assert(!ContainsNearbyAlmostDuplicate(a, 0, 0)); // indices must be distinct
	assert(!ContainsNearbyAlmostDuplicate(a, 0, 1));
	assert(ContainsNearbyAlmostDuplicate(a, 3, 0));
	assert(!ContainsNearbyAlmostDuplicate(a, 2, 0));
	assert(!ContainsNearbyAlmostDuplicate(a, -1, -1));
	a.clear();
	assert(abs(2147483647L - -1) == (long)2147483648);
	assert(abs(-1 - 2147483647L) == (long)2147483648);
	a = {2147483647, -1, 2147483647}; // 0x7FFFF_FFFF, 0xFFFF_FFFF
	assert(!ContainsNearbyAlmostDuplicate(a, 1, 2147483647));
	assert(!ContainsNearbyAlmostDuplicate(a, 1, -2147483648L)); // 2147483648 is 0x8000_0000 = 0xFFFF_FFFF_8000_0000 < 0
	a.clear();
	assert(abs(-INT_MIN - 0x7FFFFFFF) == 1);
	assert(abs(0x7FFFFFFF - -INT_MIN) == 1);
	a = {(long)-2147483648, 2147483647};			 // 0xFFFF_FFFF_8000_0000, 0x7FFF_FFFF
	assert(!ContainsNearbyAlmostDuplicate(a, 1, 1)); // -2147483648 = 0xFFFF_FFFF_8000_0000; 2147483647 = 0x7FFF_FFFF. One in negative bucket, another in positive bucket. Different from abs((long)2147483648 - (long)2147483647)
	a.clear();
	a = {4, 1, -1, 6, 5};
	assert(ContainsNearbyAlmostDuplicate(a, 3, 1));
}
TEST(RangeTests, VectorEqualSplitTests)
{
	vector<int> data;
	data = {1};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {1, 2};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {1, 1};
	assert(VectorEqualSplit(data) == 1);
	data.clear();
	data = {0, 0};
	assert(VectorEqualSplit(data) == 1);
	data.clear();
	data = {0, 0, 0};
	assert(VectorEqualSplit(data) == 2);
	data.clear();
	data = {1, 1, 1};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {2, 2, 2};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {1, 1, 1, 1, 1};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {2, 2, 2, 2, 2};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {1, 1, 1, 1};
	assert(VectorEqualSplit(data) == 2);
	data.clear();
	data = {1, 1, 1, 1, 1, 1};
	assert(VectorEqualSplit(data) == 1);
	data.clear();
	data = {1, 2, 1};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {1, 2, 1, 2};
	assert(VectorEqualSplit(data) == 1);
	data.clear();
	data = {2, 2, 2, 3, 3};
	assert(VectorEqualSplit(data) == 2);
	data.clear();
	data = {3, 2, 3, 2, 2, 2, 2};
	/*
	 * (1) [3 2 3] [2 2 2 2]
	 * (2) [2 2] [2 2]
	 * (3) [2] [2]
	 */
	assert(VectorEqualSplit(data) == 3);
	data.clear();
	data = {1, 1, 1, 1};
	assert(VectorEqualSplit(data) == 2);
	data.clear();
	data = {4, 1, 0, 1, 1, 0, 1};
	assert(VectorEqualSplit(data) == 3);
	data.clear();
	data = {0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 2};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {2, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 2, 0};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {16384, 8192, 8192, 16384, 8192, 8192, 32768, 32768};
	assert(VectorEqualSplit(data) == 4);
	data.clear();
	data = {8760958, 8760957, 547560, 547560, 547560, 273780, 273780, 2190239, 4380479, 4380479, 4380478};
	assert(VectorEqualSplit(data) == 1);
	data.clear();
	data = {0, 0, 0, 0, 0};
	/*
	 * (1) [0] [0 0 0 0]
	 * (2) [0] [0 0 0]
	 * (3) [0] [0 0]
	 * (4) [0] [0]
	 */
	assert(VectorEqualSplit(data) == 4);
	data.clear();
	data = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	assert(VectorEqualSplit(data) == 2);
	data.clear();
	data = {21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211, 21211};
	assert(VectorEqualSplit(data) == 0);
	data.clear();
	data = {999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994, 999999994};
	assert(VectorEqualSplit(data) == 6);
	data.clear();
}