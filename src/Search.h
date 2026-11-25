#pragma once
template <typename T>
constexpr T BinomialCoefficients(size_t, size_t);
template <typename T>
constexpr T ceil_div(T, T);
class Search
{
private:
    uint64_t _lcm_ab, _lcm_bc, _lcm_ac, _lcm_abc;
    vector<int> _steps = { 0, 1, 0, -1, 0 } /* four cardinal directions (left, right, up, and down). */, _diagonals = { -1, -1, 1, 1, -1 };
    void _KMPTable(string const&, vector<long>&);
    bool _CanEatAllBananasInTime(vector<size_t> const&, size_t, size_t);
    bool _IsValidSubSequence(vector<size_t> const&, size_t, size_t);
    bool _CanMakeBouquets(vector<size_t> const&, size_t, size_t, size_t);
    bool _HasKthSmallest(size_t, size_t, size_t, size_t);
    bool _HasKthSmallestPairs(vector<long> const&, size_t, long);
    bool _HasNUglyNumbers(size_t, uint64_t, uint64_t, uint64_t, uint64_t);
    bool _WithinThreshold(vector<size_t> const&, size_t, size_t);
    bool _CanWalkFromTopToBottomRow(size_t, size_t, vector<vector<size_t>> const&, size_t);
public:
    void KMPSearch(string const&, string const&, vector<size_t>&);
    vector<long> SearchRange(size_t, vector<size_t> const&);
    long BinarySearch(size_t, vector<size_t> const&);
    long BinarySearchMinimum(vector<long> const& data, long, long);
    int BinarySearchCountUpper(vector<long> const&, long, long, long);
    int BinarySearchCountLower(vector<long> const&, long, long, long);
    int BinarySearch(const string&, vector<string> const&);
    bool GridSearch(vector<string> const&, vector<string> const&);
    vector<string> FindShortestPath(int, int, int, int, int);
    size_t MinEatingSpeed(vector<size_t> const&, size_t);
    size_t MinCapacityToShipWithinDays(vector<size_t> const&, size_t);
    size_t MinimumLargestSum(vector<size_t> const&, size_t);
    long MinDaysToMakeBouquets(vector<size_t> const&, size_t, size_t);
    size_t MultiplicationTableKthSmallestNumber(size_t, size_t, size_t);
    long SmallestDistancePair(vector<long>&, size_t);
    size_t NthUglyNumber(size_t, size_t, size_t, size_t);
    size_t SmallestDivisor(vector<size_t> const&, size_t);
    size_t LatestDayToCross(size_t, size_t, vector<vector<long>> const&);
};