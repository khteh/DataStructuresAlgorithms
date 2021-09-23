#include "stdafx.h"
#include "PriorityQueueMedian.h"

template class PriorityQueueMedian<long>;

template<typename T>
PriorityQueueMedian<T>::PriorityQueueMedian()
{
}

template<typename T>
PriorityQueueMedian<T>::~PriorityQueueMedian()
{
	Clear();
}
template<typename T>
void PriorityQueueMedian<T>::Clear()
{
	while (!maxHeap.empty())
		maxHeap.pop();
	while (!minHeap.empty())
		minHeap.pop();
}
/*
 maxHeap...Median...minHeap
	pqueue.Add(6);
	pqueue.Add(5);
	pqueue.Add(1);
	pqueue.Add(3);
	pqueue.Add(2);
	pqueue.Add(7);
Min     Max
6		5
6		5 1
6		5 3 1
5 6		3 1
5 6		3 2 1
5 6 7	3 2 1 <= Median: 8
	pqueue.Add(8)
5 6 7 8	3 2 1 <= Median: 5
*/
template<typename T>
void PriorityQueueMedian<T>::Add(T item)
{
	if (minHeap.empty() && maxHeap.empty())
		minHeap.push(item); // If start with maxHeap, the logic below has to toggle.
	else {
		if (item < minHeap.top())
			maxHeap.push(item);
		else
			minHeap.push(item);
		if ((int)(maxHeap.size() - minHeap.size()) > 1) {
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		} else if ((int)(minHeap.size() - maxHeap.size()) > 1) {
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
	}
}

template<typename T>
double PriorityQueueMedian<T>::GetMedian()
{
	if (maxHeap.empty() && minHeap.empty())
		return 0;
	else if (maxHeap.empty())
		return minHeap.top();
	else if (minHeap.empty())
		return maxHeap.top();
	else if (minHeap.size() == maxHeap.size())
		return (double)((double)minHeap.top() + (double)maxHeap.top()) / 2;
	else
		return maxHeap.size() > minHeap.size() ? maxHeap.top() : minHeap.top();
}