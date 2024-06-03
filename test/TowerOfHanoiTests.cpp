#include "pch.h"
using namespace std;
class ResetTowerOfHanoiTestFixture : public testing::TestWithParam<tuple<int, size_t, vector<size_t>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        towerCount = get<1>(GetParam());
        discs = get<2>(GetParam());
    }
    int ResetTowerOfHanoiTest()
    {
        return ResetTowerOfHanoi(towerCount, discs);
    }

protected:
    int _expected;
    size_t towerCount;
    vector<size_t> discs;
};
TEST_P(ResetTowerOfHanoiTestFixture, ResetTowerOfHanoiTests)
{
    ASSERT_EQ(this->_expected, this->ResetTowerOfHanoiTest());
}
INSTANTIATE_TEST_SUITE_P(
    ResetTowerOfHanoiTests,
    ResetTowerOfHanoiTestFixture,
    ::testing::Values(make_tuple(0, 4, vector<size_t>{1}), make_tuple(1, 4, vector<size_t>{2}), make_tuple(1, 4, vector<size_t>{2, 1}),
                      make_tuple(2, 4, vector<size_t>{2, 3}), make_tuple(3, 4, vector<size_t>{4, 3, 2, 1}), make_tuple(3, 4, vector<size_t>{1, 4, 1}),
                      make_tuple(4, 4, vector<size_t>{4, 2, 2, 1}), make_tuple(5, 4, vector<size_t>{1, 3, 3}), make_tuple(7, 4, vector<size_t>{2, 1, 3, 2}),
                      make_tuple(8, 4, vector<size_t>{2, 4, 4, 4}),
                      make_tuple(6, 4, vector<size_t>{2, 4, 2, 4}), make_tuple(10, 4, vector<size_t>{3, 1, 2, 1, 4}), make_tuple(11, 4, vector<size_t>{1, 1, 3, 1, 4}), make_tuple(14, 4, vector<size_t>{1, 4, 2, 4, 2, 2}), make_tuple(19, 4, vector<size_t>{1, 1, 3, 3, 1, 3, 2})));
