#pragma once
#include <vector>
#include <limits>
#include <ranges>
#include <algorithm>
#include "Heap.h"
#include "Sort.h"
using namespace std;
namespace ranges = std::ranges;
template <typename T>
class Matrix
{
private:
	vector<vector<T>> matrix_;
public:
	Matrix();
	Matrix(vector<vector<T>> &);
	void MatrixDistance(vector<vector<T>>&, size_t, size_t);
	void MatrixSort(vector<vector<T>>&);
	T MatrixPatternCount(vector<vector<T>>&);
	void MatrixSortWithHeap(vector<vector<T>>&);
	T Sum(vector<vector<size_t>> &);
	T LargestSumSubmatrix(vector<vector<size_t>> &);
	bool SearchMatrix(vector<vector<T>>&, T);
	bool SearchMatrix1(vector<vector<T>>&, T);
	bool SearchMatrixRow(vector<vector<T>>&, T, size_t, T, T);
	bool SearchMatrixCol(vector<vector<T>>&, T, size_t, T, T);
	void RotateMatrix90DegressClockwise(vector<vector<T>>&);
	void RotateMatrixRTimesAntiClockwise(vector<vector<T>>&, size_t);
	vector<T> MatrixSprialOrder(vector<vector<T>>&);
};