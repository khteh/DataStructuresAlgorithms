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
	vector<vector<T>> _matrix;

public:
	Matrix();
	Matrix(vector<vector<T>> &);
	void MatrixDistance(vector<vector<T>> &, size_t, size_t);
	void MatrixSort(vector<vector<T>> &);
	T MatrixPatternCount(vector<vector<T>> &);
	void MatrixSortWithHeap(vector<vector<T>> &);
	T Sum(vector<vector<size_t>> &);
	T LargestSumSubmatrix(vector<vector<size_t>> &);
	bool SearchMatrix(T, vector<vector<T>> const &) const;
	bool SearchMatrix1(T, vector<vector<T>> const &) const;
	bool SearchMatrixRow(vector<vector<T>> const &, T, size_t, T, T) const;
	bool SearchMatrixCol(vector<vector<T>> const &, T, size_t, T, T) const;
	void RotateMatrix90DegressClockwise(vector<vector<T>> &);
	void RotateMatrixRTimesAntiClockwise(vector<vector<T>> &, size_t);
	vector<T> MatrixSprialOrder(vector<vector<T>> &);
	T ChessQueensMoveCount(T, T /*[1,rows]*/, T /*[1,cols]*/, vector<vector<size_t>> &);
	size_t GridlandMetro(T, T, vector<vector<T>> const &);
	size_t SurfaceArea3D(vector<vector<T>> const &);
};