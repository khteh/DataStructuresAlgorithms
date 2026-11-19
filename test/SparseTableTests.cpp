#include "pch.h"
using namespace std;
// The position of the leftmost best value in [l, r] by a linear scan, to check the sparse table against
template <typename T, typename Compare>
static size_t ScanIndex(vector<T> const &values, size_t l, size_t r, Compare better)
{
	size_t best = l;
	for (size_t x = l + 1; x <= r; x++)
		if (better(values[x], values[best]))
			best = x;
	return best;
}
// Smallest / largest x in [l, r] whose value is at least as good as the bound, or -1, by a linear scan
template <typename T, typename Compare>
static long ScanLeftMost(vector<T> const &values, long l, long r, T const &bound, Compare better)
{
	for (long x = l; x <= r; x++)
		if (!better(bound, values[x]))
			return x;
	return -1;
}
template <typename T, typename Compare>
static long ScanRightMost(vector<T> const &values, long l, long r, T const &bound, Compare better)
{
	for (long x = r; x >= l; x--)
		if (!better(bound, values[x]))
			return x;
	return -1;
}
TEST(SparseTableTests, MinimumTest)
{
	vector<long> values{5, 2, 8, 2, 9, 1, 7};
	SparseTable<long> lowest(values); // less<long>: the minimum
	ASSERT_EQ(5, lowest.Index(0, 6));
	ASSERT_EQ(1, lowest.Best(0, 6));
	ASSERT_EQ(1, lowest.Index(0, 4)); // 2 at both 1 and 3: the leftmost wins
	ASSERT_EQ(3, lowest.Index(2, 4));
	ASSERT_EQ(3, lowest.Index(3, 3)); // A single position
	ASSERT_EQ(9, lowest.Best(4, 4));
}
TEST(SparseTableTests, MaximumTest)
{
	vector<long> values{5, 2, 8, 2, 9, 1, 7};
	SparseTable<long, greater<long>> highest(values);
	ASSERT_EQ(4, highest.Index(0, 6));
	ASSERT_EQ(9, highest.Best(0, 6));
	ASSERT_EQ(2, highest.Index(0, 3));
	ASSERT_EQ(6, highest.Index(5, 6));
	vector<long> ties{3, 9, 1, 9};
	SparseTable<long, greater<long>> highestTies(ties);
	ASSERT_EQ(1, highestTies.Index(0, 3)); // 9 at both 1 and 3: the leftmost wins
	ASSERT_EQ(3, highestTies.Index(2, 3));
}
TEST(SparseTableTests, OtherTypesTest)
{
	vector<double> prices{2.5, -1.25, 3.75, -1.25};
	ASSERT_DOUBLE_EQ(-1.25, SparseTable<double>(prices).Best(0, 3));
	ASSERT_EQ(1, SparseTable<double>(prices).Index(0, 3));
	ASSERT_DOUBLE_EQ(3.75, (SparseTable<double, greater<double>>(prices).Best(0, 3)));
	vector<string> words{"pear", "apple", "zebra", "mango", "apple"};
	SparseTable<string> first(words);
	SparseTable<string, greater<string>> last(words);
	ASSERT_EQ("apple", first.Best(0, 4));
	ASSERT_EQ(1, first.Index(0, 4)); // "apple" at both 1 and 4: the leftmost wins
	ASSERT_EQ("mango", first.Best(2, 3));
	ASSERT_EQ("zebra", last.Best(0, 4));
	ASSERT_EQ(2, last.Index(0, 4));
	vector<uint64_t> big{numeric_limits<uint64_t>::max(), 0, numeric_limits<uint64_t>::max() - 1};
	ASSERT_EQ(1, SparseTable<uint64_t>(big).Index(0, 2)); // 0
	ASSERT_EQ(0, (SparseTable<uint64_t, greater<uint64_t>>(big).Index(0, 2))); // The largest uint64_t
	// The table keeps a reference to the values: from a temporary it would dangle, so that doesn't compile
	static_assert(is_constructible_v<SparseTable<long>, vector<long> &>);
	static_assert(!is_constructible_v<SparseTable<long>, vector<long> &&>);
}
TEST(SparseTableTests, LeftMostRightMostTest)
{
	vector<long> values{5, 2, 8, 2, 9, 1, 7};
	// Minimum table: the first / last value <= bound
	SparseTable<long> lowest(values);
	ASSERT_EQ(1, lowest.LeftMost(0, 6, 2));
	ASSERT_EQ(5, lowest.RightMost(0, 6, 2));
	ASSERT_EQ(3, lowest.LeftMost(2, 4, 2));
	ASSERT_EQ(3, lowest.RightMost(2, 4, 2));
	ASSERT_EQ(-1, lowest.LeftMost(2, 2, 2)); // 8 > 2
	ASSERT_EQ(-1, lowest.RightMost(0, 6, 0)); // Nothing <= 0
	ASSERT_EQ(0, lowest.LeftMost(0, 6, 9)); // Everything <= 9
	ASSERT_EQ(6, lowest.RightMost(0, 6, 9));
	// Maximum table: the first / last value >= bound
	SparseTable<long, greater<long>> highest(values);
	ASSERT_EQ(2, highest.LeftMost(0, 6, 8));
	ASSERT_EQ(4, highest.RightMost(0, 6, 8));
	ASSERT_EQ(-1, highest.LeftMost(0, 6, 10)); // Nothing >= 10
	ASSERT_EQ(6, highest.RightMost(5, 6, 7));
	ASSERT_EQ(-1, highest.RightMost(5, 5, 2)); // 1 < 2
}
// Every [l, r] of every length up to 40 (all the block sizes and overlaps), both orderings, against a linear scan
TEST(SparseTableTests, RandomTest)
{
	mt19937 rng(42);
	for (size_t n = 1; n <= 40; n++)
	{
		vector<long> values(n);
		for (long &v : values)
			v = (long)(rng() % 10) - 5; // Small range: many ties
		SparseTable<long> lowest(values);
		SparseTable<long, greater<long>> highest(values);
		for (size_t l = 0; l < n; l++)
			for (size_t r = l; r < n; r++)
			{
				ASSERT_EQ(ScanIndex(values, l, r, less<long>()), lowest.Index(l, r)) << "n " << n << " [" << l << ", " << r << "]";
				ASSERT_EQ(ScanIndex(values, l, r, greater<long>()), highest.Index(l, r)) << "n " << n << " [" << l << ", " << r << "]";
				for (long bound = -6; bound <= 5; bound++)
				{
					ASSERT_EQ(ScanLeftMost(values, l, r, bound, less<long>()), lowest.LeftMost(l, r, bound));
					ASSERT_EQ(ScanRightMost(values, l, r, bound, less<long>()), lowest.RightMost(l, r, bound));
					ASSERT_EQ(ScanLeftMost(values, l, r, bound, greater<long>()), highest.LeftMost(l, r, bound));
					ASSERT_EQ(ScanRightMost(values, l, r, bound, greater<long>()), highest.RightMost(l, r, bound));
				}
			}
	}
}
