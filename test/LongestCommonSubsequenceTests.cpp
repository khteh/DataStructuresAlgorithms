#include "pch.h"
using namespace std;
class LongestCommonSubsequenceTestFixture : public testing::TestWithParam<tuple<tuple<size_t, string>, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
	}
	tuple<size_t, string> LongestCommonSubsequenceTest()
	{
		return _lcs.LCSLengthWithBackTrack(_data1, _data2);
	}

protected:
	LongestCommonSubsequence<char> _lcs;
	tuple<size_t, string> _expected;
	string _data1, _data2;
};
TEST_P(LongestCommonSubsequenceTestFixture, LongestCommonSubsequenceTests)
{
	ASSERT_EQ(this->_expected, this->LongestCommonSubsequenceTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestCommonSubsequenceTests,
	LongestCommonSubsequenceTestFixture,
	::testing::Values(make_tuple(make_tuple(2, "AY"), "HARRY", "SALLY"), make_tuple(make_tuple(3, "NHA"), "SHINCHAN", "NOHARAAA"), make_tuple(make_tuple(2, "BD"), "ABCDEF", "FBDAMN"), make_tuple(make_tuple(2, "aa"), "aa", "baaa"),
					  make_tuple(make_tuple(5, "ababa"), "abacba", "abcaba"), make_tuple(make_tuple(15, "DGCGTRMZJRBAJJV"), "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS", "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC")));

class LongestCommonSubsequenceCollectionTestFixture : public testing::TestWithParam<tuple<tuple<size_t, vector<size_t>>, vector<size_t>, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
	}
	tuple<size_t, vector<size_t>> LongestCommonSubsequenceCollectionTest()
	{
		return _lcs.LCSLengthWithBackTrack(_data1, _data2);
	}

protected:
	LongestCommonSubsequence<size_t> _lcs;
	tuple<size_t, vector<size_t>> _expected;
	vector<size_t> _data1, _data2;
};
TEST_P(LongestCommonSubsequenceCollectionTestFixture, LongestCommonSubsequenceCollectionTests)
{
	ASSERT_EQ(this->_expected, this->LongestCommonSubsequenceCollectionTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestCommonSubsequenceCollectionTests,
	LongestCommonSubsequenceCollectionTestFixture,
	::testing::Values(make_tuple(make_tuple(3, vector<size_t>{1, 2, 3}) /*"1 2 3", "1 2 1", "3 4 1" are all correct answers*/, vector<size_t>{1, 2, 3, 4, 1}, vector<size_t>{3, 4, 1, 2, 1, 3})));