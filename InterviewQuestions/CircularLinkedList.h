#pragma once
#include "Node.h"
#include "LinkedList.h"
template<typename T>
class CircularLinkedList : public LinkedList<T>
{
private:
	using LinkedList<T>::m_head;
public:
	CircularLinkedList(vector<T>&);
	~CircularLinkedList();
	size_t Length() const;
	shared_ptr<Node<T>> Find(Node<T>&);
	void Print(shared_ptr<Node<T>> n = nullptr);
	void Clear();
	shared_ptr<Node<T>> LoopStart(shared_ptr<Node<T>>&);
};