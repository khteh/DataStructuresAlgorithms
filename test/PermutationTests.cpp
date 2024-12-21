#include "pch.h"
using namespace std;
TEST(StringPermutationTests, StringPermutationTest)
{
    Permutation<string> permutation;
    set<string> permutations;
    permutations = permutation.Permute("abc");
    ASSERT_EQ(6, permutations.size());
    ASSERT_EQ(1, permutations.count("abc"));
    ASSERT_EQ(1, permutations.count("bac"));
    ASSERT_EQ(1, permutations.count("bca"));
    ASSERT_EQ(1, permutations.count("acb"));
    ASSERT_EQ(1, permutations.count("cba"));
    ASSERT_EQ(1, permutations.count("cab"));
    cout << "permutations of \"abc\" are: ";
    ranges::copy(permutations, ostream_iterator<string>(cout, " "));
    cout << endl;
    permutations.clear();

    OrderedMergedCombinations(permutations, string("Hey"), string("Bob"), string(""));
    cout << "Ordered permutations of \"HeyBob\" are: ";
    ranges::copy(permutations, ostream_iterator<string>(cout, " "));
    cout << endl;
    ASSERT_EQ(20, permutations.size());
    ASSERT_EQ(1, permutations.count("HeBoby"));
    ASSERT_EQ(1, permutations.count("HeBoyb"));
    ASSERT_EQ(1, permutations.count("HeByob"));
    ASSERT_EQ(1, permutations.count("HeyBob"));
    ASSERT_EQ(1, permutations.count("HBoeby"));
    ASSERT_EQ(1, permutations.count("HBoeyb"));
    ASSERT_EQ(1, permutations.count("HBobey"));
    ASSERT_EQ(1, permutations.count("HBeoby"));
    ASSERT_EQ(1, permutations.count("HBeoyb"));
    ASSERT_EQ(1, permutations.count("HBeyob"));
    ASSERT_EQ(1, permutations.count("BoHeby"));
    ASSERT_EQ(1, permutations.count("BoHeyb"));
    ASSERT_EQ(1, permutations.count("BoHbey"));
    ASSERT_EQ(1, permutations.count("BobHey"));
    ASSERT_EQ(1, permutations.count("BHoeby"));
    ASSERT_EQ(1, permutations.count("BHoeyb"));
    ASSERT_EQ(1, permutations.count("BHobey"));
    ASSERT_EQ(1, permutations.count("BHeoby"));
    ASSERT_EQ(1, permutations.count("BHeoyb"));
    ASSERT_EQ(1, permutations.count("BHeyob"));
}
class AbsolutePermutationTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _n = get<1>(GetParam());
        _k = get<2>(GetParam());
    }
    vector<long> AbsolutePermutationTest()
    {
        return _permutation.AbsolutePermutation(_n, _k);
    }

protected:
    Permutation<long> _permutation;
    vector<long> _expected;
    size_t _n, _k;
};
TEST_P(AbsolutePermutationTestFixture, AbsolutePermutationTests)
{
    ASSERT_EQ(this->_expected, this->AbsolutePermutationTest());
}
INSTANTIATE_TEST_SUITE_P(
    AbsolutePermutationTests,
    AbsolutePermutationTestFixture,
    ::testing::Values(make_tuple(ranges::iota_view(1, 11) | ranges::to<vector<long>>(), 10, 0), make_tuple(vector<long>{2, 1, 4, 3, 6, 5, 8, 7, 10, 9}, 10, 1)));

class ListPermutationTestFixture : public testing::TestWithParam<tuple<size_t, vector<long>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _var = get<1>(GetParam());
    }
    size_t ListPermutationTest()
    {
        set<vector<long>> permutations;
        permutations = _permutation.Permute(_var);
        /*
        for (set<vector<long>>::iterator it = permutations.begin(); it != permutations.end(); it++)
        {
            ranges::copy(*it, ostream_iterator<long>(cout, " "));
            cout << endl;
        }*/
        return permutations.size();
    }

protected:
    Permutation<long> _permutation;
    size_t _expected;
    vector<long> _var;
};
TEST_P(ListPermutationTestFixture, ListPermutationTests)
{
    ASSERT_EQ(this->_expected, this->ListPermutationTest());
}
INSTANTIATE_TEST_SUITE_P(
    ListPermutationTests,
    ListPermutationTestFixture,
    ::testing::Values(make_tuple(6, ranges::iota_view(1, 4) | ranges::to<vector<long>>()), make_tuple(120, ranges::iota_view(1, 6) | ranges::to<vector<long>>())));
class RangePermutationsTestFixture : public testing::TestWithParam<tuple<size_t, size_t, size_t, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _size = get<1>(GetParam());
        _resultSize = get<2>(GetParam());
        _step = get<3>(GetParam());
    }
    size_t RangePermutationsTest()
    {
        size_t ul = 1;
        set<size_t> uset;
        generate_n(inserter(uset, uset.end()), _size, [&ul]()
                   { return ul++; });
        return _permutation.RangePermutations(vector<size_t>{}, uset, _resultSize, _step).size();
    }

protected:
    Permutation<size_t> _permutation;
    size_t _expected, _size, _step, _resultSize;
};
TEST_P(RangePermutationsTestFixture, RangePermutationsTests)
{
    ASSERT_EQ(this->_expected, this->RangePermutationsTest());
}
INSTANTIATE_TEST_SUITE_P(
    RangePermutationsTests,
    RangePermutationsTestFixture,
    ::testing::Values(make_tuple(6, 3, 3, 1), make_tuple(6, 3, 2, 1), make_tuple(120, 5, 5, 1), make_tuple(5040, 7, 7, 1), make_tuple(362880, 9, 9, 1)));
class PermutationGameTestFixture : public testing::TestWithParam<tuple<bool, vector<size_t>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
    }
    bool PermutationGameTest()
    {
        return _permutation.PermutationGame(_data);
    }

protected:
    Permutation<size_t> _permutation;
    bool _expected;
    vector<size_t> _data;
};
TEST_P(PermutationGameTestFixture, PermutationGameTests)
{
    ASSERT_EQ(this->_expected, this->PermutationGameTest());
}
INSTANTIATE_TEST_SUITE_P(
    PermutationGameTests,
    PermutationGameTestFixture,
    ::testing::Values(make_tuple(true, vector<size_t>{1, 3, 2}), make_tuple(true, vector<size_t>{4, 2, 3, 1}), make_tuple(false, vector<size_t>{5, 3, 2, 1, 4}), make_tuple(false, vector<size_t>{11, 9, 10, 5, 8, 3, 2, 7, 6, 4, 1}), make_tuple(true, vector<size_t>{10, 7, 9, 2, 5, 8, 4, 1, 3, 6})));