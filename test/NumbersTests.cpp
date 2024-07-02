#include "pch.h"
using namespace std;
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
