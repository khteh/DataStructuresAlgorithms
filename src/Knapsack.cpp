#include "pch.h"
#include "Knapsack.h"
void Knapsack::ClearCoinsChangeCache()
{
	coinChangeCache.clear();
}
void Knapsack::ClearKnapsackCache()
{
	knapsackCache.clear();
}
void Knapsack::ClearDPMemoization()
{
	dpMemoization.clear();
}
/* https://www.hackerrank.com/challenges/coin-change/problem
 * Times out due to recursion!
 */
set<vector<size_t>> Knapsack::CoinsChange(long amount, vector<size_t> &coins)
{
	set<vector<size_t>> combinations;
	if (amount > 0)
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end(); coin++)
		{
			if (amount >= (long)*coin)
			{
				set<vector<size_t>> tmp;
				if (!coinChangeCache.count(amount - *coin))
				{
					tmp = CoinsChange(amount - *coin, coins);
					if (!tmp.empty())
						coinChangeCache[amount - *coin] = tmp;
				}
				else
					tmp = coinChangeCache[amount - *coin];
				if (!tmp.empty())
					for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						vector<size_t> change(*it);
						size_t sum = parallel_reduce(
										 blocked_range<size_t>(0, change.size()), 0,
										 [&](tbb::blocked_range<size_t> const &r, long running_total)
										 {
											 for (size_t i = r.begin(); i < r.end(); i++)
												 running_total += change[i];
											 return running_total;
										 },
										 std::plus<long>()) +
									 *coin;
						if (sum == amount)
						{
							change.push_back(*coin);
							ranges::sort(change);
							combinations.insert(change);
						}
					}
				else if (*coin == amount)
					combinations.insert(vector<size_t>{*coin});
			} // if (amount >= (long)coins[i]) {
		}
	return combinations;
}
set<vector<size_t>> Knapsack::CoinsChangeDynamicProgramming(long amount, vector<size_t> &coins)
{
	map<size_t, set<vector<size_t>>> dp;
	ranges::sort(coins);
	if (amount >= 0)
		for (size_t i = coins[0]; i <= (size_t)amount; i++) // Bottom-Up
			for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end(); coin++)
			{
				if (i == *coin)
					dp[i].insert(vector<size_t>{i});
				else if (i > *coin)
				{ // i:5 coins[j]:2 delta:3 dp[3] = {3}
					size_t delta = i - *coin;
					if (dp.count(delta))
					{
						for (set<vector<size_t>>::iterator it = dp[delta].begin(); it != dp[delta].end(); it++)
						{
							vector<size_t> tmp = *it;
							tmp.push_back(*coin);
							ranges::sort(tmp);
							dp[i].insert(tmp);
						}
					}
				}
			}
	return dp[amount];
}
/* https://www.hackerrank.com/challenges/coin-change/problem
 * https://leetcode.com/problems/coin-change-2/
 * 100%
 * coins: {2,3,5} amount: 10
 * coin = 2; i = starts from 2
 * ways: 1 0 1 0 1 0 1 0 1 0 1
 * i:    0 1 2 3 4 5 6 7 8 9 10
 *
 * coin = 3; i = starts from 3
 * ways: 1 0 1 1 1 1 2 1 2 2 2
 * i:    0 1 2 3 4 5 6 7 8 9 10
 *
 * coin = 5; i = starts from 5
 * ways: 1 0 1 1 1 2 2 2 3 3 4
 * i:    0 1 2 3 4 5 6 7 8 9 10 {5,5},{5,2,3},{2,2,3,3},{2,2,2,2,2}
 */
size_t Knapsack::CoinsChangeUniqueWaysDynamicProgramming(long amount, vector<size_t> &coins)
{
	if (amount <= 0 || coins.empty())
		return 0;
	vector<size_t> dp(amount + 1, 0); // Index: amount. Value: #ways or #posibilities
	dp[0] = 1;						  // $0 is one possibility
	for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end(); coin++)
		for (size_t i = *coin; i <= (size_t)amount; i++)
			dp[i] += dp[i - *coin];
	return dp[amount];
}
/* https://leetcode.com/problems/combination-sum-iv/
 * 100%
 * coins: {2,3,5} amount: 10
 * ways: 1 0 1 1 1 3 2 5 6 8 14
 * i:    0 1 2 3 4 5 6 7 8 9 10
 */
size_t Knapsack::CoinsChangeDuplicateWaysDynamicProgramming(long amount, vector<size_t> &coins)
{
	if (amount <= 0 || coins.empty())
		return 0;
	ranges::sort(coins);
	vector<size_t> dp(amount + 1, 0); // Index: amount. Value: #ways or #posibilities
	dp[0] = 1;						  // $0 is one possibility
	for (size_t i = coins[0]; i <= (size_t)amount; i++)
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end() && i >= *coin; coin++)
			dp[i] += dp[i - *coin];
	return dp[amount];
}
/* https://leetcode.com/problems/coin-change/
 * 100%
 * coins: {1,2,5}, amount: 10
 * i:    0 1 2     3     4     5        6       7      8       9       10
 * ways: 0 1 {2,1} {2,2} {3,2} {3,3,1} {2,3,2} {3,2,2} {3,3,3} {4,3,3} {4,4,2}
 */
long Knapsack::CoinsChangeFewestCoinsDynamicProgramming(long amount, vector<size_t> &coins)
{
	if (amount <= 0 || coins.empty())
		return 0;
	ranges::sort(coins);
	vector<size_t> dp(amount + 1, numeric_limits<size_t>::max()); // Index: amount. Value: #coins
	dp[0] = 0;													  // $0 = 0 coins
	for (size_t i = coins[0]; i <= amount; i++)
		for (vector<size_t>::iterator coin = coins.begin(); coin != coins.end() && i >= *coin; coin++)
			if (dp[i - *coin] != numeric_limits<size_t>::max())
				dp[i] = min(dp[i], dp[i - *coin] + 1);
	return dp[amount] == numeric_limits<size_t>::max() ? -1 : dp[amount];
}
/* https://www.hackerrank.com/challenges/unbounded-knapsack/problem
 * 100%
 */
set<vector<size_t>> Knapsack::KnapsackCombinations(long amount, vector<size_t> &numbers)
{
	set<vector<size_t>> combinations;
	if (amount > 0 && !numbers.empty())
	{
		if (numbers.size() == 1 && (long)numbers[0] <= amount)
			combinations.insert(vector<size_t>{amount - amount % numbers[0]}); // Multiples of numbers[0] closest to amount
		else if (ranges::find(numbers, 1) != numbers.end())
			combinations.insert(vector<size_t>{(size_t)amount});
		else
		{
			for (vector<size_t>::iterator number = numbers.begin(); number != numbers.end(); number++)
			{
				if (amount >= (long)*number)
				{
					set<vector<size_t>> tmp;
					if (!knapsackCache.count(amount - *number))
					{
						tmp = KnapsackCombinations(amount - *number, numbers);
						if (!tmp.empty())
							knapsackCache[amount - *number] = tmp;
					}
					else
						tmp = knapsackCache[amount - *number];
					if (!tmp.empty())
						for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
						{
							vector<size_t> change(*it);
							size_t sum = parallel_reduce(
											 blocked_range<size_t>(0, change.size()), 0,
											 [&](tbb::blocked_range<size_t> const &r, long running_total)
											 {
												 for (size_t i = r.begin(); i < r.end(); i++)
													 running_total += change[i];
												 return running_total;
											 },
											 std::plus<long>()) +
										 *number;
							if (sum <= (size_t)amount)
							{
								change.push_back(*number);
								ranges::sort(change);
								combinations.insert(change);
							}
						}
					else
						combinations.insert(vector<size_t>{*number});
				} // if (amount >= (long)numbers[i]) {
			}
		}
	}
	return combinations;
}
// Bounded places an upper bound on the number of copies of each kind of item included in the knapsack
// Unbounded places no upper bound on the number of copies of each kind of item included in the knapsack
size_t Knapsack::UnboundedKnapsack(long k, vector<size_t> &arr)
{
	knapsackCache.clear();
	set<vector<size_t>> combinations = KnapsackCombinations(k, arr);
	set<size_t> sums;
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
	{
		size_t sum = parallel_reduce(
			blocked_range<size_t>(0, it->size()), (size_t)0,
			[&](tbb::blocked_range<size_t> const &r, size_t running_total)
			{
				for (size_t i = r.begin(); i < r.end(); i++)
					running_total += (*it)[i];
				return running_total;
			},
			std::plus<size_t>());
		sums.insert(sum);
	}
	return sums.empty() ? 0 : *sums.rbegin();
}
set<vector<size_t>> Knapsack::_BoundedKnapsack(long amount, vector<size_t> &numbers)
{
	set<vector<size_t>> combinations;
	if (amount > 0 && !numbers.empty())
	{
		for (vector<size_t>::iterator number = numbers.begin(); number != numbers.end(); number++)
		{
			if (amount >= (long)*number)
			{
				set<vector<size_t>> tmp;
				if (!knapsackCache.count(amount - *number))
				{
					tmp = _BoundedKnapsack(amount - *number, numbers);
					knapsackCache[amount - *number] = tmp;
				}
				else
					tmp = knapsackCache[amount - *number];
				if (!tmp.empty())
				{
					for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
					{
						vector<size_t> tmp1(*it);
						size_t sum = parallel_reduce(
										 blocked_range<size_t>(0, tmp1.size()), 0,
										 [&](tbb::blocked_range<size_t> const &r, long running_total)
										 {
											 for (size_t i = r.begin(); i < r.end(); i++)
												 running_total += tmp1[i];
											 return running_total;
										 },
										 std::plus<long>()) +
									 *number;
						if (sum == amount)
						{
							tmp1.push_back(*number);
							ranges::sort(tmp1);
							size_t cnt = ranges::count(tmp1, *number);
							size_t cnt1 = ranges::count(numbers, *number);
							if (cnt <= cnt1) // The result must not contain more than the input as this is *Bounded* knapsack.
								combinations.insert(tmp1);
						}
					}
				}
				else
					combinations.insert(vector<size_t>{*number});
			}
		}
	}
	return combinations;
}
vector<vector<size_t>> Knapsack::BoundedKnapsack(long amount, vector<size_t> &numbers)
{
	vector<vector<size_t>> result;
	knapsackCache.clear();
	set<vector<size_t>> combinations = _BoundedKnapsack(amount, numbers);
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
	{
		size_t sum = parallel_reduce(
			blocked_range<size_t>(0, it->size()), (size_t)0,
			[&](tbb::blocked_range<size_t> const &r, size_t running_total)
			{
				for (size_t i = r.begin(); i < r.end(); i++)
					running_total += (*it)[i];
				return running_total;
			},
			std::plus<size_t>());
		if (sum == amount)
			result.push_back(*it);
	}
	return result;
}
/* https://leetcode.com/problems/combination-sum-iii/
 * 100%
 */
set<vector<size_t>> Knapsack::_BoundedKnapsackCombinationSum(size_t size, size_t sum, size_t max)
{
	set<vector<size_t>> combinations;
	for (size_t i = 1; i < max; i++)
	{
		if (sum >= i)
		{
			set<vector<size_t>> tmp;
			if (!knapsackCache.count(sum - i))
			{
				tmp = _BoundedKnapsackCombinationSum(size, sum - i, max);
				knapsackCache[sum - i] = tmp;
			}
			else
				tmp = knapsackCache[sum - i];
			if (!tmp.empty())
				for (set<vector<size_t>>::iterator it = tmp.begin(); it != tmp.end(); it++)
				{
					if (it->size() < size && ranges::find(*it, i) == it->end())
					{
						vector<size_t> change(*it);
						change.push_back(i);
						size_t total = parallel_reduce(
							blocked_range<size_t>(0, change.size()), (size_t)0,
							[&](tbb::blocked_range<size_t> const &r, size_t running_total)
							{
								for (size_t i = r.begin(); i < r.end(); i++)
									running_total += change[i];
								return running_total;
							},
							std::plus<size_t>());
						if (total == sum)
						{
							ranges::sort(change);
							combinations.insert(change);
						}
					}
				}
			else if (i == sum)
				combinations.insert(vector<size_t>{i});
		}
	} // for
	return combinations;
}
set<vector<size_t>> Knapsack::BoundedKnapsackCombinationSum(size_t size, size_t sum, size_t max)
{
	knapsackCache.clear();
	set<vector<size_t>> combinations = _BoundedKnapsackCombinationSum(size, sum, max);
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end();)
		if (it->size() != size)
			it = combinations.erase(it);
		else
			it++;
	return combinations;
}
/* The Recursive Staircase - Top Down Dynamic Programming
 *			   6(13)
 *       4(5)        5(8)
 *    2(2)     3(3)
 *  0(1)	1(1)
 *     -1(0) 0(1)
 */
size_t Knapsack::StairsClimbingDynamicProgramming(long destination, vector<size_t> &steps)
{
	if (!destination) // 0 step = stays. So it is one possibility.
		return 1;
	else if (destination < 0) // Impossible
		return 0;
	size_t combinations = 0;
	for (vector<size_t>::iterator it = steps.begin(); it != steps.end(); it++)
	{
		if (!dpMemoization.count(destination - *it))
			dpMemoization[destination - *it] = StairsClimbingDynamicProgramming(destination - *it, steps);
		combinations += dpMemoization[destination - *it];
	}
	return combinations;
}
/* The Recursive Staircase - Bottom Up Dynamic Programming
 * Steps: {1,2} Destination: 6
 *  0 1 2 3 4 5 6
 * {1,1,2,3,5,8,13} <= [i] = [i-1] + [i-2]
 * {1,0}, {1,1}, {2,1}, {2,3}, {5,3}, {5,8}, {13,8} => [N%2] = 13
 *
 * Steps: {1,2,3} Destination: 6
 *  0 1 2 3 4 5  6
 * {1,1,2,4,7,13,24} <= [i] = [i-1] + [i-2] + [i-3]
 * {1,0,0}, {1,1,0}, {1,1,2}, {4,1,2}, {4,7,2}, {4,7,13}, {24,7,13} => [n%3] = 24
 */
size_t Knapsack::StairsClimbingDynamicProgrammingBottomUp(long destination, vector<size_t> &steps)
{
	vector<size_t> combinations(steps.size(), 0);
	combinations[0] = 1;
	for (size_t i = 1; i <= (size_t)destination; i++)
	{
		combinations[i % combinations.size()] = parallel_reduce(
			blocked_range<size_t>(0, combinations.size()), (size_t)0,
			[&](tbb::blocked_range<size_t> const &r, size_t running_total)
			{
				for (size_t i = r.begin(); i < r.end(); i++)
					running_total += combinations[i];
				return running_total;
			},
			std::plus<size_t>());
	}
	return combinations[destination % combinations.size()];
}