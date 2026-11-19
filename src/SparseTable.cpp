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
template <typename T, typename Compare>
    requires strict_weak_order<Compare, T const&, T const&>
SparseTable<T, Compare>::SparseTable(vector<T> const& v, Compare better)
    : _values(v), _table(bit_width(v.size()), vector<size_t>(v.size())), _better(better)
{
    iota(_table[0].begin(), _table[0].end(), 0); // A block of 1: each position is its own best
    for (size_t level = 1; level < _table.size(); level++)
        for (size_t x = 0; x + (1UL << level) <= _values.size(); x++) // The best of a block of 2^level is the better of its two halves
            _table[level][x] = _best(_table[level - 1][x], _table[level - 1][x + (1UL << (level - 1))]);
}
// The better of positions left < right; on a tie, left, so that the leftmost best wins
template <typename T, typename Compare>
    requires strict_weak_order<Compare, T const&, T const&>
size_t SparseTable<T, Compare>::_best(size_t left, size_t right) const
{
    return _better(_values[right], _values[left]) ? right : left;
}
// [l, r] is covered by two blocks of the largest power of two that fits: [l, l + 2^level) and (r - 2^level, r], which may overlap
template <typename T, typename Compare>
    requires strict_weak_order<Compare, T const&, T const&>
size_t SparseTable<T, Compare>::Index(size_t l, size_t r) const
{
    size_t level = bit_width(r - l + 1) - 1;
    return _best(_table[level][l], _table[level][r - (1UL << level) + 1]);
}
template <typename T, typename Compare>
    requires strict_weak_order<Compare, T const&, T const&>
T const& SparseTable<T, Compare>::Best(size_t l, size_t r) const
{
    return _values[Index(l, r)];
}
/*
 * The smallest x in [l, r] whose value is at least as good as the bound (not worse: !_better(bound, value)), or -1.
 * For less<T>: the first value <= bound. For greater<T>: the first value >= bound.
 * Binary search: Best(l, x) is at least as good as the bound for every x from the answer on.
 */
template <typename T, typename Compare>
    requires strict_weak_order<Compare, T const&, T const&>
long SparseTable<T, Compare>::LeftMost(long l, long r, T const& bound) const
{
    if (_better(bound, Best(l, r)))
        return -1L;
    while (l < r) {
        long mid = (l + r) / 2;
        if (!_better(bound, Best(l, mid)))
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
/*
 * The largest x in [l, r] whose value is at least as good as the bound, or -1.
 * Binary search: Best(x, r) is at least as good as the bound for every x up to the answer.
 */
template <typename T, typename Compare>
    requires strict_weak_order<Compare, T const&, T const&>
long SparseTable<T, Compare>::RightMost(long l, long r, T const& bound) const
{
    if (_better(bound, Best(l, r)))
        return -1L;
    while (l < r) {
        long mid = (l + r + 1) / 2;
        if (!_better(bound, Best(mid, r)))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
