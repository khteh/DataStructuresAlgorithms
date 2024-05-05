#include "pch.h"
using namespace std;
class NimGameFixture
{
protected:
    void SetUp(size_t expected, vector<size_t> data)
    {
        _expected = expected;
        _data = data;
    }
    size_t _expected;
    vector<size_t> _data;
    GameTheory _game;
};

class NormalPlayNimTestFixture : public NimGameFixture, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
    void SetUp() override
    {
        NimGameFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    size_t NormalPlayNimTest()
    {
        return _game.NormalPlayNim(_data);
    }
};
TEST_P(NormalPlayNimTestFixture, NormalPlayNimTests)
{
    ASSERT_EQ(this->_expected, this->NormalPlayNimTest());
}
INSTANTIATE_TEST_SUITE_P(
    NormalPlayNimTests,
    NormalPlayNimTestFixture,
    ::testing::Values(make_tuple(0, vector<size_t>{}),
                      make_tuple(1, vector<size_t>{1}),
                      make_tuple(0, vector<size_t>{1, 1}),
                      make_tuple(3, vector<size_t>{1, 1, 1}), // Take 1 from any of the 3 heaps
                      make_tuple(1, vector<size_t>{1, 2, 1}), // Remove 2 from the heap with 2 elements
                      make_tuple(1, vector<size_t>{2, 3})));
class MisèrePlayNimTestFixture : public NimGameFixture, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
    void SetUp() override
    {
        NimGameFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    size_t MisèrePlayNimTest()
    {
        return _game.MisèrePlayNim(_data);
    }
};
TEST_P(MisèrePlayNimTestFixture, MisèrePlayNimTests)
{
    ASSERT_EQ(this->_expected, this->MisèrePlayNimTest());
}
INSTANTIATE_TEST_SUITE_P(
    MisèrePlayNimTests,
    MisèrePlayNimTestFixture,
    ::testing::Values(make_tuple(0, vector<size_t>{}),
                      make_tuple(1, vector<size_t>{1}),
                      make_tuple(0, vector<size_t>{1, 1}),
                      make_tuple(1, vector<size_t>{2, 1, 3}),
                      make_tuple(0, vector<size_t>{9, 8, 4, 4, 4, 7}),
                      make_tuple(0, vector<size_t>{8, 7, 3, 6}),
                      make_tuple(0, vector<size_t>{8, 10})));

class NimbleGameTestFixture : public NimGameFixture, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
    void SetUp() override
    {
        NimGameFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    size_t NimbleGameTest()
    {
        return _game.NimbleGame(_data);
    }
};
TEST_P(NimbleGameTestFixture, NimbleGameTests)
{
    ASSERT_EQ(this->_expected, this->NimbleGameTest());
}
INSTANTIATE_TEST_SUITE_P(
    NimbleGameTests,
    NimbleGameTestFixture,
    ::testing::Values(make_tuple(1, vector<size_t>{0}),
                      make_tuple(0, vector<size_t>{0, 2, 3, 0, 6}),
                      make_tuple(1, vector<size_t>{10}),
                      make_tuple(0, vector<size_t>{826, 571, 236, 413, 212, 921, 948, 859, 985, 837}),
                      make_tuple(0, vector<size_t>{225, 441, 775}),
                      make_tuple(1, vector<size_t>{297, 452}),
                      make_tuple(0, vector<size_t>{279, 758, 334, 495, 288, 157, 924, 346, 663})));

class CounterGameTestFixture : public testing::TestWithParam<tuple<size_t, long>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
    }
    size_t CounterGameTest()
    {
        return _game.CounterGame(_data);
    }

protected:
    bool _expected;
    long _data;
    GameTheory _game;
};
TEST_P(CounterGameTestFixture, CounterGameTests)
{
    ASSERT_EQ(this->_expected, this->CounterGameTest());
}
INSTANTIATE_TEST_SUITE_P(
    CounterGameTests,
    CounterGameTestFixture,
    ::testing::Values(make_tuple(true, 6),
                      make_tuple(false, 8),
                      make_tuple(false, 132),
                      make_tuple(true, 1246326493)));

class GameOfStonesTestFixture : public testing::TestWithParam<tuple<string, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
    }
    string GameOfStonesTest()
    {
        return _game.GameOfStones(_data);
    }

protected:
    string _expected;
    size_t _data;
    GameTheory _game;
};
TEST_P(GameOfStonesTestFixture, GameOfStonesTests)
{
    ASSERT_EQ(this->_expected, this->GameOfStonesTest());
}
INSTANTIATE_TEST_SUITE_P(
    GameOfStonesTests,
    GameOfStonesTestFixture,
    ::testing::Values(make_tuple("Second", 0),
                      make_tuple("Second", 1),
                      make_tuple("First", 2),
                      make_tuple("First", 3),
                      make_tuple("First", 4),
                      make_tuple("First", 5),
                      make_tuple("First", 6),
                      make_tuple("Second", 7),
                      make_tuple("Second", 8),
                      make_tuple("First", 9),
                      make_tuple("First", 10),
                      make_tuple("First", 11),
                      make_tuple("First", 12),
                      make_tuple("First", 13),
                      make_tuple("Second", 14)));
