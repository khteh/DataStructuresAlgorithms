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