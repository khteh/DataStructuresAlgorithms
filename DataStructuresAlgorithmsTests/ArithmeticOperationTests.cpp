#include "pch.h"
using namespace std;
TEST(ArithmerticOperationsTests, XORTest)
{
	ASSERT_EQ(1, XOR(1));
	ASSERT_EQ(3, XOR(2));
	ASSERT_EQ(0, XOR(3));
	ASSERT_EQ(4, XOR(4));
	ASSERT_EQ(1, XOR(5));
}
TEST(ArithmerticOperationsTests, ToggleSignTest)
{
	ASSERT_EQ(10, ToggleSign(-10));
	ASSERT_EQ(-10, ToggleSign(10));
}
TEST(ArithmerticOperationsTests, AbsoluteTest)
{
	ASSERT_EQ(10, absolute(-10));
	ASSERT_EQ(10, absolute(10));
}
TEST(ArithmerticOperationsTests, SubtractWithPlusSignTest)
{
	ASSERT_EQ(5, SubtractWithPlusSign(10, 5));
	ASSERT_EQ(15, SubtractWithPlusSign(10, -5));
}
TEST(ArithmerticOperationsTests, MultiplyWithPlusSignTest)
{
	ASSERT_EQ(50, MultiplyWithPlusSign(10, 5));
	ASSERT_EQ(-50, MultiplyWithPlusSign(10, -5));
}
TEST(ArithmerticOperationsTests, DivideWithPlusSignTests)
{
	ASSERT_EQ(3, DivideWithPlusSign(10, 3));
	ASSERT_EQ(-3, DivideWithPlusSign(10, -3));
	ASSERT_EQ(-3, DivideWithPlusSign(-10, 3));
	ASSERT_EQ(3, DivideWithPlusSign(-10, -3));
	ASSERT_EQ(10, DivideWithPlusSign(-10, -1));
	ASSERT_EQ(-1, DivideWithPlusSign(-1, 1));
	ASSERT_EQ(-1, DivideWithPlusSign(1, -1));
	ASSERT_EQ(1, DivideWithPlusSign(-1, -1));
	ASSERT_EQ((long)2147483648, DivideWithPlusSign(-2147483648, -1));
	ASSERT_EQ(-2147483648, DivideWithPlusSign(-2147483648, 1));
	ASSERT_EQ(-2147483648, DivideWithPlusSign(2147483648, -1)); // Takes very long time to ToggleSign of 64-bit value
}
TEST(ArithmerticOperationsTests, DivisionTests)
{
	ASSERT_EQ(3, divide(10, 3));
	ASSERT_EQ(-3, divide(10, -3));
	ASSERT_EQ(-3, divide(-10, 3));
	ASSERT_EQ(3, divide(-10, -3));
	ASSERT_EQ(-1, divide(-1, 1));
	ASSERT_EQ(-1, divide(1, -1));
	ASSERT_EQ(1, divide(-1, -1));
	ASSERT_EQ((long)2147483648, divide(-2147483648, -1));
	ASSERT_EQ(-2147483648, divide(-2147483648, 1));
	ASSERT_EQ(-2147483648, divide(2147483648, -1)); // Takes very long time to ToggleSign of 64-bit value
}
TEST(ArithmerticOperationsTests, AddWithoutArithmeticTests)
{
	cout << "Test addition without using arithmetic symbol: " << endl;
	ASSERT_EQ(0, AddWithoutArithmetic(0, 0));
	ASSERT_EQ(0, AddWithoutArithmetic(-1, 1));
	ASSERT_EQ(0x1dd9b7dde, AddWithoutArithmetic(0xdeadbeef, 0xfeedbeef));
	ASSERT_EQ(0xdeadbeef, AddWithoutArithmetic(0xdeadbeef, 0));
	ASSERT_EQ(0xfeedbeef, AddWithoutArithmetic(0, 0xfeedbeef));
}
TEST(ArithmerticOperationsTests, NumberStringSumTests)
{
	ASSERT_EQ("11111111100", NumberStringSum(string("1234567890"), string("9876543210")));
	ASSERT_EQ("168", NumberStringSum(string("123"), string("45")));
}
TEST(ArithmerticOperationsTests, NumberStringMultiplicationTests)
{
	string line = "-4";
	string line1 = "5";
	ASSERT_EQ("-20", NumberStringMultiplication(line, line1));
	line = "3";
	line1 = "-4";
	ASSERT_EQ("-12", NumberStringMultiplication(line, line1));
	line = "-7";
	line1 = "-8";
	ASSERT_EQ("56", NumberStringMultiplication(line, line1));
	line = "123456";
	line1 = "654321";
	ASSERT_EQ("80779853376", NumberStringMultiplication(line, line1));
	line = "456789";
	line1 = "987654";
	ASSERT_EQ("451149483006", NumberStringMultiplication(line, line1));
}