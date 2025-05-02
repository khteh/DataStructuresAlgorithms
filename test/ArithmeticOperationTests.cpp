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
class GCDTestFixture : public ArithmerticOperationsTestFixture<long>, public testing::TestWithParam<tuple<long, long, long>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	long GCDTest()
	{
		return _arithmetic.gcd(_var1, _var2);
	}
};
TEST_P(GCDTestFixture, GCDTests)
{
	ASSERT_EQ(this->_expected, this->GCDTest());
}
INSTANTIATE_TEST_SUITE_P(
	GCDTests,
	GCDTestFixture,
	::testing::Values(make_tuple(5, 10, 15), make_tuple(5, 35, 10), make_tuple(1, 31, 2), make_tuple(5, 15, 35)));
class GCDExtendedTestFixture : public testing::TestWithParam<tuple<GCDExtendedEuclideanResult<long>, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var1 = get<1>(GetParam());
		_var2 = get<2>(GetParam());
	}
	GCDExtendedEuclideanResult<long> GCDExtendedTest()
	{
		return _arithmetic.gcd_extended(_var1, _var2);
	}

protected:
	Arithmetic<long> _arithmetic;
	long _var1, _var2;
	GCDExtendedEuclideanResult<long> _expected;
};
TEST_P(GCDExtendedTestFixture, GCDExtendedTests)
{
	ASSERT_EQ(this->_expected, this->GCDExtendedTest());
}
INSTANTIATE_TEST_SUITE_P(
	GCDExtendedTests,
	GCDExtendedTestFixture,
	::testing::Values(make_tuple(GCDExtendedEuclideanResult<long>(5, 1, -2), 15, 35), make_tuple(GCDExtendedEuclideanResult<long>(10, 1, -1), 20, 30), make_tuple(GCDExtendedEuclideanResult<long>(7, 1, -1), 14, 21),
					  make_tuple(GCDExtendedEuclideanResult<long>(11, 1, -2), 55, 121), make_tuple(GCDExtendedEuclideanResult<long>(13, -1, 2), 91, 169)));
class ModInverseTestFixture : public ArithmerticOperationsTestFixture<long>, public testing::TestWithParam<tuple<long, long, long>>
{
public:
	void SetUp() override
	{
		ArithmerticOperationsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	long ModInverseTest()
	{
		return _arithmetic.ModInverse(_var1, _var2);
	}
};
TEST_P(ModInverseTestFixture, ModInverseTests)
{
	ASSERT_EQ(this->_expected, this->ModInverseTest());
}
INSTANTIATE_TEST_SUITE_P(
	ModInverseTests,
	ModInverseTestFixture,
	::testing::Values(make_tuple(4, 3, 11), make_tuple(12, 10, 17), make_tuple(2, 4, 7), make_tuple(8, 7, 11), make_tuple(2, 7, 13)));
class DivideModuloTestFixture : public testing::TestWithParam<tuple<long, long, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_dividend = get<1>(GetParam());
		_divisor = get<2>(GetParam());
		_modulo = get<3>(GetParam());
	}
	long DivideModuloTest()
	{
		return _arithmetic.Divide(_dividend, _divisor, _modulo);
	}

protected:
	Arithmetic<long> _arithmetic;
	long _expected, _dividend, _divisor, _modulo;
};
TEST_P(DivideModuloTestFixture, DivideModuloTests)
{
	ASSERT_EQ(this->_expected, this->DivideModuloTest());
}
INSTANTIATE_TEST_SUITE_P(
	DivideModuloTests,
	DivideModuloTestFixture,
	::testing::Values(make_tuple(2, 8, 4, 5), make_tuple(1, 8, 3, 5), make_tuple(4, 11, 4, 5), make_tuple(10, 15, 7, 11), make_tuple(16, 23, 11, 17)));
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
		return _arithmetic.Divide(_var1, _var2);
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
	DivisionOperationsTests,
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
class NumberVectorsSumTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var1 = get<1>(GetParam());
		_var2 = get<2>(GetParam());
	}
	size_t NumberVectorsSumTest()
	{
		vector<size_t> var1, var2, result;
		_arithmetic.NumberToVector(_var1, var1);
		_arithmetic.NumberToVector(_var2, var2);
		_arithmetic.NumberVectorsSum(var1, var2, result);
		return _arithmetic.DigitsVectorToNumber(result);
	}

protected:
	Arithmetic<size_t> _arithmetic;
	size_t _var1, _var2, _expected;
};
TEST_P(NumberVectorsSumTestFixture, NumberVectorsSumTests)
{
	ASSERT_EQ(this->_expected, this->NumberVectorsSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberVectorsSumTests,
	NumberVectorsSumTestFixture,
	::testing::Values(make_tuple(11111111100, 1234567890, 9876543210), make_tuple(168, 123, 45)));
class NumberVectorsMultiplicationTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var1 = get<1>(GetParam());
		_var2 = get<2>(GetParam());
	}
	size_t NumberVectorsMultiplicationTest()
	{
		vector<size_t> var1, var2, result;
		_arithmetic.NumberToVector(_var1, var1);
		_arithmetic.NumberToVector(_var2, var2);
		_arithmetic.NumberVectorsMultiplication(var1, var2, result);
		return _arithmetic.DigitsVectorToNumber(result);
	}

protected:
	Arithmetic<size_t> _arithmetic;
	size_t _var1, _var2, _expected;
};
TEST_P(NumberVectorsMultiplicationTestFixture, NumberVectorsMultiplicationTests)
{
	ASSERT_EQ(this->_expected, this->NumberVectorsMultiplicationTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberVectorsMultiplicationTests,
	NumberVectorsMultiplicationTestFixture,
	::testing::Values(make_tuple(56088, 123, 456), make_tuple(80779853376, 123456, 654321), make_tuple(451149483006, 456789, 987654)));
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
class SansaXorTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t SansaXorTest()
	{
		return _arithmetic.SansaXor(_data);
	}

protected:
	Arithmetic<size_t> _arithmetic;
	size_t _expected;
	vector<size_t> _data;
};
TEST_P(SansaXorTestFixture, SansaXorTests)
{
	ASSERT_EQ(this->_expected, this->SansaXorTest());
}
INSTANTIATE_TEST_SUITE_P(
	SansaXorTests,
	SansaXorTestFixture,
	::testing::Values(make_tuple(6, vector<size_t>{3, 4, 5}), make_tuple(2, vector<size_t>{1, 2, 3}),
					  // make_tuple(0, ranges::iota_view(0, 10) | ranges::to<vector<size_t>>()),
					  make_tuple(0, []() -> generator<size_t>
												{ co_yield ranges::elements_of(ranges::iota_view(0, 10)); }() | ranges::to<vector>())));

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
class MultinomialCoefficientsTestFixture : public testing::TestWithParam<tuple<long double, size_t, vector<size_t>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
		_k = get<2>(GetParam());
		_modulo = get<3>(GetParam());
	}
	long double MultinomialCoefficientsTest()
	{
		return MultinomialCoefficients(_n, _k, _modulo);
	}

protected:
	long double _expected;
	size_t _n, _modulo;
	vector<size_t> _k;
};
TEST_P(MultinomialCoefficientsTestFixture, MultinomialCoefficientsTests)
{
	ASSERT_EQ(this->_expected, this->MultinomialCoefficientsTest());
}
#if defined(__GNUC__) || defined(__GNUG__)
INSTANTIATE_TEST_SUITE_P(
	MultinomialCoefficientsTests,
	MultinomialCoefficientsTestFixture,
	::testing::Values(make_tuple(908107200, 15, vector<size_t>{3, 5, 2}, 0), make_tuple(1689515283456000, 20, vector<size_t>{3, 5, 2}, 0), make_tuple(908107200, 15, vector<size_t>{3, 5, 2}, 1e9 + 7), make_tuple(271629395, 20, vector<size_t>{3, 5, 2}, 1e9 + 7), make_tuple(358639400, 25, vector<size_t>{3, 5, 2}, 1e9 + 7)));
#else
INSTANTIATE_TEST_SUITE_P(
	MultinomialCoefficientsTests,
	MultinomialCoefficientsTestFixture,
	::testing::Values(make_tuple(908107200, 15, vector<size_t>{3, 5, 2}, 0), make_tuple(1689515283456000, 20, vector<size_t>{3, 5, 2}, 0), make_tuple(908107200, 15, vector<size_t>{3, 5, 2}, 1e9 + 7), make_tuple(271629395, 20, vector<size_t>{3, 5, 2}, 1e9 + 7)));
#endif