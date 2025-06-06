#pragma once
#include "Node.h"
using namespace std;

template <typename T>
class LinkedList
{
protected:
	shared_ptr<Node<T>> _head;
	void SetHead(shared_ptr<Node<T>>);
	shared_ptr<Node<T>> Split(shared_ptr<Node<T>>, size_t);
	void Merge(shared_ptr<Node<T>> &, shared_ptr<Node<T>> &, shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> AddNumbers(shared_ptr<Node<T>>, shared_ptr<Node<T>>, T carry = 0)
		requires integral_type<T>;

public:
	LinkedList();
	LinkedList(shared_ptr<Node<T>>);
	LinkedList(vector<T> const &);
	virtual ~LinkedList();
	void LoadData(vector<T> const &);
	shared_ptr<Node<T>> Head();
	shared_ptr<Node<T>> Tail();
	virtual shared_ptr<Node<T>> Find(const Node<T> &);
	size_t Join(LinkedList<T> &);
	virtual void Print(shared_ptr<Node<T>> n = nullptr);
	void SplitList(shared_ptr<Node<T>> &, shared_ptr<Node<T>> &);
	void ToVector(vector<T> &);
	virtual size_t Length() const;
	virtual void Clear();
	void Reverse(size_t, size_t);
	void RotateRight(size_t);
	void Sort();
	void RemoveAllDuplicates();
	void RemoveDuplicates();
	void MoveHead2Tail();
	shared_ptr<Node<T>> AddItem(T);
	shared_ptr<Node<T>> RemoveHead();
	void MoveItem2Tail(T);
	bool operator==(LinkedList<T> &);
	bool operator!=(LinkedList<T> &);
	bool operator<(LinkedList<T> &);
	bool operator>(LinkedList<T> &);
	shared_ptr<Node<T>> operator[](size_t) const;
	// Implement an algorithm to find the nth to last element of a singly linked list.
	shared_ptr<Node<T>> NthElementFromBack(long);
	shared_ptr<Node<T>> RemoveNthElementFromBack(long);
	shared_ptr<Node<T>> AddNumbers(LinkedList<T> &)
		requires integral_type<T>;
};