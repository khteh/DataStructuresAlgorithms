#pragma once
using namespace std;
template <typename T>
class Node : public enable_shared_from_this<Node<T>>
{
protected:
	T _item;
	shared_ptr<Node<T>> _left, _right, _next;
	weak_ptr<Node<T>> _previous, _parent; // Use weak_ptr to prevent circular references which results in memory leaks
	T MinSubTreesDifference(shared_ptr<Node<T>>, T, T)
		requires arithmetic_type<T>;
	void Swap(Node &);
	set<shared_ptr<Node<T>>> _adjacents;

public:
	Node();
	explicit Node(T);
	Node(const Node &); // Copy constructor
	Node(Node &&);		// Move constructor
	Node(const shared_ptr<Node>);
	virtual ~Node();
	T Item() const;
	T Sum() const;
	shared_ptr<Node<T>> Next() const;
	shared_ptr<Node<T>> Parent() const;
	shared_ptr<Node<T>> Previous() const;
	shared_ptr<Node<T>> Left() const;
	shared_ptr<Node<T>> Right() const;
	T MinSubTreesDifference(T sum = 0)
		requires arithmetic_type<T>;
	void SetParent(shared_ptr<Node<T>>);
	void SetPrevious(shared_ptr<Node<T>>);
	void SetNext(shared_ptr<Node<T>>);
	void SetLeft(shared_ptr<Node<T>>);
	void SetRight(shared_ptr<Node<T>>);
	void SetItem(T);
	Node<T> &operator=(T);
	// Node<T> &operator=(const Node<T> &); // Copy assignment operator https://stackoverflow.com/questions/72345198/c20-unable-to-satisfy-constraint-for-rangesremove-if
	// Node<T> &operator=(Node<T> &&); // Move assignment operator
	/*
	https://stackoverflow.com/questions/64378721/what-is-the-difference-between-the-copy-constructor-and-move-constructor-in-c
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
	typedef typename set<shared_ptr<Node<T>>>::const_iterator IteratorType;
	IteratorType AdjacentsStart() const;
	IteratorType AdjacentsEnd() const;
};