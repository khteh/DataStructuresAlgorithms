#pragma once
/*
 maxHeap...Median...minHeap
 */
template <typename T>
class PriorityQueueMedian
{
private:
	priority_queue<T> _maxHeap;						   // Using default less<T> comparer. The list grows down. Top() returns maximum value.
	priority_queue<T, vector<T>, greater<T>> _minHeap; // The list grows up. Top() returns minimum value.
public:
	PriorityQueueMedian();
	~PriorityQueueMedian();
	void Add(T);
	double GetMedian();
	void Clear();
};