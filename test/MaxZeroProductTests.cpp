#include "pch.h"
using namespace std;
TEST(DISABLED_MaxZeroProductTests, MaxZeroProductBruteForceTest)
{
	vector<long> data;
	data.push_back(2 * 2);
	data.push_back(2 * 2 * 2);
	data.push_back(2 * 2 * 2 * 2); // 4
	data.push_back(5 * 5);
	data.push_back(5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5); // 5
	ASSERT_EQ(5, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 5 * 5);
	data.push_back(2 * 2 * 5 * 5);
	data.push_back(2 * 2 * 2 * 5 * 5 * 5);
	ASSERT_EQ(6, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(7);
	data.push_back(15); // 3 * 5
	data.push_back(6);	// 2
	data.push_back(20); // 2 * 2 * 5
	data.push_back(5);	// 5
	data.push_back(10); // 2 * 5
	ASSERT_EQ(3, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data = {25, 10, 25, 10, 32};
	ASSERT_EQ(4, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data = {1, 1, 100};
	ASSERT_EQ(2, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data = {1, 4, 25};
	ASSERT_EQ(2, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data = {1, 1, 101};
	ASSERT_EQ(0, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data = {1, 25, 25};
	ASSERT_EQ(0, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data = {125, 100, 125, 100, 64};
	ASSERT_EQ(6, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.resize(9);
	ranges::generate(data, [i = 1]() mutable
					 { return i++; });
	ASSERT_EQ(1, MaxZeroProductBruteForce<long>(data));
	data.push_back(10);
	ASSERT_EQ(2, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(10);
	data.push_back(1000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	ASSERT_EQ(21, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(100000);
	data.push_back(10000000);
	data.push_back(10000000);
	data.push_back(10000000);
	ASSERT_EQ(21, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(1220703125);
	data.push_back(8192);
	ASSERT_EQ(13, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5); // 2^26
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	ASSERT_EQ(25, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^25
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);														   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);													   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);													   // 5^12
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);												   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);														   // 5^12
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^23
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(1000000000);
	data.push_back(1000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	ASSERT_EQ(26, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	data.push_back(2000000000);
	ASSERT_EQ(27, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5);
	data.push_back(5 * 5);
	data.push_back(5);
	data.push_back(1);
	data.push_back(2);
	ASSERT_EQ(1, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(1024);
	data.push_back(512);
	data.push_back(256);
	data.push_back(128);
	data.push_back(64);
	data.push_back(32);
	data.push_back(16);
	data.push_back(8);
	data.push_back(4);
	data.push_back(2);
	data.push_back(1);
	data.push_back(3);
	data.push_back(5);
	ASSERT_EQ(1, MaxZeroProductBruteForce<long>(data));
	data.clear();
	data.push_back(1024);
	data.push_back(512);
	data.push_back(256);
	data.push_back(128);
	data.push_back(64);
	data.push_back(32);
	data.push_back(5); // this
	data.push_back(8);
	data.push_back(4);
	data.push_back(2); // this
	data.push_back(1);
	data.push_back(3);
	data.push_back(16);
	ASSERT_EQ(1, MaxZeroProductBruteForce<long>(data));
	data.clear();
	random_device device;
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<uint64_t> dist(0, 1000000000);
	data.resize(100);
	ranges::generate(data, [&]
					 { return dist(device); });
	long result1 = MaxZeroProductBruteForce<long>(data);
	// long result2 = MaxZeroProduct(data);
	//  ASSERT_EQ(result1, result2); MaxZeroProduct still WIP
}