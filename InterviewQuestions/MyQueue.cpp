#include "stdafx.h"
#include "MyQueue.h"

template class MyQueue<int>;

template<class T>
MyQueue<T>::MyQueue()
{
}

template<class T>
MyQueue<T>::~MyQueue()
{
}

template<class T>
size_t MyQueue<T>::size()
{
	return front_.size() + back_.size();
}

template<class T>
bool MyQueue<T>::isEmpty()
{
	return size() == 0;
}

template<class T>
T MyQueue<T>::peek()
{
	if (!front_.isEmpty())
		return front_.peek();
	else if (!back_.isEmpty()) {
		back2front();
		return front_.peek();
	}
}

template<class T>
T MyQueue<T>::front()
{
	if (!front_.isEmpty())
		return front_.pop();
	else if (!back_.isEmpty()) {
		back2front();
		return front_.pop();
	}
}

template<class T>
void MyQueue<T>::push_back(T item)
{
	back_.push(item);
}

template<class T>
void MyQueue<T>::back2front()
{
	while (!back_.isEmpty())
		front_.push(back_.pop());
}