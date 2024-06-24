#pragma once
#include <assert.h>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include "Vertex.h"
#include "oneapi/tbb.h"
using namespace oneapi::tbb;
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