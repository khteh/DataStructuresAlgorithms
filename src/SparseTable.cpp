#include "pch.h"
#include "SparseTable.h"
template class SparseTable<int64_t>;
template class SparseTable<uint64_t>;
#ifdef __SIZEOF_INT128__
template class SparseTable<int128_t>;
template class SparseTable<uint128_t>;
#endif
#ifdef _MSC_VER
template class SparseTable<size_t>;
template class SparseTable<long>;
#endif
template<typename T>
// Sparse table: Index(l, r) is the position of the leftmost minimum of values[l .. r], in O(1)
SparseTable<T>::SparseTable(vector<T> const& v)
    : _values(v), _table(bit_width(v.size()), vector<T>(v.size()))
{
    iota(_table[0].begin(), _table[0].end(), 0);
    for (size_t level = 1; level < _table.size(); level++)
        for (size_t x = 0; x + (1UL << level) <= _values.size(); x++) {
            T left = _table[level - 1][x], right = _table[level - 1][x + (1UL << (level - 1))];
            _table[level][x] = _values[right] < _values[left] ? right : left;
        }
}
template<typename T>
T SparseTable<T>::Index(size_t l, size_t r) const
{
    size_t level = bit_width((size_t)(r - l + 1)) - 1;
    T left = _table[level][l], right = _table[level][r - (1L << level) + 1];
    return _values[right] < _values[left] ? right : left;
}
template<typename T>
T SparseTable<T>::Min(size_t l, size_t r) const
{
    return _values[Index(l, r)];
}
// The smallest x in [l, r] with values[x] <= allowedP, or -1
template<typename T>
long SparseTable<T>::LeftMost(long l, long r, T allowedP)
{
    if (Min(l, r) > allowedP)
        return -1L;
    while (l < r) {
        long mid = (l + r) / 2;
        if (Min(l, mid) <= allowedP)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
// The largest x in [l, r] with values[x] <= allowedP, or -1. Binary search: min(values[x .. r]) <= allowedP for every x up to the answer
template<typename T>
long SparseTable<T>::RightMost(long l, long r, T allowedP)
{
    if (Min(l, r) > allowedP)
        return -1L;
    while (l < r) {
        long mid = (l + r + 1) / 2;
        if (Min(mid, r) <= allowedP)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}