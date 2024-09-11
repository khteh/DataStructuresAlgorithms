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
size_t Matrix<T>::GridlandMetro(T rows, T cols, vector<vector<T>> const &tracks)
{
	size_t count = 0;
	map<T, vector<pair<T, T>>> occupied;
	for (typename vector<vector<T>>::const_iterator it = tracks.begin(); it != tracks.end(); it++)
	{
		if (occupied.find((*it)[0] - 1) == occupied.end())
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
size_t Matrix<T>::SurfaceArea3D(vector<vector<T>> const &data)
{
	size_t zArea = 0, xArea = 0, yArea = 0;
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
				if (i != 0)
					xArea += abs((long)(data[i][j] - data[i - 1][j]));
			}
			if (i != 0 && i != data.size() - 1)
				xArea += abs((long)(data[i][j] - data[i - 1][j]));
			// Y-Axis : Front/Back views
			if (j == 0) // Start Y-Axis border
				yArea += data[i][j];
			if (j == data[i].size() - 1)
			{ // End Y-Axis border
				yArea += data[i][j];
				if (j != 0)
					yArea += abs((long)(data[i][j] - data[i][j - 1]));
			}
			if (j != 0 && j != data[i].size() - 1)
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
/* https://www.hackerrank.com/challenges/bomber-man/problem
 * 100%
-1	-1	-1	0s	-1	-1	-1	1s (BeforeExplosion)
-1	3	-1		-1	3	-1
-1	-1	-1		-1	-1	-1

5	5	5	2s	 5	-1	5	3s
5	3	5		-1	-1	-1
5	5	5		 5	-1	5

5	7	5	4s	-1	-1	-1	5s
7	7	7		-1	7	-1
5	7	5		-1	-1	-1

9	9	9	6s	9	-1	9	7s: repeat 3s
9	7	9		-1	-1	-1
9	9	9		9	-1	9

9	11	9	8s	-1	-1	-1	9s: repeat 5s
11	11	11		-1	11	-1
9	11	9		-1	-1	-1

13	13	13	10s	13	-1	13
13	11	13		-1	-1	-1	11s: repeat 3s
13	13	13		13	-1	13

-1	-1	-1	-1	-1	-1	-1	0s	-1	-1	-1	-1	-1	-1	-1	1s (BeforeExplosion)
-1	-1	-1	3	-1	3	-1		-1	-1	-1	3	-1	3	-1
-1	-1	-1	-1	3	-1	-1		-1	-1	-1	-1	3	-1	-1
-1	-1	3	-1	-1	-1	-1		-1	-1	3	-1	-1	-1	-1
3	3	-1	-1	-1	3	3		3	3	-1	-1	-1	3	3
3	3	-1	3	-1	-1	-1		3	3	-1	3	-1	-1	-1

5	5	5	5	5	5	5	2s	5	5	5	-1	5	-1	5	3s (AfterExplosion)
5	5	5	3	5	3	5		5	5	-1	-1	-1	-1	-1
5	5	5	5	3	5	5		5	5	-1	-1	-1	-1	5
5	5	3	5	5	5	5		-1	-1	-1	-1	-1	-1	-1
3	3	5	5	5	3	3		-1	-1	-1	-1	-1	-1	-1
3	3	5	3	5	5	5		-1	-1	-1	-1	-1	-1	-1

5	5	5	7	5	7	5	4s	-1	-1	-1	-1	-1	-1	-1	5s
5	5	7	7	7	7	7		-1	-1	-1	7	-1	7	-1
5	5	7	7	7	7	5		-1	-1	-1	7	7	-1	-1
7	7	7	7	7	7	7		-1	-1	7	7	7	7	-1
7	7	7	7	7	7	7		7	7	7	7	7	7	7
7	7	7	7	7	7	7		7	7	7	7	7	7	7

9	9	9	9	9	9	9	6s	9	9	9	-1	9	-1	9	7s (Repeats 3s)
9	9	9	7	9	7	9		9	9	-1	-1	-1	-1	-1
9	9	9	7	7	9	9		9	9	-1	-1	-1	-1	9
9	9	7	7	7	7	9		-1	-1	-1	-1	-1	-1	-1
7	7	7	7	7	7	7		-1	-1	-1	-1	-1	-1	-1
7	7	7	7	7	7	7		-1	-1	-1	-1	-1	-1	-1

9	9	9	11	9	11	9	8s	-1	-1	-1	-1	-1	-1	-1	9s (Repeats 5s)
9	9	11	11	11	11	11		-1	-1	-1	11	-1	11	-1
9	9	11	11	11	11	9		-1	-1	-1	11	11	-1	-1
11	11	11	11	11	11	11		-1	-1	11	11	11	11	-1
11	11	11	11	11	11	11		11	11	11	11	11	11	11
11	11	11	11	11	11	11		11	11	11	11	11	11	11

5: [5 9  13] <= %4 == 1
3: [3 7 11  15] <= %4 == 3
 */
template <typename T>
vector<string> Matrix<T>::BomberMan(size_t n, vector<string> const &grid)
{
	vector<vector<long>> grid1;
	vector<string> result, explosion3s, explosion5s;
	if (n <= 1)
		return grid;
	else if (!(n % 2))
	{
		for (size_t i = 0; i < grid.size(); i++)
			result.push_back(string(grid[i].size(), 'O'));
		return result;
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
					explosion3s.push_back(tmp);
				}
			}
			else if (second == 5)
			{
				for (size_t i = 0; i < grid1.size(); i++)
				{
					string tmp;
					for (size_t j = 0; j < grid1[i].size(); j++)
						tmp.push_back(grid1[i][j] == -1 ? '.' : 'O');
					explosion5s.push_back(tmp);
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
	return n % 4 == 1 ? explosion5s : explosion3s;
}
