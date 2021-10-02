#include "stdafx.h"
#include "CircularLinkedList.h"
template class CircularLinkedList<int>;
template class CircularLinkedList<long>;
template class CircularLinkedList<string>;
using Type = std::variant<int, long>;
template<typename T>
CircularLinkedList<T>::CircularLinkedList(vector<T>& data)
{
	m_head.reset();
	shared_ptr<Node<T>> tail = nullptr;
	for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		if (!m_head) {
			m_head = make_shared<Node<T>>(*it);
			tail = m_head;
		} else {
			Node<T> node(*it);
			shared_ptr<Node<T>> n = Find(node);
			if (!n)	
				n = make_shared<Node<T>>(*it);
			tail->SetNext(n); // Point the existing tail to this new node
			//n->SetPrevious(tail); Not applicable as the loop start will have 2 parents
			tail = n;
		}
	}
}
template<typename T>
CircularLinkedList<T>::~CircularLinkedList()
{
	Clear();
}
template<typename T>
size_t CircularLinkedList<T>::Length() const
{
	size_t length = 0;
	set<shared_ptr<Node<T>>> visited;
	for (shared_ptr<Node<T>> node = m_head; node && visited.find(node) == visited.end(); node = node->Next()) {
		length++;
		visited.insert(node);
	}
	return length;
}
template<typename T>
void CircularLinkedList<T>::Print(shared_ptr<Node<T>>node)
{
	set<shared_ptr<Node<T>>> visited;
	for (shared_ptr<Node<T>> n = node ? node : m_head; n && visited.find(node) == visited.end(); n = n->Next()) {
		cout << n->Item() << " ";
		visited.insert(node);
	}
	cout << endl;
}
template<typename T>
void CircularLinkedList<T>::Clear()
{
	set<shared_ptr<Node<T>>> visited;
	for (shared_ptr<Node<T>> n = m_head; n && visited.find(n) == visited.end();) {
		visited.insert(n);
		shared_ptr<Node<T>> tmp = n;
		n = n->Next();
		tmp.reset();
	}
	m_head.reset();
}
template<typename T>
shared_ptr<Node<T>> CircularLinkedList<T>::Find(Node<T>& n)
{
	set<shared_ptr<Node<T>>> visited;
	shared_ptr<Node<T>> node = nullptr;
	for (node = m_head; node; node = node->Next()) {
		if (visited.find(node) == visited.end()) {
			if (*node == n)
				break;
			else
				visited.insert(node);
		}
		else
			break;
	}
	return node;
}
/*
* This functions checks and returns the start of the loop if it is a circular linked list.
* p1: one step at a time
* p2: 2 steps at a time
* Loop starts at 0
* -1 [0] 1  2  3 <= 1 node before the loop start
*    p1  p2		<= When p1 enters, p2 is 1 node in front of the loop start
*        p1    p2
*        p2 p1
*              p1,p2	<= p1 and p2 meet at 1 node before the loop start
* -2 -1  [0] 1  2  3 <= 2 nodes before the loop start
*    p1  p2
*        p1    p2 <= When p1 enters, p2 is 2 node in front of the loop start
*        p2 p1
*              p1,p2	<= p1 and p2 meet at 2 node before the loop start
* -3 -2 -1  [0] 1  2  3 <= 3 nodes before the loop start
*    p1  p2
*        p1     p2
*		     p1       p2 <= When p1 enters, p2 is 3 node in front of the loop start
*               p1,p2 <= p1 and p2 meet at 3 node before the loop start
* 2 Properties which are ALWAYS right when p1,p2 initially starts out from k nodes before the loop start:
* (1) When p1 enters, p2 is k node in front of the loop start
* (2) p1 and p2 meet at k node before the loop start
*/
template<typename T>
shared_ptr<Node<T>> CircularLinkedList<T>::LoopStart(shared_ptr<Node<T>>& n)
{
	shared_ptr<Node<T>> p1 = n, p2 = n;
	if (n) {
		for (; p2 && p2->Next() != nullptr;) { // p2 will be null if the list only has 2 items and it is not a loop
			p1 = p1->Next();
			p2 = p2->Next()->Next();
			if (p1 == p2)
				break;
		}
		if (!p2 || !p2->Next())
			return nullptr;
		for (p1 = n; p1 != p2; p1 = p1->Next(), p2 = p2->Next());
		return p2;
	}
	return nullptr;
}