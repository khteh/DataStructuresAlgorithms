#include "pch.h"
using namespace std;
class MinimumLossTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long MinimumLossTest()
	{
		return MinimumLoss(_data);
	}

protected:
	vector<long> _data;
	long _expected;
};
TEST_P(MinimumLossTestFixture, MinimumLossTests)
{
	ASSERT_EQ(this->_expected, this->MinimumLossTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinimumLossTests,
	MinimumLossTestFixture,
	::testing::Values(make_tuple(2, vector<long>{5, 10, 3}),
					  make_tuple(2, vector<long>{20, 7, 8, 2, 5}),
                      make_tuple(1, vector<long>{2, 3, 4, 1})
                      ));