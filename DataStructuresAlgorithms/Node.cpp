#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <set>
using namespace std;

template class Node<int>;
template class Node<long>;
template class Node<string>;
template class Node<size_t>;
template class Node<float>;
template class Node<double>;
template <typename T>
Node<T>::Node()
	: m_item(T()), m_previous(nullptr), m_next(nullptr), m_left(nullptr), m_right(nullptr)
{
}
template <typename T>
Node<T>::Node(T item)
	: m_item(item), m_previous(nullptr), m_next(nullptr), m_left(nullptr), m_right(nullptr)
{
}
template <typename T>
Node<T>::Node(const Node &node) // Shallow Copy !!! It will have runtime error with create/delete of objects
	: m_item(node.m_item), m_previous(node.m_previous), m_next(node.m_next), m_left(node.m_left), m_right(node.m_right)
{
}

template <typename T>
Node<T>::Node(const shared_ptr<Node> node) // Shallow Copy !!! It will have runtime error with create/delete of objects
	: m_item(node->m_item), m_previous(node->m_previous), m_next(node->m_next), m_left(node->m_left), m_right(node->m_right)
{
}

template <typename T>
Node<T>::~Node()
{
	// m_item = default(T);
}

template <typename T>
T Node<T>::Item()
{
	return m_item;
}
template <typename T>
shared_ptr<Node<T>> Node<T>::Previous() const
{
	return m_previous;
}
template <typename T>
shared_ptr<Node<T>> Node<T>::Next() const
{
	return m_next;
}

template <typename T>
shared_ptr<Node<T>> Node<T>::Left() const
{
	return m_left;
}

template <typename T>
shared_ptr<Node<T>> Node<T>::Right() const
{
	return m_right;
}
template <typename T>
T Node<T>::MinSubTreesDifference(shared_ptr<Node<T>> n, T sum, T subtreeSum)
{
	ostringstream oss;
	if constexpr (is_same_v<T, long> || is_same_v<T, int> || is_same_v<T, size_t>)
	{
		T adjustedSum = subtreeSum - n->Item();
		if (sum + n->Item() == adjustedSum)
			return 0;
		else if (sum + n->Item() > adjustedSum)
			return abs((long)sum - (long)subtreeSum);
		else
			return n->MinSubTreesDifference(sum);
	}
	else
	{
		oss << __FUNCTION__ << " is only applicable to integral types!";
		throw runtime_error(oss.str());
	}
}
template <typename T>
T Node<T>::MinSubTreesDifference(T sum)
{
	/*
			10
		11		5
	Diff: 15 - 11 = 4
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	ostringstream oss;
	if constexpr (is_same_v<T, long> || is_same_v<T, int> || is_same_v<T, size_t>)
	{
		if (!m_left && !m_right)
			return abs((long)sum - (long)m_item);
		else if (!m_left)
			return m_right->MinSubTreesDifference(sum + m_item);
		else if (!m_right)
			return m_left->MinSubTreesDifference(sum + m_item);
		T leftSum = m_left ? m_left->Sum() : 0;
		T rightSum = m_right ? m_right->Sum() : 0;
		sum += m_item;
		if (leftSum == rightSum)
			return 0;
		else if (leftSum < rightSum)
			return MinSubTreesDifference(m_right, sum + leftSum, rightSum);
		else
			return MinSubTreesDifference(m_left, sum + rightSum, leftSum);
	}
	else
	{
		oss << __FUNCTION__ << " is only applicable to integral types!";
		throw runtime_error(oss.str());
	}
}
template <typename T>
T Node<T>::Sum()
{
	T sum = m_item;
	if (m_left)
		sum += m_left->Sum();
	if (m_right)
		sum += m_right->Sum();
	return sum;
}
template <typename T>
void Node<T>::SetPrevious(shared_ptr<Node<T>> node)
{
	m_previous = node;
}
template <typename T>
void Node<T>::SetNext(shared_ptr<Node<T>> node)
{
	m_next = node;
	if (node)
		node->SetPrevious(this->shared_from_this());
	m_adjacents.insert(node);
}

template <typename T>
void Node<T>::SetLeft(shared_ptr<Node<T>> node)
{
	m_left = node;
}

template <typename T>
void Node<T>::SetRight(shared_ptr<Node<T>> node)
{
	m_right = node;
}

template <typename T>
void Node<T>::SetItem(T item)
{
	m_item = item;
}

template <typename T>
Node<T> &Node<T>::operator=(Node<T> &rhs)
{
	m_previous = rhs.Previous();
	m_item = rhs.Item();
	m_next = rhs.Next();
	m_left = rhs.Left();
	m_right = rhs.Right();
	return *this;
}

template <typename T>
bool Node<T>::operator==(Node<T> &rhs)
{
	return m_item == rhs.Item();
}

template <typename T>
bool Node<T>::operator!=(Node<T> &rhs)
{
	return !(*this == rhs);
}

template <typename T>
bool Node<T>::operator<(Node<T> &rhs)
{
	return m_item < rhs.Item();
}

template <typename T>
bool Node<T>::operator>(Node<T> &rhs)
{
	return m_item > rhs.Item();
}

template <typename T>
bool Node<T>::isLeaf()
{
	return !Next() && !Left() && !Right();
}