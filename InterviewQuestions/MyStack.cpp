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
bool MyStack<T>::isEmpty()
{
	return !m_top;
}

template <typename T>
T MyStack<T>::pop()
{
	shared_ptr<Node<T>> top = m_top;
	m_top = m_top->Next();
	m_size--;
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
T MyStack<T>::peek()
{
	return !isEmpty() ? m_top->Item() : numeric_limits<T>::max();
}

template <typename T>
unsigned long MyStack<T>::size()
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
void MyStack<T>::PrintStack()
{
	for (shared_ptr<Node<T>> node = m_top; node; node = node->Next())
		cout << node->Item() << " ";
	cout << endl;
}