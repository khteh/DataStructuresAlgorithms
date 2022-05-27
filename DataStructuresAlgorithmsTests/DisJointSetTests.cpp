#include "pch.h"
using namespace std;
TEST(DisJointSetTests, ConnectedCellsInAGridTest) {
	vector<vector<long>> grid = { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0} };
	ASSERT_EQ(5, ConnectedCellsInAGrid(grid));

	grid = { {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0} };
	ASSERT_EQ(8, ConnectedCellsInAGrid(grid));

	grid = { {1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1} };
	ASSERT_EQ(5, ConnectedCellsInAGrid(grid));

	grid = { {0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0} };
	ASSERT_EQ(15, ConnectedCellsInAGrid(grid));

	grid = { {1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0} };
	ASSERT_EQ(9, ConnectedCellsInAGrid(grid));

	grid = { {1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0} };
	ASSERT_EQ(1, ConnectedCellsInAGrid(grid));
}