#pragma once
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <ranges>
#include <memory>
#include "oneapi/tbb.h"
#include "Vertex.h"
using namespace oneapi::tbb;
using namespace std;
template <typename T>
class GameTheory
{
private:
    set<vector<T>> _permutationGameWinningNumbersCache;
    bool IsIncreasingSequence(vector<T> const &);

public:
    bool SolvabilityOfTheTilesGame(vector<T> const &);
    size_t SnakesAndLaddersGame(vector<vector<T>> const &, vector<vector<T>> const &);
    size_t SnakesAndLaddersGameFast(vector<vector<T>> const &, vector<vector<T>> const &);
    size_t NormalPlayNim(vector<T> const &);
    size_t MisèrePlayNim(vector<T> const &);
    size_t NimbleGame(vector<T> const &);
    bool CounterGame(T n); // long
    string GameOfStones(T);
    bool PermutationGame(const vector<T>);
};