#pragma once
#include <set>
#include <memory>
#include <sstream>
#include <limits>
#include <concepts>
#include <cstdlib>
using namespace std;
template<typename T>
concept arithmetic_type = integral<T> || floating_point<T>;
template<typename T>
concept integral_type = integral<T>;
template <typename T>
class Node : public enable_shared_from_this<Node<T>>
{
protected:
	T m_item;
	shared_ptr<Node<T>> m_next, m_previous, m_left, m_right;
	T MinSubTreesDifference(shared_ptr<Node<T>>, T, T) requires arithmetic_type<T>;

public:
	Node();
	explicit Node(T item);
	Node(const Node &);
	Node(const shared_ptr<Node>);
	virtual ~Node();
	T Item() const;
	T Sum() const;
	shared_ptr<Node<T>> Next() const;
	shared_ptr<Node<T>> Previous() const;
	shared_ptr<Node<T>> Left() const;
	shared_ptr<Node<T>> Right() const;
	T MinSubTreesDifference(T sum = 0) requires arithmetic_type<T>;
	void SetPrevious(shared_ptr<Node<T>>);
	void SetNext(shared_ptr<Node<T>>);
	void SetLeft(shared_ptr<Node<T>>);
	void SetRight(shared_ptr<Node<T>>);
	void SetItem(T);
	Node<T>& operator=(T);
	Node<T>& operator=(Node<T> &);
	Node<T>& operator=(Node<T>);
	bool operator==(Node<T>) const;
	bool operator!=(Node<T> &) const;
	bool operator<(Node<T> &) const;
	bool operator>(Node<T> &) const;
	bool isLeaf() const;
	set<shared_ptr<Node<T>>> m_adjacents;
};