#pragma once
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <ranges>
#include <memory>
#include <concepts>
#include "GenericConstaints.h"
#include "oneapi/tbb.h"
#include "Vertex.h"
using namespace oneapi::tbb;
using namespace std;
/*
https://en.wikipedia.org/wiki/Fenwick_tree
https://cs.stackexchange.com/questions/10538/bit-what-is-the-intuition-behind-a-binary-indexed-tree-and-how-was-it-thought-a?newreg=7edb322aac564e6a8a22ad783eb5a6ee
*/
template <integral_type T>
class FenwickTree
{
private:
    T lsb(T);
    vector<T> _data;

public:
    FenwickTree();
    explicit FenwickTree(size_t);
    FenwickTree(vector<T> const &);
    void Construct(vector<T> const &);
    T Query(T);
    void Update(T, T);
    size_t InsertionSortShiftCount(vector<T> const &);
};