#pragma once
#include <algorithm>
#include <concepts>
#include <set>
#include <map>
#include <vector>
#include <ranges>
#include <sstream>
#include "oneapi/tbb.h"
#include "DataStructuresAlgorithms.h"
using namespace oneapi::tbb;
using namespace std;
template <typename T>
class Permutation
{
private:
    vector<T> InsertItemAt(T toInsert, vector<T> &items, size_t offset)
        requires integral_type<T>;
    set<vector<T>> _permutationGameWinningNumbersCache;
    bool IsIncreasingSequence(vector<T> const &)
        requires integral_type<T>;

public:
    set<string> Permute(string const &);
    set<vector<T>> Permute(vector<T> &)
        requires integral_type<T>;
    void GetPermutations(string &, set<string> &, set<string> &);
    vector<T> AbsolutePermutation(size_t, size_t)
        requires integral_type<T>;
    vector<vector<T>> RangePermutations(vector<T>, set<T>, size_t, size_t)
        requires integral_type<T>;
    bool PermutationGame(const vector<T>)
        requires integral_type<T>;
};