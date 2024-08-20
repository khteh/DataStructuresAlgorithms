#include "stdafx.h"
#include "PriorityQueueMedian.h"

template class PriorityQueueMedian<long>;

template <typename T>
PriorityQueueMedian<T>::PriorityQueueMedian()
{
}

template <typename T>
PriorityQueueMedian<T>::~PriorityQueueMedian()
{
	Clear();
}
template <typename T>
void PriorityQueueMedian<T>::Clear()
{
	while (!_maxHeap.empty())
		_maxHeap.pop();
	while (!_minHeap.empty())
		_minHeap.pop();
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
template <typename T>
void PriorityQueueMedian<T>::Add(T item)
{
	if (_minHeap.empty() && _maxHeap.empty())
		_minHeap.push(item); // If start with maxHeap, the logic below has to toggle.
	else
	{
		if (item < _minHeap.top())
			_maxHeap.push(item);
		else
			_minHeap.push(item);
		if ((int)(_maxHeap.size() - _minHeap.size()) > 1)
		{
			_minHeap.push(_maxHeap.top());
			_maxHeap.pop();
		}
		else if ((int)(_minHeap.size() - _maxHeap.size()) > 1)
		{
			_maxHeap.push(_minHeap.top());
			_minHeap.pop();
		}
	}
}
template <typename T>
double PriorityQueueMedian<T>::GetMedian()
{
	if (_maxHeap.empty() && _minHeap.empty())
		return 0;
	else if (_maxHeap.empty())
		return _minHeap.top();
	else if (_minHeap.empty())
		return _maxHeap.top();
	else if (_minHeap.size() == _maxHeap.size())
		return (double)((double)_minHeap.top() + (double)_maxHeap.top()) / 2;
	else
		return _maxHeap.size() > _minHeap.size() ? _maxHeap.top() : _minHeap.top();
}