#include "pch.h"
using namespace std;
TEST(GreedyAlgorithmTests, GreedyAlgorithmTest) {
	vector<size_t> a, b;
	a.clear();
	a = { 1, 3, 7, 9, 9 };
	b.clear();
	b = { 5, 6, 8, 9, 10 };
	ASSERT_EQ(3, MaxNonOverlappingSegments(a, b));
	a.clear();
	a = { 1, 6, 7, 9, 10 };
	b.clear();
	b = { 5, 6, 8, 9, 10 };
	ASSERT_EQ(5, MaxNonOverlappingSegments(a, b)); // No overlapping segments
	a.clear();
	a.resize(6);
	generate(a.begin(), a.end(), [i = 1]() mutable
	{ return i++; });
	b.clear();
	b.resize(6);
	generate(b.begin(), b.end(), [i = 5]() mutable
	{ return i++; });
	ASSERT_EQ(2, MaxNonOverlappingSegments(a, b));
	a.clear();
	a = { 1, 2, 3, 4, 1, 1, 3 };
	ASSERT_EQ(3, TieRopes(a, 4));
	a.clear();
	a = { 2, 5, 6 };
	ASSERT_EQ(15, getMinimumCost(2, a));
	a.clear();
	a = { 1, 3, 5, 7, 9 };
	ASSERT_EQ(29, getMinimumCost(3, a));
	a.clear();
	a = { 10, 100, 300, 200, 1000, 20, 30 };
	ASSERT_EQ(20, maxMin(3, a));
	a.clear();
	a = { 1, 2, 3, 4, 10, 20, 30, 40, 100, 200 };
	ASSERT_EQ(3, maxMin(4, a));
	a.clear();
	a = { 1, 2, 1, 2, 1 };
	ASSERT_EQ(0, maxMin(2, a));
	a.clear();
	a = { 100, 200, 300, 350, 400, 401, 402 };
	ASSERT_EQ(2, maxMin(3, a));
}