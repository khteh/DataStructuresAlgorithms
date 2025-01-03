#include "Range.h"
/* https://en.wikipedia.org/wiki/Maximum_subarray_problem
 * Kadane's algorithm
 */
long Range::ConsecutiveMaximumSum(vector<long> const &data, vector<long> &result)
{
	vector<long> kadane;
	map<long, vector<long>> results;
	long max_ending_here = 0, max_so_far = 0; // max_so_far = max of all max_ending_here's found
	for (vector<long>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		max_ending_here += *it;
		if (max_ending_here < 0)
		{
			max_ending_here = 0;
			kadane.clear();
		}
		else
			kadane.push_back(*it);
		if (max_so_far < max_ending_here)
		{
			max_so_far = max_ending_here;
			results.emplace(max_so_far, kadane);
		}
	}
	result = results[max_so_far];
	return max_so_far;
}
/*
 * https://www.hackerrank.com/challenges/maximum-subarray-sum/problem
 * https://www.youtube.com/watch?v=u_ft5jCDZXk&t=577s
 * (1) Use (Kadane's algorithm) % m
 * (2) Fact: a % m = (a + m) % m
 *                 = a % m + m % m
 *
 * a[i]: 1 2 -5 4 -8   6 7  3  -7 11 12 (m: 15)
 * sums: 1 3 13 2  9   0 7  10  3 14 11 (S[j] % m)
 *  max: 1 3 13 14 ...
 * S(i...j] = (S[j] - S[i]) % m
 *
 * To make the value positive, + m
 * S(i...j] = (S[j] - S[i] + m) % m
 *
 * So, the problem simplifies to maximizing S[i...j]
 *
 * Analysis:
 * S[j] = 8, j = 7
 * 8 - 1 = 7
 * 8 - 3 = 5
 * 8 - 6 = 2
 * 8 - 10 = -2 (+ 15 ) = 13 <- max
 * 8 - 2 = 6
 * 8 - 0 = 8
 * 8 - 8 = 0
 * 8 - 0 = 8
 * Subtracting S[i] from S[j] with S[i] <= S[j] will ALWAYS yield <= S[j]
 * To maximize, subtract the smallest number of S[i] greater than S[j] from S[j]
 *
 * 100%
 *
 * Using vector::insert gives a sorted list
 * a[i] sum maxSum	sums
 * 1	1	1		[1]
 * 2	3	3		[1 3]
 * -5	13	13		[1 3 13]
 * 4	2	14		[1 (2) 3 13]
 * -8	9   14		[1 1 3 (9) 13]
 * 6	0	14		[(0) 1 1 3 9 13]
 * 7	7	14		[0 1 1 3 (7) 9 13]	max(14, 13)
 * 3	10	14		[0 1 1 3 7 9 (10) 13]
 * -7	3	14		[0 1 1 3 (3) 7 9 10 13] max(14, 11)
 * 11	14	14		[0 1 1 3 3 7 9 10 13 14]
 * 12	11	14		[0 1 1 3 3 7 9 10 (11) 13 14]
 *
 * Using vector::push_back results in unsorted list
 * a[i] sum maxSum	sums
 * 1	1	1		[1]
 * 2	3	3		[1 3]
 * -5	13	13		[1 3 13]
 * 4	2	14		[1 3 13 2]
 * -8	9   14		[1 3 13 2 9]
 * 6	0	14		[1 3 13 2 9 0]
 * 7	7	14		[1 3 13 2 9 0 7] <= max(14, 9) Diff here compared to vector::insert
 * 3	10	14		[1 3 13 2 9 0 7 10]
 * -7	3	14		[1 3 13 2 9 0 7 10 3] <= max(14, 5) Diff here compared to vector::insert
 * 11	14	14		[1 3 13 2 9 0 7 10 3 14]
 * 12	11	14		[1 3 13 2 9 0 7 10 3 14 11]
 */
size_t Range::ConsecutiveMaximumSumModulo(vector<long> const &data, size_t modulo)
{
	size_t maxSum = numeric_limits<size_t>::min(), sum = numeric_limits<size_t>::min();
	vector<size_t> sums; // Using set<size_t> will cause time out!
	for (vector<long>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		sum += *it;
		sum %= modulo;
		maxSum = max(maxSum, sum);
		vector<size_t>::const_iterator it1 = upper_bound(sums.begin(), sums.end(), sum);
		if (it1 != sums.end())
		{
			size_t max1 = (sum - *it1 + modulo) % modulo;
			maxSum = max(maxSum, max1);
		}
		sums.insert(it1, sum); // Insert item before it1
	}
	return maxSum;
}
/* https://leetcode.com/problems/maximum-product-subarray/
 * 100%
 */
long Range::ConsecutiveLargestProduct(vector<long> const &data)
{
	vector<long> tmp;
	map<long, vector<long>> results;
	long maxproduct = numeric_limits<long>::min(), max_ending_here = 1, min_ending_here = 1;
	bool zero = false;
	for (vector<long>::const_iterator it = data.begin(); it != data.end(); it++)
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
size_t Range::MinSumSubSequence(size_t target, vector<size_t> const &data)
{
	size_t count = numeric_limits<size_t>::max();
	size_t sum = 0;
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
/*
 * https://www.hackerrank.com/challenges/minimum-loss/problem
 * 100%
 */
size_t Range::MinimumLoss(vector<size_t> const &data)
{
	map<size_t, size_t, greater<size_t>> prices;
	for (size_t i = 0; i < data.size(); i++)
		prices.emplace(data[i], i);
	size_t minPrice = numeric_limits<size_t>::max();
	for (map<size_t, size_t, greater<size_t>>::iterator it = prices.begin(); it != prices.end(); it++)
	{
		size_t index = it->second;
		map<size_t, size_t, greater<size_t>>::iterator it1 = find_if(next(it), prices.end(), [index](const auto &it2)
																	 { return it2.second > index; });
		if (it1 != prices.end() && it1->first < it->first)
			minPrice = min((it->first - it1->first), minPrice);
	}
	return minPrice;
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
size_t Range::MinimumBribes(size_t maxBribes, vector<long> const &data)
{
	size_t bribes = 0;
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
		for (long j = max<long>(0L, data[i] - maxBribes); j < i; j++)
			if (data[j] > data[i])
				bribes++;
	}
	return bribes;
}
/* https://www.hackerrank.com/challenges/pylons/problem
100%
i: 0 1 2 3 4 5 6
   0 1 1 1 0 0 0 (k:3)
   i:0 [2, 0] j:2
			 i:5 [6, 3] j: 3
			   i:6 [6, 4] result: -1

i: 0 1 2 3 4 5
   0 1 1 1 1 0 (k:2)
   i:0 [1,0] j:1
		 i:3 [4,2] j:4 result: 2

i: 0 1 2 3
   1 0 1 0 (k:2)
   i:0 [1,0] j:0
	   i:2 [3, 1] j:2 result: 2

i: 0 1 2 3
   0 1 1 0 (k:2)
   i:0 [1,0] j:1
		 i:3 [3, 2] j: 2 result: 2

i: 0 1 2 3 4
   0 1 0 1 0 (k:3)
   i:0 [2,0] j:1
		   i:4 [4, 2] j: 3 result: 2
 */
long Range::MinEnergyInstallations(vector<size_t> &data, long k)
{
	vector<size_t> installations;
	for (size_t i = 0; i < data.size(); i = installations.back() + k)
	{
		bool found = false;
		for (long j = min(data.size() - 1, i + k - 1), lowerbound = installations.empty() ? 0 : installations.back() + 1; !found && j >= lowerbound; j--)
			if (data[j])
			{
				found = true;
				installations.push_back(j);
			}
		if (!found)
			return -1;
	}
	return installations.size();
}
/* https://www.hackerrank.com/challenges/candies/problem
Note that when two children have equal rating, they are allowed to have different number of candies.
100%
1 1 1 1 1 -> 5

4 5 6 5 4 -> 1 2 3 2 1 = 9

4 5 6 4 5 -> 1 2 3 2 3 -> 1 2 3 1 2 = 9

6 5 3 4 1 -> 3 2 1 2 1 = 9

6 5 4 2 3 -> 4 3 2 1 2 = 12

4 5 6 6 6 5 4 -> 1 2 3 2 1 0 -1 -> 1 2 3 2 1 2 1 = 12

4 5 6 6 6 4 5 -> 1 2 3 1 2 1 2 = 12

6 5 3 3 3 4 1 -> 3 2 1 1 1 2 1 = 11

6 5 4 4 4 2 3 -> 3 2 1 1 1 2 3 = 13

4 6 4 5 6 2
1 2 1 2 3 1

2 4 2 6 1 7 8 9 2 1
1 2 1 2 1 2 3 4 3 2 -> 1 2 1 2 1 2 3 4 3 1 -> 1 2 1 2 1 2 3 4 2 1

2 4 3 5 2 6 4 5
1 2 1 2 1 2 1 2

6 5 4 4 4 2 3 -> 3 2 1 2 1 2 3 = 14
 */
size_t Range::MinimumCandies(vector<size_t> const &data)
{
	vector<size_t> result(data.size(), 1);
	for (size_t i = 0; i < data.size() - 1; i++)
		if (data[i] < data[i + 1])
			result[i + 1] = result[i] + 1;
	for (size_t i = data.size() - 1; i >= 1; i--)
		if (data[i - 1] > data[i] && result[i - 1] <= result[i])
			result[i - 1] = result[i] + 1;
	size_t sum = parallel_reduce(
		blocked_range<size_t>(0, result.size()), (size_t)0,
		[&](tbb::blocked_range<size_t> const &r, size_t running_total)
		{
			for (size_t i = r.begin(); i < r.end(); i++)
				running_total += result[i];
			return running_total;
		},
		std::plus<size_t>());
	return sum;
}
/*
 * https://app.codility.com/programmers/task/longest_nonnegative_sum_slice/
 * https://app.codility.com/programmers/challenges/ferrum2018/
 * Find the longest sequence when the graph crosses a previous point. The crossing point is when negative becomes positive and vice versa
 * 100%
 */
long Range::LongestNonNegativeSumSlice(vector<long> const &data)
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
		if (sums.count(sum))
			max_len = max(max_len, i - sums[sum]);
		else
			sums.emplace(sum, i);
	}
	return max_len;
}
size_t Range::LongestUpDownAlternatingSubSequence(vector<long> const &data, vector<long> &result)
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
				if (!sequences.count(index - start))
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
size_t Range::SumPairs(size_t sum, vector<size_t> const &data)
{
	size_t count = 0;
	size_t diff;
	set<size_t> pairs, duplicates;
	for (vector<size_t>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		diff = sum - *it;
		if (pairs.count(diff) && !duplicates.count(diff))
		{
			count++;
			duplicates.emplace(diff);
		}
		else
			pairs.emplace(*it);
	}
	return count;
}
/*
https://www.hackerrank.com/challenges/icecream-parlor/problem
100%
*/
void Range::SumPairs(size_t sum, vector<size_t> const &data, vector<size_t> &result)
{
	size_t diff;
	map<size_t, size_t> pairs;
	set<size_t> duplicates;
	for (size_t i = 0; i < data.size(); i++)
	{
		diff = sum - data[i];
		if (pairs.count(diff) && !duplicates.count(diff))
		{
			result.push_back(pairs[diff]);
			result.push_back(i);
			duplicates.emplace(diff);
		}
		else
			pairs.emplace(data[i], i);
	}
}
/*
 * https://www.geeksforgeeks.org/maximum-value-pair-array/
 * Start from MSB, add the bit to the result if there are 2 elements having the same prefix value when ANDed
 */
unsigned long long Range::MaxAndPair(vector<unsigned long long> const &data)
{
	unsigned long long result = 0;
	for (unsigned long long msb = 1 << BitCount(*ranges::max_element(data)) - 1, pattern = result | msb; msb > 0; msb >>= 1, pattern = result | msb)
	{
		size_t count = 0;
		for (vector<unsigned long long>::const_iterator it = data.begin(); count < 2 && it != data.end(); it++)
			if ((*it & pattern) == pattern)
				count++;
		if (count >= 2)
			result |= msb;
	}
	return result;
}
/*
https://www.geeksforgeeks.org/maximum-xor-of-two-numbers-in-an-array/
n: [1, 2, 3, 4, 5, 6, 7]
mask: 0x100
prefixes: 0, 0x100
result: 0
maxx: 0x100
maxx ^ prefix: 0x100 ^ 0 = 0x100 => result = 0x100

mask: 0x110
prefixes: 0, 0x10, 0x100, 0x110
result = 0x100
maxx: 0x110
maxx ^ prefix: 0x110 ^ 0 = 0x110 => result = 0x110

mask: 0x111
prefixes: [1,2,3,4,5,6,7]
result = 0x110
maxx: 0x111
maxx ^ prefix: 0x111 ^ 1 = 0x110 => result = 0x111

n: [1, 2, 3, 4]
mask: 0x100
prefixes: 0, 0x100
maxx: 0x100
maxx ^ prefix: 0x100 ^ 0 = 0x100 => result = 0x100

mask: 0x110
prefixes: 0, 0x10, 0x100
result: 0x100
maxx: 0x110
maxx ^ prefix: 0x110 ^ 0 = 0x110
			   0x110 ^ 0x10 = 0x100 => result = 0x110

mask: 0x111
prefixes: [1,2,3,4] [001, 010, 011, 100]
result = 0x110
maxx: 0x111
maxx ^ prefix: 0x111 ^ 1 = 0x110
			   0x111 ^ 0x10 = 0x101
			   0x111 ^ 0x11 = 0x100 => result = 0x111
*/
unsigned long long Range::MaxXorPair(vector<unsigned long long> const &data)
{
	unsigned long long result = 0;
	set<unsigned long long> prefixes;
	for (unsigned long long msb = 1 << BitCount(*ranges::max_element(data)) - 1, mask = msb; msb > 0; msb >>= 1, mask |= msb)
	{
		prefixes.clear();
		for (vector<unsigned long long>::const_iterator it = data.begin(); it != data.end(); it++)
			prefixes.emplace(*it & mask);
		unsigned long long maxx = result | msb;
		/*
		 Find a pair in the prefixes where a^b = maxx
		1 ^ 2 = 3 => 1 = 3 ^ 2
					 2 = 3 ^ 1
		a ^ b = maxx => a = maxx ^ b (True if a is in the prefixes set)
						b = maxx ^ a (True if b is in the prefixes set)
		*/
		for (set<unsigned long long>::const_iterator it = prefixes.begin(); it != prefixes.end(); it++)
			if (prefixes.count(*it ^ maxx))
			{
				result = maxx;
				break;
			}
	}
	return result;
}

/* 0 1 2 3 4 5 6 7 8 9
 *         ^ (10 / 2 - 1)
 * (0,9), (0,8)	2
 * (1,9), (1,8), (1,7), 3
 * (2,9), (2,8), (2,7), (2,6), 4
 * (3,9), (3,8), (3,7), (3,6), (3,5) 5
 * (4,9), (4,8), (4,7), (4,6), (4,5), (4,4) 6
 * (5,9), (5,8), (5,7), (5,6), (5,5) 5
 * (6,9), (6,8), (6,7), (6,6) 4
 * (7,9), (7,8), (7,7) 3
 * (8,9), (8,8) 2
 * (9,9) 1
 * Count = 35

 * 0 1 2 3 4 5 6 7 8 9 10
 *         ^ (11 / 2 - 1)
 * (0,10), (0,9), (0,8)	3
 * (1,10), (1,9), (1,8), (1,7), 4
 * (2,10), (2,9), (2,8), (2,7), (2,6), 5
 * (3,10), (3,9), (3,8), (3,7), (3,6), (3,5) 6
 * (4,10), (4,9), (4,8), (4,7), (4,6), (4,5), (4,4) 7
 * (5,10), (5,9), (5,8), (5,7), (5,6), (5,5) 6
 * (6,10), (6,9), (6,8), (6,7), (6,6) 5
 * (7,10), (7,9), (7,8), (7,7) 4
 * (8,10), (8,9), (8,8) 3
 * (9,10), (9,9) 2
 * Count = 45
 */
size_t Range::GreaterThanSumPairs(size_t sum, vector<size_t> const &data)
{
	size_t count = 0, count1;
	for (size_t i = 0; i <= data.size() / 2 - 1; i++)
	{
		count1 = 0;
		for (long j = data.size() - 1; j >= 0 && data[i] + data[j] >= sum && i <= j; j--)
			count1++;
		if (!i && count1)
			count += count1 - 1;
		if (i != data.size() / 2 - 1)
			count1 *= 2;
		count += count1;
	}
	return count;
}
/* https://leetcode.com/problems/3sum/
 * 100%
 */
vector<vector<long>> Range::TripletsZeroSum(vector<long> &nums)
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
	return vector<vector<long>>(result.begin(), result.end());
}
/* https://leetcode.com/problems/4sum/
 * 100%
 */
vector<vector<long>> Range::QuadrupletsSum(long target, vector<long> &nums)
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
	return vector<vector<long>>(result.begin(), result.end());
}
/* https://www.hackerrank.com/challenges/pairs/problem
 * 100%
 *       1 2 3 4 5 6 (diff: 1)
 * tmp:  2 3 4 5 6 7
 * count:1 2 3 4 5  	=> 5 pairs
 */
size_t Range::NumberDiffPairs(long diff, vector<long> const &numbers)
{
	size_t count = 0;
	set<long> pairs(numbers.begin(), numbers.end());
	long tmp;
	for (vector<long>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		tmp = *it + diff;
		if (pairs.count(tmp))
			count++;
	}
	return count;
}
size_t Range::NumberDiffPairs(long diff, set<long> const &numbers)
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
size_t Range::StockMax(vector<long> const &prices)
{
	size_t profit = 0;
	size_t maxIndex = 0;
	for (size_t i = 0; i < prices.size(); i++)
	{
		if (maxIndex <= i)
		{
			vector<long>::const_iterator peak = ranges::max_element(prices.begin() + i, prices.end());
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
/* A zero - indexed array A consisting of N integers is given.It contains daily prices of a stock share for a period of N consecutive days.
 * If a single share was bought on day P and sold on day Q, where 0 ≤ P ≤ Q < N, then the profit of such transaction is equal to A[Q] − A[P], provided that A[Q] ≥ A[P].
 * Otherwise, the transaction brings loss of A[P] − A[Q].
 * For example, consider the following array A consisting of six elements such that:
 * A[0] = 23171
 * A[1] = 21011
 * A[2] = 21123
 * A[3] = 21366
 * A[4] = 21013
 * A[5] = 21367
 * If a share was bought on day 0 and sold on day 2, a loss of 2048 would occur because A[2] − A[0] = 21123 − 23171 = −2048.
 * If a share was bought on day 4 and sold on day 5, a profit of 354 would occur because A[5] − A[4] = 21367 − 21013 = 354.
 * Maximum possible profit was 356. It would occur if a share was bought on day 1 and sold on day 5.
 * 100%
 */
long Range::MaxProfit(vector<long> const &data)
{
	long min = numeric_limits<long>::max();
	long delta = 0;
	for (vector<long>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		if (*it < min)
			min = *it;
		if ((*it - min) > delta)
			delta = (*it - min);
	}
	return delta;
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
long Range::StockMaxProfit(vector<long> const &prices)
{
	if (prices.size() < 2)
		return 0;
	long profit = 0;
	vector<long> stay, bought, sold;
	stay.push_back(0);
	bought.push_back(-prices[0]);
	sold.push_back(0);
	for (size_t i = 1; i < prices.size(); i++)
	{
		stay.push_back(max(stay[i - 1], sold[i - 1]));
		bought.push_back(max(bought[i - 1], stay[i - 1] - prices[i]));
		sold.push_back(bought[i - 1] + prices[i]);
	}
	return max(stay.back(), sold.back());
}
/*
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 * 100%
 * [7,1,5,3,6,4]
 * 5 - 1 = 4
 * 6 - 3 = 3 : profit: 7
 *
 * [1,2,3,4,5]
 * profit: 4
 */
long Range::StockMaxProfit1(vector<long> const &prices)
{
	long profit = 0, current = prices[0], bought = prices[0];
	for (size_t i = 1; i < prices.size(); i++)
	{
		for (; i < prices.size() && prices[i] >= prices[i - 1]; i++)
			current = prices[i];
		if (current > bought)
			profit += (current - bought);
		if (i < prices.size())
		{
			bought = prices[i];
			current = bought;
		}
	}
	return profit;
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
size_t Range::SherlockAndCost(vector<size_t> const &data)
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
vector<size_t> Range::WiggleMaxLength(vector<size_t> const &nums)
{
	vector<size_t> result;
	bool direction = false; // false: down. true: up
	if (nums.empty())
		return result;
	result.push_back(*nums.begin());
	for (vector<size_t>::const_iterator it = nums.begin(); it != nums.end(); it++)
	{
		if (*it < result.back())
		{
			if (result.size() == 1 || direction)
				result.push_back(*it);
			else if (!direction && *it < result.back())
				result.back() = *it;
			direction = false;
		}
		else if (*it > result.back())
		{
			if (result.size() == 1 || !direction)
				result.push_back(*it);
			else if (direction && *it > result.back())
				result.back() = *it;
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
bool Range::ContainsNearbyAlmostDuplicate(vector<long> const &nums, long k, long t)
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
size_t Range::VectorEqualSplit(vector<int> const &data)
{
	set<int> unique(data.begin(), data.end());
	size_t result = 0;
	if (data.size() < 2)
		return result;
	int right = parallel_reduce(
		blocked_range<size_t>(0, data.size()), 0,
		[&](tbb::blocked_range<size_t> const &r, int running_total)
		{
			for (size_t j = r.begin(); j < r.end(); j++)
				running_total += data[j];
			return running_total;
		},
		std::plus<int>());
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
size_t Range::MaxProductOfNonOverlappingWordLengths(vector<string> const &words)
{
	size_t result = 0;
	map<size_t, size_t> patterns;
	for (vector<string>::const_iterator it = words.begin(); it != words.end(); it++)
	{
		int pattern = 0;
		for (size_t c = 0; c < it->size(); c++)
			pattern |= 1 << ((*it)[c] - 'a');
		patterns[pattern] = max(patterns[pattern], it->size());
		for (map<size_t, size_t>::iterator it1 = patterns.begin(); it1 != patterns.end(); it1++)
			if (!(it1->first & pattern))
				result = max(result, it1->second * it->size());
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
string Range::AlmostSorted(vector<long> const &arr)
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
				if (diff[index] + diff[0])
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
/*
 * https://www.hackerrank.com/challenges/picking-numbers/problem
 * 100%
 */
size_t Range::PickNumbersFromRange(vector<size_t> const &data)
{
	size_t max = 0;
	for (vector<size_t>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		size_t value = *it;
		size_t cnt = ranges::count_if(data, [&value](size_t j)
									  { return j == value; });
		size_t oneless = 0;
		if (value > 0)
			oneless = ranges::count_if(data, [&value](size_t j)
									   { return j == (value - 1); });
		size_t onemore = ranges::count_if(data, [&value](size_t j)
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
/*
 * https://www.hackerrank.com/challenges/non-divisible-subset/problem
 * 100%
 */
size_t Range::MaxNonDivisableSubset(vector<size_t> const &data, size_t k)
{
	vector<size_t> counts(k, 0);
	for (vector<size_t>::const_iterator it = data.begin(); it != data.end(); it++)
		counts[(*it) % k]++; // Index is the remainder: num mod k
	/*
	 * Case 1: if (!((A+B) % k)), (A mod k) = 0 and (B mod k) = 0
	 *         p = 0; q = 0: At most one number in S` from S which is perfectly divisible by k. Cannot have both 3 and 6 which are evenly divisible by k=3 in S` as 3+6 = 9 is divisible by k.
	 * Case 2: if ((A+B) % k), p + q = k
	 * case k is even and p=k-q: Cannot have two numbers which have remainder k/2 and k/2 be in S` at the same time. For example, [21, 63, 75], k = 6 => 21+63=84, 21+75=96, 63+75=138 all are divisible by k.
	 */
	size_t result = min<size_t>(counts[0], 1); // case p = 0; q = 0
	bool even = !(k % 2);
	for (size_t p = 1; p <= k / 2; p++)
		result += (!even || p != k / 2) ? max(counts[p], counts[k - p]) : min<size_t>(counts[p], 1);
	return result;
}
/*
 * https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem
 * 100%
(k:1) 1 2 3 5 9
 * 1, 2, 3, 5, 9 (k:1)
 *    c
 *          c
 * 1, 2, 3, 4, 5 (k:1)
 *    c
 *             c
(k:2) 9, 5, 4, 2, 6, 15, 12  => [2], [4, 5, 6], [9], [12], [15]
 * 2, 4, 5, 6, 9, 12, 15
 *    c
 *             c
 *                 c
 *                     c
(k: 2) 7, 2, 4, 6, 5, 9, 12, 11 => [2], [4], [5], [6], [7], [9], [11], [12]
 * 2, 4, 5, 6, 7, 9, 11, 12
 *    c
 *                c
 *                        c
 */
size_t Range::HackerlandRadioTransmitters(vector<size_t> &data, long k)
{
	ranges::sort(data);
	set<size_t> dataset(data.begin(), data.end());
	vector<size_t> installations;
	for (vector<size_t>::const_iterator it = data.begin(); it != data.end();)
	{
		size_t center = *it + k;
		for (; !dataset.count(center); center--)
			;
		installations.push_back(center);
		for (size_t end = center + k; it != data.end() && *it <= end; it++)
			;
	}
	return installations.size();
}
/*
 * https://www.hackerrank.com/challenges/sherlock-and-minimax
 * Find a value between p and q which provides the maximum of min(abs(data[i] - M))
 *
 * 100%
 */
size_t Range::SherlockAndMinimax(vector<size_t> &data, size_t p, size_t q)
{
	ranges::sort(data);
	if (q < data[0])
		return p;
	else if (p > data[data.size() - 1])
		return q;
	long maxOfMinAbs = numeric_limits<long>::min(), result, mid = data[0], diff;
	if (p < data[0]) // Checkout the head of the data
	{
		maxOfMinAbs = data[0] - p;
		result = p;
	}
	for (size_t i = 0; i < data.size() && mid < q; i++)
	{
		mid = data[i] + (data[i + 1] - data[i]) / 2;
		if (mid >= p && mid <= q)
		{
			diff = min(mid - data[i], data[i + 1] - mid);
			if (diff > maxOfMinAbs)
			{
				maxOfMinAbs = diff;
				result = mid;
			}
		}
		else if (mid < p)
		{
			diff = data[i + 1] - p;
			if (diff > maxOfMinAbs)
			{
				maxOfMinAbs = diff;
				result = p;
			}
		}
		else if (mid > q)
		{
			diff = q - data[i];
			if (diff > maxOfMinAbs)
			{
				maxOfMinAbs = diff;
				result = q;
			}
		}
	}
	if (data[data.size() - 1] < q) // Check out the tail of the data
	{
		diff = q - data[data.size() - 1];
		if (diff > maxOfMinAbs)
		{
			maxOfMinAbs = diff;
			result = q;
		}
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/chief-hopper/problem
 * 100%
3 2
3 3
3 4
2 3
1 2

4 3
4 4
3 3
2 2
2 4

4 4
3 4
2 4

3 1
4 6
2 4
*
 */
size_t Range::ChiefHopper(vector<size_t> const &data)
{
	size_t e = 0;
	for (vector<size_t>::const_reverse_iterator it = data.rbegin(); it != data.rend(); it++)
		e = (size_t)ceil((e + *it) / 2.0);
	return e;
}
/* https://www.hackerrank.com/challenges/flatland-space-stations/problem
 * 100%
 */
size_t Range::MaxClosestDistance(size_t n, vector<size_t> &c)
{
	size_t distance = 0;
	ranges::sort(c);
	for (size_t i = 0, j = 0; i < n; i++)
	{
		size_t d = numeric_limits<size_t>::max();
		if (i == c[j])
			d = 0;
		else if (i < c[j])
			d = c[j] - i;
		else // i > c[j]
		{
			d = i - c[j];
			size_t k = j;
			for (; k < c.size() && i > c[k]; k++)
			{
				size_t d1 = i - c[k];
				if (d1 <= d)
					j = k;
				d = min(d, d1);
			}
			if (k < c.size() && c[k] >= i)
			{
				size_t d1 = c[k] - i;
				if (d1 <= d)
					j = k;
				d = min(d, d1);
			}
		}
		distance = max(distance, d);
	}
	return distance;
}
/*
 * https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
 * 100%
 */
size_t Range::LiveMedianCalculation(size_t d, vector<size_t> const &data)
{
	size_t count = 0;
	bool odd = d % 2;
	size_t half = d / 2;
	vector<size_t> fifo(data.begin(), data.begin() + d);
	ranges::sort(fifo);
	for (size_t i = d; i < data.size(); i++)
	{
		double m = odd ? fifo[d / 2] : (double)(fifo[d / 2 - 1] + fifo[d / 2]) / 2l;
		if (data[i] >= 2 * m)
			count++;
		fifo.erase(find(fifo.begin(), fifo.end(), data[i - d]));
		fifo.insert(lower_bound(fifo.begin(), fifo.end(), data[i]), data[i]); // Look for element >= data[i]
	}
	return count;
}
/* https://www.hackerrank.com/challenges/xor-quadruples/problem
 * https://www.hackerrank.com/challenges/xor-quadruples/editorial
 * Time out using conventional 4 for loops due to O(N^3)
 * 100%
 * Given A,B,C,D return number of quadruples which satisfy:
 * W ^ X ^ Y ^ Z > 0
 * 1 <= W <= A
 * 1 <= X <= B
 * 1 <= Y <= C
 * 1 <= Z <= D
 * 1 <= A,B,C,D <= 3000
 * When you count the number of beautiful quadruples, you should consider two quadruples as same if the following are true:
 * They contain same integers.
 * Number of times each integers occur in the quadruple is same.
 * For example [1,1,2,3] and [1,2,1,3] should be considered as same.
 *
 * ABCD: 1 2 3 4:
1 1 1 1: 0
1 1 1 2: 3
1 1 1 3: 2
1 1 1 4: 5

1 1 2 1: 3
1 1 2 2: 0
1 1 2 3: 1
1 1 2 4: 6

1 1 3 1: 2
1 1 3 2: 1
1 1 3 3: 0
1 1 3 4: 7

1 2 1 1: 3
1 2 1 2: 0
1 2 1 3: 1
1 2 1 4: 6

1 2 2 1: 0
1 2 2 2: 3
1 2 2 3: 2
1 2 2 4: 5

1 2 3 1: 1
1 2 3 2: 2
1 2 3 3: 3
1 2 3 4: 4

1: [[1 1 2 3]]
2: [[1 1 1 3],[1 2 2 3]]
3: [[1 1 1 2],[1 2 2 2],[1 2 3 3]]
4: [[1 2 3 4]]
5: [[1 1 1 4],[1 2 2 4]]
6: [[1 1 2 4]]
7: [[1 1 3 4]]
*/
unsigned long long Range::BeautifulQuadruples(size_t a, size_t b, size_t c, size_t d)
{
	/*
		if a^b^c^d = 0 then a^b = c^d, therefore sort values to avoid duplications
	*/
	vector<size_t> abcd{a, b, c, d};
	ranges::sort(abcd);
	vector<unsigned long long> totalB(abcd[3] + 1, 0); // pair# (w,x} 1 <= w <= A, 1 <= x <= B, w <= x
	vector<unsigned long long> data;
	data.resize(abcd[3]);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	Range range;
	unsigned long long maxXOR = range.MaxXorPair(data);
	vector<vector<unsigned long long>> cntB(abcd[3] + 1, vector<unsigned long long>(maxXOR + 1, 0)); // pair# {w,x} 1 <= w <= A, 1 <= x <= B, w <= x, cntB[x][1] = w ^ x
	for (size_t w = 1; w <= abcd[0]; w++)
		for (size_t x = w; x <= abcd[1]; x++)
		{
			totalB[x]++;
			cntB[x][w ^ x]++;
		}
	// Create cumulative sum, such that, total[B] gives number of pair {w,x}, where 1 <= w <= A, "x <= B" and w <= x
	for (size_t i = 1; i < totalB.size(); i++)
		totalB[i] += totalB[i - 1];
	// Create cumulative array, so that, cntB[B][x] gives all pairs {w,x}, where "x <= B" and cntB[x][1] = w ^ x
	for (size_t x = 1; x < cntB.size(); x++)
		for (size_t z = 0; z < cntB[x].size(); z++)
			cntB[x][z] += cntB[x - 1][z];
	/* Now, what are the possible pairs of [w,x] that we can use together with [y,z] such that w^x^y^z != 0
	 * We can choose from totalB[y] pairs of [w,x]. Out of these pairs there are cntB[y][i] which, when combined with [y,z], will produce 0.
	 * This means we have a total of totalB[y] - cntB[y][i] provide non-zero result
	 */
	unsigned long long result = 0;
	for (size_t y = 1; y <= abcd[2]; y++)
		for (size_t z = y; z <= abcd[3]; z++)
			result += totalB[y] - cntB[y][y ^ z];
	return result;
}
