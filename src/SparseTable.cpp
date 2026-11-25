#include "pch.h"
#include "SparseTable.h"
// Each T with less<T> (minimum) and greater<T> (maximum). For any other T or Compare, add a line here
template class SparseTable<int64_t, less<int64_t>>;
template class SparseTable<int64_t, greater<int64_t>>;
template class SparseTable<uint64_t, less<uint64_t>>;
template class SparseTable<uint64_t, greater<uint64_t>>;
template class SparseTable<double, less<double>>;
template class SparseTable<double, greater<double>>;
template class SparseTable<string, less<string>>;
template class SparseTable<string, greater<string>>;
// Any comparator at runtime, including lambdas: SparseTable<T, function<bool(T const&, T const&)>>
template class SparseTable<int64_t, function<bool(int64_t const&, int64_t const&)>>;
template class SparseTable<uint64_t, function<bool(uint64_t const&, uint64_t const&)>>;
template class SparseTable<double, function<bool(double const&, double const&)>>;
template class SparseTable<string, function<bool(string const&, string const&)>>;
#ifdef __SIZEOF_INT128__
template class SparseTable<int128_t, less<int128_t>>;
template class SparseTable<int128_t, greater<int128_t>>;
template class SparseTable<uint128_t, less<uint128_t>>;
template class SparseTable<uint128_t, greater<uint128_t>>;
#endif
#ifdef _MSC_VER
template class SparseTable<size_t, less<size_t>>;
template class SparseTable<size_t, greater<size_t>>;
template class SparseTable<long, less<long>>;
template class SparseTable<long, greater<long>>;
#endif
/*
“Sparse” is about which ranges have their answer stored ahead of time. There are about N²/2 possible ranges l … r. The sparse table stores the answer for only the ranges whose length is a power of two: 1, 2, 4, 8, ….
That’s about N log₂ N of them. Every other range is answered by combining two stored ones. So the table is a sparse sample of all the ranges.
There is a dense equivalent: store the answer for every range, best[l][r], for all l ≤ r. You build it row by row: best[l][r] is the better of best[l][r − 1] and position r. A query is then a single lookup:

                        Dense table	            Sparse table
Ranges stored	        all of them,            ~N²/2	only power-of-two lengths, ~N log₂ N
Build time and memory	O(N²)	                O(N log N)
Query	                1 lookup	            2 lookups + 1 comparison
Works for sum, xor, …	yes (no overlap needed)	no (the overlap would count twice)
N = 30,000	            ~450 million entries,   ~3.6 GB as 8-byte positions	30,000 × 15 ≈ 450,000 entries, ~3.6 MB

The sparse table costs one extra comparison per query and saves a factor of about N / log N in memory. For the bracket problem, the dense table wouldn’t fit in memory.
For N = 8, as in the )(())(( example, the sparse table stores 8 + 7 + 5 + 1 = 21 of the 36 ranges. That’s not very sparse yet. The saving grows with N.
Where the name comes from: as far as I know, the name was made popular by Bender and Farach-Colton’s paper “The LCA Problem Revisited” (2000). It describes this structure as an improvement on the naive dense O(N²) table for range-minimum queries.

Other structures for the same range queries:
Structure	                                        Build	Query	    Notes
Dense table	                                        O(N²)	O(1)	    only for small N
Sparse table	                                    O(N log N)	O(1)	min/max-like operations only; no updates
Segment tree	                                    O(N)	O(log N)	any associative operation, and supports updating values
Block decomposition + Cartesian tree (Fischer–Heun)	O(N)	O(1)	    optimal, but much more complex
*/
/*
In the bracket problem (String::LongestValidParenthesesWithFixes), use the sparse table on P from the example string "")(())(("".
Here is the sparse table built over P for ")(())((", the example from before:
position:              0    1    2    3    4    5    6    7
P:                     0   -1    0    1    0   -1    0    1

1. Building the table
Row level L stores, for each start position x, the position of the lowest P in the block of 2^L positions starting at x:

level 0 (blocks of 1):   0    1    2    3    4    5    6    7     each position is its own minimum
level 1 (blocks of 2):   1    1    2    4    5    5    6    -
level 2 (blocks of 4):   1    1    5    5    5    -    -    -
level 3 (blocks of 8):   1    -    -    -    -    -    -    -

Each entry is computed from two entries in the row above, because a block of 2^L is two blocks of 2^(L−1) side by side. For example, level 2 at x = 2 is the block 2 … 5:

Its left half 2 … 3 has its minimum at level 1[2] = 2 (P = 0).
Its right half 4 … 5 has its minimum at level 1[4] = 5 (P = −1).
−1 is lower, so the entry is 5.

A “−” means the block would run past the end. There are log₂ N rows of N entries, so building the table takes O(N log N) time and memory, once.
=== Overlap example ===
level 0:  0  1  2  3
level 1:  0  2  2  -      min(3, 9) at 0; min(9, 1) at 2; min(1, 9) at 2
level 2:  2  -  -  -      the better of level 1[0] (3) and level 1[2] (1): position 2

level 1 is a level of 2 items. _table[1][0] and _table[1][1] overlaps at [1], _table[1][1] and _table[1][2] overlaps at [2]
level 2 is a level of 4 items. However, level-1 only has 3. The overlap is at index-1
===
The constructor rejects any comparator for which Compare(a, a) is true.
Compare(a, a) true means a non-strict comparator such as a <= b, which would turn ties into wins and LeftMost / RightMost's "at least as good as the bound" into "strictly better".
This refers to what a non-strict comparator such as less_equal would do to the two places in SparseTable that call _compare. “At least as good as the bound” and “strictly better” differ only in whether a value equal to the bound counts.
1. LeftMost and RightMost: “at least as good as the bound” vs “strictly better”
Both decide whether a position qualifies with this test:

!_compare(bound, value) // the bound is not strictly better than the value

What that means depends on the comparator:

Comparator	            !_compare(bound, value)	            In words	                                Does value == bound qualify?
less (strict)	        !(bound < value) → value <= bound	the value is at least as good as the bound	yes
less_equal (non-strict)	!(bound <= value) → value < bound	the value is strictly better than the bound	no

With less, “good” means small, so “at least as good as 2” is ≤ 2 and “strictly better than 2” is < 2. A non-strict comparator therefore silently drops every value that equals the bound.

Example: values = {5, 2, 8, 2, 9, 1, 7} and LeftMost(0, 6, 2), the first value that’s at most 2:
- With less: position 1, the first 2.
- With less_equal: position 5, the 1, because both 2s now fail the test.

In the bracket problem this is the difference between right and wrong. The bound is the largest P allowed at the other end, and the best end often sits exactly on it. In ((() with K = 0, the () is found only because P[4] = 2 equals the bound 2.

2. _betterOf: “turn ties into wins”
_betterOf picks the right-hand position only if its value is strictly better:

_compare(_values[right], _values[left]) ? right : left

- With less: on equal values, right < left is false, so the left position is kept. This is the leftmost-tie guarantee.
- With less_equal: on equal values, right <= left is true. An equal value now counts as a win for the right position, so Index returns the rightmost tie.

So a non-strict comparator breaks both places at once:

Index quietly changes from leftmost to rightmost.
LeftMost and RightMost stop accepting values equal to the bound.
*/
template <typename T, StrictComparator<T> Compare>
SparseTable<T, Compare>::SparseTable(vector<T> const& v, Compare better, SparseTableTie tie)
    : _values(v), _table(bit_width(v.size()), vector<size_t>(v.size())), _compare(better), _tie(tie)
{
    // A strict ordering never puts a value before itself. Compare(a, a) true means a non-strict comparator such as a <= b, which would
    // turn ties into wins and LeftMost / RightMost's "at least as good as the bound" into "strictly better". O(N), against the O(N log N) build
    for (T const& value : _values)
        if (_compare(value, value))
            throw invalid_argument("SparseTable: Compare must be a strict ordering, but Compare(a, a) is true");
    iota(_table[0].begin(), _table[0].end(), 0); // A block of 1: each position is its own best
    for (size_t level = 1; level < _table.size(); level++)
        for (size_t x = 0; x + (1UL << level) <= _values.size(); x++) // The best of a block of 2^level is the better of its two halves
            _table[level][x] = _betterOf(_table[level - 1][x], _table[level - 1][x + (1UL << (level - 1))]);
}
// The better of positions left <= right; on a tie, left (the default, so that the leftmost best wins) or right (SparseTableTie::Rightmost)
template <typename T, StrictComparator<T> Compare>
size_t SparseTable<T, Compare>::_betterOf(size_t left, size_t right) const
{
    // On a tie (neither value strictly better), left for SparseTableTie::Leftmost, right for SparseTableTie::Rightmost.
    // Index() relies on left <= right: on a tie, the second block's answer is then the overall rightmost, just as the first block's is the leftmost
    return (_compare(_values[right], _values[left]) || (_tie == SparseTableTie::Rightmost && !_compare(_values[left], _values[right]))) ? right : left;
}
/*
Position of the leftmost best value in [l, r].
“Leftmost” says which position you get when the best value occurs more than once in the range. It applies to every use case.

With values = {5, 2, 8, 2, 9, 1, 7}, the minimum of positions 0 … 4 is 2, which appears at both position 1 and position 3. Both are correct answers to “where is the minimum?”. The comment promises the leftmost one, so Index(0, 4) returns 1, never 3. MinimumTest checks exactly this. Without the word, a caller couldn’t rely on either.
How the code guarantees it. _betterOf(left, right) takes the right-hand position only if its value is strictly better. _compare is a strict ordering, so on a tie it’s false, and the left position is kept:

return _compare(_values[right], _values[left]) ? right : left;

That applies at every step:
i)  When building the table, each block is its left half and its right half. On a tie, the left half’s position wins, so every entry is the leftmost best in its block.
ii) In Index() here, the two blocks may overlap. On a tie, the first block’s answer is the overall leftmost:
    - The leftmost best position p in l … r is either in the first block or not.
    - If p is in the first block, that block returns p, because it’s that block’s leftmost best too.
    - If p isn’t in the first block, the first block holds no best value at all, so there’s no tie.
_betterOf keeps the left position unless the right one is strictly better. A tie means neither value is better than the other, and that’s the same idea for any strict weak ordering. So:

Table	                                Values	                            Index(0, 3)	Why
SparseTable<long> (less, min)	        {5, 2, 8, 2}	                    1	        the leftmost of the two minimums
SparseTable<long, greater<long>> (max)	{3, 9, 1, 9}	                    1	        the leftmost of the two maximums
SparseTable<string>	                    {"pear", "apple", "zebra", "apple"}	1	        the leftmost of the two “apple”s

2. Finding the lowest point: Index(l, r) - Continue from 1. in the comment of the constructor.

Any range l … r is covered by two blocks of the same power-of-two size: one starting at l, one ending at r. The size is the largest power of two that fits in the range.
The two blocks may overlap, but that’s harmless: counting the same position twice doesn’t change the minimum. So a lookup is just two table entries and one comparison:

Query	    Length → block size	Block from l	            Block ending at r	        Lowest point
Index(0, 7)	8 → 8	            0 … 7: position 1 (P = −1)	the same block	            1
Index(2, 7)	6 → 4	            2 … 5: position 5 (P = −1)	4 … 7: position 5 (P = −1)	5
Index(2, 4)	3 → 2	            2 … 3: position 2 (P = 0)	3 … 4: position 4 (P = 0)	2 (tie: the leftmost wins)

These match the earlier divide-and-conquer trace: the whole range split at t = 1, and range 2 … 7 split at t = 5.
*/
// [l, r] is covered by two blocks of the largest power of two that fits: [l, l + 2^level) and (r - 2^level, r], which may overlap
template <typename T, StrictComparator<T> Compare>
size_t SparseTable<T, Compare>::Index(size_t l, size_t r) const
{
    size_t level = bit_width(r - l + 1) - 1;
    return _betterOf(_table[level][l], _table[level][r - (1UL << level) + 1]);
}
template <typename T, StrictComparator<T> Compare>
T const& SparseTable<T, Compare>::Best(size_t l, size_t r) const
{
    // The best value in [l, r]: the minimum for less<T>, the maximum for greater<T>
    return _values[Index(l, r)];
}
/*
 * The smallest x in [l, r] whose value is at least as good as the bound (not worse: !_compare(bound, value)), or -1.
 * For less<T>: the first value <= bound. For greater<T>: the first value >= bound.
 * Binary search: Best(l, x) is at least as good as the bound for every x from the answer on.
 */
template <typename T, StrictComparator<T> Compare>
long SparseTable<T, Compare>::LeftMost(long l, long r, T const& bound) const
{
    if (_compare(bound, Best(l, r)))
        return -1L;
    for (;l < r; ) {
        long mid = (l + r) / 2;
        if (!_compare(bound, Best(l, mid)))
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
/*
Finding the farthest end: RightMost(l, r, bound)

This answers “what’s the largest x in l … r whose value is ≤ bound?” The trick is that for a candidate x, “min of values[x … r] ≤ bound” is true for every x up to the answer and false after it. That’s exactly what a binary search needs, and each test is one O(1) Index lookup.

From the earlier trace: i = 1, m = −1, bound 1, looking on the right of t = 1 among odd positions:

l … r	mid	min of oddP[mid … r]	≤ 1?	Next
1 … 7	4	−1 (at position 5)	yes	l = 4
4 … 7	6	1 (at position 7)	yes	l = 6
6 … 7	7	1	yes	l = 7

The answer is j = 7: the substring s[1..7) = (())((, length 6, which is the answer for this string. That took 3 steps instead of scanning 7 positions. LeftMost is the mirror image: it searches for the smallest x, testing min of values[l … mid].
 * The largest x in [l, r] whose value is at least as good as the bound, or -1.
 * Binary search: Best(x, r) is at least as good as the bound for every x up to the answer.
 *
 * SparseTableTie::Rightmost gives you the rightmost tie from Index deliberately. It does that without the LeftMost/RightMost breakage that less_equal would bring along with it:
 *                              Index on ties	LeftMost / RightMost with a value equal to the bound
less, default Leftmost	        leftmost	    qualifies ✓
less, SparseTableTie::Rightmost	rightmost	    qualifies ✓
less_equal (now rejected)	    rightmost	    doesn’t qualify ✗

With values = {5, 2, 8, 2, 9, 1, 7}:

SparseTable<long>(values, {}, SparseTableTie::Rightmost): Index(0, 4) returns 3, the second 2, and LeftMost(0, 6, 2) still returns 1.
A less_equal table, if it were allowed: it would also return 3 from Index, but LeftMost would return 5.
 */
template <typename T, StrictComparator<T> Compare>
long SparseTable<T, Compare>::RightMost(long l, long r, T const& bound) const
{
    if (_compare(bound, Best(l, r)))
        return -1L;
    for (;l < r;) {
        long mid = (l + r + 1) / 2;
        if (!_compare(bound, Best(mid, r)))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
