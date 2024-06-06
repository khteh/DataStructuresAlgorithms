#pragma once
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <math.h>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
using namespace tbb;
#endif
using namespace std;
typedef enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	NoChange
} direction_t;
class Range
{
public:
	long NumberSolitaire(vector<long> const &);
	long ConsecutiveMaximumSum(vector<long> const &, vector<long> &);
	size_t ConsecutiveMaximumSumModulo(vector<long> const &, size_t);
	long ConsecutiveLargestProduct(vector<long> const &);
	size_t MinSumSubSequence(size_t, vector<size_t> const &);
	long LongestNonNegativeSumSlice(vector<long> const &);
	size_t SumPairs(size_t, vector<size_t> const &);
	size_t GreaterThanSumPairs(size_t, vector<size_t> const &);
	vector<vector<long>> TripletsZeroSum(vector<long> &);
	vector<vector<long>> QuadrupletsSum(long, vector<long> &);
	size_t LongestUpDownAlternatingSubSequence(vector<long> const &, vector<long> &);
	size_t NumberDiffPairs(long, vector<long> const &);
	size_t NumberDiffPairs(long, set<long> const &);
	size_t StockMax(vector<long> const &);
	long MaxProfit(vector<long> const &);
	long MinimumLoss(vector<long> const &);
	long StockMaxProfit(vector<long> const &);
	long StockMaxProfit1(vector<long> const &);
	size_t SherlockAndCost(vector<size_t> const &);
	vector<size_t> WiggleMaxLength(vector<size_t> const &);
	bool ContainsNearbyAlmostDuplicate(vector<long> const &, long, long);
	size_t VectorEqualSplit(vector<int> const &); // Only tested working with int type.
	size_t MaxProductOfNonOverlappingWordLengths(vector<string> const &);
	string AlmostSorted(vector<long> const &);
	long MinimumBribes(size_t, vector<long> const &);
	size_t PickNumbersFromRange(vector<size_t> const &);
	vector<long> LastNumbers(size_t, long, long);
	size_t MaxNonDivisableSubset(vector<size_t> const &, size_t);
	size_t HackerlandRadioTransmitters(vector<size_t> &, long);
	size_t SherlockAndMinimax(vector<size_t> &, size_t, size_t);
	size_t ChiefHopper(vector<size_t> const &);
};