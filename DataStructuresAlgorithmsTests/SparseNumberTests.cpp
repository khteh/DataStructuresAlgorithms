#include "pch.h"
using namespace std;
TEST(SparseNumberTests, SparseNumberTest) {
	ASSERT_TRUE(isSparseNumber(0));
	ASSERT_TRUE(isSparseNumber(1));
	ASSERT_TRUE(isSparseNumber(2));
	ASSERT_FALSE(isSparseNumber(3));
	ASSERT_TRUE(isSparseNumber(4));
	ASSERT_TRUE(isSparseNumber(5));
	ASSERT_FALSE(isSparseNumber(6));
	ASSERT_FALSE(isSparseNumber(7));
	ASSERT_TRUE(isSparseNumber(8));
	ASSERT_TRUE(isSparseNumber(9));
	ASSERT_EQ(1, NextSparseNumber(0));
	ASSERT_EQ(2, NextSparseNumber(1));
	ASSERT_EQ(4, NextSparseNumber(2));
	ASSERT_EQ(4, NextSparseNumber(3));
	ASSERT_EQ(5, NextSparseNumber(4));
	ASSERT_EQ(8, NextSparseNumber(5));
	ASSERT_EQ(8, NextSparseNumber(6));
	ASSERT_EQ(8, NextSparseNumber(7));
	ASSERT_EQ(9, NextSparseNumber(8));
	ASSERT_EQ(10, NextSparseNumber(9));
}