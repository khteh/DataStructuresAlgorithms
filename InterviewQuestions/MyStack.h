#pragma once
#include "Node.h"

template <typename T>
class MyStack
{
private:
	shared_ptr<Node<T>> m_top;
	unsigned long m_size;

public:
	MyStack();
	MyStack(const MyStack &);
	~MyStack();
	bool isEmpty();
	T pop();
	void push(T);
	T peek();
	void clear();
	unsigned long size();
	void PrintStack();
};