#include "GameTheory.h"
/*
 * https://www.hackerrank.com/challenges/chocolate-in-box/problem
 * https://en.wikipedia.org/wiki/Nim
 * Normal play: Player to take the LAST object wins.
 * Misère play: Player to take the LAST object loses.
 *
 * Theorem. In a normal Nim game, the player making the first move has a winning strategy if and only if the nim-sum of the sizes of the heaps is not zero.
 * Otherwise, the second player has a winning strategy.
 *
 * In normal play, the winning strategy is to finish every move with a nim-sum of 0. This is always possible if the nim-sum is not zero before the move.
 * If the nim-sum is zero, then the next player will lose if the other player does not make a mistake. To find out which move to make,
 * let X be the nim-sum of all the heap sizes. Find a heap where the nim-sum of X and heap-size is less than the heap-size;
 * the winning strategy is to play in such a heap, reducing that heap to the nim-sum of its original size with X.
 * In the example above, taking the nim-sum of the sizes is X = 3 ⊕ 4 ⊕ 5 = 2. The nim-sums of the heap sizes A=3, B=4, and C=5 with X=2 are
 * A ⊕ X = 3 ⊕ 2 = 1 [Since (011) ⊕ (010) = 001 ] <= the nim-sum of X and heap-size is less than the heap-size
 * B ⊕ X = 4 ⊕ 2 = 6
 * C ⊕ X = 5 ⊕ 2 = 7
 * The only heap that is reduced is heap A, so the winning move is to reduce the size of heap A to 1 (by removing two objects).
 *
 * Normal play:
 * [1, 2, 1] -> [1, 0, 1] -> [0,0,1]	(Nim-sum: 2)
 *    [2, 3] -> [2, 2] -> [1, 2] -> [1,1] -> [0,1] (Nim-sum: 1)
 *
 * Misère play (Same strategy as Normal play):
 * [1, 2, 1] -> [1, 1, 1] -> [0,1,1] -> [0,0,1] (Nim-sum: 2)
 *    [2, 3] -> [2, 2] -> [1, 2] -> [1,0]	(Nim-sum: 1)
 * 100%
 */
size_t GameTheory::NormalPlayNim(vector<size_t> &data)
{
#ifdef _MSC_VER
    // https://docs.microsoft.com/en-us/cpp/parallel/concrt/how-to-perform-map-and-reduce-operations-in-parallel?view=msvc-170
    size_t sum = parallel_reduce(data.begin(), data.end(), 0 /* Identity for XOR */, [](size_t a, size_t b)
                                 { return a ^ b; });
#elif defined(__GNUC__) || defined(__GNUG__)
    size_t sum = parallel_reduce(
        blocked_range<size_t>(0, data.size()), 0 /* Identity for XOR */,
        [&](tbb::blocked_range<size_t> r, size_t running_total)
        {
            for (int i = r.begin(); i < r.end(); i++)
                running_total ^= data[i];
            return running_total;
        },
        std::bit_xor<size_t>());
#endif
    if (!sum) // In a normal Nim game, the player making the first move has a winning strategy if and only if the nim-sum of the sizes of the heaps is not zero.
        return 0;
    size_t count = 0;
    for (vector<size_t>::iterator it = data.begin(); it != data.end(); it++)
        if ((*it ^ sum) < *it)
            count++;
    return count;
}
/*
 * https://www.hackerrank.com/challenges/counter-game/problem
 * 100%
 */
bool GameTheory::CounterGame(long n)
{
    bool flag = false;
    for (; n > 1; flag = !flag)
    {
        bool isPowerOfTwo = !(n & (n - 1));
        if (isPowerOfTwo)
            n /= 2;
        else
        {
            unsigned long m = 1UL << (sizeof(long) * 8 - 1);
            for (; !(m & n); m >>= 1)
                ;
            n -= m;
        }
        if (n == 1)
            return flag;
    }
    return flag;
}
/*
 * https://www.hackerrank.com/challenges/game-of-stones-1/problem
 * The winning pattern repeats every 7 stones
 * 100%
 */
string GameTheory::GameOfStones(size_t n)
{
    return n % 7 <= 1 ? "Second" : "First";
}