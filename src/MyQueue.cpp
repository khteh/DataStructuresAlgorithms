#include "pch.h"
#include "MyQueue.h"
template class MyQueue<int>;

template <typename T>
MyQueue<T>::MyQueue()
{
}
template <typename T>
MyQueue<T>::~MyQueue()
{
}

template <typename T>
size_t MyQueue<T>::size()
{
	return _front.size() + _back.size();
}

template <typename T>
bool MyQueue<T>::isEmpty()
{
	return size() == 0;
}

template <typename T>
T MyQueue<T>::peek()
{
	if (!_front.isEmpty())
		return _front.peek();
	else if (!_back.isEmpty())
	{
		back2front();
		return _front.peek();
	}
	return numeric_limits<T>::min();
}

template <typename T>
T MyQueue<T>::front()
{
	if (!_front.isEmpty())
		return _front.pop();
	else if (!_back.isEmpty())
	{
		back2front();
		return _front.pop();
	}
	return numeric_limits<T>::min();
}

template <typename T>
void MyQueue<T>::push_back(T item)
{
	_back.push(item);
}

template <typename T>
void MyQueue<T>::back2front()
{
	while (!_back.isEmpty())
		_front.push(_back.pop());
}