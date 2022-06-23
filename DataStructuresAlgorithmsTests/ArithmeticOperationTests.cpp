#include "pch.h"
using namespace std;
TEST(ArithmerticOperationsTests, XORTest)
{
	Arithmetic arithmetic;
	ASSERT_EQ(1, arithmetic.XOR(1));
	ASSERT_EQ(3, arithmetic.XOR(2));
	ASSERT_EQ(0, arithmetic.XOR(3));
	ASSERT_EQ(4, arithmetic.XOR(4));
	ASSERT_EQ(1, arithmetic.XOR(5));
}
TEST(ArithmerticOperationsTests, ToggleSignTest)
{
	Arithmetic arithmetic;
	ASSERT_EQ(10, arithmetic.ToggleSign(-10));
	ASSERT_EQ(-10, arithmetic.ToggleSign(10));
}
TEST(ArithmerticOperationsTests, AbsoluteTest)
{
	Arithmetic arithmetic;
	ASSERT_EQ(10, arithmetic.absolute(-10));
	ASSERT_EQ(10, arithmetic.absolute(10));
}
TEST(ArithmerticOperationsTests, SubtractWithPlusSignTest)
{
	Arithmetic arithmetic;
	ASSERT_EQ(5, arithmetic.SubtractWithPlusSign(10, 5));
	ASSERT_EQ(15, arithmetic.SubtractWithPlusSign(10, -5));
}
TEST(ArithmerticOperationsTests, MultiplyWithPlusSignTest)
{
	Arithmetic arithmetic;
	ASSERT_EQ(50, arithmetic.MultiplyWithPlusSign(10, 5));
	ASSERT_EQ(-50, arithmetic.MultiplyWithPlusSign(10, -5));
}
TEST(ArithmerticOperationsTests, DivideWithPlusSignTests)
{
	Arithmetic arithmetic;
	ASSERT_EQ(3, arithmetic.DivideWithPlusSign(10, 3));
	ASSERT_EQ(-3, arithmetic.DivideWithPlusSign(10, -3));
	ASSERT_EQ(-3, arithmetic.DivideWithPlusSign(-10, 3));
	ASSERT_EQ(3, arithmetic.DivideWithPlusSign(-10, -3));
	ASSERT_EQ(10, arithmetic.DivideWithPlusSign(-10, -1));
	ASSERT_EQ(-1, arithmetic.DivideWithPlusSign(-1, 1));
	ASSERT_EQ(-1, arithmetic.DivideWithPlusSign(1, -1));
	ASSERT_EQ(1, arithmetic.DivideWithPlusSign(-1, -1));
	ASSERT_EQ((long)2147483648, arithmetic.DivideWithPlusSign(-2147483648, -1));
	ASSERT_EQ(-2147483648, arithmetic.DivideWithPlusSign(-2147483648, 1));
	ASSERT_EQ(-2147483648, arithmetic.DivideWithPlusSign(2147483648, -1)); // Takes very long time to Arithmetic.ToggleSign( of 64-bit value
}
TEST(ArithmerticOperationsTests, DivisionTests)
{
	Arithmetic arithmetic;
	ASSERT_EQ(3, arithmetic.divide(10, 3));
	ASSERT_EQ(-3, arithmetic.divide(10, -3));
	ASSERT_EQ(-3, arithmetic.divide(-10, 3));
	ASSERT_EQ(3, arithmetic.divide(-10, -3));
	ASSERT_EQ(-1, arithmetic.divide(-1, 1));
	ASSERT_EQ(-1, arithmetic.divide(1, -1));
	ASSERT_EQ(1, arithmetic.divide(-1, -1));
	ASSERT_EQ((long)2147483648, arithmetic.divide(-2147483648, -1));
	ASSERT_EQ(-2147483648, arithmetic.divide(-2147483648, 1));
	ASSERT_EQ(-2147483648, arithmetic.divide(2147483648, -1)); // Takes very long time to Arithmetic.ToggleSign( of 64-bit value
}
TEST(ArithmerticOperationsTests, AddWithoutArithmeticTests)
{
	Arithmetic arithmetic;
	cout << "Test addition without using arithmetic symbol: " << endl;
	ASSERT_EQ(0, arithmetic.AddWithoutArithmetic(0, 0));
	ASSERT_EQ(0, arithmetic.AddWithoutArithmetic(-1, 1));
	ASSERT_EQ(0x1dd9b7dde, arithmetic.AddWithoutArithmetic(0xdeadbeef, 0xfeedbeef));
	ASSERT_EQ(0xdeadbeef, arithmetic.AddWithoutArithmetic(0xdeadbeef, 0));
	ASSERT_EQ(0xfeedbeef, arithmetic.AddWithoutArithmetic(0, 0xfeedbeef));
}
TEST(ArithmerticOperationsTests, NumberStringSumTests)
{
	Arithmetic arithmetic;
	ASSERT_EQ("11111111100", arithmetic.NumberStringSum(string("1234567890"), string("9876543210")));
	ASSERT_EQ("168", arithmetic.NumberStringSum(string("123"), string("45")));
}
TEST(ArithmerticOperationsTests, NumberStringMultiplicationTests)
{
	Arithmetic arithmetic;
	string line = "-4";
	string line1 = "5";
	ASSERT_EQ("-20", arithmetic.NumberStringMultiplication(line, line1));
	line = "3";
	line1 = "-4";
	ASSERT_EQ("-12", arithmetic.NumberStringMultiplication(line, line1));
	line = "-7";
	line1 = "-8";
	ASSERT_EQ("56", arithmetic.NumberStringMultiplication(line, line1));
	line = "123456";
	line1 = "654321";
	ASSERT_EQ("80779853376", arithmetic.NumberStringMultiplication(line, line1));
	line = "456789";
	line1 = "987654";
	ASSERT_EQ("451149483006", arithmetic.NumberStringMultiplication(line, line1));
}