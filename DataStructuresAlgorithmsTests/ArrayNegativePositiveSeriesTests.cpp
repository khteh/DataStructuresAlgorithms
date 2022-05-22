#include "pch.h"
using namespace std;
TEST(ArrayNegativePositiveSeriesTests, ArrayNegativePositiveSeriesTest) {
	vector<long> a{ 2, -1, -3, -7, -8, 9, 5, -5, -7 };
	// Start of Sort numbers into consecutive positive/negative numbers
	// 2,-1,-3,-7,-8,9,5,-5,-7
	sortNumbers(a);
	copy(a.begin(), a.end(), ostream_iterator<long>(cout, " "));
	cout << endl;
	a.clear();
	vector<long> testArr{ 2, -1, -3, -7, -8, 9, 5, -5, -7 };
	vector<long> result{ 2, -1, 9, -3, 5, -7, -8, -5, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr = { 2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr = { 2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr = { 2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr = { -1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7 };
	result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr = { -1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1 };
	result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_TRUE(testArr.empty());

	testArr.push_back(1);
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(1, testArr.size());
	ASSERT_EQ(1, testArr[0]);
	testArr.clear();

	testArr.push_back(1);
	testArr.push_back(-1);
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(2, testArr.size());
	ASSERT_EQ(1, testArr[0]);
	ASSERT_EQ(-1, testArr[1]);
}