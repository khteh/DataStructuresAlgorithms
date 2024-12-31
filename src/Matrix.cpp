#include "stdafx.h"
#include "Matrix.h"
template class Matrix<long>;
template class Matrix<size_t>;
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
					data[i][j] = abs((long)(x - i)) + abs((long)(y - j));
				else if (x == i && y != j)
					data[i][j] = abs((long)(y - j));
				else if (x != i && y == j)
					data[i][j] = abs((long)(x - i));
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
T Matrix<T>::MatrixPatternCount(vector<vector<T>> const &data)
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
vector<T> Matrix<T>::MatrixSprialOrder(vector<vector<T>> const &matrix)
{
	vector<T> result;
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
T Matrix<T>::ChessQueensMoveCount(T dimension, T r_q /*[1,dimension]*/, T c_q /*[1,dimension]*/, vector<vector<size_t>> const &obstacles)
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
/*
 * https://www.hackerrank.com/challenges/gridland-metro/problem
 * 100%
 */
template <typename T>
T Matrix<T>::GridlandMetro(T rows, T cols, vector<vector<T>> const &tracks)
{
	T count = 0;
	map<T, vector<pair<T, T>>> occupied;
	for (typename vector<vector<T>>::const_iterator it = tracks.begin(); it != tracks.end(); it++)
	{
		if (!occupied.count((*it)[0] - 1))
			occupied[(*it)[0] - 1].push_back(pair<T, T>((*it)[1] - 1, (*it)[2] - 1));
		else
		{
			bool found = false;
			T start = (*it)[1] - 1, finish = (*it)[2] - 1;
			for (typename vector<pair<T, T>>::iterator it1 = occupied[(*it)[0] - 1].begin(); !found && it1 != occupied[(*it)[0] - 1].end(); it1++)
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
				occupied[(*it)[0] - 1].push_back(pair<T, T>((*it)[1] - 1, (*it)[2] - 1));
		}
	}
	for (typename map<T, vector<pair<T, T>>>::const_iterator it = occupied.begin(); it != occupied.end(); it++)
	{
		size_t tracklength = 0;
		for (typename vector<pair<T, T>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
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
T Matrix<T>::SurfaceArea3D(vector<vector<T>> const &data)
{
	T zArea = 0, xArea = 0, yArea = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
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
		{
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
		{
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
						result = max(result, 2 * height + 2 * (*it - cols[l]));
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
