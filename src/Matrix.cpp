#include "stdafx.h"
#include "Matrix.h"
template class Matrix<long>;
template <typename T>
Matrix<T>::Matrix() {}
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
template <typename T>
Matrix<T>::Matrix(vector<vector<T>> &matrix)
	: _matrix(matrix.size(), vector<T>(matrix.empty() ? 0 : matrix[0].size())) // Defaults to zero initial value
{
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			_matrix[i][j] = matrix[i][j];
			if (i > 0)
				_matrix[i][j] += _matrix[i - 1][j];
			if (j > 0)
				_matrix[i][j] += _matrix[i][j - 1];
			if (i > 0 && j > 0)
				_matrix[i][j] -= _matrix[i - 1][j - 1];
		}
}
// -1  0 -1
// -1 -1 -1
// -1 -1 -1
template <typename T>
void Matrix<T>::MatrixDistance(vector<vector<T>> &data, size_t x, size_t y)
{
	if (x < data.size() && y < data[0].size())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			for (size_t j = 0; j < data[0].size(); j++)
			{
				if (x != i && y != j)
					data[i][j] = abs((T)(x - i)) + abs((T)(y - j));
				else if (x == i && y != j)
					data[i][j] = abs((T)(y - j));
				else if (x != i && y == j)
					data[i][j] = abs((T)(x - i));
			}
		}
	}
}
template <typename T>
void Matrix<T>::MatrixSort(vector<vector<T>> &data)
{
	Sort<T> sort;
	vector<T> sorted;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			sorted.push_back(data[i][j]);
	sort.QuickSort(sorted, 0, sorted.size() - 1);
	size_t k = 0;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			data[j][i] = sorted[k++];
}
template <typename T>
void Matrix<T>::MatrixSortWithHeap(vector<vector<T>> &data)
{
	Heap<T> heap;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			heap.InsertItem(data[i][j]);
	// QuickSort(sorted, 0, sorted.size() - 1);
	size_t k = 0;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
			data[j][i] = heap.pop()->Item();
}
// You are given a matrix. Elements in matrix can be either 0 or 1. Each row and column of matrix is sorted in ascending order.
// Find number of '0's in the given matrix. Expected complexity is O(log(N)).
template <typename T>
T Matrix<T>::MatrixPatternCount(vector<vector<T>> &data)
{
	T i = data.size() - 1, j = data[0].size() - 1;
	T count = T();
	for (; i >= 0 && j >= 0; i--, j--)
		if (!data[i][j])
		{
			count = (i + 1) * (j + 1);
			break;
		}
	long ii = i, jj = j;
	if (ii < (long)data.size() - 1)
		for (; j >= 0; j--)
			for (i = ii + 1; !data[i][j]; i++)
				count++;
	i = ii;
	if (jj < (long)data[ii].size() - 1)
		for (; i >= 0; i--)
			for (j = jj + 1; !data[i][j]; j++)
				count++;
	return count;
}
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

[1,1] - [3,2]			30 - (-1) - 15 + 2 = 31 - 15 + 2 = 31 - 13 = 18
[0,2] - [3,3]			37 - (16) = 21
*/
template <typename T>
T Matrix<T>::Sum(vector<vector<size_t>> &area)
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
template <typename T>
T Matrix<T>::LargestSumSubmatrix(vector<vector<size_t>> &matrix)
{
	T sum = numeric_limits<T>::min();
	for (size_t r1 = 0; r1 < _matrix.size(); r1++)
		for (size_t r2 = r1; r2 < _matrix.size(); r2++)
			for (size_t c1 = 0; c1 < _matrix[r1].size(); c1++)
				for (size_t c2 = c1; c2 < _matrix[r2].size(); c2++)
				{
					vector<vector<size_t>> area = vector<vector<size_t>>{{r1, c1}, {r2, c2}};
					T tmp = Sum(area);
					if (tmp > sum)
					{
						sum = tmp;
						matrix = area;
					}
				}
	return sum;
}
/* https://leetcode.com/problems/search-a-2d-matrix/
 * 100%
 */
template <typename T>
bool Matrix<T>::SearchMatrix(T target, vector<vector<T>> const &matrix) const
{
	if (matrix.empty())
		return false;
	size_t rlower = 0, rupper = matrix.size() - 1, rmiddle = (rupper) / 2 + (rupper) % 2;
	// First get the row
	for (; rlower < rupper;)
	{
		if (target == matrix[rlower][0] || target == matrix[rmiddle][0] || target == matrix[rupper][0])
			return true;
		else if (target > matrix[rlower][0] && target < matrix[rmiddle][0])
		{
			rupper = rmiddle - 1;
			rmiddle = rlower + (rupper - rlower) / 2 + (rupper - rlower) % 2;
		}
		else if (target > matrix[rmiddle][0] && target < matrix[rupper][0])
		{
			rlower = rmiddle;
			rupper--;
			rmiddle = rlower + (rupper - rlower) / 2 + (rupper - rlower) % 2;
		}
		else if (target > matrix[rupper][0])
		{
			rlower = rupper;
			rmiddle = rupper;
		}
		else if (target < matrix[rlower][0])
			return false;
	}
	if (rlower == rmiddle || rlower == rupper)
	{ // Found the row
		size_t row = rlower;
		if (matrix[row].empty())
			return false;
		size_t clower = 0, cupper = matrix[row].size() - 1, cmiddle = (cupper) / 2 + (cupper) % 2;
		for (; clower <= cupper;)
		{
			if (target == matrix[row][clower] || target == matrix[row][cmiddle] || target == matrix[row][cupper])
				return true;
			else if (target > matrix[row][clower] && target < matrix[row][cmiddle])
			{
				cupper = cmiddle - 1;
				cmiddle = clower + (cupper - clower) / 2 + (cupper - clower) % 2;
			}
			else if (target > matrix[row][cmiddle] && target < matrix[row][cupper])
			{
				clower = cmiddle + 1;
				cmiddle = clower + (cupper - clower) / 2 + (cupper - clower) % 2;
			}
			else if (target > matrix[row][cupper] || target < matrix[row][clower])
				return false;
		}
	}
	return false;
}
template <typename T>
bool Matrix<T>::SearchMatrixRow(vector<vector<T>> const &matrix, T target, size_t row, T start, T end) const
{
	if (start >= 0 && end < (long)matrix[row].size() && start <= end)
	{
		if (matrix[row][start] == target || matrix[row][end] == target)
			return true;
		long middle = start + (end - start) / 2 + (end - start) % 2;
		if (matrix[row][middle] == target)
			return true;
		else if (matrix[row][middle] > target)
			return SearchMatrixRow(matrix, target, row, start, middle - 1);
		else
			return SearchMatrixRow(matrix, target, row, middle + 1, end);
	}
	return false;
}
template <typename T>
bool Matrix<T>::SearchMatrixCol(vector<vector<T>> const &matrix, T target, size_t col, T start, T end) const
{
	if (start >= 0 && end < (long)matrix.size() && start <= end)
	{
		if (matrix[start][col] == target || matrix[end][col] == target)
			return true;
		long middle = start + (end - start) / 2 + (end - start) % 2;
		if (matrix[middle][col] == target)
			return true;
		else if (matrix[middle][col] > target)
			return SearchMatrixCol(matrix, target, col, start, middle - 1);
		else
			return SearchMatrixCol(matrix, target, col, middle + 1, end);
	}
	return false;
}
/* https://leetcode.com/problems/spiral-matrix/
 * 100%
 */
template <typename T>
vector<T> Matrix<T>::MatrixSprialOrder(vector<vector<T>> &matrix)
{
	vector<long> result;
	int row = 0, col = 0;
	int left = 0, right = matrix[0].size() - 1, top = 0, bottom = matrix.size() - 1;
	for (row = top, col = left; top <= bottom && left <= right;)
	{
		// left to right
		for (; col <= right; col++)
			result.push_back(matrix[row][col]);
		top++;
		col--;
		row++;
		if (!(top <= bottom))
			return result;
		// top to bottom
		for (; row <= bottom; row++)
			result.push_back(matrix[row][col]);
		right--;
		bottom--;
		row--;
		col--;
		if (!(left <= right))
			return result;
		// right to left
		for (; col >= left; col--)
			result.push_back(matrix[row][col]);
		col++;
		row--;
		if (!(top <= bottom))
			return result;
		// bottom to top
		for (; row >= top; row--)
			result.push_back(matrix[row][col]);
		left++;
		row++;
		col++;
	}
	return result;
}
/* https://leetcode.com/problems/rotate-image/
 * Rotate a NxN 2D matrix 90 degree clockwise in-place.
 * 100%
 * [1] 2 [3]	7 [2]  1     7 4 1
 * 4   5  6  => 4  5  [6] => 8 5 2
 * 7  8   9     9  8   3     9 6 3
 *
 * [3] 2  1     7 [6] 1
 * 4   5  6     4  5  2
 * 7   8 [9]    9 [8] 3
 *
 * [9] 2 1      7  [8] 1
 * 4   5 6      [4] 5  2
 * [7] 8 3      9   6  3
 */
template <typename T>
void Matrix<T>::RotateMatrix90DegressClockwise(vector<vector<T>> &matrix)
{
	for (long i = 0, j = matrix.size() - 1; i < j; i++, j--)
	{
		for (size_t k = 0; k < (size_t)(j - i); k++)
		{
			swap(matrix[i][i + k], matrix[i + k][j]);
			swap(matrix[i][i + k], matrix[j][j - k]);
			swap(matrix[i][i + k], matrix[j - k][i]);
		}
	}
}
/*
 * https://www.hackerrank.com/challenges/matrix-rotation-algo/problem
 * 100%
 * 1 2  r: 3
 * 3 4

 * 2 4
 * 1 3

 * 4 3
 * 2 1

 * 3 1
 * 4 2

1 2 4 3
r1: 2 4 3 1
r2: 4 3 1 2
r3: 3 1 2 4
 */
template <typename T>
void Matrix<T>::RotateMatrixRTimesAntiClockwise(vector<vector<T>> &matrix, size_t rotation)
{
	if (!matrix.empty())
	{
		long bottom = matrix.size() - 1, right = matrix[0].size() - 1, top = 0, left = 0;
		vector<T> items;
		for (; left < right && top < bottom; top++, left++, bottom--, right--)
		{
			size_t rowCount = right - left + 1, colCount = bottom - top - 1;
			size_t count = 2 * rowCount + 2 * (bottom - top - 1);
			if (!count)
				return;
			items.clear();
			size_t r = rotation % count;
			if (!r)
				continue;
			// Copy top row
			items.insert(items.end(), matrix[top].begin() + left, matrix[top].begin() + left + rowCount);
			// Copy right column
			for (size_t y = top + 1; y < bottom; y++)
				items.push_back(matrix[y][right]);
			// Copy bottom row in reverse order
			items.insert(items.end(), matrix[bottom].rbegin() + left, matrix[bottom].rbegin() + left + rowCount); // left here is offset from the right which is the same both left and right
			// Copy left column in reverse order
			for (long y = bottom - 1; y > top; y--)
				items.push_back(matrix[y][left]);
			ranges::rotate(items, items.begin() + rotation % count);
			// Copy back top row
			ranges::copy(items.begin(), items.begin() + rowCount, matrix[top].begin() + left);
			// Copy back right column
			for (size_t y = top + 1, i = rowCount; y < bottom && i < rowCount + colCount; y++, i++)
				matrix[y][right] = items[i];
			// Copy back bottom row in reverse order
			ranges::copy(items.begin() + rowCount + colCount, items.begin() + 2 * rowCount + colCount, matrix[bottom].rbegin() + left);
			// Copy back left column
			for (long y = bottom - 1, i = 2 * rowCount + colCount; y > top && i < 2 * rowCount + 2 * colCount; y--, i++)
				matrix[y][left] = items[i];
		}
	}
}
/* https://leetcode.com/problems/search-a-2d-matrix-ii/
 * 100%
 */
template <typename T>
bool Matrix<T>::SearchMatrix1(T target, vector<vector<T>> const &matrix) const
{
	if (matrix.empty())
		return false;
	for (size_t row = 0, col = 0;;)
	{
		if ((row < matrix.size() && SearchMatrixRow(matrix, target, row, col, matrix[row < matrix.size() ? row : row - 1].size() - 1)) ||
			(col < matrix[row < matrix.size() ? row : row - 1].size() && SearchMatrixCol(matrix, target, col, row, matrix.size() - 1)))
			return true;
		if (row < matrix.size())
			row++;
		if (col < matrix[row < matrix.size() ? row : row - 1].size())
			col++;
		if (row >= matrix.size() && col >= matrix[row < matrix.size() ? row : row - 1].size())
			break;
	}
	return false;
}
/*
 * https://www.hackerrank.com/challenges/queens-attack-2/problem
 * 100%
 */
template <typename T>
T Matrix<T>::ChessQueensMoveCount(T dimension, T r_q /*[1,dimension]*/, T c_q /*[1,dimension]*/, vector<vector<size_t>> &obstacles)
{
	r_q--;
	c_q--;
	T count = 0, bottom = -1, left = -1, top = dimension, right = dimension, top_left = min(dimension - r_q - 1l, c_q), top_right = min(dimension - r_q - 1l, dimension - c_q - 1l), bottom_left = min(r_q, c_q), bottom_right = min(r_q, dimension - c_q - 1l);
	for (vector<vector<size_t>>::const_iterator it = obstacles.begin(); it != obstacles.end(); it++)
	{
		T r /*y*/ = (*it)[0] - 1, c /*x*/ = (*it)[1] - 1;
		if (c == c_q && r > r_q && r < top) // TOP
			top = r;
		else if (c == c_q && r < r_q && r > bottom) // Bottom
			bottom = r;
		else if (r == r_q && c < c_q && c > left) // Left
			left = c;
		else if (r == r_q && c > c_q && c < right) // Right
			right = c;
		else if (c < c_q && r > r_q && r - r_q == c_q - c && r - r_q < top_left) // Top-left
			top_left = r - r_q - 1;
		else if (c > c_q && r > r_q && r - r_q == c - c_q && r - r_q < top_right) // Top-right
			top_right = r - r_q - 1;
		else if (c < c_q && r < r_q && r_q - r == c_q - c && r_q - r < bottom_left) // Bottom-Left
			bottom_left = r_q - r - 1;
		else if (c > c_q && r < r_q && r_q - r == c - c_q && r_q - r < bottom_right) // Bottom-Right
			bottom_right = r_q - r - 1;
	}
	count += top - r_q - 1;
	count += bottom >= 0 ? r_q - bottom - 1 : r_q;
	count += left >= 0 ? c_q - left - 1 : c_q;
	count += right - c_q - 1;
	count += top_left + top_right + bottom_left + bottom_right;
	return count;
}