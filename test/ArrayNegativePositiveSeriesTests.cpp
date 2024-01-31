#include "pch.h"
using namespace std;
TEST(ArrayNegativePositiveSeriesTests, ArrayNegativePositiveSeriesTest) {
	Sort<long> sort;
	vector<long> testArr{ 2, -1, -3, -7, -8, 9, 5, -5, -7 };
	vector<long> result { 2, -1, 9, -3, 5, -7, -8, -5, -7 };
	// Sort numbers into consecutive positive/negative numbers
	sort.SortNumbers(testArr);
	ASSERT_EQ(result, testArr);

	testArr.clear();
	result.clear();
	testArr = { -1, -3, -7, -8, 9, 5, -5, -7, 2 };
	result =  { -1, 9, -3, 5, -7, 2, -8, -5, -7 };
	// Sort numbers into consecutive positive/negative numbers
	sort.SortNumbers(testArr);
	ASSERT_EQ(result, testArr);

	testArr.clear();
	result.clear();
	testArr = { 2, -1, -3, -7, -8, 9, 5, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, -8, -5, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	result.clear();
	testArr = { 2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	result.clear();
	testArr = { 2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	result.clear();
	testArr = { 2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7 };
	result = { 2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	result.clear();
	testArr = { -1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7 };
	result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	result.clear();
	testArr = { -1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1 };
	result = { -1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1 };
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(testArr, result);

	testArr.clear();
	result.clear();
	testArr.clear();
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_TRUE(testArr.empty());

	testArr.clear();
	result.clear();
	testArr.push_back(1);
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(1, testArr.size());
	ASSERT_EQ(1, testArr[0]);
	testArr.clear();

	testArr.clear();
	result.clear();
	testArr.push_back(1);
	testArr.push_back(-1);
	OrderArrayIntoNegativePositiveSeries(testArr);
	ASSERT_EQ(2, testArr.size());
	ASSERT_EQ(1, testArr[0]);
	ASSERT_EQ(-1, testArr[1]);
}