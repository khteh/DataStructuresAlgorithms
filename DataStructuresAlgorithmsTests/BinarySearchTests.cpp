#include "pch.h"
using namespace std;
TEST(BinarySearchTests, BinarySearchTest) {
	int pos;
	vector<size_t> source;
	long data[12] = { 15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5 };
	/*L				      M			         U*/
	source.resize(30);
	ranges::generate(source.begin(), source.begin() + 10, [i = 0]() mutable	{ return i++; });
	ranges::generate(source.begin() + 10, source.begin() + 20, [i = 1000]() mutable	{ return i++; });
	ranges::generate(source.begin() + 20, source.begin() + 30, [i = 2000]() mutable	{ return i++; });
	ranges::rotate(source, source.begin() + source.size() / 2);
	pos = BinarySearch(source, 1000);
	ASSERT_GE(pos, 0);
	ASSERT_EQ(1000, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 1000 found at location: " << pos << ", " << source[pos] << endl;

	source.clear();
	source.assign(&data[0], &data[11]);
	pos = BinarySearch(source, 20);
	ASSERT_EQ(5, pos);
	ASSERT_EQ(20, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 20 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 17);
	ASSERT_EQ(2, pos);
	ASSERT_EQ(17, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 0);
	ASSERT_EQ(6, pos);
	ASSERT_EQ(0, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 3);
	ASSERT_EQ(9, pos);
	ASSERT_EQ(3, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 3 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 11);
	ASSERT_LT(pos, 0);

	long data1[20] = { 15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	/*L				             M			          U*/
	source.clear();
	source.assign(&data1[0], &data1[14]);
	pos = BinarySearch(source, 0);
	ASSERT_EQ(6, pos);
	ASSERT_EQ(0, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 0 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 5);
	ASSERT_EQ(11, pos);
	ASSERT_EQ(5, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 5 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 17);
	ASSERT_EQ(2, pos);
	ASSERT_EQ(17, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 17 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 11);
	ASSERT_LT(pos, 0);

	long data2[12] = { 4, 8, 9, 9, 9, 10, 12, 13, 1, 2, 2, 3 };
	source.clear();
	source.assign(&data2[0], &data2[11]);
	pos = BinarySearch(source, 9);
	ASSERT_GT(pos, 0);
	ASSERT_EQ(9, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 9 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 2);
	ASSERT_GT(pos, 0);
	ASSERT_EQ(2, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 2 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 12);
	ASSERT_EQ(6, pos);
	ASSERT_EQ(12, source[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: 12 found at location: " << pos << ", " << source[pos] << endl;
	pos = BinarySearch(source, 0);
	ASSERT_LT(pos, 0);
}
TEST(BinarySearchTests, MatrixBinarySearchTest) {
	vector<size_t> source;
	vector<vector<long>> a = { {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50} };
	Matrix<long> matrix(a);
	ASSERT_TRUE(matrix.SearchMatrix(a, 3));
	ASSERT_FALSE(matrix.SearchMatrix(a, 13));
	a.clear();
	a = { {1} };
	ASSERT_FALSE(matrix.SearchMatrix(a, 0));
	ASSERT_TRUE(matrix.SearchMatrix(a, 1));
	a.clear();
	a = { {1}, {3} };
	ASSERT_TRUE(matrix.SearchMatrix(a, 1));
	ASSERT_FALSE(matrix.SearchMatrix(a, 0));
	a.clear();
	a = { {1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30} };
	ASSERT_TRUE(matrix.SearchMatrix1(a, 1));
	ASSERT_TRUE(matrix.SearchMatrix1(a, 5));
	ASSERT_TRUE(matrix.SearchMatrix1(a, 9));
	ASSERT_TRUE(matrix.SearchMatrix1(a, 17));
	ASSERT_TRUE(matrix.SearchMatrix1(a, 30));
	ASSERT_FALSE(matrix.SearchMatrix1(a, 0));
	a.clear();
	a = { {1}, {2}, {3}, {4}, {5} };
	ASSERT_TRUE(matrix.SearchMatrix1(a, 2));
	ASSERT_FALSE(matrix.SearchMatrix1(a, 0));
	a.clear();
	a = { {1, 1} };
	ASSERT_TRUE(matrix.SearchMatrix1(a, 1));
	ASSERT_FALSE(matrix.SearchMatrix1(a, 0));
}
TEST(BinarySearchTests, VectorBinarySearchTest) {
	vector<size_t> source;
	source = { 5, 7, 7, 8, 8, 10 };
	vector<long> result = searchRange(source, 8);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(3, result[0]);
	ASSERT_EQ(4, result[1]);

	source.clear();
	result = searchRange(source, 0);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(-1, result[0]);
	ASSERT_EQ(-1, result[1]);

	source.clear();
	source = { 1 };
	result = searchRange(source, 1);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(0, result[0]);
	ASSERT_EQ(0, result[1]);

	source.clear();
	source = { 1, 3 };
	result = searchRange(source, 1);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(0, result[0]);
	ASSERT_EQ(0, result[1]);
	result = searchRange(source, 3);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(1, result[0]);
	ASSERT_EQ(1, result[1]);

	source.clear();
	source = { 1, 5 };
	result = searchRange(source, 4);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(-1, result[0]);
	ASSERT_EQ(-1, result[1]);

	source.clear();
	source = { 0, 0, 1, 1, 1, 4, 5, 5 };
	result = searchRange(source, 2);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(-1, result[0]);
	ASSERT_EQ(-1, result[1]);

	source.clear();
	source = { 0, 1, 2, 3, 4, 4, 4 };
	result = searchRange(source, 2);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	ASSERT_EQ(2, result[0]);
	ASSERT_EQ(2, result[1]);
}
TEST(BinarySearchTests, VectorMinimumBinarySearchTest) {
	vector<long> b{ 3, 4, 1, 5 };
	ASSERT_EQ(1, BinarySearchMinimum(b, 0, b.size() - 1));
}
TEST(BinarySearchTests, BinarySearchStringTest) {
	int pos;
	vector<string> str{ "abc", "ABC", "", "123", "789", "xyz", "XYZ", "" };
	ranges::sort(str);

	pos = BinarySearch(str, string("123"));
	ASSERT_EQ(2, pos);
	ASSERT_EQ("123", str[pos]);
	// cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: \"123\" found at location: " << pos << ", " << str[pos] << endl;

	pos = BinarySearch(str, string("abc"));
	ASSERT_EQ(6, pos);
	ASSERT_EQ("abc", str[pos]);
}
TEST(BinarySearchTests, BinarySearchCountTest) {
	vector<long> ages(50, 20);
	ages.resize(100);
	// 0:49 20, 50: 79 30, 80: 99 50
	ranges::generate(ages.begin() + 50, ages.begin() + 80, [i = 30]() mutable { return i; });
	ranges::generate(ages.begin() + 80, ages.end(), [i = 50]() mutable { return i; });
	int count = BinarySearchCountUpper(ages, 18, 0, ages.size() - 1) - BinarySearchCountLower(ages, 18, 0, ages.size() - 1);
	ASSERT_EQ(0, count);
	count = BinarySearchCountUpper(ages, 20, 0, ages.size() - 1) - BinarySearchCountLower(ages, 20, 0, ages.size() - 1) + 1;
	ASSERT_EQ(50, count);
	count = BinarySearchCountUpper(ages, 30, 0, ages.size() - 1) - BinarySearchCountLower(ages, 30, 0, ages.size() - 1) + 1;
	ASSERT_EQ(30, count);
	count = BinarySearchCountUpper(ages, 50, 0, ages.size() - 1) - BinarySearchCountLower(ages, 50, 0, ages.size() - 1) + 1;
	ASSERT_EQ(20, count);
}