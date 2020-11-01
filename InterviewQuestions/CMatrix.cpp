#include "stdafx.h"
#include "CMatrix.h"
template class CMatrix<long>;
/*
* Matrix area sum using bottom-up dynamic programming
* 	0	1	2	3
0	2	0	-3	4
1	6	3	2	-1
2	5	4	7	3
3	2	-6	8	1
				
	0	1	2	3
0	2	2	-1	3
1	8	11	10	13
2	13	20	26	32
3	15	16	30	37
				
[1,1] - [3,2]			30 - 15 - (-1) + 2 = 18	
[0,2] - [3,3]			37 - 16 = 21	

https://leetcode.com/problems/range-sum-query-2d-immutable/
https://www.youtube.com/watch?v=PwDqpOMwg6U
*/
template<typename T>
CMatrix<T>::CMatrix(vector<vector<T>>& matrix)
	:_matrix(matrix.size(), vector<T>(matrix.empty() ? 0 : matrix[0].size())) // Defaults to zero initial value
{
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[i].size(); j++) {
			_matrix[i][j] = matrix[i][j];
			if (i > 0)
				_matrix[i][j] += _matrix[i - 1][j];
			if (j > 0)
				_matrix[i][j] += _matrix[i][j - 1];
			if (i > 0 && j > 0)
				_matrix[i][j] -= _matrix[i - 1][j - 1];
		}
}
template<typename T>
T CMatrix<T>::Sum(vector<vector<size_t>>& area)
{
	if (_matrix.empty() || area.empty() || area.size() < 2 || area[0].size() < 2)
		return 0;
	size_t r1 = area[0][0], c1 = area[0][1], r2 = area[1][0], c2 = area[1][1];
	if (r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0 || r2 < r1 || c2 < c1 || r2 >= _matrix.size() || c2 >= _matrix[0].size())
		return 0;
	T sum = _matrix[r2][c2];
	if (r1 > 0)
		sum -= _matrix[r1 - 1][c2];
	if (c1 > 0)
		sum -= _matrix[r2][c1 - 1];
	if (r1 > 0 && c1 > 0)
		sum += _matrix[r1 - 1][c1 - 1];
	return sum;
}