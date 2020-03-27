#pragma once
#include "Node.h"
#include <vector>
#include <iostream>
#include <variant>
#include <memory>
using namespace std;
template<class T>
class LinkedList
{
private:
	shared_ptr<Node<T>> m_head;
	void SetHead(shared_ptr<Node<T>>);
public:
	LinkedList(shared_ptr<Node<T>>);
	LinkedList(vector<T>&);
	virtual ~LinkedList();
	shared_ptr<Node<T>> Head();
	shared_ptr<Node<T>> Tail();
	shared_ptr<Node<T>> Find(Node<T>&);
	size_t Join(LinkedList<T>&);
	void Print(shared_ptr<Node<T>> n = nullptr);
	void SplitList(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	void ToVector(vector<T>&);
	size_t Length() const;
	void Clear();
	bool operator==(LinkedList<T>&);
	bool operator!=(LinkedList<T>&);
	bool operator<(LinkedList<T>&);
	bool operator>(LinkedList<T>&);
	// Implement an algorithm to find the nth to last element of a singly linked list.
	shared_ptr<Node<T>> NthElementFromBack(size_t);
	shared_ptr<Node<T>> AddNumbers(shared_ptr<Node<T>>, shared_ptr<Node<T>>, T carry = 0);
};