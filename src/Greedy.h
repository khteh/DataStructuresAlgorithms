#pragma once
#include <assert.h>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include "oneapi/tbb.h"
#include "Vertex.h"
using namespace oneapi::tbb;
using namespace std;
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