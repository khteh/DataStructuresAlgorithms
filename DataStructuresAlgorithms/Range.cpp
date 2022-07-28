#include "Range.h"
// https://en.wikipedia.org/wiki/Maximum_subarray_problem
// Kadane's algorithm
long Range::ConsecutiveLargestSum(vector<long>& data, vector<long>& result)
{
	vector<long> tmp;
	map<long, vector<long>> results;
	long max_ending_here = 0, max_so_far = 0; // max_so_far = max of all max_ending_here's found
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
	{
		max_ending_here += *it;
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			tmp.clear();
		}
		else
			tmp.push_back(*it);
		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			results.emplace(max_so_far, tmp);
		}
	}
	result = results[max_so_far];
	return max_so_far;
}
/* https://leetcode.com/problems/maximum-product-subarray/
 * 100%
 */
long Range::ConsecutiveLargestProduct(vector<long>& data)
{
	vector<long> tmp;
	map<long, vector<long>> results;
	long maxproduct = numeric_limits<long>::min(), max_ending_here = 1, min_ending_here = 1;
	bool zero = false;
	for (vector<long>::iterator it = data.begin(); it != data.end(); it++)
	{
		if (!*it)
		{
			zero = true;
			maxproduct = max(maxproduct, 0L);
		}
		else if (*it > 0)
		{
			min_ending_here = zero ? 1 : min(1L, min_ending_here * *it); // -ve * +ve
			max_ending_here = zero ? *it : max_ending_here * *it;
			zero = false;
			maxproduct = max(maxproduct, max_ending_here);
		}
		else
		{ // < 0
			long tmp = max_ending_here;
			if (!zero)
			{
				if (min_ending_here * *it > 0)
				{
					max_ending_here = min_ending_here * *it;
					maxproduct = max(maxproduct, max_ending_here);
				}
				else
					max_ending_here = 1;
				min_ending_here = tmp ? min(1L, tmp * *it) : *it; // +ve * -ve
			}
			else
			{
				min_ending_here = *it;
				max_ending_here = 1;
			}
			zero = false;
		}
	}
	return maxproduct;
}
/* https://leetcode.com/problems/minimum-size-subarray-sum/
*  100%
 0 1 2 3 4 5
[2,3,1,2,4,3] target: 7
 j     i		sum: 8 count: 4
   j   i		sum: 6
   j     i		sum: 10 count: 4
	 j   i		sum: 7 count: 3
	   j i		sum: 6
	   j   i	sum: 9 count: 3
		 j i	sum: 7 count: 2
[1 4 4]
 j i     sum: 5 count: 2
   i,j   sum: 4 count: 1
   j i   sum: 8 count: 2
	 i,j sum: 4 count: 1
*/
long Range::ConsecutiveSumMinCount(long target, vector<long>& data)
{
	size_t count = numeric_limits<size_t>::max();
	long sum = 0;
	for (size_t i = 0, j = 0; i < data.size(); i++)
	{
		sum += data[i];
		for (; sum >= target; j++)
		{
			sum -= data[j];
			count = min(count, i - j + 1);
		}
	}
	return count == numeric_limits<size_t>::max() ? -1 : count;
}
// https://app.codility.com/programmers/task/longest_nonnegative_sum_slice/
// https://app.codility.com/programmers/challenges/ferrum2018/
// Find the longest sequence when the graph crosses a previous point. The crossing point is when negative becomes positive and vice versa
// 100%
long Range::LongestNonNegativeSumSlice(vector<long>& data)
{
	// -1, -1, -1, -1, -1, -1, 1 (max_len = max(1, 6 - 4) = 2), 1 (max_len = max(2, 7 - 3) = 4)
	//  1,  1,  1,  1,  1,  1,-1 (max_len = max(6, 6 - 4) = 6),-1 (max_len = max(6, 7 - 3) = 6)
	map<long, size_t> sums;
	long sum = 0;
	size_t max_len = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		sum += data[i];
		if (sum >= 0)
			max_len = i + 1;
		else if (data[i] >= 0 && max_len == 0)
			max_len = 1;
		if (sums.find(sum) != sums.end())
			max_len = max(max_len, i - sums[sum]);
		else
			sums.emplace(sum, i);
	}
	return max_len;
}
size_t Range::LongestUpDownAlternatingSubSequence(const vector<long>& data, vector<long>& result)
{
	map<size_t, vector<long>> sequences;
	direction_t direction = Direction::NoChange, flag = Direction::NoChange;
	size_t count = 0, start = 0, index = 0;
	if (data.size() > 1)
	{
		for (vector<long>::const_iterator it = data.begin() + 1; it != data.end(); it++, index++)
		{
			flag = *it > *(it - 1) ? Direction::Up : *it < *(it - 1) ? Direction::Down
				: Direction::NoChange;
			if (flag != direction)
			{
				count++;
				direction = flag;
			}
			else
			{
				direction = Direction::NoChange;
				if (sequences.find(index - start) == sequences.end())
				{
					vector<long> tmp(data.begin() + start, it);
					sequences.emplace(index - start, tmp);
				}
				start = index;
			}
		}
	}
	if (!sequences.empty())
		result = sequences.rbegin()->second;
	return result.size();
}
/*        1 2 3 4 5 6 (sum: 8)
 * diff:  7 6 5 4 3 2
 * pairs: 1 2 3 4 . .  <= 2 pairs: {[3,5], [2,6]}
 *
 * 	     1 2 3 4 5 6 5 (sum: 8)
 * diff: 7 6 5 4 3 2 3
 * pairs:1 2 3 4 . .    <= 2 pairs: {[3,5], [2,6]}
 */
size_t Range::SumPairs(long sum, vector<long>& numbers)
{
	size_t count = 0;
	long diff;
	set<long> pairs, duplicates;
	for (vector<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		diff = sum - *it;
		if (pairs.find(diff) != pairs.end() && duplicates.find(diff) == duplicates.end())
		{
			count++;
			duplicates.emplace(diff);
		}
		else
			pairs.emplace(*it);
	}
	return count;
}
/* https://leetcode.com/problems/3sum/
 * 100%
 */
vector<vector<long>> Range::TripletsZeroSum(vector<long>& nums)
{
	set<vector<long>> result;
	if (nums.empty() || nums.size() < 3)
		return vector<vector<long>>();
	ranges::sort(nums);
	// -1,0,1,2,-1,-4 => -1, -1, 0, 1, 2, 4
	// -4,-1,-1,0,1,2
	for (size_t i = 0; i < nums.size(); i++)
	{
		for (size_t j = i + 1, k = nums.size() - 1; j < k;)
		{
			long sum = nums[i] + nums[j] + nums[k];
			if (!sum)
				result.insert(vector<long>{nums[i], nums[j++], nums[k--]});
			else if (sum < 0)
				j++;
			else
				k--;
		}
	}
	vector<vector<long>> result1(result.begin(), result.end());
	return result1;
}
/* https://leetcode.com/problems/4sum/
 * 100%
 */
vector<vector<long>> Range::QuadrupletsSum(long target, vector<long>& nums)
{
	set<vector<long>> result;
	if (nums.empty() || nums.size() < 4)
		return vector<vector<long>>();
	ranges::sort(nums);
	// -1,0,1,2,-1,-4 => -1, -1, 0, 1, 2, 4
	// -4,-1,-1,0,1,2
	for (size_t i = 0; i < nums.size(); i++)
	{
		for (size_t j = i + 1, k = nums.size() - 1; j < k; j++)
			for (size_t l = j + 1, m = k; l < m;)
			{
				long sum = nums[i] + nums[j] + nums[l] + nums[m];
				if (sum == target)
					result.insert(vector<long>{nums[i], nums[j], nums[l++], nums[m--]});
				else if (sum < target)
					l++;
				else
					m--;
			}
	}
	vector<vector<long>> result1(result.begin(), result.end());
	return result1;
}
/* https://www.hackerrank.com/challenges/pairs/problem
 * 100%
 *       1 2 3 4 5 6 (diff: 1)
 * tmp:  2 3 4 5 6 7
 * count:1 2 3 4 5  	=> 5 pairs
 */
size_t Range::NumberDiffPairs(long diff, vector<long>& numbers)
{
	size_t count = 0;
	set<long> pairs(numbers.begin(), numbers.end());
	long tmp;
	for (vector<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		tmp = *it + diff;
		if (pairs.find(tmp) != pairs.end())
			count++;
	}
	return count;
}
size_t Range::NumberDiffPairs(long diff, set<long>& numbers)
{
	size_t count = 0;
	long tmp;
	set<long>::iterator srcIt;
	for (set<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		tmp = diff + *it;
		srcIt = numbers.find(tmp);
		if (srcIt != numbers.end())
			count++;
	}
	return count;
}
/* https://www.hackerrank.com/challenges/stockmax/problem
 * 100%
 * { 1, 2, 100 } : (100 - 1 = 99) + (100 - 2 = 98) = 197
 */
size_t Range::StockMax(vector<long>& prices)
{
	size_t profit = 0;
	size_t maxIndex = 0;
	for (size_t i = 0; i < prices.size(); i++)
	{
		if (maxIndex <= i)
		{
			vector<long>::iterator peak = ranges::max_element(prices.begin() + i, prices.end());
			if (peak != prices.end())
				maxIndex = distance(prices.begin(), peak);
		}
		if (maxIndex > i)
		{
			// cout << "Profit: " << *peak - prices[i] << endl;
			profit += prices[maxIndex] - prices[i];
		}
	}
	return profit;
}
/* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
* 100%
* State machine of 3 states: (stay, bought, sold). Keep track of amount of profit at every state.
* stay -> bought -> sold -> stay
* stay -> stay
* bought -> bought
* sold -> stay
*
* stay[i] = max(stay[i - 1], sold[i - 1]); // Stay put, or rest from sold state
* bought[i] = max(bought[i - 1], stay[i - 1] - prices[i]); // Stay put, or buy again (Cannot buy immediately after sell)
* sold[i] = bought[i - 1] + prices[i]; // Sell
* 
* stay[0] = 0; // At the start, you don't have any stock if you just rest
* bought[0] = -prices[0]; // After buy, you should have -prices[0] profit. Be positive!
* sold[0] = 0;

		1  2  3	 0 2
stay:   0  0  1  2 2
bought: -1 -1 -1 1 1
sold:   0  1  2 -1 3
*/
long Range::StockMaxProfit(vector<long>& prices)
{
	if (prices.size() < 2)
		return 0;
	long profit = 0;
	vector<long> stay(prices.size(), 0), bought(prices.size(), 0), sold(prices.size(), 0);
	stay[0] = 0;
	bought[0] = -prices[0];
	sold[0] = 0;
	for (size_t i = 1; i < prices.size(); i++)
	{
		stay[i] = max(stay[i - 1], sold[i - 1]);
		bought[i] = max(bought[i - 1], stay[i - 1] - prices[i]);
		sold[i] = bought[i - 1] + prices[i];
	}
	return max(stay.back(), sold.back());
}
/*
	https://www.hackerrank.com/challenges/sherlock-and-cost/problem
	100%
4 7 9
i: 1
hl = 4 - 1 = 3 {4 1 9}
lh = 7 - 1 = 6 {1 7 9}
hh = 7 - 4 = 3 {4 7 9}
l = max(0, 0+3) = 3
h = max(0+3, 0+6) = 6

i: 2
hl = 7 - 1 = 6 {4 7 1}
lh = 9 - 1 = 8 {4 1 9}
hh = 9 - 7 = 2 {4 7 9}
l = max(3, 6+6) = 12
h = max(6+2, 3+8) = 11
*/
size_t Range::SherlockAndCost(vector<size_t>& data)
{
	/*
		lh: low to high from data[i - 1]=1 to data[i]
		hl: high to low from data[i - 1] to data[i]=1
		hh: hight to high from data[i - 1] to data[i]
	*/
	size_t l = 0, h = 0, lh, hh, hl, newLow, newHigh;
	for (size_t i = 1; i < data.size(); i++)
	{
		lh = abs((long)data[i] - 1);
		hl = abs((long)data[i - 1] - 1);
		hh = abs((long)data[i] - (long)data[i - 1]);

		newLow = max(l, h + hl);
		newHigh = max(h + hh, l + lh);

		l = newLow;
		h = newHigh;
	}
	return max(l, h);
}
/* https://leetcode.com/problems/wiggle-subsequence/
 * 100%
 * 1 17 5 10 13 15 10 5 16 8
 * 1 17 5 15 5 16 8
 *
 * 1 17 5 10 13 15 12 5 16 8
 * 1 17 5 15 5 16 8
 *
 * 1 17 5 10 13 11 12 5 16 8
 * 1 17 5 13 11 12 5 16 8
 */
vector<long> Range::WiggleMaxLength(vector<long>& nums)
{
	vector<long> result;
	bool direction = false; // false: down. true: up
	for (size_t i = 0; i < nums.size(); i++)
	{
		if (!i)
			result.push_back(nums[i]);
		else if (nums[i] < result.back())
		{
			if (result.size() == 1 || direction)
				result.push_back(nums[i]);
			else if (!direction && nums[i] < result.back())
				result.back() = nums[i];
			direction = false;
		}
		else if (nums[i] > result.back())
		{
			if (result.size() == 1 || !direction)
				result.push_back(nums[i]);
			else if (direction && nums[i] > result.back())
				result.back() = nums[i];
			direction = true;
		}
	}
	return result;
}
/* https://leetcode.com/problems/contains-duplicate-iii/
* Given an integer array nums and two integers k and t, return true if there are two distinct indices i and j in the array such that
* abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.
* 100%

Test cases:
[2147483647,-1,2147483647] => false
k: 1
t: 2147483647

[2147483647,-1,2147483647] => false
k: 1
t: -2147483648L (0xFFFF_FFFF_8000_0000)

[10,-1,10] => false
k: 1
t: 10

[-2147483648,2147483647] => [0x80000_000, 0x7FFF_FFFF] => false
k: 1
t: 1
*/
bool Range::ContainsNearbyAlmostDuplicate(vector<long>& nums, long k, long t)
{
	multiset<long> buckets;
	if (k > 0 && t >= 0)
	{ // Absolute diff. t >= 0. k = 0 means diff is 0.
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (i > k)
				buckets.erase(nums[i - k - 1]);
			multiset<long>::iterator it = buckets.lower_bound(nums[i] - t); // >= nums[i] - t
			if (it != buckets.end() && *it <= (nums[i] + t))
				return true;
			buckets.emplace(nums[i]);
		}
	}
	return false;
}
/*
 * https://www.hackerrank.com/challenges/array-splitting/problem
 * 100%
 * Do NOT change the data type from int to long!
 * Only tested working with int type.
 */
size_t Range::VectorEqualSplit(vector<int>& data)
{
	set<int> unique(data.begin(), data.end());
	size_t result = 0;
	if (data.size() < 2)
		return result;
#ifdef _MSC_VER
	int right = parallel_reduce(data.begin(), data.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
	int right = parallel_reduce(
		blocked_range<int>(0, data.size()), 0,
		[&](tbb::blocked_range<int> r, int running_total)
		{
			for (int j = r.begin(); j < r.end(); j++)
				running_total += data[j];
			return running_total;
		},
		std::plus<int>());
#endif
	int left = 0;
	size_t i = 0;
	if (!right)
		return data.size() - 1;
	else if (unique.size() == 1 && data[0] && (right % 2 || data.size() % 2))
		return 0;
	else
		for (; i < data.size() && left != right; left += data[i], right -= data[i++])
			;
	if (left == right && i < data.size())
	{
		result++;
		vector<int> leftSplit = vector<int>(data.begin(), data.begin() + i);
		vector<int> rightSplit = vector<int>(data.begin() + i, data.end());
		result += max(VectorEqualSplit(leftSplit), VectorEqualSplit(rightSplit));
	}
	return result;
}
/* https://leetcode.com/problems/maximum-product-of-word-lengths/
 * 100%
 */
size_t Range::MaxProductOfNonOverlappingWordLengths(vector<string>& words)
{
	size_t result = 0;
	map<size_t, size_t> patterns;
	for (size_t i = 0; i < words.size(); i++)
	{
		int pattern = 0;
		for (size_t c = 0; c < words[i].size(); c++)
			pattern |= 1 << (words[i][c] - 'a');
		patterns[pattern] = max(patterns[pattern], words[i].size());
		for (map<size_t, size_t>::iterator it = patterns.begin(); it != patterns.end(); it++)
			if (!(it->first & pattern))
				result = max(result, it->second * words[i].size());
	}
	return result;
}
/* https://www.hackerrank.com/challenges/almost-sorted/problem
   100%
4 2
2 4 : swap
2 -2

3 1 2
1 2 3 : No
2 -1 -1

1 3 2 4
1 2 3 4 : Swap 1 2
0 1 -1 0

1 4 2 3
1 2 3 4 : No
0 2 -1 -1 : 0

1 4 3 5 2
1 2 3 4 5 : No
0 2 0 1 -3: 0

1 4 3 2
1 2 3 4 : Swap 1 3
0 2 0 -2

1 5 4 3 2
1 2 3 4 5: Reverse 1-4
0 3 1 -1 -3

1 5 3 4 2
1 2 3 4 5: Swap 1 4
0 3 0 0 -3

4 2
2 4 : Swap 0 1
2 -2

1 5 4 3 2 6
1 2 3 4 5 6	: Reverse 1 4
0 3 1 -1 -3 0

43 65 1  98 99 101
1  43 65 98 99 101 : No
42 22 -64 0 0  0

2 3 1 4 5 6
1 2 3 4 5 6 : No
1 1 -2 0 0 0
*/
string Range::AlmostSorted(vector<long>& arr)
{
	ostringstream oss;
	vector<long> sorted(arr);
	ranges::sort(sorted);
	vector<long> diff;
	long positive = -1, sum = 0;
	for (size_t i = 0; i < arr.size(); i++)
	{
		long delta = arr[i] - sorted[i];
		if (delta > 0 && positive < 0)
			positive = i;
		if (positive >= 0)
		{ // Start tracking from the first positive delta to minimize space complexity
			size_t index = i - positive;
			diff.push_back(delta);
			sum += diff[index];
			if (diff[index] < 0 && sum == 0)
			{
				size_t positives = ranges::count_if(diff, [](long i)
					{ return i > 0; });
				size_t negatives = ranges::count_if(diff, [](long i)
					{ return i < 0; });
				if (diff[index] + diff[0] != 0)
					return "no";
				else if (positives == 1 && negatives == 1)
				{
					if (!oss.str().empty())
						return "no";
					oss << "swap " << positive + 1 << " " << i + 1;
				}
				else if (i > (size_t)(positive + 1))
				{
					if (!oss.str().empty())
						return "no";
					oss << "reverse " << positive + 1 << " " << i + 1;
				}
			}
		}
	}
	return oss.str().empty() ? "no" : oss.str();
}
/* https://www.hackerrank.com/challenges/new-year-chaos/problem
 * 100%
 * 0 1 2 3 4 5 6 7 <- i
 * 1 2 5 3 7 8 6 4
 * i: 7 -> bribes: [5, 7, 8, 6]
 * i: 6 -> bribes: [7, 8]
 * i: 5 -> bribes: []
 * i: 4 -> bribes: []
 * i: 3 -> bribes: [5]
 * i: 2 -> bribes: []
 * i: 1 -> bribes: []
 * i: 0 -> bribes: []
 *
 * 0 1 2 3 4 <- i, maxBribes = 2
 * 2 1 5 3 4
 * i: 4 -> [5]
 * i: 3 -> [5]
 * i: 2 ->
 * i: 1 -> [2]
 * i: 0 ->
 *
 * 0 1 2 3 4 <- i, maxBribes = 3
 * 2 5 1 3 4
 * i: 4 -> [5]
 * i: 3 -> [5]
 * i: 2 -> [2, 5]
 * i: 1 ->
 * i: 0 ->
 *
 * 0 1 2 3 4 <- i, maxBribes = 4
 * 5 2 1 3 4
 * i: 4 -> [5]
 * i: 3 -> [5]
 * i: 2 -> [5, 2]
 * i: 1 -> [5]
 * i: 0
 */
long Range::MinimumBribes(size_t maxBribes, vector<long>& data)
{
	long bribes = 0;
	for (long i = data.size() - 1; i >= 0; i--)
	{
		/*
		 * 0 1 2 3 4 5 6 7 <- i
		 * 1 2 5 3 7 8 6 4
		 * i: 7 -> bribes: [5, 7, 8, 6]
		 * i: 6 -> bribes: [7, 8]
		 * i: 5 -> bribes: []
		 * i: 4 -> bribes: []
		 * i: 3 -> bribes: [5]
		 * i: 2 -> bribes: []
		 * i: 1 -> bribes: []
		 * i: 0 -> bribes: []
		 */
		if (data[i] - (i + 1) > (long)maxBribes)
			return -1;
		for (long j = max(0L, data[i] - (long)maxBribes); j < i; j++)
			if (data[j] > data[i])
				bribes++;
	}
	return bribes;
}
/*
 * https://www.hackerrank.com/challenges/picking-numbers/problem
 * 100%
 */
size_t Range::PickNumbersFromRange(vector<long>& a)
{
	size_t max = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		long value = a[i];
		size_t cnt = ranges::count_if(a, [&value](long j)
			{ return j == value; });
		size_t oneless = 0;
		if (value > 0)
			oneless = ranges::count_if(a, [&value](long j)
				{ return j == (value - 1); });
		size_t onemore = ranges::count_if(a, [&value](long j)
			{ return j == (value + 1); });
		cnt = cnt + oneless > cnt + onemore ? cnt + oneless : cnt + onemore;
		if (cnt > max)
			max = cnt;
	}
	return max;
}
/*
 * https://www.hackerrank.com/challenges/manasa-and-stones/problem
 * 100%
 * 3 1 1
 * 000 : 0 1 2
 * 001 : 0 1 2
 * 010 : 0 1 2
 * 011 : 0 1 2

 * 3 1 2
 * 000 : 0 1 2
 * 001 : 0 1 3
 * 010 : 0 2 3
 * 011 : 0 2 4
 *
 * 4 10 10
 * 0000 : 0 10 20 30
 * 0001 : 0 10 20 30
 * ...
 *
 * 4 10 100
 * 0000 : 0 10 20 30
 * 0001 : 0 10 20 120
 * 0010 : 0 10 110 120
 * 0011 : 0 10 110 210
 * 0100 : 0 100 110 120
 * 0101 : 0 100 110 210
 * 0110 : 0 100 200 210
 * 0111 : 0 100 200 300
 */
vector<long> Range::LastNumbers(size_t n, long a, long b)
{
	vector<long> result;
	long diff = abs(a - b), num = min(a, b) * (n - 1), maximum = max(a, b) * (n - 1);
	if (a == b)
		return vector<long>{num};
	result.resize(((maximum - num) / diff) + 1);
	ranges::generate(result, [n = num, diff]() mutable
		{ long result = n; n += diff; return result; });
	return result;
}