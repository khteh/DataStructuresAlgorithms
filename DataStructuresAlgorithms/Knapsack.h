#pragma once
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <ranges>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
using namespace tbb;
#endif
using namespace std;
namespace ranges = std::ranges;
class Knapsack
{
private:
	map<long, set<vector<size_t>>> coinChangeCache;
	map<long, set<vector<size_t>>> knapsackCache;
	map<long, size_t> dpMemoization;
	set<vector<size_t>> _BoundedKnapsack(long, vector<size_t> &);
	set<vector<size_t>> _BoundedKnapsackCombinationSum(size_t, size_t, size_t);
	set<vector<size_t>> KnapsackCombinations(long, vector<size_t> &);

public:
	void ClearCoinChangeCache();
	void ClearKnapsackCache();
	void ClearDPMemoization();
	set<vector<size_t>> CoinChange(long, vector<size_t> &);
	set<vector<size_t>> CoinsChangeDynamicProgramming(long, vector<size_t> &);
	size_t CoinsChangeUniqueWaysDynamicProgramming(long, vector<size_t> &);
	size_t CoinsChangeDuplicateWaysDynamicProgramming(size_t, vector<size_t> &);
	long CoinsChangeFewestCoinsDynamicProgramming(long, vector<size_t> &);
	size_t UnboundedKnapsack(long, vector<size_t> &);
	vector<vector<size_t>> BoundedKnapsack(long, vector<size_t> &);
	set<vector<size_t>> BoundedKnapsackCombinationSum(size_t, size_t, size_t max = 10);
	size_t StairsClimbingDynamicProgramming(long, vector<size_t> &);
	size_t StairsClimbingDynamicProgrammingBottomUp(long, vector<size_t> &);
};