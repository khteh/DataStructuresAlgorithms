#pragma once
#include <limits>
#include <vector>
#include <sstream>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
using namespace tbb;
#endif
using namespace std;
class GameTheory
{
public:
    size_t NormalPlayNim(vector<size_t> &);
    bool CounterGame(long n);
    string GameOfStones(size_t);
};