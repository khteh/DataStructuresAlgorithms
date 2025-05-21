#pragma once
#include "Arithmetic.h"
#include "cout128.h"
using namespace std;
template <typename T>
class DynamicProgramming
{
public:
    T Factorial(size_t, T modulo = 0)
        requires arithmetic_type<T>;
    T Fibonacci(long)
        requires arithmetic_type<T>;
    string FibonacciModified(T, T, size_t)
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
    void FloydWarshall(size_t, vector<vector<T>> const &, vector<vector<T>> &)
        requires signed_integral_type<T>;
    T VectorSlicesSum(vector<T> const &)
        requires arithmetic_type<T>;
};