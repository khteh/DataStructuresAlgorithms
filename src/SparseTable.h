#pragma once
/*
 * Sparse table: Index(l, r) is the position of the leftmost "best" of values[l .. r], in O(1) after O(N log N) preprocessing.
 * Compare decides what best means, as a strict weak ordering: Compare(a, b) is true when a is strictly better than b.
 * less<T>, the default, gives the minimum; greater<T> gives the maximum; any other ordering of any T works the same way.
 * The O(1) query covers [l, r] with two power-of-two blocks that may overlap, which is only correct because taking the best of the
 * same value twice changes nothing. So it suits min and max, but not sum, product or xor: use prefix sums or a Fenwick tree for those.
 * The table keeps a reference to the values, which must outlive it: constructing it from a temporary vector is a compile error.
 * Defined in SparseTable.cpp, which instantiates it for the common T and Compare types: add a line there for any other.
 */
template <typename T, typename Compare = less<T>>
    requires strict_weak_order<Compare, T const&, T const&>
class SparseTable {
private:
    vector<T> const& _values;
    vector<vector<size_t>> _table; // _table[level][x]: position of the leftmost best of _values[x .. x + 2^level - 1]
    Compare _compare; // _compare(a, b): a is strictly better than b
    size_t _betterOf(size_t, size_t) const;

public:
    explicit SparseTable(vector<T> const&, Compare = Compare());
    SparseTable(vector<T>&&, Compare = Compare()) = delete; // Would keep a reference to a temporary
    size_t Index(size_t, size_t) const; // Position of the leftmost best value in [l, r]
    T const& Best(size_t, size_t) const; // The best value in [l, r]: the minimum for less<T>, the maximum for greater<T>
    long LeftMost(long, long, T const&) const; // The smallest x in [l, r] whose value is at least as good as the bound, or -1
    long RightMost(long, long, T const&) const; // The largest x in [l, r] whose value is at least as good as the bound, or -1
};
