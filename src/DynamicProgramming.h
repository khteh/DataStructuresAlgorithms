#pragma once
#include <algorithm>
#include <limits>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <set>
#include <map>
#include <math.h>
#include <ranges>
#include "GenericConstraints.h"
#include "Arithmetic.h"
using namespace std;
template <typename T>
class DynamicProgramming
{
public:
    long double Factorial(T)
        requires arithmetic_type<T>;
    long double Fibonacci(T)
        requires arithmetic_type<T>;
    string FibonacciModified(T, T, T)
        requires arithmetic_type<T>;
    T LargestNumberCompositionProduct(T)
        requires arithmetic_type<T>;
    T EggDrops(T, T)
        requires arithmetic_type<T>;
    bool WordBreak(string const &, set<string> const &);
    void WordBreak2(string const &, set<string> const &, vector<string> &);
    bool Abbreviation(string const &, string const &);
    size_t FindSubsequence(string const &, string const &);
    T NumberSolitaire(vector<T> const &)
        requires arithmetic_type<T>;
    unsigned long long WaysToFillRange(T, T, T)
        requires arithmetic_type<T>;
};