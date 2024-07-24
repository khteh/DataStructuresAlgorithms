#include "pch.h"
using namespace std;
class IsSparseNumberTestFixture : public testing::TestWithParam<tuple<bool, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var = get<1>(GetParam());
	}
	bool IsSparseNumberTest()
	{
		return IsSparseNumber(_var);
	}

protected:
	bool _expected;
	long _var;
};
TEST_P(IsSparseNumberTestFixture, IsSparseNumberTests)
{
	ASSERT_EQ(this->_expected, this->IsSparseNumberTest());
}
INSTANTIATE_TEST_SUITE_P(
	IsSparseNumberTests,
	IsSparseNumberTestFixture,
	::testing::Values(make_tuple(true, 0), make_tuple(true, 1), make_tuple(true, 2), make_tuple(false, 3), make_tuple(true, 4), make_tuple(true, 5), make_tuple(false, 6), make_tuple(false, 7), make_tuple(true, 8), make_tuple(true, 9)));
class NextSparseNumberTestFixture : public testing::TestWithParam<tuple<long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var = get<1>(GetParam());
	}
	long NextSparseNumberTest()
	{
		return NextSparseNumber(_var);
	}

protected:
	long _expected, _var;
};
TEST_P(NextSparseNumberTestFixture, NextSparseNumberTests)
{
	ASSERT_EQ(this->_expected, this->NextSparseNumberTest());
}
INSTANTIATE_TEST_SUITE_P(
	NextSparseNumberTests,
	NextSparseNumberTestFixture,
	::testing::Values(make_tuple(1, 0), make_tuple(2, 1), make_tuple(4, 2), make_tuple(4, 3), make_tuple(5, 4), make_tuple(8, 5), make_tuple(8, 6), make_tuple(8, 7), make_tuple(9, 8), make_tuple(10, 9)));
