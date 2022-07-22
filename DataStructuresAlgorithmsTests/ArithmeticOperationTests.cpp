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
class DivideWithPlusSignTestFixture : public testing::TestWithParam<tuple<long, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var1 = get<1>(GetParam());
		_var2 = get<2>(GetParam());
	}
	long DivideWithPlusSignTest()
	{
		return _arithmetic.DivideWithPlusSign(_var1, _var2);
	}
	long DivisionTest()
	{
		return _arithmetic.divide(_var1, _var2);
	}

protected:
	Arithmetic _arithmetic;
	long _var1, _var2;
	long _expected;
};
TEST_P(DivideWithPlusSignTestFixture, DivideWithPlusSignTests)
{
	ASSERT_EQ(this->_expected, this->DivideWithPlusSignTest());
}
TEST_P(DivideWithPlusSignTestFixture, DivisionTests)
{
	ASSERT_EQ(this->_expected, this->DivisionTest());
}
INSTANTIATE_TEST_SUITE_P(
	ArithmerticOperationsTests,
	DivideWithPlusSignTestFixture,
	::testing::Values(make_tuple(3, 10, 3), make_tuple(-3, 10, -3), make_tuple(-3, -10, 3), make_tuple(3, -10, -3), make_tuple(10, -10, -1), make_tuple(-1, -1, 1), make_tuple(-1, 1, -1), make_tuple(1, -1, -1),
					  make_tuple(2147483648L, -2147483648, -1), make_tuple(-2147483648, -2147483648, 1), make_tuple(-2147483648, 2147483648L, -1)));
class AddWithoutArithmeticTestFixture : public testing::TestWithParam<tuple<long long, long long, long long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var1 = get<1>(GetParam());
		_var2 = get<2>(GetParam());
	}
	long long AddWithoutArithmeticTest()
	{
		return _arithmetic.AddWithoutArithmetic(_var1, _var2);
	}

protected:
	Arithmetic _arithmetic;
	long long _var1, _var2;
	long long _expected;
};
TEST_P(AddWithoutArithmeticTestFixture, AddWithoutArithmeticTests)
{
	ASSERT_EQ(this->_expected, this->AddWithoutArithmeticTest());
}
INSTANTIATE_TEST_SUITE_P(
	ArithmerticOperationsTests,
	AddWithoutArithmeticTestFixture,
	::testing::Values(make_tuple(0, 0, 0), make_tuple(0, -1, 1), make_tuple(0x1dd9b7dde, 0xdeadbeef, 0xfeedbeef), make_tuple(0xdeadbeef, 0xdeadbeef, 0), make_tuple(0xfeedbeef, 0, 0xfeedbeef)));
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