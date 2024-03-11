#include "pch.h"
using namespace std;
class MaxNonDivisableSubsetTestFixture : public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
        _k = get<0>(GetParam());
		_expected = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	size_t MaxNonDivisableSubsetTest()
	{
		return MaxNonDivisableSubset(_data, _k);
	}

protected:
	vector<size_t> _data;
    size_t _k;
	size_t _expected;
};
TEST_P(MaxNonDivisableSubsetTestFixture, MaxNonDivisableSubsetTests)
{
	ASSERT_EQ(this->_expected, this->MaxNonDivisableSubsetTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxNonDivisableSubsetTests,
	MaxNonDivisableSubsetTestFixture,
	::testing::Values(make_tuple(3, 3, vector<size_t>{1,2,3,4,5,6}),
					  make_tuple(6, 8, vector<size_t>{12 ,6 ,1, 9, 13, 15, 10, 21, 14, 32, 5, 8, 23, 19}),
                      make_tuple(3, 3, vector<size_t>{1, 7, 2, 4})
                      ));