#pragma once
#include <set>
#include <memory>
using namespace std;

template<class T>
class Node : public enable_shared_from_this<Node<T>>
{
protected:
	T m_item;
	shared_ptr<Node<T>> m_next, m_previous, m_left, m_right;
public:
	explicit Node(T item);
	Node(const Node &);
	Node(const shared_ptr<Node>);
	virtual ~Node();
	T Item();
	shared_ptr<Node<T>> Next();
	shared_ptr<Node<T>> Previous();
	shared_ptr<Node<T>> Left();
	shared_ptr<Node<T>> Right();
	void SetPrevious(shared_ptr<Node<T>>);
	void SetNext(shared_ptr<Node<T>>);
	void SetLeft(shared_ptr<Node<T>>);
	void SetRight(shared_ptr<Node<T>>);
	void SetItem(T);
	Node<T>& operator=(Node<T>&);
	bool operator==(Node<T>&);
	bool operator!=(Node<T>&);
	bool operator<(Node<T>&);
	bool operator>(Node<T>&);
	bool isLeaf();
	set<shared_ptr<Node<T>>> m_adjacents;
};