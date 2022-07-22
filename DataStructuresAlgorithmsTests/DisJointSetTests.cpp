#include "pch.h"
using namespace std;
TEST(DisJointSetTests, DisJointSetTest)
{
	vector<long> a = {1, 3, 5, 7, 9};
	DisJointSet<long> disjointSet(a);
	disjointSet.Print(a);
	// Test islands
	// assert(disjointSet.Find(0) == 0); C++ map will insert non-existing key silently
	ASSERT_EQ(1, disjointSet.Find(1));
	ASSERT_EQ(3, disjointSet.Find(3));
	ASSERT_EQ(5, disjointSet.Find(5));
	ASSERT_EQ(7, disjointSet.Find(7));
	ASSERT_EQ(9, disjointSet.Find(9));
	// Test all islands of Rank 0
	ASSERT_EQ(0, disjointSet.Rank(1));
	ASSERT_EQ(0, disjointSet.Rank(3));
	ASSERT_EQ(0, disjointSet.Rank(5));
	ASSERT_EQ(0, disjointSet.Rank(7));
	ASSERT_EQ(0, disjointSet.Rank(9));
	ASSERT_NE(disjointSet.Find(1), disjointSet.Find(3));
	ASSERT_NE(disjointSet.Find(3), disjointSet.Find(5));
	ASSERT_NE(disjointSet.Find(5), disjointSet.Find(7));
	ASSERT_NE(disjointSet.Find(7), disjointSet.Find(9));
	ASSERT_EQ(7, disjointSet.Union(3, 7)); // 3,7 root: 7
	ASSERT_NE(disjointSet.Find(1), disjointSet.Find(3));
	ASSERT_NE(disjointSet.Find(3), disjointSet.Find(5));
	ASSERT_NE(disjointSet.Find(5), disjointSet.Find(7));
	ASSERT_NE(disjointSet.Find(7), disjointSet.Find(9));
	ASSERT_EQ(disjointSet.Find(3), disjointSet.Find(7));
	ASSERT_EQ(1, disjointSet.Rank(3));
	ASSERT_EQ(1, disjointSet.Rank(7));
	disjointSet.Print(a);
	// Put smaller ranked item under bigger ranked item if ranks are different
	ASSERT_EQ(7, disjointSet.Union(1, 3));							 // 1, 3, 7 root: 7
	ASSERT_EQ(numeric_limits<long>::min(), disjointSet.Union(1, 7)); // Already joined!
	ASSERT_EQ(1, disjointSet.Rank(1));
	ASSERT_EQ(1, disjointSet.Rank(3));
	ASSERT_EQ(1, disjointSet.Rank(7));
	disjointSet.Print(a);
	ASSERT_EQ(disjointSet.Find(1), disjointSet.Find(3));
	ASSERT_NE(disjointSet.Find(3), disjointSet.Find(5));
	ASSERT_NE(disjointSet.Find(5), disjointSet.Find(7));
	ASSERT_NE(disjointSet.Find(7), disjointSet.Find(9));
	ASSERT_EQ(disjointSet.Find(3), disjointSet.Find(7));
	// assert(disjointSet.Find(2) == 0); C++ map will insert non-existing key silently
	// assert(disjointSet.Find(1) != disjointSet.Find(2)); C++ map will insert non-existing key silently
}
class ConnectedCellsInAGridTestFixture : public testing::TestWithParam<tuple<size_t, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_grid = get<1>(GetParam());
	}
	size_t ConnectedCellsInAGridTest()
	{
		return ConnectedCellsInAGrid(_grid);
	}

protected:
	vector<vector<long>> _grid;
	size_t _expected;
};
TEST_P(ConnectedCellsInAGridTestFixture, ConnectedCellsInAGridTests)
{
	ASSERT_EQ(this->_expected, this->ConnectedCellsInAGridTest());
}
INSTANTIATE_TEST_SUITE_P(
	DisJointSetTests,
	ConnectedCellsInAGridTestFixture,
	::testing::Values(make_tuple(5, vector<vector<long>>{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}}),
					  make_tuple(8, vector<vector<long>>{{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}),
					  make_tuple(5, vector<vector<long>>{{1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1}}),
					  make_tuple(15, vector<vector<long>>{{0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0}}),
					  make_tuple(9, vector<vector<long>>{{1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0}}),
					  make_tuple(1, vector<vector<long>>{{1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0}})));