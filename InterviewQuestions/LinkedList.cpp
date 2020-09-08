#include "stdafx.h"
#include "LinkedList.h"
template class LinkedList<int>;
template class LinkedList<long>;
template class LinkedList<string>;
using Type = std::variant<int, long>;
template<typename T>
LinkedList<T>::LinkedList(shared_ptr<Node<T>> n)
{
	m_head = n;
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
			shared_ptr<Node<T>>n = make_shared<Node<T>>(*it);
			tail->SetNext(n);
			n->SetPrevious(tail);
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