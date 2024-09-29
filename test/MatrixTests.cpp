#include "pch.h"
using namespace std;
TEST(MatrixTests, FindMaxPathTests)
{
	vector<vector<size_t>> grid;
	grid = {{1, 3, 5}, {2, 4, 6}, {7, 8, 9}};
	pathResult_t pathResult = FindMaxPath(grid, 0, 0);
	ASSERT_EQ(27, pathResult.sum);
}
TEST(MatrixTests, FindShortestPathTests)
{
	vector<vector<char>> maze = {{'1', '1', '1', '1', '1'}, {'S', '1', 'X', '1', '1'}, {'1', '1', '1', '1', '1'}, {'X', '1', '1', 'E', '1'}, {'1', '1', '1', '1', 'X'}};
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
	vector<vector<long>> grid = {{1, 3, 5}, {6, 4, 2}, {7, 9, 8}};
	vector<vector<long>> expected = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
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
	vector<vector<long>> grid = {{1, 3, 5}, {6, 4, 2}, {7, 9, 8}};
	vector<vector<long>> expected = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
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
class MatrixPatternCountTestFixture : public testing::TestWithParam<tuple<long, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long MatrixPatternCountTest()
	{
		return _matrix.MatrixPatternCount(_data);
	}

protected:
	Matrix<long> _matrix;
	vector<vector<long>> _data;
	long _expected;
};
TEST_P(MatrixPatternCountTestFixture, MatrixPatternCountTests)
{
	ASSERT_EQ(this->_expected, this->MatrixPatternCountTest());
}
INSTANTIATE_TEST_SUITE_P(
	MatrixPatternCountTests,
	MatrixPatternCountTestFixture,
	::testing::Values(make_tuple(3l, vector<vector<long>>{{0, 0, 1}, {0, 1, 1}, {1, 1, 1}}),
					  make_tuple(4l, vector<vector<long>>{{0, 0, 1}, {0, 0, 1}, {1, 1, 1}}),
					  make_tuple(6l, vector<vector<long>>{{0, 0, 0, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1}})));

class TwoCrossesChallengeTestFixture : public testing::TestWithParam<tuple<size_t, vector<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t TwoCrossesChallengeTest()
	{
		return _matrix.TwoCrosses(_data);
	}

protected:
	Matrix<size_t> _matrix;
	vector<string> _data;
	size_t _expected;
};
TEST_P(TwoCrossesChallengeTestFixture, TwoCrossesChallengeTests)
{
	ASSERT_EQ(this->_expected, this->TwoCrossesChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
	TwoCrossesChallengeTests,
	TwoCrossesChallengeTestFixture,
	::testing::Values(make_tuple(1, vector<string>{"GGGGGGGGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GBBBGGBGG", "GGGGGGGGG"}),
					  make_tuple(5, vector<string>{"GGGGGGG", "BGBBBBG", "BGBBBBG", "GGGGGGG", "GGGGGGG", "BGBBBBG"}),
					  make_tuple(45, vector<string>{"GBGBGGB", "GBGBGGB", "GBGBGGB", "GGGGGGG", "GGGGGGG", "GBGBGGB", "GBGBGGB"}),
					  make_tuple(81, vector<string>{"GGGGGGGG", "GBGBGGBG", "GBGBGGBG", "GGGGGGGG", "GBGBGGBG", "GGGGGGGG", "GBGBGGBG", "GGGGGGGG"}),
					  make_tuple(45, vector<string>{"GGGGGGGGGG", "GBBBBBBGGG", "GGGGGGGGGG", "GGGGGGGGGG", "GBBBBBBGGG", "GGGGGGGGGG", "GBBBBBBGGG", "GBBBBBBGGG", "GGGGGGGGGG"}),
					  make_tuple(85, vector<string>{"BBBBBGGBGG", "GGGGGGGGGG", "GGGGGGGGGG", "BBBBBGGBGG", "BBBBBGGBGG", "GGGGGGGGGG", "BBBBBGGBGG", "GGGGGGGGGG", "BBBBBGGBGG", "GGGGGGGGGG"}),
					  make_tuple(81, vector<string>{"GGGGGGGGGGGG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GBGGBBBBBBBG", "GGGGGGGGGGGG", "GBGGBBBBBBBG"}),
					  make_tuple(189, vector<string>{"GGGGGGGGGGGG", "GGGGGGGGGGGG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "GGGGGGGGGGGG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "BGBGGGBGBGBG", "GGGGGGGGGGGG", "GGGGGGGGGGGG"}),
					  make_tuple(25, vector<string>{"BGB", "GGG", "BGB", "BGB", "GGG", "BGB"}), make_tuple(25, vector<string>{"BGBBGB", "GGGGGG", "BGBBGB"})));

TEST(MatrixTests, PathExistsTest)
{
	vector<vector<char>> maze = {{0, 0, 1, 0, 1}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 1}, {0, 1, 1, 0, 0}};
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
	maze = {{0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}};
	queue<string> puzzleResult1;
	ASSERT_FALSE(PathExists(maze, 0, 0, 1, 2, puzzleResult1, 1));
	ASSERT_TRUE(puzzleResult.empty());
}
TEST(MatrixTests, WordExistsInGridTest)
{
	vector<vector<char>> maze;
	maze = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
	ASSERT_TRUE(WordExistsInGrid(maze, string("ABCCED")));
	ASSERT_FALSE(WordExistsInGrid(maze, string("ABCB")));
}
class MergeIntervalsTestFixture : public testing::TestWithParam<tuple<vector<vector<long>>, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<vector<long>> MergeIntervalsTest()
	{
		return MergeIntervals(_data);
	}

protected:
	vector<vector<long>> _data;
	vector<vector<long>> _expected;
};
TEST_P(MergeIntervalsTestFixture, MergeIntervalsTests)
{
	ASSERT_EQ(this->_expected, this->MergeIntervalsTest());
}
INSTANTIATE_TEST_SUITE_P(
	MergeIntervalsTests,
	MergeIntervalsTestFixture,
	::testing::Values(make_tuple(vector<vector<long>>{{1, 6}, {8, 10}, {15, 18}}, vector<vector<long>>{{1, 3}, {2, 6}, {8, 10}, {15, 18}}),
					  make_tuple(vector<vector<long>>{{1, 5}}, vector<vector<long>>{{1, 4}, {4, 5}}),
					  make_tuple(vector<vector<long>>{{1, 10}}, vector<vector<long>>{{2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10}})));

class MatrixSpiralOrderTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<long> SpiralOrderTest()
	{
		return _matrix.MatrixSprialOrder(_data);
	}

protected:
	Matrix<long> _matrix;
	vector<vector<long>> _data;
	vector<long> _expected;
};
TEST_P(MatrixSpiralOrderTestFixture, SpiralOrderTests)
{
	ASSERT_EQ(this->_expected, this->SpiralOrderTest());
}
INSTANTIATE_TEST_SUITE_P(
	SpiralOrderTests,
	MatrixSpiralOrderTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 2, 3, 6, 9, 8, 7, 4, 5}, vector<vector<long>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}),
					  make_tuple(vector<long>{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}, vector<vector<long>>{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}),
					  make_tuple(vector<long>{1, 2, 4, 3}, vector<vector<long>>{{1, 2}, {3, 4}})));

TEST(MatrixTests, RotateMatrix90DegressClockwiseTests)
{
	Matrix<long> matrix;
	vector<vector<long>> grid1, grid2;
	grid1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	grid2 = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
	matrix.RotateMatrix90DegressClockwise(grid1);
	ASSERT_EQ(grid1, grid2);
}
TEST(MatrixTests, RotateMatrixRTimesAntiClockwiseTests)
{
	Matrix<long> matrix;
	vector<vector<long>> grid1, grid2;
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1 = {{1}};
	grid2 = {{1}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{}};
	grid2 = {{}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{2, 4}, {1, 3}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{4, 3}, {2, 1}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 2);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{3, 1}, {4, 2}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 3);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{1, 2}, {3, 4}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 0);
	ASSERT_EQ(grid1, grid2);
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 4);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{2, 4}, {1, 3}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 5);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{4, 3}, {2, 1}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 6);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2}, {3, 4}};
	grid2 = {{3, 1}, {4, 2}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 7);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {12, 1, 2, 5}, {11, 4, 3, 6}, {10, 9, 8, 7}};
	grid2 = {{3, 4, 5, 6}, {2, 3, 4, 7}, {1, 2, 1, 8}, {12, 11, 10, 9}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 2);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	grid2 = {{3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 2);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	grid2 = {{2, 3, 4, 8}, {1, 7, 11, 12}, {5, 6, 10, 16}, {9, 13, 14, 15}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 1);
	ASSERT_EQ(grid1, grid2);
	grid1.clear();
	grid2.clear();
	grid1 = {{1, 2, 3, 4}, {7, 8, 9, 10}, {13, 14, 15, 16}, {19, 20, 21, 22}, {25, 26, 27, 28}};
	grid2 = {{28, 27, 26, 25}, {22, 9, 15, 19}, {16, 8, 21, 13}, {10, 14, 20, 7}, {4, 3, 2, 1}};
	matrix.RotateMatrixRTimesAntiClockwise(grid1, 7);
	ASSERT_EQ(grid1, grid2);
}
class SurfaceArea3DTestFixture : public testing::TestWithParam<tuple<size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t SurfaceArea3DTest()
	{
		return _matrix.SurfaceArea3D(_data);
	}

protected:
	Matrix<size_t> _matrix;
	vector<vector<size_t>> _data;
	size_t _expected;
};
TEST_P(SurfaceArea3DTestFixture, SurfaceArea3DTests)
{
	ASSERT_EQ(this->_expected, this->SurfaceArea3DTest());
}
INSTANTIATE_TEST_SUITE_P(
	SurfaceArea3DTests,
	SurfaceArea3DTestFixture,
	::testing::Values(make_tuple(6, vector<vector<size_t>>{{1}}),
					  make_tuple(12, vector<vector<size_t>>{{1, 0, 1}}),
					  make_tuple(60, vector<vector<size_t>>{{1, 3, 4}, {2, 2, 3}, {1, 2, 4}}),
					  make_tuple(90, vector<vector<size_t>>{{1, 2, 3, 4, 5, 5, 4, 3, 2, 1}}),
					  make_tuple(90, vector<vector<size_t>>{{1}, {2}, {3}, {4}, {5}, {5}, {4}, {3}, {2}, {1}}),
					  make_tuple(102, vector<vector<size_t>>{{1, 2, 3, 4, 5, 4, 5, 4, 3, 2, 1}}),
					  make_tuple(102, vector<vector<size_t>>{{1}, {2}, {3}, {4}, {5}, {4}, {5}, {4}, {3}, {2}, {1}}),
					  make_tuple(1482, vector<vector<size_t>>{{51}, {32}, {28}, {49}, {28}, {21}, {98}, {56}, {99}, {77}})));

TEST(MatrixTests, MatrixSumTest)
{
	vector<vector<long>> grid;
	vector<vector<size_t>> ugrid;
	grid = {{2, 0, -3, 4}, {6, 3, 2, -1}, {5, 4, 7, 3}, {2, -6, 8, 1}};
	ugrid = {{1, 1}, {3, 2}};
	Matrix<long> matrix(grid);
	ASSERT_EQ(18, matrix.Sum(ugrid));
	ugrid.clear();
	ugrid = {{0, 2}, {3, 3}};
	ASSERT_EQ(21, matrix.Sum(ugrid));

	grid.clear();
	grid = {{-4, -5}};
	Matrix<long> matrix1(grid);
	ugrid.clear();
	ugrid = {{0, 0}, {0, 0}};
	ASSERT_EQ(-4, matrix1.Sum(ugrid));
	ugrid.clear();
	ugrid = {{0, 0}, {0, 1}};
	ASSERT_EQ(-9, matrix1.Sum(ugrid));
}

TEST(MatrixTests, LargestSumSubmatrixTest)
{
	vector<vector<long>> grid;
	vector<vector<size_t>> ugrid, ugrid1;
	grid = {{2, 0, -3, 4}, {6, 3, 2, -1}, {5, 4, 7, 3}, {2, -6, 8, 1}};
	Matrix<long> matrix(grid);
	ASSERT_EQ(37, matrix.LargestSumSubmatrix(ugrid));
	ASSERT_FALSE(ugrid.empty());
	ugrid1 = {{0, 0}, {3, 3}};
	ASSERT_EQ(ugrid1, ugrid);

	grid.clear();
	grid = {{-4, -5}};
	Matrix<long> matrix1(grid);
	ugrid.clear();
	ugrid1.clear();
	ASSERT_EQ(-4, matrix1.LargestSumSubmatrix(ugrid));
	ASSERT_FALSE(ugrid.empty());
	ugrid1 = {{0, 0}, {0, 0}};
	ASSERT_EQ(ugrid1, ugrid);

	grid.clear();
	grid = {{-1, -2, -3, -4}, {-2, 3, 2, -3}, {-3, 4, 7, -2}, {-4, -3, -2, -1}};
	Matrix<long> matrix2(grid);
	ugrid.clear();
	ugrid1.clear();
	ASSERT_EQ(16, matrix2.LargestSumSubmatrix(ugrid));
	ASSERT_FALSE(ugrid.empty());
	ugrid1 = {{1, 1}, {2, 2}};
	ASSERT_EQ(ugrid1, ugrid);
}
class ChessQueensMoveCountTestFixture : public testing::TestWithParam<tuple<long, long, long, long, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_dimension = get<1>(GetParam());
		_r_q = get<2>(GetParam());
		_c_q = get<3>(GetParam());
		_obstacles = get<4>(GetParam());
	}
	long ChessQueensMoveCountTest()
	{
		return _matrix.ChessQueensMoveCount(_dimension, _r_q, _c_q, _obstacles);
	}

protected:
	Matrix<long> _matrix;
	long _dimension, _r_q, _c_q;
	vector<vector<size_t>> _obstacles;
	size_t _expected;
};
TEST_P(ChessQueensMoveCountTestFixture, ChessQueensMoveCountTests)
{
	ASSERT_EQ(this->_expected, this->ChessQueensMoveCountTest());
}
INSTANTIATE_TEST_SUITE_P(
	ChessQueensMoveCountTests,
	ChessQueensMoveCountTestFixture,
	// ChessQueensMoveCount(T rows, T r_q /*[1,rows]*/, T c_q /*[1,cols]*/, vector<vector<size_t>> &obstacles)
	::testing::Values(make_tuple(9, 4, 4, 4, vector<vector<size_t>>{}),
					  make_tuple(10, 5, 4, 3, vector<vector<size_t>>{{5, 5}, {4, 2}, {2, 3}}),
					  make_tuple(0, 1, 1, 1, vector<vector<size_t>>{}),
					  make_tuple(0, 88587, 20001, 20003, vector<vector<size_t>>{{20001, 20002}, {20001, 20004}, {20000, 20003}, {20002, 20003}, {20000, 20004}, {20000, 20002}, {20002, 20004}, {20002, 20002}, {564, 323}}),
					  make_tuple(308369, 100000, 4187, 5068, vector<vector<size_t>>{})));

class GridlandMetroTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_rows = get<1>(GetParam());
		_cols = get<2>(GetParam());
		_data = get<3>(GetParam());
	}
	size_t GridlandMetroTest()
	{
		return _matrix.GridlandMetro(_rows, _cols, _data);
	}

protected:
	Matrix<size_t> _matrix;
	size_t _expected, _rows, _cols;
	vector<vector<size_t>> _data;
};
TEST_P(GridlandMetroTestFixture, GridlandMetroTests)
{
	ASSERT_EQ(this->_expected, this->GridlandMetroTest());
}
INSTANTIATE_TEST_SUITE_P(
	GridlandMetroTests,
	GridlandMetroTestFixture,
	::testing::Values(make_tuple(9, 4, 4, vector<vector<size_t>>{{2, 2, 3}, {3, 1, 4}, {4, 4, 4}}),
					  make_tuple(0, 1, 5, vector<vector<size_t>>{{1, 1, 2}, {1, 2, 4}, {1, 3, 5}}),
					  make_tuple(11, 3, 7, vector<vector<size_t>>{{1, 1, 3}, {2, 2, 2}, {3, 1, 6}, {3, 6, 6}}),
					  make_tuple(335820405811182700, 693177850, 484465003, vector<vector<size_t>>{
																			   {236503426, 316332186, 461015095},
																			   {325185143, 159242615, 308431802},
																			   {55252986, 91207426, 145729635},
																			   {570145738, 66187476, 391212600},
																			   {371200915, 365371882, 394702624},
																			   {118881009, 192274800, 210407482},
																			   {494441153, 367388414, 454335996},
																			   {679306824, 25218436, 93249072},
																			   {664325323, 205159570, 231255973},
																			   {397092493, 153491684, 180964464},
																			   {481315381, 2248120, 93447775},
																			   {479915594, 29751180, 336039384},
																			   {237043892, 220540564, 426154493},
																			   {350500883, 222092050, 333611680},
																			   {467416230, 12887611, 289492620},
																			   {118881009, 192274800, 199091060},
																			   {55252986, 145729635, 180957024},
																			   {236503426, 461015095, 483469100},
																			   {467416230, 289492620, 406503093},
																			   {664325323, 205159570, 413796563},
																			   {467416230, 12887611, 163385052},
																			   {325185143, 308431802, 378788221},
																			   {679306824, 25218436, 138282970},
																			   {55252986, 145729635, 180435002},
																			   {236503426, 461015095, 465216925},
																			   {397092493, 153491684, 438933079},
																			   {570145738, 66187476, 357191181},
																			   {664325323, 231255973, 378071076},
																			   {325185143, 308431802, 393452446},
																			   {371200915, 394702624, 478996774},
																			   {479915594, 336039384, 347196320},
																			   {494441153, 454335996, 462823117},
																			   {397092493, 153491684, 278739320},
																			   {397092493, 180964464, 420999696},
																			   {237043892, 426154493, 445271380},
																			   {570145738, 391212600, 455384599},
																			   {350500883, 222092050, 480223826},
																			   {237043892, 220540564, 416563766},
																			   {570145738, 66187476, 276585244},
																			   {118881009, 210407482, 391001534},
																			   {494441153, 367388414, 455636020},
																			   {467416230, 289492620, 409024638},
																			   {55252986, 145729635, 151698140},
																			   {479915594, 336039384, 365916020},
																			   {118881009, 192274800, 440912976},
																			   {481315381, 93447775, 210550337},
																		   })));
class BomberManTestFixture : public testing::TestWithParam<tuple<vector<string>, size_t, vector<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_second = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	vector<string> BomberManTest()
	{
		return _matrix.BomberMan(_second, _data);
	}

protected:
	Matrix<size_t> _matrix;
	vector<string> _expected;
	size_t _second;
	vector<string> _data;
};
TEST_P(BomberManTestFixture, BomberManTests)
{
	ASSERT_EQ(this->_expected, this->BomberManTest());
}
INSTANTIATE_TEST_SUITE_P(
	BomberManTests,
	BomberManTestFixture,
	::testing::Values(make_tuple(vector<string>{"O.O", "...", "O.O"}, 3, vector<string>{"...", ".O.", "..."}), make_tuple(vector<string>{"OOO.OOO", "OO...OO", "OOO...O", "..OO.OO", "...OOOO", "...OOOO"}, 3, vector<string>{".......", "...O...", "....O..", ".......", "OO.....", "OO....."}), make_tuple(vector<string>{".......", "...O.O.", "...OO..", "..OOOO.", "OOOOOOO", "OOOOOOO"}, 5, vector<string>{".......", "...O.O.", "....O..", "..O....", "OO...OO", "OO.O..."}),
					  make_tuple(vector<string>{"OOOOO........OOOO........OOOOOOOOOO...O.....OOO...OOOOOOOOOOO...OOOOOOOOOOOOOOOOOOOOOOOOO....O...O....O...OOOOOOO....OOOOOOO.....O.....OOOOOOO......OOO.....OOO....OO....OO....OOO...OOOOO....OOOOO...O"}, 181054341, vector<string>{"O..OO........O..O........OO.O.OO.OO...O.....OOO...OO.O..OOOOO...O.O..O..O.O..OOO..O..O..O....O...O....O...O..O..O....O.O.O.O.....O.....OOOO..O......O.O.....OOO....OO....OO....O.O...O..OO....OO..O...O"}),
					  make_tuple(vector<string>{".........O.........OOOOOO.........OOO..........O.....OO.......OO...O...OO..........OOO........O...OO......OOOOOOOOO.............O........OOOO...OOOOOO...O...OO........OO...OOOOO........OOOOOOOO....."}, 329973043, vector<string>{"OOOO.O.O...OOO.O.O........O.OOO.O.....OO..O..O...OOO....O.OOO....O...O....O..O.O.O.....OOOO.O...O....OO.O...........O.O..O.O..O...OO.OOO......O........O...O....O.O..O....O.......OOOO.O..........OO.O"})));
class MaxQuadrantSumTestFixture : public testing::TestWithParam<tuple<size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t MaxQuadrantSumTest()
	{
		return _matrix.MaxQuadrantSum(_data);
	}

protected:
	Matrix<size_t> _matrix;
	size_t _expected;
	vector<vector<size_t>> _data;
};
TEST_P(MaxQuadrantSumTestFixture, MaxQuadrantSumTests)
{
	ASSERT_EQ(this->_expected, this->MaxQuadrantSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxQuadrantSumTests,
	MaxQuadrantSumTestFixture,
	::testing::Values(make_tuple(4, vector<vector<size_t>>{{1, 2}, {3, 4}}), make_tuple(414, vector<vector<size_t>>{{112, 42, 83, 119}, {56, 125, 56, 49}, {15, 78, 101, 43}, {62, 98, 114, 108}}), make_tuple(12781, vector<vector<size_t>>{{517, 37, 380, 3727}, {3049, 1181, 2690, 1587}, {3227, 3500, 2665, 383}, {4041, 2013, 384, 965}})));