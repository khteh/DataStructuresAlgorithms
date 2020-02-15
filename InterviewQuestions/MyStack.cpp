#include "StdAfx.h"
#include "MyStack.h"
#include <iostream>
#include <string>
using namespace std;

template class MyStack<int>;
template class MyStack<long>;
template class MyStack<string>;

template<class T>
MyStack<T>::MyStack()
	: m_top(nullptr), m_size(0)
{
}

template<class T>
MyStack<T>::MyStack(const MyStack &stack)
{
	m_size = stack.m_size;
	m_top = stack.m_top;
}

template<class T>
MyStack<T>::~MyStack()
{
	clear();
}

template<class T>
bool MyStack<T>::isEmpty()
{
	return m_top == nullptr;
}

template<class T>
T MyStack<T>::pop()
{
	Node<T> *top = m_top;
	m_top = m_top->Next();
	m_size--;
	return top->Item();
}

template<class T>
void MyStack<T>::push(T item)
{
	Node<T>* node = m_top;
	m_top = new Node<T>(item);
	m_top->SetNext(node);
	m_size++;
}

template<class T>
T MyStack<T>::peek()
{
	if (!isEmpty())
		return m_top->Item();
}

template<class T>
unsigned long MyStack<T>::size()
{
	return m_size;
}

template<class T>
void MyStack<T>::clear()
{
	Node<T> *next;
	for (Node<T> *node = m_top; node;)
	{
		next = node->Next();
		delete node;
		node = nullptr;
		node = next;
	}
	m_top = nullptr;
	m_size = 0;
}

template<class T>
void MyStack<T>::PrintStack()
{
	for (Node<T> *node = m_top; node; node = node->Next())
		cout << node->Item() << " ";
	cout << endl;
}