#pragma once
#include <vector>
#include <limits>
using namespace std;
template<typename T>
class CMatrix
{
private:
	vector<vector<T>> _matrix;
public:
	CMatrix(vector<vector<T>>&);
	T Sum(vector<vector<size_t>>&);
	T LargestSumSubmatrix(vector<vector<size_t>>&);
};