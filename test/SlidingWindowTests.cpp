#include "pch.h"
using namespace std;
class MaxSlidingWindowTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<long>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _n = get<1>(GetParam());
        _data = get<2>(GetParam());
    }
    vector<long> MaxSlidingWindowTest()
    {
        vector<long> result;
        _slidingWindow.MaxSlidingWindow(_data, _n, result);
        return result;
    }

protected:
    SlidingWindow<long> _slidingWindow;
    vector<long> _expected, _data;
    size_t _n;
};
TEST_P(MaxSlidingWindowTestFixture, MaxSlidingWindowTests)
{
    ASSERT_EQ(this->_expected, this->MaxSlidingWindowTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxSlidingWindowTests,
    MaxSlidingWindowTestFixture,
    ::testing::Values(make_tuple(vector<long>{3, 3, 5, 5, 6, 7}, 3, vector<long>{1, 3, -1, -3, 5, 3, 6, 7}),
        make_tuple(vector<long>{3, 3}, 3, vector<long>{3, 1, 1, 3}),
        make_tuple(vector<long>{-3, -2, -1, 0, 1, 2}, 1uz, views::iota(-3l, 3l) | ranges::to<vector<long>>())
        /*make_tuple(vector<long>{-3, -2, -1, 0, 1, 2}, 1, []() -> generator<long> { co_yield ranges::elements_of(views::iota(-3, 3)); }() | ranges::to<vector>())*/
    ));
class MaxHarvestTestFixture : public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _param = get<1>(GetParam());
        _data = get<2>(GetParam());
    }
    int64_t MaxHarvestTest()
    {
        return _slidingWindow.MaxHarvest(_data, _param);
    }
protected:
    SlidingWindow<size_t> _slidingWindow;
    vector<size_t> _data;
    size_t _param, _expected;
};
TEST_P(MaxHarvestTestFixture, MaxHarvestTests)
{
    ASSERT_EQ(this->_expected, this->MaxHarvestTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxHarvestTests,
    MaxHarvestTestFixture,
    ::testing::Values(make_tuple(3, 2, vector<size_t>{1, 2, 1}),
        make_tuple(3, 2, vector<size_t>{0, 1, 2, 2}),
        make_tuple(4, 2, vector<size_t>{1, 2, 3, 2, 2}),
        make_tuple(4, 2, vector<size_t>{1, 1, 0, 2, 2, 2}),
        make_tuple(6, 3, vector<size_t>{1, 1, 0, 3, 2, 2, 3, 3}),
        make_tuple(6, 3, vector<size_t>{1, 1, 0, 3, 2, 3, 2, 3}),
        make_tuple(6, 3, vector<size_t>{1, 1, 0, 2, 2, 2, 3, 3}),
        make_tuple(7, 3, vector<size_t>{0, 1, 1, 3, 2, 2, 3, 3})));
class SteadyGeneChallengeTestFixture : public testing::TestWithParam<tuple<size_t, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
    }
    size_t SteadyGeneChallengeTest()
    {
        return _slidingWindow.SteadyGene(_data);
    }
protected:
    SlidingWindow<size_t> _slidingWindow;
    string _data;
    size_t _expected;
};
TEST_P(SteadyGeneChallengeTestFixture, SteadyGeneChallengeTests)
{
    ASSERT_EQ(this->_expected, this->SteadyGeneChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
    SteadyGeneChallengeTests,
    SteadyGeneChallengeTestFixture,
    ::testing::Values(make_tuple(2, "ATAA"), make_tuple(1, "ACGTCCGT"), make_tuple(0, "AAGTGCCT"), make_tuple(2, "ACTGAAAG"), make_tuple(5, "GAAATAAA"), make_tuple(5, "TGATGCCGTCCCCTCAACTTGAGTGCTCCTAATGCGTTGC")));
class LongestCommonSubstringWithFixesTestFixture : public testing::TestWithParam<tuple<size_t, string, string, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _str1 = get<1>(GetParam());
        _str2 = get<2>(GetParam());
        _k = get<3>(GetParam());
    }
    size_t LongestCommonSubstringWithFixesTest()
    {
        return _slidingWindow.LongestCommonSubstringWithFixes(_str1, _str2, _k);
    }
protected:
    SlidingWindow<size_t> _slidingWindow;
    string _str1, _str2;
    size_t _expected, _k;
};
TEST_P(LongestCommonSubstringWithFixesTestFixture, LongestCommonSubstringWithFixesTests)
{
    ASSERT_EQ(this->_expected, this->LongestCommonSubstringWithFixesTest());
}
INSTANTIATE_TEST_SUITE_P(
    LongestCommonSubstringWithFixesTests,
    LongestCommonSubstringWithFixesTestFixture,
    ::testing::Values(make_tuple(2, "abcd", "adbc", 0), make_tuple(3, "abcd", "adbc", 1), make_tuple(4, "helloworld", "yellomarin", 0), make_tuple(8, "helloworld", "yellomarin", 3),
        make_tuple(4, "tabriz", "torino", 2), make_tuple(3, "abacba", "abcaba", 0)));

class LongestStringWithCharacterReplacementTestFixture : public testing::TestWithParam<tuple<size_t, string, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _string = get<1>(GetParam());
        _k = get<2>(GetParam());
    }
    size_t LongestStringWithCharacterReplacementTest()
    {
        return _slidingWindow.LongestStringWithCharacterReplacement(_string, _k);
    }

protected:
    SlidingWindow<size_t> _slidingWindow;
    size_t _expected, _k;
    string _string;
};
TEST_P(LongestStringWithCharacterReplacementTestFixture, LongestStringWithCharacterReplacementTests)
{
    ASSERT_EQ(this->_expected, this->LongestStringWithCharacterReplacementTest());
}
INSTANTIATE_TEST_SUITE_P(
    LongestStringWithCharacterReplacementTests,
    LongestStringWithCharacterReplacementTestFixture,
    ::testing::Values(make_tuple(4, "ABAB", 2), make_tuple(4, "AABABBA", 1), make_tuple(4, "ACTGAAAG", 1), make_tuple(7, "GAAATAAA", 1)));
