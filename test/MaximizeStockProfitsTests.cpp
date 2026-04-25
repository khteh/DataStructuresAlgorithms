#include "pch.h"
using namespace std;
template <typename T1, typename T2>
class MaximizeStockProfitsTestFixture
{
public:
    void SetUp(T1 expected, vector<T2> data)
    {
        _expected = expected;
        _data = data;
    }

protected:
    MaximizeStockProfits<T2> _stock;
    vector<T2> _data;
    T1 _expected;
};
class MaxProfitK1TestFixture : public MaximizeStockProfitsTestFixture<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfitsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long MaxProfitK1Test()
    {
        return _stock.MaxProfitK1(_data);
    }
};
TEST_P(MaxProfitK1TestFixture, MaxProfitK1Tests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitK1Test());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitK1Tests,
    MaxProfitK1TestFixture,
    ::testing::Values(make_tuple(5, vector<long>{7, 1, 5, 3, 6, 4}), make_tuple(0, vector<long>{7, 6, 4, 3, 1}), make_tuple(2, vector<long>{2, 4, 1})));
class MaxProfitK2TestFixture : public MaximizeStockProfitsTestFixture<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfitsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long MaxProfitK2Test()
    {
        return _stock.MaxProfitK2(_data);
    }
};
TEST_P(MaxProfitK2TestFixture, MaxProfitK2Tests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitK2Test());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitK2Tests,
    MaxProfitK2TestFixture,
    ::testing::Values(make_tuple(6, vector<long>{3, 3, 5, 0, 0, 3, 1, 4}), make_tuple(4, vector<long>{1, 2, 3, 4, 5}), make_tuple(0, vector<long>{7, 6, 4, 3, 1})));
class MaxProfitKInfinityTestFixture : public MaximizeStockProfitsTestFixture<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfitsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long MaxProfitKInfinityTest()
    {
        return _stock.MaxProfitKInfinity(_data);
    }
};
TEST_P(MaxProfitKInfinityTestFixture, MaxProfitKInfinityTests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitKInfinityTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitKInfinityTests,
    MaxProfitKInfinityTestFixture,
    ::testing::Values(make_tuple(7, vector<long>{7, 1, 5, 3, 6, 4}), make_tuple(4, views::iota(1, 6) | ranges::to<vector<long>>()), make_tuple(0, vector<long>{5, 4, 3, 2, 1}),
                      make_tuple(1, vector<long>{1, 2}), make_tuple(0, vector<long>{1, 1})));

template <typename T1, typename T2, typename T3>
class MaximizeStockProfits2ParamsTestFixture
{
public:
    void SetUp(T1 expected, T2 var, vector<T3> data)
    {
        _expected = expected;
        _var = var;
        _data = data;
    }

protected:
    MaximizeStockProfits<T3> _stock;
    vector<T3> _data;
    T1 _expected;
    T2 _var;
};

class MaxProfitKArbitraryTestFixture : public MaximizeStockProfits2ParamsTestFixture<long, size_t, long>, public testing::TestWithParam<tuple<long, size_t, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfits2ParamsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
    }
    long MaxProfitKArbitraryTest()
    {
        return _stock.MaxProfitKArbitrary(_data, _var);
    }
};
TEST_P(MaxProfitKArbitraryTestFixture, MaxProfitKArbitraryTests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitKArbitraryTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitKArbitraryTests,
    MaxProfitKArbitraryTestFixture,
    ::testing::Values(make_tuple(2, 2, vector<long>{2, 4, 1}), make_tuple(7, 2, vector<long>{3, 2, 6, 5, 0, 3})));

class MaxProfitKInfinityCoolDownTestFixture : public MaximizeStockProfitsTestFixture<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfitsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long MaxProfitKInfinityCoolDownTest()
    {
        return _stock.MaxProfitKInfinityCoolDown(_data);
    }
};
TEST_P(MaxProfitKInfinityCoolDownTestFixture, MaxProfitKInfinityCoolDownTests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitKInfinityCoolDownTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitKInfinityCoolDownTests,
    MaxProfitKInfinityCoolDownTestFixture,
    ::testing::Values(make_tuple(3, vector<long>{1, 2, 3, 0, 2}), make_tuple(6, vector<long>{1, 2, 3, 0, 1, 5}), make_tuple(9, vector<long>{1, 2, 6, 0, 1, 5})));

class MaxProfitKInfinityWithFeeTestFixture : public MaximizeStockProfits2ParamsTestFixture<long, long, long>, public testing::TestWithParam<tuple<long, long, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfits2ParamsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
    }
    long MaxProfitKInfinityWithFeeTest()
    {
        return _stock.MaxProfitKInfinityWithFee(_data, _var);
    }
};
TEST_P(MaxProfitKInfinityWithFeeTestFixture, MaxProfitKInfinityWithFeeTests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitKInfinityWithFeeTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitKInfinityWithFeeTests,
    MaxProfitKInfinityWithFeeTestFixture,
    ::testing::Values(make_tuple(8, 2, vector<long>{1, 3, 2, 8, 4, 9}), make_tuple(6, 3, vector<long>{1, 3, 7, 5, 10, 3})));

class MaxProfitTestFixture : public MaximizeStockProfitsTestFixture<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
    void SetUp() override
    {
        MaximizeStockProfitsTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long MaxProfitTest()
    {
        return _stock.MaxProfit(_data);
    }
};
TEST_P(MaxProfitTestFixture, MaxProfitTests)
{
    ASSERT_EQ(this->_expected, this->MaxProfitTest());
}
INSTANTIATE_TEST_SUITE_P(
    MaxProfitTests,
    MaxProfitTestFixture,
    ::testing::Values(make_tuple(0, vector<long>{5, 3, 2}),
                      make_tuple(197, vector<long>{1, 2, 100}), // (100 - 1 = 99) + (100 - 2 = 98) = 197
                      make_tuple(3, vector<long>{1, 3, 1, 2})));
