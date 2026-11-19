#pragma once
template <typename T>
// Sparse table: Index(l, r) is the position of the leftmost minimum of values[l .. r], in O(1)
class SparseTable {
private:
    vector<T> const& _values;
    vector<vector<T>> _table; // table[level][x]: leftmost minimum of values[x .. x + 2^level - 1]

public:
    SparseTable(vector<T> const&);
    T Index(size_t, size_t) const;
    T Min(size_t, size_t) const;
    long LeftMost(long, long, T);
    long RightMost(long, long, T);
};
