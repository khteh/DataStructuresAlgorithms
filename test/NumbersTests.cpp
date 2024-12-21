#include "pch.h"
using namespace std;
class BitCountTestFixture : public testing::TestWithParam<tuple<size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
	}
	size_t BitCountTest()
	{
		return BitCount(_n);
	}

protected:
	size_t _expected;
	size_t _n;
};
TEST_P(BitCountTestFixture, BitCountTests)
{
	ASSERT_EQ(this->_expected, this->BitCountTest());
}
/*
Number of binary bits needed in a number to represent number 'n'
0: 0

1: 1 (1)

2: 10 (2)
3: 11 (2)

4: 100 (3)
5: 101 (3)
6: 110 (3)
7: 111 (3)

8: 1000 (4)
9: 1001 (4)
10:1010 (4)
*/
INSTANTIATE_TEST_SUITE_P(
	BitCountTests,
	BitCountTestFixture,
	::testing::Values(make_tuple(0, 0), make_tuple(1, 1), make_tuple(2, 2), make_tuple(2, 3), make_tuple(3, 4), make_tuple(3, 5), make_tuple(3, 6), make_tuple(3, 7), make_tuple(4, 8), make_tuple(4, 9), make_tuple(4, 10)));
class BitCountOfNChoicesTestFixture : public testing::TestWithParam<tuple<size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
	}
	size_t BitCountOfNChoicesTest()
	{
		return BitCountOfNChoices(_n);
	}

protected:
	size_t _expected;
	size_t _n;
};
TEST_P(BitCountOfNChoicesTestFixture, BitCountOfNChoicesTests)
{
	ASSERT_EQ(this->_expected, this->BitCountOfNChoicesTest());
}
/*
Number of binary bits needed in a number to represent n number of choices
1: 1 (1)
2: 0 1 (1)

3: 0 01 10 (2)
4: 0 01 10 11 (2)

5: 0 01 10 11 100 (3)
6: 0 01 10 11 100 101 (3)
7: 0 01 10 11 100 101 110 (3)
8: 0 01 10 11 100 101 110 111 (3)

9: 0 01 10 11 100 101 110 111 1000 (4)
10:0 01 10 11 100 101 110 111 1000 1001 (4)
*/
INSTANTIATE_TEST_SUITE_P(
	BitCountOfNChoicesTests,
	BitCountOfNChoicesTestFixture,
	::testing::Values(make_tuple(0, 0), make_tuple(1, 1), make_tuple(1, 2), make_tuple(2, 3), make_tuple(2, 4), make_tuple(3, 5), make_tuple(3, 6), make_tuple(3, 7), make_tuple(3, 8), make_tuple(4, 9), make_tuple(4, 10)));
/*
	assert(numberToRoman(4) == "IV");
	assert(numberToRoman(9) == "IX");
	assert(numberToRoman(40) == "XL");
	assert(numberToRoman(90) == "XC");
	assert(numberToRoman(400) == "CD");
	assert(numberToRoman(900) == "CM");
*/
class NumberToRomanTestFixture : public testing::TestWithParam<tuple<string, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
	}
	string NumberToRomanTest()
	{
		return NumberToRoman(_n);
	}

protected:
	string _expected;
	size_t _n;
};
TEST_P(NumberToRomanTestFixture, NumberToRomanTests)
{
	ASSERT_EQ(this->_expected, this->NumberToRomanTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberToRomanTests,
	NumberToRomanTestFixture,
	::testing::Values(make_tuple("IV", 4),
					  make_tuple("IX", 9),
					  make_tuple("XL", 40),
					  make_tuple("XC", 90),
					  make_tuple("CD", 400), make_tuple("CM", 900)));
class CountDigitsTestFixture : public testing::TestWithParam<tuple<size_t, char, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_digit = get<1>(GetParam());
		_n = get<2>(GetParam());
	}
	size_t CountDigitsTest()
	{
		/*
		 * Test CountDigits
		 * 0 - 99: 10 + 10 = 20
		 * 100 - 199: 2 * 20
		 * 200 - 299: 3 * 20 + 100 = 160
		 * 300 - 345: 5(first digit) + 10(second digit) = 15
		 * total: 160 + 15 = 175
		 * size_t CountDigits(char digit, size_t n)
		 */
		return CountDigits(_digit, _n);
	}

protected:
	size_t _expected, _n;
	char _digit;
};
TEST_P(CountDigitsTestFixture, CountDigitsTests)
{
	ASSERT_EQ(this->_expected, this->CountDigitsTest());
}
INSTANTIATE_TEST_SUITE_P(
	CountDigitsTests,
	CountDigitsTestFixture,
	::testing::Values(make_tuple(175, 2, 345),
					  make_tuple(175, 0, 345),
					  make_tuple(10, 3, 35)));
class CountNumbersWithUniqueDigitsTestFixture : public testing::TestWithParam<tuple<size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
	}
	size_t CountNumbersWithUniqueDigitsTest()
	{
		return CountNumbersWithUniqueDigits(_n);
	}

protected:
	size_t _expected, _n;
};
TEST_P(CountNumbersWithUniqueDigitsTestFixture, CountNumbersWithUniqueDigitsTests)
{
	ASSERT_EQ(this->_expected, this->CountNumbersWithUniqueDigitsTest());
}
INSTANTIATE_TEST_SUITE_P(
	CountNumbersWithUniqueDigitsTests,
	CountNumbersWithUniqueDigitsTestFixture,
	::testing::Values(make_tuple(1, 0),
					  make_tuple(10, 1),
					  make_tuple(91, 2),   /* [0,100) */
					  make_tuple(739, 3),  /* [0,1000) */
					  make_tuple(0, 11))); /* Out of range */
class KaprekarNumbersTestFixture : public testing::TestWithParam<tuple<vector<long>, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_p = get<1>(GetParam());
		_q = get<2>(GetParam());
	}
	vector<long> KaprekarNumbersTest()
	{
		return KaprekarNumbers(_p, _q);
	}

protected:
	vector<long> _expected;
	long _p, _q;
};
TEST_P(KaprekarNumbersTestFixture, KaprekarNumbersTests)
{
	ASSERT_EQ(this->_expected, this->KaprekarNumbersTest());
}
INSTANTIATE_TEST_SUITE_P(
	KaprekarNumbersTests,
	KaprekarNumbersTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 9, 45, 55, 99}, 1, 100),
					  make_tuple(vector<long>{1, 9, 45, 55, 99, 297, 703, 999, 2223, 2728, 4950, 5050, 7272, 7777, 9999, 17344, 22222, 77778, 82656, 95121, 99999}, 1, 99999)));
class BinomialCoefficientsTestFixture : public testing::TestWithParam<tuple<unsigned long long, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
		_k = get<2>(GetParam());
	}
	unsigned long long BinomialCoefficientsTest()
	{
		return BinomialCoefficients(_n, _k);
	}

protected:
	unsigned long long _expected;
	size_t _n, _k;
};
TEST_P(BinomialCoefficientsTestFixture, BinomialCoefficientsTests)
{
	ASSERT_EQ(this->_expected, this->BinomialCoefficientsTest());
}
INSTANTIATE_TEST_SUITE_P(
	BinomialCoefficientsTests,
	BinomialCoefficientsTestFixture,
	::testing::Values(make_tuple(6, 4, 2),
					  make_tuple(252, 10, 5),
					  make_tuple(184756, 20, 10)));
class PowerSumTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_sum = get<1>(GetParam());
		_power = get<2>(GetParam());
	}
	size_t PowerSumTest()
	{
		return PowerSum(_sum, _power, 1);
	}

protected:
	size_t _expected, _sum, _power;
};
TEST_P(PowerSumTestFixture, PowerSumTests)
{
	ASSERT_EQ(this->_expected, this->PowerSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	PowerSumTests,
	PowerSumTestFixture,
	::testing::Values(make_tuple(1, 10, 2),
					  make_tuple(3, 100, 2),
					  make_tuple(1, 100, 3)));
class SuperDigitTestFixture : public testing::TestWithParam<tuple<char, string, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_num = get<1>(GetParam());
		_k = get<2>(GetParam());
	}
	char SuperDigitTest()
	{
		return SuperDigit(_num, _k);
	}

protected:
	size_t _expected, _k;
	string _num;
};
TEST_P(SuperDigitTestFixture, SuperDigitTests)
{
	ASSERT_EQ(this->_expected, this->SuperDigitTest());
}
INSTANTIATE_TEST_SUITE_P(
	SuperDigitTests,
	SuperDigitTestFixture,
	::testing::Values(make_tuple(8, "9875", 4),
					  make_tuple(3, "148", 3), make_tuple(1, "1000000000", 1000),
					  make_tuple(9, "123", 3), make_tuple(9, "9999999999", 1000)));