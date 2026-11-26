#pragma once
namespace ranges = std::ranges;
template <typename T>
class SlidingWindow
{
public:
    void MaxSlidingWindow(vector<T> const&, size_t, vector<T>&);
    size_t MaxHarvest(vector<T> const&, size_t);
    size_t SteadyGene(string const&);
    size_t LongestStringWithCharacterReplacement(string const&, size_t);
    size_t LongestCommonSubstringWithFixes(string const&, string const&, size_t);
};
