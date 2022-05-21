#include "pch.h"
using namespace std;
TEST(QueueTests, QueueTest) {
	MyQueue<int> myQueue;
	myQueue.push_back(-1);
	myQueue.push_back(0);
	myQueue.push_back(10);
	ASSERT_EQ(3, myQueue.size());
	ASSERT_EQ(-1, myQueue.front());
	ASSERT_EQ(2, myQueue.size());
	ASSERT_EQ(0, myQueue.front());
	ASSERT_EQ(1, myQueue.size());
	ASSERT_EQ(10, myQueue.front());
	ASSERT_EQ(0, myQueue.size());
}