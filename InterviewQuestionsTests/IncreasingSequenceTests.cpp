#include "pch.h"
using namespace std;
TEST(IncreasingSequenceTests, IncreasingSequenceTest) {
	vector<long> a, b;
	a.clear();
	b.clear();
	a = { 5, 3, 7, 7, 10 };
	b = { 1, 6, 6, 9, 9 };
	ASSERT_EQ(2, IncreasingSequences(a, b));
	a.clear();
	b.clear();
	a = { 1, 5, 6 };
	b = { -2, 0, 2 };
	ASSERT_EQ(0, IncreasingSequences(a, b));
	a.clear();
	b.clear();
	a = { 2, 5 };
	b = { 1, 6 };
	ASSERT_EQ(0, IncreasingSequences(a, b));
	a.clear();
	b.clear();
	a = { 5, -3, 6, 4, 8 };
	b = { 2, 6, -5, 1, 0 };
	ASSERT_EQ(-1, IncreasingSequences(a, b));

	a.clear();
	b.clear();
	a = { 0, 0, 0 };
	b = { 1, 2, 3 };
	ASSERT_EQ(-1, IncreasingSequences(a, b));

	a.clear();
	b.clear();
	a = { 0, 1, 1, 2 };
	b = { 5, 4, 4, 3 };
	ASSERT_EQ(-1, IncreasingSequences(a, b)); // a increasing; b decreasing

	a.clear();
	b.clear();
	a = { 0, 1, 1, 2 };
	b = { 3, 4, 4, 5 };
	ASSERT_EQ(-1, IncreasingSequences(a, b)); // a increasing; b increasing

	a.clear();
	b.clear();
	a = { 2, 1, 1, 0 };
	b = { 5, 4, 4, 3 };
	ASSERT_EQ(-1, IncreasingSequences(a, b)); // a decreasing; b decreasing

	a.clear();
	b.clear();
	a = { 0, 2, 2, 4, 6, 6, 8, 10, 10 };
	b = { 1, 2, 2, 3, 4, 4, 5, 6, 6 };
	ASSERT_EQ(-1, IncreasingSequences(a, b));

	a.clear();
	b.clear();
	a = { 0, 1, 1, 2, 3, 3, 4, 5, 5 };
	b = { 10, 10, 9, 8, 8, 7, 6, 6, 5 };
	ASSERT_EQ(-1, IncreasingSequences(a, b));

	a.clear();
	b.clear();
	a = { 0, -1, -2 };
	b = { -2, 1, 2 };
	ASSERT_EQ(-1, IncreasingSequences(a, b));
	// Performance tests
	a.clear();
	b.clear();
	a.resize(100000);
	b.resize(100000);
	iota(a.begin(), a.end(), 0);
	iota(b.begin(), b.end(), -1000000000); // a and b increasing
	ASSERT_EQ(0, IncreasingSequences(a, b));

	a.clear();
	b.clear();
	a.resize(100000);
	b.resize(100000);
	iota(a.begin(), a.end(), -50000);
	iota(b.begin(), b.end(), 50000);
	sort(a.begin(), a.end(), greater<long>()); // a and b decreasing
	sort(b.begin(), b.end(), greater<long>());
	ASSERT_EQ(-1, IncreasingSequences(a, b));

	a.clear();
	b.clear();
	a.resize(100000);
	b.resize(100000);
	iota(a.begin(), a.end(), 0);		   // a increasing
	iota(b.begin(), b.end(), -1000000000); // b decreasing
	sort(b.begin(), b.end(), greater<long>());
	ASSERT_EQ(-1, IncreasingSequences(a, b));
	a.clear();
	vector<size_t> c = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
	ASSERT_EQ(6, LongestIncreasingSubsequence(c));	   // 0, 2, 6, 9, 13, 15
	ASSERT_EQ(6, LongestIncreasingSubsequenceNlogN(c)); // 0, 2, 6, 9, 13, 15
	c.clear();
	c = { 3, 2, 4, 1, 5 };
	ASSERT_TRUE(increasingTriplet(c));
	ASSERT_EQ(3, LongestIncreasingSubsequenceNlogN(c)); // 3,4,5
	c.clear();
	c = { 1, 1, 1, 1, 1 };
	ASSERT_TRUE(!increasingTriplet(c));
	ASSERT_EQ(1, LongestIncreasingSubsequenceNlogN(c)); // 1
}