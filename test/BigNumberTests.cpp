#include "pch.h"
using namespace std;
// BigFromString / BigToString round trip. Leading zeros are dropped.
class BigNumberStringTestFixture : public testing::TestWithParam<tuple<string, string, BigNumber>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_input = get<1>(GetParam());
		_limbs = get<2>(GetParam());
	}

protected:
	string _expected, _input;
	BigNumber _limbs;
};
TEST_P(BigNumberStringTestFixture, BigNumberStringTests)
{
	BigNumber number = BigFromString(_input);
	ASSERT_EQ(_limbs, number); // Least significant limb first
	ASSERT_EQ(_expected, BigToString(number));
}
// Columns: expected string, input string, expected limbs
INSTANTIATE_TEST_SUITE_P(
	BigNumberStringTests,
	BigNumberStringTestFixture,
	::testing::Values(
		make_tuple("0", "0", BigNumber{0}),
		make_tuple("0", "0000", BigNumber{0}),
		make_tuple("123", "000123", BigNumber{123}),
		make_tuple("999999999", "999999999", BigNumber{999999999}),							// Largest single limb
		make_tuple("1000000000", "1000000000", BigNumber{0, 1}),								// 10^9: second limb
		make_tuple("1000000005", "1000000005", BigNumber{5, 1}),								// Middle limb printed as 000000005
		make_tuple("123456789012345678901", "123456789012345678901", BigNumber{345678901, 456789012, 123}),
		make_tuple("18446744073709551615", "18446744073709551615", BigNumber{709551615, 446744073, 18}))); // UINT64_MAX
TEST(BigNumberTests, BigFromNumberTest)
{
	ASSERT_EQ(BigNumber{0}, BigFromNumber(0));
	ASSERT_EQ(BigNumber{999999999}, BigFromNumber(999999999));
	ASSERT_EQ((BigNumber{0, 1}), BigFromNumber(1000000000));
	ASSERT_EQ("18446744073709551615", BigToString(BigFromNumber(numeric_limits<uint64_t>::max())));
}
// Invalid input: std::invalid_argument
TEST(BigNumberTests, BigNumberValidationTest)
{
	for (string_view invalid : {"", "-1", "+1", " 1", "1 ", "12a3", "1.5"})
		ASSERT_THROW(BigFromString(invalid), invalid_argument) << "\"" << invalid << "\"";
	BigNumber one{1};
	for (BigNumber const &invalid : {BigNumber{}, BigNumber{1000000000}, BigNumber{5, 0}, BigNumber{0, 0}})
	{
		ASSERT_THROW(BigValidate(invalid), invalid_argument);
		ASSERT_THROW(BigToString(invalid), invalid_argument);
		ASSERT_THROW(BigAdd(invalid, one), invalid_argument);
		ASSERT_THROW(BigSubtract(invalid, BigNumber{0}), invalid_argument);
		ASSERT_THROW(BigSubtract(one, invalid), invalid_argument);
		ASSERT_THROW(BigMultiply(one, invalid), invalid_argument);
		ASSERT_THROW(BigDivide(invalid, one), invalid_argument);
		ASSERT_THROW(BigDivide(one, invalid), invalid_argument);
		ASSERT_THROW(BigCompare(invalid, one), invalid_argument);
	}
	ASSERT_NO_THROW(BigValidate(BigNumber{0}));
	ASSERT_NO_THROW(BigValidate((BigNumber{0, 0, 7})));
}
TEST(BigNumberTests, BigCompareTest)
{
	ASSERT_EQ(strong_ordering::equal, BigCompare(BigFromString("0"), BigFromString("0")));
	ASSERT_EQ(strong_ordering::less, BigCompare(BigFromString("999999999"), BigFromString("1000000000")));		// Fewer limbs
	ASSERT_EQ(strong_ordering::greater, BigCompare(BigFromString("2000000001"), BigFromString("1999999999"))); // Same limbs, top limb decides
	ASSERT_EQ(strong_ordering::less, BigCompare(BigFromString("1000000001"), BigFromString("1000000002")));	// Same top limb, next one decides
}
class BigMultiplyTestFixture : public testing::TestWithParam<tuple<string, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_a = get<1>(GetParam());
		_b = get<2>(GetParam());
	}

protected:
	string _expected, _a, _b;
};
TEST_P(BigMultiplyTestFixture, BigMultiplyTests)
{
	ASSERT_EQ(_expected, BigToString(BigMultiply(BigFromString(_a), BigFromString(_b))));
	ASSERT_EQ(_expected, BigToString(BigMultiply(BigFromString(_b), BigFromString(_a)))); // Commutative
}
// Columns: expected product, a, b
INSTANTIATE_TEST_SUITE_P(
	BigMultiplyTests,
	BigMultiplyTestFixture,
	::testing::Values(
		make_tuple("0", "0", "0"),
		make_tuple("0", "0", "123456789012345678901234567890"),
		make_tuple("123456789012345678901234567890", "1", "123456789012345678901234567890"),
		make_tuple("999999998000000001", "999999999", "999999999"),					   // Largest limb product: carry into the next limb
		make_tuple("1000000000000000000", "1000000000", "1000000000"),				   // 10^9 x 10^9
		make_tuple("999999999999999998000000000000000001", "999999999999999999", "999999999999999999"), // (10^18 - 1)^2: carries through every limb
		make_tuple("340282366920938463426481119284349108225", "18446744073709551615", "18446744073709551615"), // UINT64_MAX^2
		make_tuple("121932631137021795226185032733622923332237463801111263526900", "123456789012345678901234567890", "987654321098765432109876543210"),
		make_tuple("1219326311370217952237463801111263526900", "12345678901234567890", "98765432109876543210")));
class BigSubtractTestFixture : public testing::TestWithParam<tuple<string, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_a = get<1>(GetParam());
		_b = get<2>(GetParam());
	}

protected:
	string _expected, _a, _b;
};
TEST_P(BigSubtractTestFixture, BigSubtractTests)
{
	ASSERT_EQ(_expected, BigToString(BigSubtract(BigFromString(_a), BigFromString(_b))));
}
// Columns: expected difference, a, b
INSTANTIATE_TEST_SUITE_P(
	BigSubtractTests,
	BigSubtractTestFixture,
	::testing::Values(
		make_tuple("0", "0", "0"),
		make_tuple("0", "123456789012345678901", "123456789012345678901"), // Every limb becomes 0: trimmed to {0}
		make_tuple("123456789012345678901", "123456789012345678901", "0"),
		make_tuple("999999999", "1000000000", "1"),							  // Borrow from the next limb
		make_tuple("999999999999999999999999999", "1000000000000000000000000000", "1"), // Borrow through every limb
		make_tuple("1", "123456789012345678901", "123456789012345678900"),	  // Leading zero limbs trimmed
		make_tuple("1000000000", "1999999999", "999999999"),
		make_tuple("340282366920938463444927863358058659840", "340282366920938463463374607431768211455", "18446744073709551615"), // 2^128 - 1 - (2^64 - 1)
		make_tuple("864197532086419753208641975320", "987654321098765432109876543210", "123456789012345678901234567890")));
TEST(BigNumberTests, BigSubtractNegativeTest)
{
	// A BigNumber is unsigned: a < b is an error
	ASSERT_THROW(BigSubtract(BigFromString("0"), BigFromString("1")), domain_error);
	ASSERT_THROW(BigSubtract(BigFromString("123456789012345678900"), BigFromString("123456789012345678901")), domain_error);
	ASSERT_THROW(BigSubtract(BigFromString("999999999"), BigFromString("1000000000")), domain_error);
}
class BigDivideTestFixture : public testing::TestWithParam<tuple<string, string, string, string>>
{
public:
	void SetUp() override
	{
		_quotient = get<0>(GetParam());
		_remainder = get<1>(GetParam());
		_dividend = get<2>(GetParam());
		_divisor = get<3>(GetParam());
	}

protected:
	string _quotient, _remainder, _dividend, _divisor;
};
TEST_P(BigDivideTestFixture, BigDivideTests)
{
	auto [quotient, remainder] = BigDivide(BigFromString(_dividend), BigFromString(_divisor));
	ASSERT_EQ(_quotient, BigToString(quotient));
	ASSERT_EQ(_remainder, BigToString(remainder));
}
// Columns: expected quotient, expected remainder, dividend, divisor
INSTANTIATE_TEST_SUITE_P(
	BigDivideTests,
	BigDivideTestFixture,
	::testing::Values(
		make_tuple("0", "0", "0", "7"),
		make_tuple("0", "5", "5", "7"),															  // Dividend < divisor
		make_tuple("0", "123456789012345678901", "123456789012345678901", "123456789012345678902"), // Multi-limb, dividend < divisor
		make_tuple("1", "0", "123456789012345678901", "123456789012345678901"),
		make_tuple("123456789012345678901", "0", "123456789012345678901", "1"),
		// Single-limb divisor: short division
		make_tuple("17636684144620811271", "4", "123456789012345678901", "7"),
		make_tuple("123456789012", "345678901", "123456789012345678901", "1000000000"), // 10^9: two-limb divisor {0, 1}
		make_tuple("1000000000", "0", "999999999000000000", "999999999"),
		// Multi-limb divisor: long division
		make_tuple("123456789012345678901234567890", "0", "121932631137021795226185032733622923332237463801111263526900", "987654321098765432109876543210"), // Exact
		make_tuple("124999998873437499901", "574845669", "123456789012345678901234567890", "987654321"),
		make_tuple("124999998", "862654320900984567894", "123456789012345678901234567890", "987654321000000000002"),
		make_tuple("18446744073709551614", "18446744073709551615", "340282366920938463444927863358058659839", "18446744073709551616"), // Around 2^64 and 2^128
		// The rare case where the estimated quotient limb is 1 too large and the divisor is added back
		make_tuple("999999999", "999999999000000001", "1000000000000000000000000000", "1000000000000000001"),
		make_tuple("499999998999999999", "500000001000000001", "499999999000000000000000000000000000", "1000000000000000001")));
TEST(BigNumberTests, BigDivideByZeroTest)
{
	ASSERT_THROW(BigDivide(BigFromString("123"), BigNumber{0}), domain_error);
	ASSERT_THROW(BigDivide(BigNumber{0}, BigNumber{0}), domain_error);
}
// Large numbers, with results known in closed form. k = 9999 and 10000: the number of digits is
// not a multiple of 9, and is a multiple of 9 + 1, so the top limb is partly and fully used.
TEST(BigNumberTests, BigNumberLargeTest)
{
	for (size_t k : {9999, 10000})
	{
		BigNumber nines = BigFromString(string(k, '9'));			 // 10^k - 1
		BigNumber power = BigFromString("1" + string(k, '0'));		 // 10^k
		BigNumber square = BigMultiply(nines, nines);				 // (10^k - 1)^2 = 10^2k - 2 x 10^k + 1
		ASSERT_EQ(string(k - 1, '9') + "8" + string(k - 1, '0') + "1", BigToString(square)) << k;
		ASSERT_EQ(power, BigAdd(nines, BigNumber{1})) << k;		 // Carry through every limb
		ASSERT_EQ(nines, BigSubtract(power, BigNumber{1})) << k;	 // Borrow through every limb
		BigNumber dividend = BigSubtract(BigMultiply(power, power), BigNumber{1}); // 10^2k - 1 = (10^k - 1)(10^k + 1)
		auto [quotient, remainder] = BigDivide(dividend, nines);
		ASSERT_EQ(BigAdd(power, BigNumber{1}), quotient) << k;
		ASSERT_EQ(BigNumber{0}, remainder) << k;
		tie(quotient, remainder) = BigDivide(square, BigAdd(power, BigNumber{1})); // (10^k - 1)^2 = (10^k + 1)(10^k - 3) + 4
		ASSERT_EQ(BigSubtract(power, BigNumber{3}), quotient) << k;
		ASSERT_EQ(BigNumber{4}, remainder) << k;
	}
}
// Random numbers: the product must match StringArithmetic, an independent implementation,
// subtraction must undo addition, and division must satisfy
// dividend = quotient x divisor + remainder, with remainder < divisor.
TEST(BigNumberTests, BigNumberRandomTest)
{
	mt19937_64 generator(12345); // Fixed seed: reproducible failures
	uniform_int_distribution<size_t> length(1, 120);
	uniform_int_distribution<int> digit(0, 9), nines(0, 3);
	auto randomNumber = [&]
	{
		string number(length(generator), '0');
		bool manyNines = !nines(generator); // Strings of 9s exercise carries and quotient corrections
		for (char &c : number)
			c = static_cast<char>('0' + (manyNines && digit(generator) < 7 ? 9 : digit(generator)));
		return number;
	};
	StringArithmetic stringArithmetic;
	for (size_t i = 0; i < 2000; i++)
	{
		string a = randomNumber(), b = randomNumber();
		BigNumber A = BigFromString(a), B = BigFromString(b);
		ASSERT_EQ(stringArithmetic.NumberStringMultiplication(a, b), BigToString(BigMultiply(A, B))) << a << " x " << b;
		ASSERT_EQ(A, BigSubtract(BigAdd(A, B), B)) << a << " + " << b << " - " << b;
		if (BigCompare(A, B) != strong_ordering::less)
		{
			ASSERT_EQ(A, BigAdd(BigSubtract(A, B), B)) << a << " - " << b << " + " << b;
		}
		if (B == BigNumber{0})
			continue;
		auto [quotient, remainder] = BigDivide(A, B);
		ASSERT_EQ(A, BigAdd(BigMultiply(quotient, B), remainder)) << a << " / " << b;
		ASSERT_EQ(strong_ordering::less, BigCompare(remainder, B)) << a << " / " << b;
	}
}
