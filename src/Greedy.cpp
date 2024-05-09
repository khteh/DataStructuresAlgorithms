#include "Greedy.h"
template class Greedy<size_t>;
/* https://app.codility.com/programmers/lessons/16-greedy_algorithms/max_nonoverlapping_segments/
 * 100%
 */
template <typename T>
T Greedy<T>::MaxNonOverlappingSegments(vector<T> &head, vector<T> &tail)
{
    size_t count = 0, last_nonoverlapping_tail;
    if (!head.empty() && !tail.empty() && head.size() == tail.size())
    {
        last_nonoverlapping_tail = tail[0];
        count++;
        for (size_t i = 1; i < head.size(); i++)
        {
            if (head[i] > last_nonoverlapping_tail)
            {
                last_nonoverlapping_tail = tail[i];
                count++;
            }
        }
    }
    return count;
}
/* https://app.codility.com/programmers/lessons/16-greedy_algorithms/tie_ropes/
 * 100%
 * A[0] = 1
 * A[1] = 2
 * A[2] = 3
 * A[3] = 4
 * A[4] = 1
 * A[5] = 1
 * A[6] = 3
 * n: 4
 * {0,1,2},{3},{4,5,6}
 */
template <typename T>
T Greedy<T>::TieRopes(T n, vector<T> &data)
{
    size_t result = 0;
    for (vector<size_t>::iterator it = data.begin(); it != data.end();)
    {
        size_t sum = 0;
        for (; sum < n && it != data.end(); sum += *it++)
            ;
        if (sum >= n)
            result++;
    }
    return result;
}
/*
 * https://www.hackerrank.com/challenges/greedy-florist/problem
 * 100%
[1 2 3 4] k: 3 => 3 people; 4 flowers. 1 extra flower
[4 3 2 1]
i:0 => 4
i:1 => 4+3 = 7
i:2 => 7+2 = 9
i:3 => 9 + 2 * 1 = 11

P1: $4 + (1+1) * 1 = $6
P2: 3rd: 2
P3: 4th: 3

[2 5 6] k: 3
[6 5 2]
i:0 => 6
i:1 => 6+5 = 11
i:2 => 11 + 2 = 13

2 + 5 + 6 = 13

[2 5 6] k: 2 => 2 people; 3 flowers.
[6 5 2]
i:0 => 6
i:1 => 6+5 = 11
i:2 => 11 + 2*2 = 15

P1: $6 + (1+1) * 2 = $10
P2: 3rd: $5

[1 3 5 7 9] k: 3 => 3 people; 5 flowers. 2 extra flowers
[9 7 5 3 1]
i:0 => 9
i:1 => 9+7 = 16
i:2 => 16+5 = 21
i:3 => 21 + 2*3 = 27
i:4 => 27 + 2*1 = $29

P1: 1st: $9 + (1+1) * 1 = $11
P2: 3rd: $7 + (1+1) * 3 = $13
P3: 5th: $5
total: 9 + 2 + 7 + 6 + 5 = $29

[1 2 3 4 5 6 7 8 9 10] k: 3 => 3 people; 10 flowers. 1 extra flower
[10 9 8 7 6 5 4 3 2 1]
i:0 -> 10
i:1 -> 10+9 = 19
i:2 -> 19+8 = 27
i:3 -> 27 + 2*7 = 41
i:4 -> 41 + 2*6 = 53
i:5 -> 53 + 2*5 = 63
i:6 -> 63 + 3*4 = 75
i:7 -> 75 + 3*3 = 84
i:8 -> 84 + 3*2 = 90
i:9 -> 90 + 4*1 = 94

P1: 10 + (1+1)*1 + (2+1)*2 = 10 + 2 + 6 = $18
P2: 9 + (1+1)*3 + (2+1)*4 = 9 + 6 + 12 = $27
P3: 8 + (1+1)*5 + (2+1)*6 = 8 + 10 + 18 = $36
extra: (3 + 1) * $7 = $28 => total: $109

P1: 10 + (1+1)*1 + (2+1)*2 + (3+1) * 3 = 10 + 2 + 6 + 12 = $30
P2: 9 + (1+1)*4 + (2+1)*5 = 9 + 8 + 15 = $32
P3: 8 + (1+1)*6 + (2+1)*7 = 8 + 12 + 21 = $41
total: $103
*/
template <typename T>
T Greedy<T>::GetMinimumCost(T n, vector<T> &costs)
{
    size_t total = 0;
    ranges::sort(costs, greater<size_t>());
    for (size_t i = 0, multiplier = 1; i < costs.size(); i++)
    {
        if (i > 0 && !(i % n))
            multiplier++;
        total += multiplier * costs[i];
    }
    return total;
}
/*
 * https://www.hackerrank.com/challenges/angry-children/problem
 * 100%
 */
template <typename T>
T Greedy<T>::MaxMin(T k, vector<T> &arr)
{
    ranges::sort(arr);
    T unfair = numeric_limits<T>::max();
    T max = 0;
    for (size_t i = 0; i < arr.size() && max < arr.size() - 1; i++)
    {
        for (max = i + k - 1; max >= arr.size(); max--)
            ;
        if (i != max)
        {
            size_t diff = abs(abs((long)arr[max]) - abs((long)arr[i]));
            if (diff < unfair)
                unfair = diff;
        }
    }
    return unfair;
}
/*
 * https://www.hackerrank.com/challenges/equal/problem
 * https://rohangupta-3817.medium.com/hackerrank-dp-equal-5adc78771571
 * 100%
 *
 * Each round can add 1, 2 or 5 to all except one element
 *
 * Strategy: Only need to consider the unique numbers. Converge the range to the max number.
 *
 * 1 1 5 => 1 1 3 => 1 1 1 (baseline: min element)
 *
 * 2 2 3 7 => 2 2 3 2 => 2 2 2 2 (baseline: min element)
 *
 * 10 7 12 => 10 7 7 -> 8 7 7 -> 7 7 7 (baseline: min element)
 *
 * 1 2 3 4 => 0 2 3 4 -> 0 0 3 4 -> 0 0 1 4 -> 0 0 0 4 -> 0 0 0 2 -> 0 0 0 0
 *		   => 1 1 3 4 -> 1 1 1 4 -> 1 1 1 2 -> 1 1 1 1 (baseline: min element)

 * 1 3 5 7 9 => 1 1 5 7 9 -> 1 1 3 7 9 -> 1 1 1 7 9 -> 1 1 1 2 9 -> 1 1 1 1 9 -> 1 1 1 1 4 -> 1 1 1 1 2 -> 1 1 1 1 1 (baseline: min element)
             => 0 3 5 7 9 -> 0 1 5 7 9 -> 0 0 5 7 9 -> 0 0 0 7 9 -> 0 0 0 2 9 -> 0 0 0 0 9 -> 0 0 0 0 4 -> 0 0 0 0 2 -> 0 0 0 0 0 (baseline: min element - 1)
             => -1 3 5 7 9 -> -1 1 5 7 9 -> -1 -1 5 7 9 -> -1 -1 0 7 9 -> -1 -1 -1 7 9 -> -1 -1 -1 2 9 -> -1 -1 -1 0 9 -> -1 -1 -1 -1 9 -> ......
 *
 * 0 1 2 -> 0 0 2 -> 0 0 0
 * 0 1 3 -> 0 0 3 -> 0 0 1 -> 0 0 0
 * 		 -> -1 1 3 -> -1 -1 3 -> -1 -1 1 -> ...
 * 		 -> 0 1 1 -> 0 0 1 -> 0 0 0 (baseline: min element)
 * 0 1 4 -> 0 0 4 -> 0 0 2 -> 0 0 0
 * 	 	 -> 0 1 -1 -> 0 -1 -1 -> -1 -1 -1 (baseline: min element OR min - 1)
 * 0 1 5 -> 0 1 0 -> 0 0 0
 *
 * 0 1 1 -> 0 0 1 -> 0 0 0
 * 0 2 2 -> 0 0 2 -> 0 0 0
 * 0 3 3 -> 0 1 3 -> 0 0 3 -> 0 0 1 -> 0 0 0
 * 		 -> -1 3 3 -> -1 1 3 -> -1 -1 3 -> -1 -1 1 -> -1 -1 -1 (baseline: min - 1)
 * 		 -> 0 -2 3 -> 0 -2 -2 -> -2 -2 -2 (baseline: min - 2)
 *
 * 0 4 4 -> 0 2 4 -> 0 0 4 -> 0 0 2 -> 0 0 0
 * 		 -> 0 -1 4 -> 0 -1 -1 -> -1 -1 -1 (baseline: min - 1)
 *
 * 0 5 5 -> 0 0 5 -> 0 0 0
 * There are only 3 baselines: min value, min - 1, min - 2
 */
template <typename T>
T Greedy<T>::EqualDistribution(vector<T> &data)
{
    size_t count = numeric_limits<size_t>::max();
    T minElement = *ranges::min_element(data);
    for (size_t base = 0; base <= 2; base++)
    {
        size_t steps = 0;
        long step = minElement - base;
        for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
        {
            long diff = *it - step;
            steps += diff / 5 + (diff % 5) / 2 + (diff % 5) % 2;
        }
        count = min(count, steps);
    }
    return count;
}