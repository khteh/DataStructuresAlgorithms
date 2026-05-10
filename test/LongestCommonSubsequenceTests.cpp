#include "pch.h"
using namespace std;
class LongestCommonSubsequenceTestFixture : public testing::TestWithParam<tuple<size_t, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
	}
	size_t LongestCommonSubsequenceTest()
	{
		return _lcs.LCSLength(_data1, _data2);
	}

protected:
	LongestCommonSubsequence<char> _lcs;
	size_t _expected;
	string _data1, _data2;
};
TEST_P(LongestCommonSubsequenceTestFixture, LongestCommonSubsequenceTests)
{
	ASSERT_EQ(this->_expected, this->LongestCommonSubsequenceTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestCommonSubsequenceTests,
	LongestCommonSubsequenceTestFixture,
	::testing::Values(make_tuple(2, "HARRY", "SALLY"), make_tuple(3, "SHINCHAN", "NOHARAAA"), make_tuple(2, "ABCDEF", "FBDAMN"), make_tuple(2, "aa", "baaa"), make_tuple(5, "abacba", "abcaba"),
					  make_tuple(15, "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS", "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC")));
class LongestCommonSubsequenceBackTrackTestFixture : public testing::TestWithParam<tuple<tuple<size_t, string>, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
		_data1.insert(0, 1, 0);
		_data2.insert(0, 1, 0);
	}
	tuple<size_t, string> LongestCommonSubsequenceBackTrackTest()
	{
		vector<vector<size_t>> table(_data1.size(), vector<size_t>(_data2.size())); // Defaults to zero initial value
		size_t length = _lcs.LCSLength(table, _data1, _data2);
		string common = _lcs.LCSBackTrack(table, _data1, _data2, _data1.size() - 1, _data2.size() - 1);
		return make_tuple(length, common);
	}

protected:
	LongestCommonSubsequence<char> _lcs;
	tuple<size_t, string> _expected;
	string _data1, _data2;
};
TEST_P(LongestCommonSubsequenceBackTrackTestFixture, LongestCommonSubsequenceBackTrackTests)
{
	ASSERT_EQ(this->_expected, this->LongestCommonSubsequenceBackTrackTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestCommonSubsequenceBackTrackTests,
	LongestCommonSubsequenceBackTrackTestFixture,
	::testing::Values(make_tuple(make_tuple(2, "AY"), "HARRY", "SALLY"), make_tuple(make_tuple(3, "NHA"), "SHINCHAN", "NOHARAAA"), make_tuple(make_tuple(2, "BD"), "ABCDEF", "FBDAMN"), make_tuple(make_tuple(2, "aa"), "aa", "baaa"),
					  make_tuple(make_tuple(5, "ababa"), "abacba", "abcaba"), make_tuple(make_tuple(15, "DGCGTRMZJRBAJJV"), "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS", "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC")));

class LongestCommonSubsequenceCollectionTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
	}
	size_t LongestCommonSubsequenceCollectionTest()
	{
		return _lcs.LCSLength(_data1, _data2);
	}

protected:
	LongestCommonSubsequence<size_t> _lcs;
	size_t _expected;
	vector<size_t> _data1, _data2;
};
TEST_P(LongestCommonSubsequenceCollectionTestFixture, LongestCommonSubsequenceCollectionTests)
{
	ASSERT_EQ(this->_expected, this->LongestCommonSubsequenceCollectionTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestCommonSubsequenceCollectionTests,
	LongestCommonSubsequenceCollectionTestFixture,
	::testing::Values(make_tuple(3 /*"1 2 3", "1 2 1", "3 4 1" are all correct answers*/, vector<size_t>{1, 2, 3, 4, 1}, vector<size_t>{3, 4, 1, 2, 1, 3})));
class LongestCommonSubsequenceCollectionBackTrackTestFixture : public testing::TestWithParam<tuple<tuple<size_t, vector<size_t>>, vector<size_t>, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
		_data1.insert(_data1.begin(), 0);
		_data2.insert(_data2.begin(), 0);
	}
	tuple<size_t, vector<size_t>> LongestCommonSubsequenceCollectionBackTrackTest()
	{
		vector<vector<size_t>> table(_data1.size(), vector<size_t>(_data2.size())); // Defaults to zero initial value
		size_t length = _lcs.LCSLength(table, _data1, _data2);
		vector<size_t> common = _lcs.LCSBackTrack(table, _data1, _data2, _data1.size() - 1, _data2.size() - 1);
		return make_tuple(length, common);
	}

protected:
	LongestCommonSubsequence<size_t> _lcs;
	tuple<size_t, vector<size_t>> _expected;
	vector<size_t> _data1, _data2;
};
TEST_P(LongestCommonSubsequenceCollectionBackTrackTestFixture, LongestCommonSubsequenceCollectionBackTrackTests)
{
	ASSERT_EQ(this->_expected, this->LongestCommonSubsequenceCollectionBackTrackTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestCommonSubsequenceCollectionBackTrackTests,
	LongestCommonSubsequenceCollectionBackTrackTestFixture,
	::testing::Values(make_tuple(make_tuple(3, vector<size_t>{1, 2, 3}) /*"1 2 3", "1 2 1", "3 4 1" are all correct answers*/, vector<size_t>{1, 2, 3, 4, 1}, vector<size_t>{3, 4, 1, 2, 1, 3})));