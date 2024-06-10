#include "pch.h"
using namespace std;
template <typename T1, typename T2>
class GameTheoryTestFixture
{
public:
    void SetUp(T1 expected, T2 var1)
    {
        _expected = expected;
        _data = var1;
    }

protected:
    GameTheory<T2> _game;
    T2 _data;
    T1 _expected;
};

class SolvabilityOfTheTilesGameTestFixture : public GameTheoryTestFixture<bool, vector<size_t>>, public testing::TestWithParam<tuple<bool, vector<size_t>>>
{
public:
    void SetUp() override
    {
        GameTheoryTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    bool SolvabilityOfTheTilesGameTest()
    {
        return _game.SolvabilityOfTheTilesGame(_data);
    }

protected:
    GameTheory<size_t> _game;
};
TEST_P(SolvabilityOfTheTilesGameTestFixture, SolvabilityOfTheTilesGameTests)
{
    ASSERT_EQ(this->_expected, this->SolvabilityOfTheTilesGameTest());
}
INSTANTIATE_TEST_SUITE_P(
    SolvabilityOfTheTilesGameTests,
    SolvabilityOfTheTilesGameTestFixture,
    ::testing::Values(make_tuple(true, vector<size_t>{3, 1, 2}), make_tuple(true, vector<size_t>{1, 3, 4, 2}), make_tuple(false, vector<size_t>{1, 2, 3, 5, 4}), make_tuple(true, vector<size_t>{4, 1, 3, 2}), make_tuple(false, vector<size_t>{1, 6, 5, 2, 3, 4})));
class SnakesAndLaddersGameTestFixture : public testing::TestWithParam<tuple<size_t, vector<vector<size_t>>, vector<vector<size_t>>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _ladders = get<1>(GetParam());
        _snakes = get<2>(GetParam());
    }
    size_t SnakesAndLaddersGameTest()
    {
        return _game.SnakesAndLaddersGameFast(_ladders, _snakes);
    }

protected:
    size_t _expected;
    vector<vector<size_t>> _ladders, _snakes;
    GameTheory<size_t> _game;
};
TEST_P(SnakesAndLaddersGameTestFixture, SnakesAndLaddersGameTests)
{
    ASSERT_EQ(this->_expected, this->SnakesAndLaddersGameTest());
}
INSTANTIATE_TEST_SUITE_P(
    SnakesAndLaddersGameTests,
    SnakesAndLaddersGameTestFixture,
    ::testing::Values(make_tuple(3, vector<vector<size_t>>{{32, 62}, {42, 68}, {12, 98}}, vector<vector<size_t>>{{95, 13}, {97, 25}, {93, 37}, {79, 27}, {75, 19}, {49, 47}, {67, 17}}),
                      make_tuple(5, vector<vector<size_t>>{{8, 52}, {6, 80}, {26, 42}, {2, 72}}, vector<vector<size_t>>{{51, 19}, {39, 11}, {37, 29}, {81, 3}, {59, 5}, {79, 23}, {53, 7}, {43, 33}, {77, 21}}),
                      make_tuple(3, vector<vector<size_t>>{{3, 5}, {7, 8}, {44, 56}, {36, 54}, {88, 91}, {77, 83}, {2, 4}, {9, 99}, {45, 78}, {31, 75}}, vector<vector<size_t>>{{10, 6}, {95, 90}, {96, 30}, {97, 52}, {98, 86}}),
                      make_tuple(3, vector<vector<size_t>>{{3, 54}, {37, 100}}, vector<vector<size_t>>{{56, 33}}),
                      make_tuple(17, vector<vector<size_t>>{{5, 6}}, vector<vector<size_t>>{{97, 95}}),
                      make_tuple(0, vector<vector<size_t>>{{3, 90}}, vector<vector<size_t>>{{99, 10}, {97, 20}, {98, 30}, {96, 40}, {95, 50}, {94, 60}, {93, 70}})));
template <typename T>
class NimGameFixture
{
protected:
    void SetUp(T expected, vector<T> data)
    {
        _expected = expected;
        _data = data;
    }
    size_t _expected;
    vector<T> _data;
    GameTheory<T> _game;
};

class NormalPlayNimTestFixture : public NimGameFixture<size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
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
class MisèrePlayNimTestFixture : public NimGameFixture<size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
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

class NimbleGameTestFixture : public NimGameFixture<size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
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

class CounterGameTestFixture : public GameTheoryTestFixture<size_t, long>, public testing::TestWithParam<tuple<size_t, long>>
{
public:
    void SetUp() override
    {
        GameTheoryTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    size_t CounterGameTest()
    {
        return _game.CounterGame(_data);
    }
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

class GameOfStonesTestFixture : public GameTheoryTestFixture<string, size_t>, public testing::TestWithParam<tuple<string, size_t>>
{
public:
    void SetUp() override
    {
        GameTheoryTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    string GameOfStonesTest()
    {
        return _game.GameOfStones(_data);
    }
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
class PermutationGameTestFixture : public GameTheoryTestFixture<bool, vector<size_t>>, public testing::TestWithParam<tuple<bool, vector<size_t>>>
{
public:
    void SetUp() override
    {
        GameTheoryTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    bool PermutationGameTest()
    {
        return _game.PermutationGame(_data);
    }

protected:
    GameTheory<size_t> _game;
};
TEST_P(PermutationGameTestFixture, PermutationGameTests)
{
    ASSERT_EQ(this->_expected, this->PermutationGameTest());
}
INSTANTIATE_TEST_SUITE_P(
    PermutationGameTests,
    PermutationGameTestFixture,
    ::testing::Values(make_tuple(true, vector<size_t>{1, 3, 2}), make_tuple(true, vector<size_t>{4, 2, 3, 1}), make_tuple(false, vector<size_t>{5, 3, 2, 1, 4}), make_tuple(false, vector<size_t>{11, 9, 10, 5, 8, 3, 2, 7, 6, 4, 1}), make_tuple(true, vector<size_t>{10, 7, 9, 2, 5, 8, 4, 1, 3, 6})));