#pragma once
#include "GenericConstraints.h"
using namespace std;
template <typename T>
class MaximizeStockProfits
{
public:
    T MaxProfitK1(vector<T> const &)
        requires arithmetic_type<T>;
    T MaxProfitK2(vector<T> const &)
        requires arithmetic_type<T>;
    T MaxProfitKInfinity(vector<T> const &)
        requires arithmetic_type<T>;
    T MaxProfitKArbitrary(vector<T> const &, size_t)
        requires arithmetic_type<T>;
    T MaxProfitKInfinityCoolDown(vector<T> const &)
        requires arithmetic_type<T>;
    T MaxProfitKInfinityWithFee(vector<T> const &, T)
        requires arithmetic_type<T>;
    T MaxProfit(vector<T> const &)
        requires arithmetic_type<T>;
};