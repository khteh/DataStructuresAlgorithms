#include "pch.h"
using namespace std;
TEST(SearchTests, BinarySearchTest)
{
	Search search;
	long pos;
	vector<size_t> source(30);
	long data[12] = {15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5};
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

	long data1[20] = {15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5, 6, 7, 8};
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

	long data2[12] = {4, 8, 9, 9, 9, 10, 12, 13, 1, 2, 2, 3};
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
	::testing::Values(make_tuple(true, 3, vector<vector<long>>{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}}),
					  make_tuple(false, 13, vector<vector<long>>{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}}),
					  make_tuple(false, 0, vector<vector<long>>{{1}}), make_tuple(true, 1, vector<vector<long>>{{1}}),
					  make_tuple(true, 1, vector<vector<long>>{{1}, {3}}), make_tuple(false, 0, vector<vector<long>>{{1}, {3}})));
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
	::testing::Values(make_tuple(true, 1, vector<vector<long>>{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}),
					  make_tuple(true, 5, vector<vector<long>>{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}),
					  make_tuple(true, 9, vector<vector<long>>{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}),
					  make_tuple(true, 17, vector<vector<long>>{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}),
					  make_tuple(true, 30, vector<vector<long>>{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}),
					  make_tuple(false, 0, vector<vector<long>>{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}}),
					  make_tuple(true, 2, vector<vector<long>>{{1}, {2}, {3}, {4}, {5}}), make_tuple(false, 0, vector<vector<long>>{{1}, {2}, {3}, {4}, {5}}),
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
	SearchTests,
	VectorBinarySearchTestFixture,
	::testing::Values(make_tuple(vector<long>{3, 4}, 8, vector<size_t>{5, 7, 7, 8, 8, 10}), make_tuple(vector<long>{-1, -1}, 0, vector<size_t>{5, 7, 7, 8, 8, 10}),
					  make_tuple(vector<long>{0, 0}, 1, vector<size_t>{1}), make_tuple(vector<long>{0, 0}, 1, vector<size_t>{1, 3}),
					  make_tuple(vector<long>{1, 1}, 3, vector<size_t>{1, 3}), make_tuple(vector<long>{-1, -1}, 4, vector<size_t>{1, 5}),
					  make_tuple(vector<long>{-1, -1}, 2, vector<size_t>{0, 0, 1, 1, 1, 4, 5, 5}), make_tuple(vector<long>{2, 2}, 2, vector<size_t>{0, 1, 2, 3, 4, 4, 4})));
TEST(SearchTests, VectorMinimumBinarySearchTest)
{
	Search search;
	vector<long> b{3, 4, 1, 5};
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
	SearchTests,
	BinarySearchStringTestFixture,
	::testing::Values(make_tuple(2, "123", vector<string>{"abc", "ABC", "", "123", "789", "xyz", "XYZ", ""}),
					  make_tuple(6, "abc", vector<string>{"abc", "ABC", "", "123", "789", "xyz", "XYZ", ""})));
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
