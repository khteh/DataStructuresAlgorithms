#include "pch.h"
using namespace std;
TEST(MatrixTests, FindMaxPathTests) {
	vector<vector<size_t>> grid;
	grid = { {1, 3, 5}, {2, 4, 6}, {7, 8, 9} };
	pathResult_t pathResult = FindMaxPath(grid, 0, 0);
	ASSERT_EQ(27, pathResult.sum);
}
TEST(MatrixTests, FindShortestPathTests)
{
	vector<vector<char>> maze = { {'1', '1', '1', '1', '1'}, {'S', '1', 'X', '1', '1'}, {'1', '1', '1', '1', '1'}, {'X', '1', '1', 'E', '1'}, {'1', '1', '1', '1', 'X'} };
	cout << "maze (" << maze.size() << "): " << endl;
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
	queue<string> mazeResult;
	ASSERT_TRUE(FindShortestPath(maze, 1, 0, mazeResult, 'E', 'X'));
	ASSERT_FALSE(mazeResult.empty());
	cout << "Shortest path: ";
	while (!mazeResult.empty())
	{
		string line = mazeResult.front();
		mazeResult.pop();
		cout << line << " ";
	}
	cout << endl;
}
TEST(MatrixTests, MatrixSortTest)
{
	Matrix<long> matrix;
	vector<vector<long>> grid = { {1, 3, 5}, {6, 4, 2}, {7, 9, 8} };
	vector<vector<long>> expected = { {1, 4, 7}, {2, 5, 8}, {3, 6, 9} };
	matrix.MatrixSort(grid);
	ASSERT_EQ(expected, grid);
	cout << "MatrixSort: " << endl;
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}
TEST(MatrixTests, MatrixSortWithHeapTest)
{
	Matrix<long> matrix;
	vector<vector<long>> grid = { {1, 3, 5}, {6, 4, 2}, {7, 9, 8} };
	vector<vector<long>> expected = { {1, 4, 7}, {2, 5, 8}, {3, 6, 9} };
	matrix.MatrixSortWithHeap(grid);
	ASSERT_EQ(expected, grid);
	cout << "MatrixSortWithHeap: " << endl;
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}
TEST(MatrixTests, MatrixPatternCountTest)
{
	Matrix<long> matrix;
	vector<vector<long>> grid = { {0, 0, 1}, {0, 1, 1}, {1, 1, 1} };
	ASSERT_EQ(3, matrix.MatrixPatternCount(grid));

	grid = { {0, 0, 1}, {0, 0, 1}, {1, 1, 1} };
	ASSERT_EQ(4, matrix.MatrixPatternCount(grid));

	grid = { {0, 0, 0, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1} };
	ASSERT_EQ(6, matrix.MatrixPatternCount(grid));
}
TEST(MatrixTests, PathExistsTest)
{
	vector<vector<char>> maze = { {0, 0, 1, 0, 1}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 1}, {0, 1, 1, 0, 0} };
	queue<string> puzzleResult;
	ASSERT_TRUE(PathExists(maze, 1, 4, 0, 3, puzzleResult, 1));
	ASSERT_FALSE(puzzleResult.empty());
	cout << "Puzzle path: ";
	while (!puzzleResult.empty())
	{
		string line = puzzleResult.front();
		puzzleResult.pop();
		cout << line << " ";
	}
	cout << endl;
	maze = { {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1} };
	queue<string> puzzleResult1;
	ASSERT_FALSE(PathExists(maze, 0, 0, 1, 2, puzzleResult1, 1));
	ASSERT_TRUE(puzzleResult.empty());
}
TEST(MatrixTests, WordExistsInGridTest)
{
	vector<vector<char>> maze;
	maze = { {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'} };
	ASSERT_TRUE(WordExistsInGrid(maze, string("ABCCED")));
	ASSERT_FALSE(WordExistsInGrid(maze, string("ABCB")));
}
TEST(MatrixTests, MergeIntervalsTest)
{
	vector<vector<long>> grid, grid1;
	grid = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };
	grid1 = MergeIntervals(grid);
	grid = { {1, 6}, {8, 10}, {15, 18} };
	ASSERT_EQ(3, grid1.size());
	ASSERT_EQ(grid, grid1);
	grid.clear();
	grid = { {1, 4}, {4, 5} };
	grid1 = MergeIntervals(grid);
	ASSERT_EQ(1, grid1.size());
	grid = { {1, 5} };
	ASSERT_EQ(grid, grid1);
	grid.clear();
	grid = { {2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10} };
	grid1 = MergeIntervals(grid);
	ASSERT_EQ(1, grid1.size());
	grid = { {1, 10} };
	ASSERT_EQ(grid, grid1);
}
TEST(MatrixTests, SpiralOrderTests) {
	Matrix<long> matrix;
	vector<vector<long>> grid1;
	vector<long> a;
	grid1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	a.clear();
	a = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
	ASSERT_EQ(a, matrix.MatrixSprialOrder(grid1));
	grid1.clear();
	grid1 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	a.clear();
	a = { 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7 };
	ASSERT_EQ(a, matrix.MatrixSprialOrder(grid1));
	grid1.clear();
	grid1 = { {1, 2}, {3, 4} };
	a.clear();
	a = { 1, 2, 4, 3 };
	ASSERT_EQ(a, matrix.MatrixSprialOrder(grid1));
}
TEST(MatrixTests, RotateMatrix90DegressClockwiseTests) {
	Matrix<long> matrix;
	vector<vector<long>> grid1, grid2;
	grid1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	grid2 = { {7, 4, 1}, {8, 5, 2}, {9, 6, 3} };
	matrix.RotateMatrix90DegressClockwise(grid1);
	ASSERT_EQ(grid1, grid2);
}
TEST(MatrixTests, RotateMatrixRTimesAntiClockwiseTests) {
	Matrix<long> matrix;
	vector<vector<long>> grid1, grid2;
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1 = { {1} };
	grid2 = { {1} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {} };
	grid2 = { {} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {2, 4}, {1, 3} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {4, 3}, {2, 1} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 2);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {3, 1}, {4, 2} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 3);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {1, 2}, {3, 4} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 0);
	ASSERT_EQ(grid1, grid2);
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 4);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {2, 4}, {1, 3} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 5);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {4, 3}, {2, 1} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 6);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2}, {3, 4} };
	grid2 = { {3, 1}, {4, 2} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 7);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2, 3, 4}, {12, 1, 2, 5}, {11, 4, 3, 6}, {10, 9, 8, 7} };
	grid2 = { {3, 4, 5, 6}, {2, 3, 4, 7}, {1, 2, 1, 8}, {12, 11, 10, 9} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 2);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
	grid2 = { {3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 2);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
	grid2 = { {2, 3, 4, 8}, {1, 7, 11, 12}, {5, 6, 10, 16}, {9, 13, 14, 15} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = { {1, 2, 3, 4}, {7, 8, 9, 10}, {13, 14, 15, 16}, {19, 20, 21, 22}, {25, 26, 27, 28} };
	grid2 = { {28, 27, 26, 25}, {22, 9, 15, 19}, {16, 8, 21, 13}, {10, 14, 20, 7}, {4, 3, 2, 1} };
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 7);
	ASSERT_EQ(grid1, grid2);
}
TEST(MatrixTests, SurfaceArea3DTest)
{
	vector<vector<long>> grid;
	grid.resize(1);
	grid[0].push_back(1);
	ASSERT_EQ(6, SurfaceArea3D(grid));
	grid.clear();
	grid.resize(1);
	grid[0] = { 1, 0, 1 };
	ASSERT_EQ(12, SurfaceArea3D(grid));

	grid = { {1, 3, 4}, {2, 2, 3}, {1, 2, 4} };
	ASSERT_EQ(60, SurfaceArea3D(grid));

	grid.clear();
	grid.resize(1);
	grid[0] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	ASSERT_EQ(90, SurfaceArea3D(grid));

	grid = { {1}, {2}, {3}, {4}, {5}, {5}, {4}, {3}, {2}, {1} };
	ASSERT_EQ(90, SurfaceArea3D(grid));

	grid.clear();
	grid.resize(1);
	grid[0] = { 1, 2, 3, 4, 5, 4, 5, 4, 3, 2, 1 };
	ASSERT_EQ(102, SurfaceArea3D(grid));

	grid = { {1}, {2}, {3}, {4}, {5}, {4}, {5}, {4}, {3}, {2}, {1} };
	ASSERT_EQ(102, SurfaceArea3D(grid));

	grid = { {51}, {32}, {28}, {49}, {28}, {21}, {98}, {56}, {99}, {77} };
	ASSERT_EQ(1482, SurfaceArea3D(grid));
}
TEST(MatrixTests, MatrixSumTest)
{
	vector<vector<long>> grid;
	vector<vector<size_t>> ugrid;
	grid = { {2, 0, -3, 4}, {6, 3, 2, -1}, {5, 4, 7, 3}, {2, -6, 8, 1} };
	ugrid = { {1, 1}, {3, 2} };
	Matrix<long> matrix(grid);
	ASSERT_EQ(18, matrix.Sum(ugrid));
	ugrid.clear();
	ugrid = { {0, 2}, {3, 3} };
	ASSERT_EQ(21, matrix.Sum(ugrid));

	grid.clear();
	grid = { {-4, -5} };
	Matrix<long> matrix1(grid);
	ugrid.clear();
	ugrid = { {0, 0}, {0, 0} };
	ASSERT_EQ(-4, matrix1.Sum(ugrid));
	ugrid.clear();
	ugrid = { {0, 0}, {0, 1} };
	ASSERT_EQ(-9, matrix1.Sum(ugrid));
}
TEST(MatrixTests, LargestSumSubmatrixTest)
{
	vector<vector<long>> grid;
	vector<vector<size_t>> ugrid, ugrid1;
	grid = { {2, 0, -3, 4}, {6, 3, 2, -1}, {5, 4, 7, 3}, {2, -6, 8, 1} };
	Matrix<long> matrix(grid);
	ASSERT_EQ(37, matrix.LargestSumSubmatrix(ugrid));
	ASSERT_FALSE(ugrid.empty());
	ugrid1 = { {0,0}, {3,3} };
	ASSERT_EQ(ugrid1, ugrid);

	grid.clear();
	grid = { {-4, -5} };
	Matrix<long> matrix1(grid);
	ugrid.clear();
	ugrid1.clear();
	ASSERT_EQ(-4, matrix1.LargestSumSubmatrix(ugrid));
	ASSERT_FALSE(ugrid.empty());
	ugrid1 = { {0,0}, {0,0} };
	ASSERT_EQ(ugrid1, ugrid);

	grid.clear();
	grid = { {-1, -2, -3, -4}, {-2, 3, 2, -3}, {-3, 4, 7, -2}, {-4, -3, -2, -1} };
	Matrix<long> matrix2(grid);
	ugrid.clear();
	ugrid1.clear();
	ASSERT_EQ(16, matrix2.LargestSumSubmatrix(ugrid));
	ASSERT_FALSE(ugrid.empty());
	ugrid1 = { {1, 1}, {2, 2} };
	ASSERT_EQ(ugrid1, ugrid);

}