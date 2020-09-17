#pragma once
#include "Node.h"
#include <vector>
#include <iostream>
#include <variant>
#include <memory>
using namespace std;
template<typename T>
class LinkedList
{
protected:
	shared_ptr<Node<T>> m_head;
	void SetHead(shared_ptr<Node<T>>);
public:
	LinkedList();
	LinkedList(shared_ptr<Node<T>>);
	LinkedList(vector<T>&);
	virtual ~LinkedList();
	shared_ptr<Node<T>> Head();
	shared_ptr<Node<T>> Tail();
	virtual shared_ptr<Node<T>> Find(Node<T>&);
	size_t Join(LinkedList<T>&);
	virtual void Print(shared_ptr<Node<T>> n = nullptr);
	void SplitList(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	void ToVector(vector<T>&);
	virtual size_t Length() const;
	virtual void Clear();
	void Reverse(size_t, size_t);
	void RemoveDuplicates();
	void MoveHead2Tail();
	shared_ptr<Node<T>> AddItem(T);
	shared_ptr<Node<T>> RemoveHead();
	void MoveItem2Tail(T);
	bool operator==(LinkedList<T>&);
	bool operator!=(LinkedList<T>&);
	bool operator<(LinkedList<T>&);
	bool operator>(LinkedList<T>&);
	// Implement an algorithm to find the nth to last element of a singly linked list.
	shared_ptr<Node<T>> NthElementFromBack(long);
	shared_ptr<Node<T>> RemoveNthElementFromBack(long);
	shared_ptr<Node<T>> AddNumbers(shared_ptr<Node<T>>, shared_ptr<Node<T>>, T carry = 0);
};