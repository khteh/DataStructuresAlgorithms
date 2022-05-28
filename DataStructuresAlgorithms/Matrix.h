#pragma once
#include <vector>
#include <limits>
using namespace std;
template <typename T>
class Matrix
{
private:
	vector<vector<T>> _matrix;

public:
	Matrix(vector<vector<T>> &);
	T Sum(vector<vector<size_t>> &);
	T LargestSumSubmatrix(vector<vector<size_t>> &);
};