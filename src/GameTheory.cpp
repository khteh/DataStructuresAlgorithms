#include "GameTheory.h"
template class GameTheory<long>;
template class GameTheory<size_t>;

/* https://www.hackerrank.com/challenges/larrys-array/problem
   https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
Formula: ( (grid width odd) && (#inversions even) )  ||  ( (grid width even) && ((blank on odd row from bottom) == (#inversions even)) )
   The given array can be then compared to a rectangle of width 3, and any height h, so that total number of tiles is (3*h)-1.
   (Like it was (w*h)-1 in the original 15 tile puzzle)
blank spaces for a grid with width 3 to satisfy (3*h)-1:
0: add 2
1: add 0
2: add 1
    Don't have to add anything to the input data to fulfil the (3*h)-1 tiles since we can arbitrarily add the numbers which are in-sequence and bigger than the biggest number currently in the board.
    100%
*/
template <typename T>
bool GameTheory<T>::SolvabilityOfTheTilesGame(vector<T> const &data)
{
    size_t inversions = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        T item = data[i];
        T smallerItems = ranges::count_if(data.begin(), data.begin() + i, [&item](T i)
                                          { return i < item; });
        inversions += item - 1 - smallerItems;
    }
    return !(inversions % 2);
}
/*
 * https://www.hackerrank.com/challenges/the-quickest-way-up/problem
 * http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code/
 * Times out!
 */
template <typename T>
size_t GameTheory<T>::SnakesAndLaddersGame(vector<vector<T>> const &ladders, vector<vector<T>> const &snakes)
{
    map<T, T> laddermap, snakemap;
    shared_ptr<Vertex<T, T>> root(make_shared<Vertex<T, T>>(1));
    map<T, shared_ptr<Vertex<T, T>>> vertices;
    vertices.emplace(1, root);
    for (size_t i = 0; i < ladders.size(); i++)
        laddermap.emplace(ladders[i][0], ladders[i][1]);
    for (size_t i = 0; i < snakes.size(); i++)
        snakemap.emplace(snakes[i][0], snakes[i][1]);
    for (size_t i = 1; i <= 100; i++)
        if (laddermap.find(i) == laddermap.end() && snakemap.find(i) == snakemap.end())
        { // Skip the number if it is at the beginning of a ladder
            shared_ptr<Vertex<T, T>> parent = vertices.find(i) != vertices.end() ? vertices[i] : nullptr;
            if (!parent)
            {
                parent = make_shared<Vertex<T, T>>(i);
                vertices.emplace(i, parent);
            }
            for (size_t j = min(6L, (long)(100L - i)); j > 0; j--)
            {
                size_t next = i + j;
                if (laddermap.find(next) != laddermap.end())
                    next = laddermap[next];
                if (snakemap.find(next) != snakemap.end())
                    next = snakemap[next];
                shared_ptr<Vertex<T, T>> vertex = vertices.find(next) != vertices.end() ? vertices[next] : nullptr;
                if (!vertex)
                {
                    vertex = make_shared<Vertex<T, T>>(next);
                    vertices.emplace(next, vertex);
                }
                parent->AddNeighbour(vertex, 0);
            }
        }
    size_t level = 0;
    map<T, vector<shared_ptr<Vertex<T, T>>>> result;
    result.emplace(level, vector<shared_ptr<Vertex<T, T>>>{root});
    for (; !result[level].empty(); level++)
    {
        vector<shared_ptr<Vertex<T, T>>> tmp;
        for (typename vector<shared_ptr<Vertex<T, T>>>::const_iterator it = result[level].begin(); it != result[level].end(); it++)
        {
            if ((*it)->GetTag() == 100)
                return level;
            vector<shared_ptr<Vertex<T, T>>> neighbours = (*it)->GetNeighbours();
            tmp.insert(tmp.end(), neighbours.begin(), neighbours.end());
        }
        result.emplace(level + 1, tmp);
    }
    return 0;
}
/*
 * https://www.hackerrank.com/challenges/the-quickest-way-up/problem
 * http://theoryofprogramming.com/2014/12/25/snakes-and-ladders-game-code/
 * 100%
 */
template <typename T>
size_t GameTheory<T>::SnakesAndLaddersGameFast(vector<vector<T>> const &ladders, vector<vector<T>> const &snakes)
{
    map<T, vector<T>> adjacency_list;
    map<T, T> laddermap, snakemap;
    for (size_t i = 0; i < ladders.size(); i++)
        laddermap.emplace(ladders[i][0], ladders[i][1]);
    for (size_t i = 0; i < snakes.size(); i++)
        snakemap.emplace(snakes[i][0], snakes[i][1]);
    for (size_t i = 1; i <= 100; i++)
        if (laddermap.find(i) == laddermap.end() && snakemap.find(i) == snakemap.end())
        { // Skip the number if it is at the beginning of a ladder
            for (size_t j = min(6L, (long)(100L - i)); j > 0; j--)
            {
                size_t next = i + j;
                if (laddermap.find(next) != laddermap.end())
                    next = laddermap[next];
                if (snakemap.find(next) != snakemap.end())
                    next = snakemap[next];
                adjacency_list[i].push_back(next);
            }
        }
    size_t level = 0;
    map<T, vector<T>> result;
    result.emplace(level, vector<T>{1});
    set<T> visited;
    for (; !result[level].empty(); level++)
    {
        vector<T> tmp;
        for (typename vector<T>::const_iterator it = result[level].begin(); it != result[level].end(); it++)
        {
            if (visited.find(*it) == visited.end())
            {
                if (*it == 100)
                    return level;
                if (adjacency_list.find(*it) != adjacency_list.end())
                    tmp.insert(tmp.end(), adjacency_list[*it].begin(), adjacency_list[*it].end());
                visited.insert(*it);
            }
        }
        result.emplace(level + 1, tmp);
    }
    return 0;
}

/*
 * https://www.hackerrank.com/challenges/chocolate-in-box/problem
 * https://www.hackerrank.com/challenges/nim-game-1/problem?isFullScreen=true
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
 * The only heap that is reduced is heap A, so the winning move is to reduce the size of heap A to 1 (by removing two objects).
 * A ⊕ X = 3 ⊕ 2 = 1 [Since (011) ⊕ (010) = 001 ] <= the nim-sum of X and heap-size is less than the heap-size.
 * B ⊕ X = 4 ⊕ 2 = 6
 * C ⊕ X = 5 ⊕ 2 = 7
 *
 * These strategies for normal play and a misère game are the same until the number of heaps with at least two objects is exactly equal to one. At that point,
 * the next player removes either all objects (or all but one) from the heap that has two or more, so no heaps will have more than one object (in other words,
 * so all remaining heaps have exactly one object each), so the players are forced to alternate removing exactly one object until the game ends. In normal play,
 * the player leaves an even number of non-zero heaps, so the same player takes last; in misère play, the player leaves an odd number of non-zero heaps, so the other player takes last.
 *
 * Normal play - Leaves even number of heaps with exactly only 1 object each:
 * [1, 1, 1] -> [0, 1, 1] -> [0, 0, 1]  (Nim-sum: 1)
 * [1, 2, 1] -> [1, 0, 1] -> [0,0,1]	(Nim-sum: 2)
 *    [2, 3] -> [2, 2] -> [1, 2] -> [1,1] -> [0,1] (Nim-sum: 1)
 * [3, 4, 5] -> [1, 4, 5] -> [1, 4, 2] -> [1, 3, 2] -> [1, 2, 2] -> [0, 2, 2] -> [0, 1, 2] -> [0, 1, 1] (Nim-sum: 2)
 * [9 8 4 4 4 7] (Nim-sum: 2)
 *
 * Misère play (Same strategy as Normal play) - Leaves odd number of heaps with exactly only 1 object each:
 * [1, 2, 3] -> [0, 2, 3] -> [0, 2, 2] -> [0, 1, 2] -> [0, 1, 0] (Nim-sum: 0)
 * [1, 2, 1] -> [1, 1, 1] -> [0,1,1] -> [0,0,1] (Nim-sum: 2)
 *    [2, 3] -> [2, 2] -> [1, 2] -> [1,0]	(Nim-sum: 1)
 * [3, 4, 5] -> [1, 4, 5] -> [1, 4, 3] -> [1, 2, 3] -> [1, 2, 2] -> [0, 2, 2] -> [0, 1, 2] -> [0, 1, 1] (Nim-sum: 2)
 * 100%
 */
template <typename T>
size_t GameTheory<T>::NormalPlayNim(vector<T> const &data)
{
#ifdef _MSC_VER
    // https://docs.microsoft.com/en-us/cpp/parallel/concrt/how-to-perform-map-and-reduce-operations-in-parallel?view=msvc-170
    // https://en.wikipedia.org/wiki/Identity_element
    T sum = parallel_reduce(data.begin(), data.end(), 0 /* Identity for Addition */, [](T a, T b)
                            { return a ^ b; });
#elif defined(__GNUC__) || defined(__GNUG__)
    T sum = parallel_reduce(
        blocked_range<T>(0, data.size()), 0 /* Identity for Addition */,
        [&](tbb::blocked_range<T> r, T running_total)
        {
            for (int i = r.begin(); i < r.end(); i++)
                running_total ^= data[i];
            return running_total;
        },
        std::bit_xor<T>());
#endif
    if (!sum)     // In a normal Nim game, the player making the first move has a winning strategy if and only if the nim-sum of the sizes of the heaps is not zero.
        return 0; // return "Second"
    size_t count = 0;
    for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
        if ((*it ^ sum) < *it)
            count++; // return "First"
    return count;    // return "Second"
}
/*
 * https://www.hackerrank.com/challenges/misere-nim-1/problem
 * https://mathoverflow.net/questions/71802/analysis-of-misere-nim
 * It is both well-known and easy to verify that a Nim position (n1,…,nk) is a second player win in misère Nim if and only if some ni>1
 * and n1⊕⋯⊕nk=0, or all ni≤1 and n1⊕⋯⊕nk=1
 * 100%
 */
template <typename T>
size_t GameTheory<T>::MisèrePlayNim(vector<T> const &data)
{
#ifdef _MSC_VER
    // https://docs.microsoft.com/en-us/cpp/parallel/concrt/how-to-perform-map-and-reduce-operations-in-parallel?view=msvc-170
    // https://en.wikipedia.org/wiki/Identity_element
    T sum = parallel_reduce(data.begin(), data.end(), 0 /* Identity for Addition */, [](T a, T b)
                            { return a ^ b; });
#elif defined(__GNUC__) || defined(__GNUG__)
    size_t sum = parallel_reduce(
        blocked_range<T>(0, data.size()), 0 /* Identity for Addition */,
        [&](tbb::blocked_range<T> r, T running_total)
        {
            for (int i = r.begin(); i < r.end(); i++)
                running_total ^= data[i];
            return running_total;
        },
        std::bit_xor<T>());
#endif
    typename vector<T>::const_iterator it = ranges::find_if(data, [](const auto &value)
                                                            { return value > 1; }); // Look for element <= data[i]
    return ((!sum && it != data.end()) || sum == 1 && it == data.end()) ? 1 /* Second*/ : 0 /* First*/;
}
/*
 * https://www.hackerrank.com/challenges/nimble-game-1/problem
 * Haven't figured out the logic.
 * 100%
 */
template <typename T>
size_t GameTheory<T>::NimbleGame(vector<T> const &data)
{
    T sum = 0;
    for (size_t i = 0; i < data.size(); i++)
        if (data[i] % 2)
            sum ^= i;
    return sum ? 0 /*"First" */ : 1 /*"Second"*/;
}
/*
 * https://www.hackerrank.com/challenges/counter-game/problem
 * 100%
 */
template <typename T>
bool GameTheory<T>::CounterGame(T n) // long
{
    bool flag = false;
    for (; n > 1; flag = !flag)
    {
        bool isPowerOfTwo = !(n & (n - 1));
        if (isPowerOfTwo)
            n /= 2;
        else
        {
            unsigned long m = 1UL << (sizeof(T) * 8 - 1);
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
template <typename T>
string GameTheory<T>::GameOfStones(T n)
{
    return n % 7 <= 1 ? "Second" : "First";
}