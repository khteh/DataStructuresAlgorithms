#include "pch.h"
using namespace std;
TEST(HIndexTests, HIndexTest)
{
	vector<size_t> udata;
	udata = { 3, 0, 6, 1, 5 };
	ASSERT_EQ(3, hIndex(udata));
	udata.clear();
	udata = { 0, 1 };
	ASSERT_EQ(1, hIndex(udata));
	udata.clear();
	udata = { 1, 1 };
	ASSERT_EQ(1, hIndex(udata));
	udata.clear();
	udata = { 123 };
	ASSERT_EQ(1, hIndex(udata));
	udata.clear();
	udata = { 1, 1, 2 };
	ASSERT_EQ(1, hIndex(udata));
	udata.clear();
	udata = { 1, 2, 2 };
	ASSERT_EQ(2, hIndex(udata));
	udata.clear();
	udata = { 3, 2, 2 };
	ASSERT_EQ(2, hIndex(udata));
	udata.clear();
	udata = { 3, 3, 2 };
	ASSERT_EQ(2, hIndex(udata));
}