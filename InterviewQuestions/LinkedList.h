#pragma once
#include "Node.h"
#include <vector>
#include <iostream>
#include <variant>
using namespace std;
template<class T>
class LinkedList
{
private:
	Node<T> *m_head;
	void SetHead(Node<T>*);
public:
	LinkedList(Node<T>*);
	LinkedList(vector<T>&);
	virtual ~LinkedList();
	Node<T>* Head();
	Node<T>* Tail();
	Node<T>* Find(Node<T>&);
	size_t Join(LinkedList<T>&);
	void Print(Node<T>* n = nullptr);
	void SplitList(Node<T>*&, Node<T>*&);
	void ToVector(vector<T>&);
	size_t Length() const;
	void Clear();
	bool operator==(LinkedList<T>&);
	bool operator!=(LinkedList<T>&);
	bool operator<(LinkedList<T>&);
	bool operator>(LinkedList<T>&);
	// Implement an algorithm to find the nth to last element of a singly linked list.
	Node<T>* NthElementFromBack(size_t);
	Node<T>* AddNumbers(Node<T>*, Node<T>*, T carry = 0);
};