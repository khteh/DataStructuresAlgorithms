#include "pch.h"
using namespace std;
TEST(EulerianPathTests, EulerianPathTest) {
	vector<string> strings, strings1;
	vector<vector<string>> sgrid;
	sgrid = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
	strings = findItinerary(sgrid, string("JFK"));
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(5, strings.size());
	strings1.clear();
	strings1 = { "JFK", "MUC", "LHR", "SFO", "SJC" };
	ASSERT_EQ(strings1, strings);
	sgrid.clear();
	sgrid = { {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"} };
	strings = findItinerary(sgrid, string("JFK"));
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(6, strings.size());
	strings1.clear();
	strings1 = { "JFK", "ATL", "JFK", "SFO", "ATL", "SFO" };
	ASSERT_EQ(strings1, strings);
	sgrid.clear();
	sgrid = { {"EZE", "AXA"}, {"TIA", "ANU"}, {"ANU", "JFK"}, {"JFK", "ANU"}, {"ANU", "EZE"}, {"TIA", "ANU"}, {"AXA", "TIA"}, {"TIA", "JFK"}, {"ANU", "TIA"}, {"JFK", "TIA"} };
	strings = findItinerary(sgrid, string("JFK"));
	ASSERT_FALSE(strings.empty());
	ASSERT_EQ(11, strings.size());
	strings1.clear();
	strings1 = { "JFK", "ANU", "EZE", "AXA", "TIA", "ANU", "JFK", "TIA", "ANU", "TIA", "JFK" };
	ASSERT_EQ(strings1, strings);
}