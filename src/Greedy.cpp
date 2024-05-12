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
[1 2 3 4 5 6 7 8 9 10] k: 3 => 3 people; 10 flowers. 1 extra flower
[10 9  8  7    6    5    4    3    2    1]
 P1 P2 P3 P1+1 P2+1 P3+1 P1+2 P2+2 P3+2 P1+3
 10+9+8+ 2*7 + 2*6 + 2*5 + 3*4 + 3*3 + 3*2 + 4*1 = 27 + 14 + 12 + 10 + 12 + 9 + 6 + 4 = $94
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