#pragma once
#include "Vertex.h"
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