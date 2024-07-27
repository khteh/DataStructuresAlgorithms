#pragma once
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <ranges>
#include <memory>
#include <concepts>
#include "oneapi/tbb.h"
#include "Vertex.h"
using namespace oneapi::tbb;
using namespace std;
/*
https://en.wikipedia.org/wiki/Fenwick_tree
https://cs.stackexchange.com/questions/10538/bit-what-is-the-intuition-behind-a-binary-indexed-tree-and-how-was-it-thought-a?newreg=7edb322aac564e6a8a22ad783eb5a6ee
*/
template <signed_integral T>
class FenwickTree
{
private:
    T lsb(T);
    vector<T> _data;

public:
    FenwickTree(size_t);
    FenwickTree(vector<T> const &);
    T Query(T);
    void Update(T, T);
};