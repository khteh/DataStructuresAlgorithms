#include "StdAfx.h"
#include "Node.h"
#include <iostream>
#include <set>
using namespace std;

template class Node<int>;
template class Node<long>;
template class Node<string>;

template<class T>
Node<T>::Node(T item)
	:m_item(item), m_previous(nullptr), m_next(nullptr), m_left(nullptr), m_right(nullptr)
{
}

template<class T>
Node<T>::Node(const Node &node) // Shallow Copy !!! It will have runtime error with create/delete of objects
	: m_item(node.m_item)
	, m_previous(node.m_previous)
	, m_next(node.m_next)
	, m_left(node.m_left)
	, m_right(node.m_right)
{
}

template<class T>
Node<T>::Node(const Node *node) // Shallow Copy !!! It will have runtime error with create/delete of objects
	: m_item(node->m_item)
	, m_previous(node->m_previous)
	, m_next(node->m_next)
	, m_left(node->m_left)
	, m_right(node->m_right)
{
}

template<class T>
Node<T>::~Node()
{
	//m_item = default(T);
}

template<class T>
T Node<T>::Item()
{
	return m_item;
}
template<class T>
Node<T>* Node<T>::Previous()
{
	return m_previous;
}
template<class T>
Node<T> *Node<T>::Next()
{
	return m_next;
}

template<class T>
Node<T> *Node<T>::Left()
{
	return m_left;
}

template<class T>
Node<T> *Node<T>::Right()
{
	return m_right;
}
template<class T>
void Node<T>::SetPrevious(Node<T>* node)
{
	m_previous = node;
}
template<class T>
void Node<T>::SetNext(Node<T> *node)
{
	m_next = node;
	if (node)
		node->SetPrevious(this);
	m_adjacents.insert(node);
}

template<class T>
void Node<T>::SetLeft(Node<T> *node)
{
	m_left = node;
}

template<class T>
void Node<T>::SetRight(Node<T> *node)
{
	m_right = node;
}

template<class T>
void Node<T>::SetItem(T item)
{
	m_item = item;
}

template<class T>
Node<T>& Node<T>::operator=(Node<T>& rhs)
{
	m_previous = rhs.Previous();
	m_item = rhs.Item();
	m_next = rhs.Next();
	m_left = rhs.Left();
	m_right = rhs.Right();
	return *this;
}

template<class T>
bool Node<T>::operator==(Node<T>& rhs)
{
	return m_item == rhs.Item() &&
	m_next == rhs.Next() &&
	m_previous == rhs.Previous() &&
	m_left == rhs.Left() &&
	m_right == rhs.Right();
}

template<class T>
bool Node<T>::operator!=(Node<T>& rhs)
{
	return !(*this == rhs);
}

template<class T>
bool Node<T>::operator<(Node<T>& rhs)
{
	return m_item < rhs.Item();
}

template<class T>
bool Node<T>::operator>(Node<T>& rhs)
{
	return m_item > rhs.Item();
}

template<class T>
bool Node<T>::isLeaf()
{
	return !Next() && !Left() && !Right();
}