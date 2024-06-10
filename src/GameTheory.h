#pragma once
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <ranges>
#include <memory>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
using namespace tbb;
#endif
#include "Vertex.h"
using namespace std;
template <typename T>
class GameTheory
{
private:
    set<string> _permutationGameWinningNumbersCache;
    bool IsIncreasingSequence(string const &);
    bool PermutationGameCheckCurrentPlayer(string);

public:
    bool SolvabilityOfTheTilesGame(vector<T> const &);
    size_t SnakesAndLaddersGame(vector<vector<T>> const &, vector<vector<T>> const &);
    size_t SnakesAndLaddersGameFast(vector<vector<T>> const &, vector<vector<T>> const &);
    size_t NormalPlayNim(vector<T> const &);
    size_t MisèrePlayNim(vector<T> const &);
    size_t NimbleGame(vector<T> const &);
    bool CounterGame(T n); // long
    string GameOfStones(T);
    bool PermutationGame(vector<T> const &);
};