#include "pch.h"
using namespace std;
class EulerianPathTestFixture : public testing::TestWithParam<tuple<vector<string>, vector<vector<string>>, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_paths = get<1>(GetParam());
		_start = get<2>(GetParam());
	}
	vector<string> EulerianPathTest()
	{
		return FindItinerary(_paths, _start);
	}

protected:
	vector<string> _expected;
	vector<vector<string>> _paths;
	string _start;
};
TEST_P(EulerianPathTestFixture, EulerianPathTests)
{
	ASSERT_EQ(this->_expected, this->EulerianPathTest());
}
INSTANTIATE_TEST_SUITE_P(
	EulerianPathTests,
	EulerianPathTestFixture,
	::testing::Values(make_tuple(vector<string>{"JFK", "MUC", "LHR", "SFO", "SJC"}, vector<vector<string>>{{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}, "JFK"),
					  make_tuple(vector<string>{"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"}, vector<vector<string>>{{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}, "JFK"),
					  make_tuple(vector<string>{"JFK", "ANU", "EZE", "AXA", "TIA", "ANU", "JFK", "TIA", "ANU", "TIA", "JFK"}, vector<vector<string>>{{"EZE", "AXA"}, {"TIA", "ANU"}, {"ANU", "JFK"}, {"JFK", "ANU"}, {"ANU", "EZE"}, {"TIA", "ANU"}, {"AXA", "TIA"}, {"TIA", "JFK"}, {"ANU", "TIA"}, {"JFK", "TIA"}}, "JFK")));
