#pragma once
#include <queue>
#include <functional>
using namespace std;

/*
 maxHeap...Median...minHeap
 */
template<class T>
class PriorityQueueMedian
{
private:
	priority_queue<T, deque<T>> maxHeap; // Using default less<T> comparer. The list grows down. Top() returns maximum value.
	priority_queue<T, deque<T>, greater<T>> minHeap; // The list grows up. Top() returns minimum value.
public:
	PriorityQueueMedian();
	~PriorityQueueMedian();
	void Add(T);
	double GetMedian();
	void Clear();
};