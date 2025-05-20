#pragma once
#include "Vertex.h"
template <typename T>
class GameTheory
{
public:
    bool SolvabilityOfTheTilesGame(vector<T> const &);
    size_t SnakesAndLaddersGame(vector<vector<T>> const &, vector<vector<T>> const &);
    size_t SnakesAndLaddersGameFast(vector<vector<T>> const &, vector<vector<T>> const &);
    size_t NormalPlayNim(vector<T> const &);
    size_t MisèrePlayNim(vector<T> const &);
    size_t NimbleGame(vector<T> const &);
    bool CounterGame(T n); // long
    string GameOfStones(T);
};