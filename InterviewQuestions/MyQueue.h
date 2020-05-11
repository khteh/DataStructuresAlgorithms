#pragma once
#include "MyStack.h"
template<class T>
class MyQueue
{
private:
	MyStack<T> front_;
	MyStack<T> back_;
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

