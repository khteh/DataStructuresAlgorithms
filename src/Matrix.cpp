#include "pch.h"
#include "Matrix.h"
template class Matrix<char>;
template class Matrix<long>;
template class Matrix<size_t>;
template <typename T>
Matrix<T>::Matrix() {}

template <typename T>
Matrix<T>::Matrix(vector<vector<T>> &grid, T active, T inactive) : _grid(grid), _active(active), _inactive(inactive) {}

/*
* Matrix area sum using bottom-up dynamic programming
*   0	1	2	3
0	1   1   1   1
1	1   1   1   1
2	1   1   1   1
3	1   1   1   1

*   0	1	2	3
0	1   2   3   4
1	2   4   6   8
2	3   6   9   12
3	4   8   12  16

[1,1] - [1,1] : 4 - 2 - 2 + 1 = 1
[1,1] - [2,2] : 9 - 3 - 3 + 1 = 4
[1,1] - [3,2] : 12 - 4 - 3 + 1 = 6
[1,1] - [2,3] : 12 - 3 - 4 + 1 = 6
[1,1] - [3,3] : 16 - 4 - 4 + 1 = 9

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

[1,1] - [1,1] : 11 - 8 - 2 + 2 = 3
[1,1] - [2,2] : 26 - 13 - (-1) + 2 = 16
[1,1] - [3,2] : 30 - 15 - (-1) + 2 = 18
[1,1] - [2,3] : 32 - 13 - 3 + 2 = 18
[1,1] - [3,3] : 37 - 15 - 3 + 2 = 21

https://leetcode.com/problems/range-sum-query-2d-immutable/
https://www.youtube.com/watch?v=PwDqpOMwg6U
*/
template <typename T>
Matrix<T>::Matrix(vector<vector<T>> &matrix)
	: _grid(matrix.size(), vector<T>(matrix.empty() ? 0 : matrix[0].size())) // Defaults to zero initial value
{
	for (size_t i = 0; i < matrix.size(); i++)
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			_grid[i][j] = matrix[i][j];
			if (i > 0)
				_grid[i][j] += _grid[i - 1][j];
			if (j > 0)
				_grid[i][j] += _grid[i][j - 1];
			if (i > 0 && j > 0)
				_grid[i][j] -= _grid[i - 1][j - 1];
		}
}
template <typename T>
void Matrix<T>::Print(vector<vector<T>> const &grid) const
{
	for (size_t i = 0; i < grid.size(); i++)
	{
		ranges::copy(grid[i], ostream_iterator<T>(cout, " "));
		cout << endl;
	}
}
/* -1  0 -1
 * -1 -1 -1
 * -1 -1 -1 x:0, y:1
 *
 * 1 0 1
 * 2 1 2
 * 3 2 3
 */
template <typename T>
void Matrix<T>::MatrixDistance(vector<vector<T>> &data, size_t x, size_t y)
{
	if (x < data.size() && y < data[0].size())
		for (size_t i = 0; i < data.size(); i++)
			for (size_t j = 0; j < data[0].size(); j++)
			{
				if (x != i && y != j)
					data[i][j] = abs((long)(x - i)) + abs((long)(y - j));
				else if (x == i && y != j)
					data[i][j] = abs((long)(y - j));
				else if (x != i && y == j)
					data[i][j] = abs((long)(x - i));
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
size_t Matrix<T>::MatrixPatternCount(vector<vector<char>> const &data)
{
	long i = data.size() - 1, j = data[0].size() - 1, count = 0;
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
	if (_grid.empty() || area.empty() || area.size() < 2 || area[0].size() < 2)
		return 0;
	size_t r1 = area[0][0], c1 = area[0][1], r2 = area[1][0], c2 = area[1][1];
	if (r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0 || r2 < r1 || c2 < c1 || r2 >= _grid.size() || c2 >= _grid[0].size())
		return 0;
	T sum = _grid[r2][c2];
	if (r1 > 0)
		sum -= _grid[r1 - 1][c2];
	if (c1 > 0)
		sum -= _grid[r2][c1 - 1];
	if (r1 > 0 && c1 > 0)
		sum += _grid[r1 - 1][c1 - 1];
	return sum;
}
template <typename T>
T Matrix<T>::LargestSumSubmatrix(vector<vector<size_t>> &matrix)
{
	T sum = numeric_limits<T>::min();
	for (size_t r1 = 0; r1 < _grid.size(); r1++)
		for (size_t r2 = r1; r2 < _grid.size(); r2++)
			for (size_t c1 = 0; c1 < _grid[r1].size(); c1++)
				for (size_t c2 = c1; c2 < _grid[r2].size(); c2++)
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
 * 1 2 3
 * 4 5 6
 * 7 8 9
 */
template <typename T>
vector<T> Matrix<T>::MatrixSprialOrder(vector<vector<T>> const &matrix)
{
	vector<T> result;
	int row = 0, col = 0;
	int left = 0, right = matrix[0].size() - 1, top = 0, bottom = matrix.size() - 1;
	for (row = top, col = left; top <= bottom && left <= right;)
	{
		// left to right: [1 2 3]
		for (; col <= right; col++)
			result.push_back(matrix[row][col]);
		top++; // top: 1
		col--; // col: 2
		row++; // row: 1
		if (top > bottom)
			return result;
		// top to bottom: [3 6 9]
		for (; row <= bottom; row++)
			result.push_back(matrix[row][col]);
		right--;  // right: 1
		bottom--; // bottom: 1
		row--;	  // row: 2
		col--;	  // col: 1
		if (left > right)
			return result;
		// right to left [9 8 7]
		for (; col >= left; col--)
			result.push_back(matrix[row][col]);
		col++; // col: 0
		row--; // row: 1
		if (top > bottom)
			return result;
		// bottom to top [7 4 1]
		for (; row >= top; row--)
			result.push_back(matrix[row][col]);
		left++; // left: 1
		row++;	// row: 0
		col++;	// col: 1
	}
	return result;
}
/* https://leetcode.com/problems/rotate-image/
 * Rotate a NxN 2D matrix 90 degree clockwise in-place.
 * 100%
 * (1) swap(matrix[i][i + k], matrix[i + k][j]):
 * [1] 2 [3]	7 [2]  1     7 4 1
 *  4  5  6  =>[4] 5  [6] => 8 5 2
 *  7 8  9      9 [8]  3     9 6 3
 *
 * (2) swap(matrix[i][i + k], matrix[j][j - k]);
 * [3] 2  1     7 [6] 1
 * 4   5  6     4  5  2
 * 7   8 [9]    9 [8] 3
 *
 * (3) swap(matrix[i][i + k], matrix[j - k][i]);
 * [9] 2 1      7  [8] 1
 * 4   5 6      [4] 5  2
 * [7] 8 3      9   6  3
 */
template <typename T>
void Matrix<T>::RotateMatrix90DegressClockwise(vector<vector<T>> &matrix)
{
	for (long i = 0, j = matrix.size() - 1; i < j; i++, j--)
		for (size_t k = 0; k < (size_t)(j - i); k++)
		{
			swap(matrix[i][i + k], matrix[i + k][j]);
			swap(matrix[i][i + k], matrix[j][j - k]);
			swap(matrix[i][i + k], matrix[j - k][i]);
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
size_t Matrix<T>::ChessQueensMoveCount(size_t dimension, size_t r_q /*[1,dimension]*/, size_t c_q /*[1,dimension]*/, vector<vector<size_t>> const &obstacles)
{
	r_q--;
	c_q--;
	long count = 0, bottom = -1, left = -1, top = dimension, right = dimension, top_left = min<long>(dimension - r_q - 1l, c_q), top_right = min<long>(dimension - r_q - 1l, dimension - c_q - 1l), bottom_left = min<long>(r_q, c_q), bottom_right = min<long>(r_q, dimension - c_q - 1l);
	for (vector<vector<size_t>>::const_iterator it = obstacles.begin(); it != obstacles.end(); it++)
	{
		long r /*y*/ = (*it)[0] - 1, c /*x*/ = (*it)[1] - 1;
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
/*
 * https://leetcode.com/problems/n-queens/description/
 * 100%
 * Fill up queens from row-0 to bottom. In each row, check if the col is safe and recurse.
 */
template <typename T>
void Matrix<T>::ChessQueensPlacements(vector<string> &board, size_t r, vector<vector<string>> &result)
{
	if (r == board.size())
	{
		result.push_back(board);
		return;
	}
	for (size_t c = 0; c < board[r].size(); c++)
	{
		bool isSafe = true;
		// Check if c is safe: no other queens in c. Since this is iterator over columns, there is no need to check the validity of columns.
		for (size_t i = 0; i < r && isSafe; i++)
			if (board[i][c] == 'Q')
				isSafe = false;
		if (isSafe)
		{
			// Check Upper-left diagonal
			for (size_t i = 1; i <= min(r, c) && isSafe; i++)
				if (board[r - i][c - i] == 'Q')
					isSafe = false;
		}
		if (isSafe)
		{
			// Check Upper-right diagonal
			// [0 1 2 3 4]: c:2
			for (size_t i = 1; i <= min(r, board[r].size() - 1 - c) && isSafe; i++)
				if (board[r - i][c + i] == 'Q')
					isSafe = false;
		}
		if (isSafe)
		{
			board[r][c] = 'Q';
			ChessQueensPlacements(board, r + 1, result); // This will recurse until the bottom of a board and return it with proper queen placements.
			board[r][c] = '.';							 // Reset the column for the new board
		}
	}
}
/*
 * https://www.hackerrank.com/challenges/gridland-metro/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::GridlandMetro(size_t rows, size_t cols, vector<vector<size_t>> const &tracks)
{
	size_t count = 0;
	map<size_t, vector<pair<size_t, size_t>>> occupied;
	for (typename vector<vector<size_t>>::const_iterator it = tracks.begin(); it != tracks.end(); it++)
	{
		if (!occupied.count((*it)[0] - 1))
			occupied[(*it)[0] - 1].push_back(pair<T, T>((*it)[1] - 1, (*it)[2] - 1));
		else
		{
			bool found = false;
			size_t start = (*it)[1] - 1, finish = (*it)[2] - 1;
			for (typename vector<pair<size_t, size_t>>::iterator it1 = occupied[(*it)[0] - 1].begin(); !found && it1 != occupied[(*it)[0] - 1].end(); it1++)
			{
				if (start >= it1->first && finish <= it1->second) // subset
					found = true;
				else if (start >= it1->first && start <= it1->second) // extend the front
				{
					found = true;
					it1->second = finish;
				}
				else if (start < it1->first && finish <= it1->second) // extend the back
				{
					found = true;
					it1->first = start;
				}
				else if (start < it1->first && finish > it1->second) // superset
				{
					found = true;
					it1->first = start;
					it1->second = finish;
				}
			}
			if (!found)
				occupied[(*it)[0] - 1].push_back(pair<size_t, size_t>((*it)[1] - 1, (*it)[2] - 1));
		}
	}
	for (typename map<size_t, vector<pair<size_t, size_t>>>::const_iterator it = occupied.begin(); it != occupied.end(); it++)
	{
		size_t tracklength = 0;
		for (typename vector<pair<size_t, size_t>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			tracklength += it1->second - it1->first + 1;
		count += cols - tracklength;
	}
	if (rows > occupied.size())
		count += (rows - occupied.size()) * cols;
	return count;
}
/* https://www.hackerrank.com/challenges/3d-surface-area/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::SurfaceArea3D(vector<vector<size_t>> const &data)
{
	size_t zArea = 0, xArea = 0, yArea = 0;
	for (size_t i = 0; i < data.size(); i++)
		for (size_t j = 0; j < data[i].size(); j++)
		{
			if (data[i][j] > 0)
				zArea++;
			// X-Axis : Side / Left/Right views
			if (i == 0) // Start X-Axis border
				xArea += data[i][j];
			if (i == data.size() - 1)
			{ // End X-Axis border
				xArea += data[i][j];
				if (i)
					xArea += abs((long)(data[i][j] - data[i - 1][j]));
			}
			if (i && i != data.size() - 1)
				xArea += abs((long)(data[i][j] - data[i - 1][j]));
			// Y-Axis : Front/Back views
			if (j == 0) // Start Y-Axis border
				yArea += data[i][j];
			if (j == data[i].size() - 1)
			{ // End Y-Axis border
				yArea += data[i][j];
				if (j)
					yArea += abs((long)(data[i][j] - data[i][j - 1]));
			}
			if (j && j != data[i].size() - 1)
				yArea += abs((long)(data[i][j] - data[i][j - 1]));
		}
	return xArea + yArea + zArea * 2;
}
/* https://www.hackerrank.com/challenges/two-pluses/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::TwoCrosses(vector<string> const &grid)
{
	multimap<size_t, vector<size_t>> crosses;
	// Firstly, record all the crosses with size > 1. A single cell is considered a valid cross
	for (size_t i = 1; i < grid.size(); i++)
		for (size_t j = 1; j < grid[i].size(); j++)
			if (grid[i][j] == 'G')
			{
				size_t up = 0, down = 0, left = 0, right = 0;
				// UP
				for (long k = i - 1; k >= 0 && grid[k][j] == 'G'; k--)
					up++;
				// DOWN
				for (long k = i + 1; k < (long)grid.size() && grid[k][j] == 'G'; k++)
					down++;
				// LEFT
				for (long k = j - 1; k >= 0 && grid[i][k] == 'G'; k--)
					left++;
				// RIGHT
				for (long k = j + 1; k < (long)grid[i].size() && grid[i][k] == 'G'; k++)
					right++;
				size_t size = min(left, right);
				size = min(size, up);
				size = min(size, down);
				for (; size; size--)
					crosses.emplace(size * 4 + 1, vector<size_t>{i, j});
			}
	// If no crosses with size > 1 found, return if there is a 'G' cell in the grid
	if (crosses.empty())
	{
		for (vector<string>::const_iterator it = grid.begin(); it != grid.end(); it++)
			if (it->find("G") != string::npos)
				return 1;
		return 0;
	}
	vector<size_t> crossCentre;
	set<size_t> products;
	size_t product = 0, firstWidth = 0;
	// Go through all the crosses, check for overlap and get the products of the 2 crosses.
	for (multimap<size_t, vector<size_t>>::iterator it1 = crosses.begin(); it1 != crosses.end(); it1++)
	{
		product = it1->first;
		crossCentre = it1->second;
		firstWidth = (it1->first - 1) / 4;
		products.insert(product);
		for (multimap<size_t, vector<size_t>>::iterator it = it1; it != crosses.end(); it++)
			if (it->first > 1)
			{
				size_t x = it->second[1], y = it->second[0];
				size_t width = (it->first - 1) / 4;
				// Above at the same x position
				if (x == crossCentre[1] && y < crossCentre[0] && y + width < crossCentre[0] - firstWidth)
					products.insert(product * it->first);
				// Below at the same x position
				else if (x == crossCentre[1] && y > crossCentre[0] && y - width > crossCentre[0] + firstWidth)
					products.insert(product * it->first);
				// Left at the same y position
				else if (y == crossCentre[0] && x < crossCentre[1] && x + width < crossCentre[1] - firstWidth)
					products.insert(product * it->first);
				// Right at the same y position
				else if (y == crossCentre[0] && x > crossCentre[1] && x - width > crossCentre[1] + firstWidth)
					products.insert(product * it->first);
				// Top left of crossCentre
				else if (x < crossCentre[1] && y < crossCentre[0])
				{
					size_t right = x + width;
					size_t down = y + width;
					size_t top = crossCentre[0] - firstWidth;
					size_t left = crossCentre[1] - firstWidth;
					if ((right < crossCentre[1] || top > y) && (left > x || down < crossCentre[0]))
						products.insert(product * it->first);
				}
				// Bottom right of crossCentre
				else if (x > crossCentre[1] && y > crossCentre[0])
				{
					size_t right = crossCentre[1] + firstWidth;
					size_t down = crossCentre[0] + firstWidth;
					size_t top = y - width;
					size_t left = x - width;
					if ((right < x || top > crossCentre[0]) && (left > crossCentre[1] || down < y))
						products.insert(product * it->first);
				}
				// Top right of crossCentre
				else if (x > crossCentre[1] && y < crossCentre[0])
				{
					size_t right = crossCentre[1] + firstWidth;
					size_t top = crossCentre[0] - firstWidth;
					size_t down = y + width;
					size_t left = x - width;
					if ((left > crossCentre[1] || top > y) && (down < crossCentre[1] || right < x))
						products.insert(product * it->first);
				}
				// Bottom left of crossCentre
				else if (x < crossCentre[1] && y > crossCentre[0])
				{
					size_t left = crossCentre[1] - firstWidth;
					size_t down = crossCentre[0] + firstWidth;
					size_t right = x + width;
					size_t top = y - width;
					if ((top > crossCentre[0] || left > x) && (right < crossCentre[1] || down < y))
						products.insert(product * it->first);
				}
			}
	}
	return *ranges::max_element(products);
}
/*
 * https://www.hackerrank.com/challenges/mr-k-marsh/problem
 100% based on editorial's solution
.	.	.	.
.	.	x	.
.	.	x	.
x	.	.	.

Left:
0	1	2	3
0	1	-1	0
0	1	-1	0
-1	0	1	2

Up:
0	0	0	0
1	1	-1	1
2	2	-1	2
-1	3	0	3

Rows: [0,1]	Height:1
Cols: [0,1,3]
Cols: 0		Cols: 1	Cols: 3
min_left:0	min_left:0	min_left:3
L:0			L:0			L:2
Result: 0	Result: 4	Result:4

Rows: [0,2]	Height:2
Cols: [0,1,3]
Cols: 0		Cols: 1		Cols: 3
min_left:0	min_left:0	min_left:3
L:0			L:0			L:2
Result: 0	Result: 6	Result:6

Rows: [0,3]	Height:3
Cols: [1,3]
Cols: 1		Cols: 3
min_left:1	min_left:1
L:0			L:0
Result: 0	Result: 10

Rows: [1,2]	Height:2
...
========================
.	.	.	.
.	.	x	.
.	.	.	.
x	.	x	.

Left:
0	1	2	3
0	1	-1	0
0	1	2	3
-1	0	-1	0

Up:
0	0	0	0
1	1	-1	1
2	2	0	2
-1	3	-1	3

Rows: [0,1]
Cols: [0,1,3]
Cols: 0		Cols: 1		Cols: 3
min_left:0	min_left:0	min_left:3
L:0			L:0			L:2
Result: 0	Result: 4	Result:4

Rows: [0,2]	Height:2
Cols: [0,1,2,3]
Cols: 0		Cols: 1		Cols: 2		Cols: 3
min_left:0	min_left:0	min_left:0	min_left:0
L:0			L:0			L:0			L:0
Result: 0	Result: 6	Result:8	Result:10

Rows: [0,3]	Height:3
Cols: [1,3]
Cols: 1	Cols: 3
min_left:1	min_left:3
L:0			L:1
Result: 0	Result: 10

Rows: [1,2]	Height:2
...
 */
template <typename T>
size_t Matrix<T>::LargestPerimeter(vector<string> const &grid)
{
	size_t result = 0;
	if (!grid.empty())
	{
		vector<vector<long>> left(grid.size(), vector<long>(grid[0].size(), 0)), up(grid.size(), vector<long>(grid[0].size(), 0));
		/*
		 * pre-calculate the number of continuous points up, down, left and right of each point that does not have a marsh. This can be done in O(N^2) time.
		 */
		for (size_t i = 0; i < grid.size(); i++)
			left[i][0] = grid[i][0] == '.' ? 0 : -1;
		for (size_t i = 0; i < grid[0].size(); i++)
			up[0][i] = grid[0][i] == '.' ? 0 : -1;
		for (size_t r = 0; r < grid.size(); r++)
			for (size_t c = 1; c < grid[r].size(); c++)
				if (grid[r][c] == '.')
					left[r][c] = left[r][c - 1] + 1;
				else
					left[r][c] = -1;
		for (size_t c = 0; c < grid[0].size(); c++)
			for (size_t r = 1; r < grid.size(); r++)
				if (grid[r][c] == '.')
					up[r][c] = up[r - 1][c] + 1;
				else
					up[r][c] = -1;
		/*
		 * Now we can solve by considering pairs of points as upper-left and lower-right to determine if a rectagular fence is possible in that rectangle, but it whould take O(N^4) time.
		 * The best solution is to try row/column pairs, because there are N^2 of them. If we have a pair of rows and the pre-calculated values we can find out which columns will have no marsh between the pair of rows and store them in increasing order of columns in O(N) time resulting in a total O(N^3).
		 * Now we have all columns to consider and we can assume one left_coloum(say l) and a right_coloum(say r) and initialize both with the first column we have stored.
		 * Now increase the right_column in each iteration and if we cannot form a rectangular fence with these two columns, we will increase left_column until a rectangle is possible or both of them are in same column. We store the maximum perimeter.
		 * This will result in a O(N^3) solution and we only need up[][] and left[][] pre-calculations.
		 */
		for (size_t r1 = 0; r1 < grid.size(); r1++)
			for (size_t r2 = r1 + 1; r2 < grid.size(); r2++)
			{
				long height = r2 - r1;
				vector<size_t> cols; // This stores the indices
				for (size_t i = 0; i < grid[r2].size(); i++)
				{
					if (up[r2][i] >= height)
						cols.push_back(i);
				}
				size_t l = 0;
				for (vector<size_t>::const_iterator it = cols.begin(); it != cols.end(); it++)
				{
					long min_left = *it - min(left[r1][*it], left[r2][*it]);
					for (; cols[l] < min_left; l++)
						;
					if (*it > cols[l])
						result = max<size_t>(result, 2 * height + 2 * (*it - cols[l]));
				}
			}
	}
	return result;
}
/* https://www.hackerrank.com/challenges/bomber-man/problem
 * 100%
0s:								1s:
-1	-1	-1	-1	-1	-1	-1		-1	-1	-1	-1	-1	-1	-1
-1	-1	-1	3	-1	3	-1		-1	-1	-1	3	-1	3	-1
-1	-1	-1	-1	3	-1	-1		-1	-1	-1	-1	3	-1	-1
-1	-1	3	-1	-1	-1	-1		-1	-1	3	-1	-1	-1	-1
3	3	-1	-1	-1	3	3		3	3	-1	-1	-1	3	3
3	3	-1	3	-1	-1	-1		3	3	-1	3	-1	-1	-1
2s:								3s:
5	5	5	5	5	5	5		5	5	5	-1	5	-1	5
5	5	5	3	5	3	5		5	5	-1	-1	-1	-1	-1
5	5	5	5	3	5	5		5	5	-1	-1	-1	-1	5
5	5	3	5	5	5	5		-1	-1	-1	-1	-1	-1	-1
3	3	5	5	5	3	3		-1	-1	-1	-1	-1	-1	-1
3	3	5	3	5	5	5		-1	-1	-1	-1	-1	-1	-1
4s:								5s:
5	5	5	7	5	7	5		-1	-1	-1	-1	-1	-1	-1
5	5	7	7	7	7	7		-1	-1	-1	7	-1	7	-1
5	5	7	7	7	7	5		-1	-1	-1	7	7	-1	-1
7	7	7	7	7	7	7		-1	-1	7	7	7	7	-1
7	7	7	7	7	7	7		7	7	7	7	7	7	7
7	7	7	7	7	7	7		7	7	7	7	7	7	7
6s:								7s:
9	9	9	9	9	9	9		9	9	9	-1	9	-1	9	7s (Repeats 3s)
9	9	9	7	9	7	9		9	9	-1	-1	-1	-1	-1
9	9	9	7	7	9	9		9	9	-1	-1	-1	-1	9
9	9	7	7	7	7	9		-1	-1	-1	-1	-1	-1	-1
7	7	7	7	7	7	7		-1	-1	-1	-1	-1	-1	-1
7	7	7	7	7	7	7		-1	-1	-1	-1	-1	-1	-1
8s:								9s:
9	9	9	11	9	11	9		-1	-1	-1	-1	-1	-1	-1	9s (Repeats 5s)
9	9	11	11	11	11	11		-1	-1	-1	11	-1	11	-1
9	9	11	11	11	11	9		-1	-1	-1	11	11	-1	-1
11	11	11	11	11	11	11		-1	-1	11	11	11	11	-1
11	11	11	11	11	11	11		11	11	11	11	11	11	11
11	11	11	11	11	11	11		11	11	11	11	11	11	11

explodeAt5s: [5 9  13] <= %4 == 1
explodeAt3s: [3 7 11  15] <= %4 == 3
 */
template <typename T>
vector<string> Matrix<T>::BomberMan(size_t n, vector<string> const &grid)
{
	vector<vector<long>> grid1;
	vector<string> filled, explodeAt3s, explodeAt5s;
	if (n <= 1)
		return grid;
	else if (!(n % 2))
	{
		for (size_t i = 0; i < grid.size(); i++)
			filled.push_back(string(grid[i].size(), 'O'));
		return filled;
	}
	// Initial state
	for (size_t i = 0; i < grid.size(); i++)
	{
		grid1.push_back(vector<long>(grid[i].size(), -1));
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 'O')
				grid1[i][j] = 3;
		}
	}
	for (size_t second = 2; second <= 5; second++)
	{
		if (second % 2)
		{ // Blow up!
			for (size_t i = 0; i < grid1.size(); i++)
				for (size_t j = 0; j < grid1[i].size(); j++)
				{
					if (grid1[i][j] == second)
					{
						// XXX: Need to check overlapping cells which blow up at the same time
						grid1[i][j] = -1;
						if (i > 0)
							grid1[i - 1][j] = -1;
						if (i < grid1.size() - 1 && grid1[i + 1][j] != second)
							grid1[i + 1][j] = -1;
						if (j > 0)
							grid1[i][j - 1] = -1;
						if (j < grid1[i].size() - 1 && grid1[i][j + 1] != second)
							grid1[i][j + 1] = -1;
					}
				}
			if (second == 3)
			{
				for (size_t i = 0; i < grid1.size(); i++)
				{
					string tmp;
					for (size_t j = 0; j < grid1[i].size(); j++)
						tmp.push_back(grid1[i][j] == -1 ? '.' : 'O');
					explodeAt3s.push_back(tmp);
				}
			}
			else if (second == 5)
			{
				for (size_t i = 0; i < grid1.size(); i++)
				{
					string tmp;
					for (size_t j = 0; j < grid1[i].size(); j++)
						tmp.push_back(grid1[i][j] == -1 ? '.' : 'O');
					explodeAt5s.push_back(tmp);
				}
			}
		}
		else
		{ // Plant bombs
			for (size_t i = 0; i < grid1.size(); i++)
				for (size_t j = 0; j < grid1[i].size(); j++)
				{
					if (grid1[i][j] == -1)
						grid1[i][j] = second + 3;
				}
		}
	}
	return n % 4 == 1 ? explodeAt5s : explodeAt3s;
}
/* https://www.hackerrank.com/challenges/flipping-the-matrix/problem
 * 1 2
 * 3 4
 *
 * 112 42  83 119
 * 56 125  56  49
 * 15  78 101  43
 * 62  98 114 108
 *
 * 100%
 */
template <typename T>
T Matrix<T>::MaxQuadrantSum(vector<vector<T>> const &data)
{
	T sum = 0;
	for (size_t i = 0; i < data.size() / 2; i++)
		for (size_t j = 0; j < data[i].size() / 2; j++)
		{
			T top_left = data[i][j];
			T top_right = data[i][data[i].size() - j - 1];
			T bottom_left = data[data.size() - i - 1][j];
			T bottom_right = data[data.size() - i - 1][data[i].size() - j - 1];
			sum += max(top_left, max(top_right, max(bottom_left, bottom_right)));
		}
	return sum;
}
/* https://www.hackerrank.com/challenges/organizing-containers-of-balls/problem
 * 100%
False:
				sum
	1	4		5
	2	3		5
sum:3	7

True:
				sum
	1	1		2
	1	1		2
sum:2	2

False:
				sum
	0	2		2
	1	1		2
sum:1	3

False:
					sum
	1	3	1		5
	2	1	2		5
	3	3	3		9
sum:6	7	6

True:
					sum
	0	2	1		3
	1	1	1		3
	2	0	0		2
sum:3	3	2

False:			sum
	1		1	2
		1		1
	1	1	1	3
sum:	2	2	2

True:			sum					sum					sum
	1	1		2	=>	2			2	=>	2			2
		1		1			1		1				1	1
	1	1	1	3			2	1	3			3		3
sum:	2	3	1		2	3	1			2	3	1
 */
template <typename T>
bool Matrix<T>::ContainersBallsSwap(vector<vector<T>> const &containers)
{
	vector<T> rowSums, colSums;
	if (!containers.empty())
		colSums.assign(containers[0].size(), 0);
	for (size_t i = 0; i < containers.size(); i++)
	{
		rowSums.push_back(parallel_reduce(blocked_range<T>(0, containers[i].size()), (T)0, [&](tbb::blocked_range<T> const &r, T running_total)
										  {
				for (size_t j = r.begin(); j < r.end(); j++)
					running_total += containers[i][j];
				return running_total; }, std::plus<size_t>()));
		for (size_t j = 0; j < containers[i].size(); j++)
			colSums[j] += containers[i][j];
	}
	ranges::sort(rowSums);
	ranges::sort(colSums);
	return rowSums == colSums;
}
/* Given a 2-dimensional array with arbitrary sizes and contains random positive values, you are required to move from the first element [0][0] to the last
 * element [n][n] using the path which will yield the maximum sum of all the elements traversed. You can only move right and down; NOT left and up.
 * 1 2
 */
template <typename T>
pathResult_t Matrix<T>::FindMaxPath(vector<vector<T>> &grid, size_t r, size_t c)
	requires integral_type<T>
{
	ostringstream oss;
	pathResult_t result;
	if (r < grid.size() && c < grid[r].size())
	{
		if (r == grid.size() - 1 && c == grid[r].size() - 1)
		{
			result.sum = grid[r][c];
			oss << "[" << r << "][" << c << "]";
			result.path = oss.str();
			return result;
		}
		pathResult_t path1 = FindMaxPath(grid, r, c + 1);
		pathResult_t path2 = FindMaxPath(grid, r + 1, c);
		oss << "[" << r << "][" << c << "] " << ((path1.sum >= path2.sum) ? path1.path : path2.path);
		result.sum = grid[r][c] + max(path1.sum, path2.sum);
		result.path = oss.str();
	}
	return result;
}
/* https://leetcode.com/problems/word-search/
 * 100%
 */
template <typename T>
bool Matrix<T>::WordExistsInGrid(vector<vector<char>> &board, string const &word)
{
	for (size_t i = 0; i < board.size(); i++)
		for (size_t j = 0; j < board[i].size(); j++)
			if (WordExistsInGrid(board, word, i, j, 0))
				return true;
	return false;
}
template <typename T>
bool Matrix<T>::WordExistsInGrid(vector<vector<char>> &board, string const &word, long row, long col, size_t offset)
{
	if (row < 0 || col < 0 || row >= (long)board.size() || col >= (long)board[row].size() || offset >= word.size() || word[offset] != board[row][col])
		return false;
	if (offset == word.size() - 1)
		return true;
	board[row][col] ^= 0x80; // "visited" mark
	bool flag = WordExistsInGrid(board, word, row, col + 1, offset + 1) ||
				WordExistsInGrid(board, word, row + 1, col, offset + 1) ||
				WordExistsInGrid(board, word, row, col - 1, offset + 1) ||
				WordExistsInGrid(board, word, row - 1, col, offset + 1);
	board[row][col] ^= 0x80; //
	return flag;
}
/* S: Start; X: Obstacle E: Destination
 * 1 1 1 1 1
 * S 1 X 1 1
 * 1 1 1 1 1
 * X 1 1 E 1
 * 1 1 1 1 X
 *
 * Returns min #steps from [r,c] to dest
 */
template <typename T>
size_t Matrix<T>::FindShortestPath(vector<vector<T>> &grid, size_t r, size_t c, stack<position_t> &result, T dest, T obstacle)
{
	position_t origin(r, c);
	set<position_t> visited;
	map<position_t, position_t> routes; // Key: current Value: parent
	queue<position_t> positions;
	positions.push(origin);
	if (grid.empty())
		return 0;
	if (r >= grid.size() || c >= grid[0].size())
		throw invalid_argument("Start/end indices out of range!");
	if (dest == obstacle)
		throw invalid_argument("Destination and obstacle use the same sign!");
	if (grid[r][c] == dest)
	{
		result.push(origin);
		return result.size();
	}
	while (!positions.empty())
	{
		position_t parent = positions.front();
		positions.pop();
		for (size_t k = 0; k < _steps.size() - 1; k++)
		{
			int r = parent.row + _steps[k], c = parent.col + _steps[k + 1];
			if (r >= 0 && c >= 0 && r < grid.size() && c < grid[r].size())
			{
				position_t current(r, c);
				if (grid[r][c] == dest)
				{ // Reach destination. The first reach is the shortest path
					result.push(current);
					result.push(parent);
					for (position_t pos = parent; pos != origin && routes.count(pos); result.push(pos), pos = routes[pos])
						;
					return result.size();
				}
				else if (grid[r][c] != obstacle && !visited.count(current))
				{ // Obstacle. Cancel this route
				  // Prevent loop
					positions.push(current);
					routes.emplace(current, parent);
					visited.emplace(current);
				}
			}
		}
	}
	return 0;
}
/*
* 0 0 1 0 1
* 0 0 0 0 0
* 0 1 1 1 1
* 0 1 1 0 0
* Start: y:1 x:4 End: y: 0 x: 3=> true

* 0 0 1 1 1
* 0 1 0 0 0
* 1 1 1 1 1
* 0 0 0 0 1
* Start: y:0 x:0 End: y: 2 x: 1  => false

* Returns min #steps from [r,c] to dest, 0 if no path exists
*/
template <typename T>
size_t Matrix<T>::PathExists(vector<vector<T>> const &grid, size_t r, size_t c, size_t y, size_t x, stack<position_t> &result, T obstacle)
{
	position_t origin(r, c), destination(y, x);
	set<position_t> visited;
	map<position_t, position_t> routes; // Key: current Value: parent
	queue<position_t> positions;
	positions.push(origin);
	if (grid.empty())
		return 0;
	if (r >= grid.size() || y >= grid.size() || c >= grid[0].size() || x >= grid[0].size())
		throw invalid_argument("Start/end indices out of range!");
	if (origin == destination)
	{
		result.push(destination);
		return result.size();
	}
	while (!positions.empty())
	{
		position_t parent = positions.front();
		positions.pop();
		for (size_t k = 0; k < _steps.size() - 1; k++)
		{
			int r = parent.row + _steps[k], c = parent.col + _steps[k + 1];
			if (r >= 0 && c >= 0 && r < grid.size() && c < grid[r].size())
			{
				position_t current(r, c);
				if (current == destination)
				{ // Reach destination. The first reach is the shortest path
					result.push(current);
					result.push(parent);
					for (position_t pos = parent; pos != origin && routes.count(pos); result.push(pos), pos = routes[pos])
						;
					return result.size();
				}
				else if (grid[r][c] != obstacle && !visited.count(current))
				{ // Obstacle. Cancel this route
					// Prevent loop
					positions.push(current);
					routes.emplace(current, parent);
					visited.emplace(current);
				}
			}
		}
	}
	return 0;
}
template <typename T>
bool Matrix<T>::TopBottomPathExists(vector<vector<T>> const &grid, size_t c, T obstacle)
{
	position_t origin(0, c);
	set<position_t> visited;
	map<position_t, position_t> routes; // Key: current Value: parent
	queue<position_t> positions;
	positions.push(origin);
	if (grid.empty())
		return false;
	if (c >= grid[0].size())
		return false;
	while (!positions.empty())
	{
		position_t parent = positions.front();
		positions.pop();
		for (size_t k = 0; k < _steps.size() - 1; k++)
		{
			int r = parent.row + _steps[k], c = parent.col + _steps[k + 1];
			if (r >= 0 && c >= 0 && r < grid.size() && c < grid[r].size())
			{
				position_t current(r, c);
				if (r == grid.size() - 1 && grid[r][c] != obstacle)
				{ // Reach destination. The first reach is the shortest path
#if 0
                        result.push(current);
                        result.push(parent);
                        for (position_t pos = parent; pos != origin && routes.count(pos); result.push(pos), pos = routes[pos])
                            ;
                        return result.size();
#endif
					return true;
				}
				else if (grid[r][c] != obstacle && !visited.count(current))
				{ // Obstacle. Cancel this route
					// Prevent loop
					positions.push(current);
					// routes.emplace(current, parent);
					visited.emplace(current);
				}
			}
		}
	}
	return false;
}
/*
 * https://leetcode.com/problems/last-day-where-you-can-still-cross/
 * Time limit exceeded!
 */
template <typename T>
size_t Matrix<T>::LatestDayToCross(size_t row, size_t col, vector<vector<T>> const &cells)
{
	vector<vector<T>> matrix(row, vector<T>(col, '0'));
	size_t days = 0;
	for (; days <= cells.size(); days++)
	{
		if (days)
			matrix[cells[days - 1][0] - 1][cells[days - 1][1] - 1] = '1';
		bool pathExists = false;
		for (size_t i = 0; i < col && !pathExists; i++)
		{
			if (matrix[0][i] != '1')
				pathExists = TopBottomPathExists(matrix, i, '1');
		}
		if (!pathExists)
		{
			Print(matrix);
			return days - 1;
		}
	}
	return days;
}

/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::LargestGridCluster_BFS()
{
	size_t result = 0;
	set<set<string>> clusters; // This is useful to check matching grids
	ostringstream location;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[0].size(); j++)
			if (_grid[i][j] == _active)
			{
				set<string> cluster;
				location.str("");
				location << i << "," << j;
				cluster.emplace(location.str());
				size_t count = 1;
				_grid[i][j] = _inactive;
				queue<pair<size_t, size_t>> todo;
				todo.emplace(i, j);
				for (; !todo.empty();)
				{
					pair<size_t, size_t> cell = todo.front();
					todo.pop();
					for (size_t k = 0; k < _steps.size() - 1; k++)
					{
						int r = cell.first + _steps[k], c = cell.second + _steps[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							location.str("");
							location << r << "," << c;
							cluster.emplace(location.str());
							count++;
							_grid[r][c] = _inactive;
							todo.emplace(r, c);
						}
					}
					for (size_t k = 0; k < _diagonals.size() - 1; k++)
					{
						int r = cell.first + _diagonals[k], c = cell.second + _diagonals[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							location.str("");
							location << r << "," << c;
							cluster.emplace(location.str());
							count++;
							_grid[r][c] = _inactive;
							todo.emplace(r, c);
						}
					}
				}
				result = max(result, count);
				clusters.emplace(cluster);
			}
	cout << clusters.size() << " clusters" << endl;
	size_t max1 = 0;
	for (set<set<string>>::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		cout << "cluster: ";
		ranges::copy(*it, ostream_iterator<string>(cout, " "));
		cout << endl;
		// cout << "Length: " << (*it)->Length() << endl;
		max1 = max(max1, it->size());
	}
	clusters.clear();
	cout << "result: " << result << ", max1: " << max1 << endl;
	assert(result == max1);
	return result;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::LargestGridCluster_DFS()
{
	size_t result = 0;
	set<set<string>> clusters; // This is useful to check matching grids
	ostringstream location;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[0].size(); j++)
			if (_grid[i][j] == _active)
			{
				set<string> cluster;
				result = max(result, DisconnectCellAllDirections(i, j, cluster));
				clusters.emplace(cluster);
			}
	cout << clusters.size() << " clusters" << endl;
	size_t max1 = 0;
	for (set<set<string>>::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		cout << "cluster: ";
		ranges::copy(*it, ostream_iterator<string>(cout, " "));
		cout << endl;
		// cout << "Length: " << (*it)->Length() << endl;
		max1 = max(max1, it->size());
	}
	clusters.clear();
	cout << "result: " << result << ", max1: " << max1 << endl;
	assert(result == max1);
	return result;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 * This is more useful to check matching grids compared to using DisJointSet
 */
template <typename T>
size_t Matrix<T>::LargestGridCluster_LinkedList_BFS()
{
	size_t result = 0;
	ostringstream location;
	set<shared_ptr<LinkedList<string>>> clusters;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[0].size(); j++)
			if (_grid[i][j] == _active)
			{
				location.str("");
				location << i << "," << j;
				shared_ptr<Node<string>> node(make_shared<Node<string>>(location.str())), tail = node;
				size_t count = 1;
				_grid[i][j] = _inactive;
				queue<pair<size_t, size_t>> todo;
				todo.emplace(i, j);
				for (; !todo.empty();)
				{
					pair<size_t, size_t> cell = todo.front();
					todo.pop();
					for (size_t k = 0; k < _steps.size() - 1; k++)
					{
						int r = cell.first + _steps[k], c = cell.second + _steps[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							location.str("");
							location << r << "," << c;
							shared_ptr<Node<string>> n(make_shared<Node<string>>(location.str()));
							tail->SetNext(n);
							tail = n;
							count++;
							_grid[r][c] = _inactive;
							todo.emplace(r, c);
						}
					}
					for (size_t k = 0; k < _diagonals.size() - 1; k++)
					{
						int r = cell.first + _diagonals[k], c = cell.second + _diagonals[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							location.str("");
							location << r << "," << c;
							shared_ptr<Node<string>> n(make_shared<Node<string>>(location.str()));
							tail->SetNext(n);
							tail = n;
							count++;
							_grid[r][c] = _inactive;
							todo.emplace(r, c);
						}
					}
				}
				result = max(result, count);
				clusters.emplace(make_shared<LinkedList<string>>(node));
			}
	cout << clusters.size() << " clusters" << endl;
	size_t max1 = 0;
	for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		vector<string> d;
		(*it)->ToVector(d); // This is useful to find matching grids
		//(*it)->Print();
		cout << "vector: ";
		ranges::copy(d, ostream_iterator<string>(cout, " "));
		cout << endl;
		// cout << "Length: " << (*it)->Length() << endl;
		max1 = max(max1, (*it)->Length());
	}
	clusters.clear();
	cout << "result: " << result << ", max1: " << max1 << endl;
	assert(result == max1);
	return result;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::LargestGridCluster_DisjointSet_BFS()
{
	vector<T> data(_grid.size() * _grid[0].size());
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	DisJointSet<T> disjointSet(data);
	size_t width = _grid[0].size();
	map<T, size_t> counts;
	size_t result = 0, largest = 0;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[0].size(); j++)
			if (_grid[i][j] == _active)
			{
				largest = 1; // This is needed
				size_t count = 1;
				T node = i * width + j + 1; // Node id is 1-based
				T currentRoot = disjointSet.Find(node);
				_grid[i][j] = _inactive;
				queue<pair<size_t, size_t>> todo;
				todo.emplace(i, j);
				for (; !todo.empty();)
				{
					pair<size_t, size_t> cell = todo.front();
					todo.pop();
					for (size_t k = 0; k < _steps.size() - 1; k++)
					{
						int r = cell.first + _steps[k], c = cell.second + _steps[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							count++;
							_grid[r][c] = _inactive;
							T neighbour = r * width + c + 1; // Node id is 1-based
							T root = disjointSet.Union(node, neighbour);
							if (root != numeric_limits<T>::min()) // If it was a new join
							{
								if (root != currentRoot && counts.count(currentRoot))
								{ // Existing disjoint set with more than one element
									counts[root] += counts[currentRoot];
									counts.erase(currentRoot);
								}
								else
								{ // Single-element set
									pair<typename map<T, size_t>::iterator, bool> result = counts.emplace(root, 2);
									if (!result.second)
										counts[root]++;
								}
							}
							todo.emplace(r, c);
						}
					}
					for (size_t k = 0; k < _diagonals.size() - 1; k++)
					{
						int r = cell.first + _diagonals[k], c = cell.second + _diagonals[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							count++;
							_grid[r][c] = _inactive;
							T neighbour = r * width + c + 1; // Node id is 1-based
							T root = disjointSet.Union(node, neighbour);
							if (root != numeric_limits<T>::min())
							{
								if (root != currentRoot && counts.count(currentRoot))
								{ // Existing disjoint set with more than one element
									counts[root] += counts[currentRoot];
									counts.erase(currentRoot);
								}
								else
								{ // Single-element set
									pair<typename map<T, size_t>::iterator, bool> result = counts.emplace(root, 2);
									if (!result.second)
										counts[root]++;
								}
							}
							todo.emplace(r, c);
						}
					}
				}
				result = max(result, count);
			}
	for (typename map<T, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
	{
		// cout << "Length: " << it->second << endl;
		if (it->second > largest)
			largest = it->second;
	}
	assert(result == largest);
	disjointSet.Print(data, _grid[0].size());
	map<T, vector<T>> sets;
	disjointSet.GetSets(data, sets);
	for (typename map<T, vector<T>>::const_iterator it = sets.begin(); it != sets.end(); it++)
	{
		cout << it->first << ": ";
		ranges::copy(it->second, ostream_iterator<T>(cout, " "));
		cout << endl;
	}
	return result;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 * This is more useful to check matching grids compared to using DisJointSet
 */
template <typename T>
size_t Matrix<T>::LargestGridCluster_LinkedList_DFS()
{
	size_t result = 0;
	ostringstream location;
	set<shared_ptr<LinkedList<string>>> clusters;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[0].size(); j++)
			if (_grid[i][j] == _active)
			{
				shared_ptr<Node<string>> node(nullptr);
				result = max(result, DisconnectCellAllDirections_LinkedList(i, j, node));
				shared_ptr<Node<string>> n = node;
				for (; n && n->Previous(); n = n->Previous())
					;
				clusters.emplace(make_shared<LinkedList<string>>(n));
			}
	cout << clusters.size() << " clusters" << endl;
	size_t max1 = 0;
	for (set<shared_ptr<LinkedList<string>>>::iterator it = clusters.begin(); it != clusters.end(); it++)
	{
		vector<string> d;
		(*it)->ToVector(d); // This is useful to find matching grids
		//(*it)->Print();
		cout << "vector: ";
		ranges::copy(d, ostream_iterator<string>(cout, " "));
		cout << endl;
		// cout << "Length: " << (*it)->Length() << endl;
		max1 = max(max1, (*it)->Length());
	}
	clusters.clear();
	cout << "result: " << result << ", max1: " << max1 << endl;
	assert(result == max1);
	return result;
}
/*
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 * 100%
 */
template <typename T>
size_t Matrix<T>::LargestGridCluster_DisjointSet_DFS()
{
	vector<T> data(_grid.size() * _grid[0].size());
	ranges::generate(data, [n = 1]() mutable
					 { return n++; });
	DisJointSet<T> disjointSet(data);
	size_t width = _grid[0].size();
	map<T, size_t> counts;
	size_t result = 0, largest = 0;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[0].size(); j++)
			if (_grid[i][j] == _active)
			{
				largest = 1; // This is needed
				size_t count = 1;
				long node = i * width + j + 1; // Node id is 1-based
				result = max(result, DisconnectCellAllDirections_DisjointSet(node, i, j, disjointSet, counts));
			}
	for (typename map<T, size_t>::iterator it = counts.begin(); it != counts.end(); it++)
	{
		// cout << "Length: " << it->second << endl;
		if (it->second > largest)
			largest = it->second;
	}
	cout << "result: " << result << ", largest: " << largest << endl;
	assert(result == largest);
	disjointSet.Print(data, _grid[0].size());
	map<T, vector<T>> sets;
	disjointSet.GetSets(data, sets);
	for (typename map<T, vector<T>>::const_iterator it = sets.begin(); it != sets.end(); it++)
	{
		cout << it->first << ": ";
		ranges::copy(it->second, ostream_iterator<long>(cout, " "));
		cout << endl;
	}
	return result;
}
/*
 * https://leetcode.com/problems/number-of-islands/
 * 100%
 * Each time when see a '1', increment the counter and then erase all connected '1's using a queue.
 */
template <typename T>
size_t Matrix<T>::GridClusterCountBFS()
{
	size_t clusters = 0;
	vector<int> steps = {0, 1, 0, -1, 0};
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[i].size(); j++)
			if (_grid[i][j] == _active)
			{
				clusters++;
				_grid[i][j] = _inactive;
				queue<pair<size_t, size_t>> todo;
				todo.emplace(i, j);
				for (; !todo.empty();)
				{
					pair<size_t, size_t> cell = todo.front();
					todo.pop();
					for (size_t k = 0; k < _steps.size() - 1; k++)
					{
						int r = cell.first + _steps[k], c = cell.second + _steps[k + 1];
						if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
						{
							_grid[r][c] = _inactive;
							todo.emplace(r, c);
						}
					}
				}
			}
	return clusters;
}
/*
 * https://leetcode.com/problems/number-of-islands/
 * 100%
 * Erase all connected cells using DFS
 */
template <typename T>
size_t Matrix<T>::GridClusterCountDFS()
{
	size_t clusters = 0;
	for (size_t i = 0; i < _grid.size(); i++)
		for (size_t j = 0; j < _grid[i].size(); j++)
			if (_grid[i][j] == _active)
			{
				clusters++;
				DisconnectCell(i, j);
			}
	return clusters;
}
template <typename T>
size_t Matrix<T>::DisconnectCell(size_t r, size_t c)
{
	size_t count = 0;
	if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
	{
		count++;
		_grid[r][c] = _inactive;
		count += DisconnectCell(r - 1, c);
		count += DisconnectCell(r + 1, c);
		count += DisconnectCell(r, c - 1);
		count += DisconnectCell(r, c + 1);
	}
	return count;
}
template <typename T>
size_t Matrix<T>::DisconnectCellAllDirections(size_t r, size_t c, set<string> &cluster)
{
	size_t count = 0;
	ostringstream location;
	if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
	{
		count++;
		_grid[r][c] = _inactive;
		location.str("");
		location << r << "," << c;
		cluster.emplace(location.str());
		count += DisconnectCellAllDirections(r - 1, c, cluster);
		count += DisconnectCellAllDirections(r + 1, c, cluster);
		count += DisconnectCellAllDirections(r, c - 1, cluster);
		count += DisconnectCellAllDirections(r, c + 1, cluster);
		count += DisconnectCellAllDirections(r - 1, c - 1, cluster);
		count += DisconnectCellAllDirections(r - 1, c + 1, cluster);
		count += DisconnectCellAllDirections(r + 1, c - 1, cluster);
		count += DisconnectCellAllDirections(r + -1, c + 1, cluster);
	}
	return count;
}

template <typename T>
size_t Matrix<T>::DisconnectCellAllDirections_LinkedList(size_t r, size_t c, shared_ptr<Node<string>> &node)
{
	size_t count = 0;
	ostringstream location;
	if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
	{
		count++;
		_grid[r][c] = _inactive;
		location.str("");
		location << r << "," << c;
		shared_ptr<Node<string>> n(make_shared<Node<string>>(location.str()));
		if (node)
		{
			node->SetNext(n);
			n->SetPrevious(node);
		}
		node = n;
		count += DisconnectCellAllDirections_LinkedList(r - 1, c, node);
		count += DisconnectCellAllDirections_LinkedList(r + 1, c, node);
		count += DisconnectCellAllDirections_LinkedList(r, c - 1, node);
		count += DisconnectCellAllDirections_LinkedList(r, c + 1, node);
		count += DisconnectCellAllDirections_LinkedList(r - 1, c - 1, node);
		count += DisconnectCellAllDirections_LinkedList(r - 1, c + 1, node);
		count += DisconnectCellAllDirections_LinkedList(r + 1, c - 1, node);
		count += DisconnectCellAllDirections_LinkedList(r + -1, c + 1, node);
	}
	return count;
}
template <typename T>
size_t Matrix<T>::DisconnectCellAllDirections_DisjointSet(T neighbour, size_t r, size_t c, DisJointSet<T> &disjointSet, map<T, size_t> &counts)
{
	size_t count = 0;
	size_t width = _grid[0].size();
	if (r >= 0 && c >= 0 && r < _grid.size() && c < _grid[r].size() && _grid[r][c] == _active)
	{
		count++;
		_grid[r][c] = _inactive;
		T currentRoot = disjointSet.Find(neighbour);
		T node = r * width + c + 1; // Node id is 1-based
		if (node != neighbour)
		{
			T root = disjointSet.Union(node, neighbour);
			if (root != numeric_limits<T>::min())
			{
				if (root != currentRoot && counts.count(currentRoot))
				{ // Existing disjoint set with more than one element
					counts[root] += counts[currentRoot];
					counts.erase(currentRoot);
				}
				else
				{ // Single-element set
					pair<typename map<T, size_t>::iterator, bool> result = counts.emplace(root, 2);
					if (!result.second)
						counts[root]++;
				}
			}
		}
		count += DisconnectCellAllDirections_DisjointSet(node, r - 1, c, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r + 1, c, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r, c - 1, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r, c + 1, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r - 1, c - 1, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r - 1, c + 1, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r + 1, c - 1, disjointSet, counts);
		count += DisconnectCellAllDirections_DisjointSet(node, r + -1, c + 1, disjointSet, counts);
	}
	return count;
}