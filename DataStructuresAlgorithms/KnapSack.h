#pragma once
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <ranges>
#ifdef _MSC_VER
#include <ppl.h>
#elif defined(__GNUC__) || defined(__GNUG__)
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
using namespace tbb;
#endif
using namespace std;
namespace ranges = std::ranges;
#ifdef _MSC_VER
using namespace concurrency;
#endif
class KnapSack
{
public:
	static void ClearCoinChangeCache();
	static void ClearKnapSackCache();
	static void ClearDPMemoization();
	static set<vector<size_t>> CoinChange(long, vector<size_t> &);
	static set<vector<size_t>> CoinsChangeDynamicProgramming(long, vector<size_t> &);
	static size_t CoinsChangeUniqueWaysDynamicProgramming(long, vector<size_t> &);
	static size_t CoinsChangeDuplicateWaysDynamicProgramming(size_t, vector<size_t> &);
	static long CoinsChangeFewestCoinsDynamicProgramming(long, vector<size_t> &);
	static set<vector<size_t>> Knapsack(long, vector<size_t> &);
	static size_t UnboundedKnapsack(long, vector<size_t> &);
	static set<vector<size_t>> _BoundedKnapsack(long, vector<size_t> &);
	static vector<vector<size_t>> BoundedKnapsack(long, vector<size_t> &);
	static set<vector<size_t>> _BoundedKnapsackCombinationSum(size_t, size_t);
	static set<vector<size_t>> BoundedKnapsackCombinationSum(size_t, size_t);
	static size_t StairsClimbingDynamicProgramming(long, vector<size_t> &);
	static size_t StairsClimbingDynamicProgrammingBottomUp(long, vector<size_t> &);
};