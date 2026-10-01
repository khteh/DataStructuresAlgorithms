#pragma once
#include "Node.h"
#include "LinkedList.h"
template <typename T>
class CircularLinkedList : public LinkedList<T>
{
private:
	using LinkedList<T>::_head;
	using LinkedList<T>::_tail;

public:
	CircularLinkedList(); // Needed by GoogleTest TEST_P
	CircularLinkedList(vector<T> const &);
	/*
	 * Copying is disabled (as in LinkedList): Clear() breaks the ring on destruction, so a shallow copy sharing the ring
	 * would be broken when the other copy is destroyed. Ownership of the ring can only be transferred (moved).
	 */
	CircularLinkedList(const CircularLinkedList &) = delete;
	CircularLinkedList &operator=(const CircularLinkedList &) = delete;
	CircularLinkedList(CircularLinkedList &&) noexcept;
	CircularLinkedList &operator=(CircularLinkedList &&) noexcept;
	~CircularLinkedList();
	size_t Length() const;
	shared_ptr<Node<T>> Find(Node<T> &);
	void Print(shared_ptr<Node<T>> n = nullptr);
	void Clear();
	T LoopStart(shared_ptr<Node<T>> &);
};