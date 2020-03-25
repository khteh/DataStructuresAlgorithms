#pragma once
#include <set>
using namespace std;

template<class T>
class Node
{
protected:
	T m_item;
	Node<T> *m_next, *m_previous, *m_left, *m_right;
public:
	explicit Node(T item);
	Node(const Node &);
	Node(const Node *);
	virtual ~Node();
	T Item();
	Node<T> *Next();
	Node<T>* Previous();
	Node<T> *Left();
	Node<T> *Right();
	void SetPrevious(Node<T>*);
	void SetNext(Node<T>*);
	void SetLeft(Node<T>*);
	void SetRight(Node<T>*);
	void SetItem(T);
	Node<T>& operator=(Node<T>&);
	bool operator==(Node<T>&);
	bool operator!=(Node<T>&);
	bool operator<(Node<T>&);
	bool operator>(Node<T>&);
	bool isLeaf();
	set<Node<T>*> m_adjacents;
};