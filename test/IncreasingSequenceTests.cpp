#include "pch.h"
using namespace std;
class IncreasingSequencesTestFixture : public testing::TestWithParam<tuple<size_t, vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_p = get<1>(GetParam());
		_q = get<2>(GetParam());
	}
	size_t IncreasingSequencesTest()
	{
		return IncreasingSequences(_p, _q);
	}

protected:
	size_t _expected;
	vector<long> _p, _q;
};
TEST_P(IncreasingSequencesTestFixture, IncreasingSequencesTests)
{
	ASSERT_EQ(this->_expected, this->IncreasingSequencesTest());
}
INSTANTIATE_TEST_SUITE_P(
	IncreasingSequencesTests,
	IncreasingSequencesTestFixture,
	::testing::Values(make_tuple(2, vector<long>{5, 3, 7, 7, 10}, vector<long>{1, 6, 6, 9, 9}),
					  make_tuple(0, vector<long>{1, 5, 6}, vector<long>{-2, 0, 2}),
					  make_tuple(0, vector<long>{2, 5}, vector<long>{1, 6}),
					  make_tuple(-1, vector<long>{5, -3, 6, 4, 8}, vector<long>{2, 6, -5, 1, 0}),
					  make_tuple(-1, vector<long>{0, 0, 0}, vector<long>{1, 2, 3}),
					  make_tuple(-1, vector<long>{0, 1, 1, 2}, vector<long>{5, 4, 4, 3}),
					  make_tuple(-1, vector<long>{0, 1, 1, 2}, vector<long>{3, 4, 4, 5}),
					  make_tuple(-1, vector<long>{2, 1, 1, 0}, vector<long>{5, 4, 4, 3}),
					  make_tuple(-1, vector<long>{0, 2, 2, 4, 6, 6, 8, 10, 10}, vector<long>{1, 2, 2, 3, 4, 4, 5, 6, 6}),
					  make_tuple(-1, vector<long>{0, 1, 1, 2, 3, 3, 4, 5, 5}, vector<long>{10, 10, 9, 8, 8, 7, 6, 6, 5}),
					  make_tuple(-1, vector<long>{0, -1, -2}, vector<long>{-2, 1, 2})));

TEST(IncreasingTripletTests, IncreasingTripletTest)
{
	vector<size_t> a = {3, 2, 4, 1, 5};
	ASSERT_TRUE(increasingTriplet(a));
	a.clear();
	a = {1, 1, 1, 1, 1};
	ASSERT_TRUE(!increasingTriplet(a));
}
template <typename T1, typename T2>
class LongestSubsequenceFixture
{
public:
	void SetUp(T1 expected, vector<T2> data)
	{
		_expected = expected;
		_data = data;
	}

protected:
	T1 _expected;
	vector<T2> _data;
};

class LongestIncreasingSubsequenceNlogNTestFixture : public LongestSubsequenceFixture<size_t, size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		LongestSubsequenceFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t LongestIncreasingSubsequenceNlogNTest()
	{
		return LongestIncreasingSubsequenceNlogN(_data);
	}
};
TEST_P(LongestIncreasingSubsequenceNlogNTestFixture, LongestIncreasingSubsequenceNlogNTests)
{
	ASSERT_EQ(this->_expected, this->LongestIncreasingSubsequenceNlogNTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestIncreasingSubsequenceNlogNTests,
	LongestIncreasingSubsequenceNlogNTestFixture,
	::testing::Values(make_tuple(1, vector<size_t>{0}), make_tuple(1, vector<size_t>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}), make_tuple(6, vector<size_t>{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}),
					  make_tuple(3, vector<size_t>{3, 2, 4, 1, 5}),
					  make_tuple(1, vector<size_t>{1, 1, 1, 1, 1})));
class LongestDecreasingSubsequenceNlogNTestFixture : public LongestSubsequenceFixture<size_t, size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		LongestSubsequenceFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t LongestDecreasingSubsequenceNlogNTest()
	{
		return LongestDecreasingSubsequenceNlogN(_data);
	}
};
TEST_P(LongestDecreasingSubsequenceNlogNTestFixture, LongestDecreasingSubsequenceNlogNTests)
{
	ASSERT_EQ(this->_expected, this->LongestDecreasingSubsequenceNlogNTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestDecreasingSubsequenceNlogNTests,
	LongestDecreasingSubsequenceNlogNTestFixture,
	::testing::Values(make_tuple(5, vector<size_t>{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}),
					  make_tuple(3, vector<size_t>{3, 2, 4, 1, 5}),
					  make_tuple(1, vector<size_t>{1, 1, 1, 1, 1})));