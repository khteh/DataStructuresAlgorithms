#include "stdafx.h"
#include "MyStack.h"
#include <iostream>
#include <string>
using namespace std;
template class MyStack<size_t>;
template class MyStack<int>;
template class MyStack<long>;
template class MyStack<string>;
template <typename T>
MyStack<T>::MyStack()
	: m_top(nullptr), m_size(0)
{
}

template <typename T>
MyStack<T>::MyStack(const MyStack &stack)
{
	m_size = stack.m_size;
	m_top = stack.m_top;
}

template <typename T>
MyStack<T>::~MyStack()
{
	clear();
}

template <typename T>
bool MyStack<T>::isEmpty() const
{
	return !m_top;
}

template <typename T>
T MyStack<T>::pop()
{
	shared_ptr<Node<T>> top = m_top;
	m_top = m_top->Next();
	m_size--;
	if (!m_size)
		m_top = nullptr;
	return top->Item();
}

template <typename T>
void MyStack<T>::push(T item)
{
	shared_ptr<Node<T>> node = m_top;
	m_top = make_shared<Node<T>>(item);
	m_top->SetNext(node);
	m_size++;
}

template <typename T>
T MyStack<T>::peek() const
{
	return !isEmpty() ? m_top->Item() : numeric_limits<T>::max();
}

template <typename T>
size_t MyStack<T>::size() const
{
	return m_size;
}

template <typename T>
void MyStack<T>::clear()
{
	shared_ptr<Node<T>> next;
	for (shared_ptr<Node<T>> node = m_top; node;)
	{
		next = node->Next();
		node.reset();
		node = next;
	}
	m_top.reset();
	m_size = 0;
}
template <typename T>
bool MyStack<T>::Has(T item) const
{
	for (shared_ptr<Node<T>> node = m_top; node; node = node->Next())
		if (node->Item() == item)
			return true;
	return false;
}
template <typename T>
void MyStack<T>::PrintStack()
{
	for (shared_ptr<Node<T>> node = m_top; node; node = node->Next())
		cout << node->Item() << " ";
	cout << endl;
}
template <typename T>
void MyStack<T>::SortStack(MyStack<T> &src, MyStack<T> &dest, sort_order_t order)
{
	T item = T();
	while (!src.isEmpty())
	{
		item = src.pop();
		switch (order)
		{
		case SortOrder::SORT_ASCENDING: // Value grows from bottom of stack to top of stack
			while (!dest.isEmpty() && item < dest.peek())
				src.push(dest.pop());
			break;
		case SortOrder::SORT_DESCENDING: // Value shrinks from bottom of stack to top of stack
			while (!dest.isEmpty() && item > dest.peek())
				src.push(dest.pop());
			break;
		default:
			throw invalid_argument("Invalid sort order");
			break;
		}
		dest.push(item);
	}
}
