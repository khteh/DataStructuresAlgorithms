#pragma once
#include "Node.h"
#include <vector>
#include <iostream>
using namespace std;
template<class T>
class LinkedList
{
private:
	Node<T> *m_head;
public:
	LinkedList(Node<T>*);
	LinkedList(vector<T>&);
	virtual ~LinkedList();
	void Print(Node<T>* n = nullptr);
	void SplitList(Node<T>*&, Node<T>*&);
	void ToVector(vector<T>&);
	size_t Length();
	// Implement an algorithm to find the nth to last element of a singly linked list.
	Node<T>* NthElementFromBack(size_t);
};