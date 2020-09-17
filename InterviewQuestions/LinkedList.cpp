#include "stdafx.h"
#include "LinkedList.h"
template class LinkedList<int>;
template class LinkedList<long>;
template class LinkedList<string>;
using Type = std::variant<int, long>;
template<typename T>
LinkedList<T>::LinkedList()
	:m_head(nullptr)
{
}
template<typename T>
LinkedList<T>::LinkedList(shared_ptr<Node<T>> n)
	:m_head(n)
{
}

template<typename T>
LinkedList<T>::LinkedList(vector<T>& data)
{
	m_head.reset();
	shared_ptr<Node<T>> tail = nullptr;
	for (vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		if (!m_head) {
			m_head = make_shared<Node<T>>(*it);
			tail = m_head;
		} else {
			shared_ptr<Node<T>> n = make_shared<Node<T>>(*it);
			tail->SetNext(n); // Point the existing tail to this new node
			n->SetPrevious(tail); // Point the new node to to existing tail as parent.
			tail = n;
		}
	}
}
template<typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::Head() 
{
	return m_head;
}
template<typename T>
void LinkedList<T>::SetHead(shared_ptr<Node<T>> node)
{
	if (!node)
		m_head.reset();
	else
		m_head = node;
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::Tail()
{
	shared_ptr<Node<T>> node = nullptr;
	for (node = m_head; node->Next(); node = node->Next());
	return node;
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::Find(Node<T>& n)
{
	shared_ptr<Node<T>> node = nullptr;
	for (node = m_head; node; node = node->Next())
		if (*node == n)
			break;
	return node;
}
template<typename T>
void LinkedList<T>::Print(shared_ptr<Node<T>>node)
{
	for (shared_ptr<Node<T>> n = node ? node : m_head; n; n = n->Next())
		cout << n->Item() << " ";
	cout << endl;
}
template<typename T>
void LinkedList<T>::ToVector(vector<T>& data)
{
	for (shared_ptr<Node<T>> n = m_head; n; n = n->Next())
		data.push_back(n->Item());
}

template<typename T>
void LinkedList<T>::SplitList(shared_ptr<Node<T>>& even, shared_ptr<Node<T>>& odd)
{
	shared_ptr<Node<T>> evenTail, oddTail;
	even = odd = nullptr;
	size_t i = 0;
	for (shared_ptr<Node<T>> n = m_head; n; n = n->Next(), i++) {
		shared_ptr<Node<T>> node = make_shared<Node<T>>(n);
		if (!(i % 2)) {
			if (!even) {
				even = node;
				evenTail = node;
			} else {
				evenTail->SetNext(node);
				evenTail = node;
			}
		} else {
			if (!odd) {
				odd = node;
				oddTail = node;
			} else {
				oddTail->SetNext(node);
				oddTail = node;
			}
		}
	}
	if (evenTail)
		evenTail->SetNext(nullptr);
	if (oddTail)
		oddTail->SetNext(nullptr);
}
// XXX: After join the ownership of the nodes in 'other' LinkedList is/should be transferred to 
// *this LinkedList. So when other calls Clear() AFTER this->Clear() it results in dangling pointer
// and undefined behaviour. To prevent that, set other.Head to nullptr
template<typename T>
size_t LinkedList<T>::Join(LinkedList<T>& other)
{
	if (*this == other)
		throw runtime_error("LinkedList Cannot join itself!");
	shared_ptr<Node<T>> tail = Tail();
	if (tail)
		tail->SetNext(other.Head());
	other.SetHead(nullptr);
	return Length();
}
template<typename T>
size_t LinkedList<T>::Length() const
{
	size_t length = 0;
	for (shared_ptr<Node<T>> node = m_head; node; node = node->Next())
		length++;
	return length;
}
template<typename T>
bool LinkedList<T>::operator==(LinkedList<T>& other)
{
	return Head() == other.Head()
		&& Tail() == other.Tail()
		&& Length() == other.Length();
}
template<typename T>
bool LinkedList<T>::operator!=(LinkedList<T>& other)
{
	return !(*this == other);
}
template<typename T>
bool LinkedList<T>::operator<(LinkedList<T>& other)
{
	return Length() < other.Length();
}
template<typename T>
bool LinkedList<T>::operator>(LinkedList<T>& other)
{
	return Length() > other.Length();
}
template<typename T>
void LinkedList<T>::Clear()
{
	for (shared_ptr<Node<T>> n = m_head; n;) {
		shared_ptr<Node<T>> tmp = n;
		n = n->Next();
		tmp.reset();
	}
	m_head.reset();
}
template<typename T>
void LinkedList<T>::MoveHead2Tail()
{
	if (m_head) {
		shared_ptr<Node<T>> newHead = m_head->Next();
		shared_ptr<Node<T>> tail = Tail();
		if (newHead && tail) {
			tail->SetNext(m_head);
			m_head->SetPrevious(tail);
			m_head->SetNext(nullptr);
			m_head = newHead;
		}
	}
}
template<typename T>
void LinkedList<T>::MoveItem2Tail(T item)
{
	shared_ptr<Node<T>> n = Find(Node<T>{item});
	shared_ptr<Node<T>> tail = Tail();
	if (tail && n != tail) {
		shared_ptr<Node<T>> parent = n->Previous();
		shared_ptr<Node<T>> next = n->Next();
		n->SetNext(nullptr);
		tail->SetNext(n);
		n->SetPrevious(tail);
		if (parent)
			parent->SetNext(next);
		if (next)
			next->SetPrevious(parent);
		if (m_head == n)
			m_head = next;
	}
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::AddItem(T item)
{
	shared_ptr<Node<T>> n = make_shared<Node<T>>(item);
	if (!m_head)
		m_head = n;
	else {
		shared_ptr<Node<T>> tail = Tail();
		tail->SetNext(n);
		n->SetPrevious(tail);
	}
	return n;
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::RemoveHead()
{
	shared_ptr<Node<T>> n = m_head;
	m_head = m_head->Next();
	if (m_head)
		m_head->SetPrevious(nullptr);
	return n;
}
/* Reverse a linked list from position start to end. Do it in one-pass.
* Input:  1->2->3->4->5->NULL, start = 1, end = 3
* Output: 1->4->3->2->5->NULL
* startNode: Node before the reversed sublist
* tail: Tail of the reversed sublist
* head: head of the reversed sublist
*/
template<typename T>
void LinkedList<T>::Reverse(size_t start, size_t end)
{
	shared_ptr<Node<T>> it = m_head, head = nullptr, startNode, tail;
	for (size_t i = 0; it && end > start && i <= end; i++, it = it->Next()) {
		if (start > 0 && i == start - 1)
			startNode = it;
		if (i >= start) {
			if (!head) {
				head = make_shared<Node<T>>(it->Item());
				tail = head;
			} else {
				shared_ptr<Node<T>> tmp = head;
				head = make_shared<Node<T>>(it->Item());
				head->SetNext(tmp);
				tmp->SetPrevious(head);
			}
		}
		if (i == end) {
			if (startNode)
				startNode->SetNext(head); // Connects the node before the reversed sublist to the head of the reversed sublist
			tail->SetNext(it->Next());
			if (!start)
				m_head = head;
		}
	}
}
/*
* Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
* Return the linked list sorted as well.
* Input: 1->2->3->3->4->4->5
* Output: 1->2->5
*/
template<typename T>
void LinkedList<T>::RemoveDuplicates()
{
	bool found = false;
	shared_ptr<Node<T>> previous = nullptr, head = nullptr;
	// 1,1,1,2,3
	// 1,0,0,3,4
	// 1,0,0,3,3
	for (shared_ptr<Node<T>> it = m_head; it; it = it->Next()) {
		if (it->Next() && it->Item() != it->Next()->Item()) {
			if (found) {
				found = false;
//				if (previous)
//					previous->SetNext(it->Next());
			} else {
				if (!head) {
					head = make_shared<Node<T>>(it->Item());
					m_head = head;
					previous = head;
				} else {
					shared_ptr<Node<T>> tmp = previous;
					previous = make_shared<Node<T>>(it->Item());
					tmp->SetNext(previous);
				}
			}
		} else if (it->Next())
			found = true;
		else if (!found && !it->Next()) { // Last unique Node
			if (!head) {
				head = make_shared<Node<T>>(it->Item());
				m_head = head;
				previous = head;
			} else
				previous->SetNext(it);
		}
	}
	if (!head && found)
		m_head = nullptr;
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::NthElementFromBack(long n) // n starts from 1
{
	shared_ptr<Node<T>> p1 = m_head;
	shared_ptr<Node<T>> p2 = m_head; // Serves as guard / offset
	for (long i = 0; i < n - 1 && p2; i++, p2 = p2->Next());
	if (!p2)
		return nullptr;
	while (p2->Next()) {
		p1 = p1->Next();
		p2 = p2->Next();
	}
	return p1;
}
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::RemoveNthElementFromBack(long n) // n starts from 1
{
	shared_ptr<Node<T>> prev = nullptr;
	shared_ptr<Node<T>> p1 = m_head; // to remove
	shared_ptr<Node<T>> p2 = m_head; // Serves as guard / offset
	for (long i = 0; i < n - 1 && p2; i++, p2 = p2->Next());
	if (!p2)
		return m_head;
	while (p2->Next()) {
		prev = p1;
		p1 = p1->Next();
		p2 = p2->Next();
	}
	if (p1 == m_head)
		return p1->Next();
	prev->SetNext(p1->Next());
	return m_head;
}
// Input: 
//   p1:   3 -> 1 -> 5
//   p2:   5 -> 9 -> 2
// Output: 8 -> 0 -> 8
template<typename T>
shared_ptr<Node<T>> LinkedList<T>::AddNumbers(shared_ptr<Node<T>> p1, shared_ptr<Node<T>> p2, T carry)
{
	if constexpr (is_same_v<T, long> || is_same_v<T, int>) {
		if (p1 || p2 || carry > T()) {
			shared_ptr<Node<T>> result = make_shared<Node<T>>(carry);
			if (p1)
				result->SetItem(result->Item() + p1->Item());
			if (p2)
				result->SetItem(result->Item() + p2->Item());
			carry = result->Item() / 10;
			result->SetItem(result->Item() % 10);
			result->SetNext(AddNumbers(p1 ? p1->Next() : nullptr, p2 ? p2->Next() : nullptr, carry));
			return result;
		}
	}
	return nullptr;
}