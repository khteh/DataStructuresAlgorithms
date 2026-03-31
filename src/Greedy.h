#pragma once
#include "Vertex.h"
template <typename T>
class Greedy
{
public:
    T MaxNonOverlappingSegments(vector<T> const &, vector<T> const &);
    T TieRopes(T, vector<T> const &);
    T GetMinimumCost(T, vector<T> &);
    T MaxMin(T, vector<T> &);
    T EqualDistribution(vector<T> const &);
    T MaxArea(vector<T> const &);
    bool CanReachDestination(vector<T> const &);
};