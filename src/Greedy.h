#pragma once
#include <assert.h>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include "Vertex.h"
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
using namespace tbb;
#endif
template <typename T>
class Greedy
{
public:
    T MaxNonOverlappingSegments(vector<T> &, vector<T> &);
    T TieRopes(T, vector<T> &);
    T GetMinimumCost(T, vector<T> &);
    T MaxMin(T, vector<T> &);
    T EqualDistribution(vector<T> &);
};