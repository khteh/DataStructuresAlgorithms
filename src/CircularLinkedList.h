#pragma once
#include "Node.h"
#include "LinkedList.h"
template <typename T>
class CircularLinkedList : public LinkedList<T>
{
private:
	using LinkedList<T>::_head;

public:
	CircularLinkedList(); // Needed by GoogleTest TEST_P
	CircularLinkedList(vector<T> const &);
	~CircularLinkedList();
	size_t Length() const;
	shared_ptr<Node<T>> Find(Node<T> &);
	void Print(shared_ptr<Node<T>> n = nullptr);
	void Clear();
	T LoopStart(shared_ptr<Node<T>> &);
};