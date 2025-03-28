#pragma once
#include "MyStack.h"
template <typename T>
class MyQueue
{
private:
	MyStack<T> _front;
	MyStack<T> _back;
	void back2front();

public:
	MyQueue();
	virtual ~MyQueue();
	T front();
	T peek();
	void push_back(T);
	size_t size();
	bool isEmpty();
};
