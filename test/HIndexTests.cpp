#include "pch.h"
using namespace std;
class HIndexTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t HIndexTest()
	{
		return hIndex(_data);
	}

protected:
	size_t _expected;
	vector<size_t> _data;
};
TEST_P(HIndexTestFixture, HIndexTests)
{
	ASSERT_EQ(this->_expected, this->HIndexTest());
}
INSTANTIATE_TEST_SUITE_P(
	HIndexTests,
	HIndexTestFixture,
	::testing::Values(make_tuple(3, vector<size_t>{3, 0, 6, 1, 5}), make_tuple(1, vector<size_t>{0, 1}), make_tuple(1, vector<size_t>{1, 1}), make_tuple(1, vector<size_t>{123}), make_tuple(1, vector<size_t>{1, 1, 2}), make_tuple(2, vector<size_t>{1, 2, 2}), make_tuple(2, vector<size_t>{3, 2, 2}), make_tuple(2, vector<size_t>{3, 3, 2})));
