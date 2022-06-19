#include "pch.h"
using namespace std;
TEST(NumbersTests, countDigitsTests)
{
	// Test countDigits
	// 0 - 99: 10 + 10 = 20
	// 100 - 199: 2 * 20
	// 200 - 299: 3 * 20 + 100 = 160
	// 300 - 345: 5(first digit) + 10(second digit) = 15
	// total: 160 + 15 = 175
	ASSERT_EQ(175, countDigits(2, 345));
	ASSERT_EQ(175, countDigits(0, 345));
	ASSERT_EQ(10, countDigits(3, 35)); // {3,13,23},30,31,32,{3}3,34,35
}
TEST(NumbersTests, countNumbersWithUniqueDigitsTests)
{
	ASSERT_EQ(1, countNumbersWithUniqueDigits(0));
	ASSERT_EQ(10, countNumbersWithUniqueDigits(1));
	ASSERT_EQ(91, countNumbersWithUniqueDigits(2));	// [0,100)
	ASSERT_EQ(739, countNumbersWithUniqueDigits(3)); // [0,1000)
	ASSERT_EQ(0, countNumbersWithUniqueDigits(11));
}