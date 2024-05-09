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
// https://www.hackerrank.com/challenges/greedy-florist/problem
// XXX: 0%
// 3 2
// 2 5 6 : 1..2 [1]
// 5 3
// 1 3 5 7 9 : 1..2 [2]
// 5 3
// 1 3 5 7 9
template <typename T>
T Greedy<T>::GetMinimumCost(T k, vector<T> &c)
{
    size_t price = 0;
    if (!c.empty())
    {
        size_t flowers = c.size();
        if (flowers > k)
        {
            size_t solos = 0;
            while ((flowers - solos) % k)
            {
                solos++;
                k--;
            }
            size_t perperson = (c.size() - solos) / k;
            ranges::sort(c);
            size_t soloCnt = 0;
            for (vector<size_t>::reverse_iterator it = c.rbegin(); it != c.rend() && soloCnt < solos; it++, soloCnt++)
                price += *it;
            for (size_t firstflower = c.size() - 1 - solos; k > 0; k--, firstflower--)
            {
                price += c[firstflower];
                for (size_t i = 1; i < perperson; i++)
                {
                    if (firstflower == perperson - 1)
                        price += c[firstflower - i] * (i + 1);
                    else
                        price += c[firstflower - perperson * i] * (i + 1);
                }
            }
        }
        else
        {
#ifdef _MSC_VER
            price = parallel_reduce(c.begin(), c.end(), 0);
#elif defined(__GNUC__) || defined(__GNUG__)
            price = parallel_reduce(
                blocked_range<size_t>(0, c.size()), 0,
                [&](tbb::blocked_range<size_t> r, size_t running_total)
                {
                    for (int i = r.begin(); i < r.end(); ++i)
                        running_total += c[i];
                    return running_total;
                },
                std::plus<size_t>());
#endif
        }
    }
    return price;
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