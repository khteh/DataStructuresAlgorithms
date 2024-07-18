#include "Permutation.h"
template class Permutation<long>;
template class Permutation<string>;
template class Permutation<size_t>;
template <typename T>
set<string> Permutation<T>::Permute(string const &str)
{
    set<string> permutations;
    if (str.empty())
        return permutations;
    else if (str.size() == 1)
    {
        permutations.insert(str);
        return permutations;
    }
    char toInsert = str[0];
    set<string> words = Permute(str.substr(1));
    for (set<string>::iterator it = words.begin(); it != words.end(); it++)
    {
        for (size_t i = 0; i <= it->size(); i++)
            permutations.insert(insertCharAt(toInsert, *it, i));
    }
    return permutations;
}
template <typename T>
vector<T> Permutation<T>::InsertItemAt(T toInsert, vector<T> &items, size_t offset)
    requires integral_type<T>
{
    vector<T> result(items.begin(), items.begin() + offset);
    result.push_back(toInsert);
    result.insert(result.end(), items.begin() + offset, items.end());
    return result;
}
// O(n!)
template <typename T>
set<vector<T>> Permutation<T>::Permute(vector<T> &data)
    requires integral_type<T>
{
    set<vector<T>> permutations;
    if (data.empty())
        return permutations;
    else if (data.size() == 1)
    {
        permutations.insert(vector<T>{data[0]});
        return permutations;
    }
    T toInsert = data[0];
    vector<T> subset(data.begin() + 1, data.end());
    set<vector<T>> combinations = Permute(subset);
    for (typename set<vector<T>>::iterator it = combinations.begin(); it != combinations.end(); it++)
    {
        vector<T> tmp = *it;
        for (size_t offset = 0; offset <= tmp.size(); offset++)
            permutations.insert(InsertItemAt(toInsert, tmp, offset));
    }
    return permutations;
}
template <typename T>
vector<vector<T>> Permutation<T>::RangePermutations(vector<T> sequence, set<T> available, size_t step)
    requires integral_type<T>
{
    vector<vector<T>> result;
    if (available.empty())
    {
        result.push_back(sequence);
        return result;
    }
    for (typename set<T>::iterator it = available.begin(); it != available.end(); it++)
        if (sequence.empty() || abs(*it - sequence.back() >= step))
        {
            vector<T> tmp(sequence);
            tmp.push_back(*it);
            set<T> setTmp(available);
            setTmp.erase(*it);
            vector<vector<T>> tmpResult = RangePermutations(tmp, setTmp, step);
            result.insert(result.end(), tmpResult.begin(), tmpResult.end());
        }
    return result;
}
template <typename T>
void Permutation<T>::GetPermutations(string &w, set<string> &dictionary, set<string> &result)
{
    for (set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
    {
        if (it->size() == w.size() && *it != w)
        {
            size_t count = 0;
            for (size_t i = 0; i < it->size() && count < 2; i++)
                if ((*it)[i] != w[i])
                    count++;
            if (count < 2)
                result.insert(*it);
        }
    }
}
/* https://www.hackerrank.com/challenges/absolute-permutation/problem
 * 100%
 */
template <typename T>
vector<T> Permutation<T>::AbsolutePermutation(size_t n, size_t k)
    requires integral_type<T>
{
    vector<T> sequence(n, 0);
    ranges::generate(sequence, [i = 1]() mutable
                     { return i++; });
    // |sequence[i] - i| = k
    vector<T> a;
    set<T> exists;
    for (size_t i = 1; i <= n; i++)
    {
        if (i > k && exists.find(i - k) == exists.end())
        {
            a.push_back(i - k);
            exists.insert(i - k);
        }
        else if (exists.find(i + k) == exists.end())
        {
            a.push_back(i + k);
            exists.insert(i + k);
        }
        else
            return vector<T>(1, -1);
    }
    vector<T> result(a);
    ranges::sort(a);
    return a == sequence ? result : vector<T>(1, -1);
}
