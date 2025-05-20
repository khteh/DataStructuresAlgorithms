#pragma once
template <typename T>
class Permutation
{
private:
    vector<T> InsertItemAt(T, vector<T> &, size_t)
        requires integral_type<T>;
    set<vector<T>> _permutationGameWinningNumbersCache;
    bool IsIncreasingSequence(vector<T> const &)
        requires integral_type<T>;
    string insertCharAt(char, string, size_t);

public:
    set<string> Permute(string const &);
    set<vector<T>> Permute(vector<T> &)
        requires integral_type<T>;
    void GetPermutations(string &, set<string> &, set<string> &);
    vector<T> AbsolutePermutation(size_t, size_t)
        requires integral_type<T>;
    vector<vector<T>> RangePermutations(vector<T>, set<T>, size_t, size_t)
        requires integral_type<T>;
    set<set<T>> RangeUniquePermutations(set<T>, set<T>, size_t, size_t)
        requires integral_type<T>;
    bool PermutationGame(const vector<T>)
        requires integral_type<T>;
};