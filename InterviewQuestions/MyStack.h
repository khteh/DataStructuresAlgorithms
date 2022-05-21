#pragma once
#include "Node.h"
typedef enum class SortOrder
{
	SORT_ASCENDING,
	SORT_DESCENDING
} sort_order_t;

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
	static void SortStack(MyStack<T>&, MyStack<T>&, sort_order_t);
};