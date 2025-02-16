#pragma once
#include <set>
#include <memory>
#include <sstream>
#include <limits>
#include <concepts>
#include <cstdlib>
#include "GenericConstraints.h"
using namespace std;
template <typename T>
class Node : public enable_shared_from_this<Node<T>>
{
protected:
	T _item;
	shared_ptr<Node<T>> _next, _previous, _left, _right;
	T MinSubTreesDifference(shared_ptr<Node<T>>, T, T)
		requires arithmetic_type<T>;
	void Swap(Node &);

public:
	Node();
	explicit Node(T item);
	Node(const Node &); // Copy constructor
	Node(Node &&);		// Move constructor
	Node(const shared_ptr<Node>);
	virtual ~Node();
	T Item() const;
	T Sum() const;
	shared_ptr<Node<T>> Next() const;
	shared_ptr<Node<T>> Previous() const;
	shared_ptr<Node<T>> Left() const;
	shared_ptr<Node<T>> Right() const;
	T MinSubTreesDifference(T sum = 0)
		requires arithmetic_type<T>;
	void SetPrevious(shared_ptr<Node<T>>);
	void SetNext(shared_ptr<Node<T>>);
	void SetLeft(shared_ptr<Node<T>>);
	void SetRight(shared_ptr<Node<T>>);
	void SetItem(T);
	Node<T> &operator=(T);
	// Node<T> &operator=(const Node<T> &); // Copy assignment operator
	// Node<T> &operator=(Node<T> &&); // Move assignment operator
	/*
    The above 2 operators can be implemented as 1 operator, like below.
    This allows the caller to decide whether to construct the rhs parameter
    using its copy constructor or move constructor...	
	*/
	Node<T> &operator=(Node<T>);
	bool operator==(Node<T>) const;
	bool operator!=(Node<T> &) const;
	bool operator<(Node<T> &) const;
	bool operator>(Node<T> &) const;
	bool isLeaf() const;
	set<shared_ptr<Node<T>>> m_adjacents;
};