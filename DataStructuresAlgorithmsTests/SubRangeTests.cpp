#include "pch.h"
using namespace std;
TEST(SubRangeTests, ConsecutiveLargestSumTest)
{
	vector<long> a = { 2, 3, -6 }, b;
	long lResult = ConsecutiveLargestSum(a, b);
	ASSERT_EQ(5, lResult);
	a = { 2, 3 };
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = { 2, 3, -6, 4, 5, 6, -20 };
	lResult = ConsecutiveLargestSum(a, b);
	ASSERT_EQ(15, lResult);
	a = { 4, 5, 6 };
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = { 0, -1, 0, 0, 1, 0, -1, -1 }, b;
	ASSERT_EQ(1, ConsecutiveLargestSum(a, b));
	a = { 0, 0, 1 };
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = { -1, -1, -1, -1, -1, -1, 1, 1 };
	ASSERT_EQ(2, ConsecutiveLargestSum(a, b));
	a = { 1, 1 };
	ASSERT_EQ(a, b);
	a.clear();
	b.clear();
	a = { -2, -3, 4, -1, -2, 1, 5, -3 };
	ASSERT_EQ(7, ConsecutiveLargestSum(a, b));
	a = { 4, -1, -2, 1, 5 };
	ASSERT_EQ(a, b);
}
TEST(SubRangeTests, ConsecutiveLargestProductTest)
{
	vector<long> a = { 2, 3, -2, 4 };
	ASSERT_EQ(6, ConsecutiveLargestProduct(a));
	a.clear();
	a = { -2, 0, -1 };
	ASSERT_EQ(0, ConsecutiveLargestProduct(a));
	a.clear();
	a = { -2, -1, 0 };
	ASSERT_EQ(2, ConsecutiveLargestProduct(a));
	a.clear();
	a = { -3, -1, -1 };
	ASSERT_EQ(3, ConsecutiveLargestProduct(a));
	a.clear();
	a = { 0, 2 };
	ASSERT_EQ(2, ConsecutiveLargestProduct(a));
	a.clear();
	a = { 3, -1, 4 };
	ASSERT_EQ(4, ConsecutiveLargestProduct(a));
	a.clear();
	a = { -1, -1 };
	ASSERT_EQ(1, ConsecutiveLargestProduct(a));
	a.clear();
	a = { 0, -2, -3 };
	ASSERT_EQ(6, ConsecutiveLargestProduct(a));
	a.clear();
	a = { 2, -5, -2, -4, 3 };
	ASSERT_EQ(24, ConsecutiveLargestProduct(a));
	a.clear();
	a = { 2, 0, -3, 2, 1, 0, 1, -2 };
	ASSERT_EQ(2, ConsecutiveLargestProduct(a));
}
TEST(SubRangeTests, ConsecutiveSumMinCountTest)
{
	vector<long> a = { 2, 3, 1, 2, 4, 3 };
	ASSERT_EQ(2, ConsecutiveSumMinCount(7, a));
	a.clear();
	ASSERT_EQ(-1, ConsecutiveSumMinCount(1, a));
	a.clear();
	a = { 1, 4, 4 };
	ASSERT_EQ(2, ConsecutiveSumMinCount(5, a));
	ASSERT_EQ(1, ConsecutiveSumMinCount(4, a));
}
TEST(SubRangeTests, LongestNonNegativeSumSliceTest)
{
	vector<long> a = { -1, -1, 1, -1, 1, 0, 1, -1, -1 };
	ASSERT_EQ(7, LongestNonNegativeSumSlice(a));
	a.clear();
	//  [1, 1, −1, −1, −1, −1, −1, 1, 1]: first or last 4
	a = { 1, 1, -1, -1, -1, -1, -1, 1, 1 };
	ASSERT_EQ(4, LongestNonNegativeSumSlice(a));
	a.clear();
	a = { 0, -1, 0, 0, 1, 0, -1, -1 };
	ASSERT_EQ(6, LongestNonNegativeSumSlice(a));
	a.clear();
	a = { -1, -1, -1, -1, -1, -1, 1, 1 };
	ASSERT_EQ(4, LongestNonNegativeSumSlice(a));
}
TEST(SubRangeTests, LongestUpDownAlternatingSubSequenceTest)
{
	vector<long> a = { 1, 2, 51, 50, 60, 55, 70, 68, 80, 76, 75, 12, 45 }, b;
	size_t count = LongestUpDownAlternatingSubSequence(a, b);
	a = { 2, 51, 50, 60, 55, 70, 68, 80, 76 };
	ASSERT_EQ(9, count);
	ASSERT_EQ(9, b.size());
	ASSERT_EQ(a, b);
}
TEST(SubRangeTests, SumPairsTest)
{
	vector<long> a = { 1, 2, 3, 4, 5, 6, 5 };
	// 1, 2, 3, 4, 5, 6, 5
	//    6  5  4
	ASSERT_EQ(2, sumpairs(a, 8));

	a.clear();
	a = { 5, 7, 9, 13, 11, 6, 6, 3, 3 };
	ASSERT_EQ(3, sumpairs(a, 12));

	// long testData[] = { 92,407,1152,403,1419,689,1029,108,128,1307,300,775,622,730,978,526,943,127,566,869,715,983,820,1394,901,606,497,98,1222,843,600,1153,302,1450,1457,973,1431,217,936,958,1258,970,1155,1061,1341,657,333,1151,790,101,588,263,101,534,747,405,585,111,849,695,1256,1508,139,336,1430,615,1295,550,783,575,992,709,828,1447,1457,738,1024,529,406,164,994,1008,50,811,564,580,952,768,863,1225,251,1032,1460,1558 };
	// vector<int> testDataVector(testData, testData + sizeof(testData) / sizeof(testData[0]));
	// assert(sumpairs(a, 8) == 2);
	a.clear();
	a.resize(10);
	iota(a.begin(), a.end(), 0);
	ASSERT_EQ(4, sumpairs(a, 10));
}
TEST(SubRangeTests, ThreeSumTest)
{
	vector<long> a = { -1, 0, 1, 2, -1, -4 };
	vector<vector<long>> grid = { {-1, -1, 2}, {-1, 0, 1} }, grid1;
	grid1 = threeSum(a);
	ASSERT_EQ(grid, grid1);
	a.clear();
	a = { 0, 0, 0 };
	grid = { {0, 0, 0} };
	grid1 = threeSum(a);
	ASSERT_EQ(grid, grid1);
}
TEST(SubRangeTests, FourSumTest)
{
	vector<long> a = { 1, 0, -1, 0, -2, 2 };
	vector<vector<long>> grid = { {-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1} }, grid1;
	grid1 = fourSum(a, 0);
	ASSERT_EQ(grid, grid1);

	a = { -3, -1, 0, 2, 4, 5 };
	grid = { {-3, -1, 2, 4} };
	grid1 = fourSum(a, 2);
	ASSERT_EQ(grid, grid1);
}
TEST(SubRangeTests, DiffPairsTest)
{
	set<long> lSet{ 1, 2, 3, 5, 6, 8, 9, 11, 12, 13 };
	ASSERT_EQ(6, diffpairs(lSet, 3));
	lSet.clear();
	lSet = { 1, 5, 3, 4, 2 };
	ASSERT_EQ(3, diffpairs(lSet, 2));
	lSet.clear();
	lSet = { 1, 3, 5, 8, 6, 4, 2 };
	ASSERT_EQ(5, diffpairs(lSet, 2));

	vector<long> a = { 1, 5, 3, 4, 2 };
	ASSERT_EQ(3, diffpairs(a, 2));
	a.clear();
	a = { 1, 3, 5, 8, 6, 4, 2 };
	ASSERT_EQ(5, diffpairs(a, 2));
}
TEST(SubRangeTests, StockMaxTest)
{
	vector<long> a = { 5, 3, 2 };
	ASSERT_EQ(0, StockMax(a));
	a.clear();
	a = { 1, 2, 100 };
	ASSERT_EQ(197, StockMax(a)); // (100 - 1 = 99) + (100 - 2 = 98) = 197
	a.clear();
	a = { 1, 3, 1, 2 };
	ASSERT_EQ(3, StockMax(a));
}
TEST(SubRangeTests, MaxProfitTest)
{
	vector<long> a = { 23171, 21011, 21123, 21366, 21013, 21367 };
	ASSERT_EQ(356, MaxProfit(a));
}
TEST(SubRangeTests, StockMaxProfitTest)
{
	vector<long> a = { 1, 2, 3, 0, 2, 5 };
	ASSERT_EQ(6, StockMaxProfit(a));
	a.clear();
	a = { 1, 2, 3, 0, 1, 5 };
	ASSERT_EQ(6, StockMaxProfit(a));
	a.clear();
	a = { 1, 2, 6, 0, 1, 5 };
	ASSERT_EQ(9, StockMaxProfit(a));
}