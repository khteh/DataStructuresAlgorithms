#include "StdAfx.h"
#include "PriorityQueueMedian.h"

template class PriorityQueueMedian<long>;

template<class T>
PriorityQueueMedian<T>::PriorityQueueMedian()
{
}

template<class T>
PriorityQueueMedian<T>::~PriorityQueueMedian()
{
	Clear();
}
template<class T>
void PriorityQueueMedian<T>::Clear()
{
	while (!maxHeap.empty())
		maxHeap.pop();
	while (!minHeap.empty())
		minHeap.pop();
}
/*
 maxHeap...Median...minHeap
 */
template<class T>
void PriorityQueueMedian<T>::Add(T item)
{
	if (!minHeap.size() && !maxHeap.size())
		maxHeap.push(item);
	else {
		if (item > maxHeap.top())
			minHeap.push(item);
		else
			maxHeap.push(item);
		if ((int)(maxHeap.size() - minHeap.size()) > 1) {
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		} else if ((int)(minHeap.size() - maxHeap.size()) > 1) {
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
	}
}

template<class T>
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