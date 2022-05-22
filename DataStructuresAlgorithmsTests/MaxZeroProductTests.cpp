#include "pch.h"
using namespace std;
TEST(MaxZeroProductTests, MaxZeroProductTest) {
	vector<int> data;
	data.push_back(2 * 2);
	data.push_back(2 * 2 * 2);
	data.push_back(2 * 2 * 2 * 2);
	data.push_back(5 * 5);
	data.push_back(5 * 5 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5);
	// assert(MaxZeroProduct(data) == 5);
	ASSERT_EQ(5, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 5 * 5);
	data.push_back(2 * 2 * 5 * 5);
	data.push_back(2 * 2 * 2 * 5 * 5 * 5);
	// assert(MaxZeroProduct(data) == 6);
	ASSERT_EQ(6, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(7);
	data.push_back(15); // 3 * 5
	data.push_back(6);	// 2
	data.push_back(20); // 2 * 2 * 5
	data.push_back(5);	// 5
	data.push_back(10); // 2 * 5
	// assert(MaxZeroProduct(data) == 3);
	ASSERT_EQ(3, MaxZeroProductBruteForce(data));
	data.clear();
	data = { 25, 10, 25, 10, 32 };
	// assert(MaxZeroProduct(data) == 4);
	ASSERT_EQ(4, MaxZeroProductBruteForce(data));
	data.clear();
	data = { 1, 1, 100 };
	// assert(MaxZeroProduct(data) == 2);
	ASSERT_EQ(2, MaxZeroProductBruteForce(data));
	data.clear();
	data = { 1, 4, 25 };
	// assert(MaxZeroProduct(data) == 2);
	ASSERT_EQ(2, MaxZeroProductBruteForce(data));
	data.clear();
	data = { 1, 1, 101 };
	// assert(MaxZeroProduct(data) == 0);
	ASSERT_EQ(0, MaxZeroProductBruteForce(data));
	data.clear();
	data = { 1, 25, 25 };
	// assert(MaxZeroProduct(data) == 0);
	ASSERT_EQ(0, MaxZeroProductBruteForce(data));
	data.clear();
	data = { 125, 100, 125, 100, 64 };
	// assert(MaxZeroProduct(data) == 6);
	ASSERT_EQ(6, MaxZeroProductBruteForce(data));
	data.clear();
	data.resize(9);
	generate(data.begin(), data.end(), [i = 1]() mutable { return i++; });
	// assert(MaxZeroProduct(data) == 1);
	ASSERT_EQ(1, MaxZeroProductBruteForce(data));
	data.push_back(10);
	// assert(MaxZeroProduct(data) == 2);
	ASSERT_EQ(2, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(10);
	data.push_back(1000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	// assert(MaxZeroProduct(data) == 21);
	ASSERT_EQ(21, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(100000);
	data.push_back(10000000);
	data.push_back(10000000);
	data.push_back(10000000);
	// assert(MaxZeroProduct(data) == 21);
	ASSERT_EQ(21, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(1220703125);
	data.push_back(8192);
	// assert(MaxZeroProduct(data) == 13);
	ASSERT_EQ(13, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5); // 2^26
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	// assert(MaxZeroProduct(data) == 25);
	ASSERT_EQ(25, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^25
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);														   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);															   // 5^12
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);													   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);													   // 5^12
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^24
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);												   // 5^12
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);														   // 5^12
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5); // 2^23
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2);
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 2 * 2);
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(100000000);
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5);
	data.push_back(1000000000);
	data.push_back(1000000);
	data.push_back(100000000);
	data.push_back(1000000000);
	// assert(MaxZeroProduct(data) == 26);
	ASSERT_EQ(26, MaxZeroProductBruteForce(data));
	data.clear();
	data.push_back(100000000);
	data.push_back(1000000000);
	data.push_back(1000000000);
	data.push_back(2000000000);
	// assert(MaxZeroProduct(data) == 27);
	ASSERT_EQ(27, MaxZeroProductBruteForce(data));
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
	// assert(MaxZeroProduct(data) == 1);
	ASSERT_EQ(1, MaxZeroProductBruteForce(data));
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
	// assert(MaxZeroProduct(data) == 1);
	ASSERT_EQ(1, MaxZeroProductBruteForce(data));
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
	// assert(MaxZeroProduct(data) == 1);
	ASSERT_EQ(1, MaxZeroProductBruteForce(data));
	data.clear();
	random_device device;
	// Uniform distribution used with vector
	// Distribution is [-5, 5] inclusive
	uniform_int_distribution<int> dist(0, 1000000000);
	data.resize(100);
	generate(data.begin(), data.end(), [&]
		{ return dist(device); });
	long result1 = MaxZeroProductBruteForce(data);
	long result2 = MaxZeroProduct(data);
	//ASSERT_EQ(result1, result2); MaxZeroProduct still WIP
}