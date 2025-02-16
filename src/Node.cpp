#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <set>
template class Node<int>;
template class Node<long>;
template class Node<string>;
template class Node<size_t>;
template class Node<float>;
template class Node<double>;
template <typename T>
Node<T>::Node()
	: _item(T()), _previous(nullptr), _next(nullptr), _left(nullptr), _right(nullptr)
{
}
template <typename T>
Node<T>::Node(T item)
	: _item(item), _previous(nullptr), _next(nullptr), _left(nullptr), _right(nullptr)
{
}
template <typename T>
Node<T>::Node(const Node &node) // Shallow Copy !!! It will have runtime error with create/delete of objects
	: _item(node._item), _previous(node._previous), _next(node._next), _left(node._left), _right(node._right)
{
}
template <typename T>
Node<T>::Node(Node &&node) // Move constructor
{
	node.Swap(*this);
}

template <typename T>
Node<T>::Node(const shared_ptr<Node> node) // Shallow Copy !!! It will have runtime error with create/delete of objects
	: _item(node->_item), _previous(node->_previous), _next(node->_next), _left(node->_left), _right(node->_right)
{
}

template <typename T>
Node<T>::~Node()
{
	// _item = default(T);
}
template <typename T>
void Node<T>::Swap(Node<T> &other)
{
	swap(_item, other._item);
	swap(_previous, other._previous);
	swap(_next, other._next);
	swap(_left, other._left);
	swap(_right, other._right);
}

template <typename T>
T Node<T>::Item() const
{
	return _item;
}
template <typename T>
shared_ptr<Node<T>> Node<T>::Previous() const
{
	return _previous;
}
template <typename T>
shared_ptr<Node<T>> Node<T>::Next() const
{
	return _next;
}

template <typename T>
shared_ptr<Node<T>> Node<T>::Left() const
{
	return _left;
}

template <typename T>
shared_ptr<Node<T>> Node<T>::Right() const
{
	return _right;
}
template <typename T>
T Node<T>::MinSubTreesDifference(shared_ptr<Node<T>> n, T sum, T subtreeSum)
	requires arithmetic_type<T>
{
	ostringstream oss;
	T adjustedSum = subtreeSum - n->Item();
	if (sum + n->Item() == adjustedSum)
		return 0;
	else if (sum + n->Item() > adjustedSum)
		return abs((double)sum - (double)subtreeSum);
	else
		return n->MinSubTreesDifference(sum);
}
template <typename T>
T Node<T>::MinSubTreesDifference(T sum)
	requires arithmetic_type<T>
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
	if (!_left && !_right)
		return abs((double)sum - (double)_item);
	else if (!_left)
		return _right->MinSubTreesDifference(sum + _item);
	else if (!_right)
		return _left->MinSubTreesDifference(sum + _item);
	T leftSum = _left ? _left->Sum() : 0;
	T rightSum = _right ? _right->Sum() : 0;
	sum += _item;
	if (leftSum == rightSum)
		return 0;
	else if (leftSum < rightSum)
		return MinSubTreesDifference(_right, sum + leftSum, rightSum);
	else
		return MinSubTreesDifference(_left, sum + rightSum, leftSum);
}
template <typename T>
T Node<T>::Sum() const
{
	T sum = _item;
	if (_left)
		sum += _left->Sum();
	if (_right)
		sum += _right->Sum();
	return sum;
}
template <typename T>
void Node<T>::SetPrevious(shared_ptr<Node<T>> node)
{
	_previous = node;
}
template <typename T>
void Node<T>::SetNext(shared_ptr<Node<T>> node)
{
	_next = node;
	if (node)
		node->SetPrevious(this->shared_from_this());
	m_adjacents.insert(node);
}

template <typename T>
void Node<T>::SetLeft(shared_ptr<Node<T>> node)
{
	_left = node;
}

template <typename T>
void Node<T>::SetRight(shared_ptr<Node<T>> node)
{
	_right = node;
}

template <typename T>
void Node<T>::SetItem(T item)
{
	_item = item;
}
template <typename T>
Node<T> &Node<T>::operator=(T item)
{
	_item = item;
	return *this;
}
#if 0
template <typename T>
Node<T> &Node<T>::operator=(const Node<T> &rhs) // Copy assignment operator
{
	_previous = rhs.Previous();
	_item = rhs.Item();
	_next = rhs.Next();
	_left = rhs.Left();
	_right = rhs.Right();
	return *this;
}
template <typename T>
Node<T> &Node<T>::operator=(Node<T> &&rhs) // Move assignment operator
{
	Node<T> tmp(move(rhs));
	tmp.Swap(*this);
	return *this;
}
#endif
/*
https://stackoverflow.com/questions/64378721/what-is-the-difference-between-the-copy-constructor-and-move-constructor-in-c
The above 2 operators can be implemented as 1 operator, like below.
This allows the caller to decide whether to construct the rhs parameter
using its copy constructor or move constructor...
*/
template <typename T>
Node<T> &Node<T>::operator=(Node<T> rhs)
{
	rhs.Swap(*this);
	return *this;
}
template <typename T>
bool Node<T>::operator==(Node<T> rhs) const
{
	return _item == rhs.Item();
}
template <typename T>
bool Node<T>::operator!=(Node<T> &rhs) const
{
	return !(*this == rhs);
}

template <typename T>
bool Node<T>::operator<(Node<T> &rhs) const
{
	return _item < rhs.Item();
}

template <typename T>
bool Node<T>::operator>(Node<T> &rhs) const
{
	return _item > rhs.Item();
}
template <typename T>
bool Node<T>::isLeaf() const
{
	return !Next() && !Left() && !Right();
}