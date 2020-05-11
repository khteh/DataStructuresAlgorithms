#include "stdafx.h"
#include "MyQueue.h"

template class MyQueue<int>;

template<typename T>
MyQueue<T>::MyQueue()
{
}
template<typename T>
MyQueue<T>::~MyQueue()
{
}

template<typename T>
size_t MyQueue<T>::size()
{
	return front_.size() + back_.size();
}

template<typename T>
bool MyQueue<T>::isEmpty()
{
	return size() == 0;
}

template<typename T>
T MyQueue<T>::peek()
{
	if (!front_.isEmpty())
		return front_.peek();
	else if (!back_.isEmpty()) {
		back2front();
		return front_.peek();
	}
	return T();
}

template<typename T>
T MyQueue<T>::front()
{
	if (!front_.isEmpty())
		return front_.pop();
	else if (!back_.isEmpty()) {
		back2front();
		return front_.pop();
	}
	return T();
}

template<typename T>
void MyQueue<T>::push_back(T item)
{
	back_.push(item);
}

template<typename T>
void MyQueue<T>::back2front()
{
	while (!back_.isEmpty())
		front_.push(back_.pop());
}