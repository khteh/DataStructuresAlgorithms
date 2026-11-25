#include "pch.h"
using namespace std;
TEST(SearchTests, BinarySearchTest)
{
	Search search;
	long pos;
	vector<size_t> source(30);
	long data[12] = { 15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5 };
	/*L				      M			         U*/
	ranges::generate(source.begin(), source.begin() + 10, [i = 0]() mutable
		{ return i++; });
	ranges::generate(source.begin() + 10, source.begin() + 20, [i = 1000]() mutable
		{ return i++; });
	ranges::generate(source.begin() + 20, source.begin() + 30, [i = 2000]() mutable
		{ return i++; });
	ranges::rotate(source, source.begin() + source.size() / 2);
	pos = search.BinarySearch(1000, source);
	ASSERT_GE(pos, 0);
	ASSERT_EQ(1000, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 1000 found at location: " << pos << ", " << source[pos] << endl;

	source.clear();
	source.assign(&data[0], &data[11]);
	pos = search.BinarySearch(20, source);
	ASSERT_EQ(5, pos);
	ASSERT_EQ(20, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 20 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(17, source);
	ASSERT_EQ(2, pos);
	ASSERT_EQ(17, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(0, source);
	ASSERT_EQ(6, pos);
	ASSERT_EQ(0, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(3, source);
	ASSERT_EQ(9, pos);
	ASSERT_EQ(3, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 3 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(11, source);
	ASSERT_LT(pos, 0);

	long data1[20] = { 15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	/*L				             M			          U*/
	source.clear();
	source.assign(&data1[0], &data1[14]);
	pos = search.BinarySearch(0, source);
	ASSERT_EQ(6, pos);
	ASSERT_EQ(0, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(5, source);
	ASSERT_EQ(11, pos);
	ASSERT_EQ(5, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 5 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(17, source);
	ASSERT_EQ(2, pos);
	ASSERT_EQ(17, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(11, source);
	ASSERT_LT(pos, 0);

	long data2[12] = { 4, 8, 9, 9, 9, 10, 12, 13, 1, 2, 2, 3 };
	source.clear();
	source.assign(&data2[0], &data2[11]);
	pos = search.BinarySearch(9, source);
	ASSERT_GT(pos, 0);
	ASSERT_EQ(9, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 9 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(2, source);
	ASSERT_GT(pos, 0);
	ASSERT_EQ(2, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 2 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(12, source);
	ASSERT_EQ(6, pos);
	ASSERT_EQ(12, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 12 found at location: " << pos << ", " << source[pos] << endl;
	pos = search.BinarySearch(0, source);
	ASSERT_LT(pos, 0);
}
TEST(SearchTests, BinarySearchCountTest)
{
	Search search;
	vector<long> ages(50, 20);
	ages.resize(100);
	// 0:49 20, 50: 79 30, 80: 99 50
	ranges::generate(ages.begin() + 50, ages.begin() + 80, [i = 30]() mutable
		{ return i; });
	ranges::generate(ages.begin() + 80, ages.end(), [i = 50]() mutable
		{ return i; });
	int count = search.BinarySearchCountUpper(ages, 18, 0, ages.size() - 1) - search.BinarySearchCountLower(ages, 18, 0, ages.size() - 1);
	ASSERT_EQ(0, count);
	count = search.BinarySearchCountUpper(ages, 20, 0, ages.size() - 1) - search.BinarySearchCountLower(ages, 20, 0, ages.size() - 1) + 1;
	ASSERT_EQ(50, count);
	count = search.BinarySearchCountUpper(ages, 30, 0, ages.size() - 1) - search.BinarySearchCountLower(ages, 30, 0, ages.size() - 1) + 1;
	ASSERT_EQ(30, count);
	count = search.BinarySearchCountUpper(ages, 50, 0, ages.size() - 1) - search.BinarySearchCountLower(ages, 50, 0, ages.size() - 1) + 1;
	ASSERT_EQ(20, count);
}

template <typename T>
class MatrixBinarySearchFixture
{
public:
	void SetUp(bool expected, T toSearch, vector<vector<T>> data)
	{
		_expected = expected;
		_toSearch = toSearch;
		_data = data;
	}

protected:
	Matrix<T> _matrix;
	bool _expected;
	T _toSearch;
	vector<vector<T>> _data;
};

class MatrixBinarySearchTestFixture : public MatrixBinarySearchFixture<long>, public testing::TestWithParam<tuple<bool, long, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		MatrixBinarySearchFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	bool MatrixBinarySearchTest()
	{
		return _matrix.SearchMatrix(_toSearch, _data);
	}
};
TEST_P(MatrixBinarySearchTestFixture, MatrixBinarySearchTests)
{
	ASSERT_EQ(this->_expected, this->MatrixBinarySearchTest());
}
INSTANTIATE_TEST_SUITE_P(
	SearchTests,
	MatrixBinarySearchTestFixture,
	::testing::Values(make_tuple(true, 3, vector<vector<long>>{{1, 3, 5, 7}, { 10, 11, 16, 20 }, { 23, 30, 34, 50 }}),
		make_tuple(false, 13, vector<vector<long>>{{1, 3, 5, 7}, { 10, 11, 16, 20 }, { 23, 30, 34, 50 }}),
		make_tuple(false, 0, vector<vector<long>>{{1}}), make_tuple(true, 1, vector<vector<long>>{{1}}),
		make_tuple(true, 1, vector<vector<long>>{{1}, { 3 }}), make_tuple(false, 0, vector<vector<long>>{{1}, { 3 }})));
class MatrixBinarySearch1TestFixture : public MatrixBinarySearchFixture<long>, public testing::TestWithParam<tuple<bool, long, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		MatrixBinarySearchFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	bool MatrixBinarySearch1Test()
	{
		return _matrix.SearchMatrix1(_toSearch, _data);
	}
};
TEST_P(MatrixBinarySearch1TestFixture, MatrixBinarySearch1Tests)
{
	ASSERT_EQ(this->_expected, this->MatrixBinarySearch1Test());
}
INSTANTIATE_TEST_SUITE_P(
	SearchTests,
	MatrixBinarySearch1TestFixture,
	::testing::Values(make_tuple(true, 1, vector<vector<long>>{{1, 4, 7, 11, 15}, { 2, 5, 8, 12, 19 }, { 3, 6, 9, 16, 22 }, { 10, 13, 14, 17, 24 }, { 18, 21, 23, 26, 30 }}),
		make_tuple(true, 5, vector<vector<long>>{{1, 4, 7, 11, 15}, { 2, 5, 8, 12, 19 }, { 3, 6, 9, 16, 22 }, { 10, 13, 14, 17, 24 }, { 18, 21, 23, 26, 30 }}),
		make_tuple(true, 9, vector<vector<long>>{{1, 4, 7, 11, 15}, { 2, 5, 8, 12, 19 }, { 3, 6, 9, 16, 22 }, { 10, 13, 14, 17, 24 }, { 18, 21, 23, 26, 30 }}),
		make_tuple(true, 17, vector<vector<long>>{{1, 4, 7, 11, 15}, { 2, 5, 8, 12, 19 }, { 3, 6, 9, 16, 22 }, { 10, 13, 14, 17, 24 }, { 18, 21, 23, 26, 30 }}),
		make_tuple(true, 30, vector<vector<long>>{{1, 4, 7, 11, 15}, { 2, 5, 8, 12, 19 }, { 3, 6, 9, 16, 22 }, { 10, 13, 14, 17, 24 }, { 18, 21, 23, 26, 30 }}),
		make_tuple(false, 0, vector<vector<long>>{{1, 4, 7, 11, 15}, { 2, 5, 8, 12, 19 }, { 3, 6, 9, 16, 22 }, { 10, 13, 14, 17, 24 }, { 18, 21, 23, 26, 30 }}),
		make_tuple(true, 2, vector<vector<long>>{{1}, { 2 }, { 3 }, { 4 }, { 5 }}), make_tuple(false, 0, vector<vector<long>>{{1}, { 2 }, { 3 }, { 4 }, { 5 }}),
		make_tuple(true, 1, vector<vector<long>>{{1, 1}}), make_tuple(false, 0, vector<vector<long>>{{1, 1}})));
class VectorBinarySearchTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_toSearch = get<1>(GetParam());
		_range = get<2>(GetParam());
	}
	vector<long> VectorBinarySearchTest()
	{
		return _search.SearchRange(_toSearch, _range);
	}

protected:
	Search _search;
	size_t _toSearch;
	vector<long> _expected;
	vector<size_t> _range;
};
TEST_P(VectorBinarySearchTestFixture, VectorBinarySearchTests)
{
	ASSERT_EQ(this->_expected, this->VectorBinarySearchTest());
}
INSTANTIATE_TEST_SUITE_P(
	VectorBinarySearchTests,
	VectorBinarySearchTestFixture,
	::testing::Values(make_tuple(vector<long>{3, 4}, 8, vector<size_t>{5, 7, 7, 8, 8, 10}), make_tuple(vector<long>{-1, -1}, 0, vector<size_t>{5, 7, 7, 8, 8, 10}),
		make_tuple(vector<long>{0, 0}, 1, vector<size_t>{1}), make_tuple(vector<long>{0, 0}, 1, vector<size_t>{1, 3}),
		make_tuple(vector<long>{1, 1}, 3, vector<size_t>{1, 3}), make_tuple(vector<long>{-1, -1}, 4, vector<size_t>{1, 5}),
		make_tuple(vector<long>{-1, -1}, 2, vector<size_t>{0, 0, 1, 1, 1, 4, 5, 5}), make_tuple(vector<long>{2, 2}, 2, vector<size_t>{0, 1, 2, 3, 4, 4, 4})));
TEST(SearchTests, VectorMinimumBinarySearchTest)
{
	Search search;
	vector<long> b{ 3, 4, 1, 5 };
	ASSERT_EQ(1, search.BinarySearchMinimum(b, 0, b.size() - 1));
}
class BinarySearchStringTestFixture : public testing::TestWithParam<tuple<int, string, vector<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_toSearch = get<1>(GetParam());
		_range = get<2>(GetParam());
	}
	int BinarySearchStringTest()
	{
		ranges::sort(_range);
		return _search.BinarySearch(_toSearch, _range);
	}

protected:
	Search _search;
	string _toSearch;
	int _expected;
	vector<string> _range;
};
TEST_P(BinarySearchStringTestFixture, BinarySearchStringTests)
{
	ASSERT_EQ(this->_expected, this->BinarySearchStringTest());
	ASSERT_EQ(this->_toSearch, this->_range[this->_expected]);
}
INSTANTIATE_TEST_SUITE_P(
	BinarySearchStringTests,
	BinarySearchStringTestFixture,
	::testing::Values(make_tuple(2, "123", vector<string>{"abc", "ABC", "", "123", "789", "xyz", "XYZ", ""}),
		make_tuple(6, "abc", vector<string>{"abc", "ABC", "", "123", "789", "xyz", "XYZ", ""})));
class MinEatingSpeedTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_piles = get<1>(GetParam());
		_hours = get<2>(GetParam());
	}
	size_t MinEatingSpeedTest()
	{
		return _search.MinEatingSpeed(_piles, _hours);
	}

protected:
	Search _search;
	size_t _expected, _hours;
	vector<size_t> _piles;
};
TEST_P(MinEatingSpeedTestFixture, MinEatingSpeedTests)
{
	ASSERT_EQ(this->_expected, this->MinEatingSpeedTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinEatingSpeedTests,
	MinEatingSpeedTestFixture,
	::testing::Values(make_tuple(2, vector<size_t>{2, 2}, 2),
		make_tuple(4, vector<size_t>{3, 6, 7, 11}, 8),
		make_tuple(30, vector<size_t>{30, 11, 23, 4, 20}, 5),
		make_tuple(23, vector<size_t>{30, 11, 23, 4, 20}, 6)));
class MinCapacityToShipWithinDaysTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_weights = get<1>(GetParam());
		_days = get<2>(GetParam());
	}
	size_t MinCapacityToShipWithinDaysTest()
	{
		return _search.MinCapacityToShipWithinDays(_weights, _days);
	}

protected:
	Search _search;
	size_t _expected, _days;
	vector<size_t> _weights;
};
TEST_P(MinCapacityToShipWithinDaysTestFixture, MinCapacityToShipWithinDaysTests)
{
	ASSERT_EQ(this->_expected, this->MinCapacityToShipWithinDaysTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinCapacityToShipWithinDaysTests,
	MinCapacityToShipWithinDaysTestFixture,
	::testing::Values(make_tuple(15, vector<size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5),
		make_tuple(55, vector<size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 1),
		make_tuple(6, vector<size_t>{3, 2, 2, 4, 1, 4}, 3),
		make_tuple(3, vector<size_t>{1, 2, 3, 1, 1}, 4)));
class MinimumLargestSumTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_k = get<2>(GetParam());
	}
	size_t MinimumLargestSumTest()
	{
		return _search.MinimumLargestSum(_data, _k);
	}

protected:
	Search _search;
	size_t _expected, _k;
	vector<size_t> _data;
};
TEST_P(MinimumLargestSumTestFixture, MinimumLargestSumTests)
{
	ASSERT_EQ(this->_expected, this->MinimumLargestSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinimumLargestSumTests,
	MinimumLargestSumTestFixture,
	::testing::Values(make_tuple(18, vector<size_t>{7, 2, 5, 10, 8}, 2),
		make_tuple(9, vector<size_t>{1, 2, 3, 4, 5}, 2),
		make_tuple(6, vector<size_t>{3, 2, 2, 4, 1, 4}, 3),
		make_tuple(0, vector<size_t>{0, 0}, 1),
		make_tuple(4, vector<size_t>{1, 4, 4}, 3),
		make_tuple(3, vector<size_t>{1, 2, 3, 1, 1}, 4)));
class MinDaysToMakeBouquetsTestFixture : public testing::TestWithParam<tuple<long, vector<size_t>, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_m = get<2>(GetParam());
		_k = get<3>(GetParam());
	}
	long MinDaysToMakeBouquetsTest()
	{
		return _search.MinDaysToMakeBouquets(_data, _m, _k);
	}

protected:
	Search _search;
	long _expected;
	size_t _m, _k;
	vector<size_t> _data;
};
TEST_P(MinDaysToMakeBouquetsTestFixture, MinDaysToMakeBouquetsTests)
{
	ASSERT_EQ(this->_expected, this->MinDaysToMakeBouquetsTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinDaysToMakeBouquetsTests,
	MinDaysToMakeBouquetsTestFixture,
	::testing::Values(make_tuple(3, vector<size_t>{1, 10, 3, 10, 2}, 3, 1),
		make_tuple(-1, vector<size_t>{1, 10, 3, 10, 2}, 3, 2),
		make_tuple(12, vector<size_t>{7, 7, 7, 7, 12, 7, 7}, 2, 3)));
class MultiplicationTableKthSmallestNumberTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_m = get<1>(GetParam());
		_n = get<2>(GetParam());
		_k = get<3>(GetParam());
	}
	size_t MultiplicationTableKthSmallestNumberTest()
	{
		return _search.MultiplicationTableKthSmallestNumber(_m, _n, _k);
	}

protected:
	Search _search;
	size_t _expected, _m, _n, _k;
};
TEST_P(MultiplicationTableKthSmallestNumberTestFixture, MultiplicationTableKthSmallestNumberTests)
{
	ASSERT_EQ(this->_expected, this->MultiplicationTableKthSmallestNumberTest());
}
INSTANTIATE_TEST_SUITE_P(
	MultiplicationTableKthSmallestNumberTests,
	MultiplicationTableKthSmallestNumberTestFixture,
	::testing::Values(make_tuple(3, 3, 3, 5),
		make_tuple(6, 2, 3, 6),
		make_tuple(9, 5, 5, 15)));
class SmallestDistancePairTestFixture : public testing::TestWithParam<tuple<long, vector<long>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_k = get<2>(GetParam());
	}
	long SmallestDistancePairTest()
	{
		return _search.SmallestDistancePair(_data, _k);
	}

protected:
	Search _search;
	long _expected;
	size_t _k;
	vector<long> _data;
};
TEST_P(SmallestDistancePairTestFixture, SmallestDistancePairTests)
{
	ASSERT_EQ(this->_expected, this->SmallestDistancePairTest());
}
INSTANTIATE_TEST_SUITE_P(
	SmallestDistancePairTests,
	SmallestDistancePairTestFixture,
	::testing::Values(make_tuple(0, vector<long>{1, 3, 3}, 1),
		make_tuple(0, vector<long>{1, 1, 1}, 2),
		make_tuple(5, vector<long>{1, 6, 1}, 3),
		make_tuple(58, vector<long>{62, 100, 4}, 2),
		make_tuple(2, vector<long>{9, 10, 7, 10, 6, 1, 5, 4, 9, 8}, 18),
		// Negative values: the distances of {-3, 1, 4} are 4, 7 and 3
		make_tuple(3, vector<long>{-3, 1, 4}, 1),
		make_tuple(4, vector<long>{-3, 1, 4}, 2),
		make_tuple(7, vector<long>{-3, 1, 4}, 3),
		make_tuple(0, vector<long>{-5, 2, -5}, 1), // A repeated negative value: distance 0
		make_tuple(7, vector<long>{-5, 2, -5}, 2)));
/*
 * https://leetcode.com/problems/last-day-where-you-can-still-cross/
 * The coordinates are 1-based ints up to row * col <= 2 x 10^4, so long: char (Console used Matrix<char>) only reaches 127
 */
// Every cell, flooded row by row or column by column, so the answer is known
static vector<vector<long>> RowMajorCells(long row, long col)
{
	vector<vector<long>> cells;
	for (long r = 1; r <= row; r++)
		for (long c = 1; c <= col; c++)
			cells.push_back({ r, c });
	return cells;
}
static vector<vector<long>> ColumnMajorCells(long row, long col)
{
	vector<vector<long>> cells;
	for (long c = 1; c <= col; c++)
		for (long r = 1; r <= row; r++)
			cells.push_back({ r, c });
	return cells;
}
class LatestDayToCrossTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_row = get<1>(GetParam());
		_col = get<2>(GetParam());
		_cells = get<3>(GetParam());
	}
	size_t LatestDayToCrossTest()
	{
		return _search.LatestDayToCross(_row, _col, _cells);
	}

protected:
	Search _search;
	size_t _expected, _row, _col;
	vector<vector<long>> _cells;
};
TEST_P(LatestDayToCrossTestFixture, LatestDayToCrossTests)
{
	ASSERT_EQ(this->_expected, this->LatestDayToCrossTest()) << this->_row << " x " << this->_col;
}
// Columns: expected last day, row, col, cells (1-based, in flooding order)
INSTANTIATE_TEST_SUITE_P(
	LatestDayToCrossTests,
	LatestDayToCrossTestFixture,
	::testing::Values(
		make_tuple(2, 2, 2, vector<vector<long>>{{1, 1}, { 2, 1 }, { 1, 2 }, { 2, 2 }}),
		make_tuple(1, 2, 2, vector<vector<long>>{{1, 1}, { 1, 2 }, { 2, 1 }, { 2, 2 }}),
		make_tuple(3, 3, 3, vector<vector<long>>{{1, 2}, { 2, 1 }, { 3, 3 }, { 2, 2 }, { 1, 1 }, { 1, 3 }, { 2, 3 }, { 3, 2 }, { 3, 1 }}),
		make_tuple(3, 6, 2, vector<vector<long>>{{4, 2}, { 6, 2 }, { 2, 1 }, { 4, 1 }, { 6, 1 }, { 3, 1 }, { 2, 2 }, { 3, 2 }, { 1, 1 }, { 5, 1 }, { 5, 2 }, { 1, 2 }}),
		make_tuple(4, 4, 3, vector<vector<long>>{{3, 1}, { 2, 3 }, { 1, 2 }, { 4, 1 }, { 1, 1 }, { 4, 3 }, { 3, 3 }, { 4, 2 }, { 1, 3 }, { 3, 2 }, { 2, 1 }, { 2, 2 }}),
		make_tuple(35, 13, 9, vector<vector<long>>{{12, 6}, { 3, 4 }, { 2, 9 }, { 9, 4 }, { 9, 2 }, { 6, 4 }, { 4, 4 }, { 8, 6 }, { 4, 9 }, { 5, 6 }, { 7, 5 }, { 12, 4 }, { 11, 8 }, { 3, 7 }, { 2, 6 }, { 9, 8 }, { 3, 5 }, { 13, 4 }, { 1, 3 }, { 10, 2 }, { 8, 9 }, { 6, 6 }, { 11, 7 }, { 11, 1 }, { 13, 9 }, { 12, 7 }, { 10, 7 }, { 8, 2 }, { 1, 8 }, { 7, 3 }, { 6, 5 }, { 2, 1 }, { 10, 6 }, { 4, 8 }, { 4, 2 }, { 9, 7 }, { 6, 2 }, { 3, 6 }, { 12, 2 }, { 10, 3 }, { 10, 5 }, { 9, 5 }, { 8, 8 }, { 8, 7 }, { 3, 2 }, { 13, 6 }, { 3, 1 }, { 5, 1 }, { 2, 7 }, { 8, 3 }, { 12, 5 }, { 11, 2 }, { 6, 3 }, { 1, 4 }, { 13, 3 }, { 4, 1 }, { 9, 9 }, { 7, 7 }, { 4, 3 }, { 12, 1 }, { 2, 2 }, { 7, 6 }, { 4, 6 }, { 7, 9 }, { 7, 2 }, { 3, 8 }, { 1, 6 }, { 11, 3 }, { 11, 4 }, { 5, 9 }, { 13, 8 }, { 1, 9 }, { 10, 1 }, { 9, 1 }, { 6, 1 }, { 10, 9 }, { 12, 9 }, { 11, 5 }, { 8, 1 }, { 13, 5 }, { 9, 6 }, { 13, 2 }, { 6, 8 }, { 2, 8 }, { 5, 3 }, { 3, 3 }, { 13, 1 }, { 11, 9 }, { 9, 3 }, { 2, 4 }, { 5, 2 }, { 8, 5 }, { 13, 7 }, { 12, 8 }, { 5, 5 }, { 7, 1 }, { 7, 4 }, { 2, 5 }, { 6, 9 }, { 4, 7 }, { 5, 8 }, { 1, 5 }, { 10, 8 }, { 8, 4 }, { 1, 1 }, { 3, 9 }, { 1, 2 }, { 7, 8 }, { 1, 7 }, { 6, 7 }, { 11, 6 }, { 4, 5 }, { 5, 7 }, { 2, 3 }, { 10, 4 }, { 5, 4 }, { 12, 3 }}),
		// The largest grids LeetCode allows (row * col = 2 x 10^4). Row by row: crossing stops when the whole top row is water, on day col
		make_tuple(9999, 2, 10000, RowMajorCells(2, 10000)),
		make_tuple(1, 10000, 2, RowMajorCells(10000, 2)),
		// Column by column: the last column is the last way across, until its top cell floods on day 100 * 199 + 1
		make_tuple(19900, 100, 200, ColumnMajorCells(100, 200))));
// Day by day: flood one more cell, then BFS from the whole top row
static size_t LatestDayToCrossBruteForce(size_t row, size_t col, vector<vector<long>> const& cells)
{
	vector<vector<bool>> water(row, vector<bool>(col, false));
	for (size_t day = 0;; day++)
	{
		if (day)
			water[cells[day - 1][0] - 1][cells[day - 1][1] - 1] = true;
		vector<vector<bool>> visited(row, vector<bool>(col, false));
		queue<pair<size_t, size_t>> q;
		for (size_t c = 0; c < col; c++)
			if (!water[0][c])
				q.emplace(0, c), visited[0][c] = true;
		bool crossed = false;
		for (; !q.empty() && !crossed; q.pop())
		{
			auto [r, c] = q.front();
			crossed = r == row - 1;
			for (auto [dr, dc] : { pair{ -1, 0 }, pair{ 1, 0 }, pair{ 0, -1 }, pair{ 0, 1 } })
			{
				long nr = (long)r + dr, nc = (long)c + dc;
				if (nr >= 0 && nc >= 0 && nr < (long)row && nc < (long)col && !water[nr][nc] && !visited[nr][nc])
					q.emplace(nr, nc), visited[nr][nc] = true;
			}
		}
		if (!crossed)
			return day - 1;
	}
}
TEST(LatestDayToCrossTests, RandomTest)
{
	mt19937 rng(9);
	Search search;
	for (size_t t = 0; t < 500; t++)
	{
		size_t row = 2 + rng() % 6, col = 2 + rng() % 6;
		vector<vector<long>> cells;
		for (size_t r = 1; r <= row; r++)
			for (size_t c = 1; c <= col; c++)
				cells.push_back({ (long)r, (long)c });
		ranges::shuffle(cells, rng);
		ASSERT_EQ(LatestDayToCrossBruteForce(row, col, cells), search.LatestDayToCross(row, col, cells)) << row << " x " << col;
	}
}
class NthUglyNumberTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
		_a = get<2>(GetParam());
		_b = get<3>(GetParam());
		_c = get<4>(GetParam());
	}
	size_t NthUglyNumberTest()
	{
		return _search.NthUglyNumber(_n, _a, _b, _c);
	}

protected:
	Search _search;
	size_t _expected, _n, _a, _b, _c;
};
TEST_P(NthUglyNumberTestFixture, NthUglyNumberTests)
{
	ASSERT_EQ(this->_expected, this->NthUglyNumberTest());
}
INSTANTIATE_TEST_SUITE_P(
	NthUglyNumberTests,
	NthUglyNumberTestFixture,
	::testing::Values(make_tuple(4, 3, 2, 3, 5),
		make_tuple(6, 4, 2, 3, 4),
		make_tuple(10, 5, 2, 11, 13)));
class SmallestDivisorTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_threshold = get<2>(GetParam());
	}
	size_t SmallestDivisorTest()
	{
		return _search.SmallestDivisor(_data, _threshold);
	}

protected:
	Search _search;
	size_t _expected, _threshold;
	vector<size_t> _data;
};
TEST_P(SmallestDivisorTestFixture, SmallestDivisorTests)
{
	ASSERT_EQ(this->_expected, this->SmallestDivisorTest());
}
INSTANTIATE_TEST_SUITE_P(
	SmallestDivisorTests,
	SmallestDivisorTestFixture,
	::testing::Values(make_tuple(5, vector<size_t>{1, 2, 5, 9}, 6),
		make_tuple(44, vector<size_t>{44, 22, 33, 11, 1}, 5)));

class StringGridPatternSearchTestFixture : public testing::TestWithParam<tuple<bool, vector<string>, vector<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_toSearch = get<1>(GetParam());
		_range = get<2>(GetParam());
	}
	bool StringGridPatternTest()
	{
		return _search.GridSearch(_toSearch, _range);
	}

protected:
	Search _search;
	bool _expected;
	vector<string> _toSearch, _range;
};
TEST_P(StringGridPatternSearchTestFixture, StringGridPatternTests)
{
	ASSERT_EQ(this->_expected, this->StringGridPatternTest());
}
INSTANTIATE_TEST_SUITE_P(
	SearchTests,
	StringGridPatternSearchTestFixture,
	::testing::Values(make_tuple(true, vector<string>{"12", "34"}, vector<string>{"123412", "561212", "123634", "781288"}),
		make_tuple(true, vector<string>{"876543", "111111", "111111"}, vector<string>{"1234567890", "0987654321", "1111111111", "1111111111", "2222222222"})));
class KMPSearchTestFixture : public testing::TestWithParam<tuple<vector<size_t>, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_toSearch = get<2>(GetParam());
	}
	vector<size_t> KMPSearchTest()
	{
		vector<size_t> result;
		_search.KMPSearch(_data, _toSearch, result);
		return result;
	}

protected:
	Search _search;
	vector<size_t> _expected;
	string _data, _toSearch;
};
TEST_P(KMPSearchTestFixture, KMPSearchTests)
{
	ASSERT_EQ(this->_expected, this->KMPSearchTest());
}
INSTANTIATE_TEST_SUITE_P(
	KMPSearchTests,
	KMPSearchTestFixture,
	::testing::Values(make_tuple(vector<size_t>{15}, "ABC ABCDAB ABCDABCDABDE", "ABCDABD"),
		make_tuple(vector<size_t>{6, 13, 17}, "ABC ABCDAB ABCDABCDABDE", "CD"),
		make_tuple(vector<size_t>{11, 12, 13}, "Hello World!!!", "!")));
class FindShortestPathTestFixture : public testing::TestWithParam<tuple<vector<string>, int, int, int, int, int>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		n = get<1>(GetParam());
		i_start = get<2>(GetParam());
		j_start = get<3>(GetParam());
		i_end = get<4>(GetParam());
		j_end = get<5>(GetParam());
	}
	vector<string> FindShortestPathTest()
	{
		return _search.FindShortestPath(n, i_start, j_start, i_end, j_end);
	}

protected:
	Search _search;
	vector<string> _expected;
	int n, i_start, j_start, i_end, j_end;
};
TEST_P(FindShortestPathTestFixture, FindShortestPathTests)
{
	ASSERT_EQ(this->_expected, this->FindShortestPathTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindShortestPathTests,
	FindShortestPathTestFixture,
	::testing::Values(make_tuple(vector<string>{"2", "UR UR"}, 5, 4, 1, 0, 3),
		make_tuple(vector<string>{"4", "UL UL UL L"}, 7, 6, 6, 0, 1),
		make_tuple(vector<string>{"Impossible"}, 6, 5, 1, 0, 5),
		make_tuple(vector<string>{"2", "LR LL"}, 7, 0, 3, 4, 3),
		make_tuple(vector<string>{"49", "R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R LR LR LR LR LR LR LR LR LR LR LR"}, 150, 24, 15, 46, 102),
		make_tuple(vector<string>{"30", "LR LR LR LR LR LR LR LR LR LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL LL"}, 70, 7, 15, 67, 3),
		make_tuple(vector<string>{"45", "LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LR LL LL LL LL LL LL LL LL LL LL LL LL"}, 100, 2, 24, 92, 45)));