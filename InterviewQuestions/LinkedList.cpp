#include "stdafx.h"
#include "LinkedList.h"
template class LinkedList<int>;
template class LinkedList<long>;
template class LinkedList<string>;
using Type = std::variant<int, long>;
template<class T>
LinkedList<T>::LinkedList(Node<T>* n)
{
	m_head = n;
}

template<class T>
LinkedList<T>::LinkedList(vector<T>& data)
{
	m_head = nullptr;
	Node<T> *tail = nullptr;
	for (vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		if (!m_head) {
			m_head = new Node<T>(*it);
			tail = m_head;
		} else {
			Node<T> *n = new Node<T>(*it);
			tail->SetNext(n);
			tail = n;
		}
	}
}

template<class T>
LinkedList<T>::~LinkedList()
{
	for (Node<T>* n = m_head; n;) {
		Node<T>* tmp = n;
		n = n->Next();
		delete tmp;
	}
}
template<class T>
Node<T>* LinkedList<T>::Head() 
{
	return m_head;
}
template<class T>
Node<T>* LinkedList<T>::Tail() 
{
	Node<T>* node = nullptr;
	for (node = m_head; node->Next(); node = node->Next());
	return node;
}
template<class T>
Node<T>* LinkedList<T>::Find(Node<T>& n) {
	Node<T>* node = nullptr;
	for (node = m_head; node; node = node->Next())
		if (*node == n)
			break;
	return node;
}
template<class T>
void LinkedList<T>::Print(Node<T> *node)
{
	for (Node<T>* n = node ? node : m_head; n; n = n->Next())
		cout << n->Item() << " ";
	cout << endl;
}

template<class T>
void LinkedList<T>::ToVector(vector<T>& data)
{
	for (Node<T>* n = m_head; n; n = n->Next())
		data.push_back(n->Item());
}

template<class T>
void LinkedList<T>::SplitList(Node<T>*& even, Node<T>*& odd)
{
	Node<T> *evenTail, *oddTail;
	even = odd = nullptr;
	size_t i = 0;
	for (Node<T>* n = m_head; n; n = n->Next(), i++) {
		if (!(i % 2)) {
			if (!even) {
				even = n;
				evenTail = n;
			} else {
				evenTail->SetNext(n);
				evenTail = n;
			}
		} else {
			if (!odd) {
				odd = n;
				oddTail = n;
			} else {
				oddTail->SetNext(n);
				oddTail = n;
			}
		}
	}
	if (evenTail)
		evenTail->SetNext(nullptr);
	if (oddTail)
		oddTail->SetNext(nullptr);
}
template<class T>
size_t LinkedList<T>::Join(LinkedList<T>& other)
{
	if (*this == other)
		throw runtime_error("LinkedList Cannot join itself!");
	Node<T>* tail = Tail();
	if (tail)
		tail->SetNext(other.Head());
	return Length();
}
template<class T>
size_t LinkedList<T>::Length() const
{
	size_t length = 0;
	for (Node<T>* node = m_head; node; node = node->Next())
		length++;
	return length;
}
template<class T>
bool LinkedList<T>::operator==(LinkedList<T>& other)
{
	return Head() == other.Head()
		&& Tail() == other.Tail()
		&& Length() == other.Length();
}
template<class T>
bool LinkedList<T>::operator!=(LinkedList<T>& other)
{
	return !(*this == other);
}
template<class T>
bool LinkedList<T>::operator<(LinkedList<T>& other)
{
	return Length() < other.Length();
}
template<class T>
bool LinkedList<T>::operator>(LinkedList<T>& other)
{
	return Length() > other.Length();
}
template<class T>
Node<T>* LinkedList<T>::NthElementFromBack(size_t n)
{
	Node<T> *p1 = m_head;
	Node<T>* p2 = m_head;
	for (size_t i = 0; i < n - 1 && p2; i++, p2 = p2->Next());
	if (!p2)
		return nullptr;
	while (p2->Next()) {
		p1 = p1->Next();
		p2 = p2->Next();
	}
	return p1;
}
// Input: 
//   p1:   3 -> 1 -> 5
//   p2:   5 -> 9 -> 2
// Output: 8 -> 0 -> 8
template<class T>
Node<T>* LinkedList<T>::AddNumbers(Node<T>* p1, Node<T>* p2, T carry)
{
	if constexpr (is_same_v<T, long> || is_same_v<T, int>) {
		if (p1 || p2 || carry > T()) {
			Node<T>* result = new Node<T>(carry);
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