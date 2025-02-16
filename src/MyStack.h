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
	shared_ptr<Node<T>> _top;
	size_t _size;
	void Swap(MyStack &);

public:
	MyStack();
	MyStack(const MyStack &); // Copy constructor
	MyStack(MyStack &&);	  // Move constructor
	virtual ~MyStack();
	bool isEmpty() const;
	T pop();
	void push(T);
	bool Has(T) const;
	T peek() const;
	void clear();
	size_t size() const;
	void PrintStack();
	static void SortStack(MyStack<T> &, MyStack<T> &, sort_order_t);
};