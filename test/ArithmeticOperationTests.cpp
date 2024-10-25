#include "pch.h"
using namespace std;
TEST(ArithmerticOperationsTests, XORTest)
{
	Arithmetic<long> arithmetic;
	ASSERT_EQ(1, arithmetic.XOR(1));
	ASSERT_EQ(3, arithmetic.XOR(2));
	ASSERT_EQ(0, arithmetic.XOR(3));
	ASSERT_EQ(4, arithmetic.XOR(4));
	ASSERT_EQ(1, arithmetic.XOR(5));
}
TEST(ArithmerticOperationsTests, ToggleSignTest)
{
	Arithmetic<long> arithmetic;
	ASSERT_EQ(10, arithmetic.ToggleSign(-10));
	ASSERT_EQ(-10, arithmetic.ToggleSign(10));
}
TEST(ArithmerticOperationsTests, AbsoluteTest)
{
	Arithmetic<long> arithmetic;
	ASSERT_EQ(10, arithmetic.absolute(-10));
	ASSERT_EQ(10, arithmetic.absolute(10));
}
TEST(ArithmerticOperationsTests, SubtractWithPlusSignTest)
{
	Arithmetic<long> arithmetic;
	ASSERT_EQ(5, arithmetic.SubtractWithPlusSign(10, 5));
	ASSERT_EQ(15, arithmetic.SubtractWithPlusSign(10, -5));
}
TEST(ArithmerticOperationsTests, MultiplyWithPlusSignTest)
{
	Arithmetic<long> arithmetic;
	ASSERT_EQ(50, arithmetic.MultiplyWithPlusSign(10, 5));
	ASSERT_EQ(-50, arithmetic.MultiplyWithPlusSign(10, -5));
}
template <typename T>
class ArithmerticOperationsTestFixture
{
public:
	void SetUp(T expected, T var1, T var2)
	{
		_expected = expected;
		_var1 = var1;
		_var2 = var2;
	}

protected:
	Arithmetic<T> _arithmetic;
	T _var1, _var2, _expected;
};
class DivideWithPlusSignTestFixture : public ArithmerticOperationsTestFixture<long>, public testing::TestWithParam<tuple<long, long, long>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	long DivideWithPlusSignTest()
	{
		return _arithmetic.DivideWithPlusSign(_var1, _var2);
	}
	long DivisionTest()
	{
		return _arithmetic.divide(_var1, _var2);
	}
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
class AddWithoutArithmeticTestFixture : public ArithmerticOperationsTestFixture<long long>, public testing::TestWithParam<tuple<long long, long long, long long>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	long long AddWithoutArithmeticTest()
	{
		return _arithmetic.AddWithoutArithmetic(_var1, _var2);
	}
};
TEST_P(AddWithoutArithmeticTestFixture, AddWithoutArithmeticTests)
{
	ASSERT_EQ(this->_expected, this->AddWithoutArithmeticTest());
}
INSTANTIATE_TEST_SUITE_P(
	ArithmerticOperationsTests,
	AddWithoutArithmeticTestFixture,
	::testing::Values(make_tuple(0, 0, 0), make_tuple(0, -1, 1), make_tuple(0x1dd9b7dde, 0xdeadbeef, 0xfeedbeef), make_tuple(0xdeadbeef, 0xdeadbeef, 0), make_tuple(0xfeedbeef, 0, 0xfeedbeef)));
class NumberStringSumTestFixture : public ArithmerticOperationsTestFixture<string>, public testing::TestWithParam<tuple<string, string, string>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	string NumberStringSumTest()
	{
		return _arithmetic.NumberStringSum(_var1, _var2);
	}
};
TEST_P(NumberStringSumTestFixture, NumberStringSumTests)
{
	ASSERT_EQ(this->_expected, this->NumberStringSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberStringSumTests,
	NumberStringSumTestFixture,
	::testing::Values(make_tuple("11111111100", "1234567890", "9876543210"), make_tuple("168", "123", "45")));
class NumberStringMultiplicationTestFixture : public ArithmerticOperationsTestFixture<string>, public testing::TestWithParam<tuple<string, string, string>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	string NumberStringMultiplicationTest()
	{
		return _arithmetic.NumberStringMultiplication(_var1, _var2);
	}
};
TEST_P(NumberStringMultiplicationTestFixture, NumberStringMultiplicationTests)
{
	ASSERT_EQ(this->_expected, this->NumberStringMultiplicationTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberStringMultiplicationTests,
	NumberStringMultiplicationTestFixture,
	::testing::Values(make_tuple("-20", "-4", "5"), make_tuple("-12", "3", "-4"), make_tuple("56", "-7", "-8"), make_tuple("80779853376", "123456", "654321"), make_tuple("451149483006", "456789", "987654")));
class XorSequenceTestFixture : public ArithmerticOperationsTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t XorSequenceTest()
	{
		return _arithmetic.XorSequence(_var1, _var2);
	}
};
TEST_P(XorSequenceTestFixture, XorSequenceTests)
{
	ASSERT_EQ(this->_expected, this->XorSequenceTest());
}
INSTANTIATE_TEST_SUITE_P(
	XorSequenceTests,
	XorSequenceTestFixture,
	::testing::Values(make_tuple(6, 1, 4), make_tuple(7, 2, 4), make_tuple(9, 2, 8), make_tuple(15, 5, 9), make_tuple(5, 3, 5), make_tuple(2, 4, 6), make_tuple(22, 15, 20)));
class IsAdditiveNumberTestFixture : public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var = get<1>(GetParam());
	}
	bool IsAdditiveNumberTest()
	{
		return _arithmetic.IsAdditiveNumber(_var);
	}

protected:
	Arithmetic<string> _arithmetic;
	bool _expected;
	string _var;
};
TEST_P(IsAdditiveNumberTestFixture, IsAdditiveNumberTests)
{
	ASSERT_EQ(this->_expected, this->IsAdditiveNumberTest());
}
INSTANTIATE_TEST_SUITE_P(
	IsAdditiveNumberTests,
	IsAdditiveNumberTestFixture,
	::testing::Values(make_tuple(true, "123"), make_tuple(true, "123581321"), make_tuple(true, "199100199"), make_tuple(false, "1203"), make_tuple(false, "1023"), make_tuple(false, "0123")));
class ReversePolishNotationTestFixture : public testing::TestWithParam<tuple<size_t, vector<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var = get<1>(GetParam());
	}
	size_t ReversePolishNotationTest()
	{
		return _arithmetic.ReversePolishNotation(_var);
	}

protected:
	Arithmetic<size_t> _arithmetic;
	long _expected;
	vector<string> _var;
};
TEST_P(ReversePolishNotationTestFixture, ReversePolishNotationTests)
{
	ASSERT_EQ(this->_expected, this->ReversePolishNotationTest());
}
INSTANTIATE_TEST_SUITE_P(
	ReversePolishNotationTests,
	ReversePolishNotationTestFixture,
	::testing::Values(make_tuple(9, vector<string>{"2", "1", "+", "3", "*"}), make_tuple(6, vector<string>{"4", "13", "5", "/", "+"}), make_tuple(22, vector<string>{"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"})));
