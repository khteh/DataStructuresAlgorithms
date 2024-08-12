#include "stdafx.h"
#include "LinkedList.h"
template class LinkedList<int>;
template class LinkedList<size_t>;
template class LinkedList<long>;
template class LinkedList<string>;
template class LinkedList<float>;
template class LinkedList<double>;
template <typename T>
LinkedList<T>::LinkedList()
	: m_head(nullptr)
{
}
template <typename T>
LinkedList<T>::LinkedList(shared_ptr<Node<T>> n)
	: m_head(n)
{
}

template <typename T>
LinkedList<T>::LinkedList(vector<T> const &data)
{
	LoadData(data);
}
template <typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}
template <typename T>
void LinkedList<T>::LoadData(vector<T> const &data)
{
	m_head.reset();
	shared_ptr<Node<T>> tail = nullptr;
	for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
	{
		if (!m_head)
		{
			m_head = make_shared<Node<T>>(*it);
			tail = m_head;
		}
		else
		{
			shared_ptr<Node<T>> n = make_shared<Node<T>>(*it);
			tail->SetNext(n);	  // Point the existing tail to this new node
			n->SetPrevious(tail); // Point the new node to to existing tail as parent.
			tail = n;
		}
	}
}
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::Head()
{
	return m_head;
}
template <typename T>
void LinkedList<T>::SetHead(shared_ptr<Node<T>> node)
{
	if (!node)
		m_head.reset();
	else
		m_head = node;
}
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::Tail()
{
	shared_ptr<Node<T>> node = nullptr;
	for (node = m_head; node->Next(); node = node->Next())
		;
	return node;
}
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::Find(const Node<T> &n)
{
	shared_ptr<Node<T>> node = nullptr;
	for (node = m_head; node; node = node->Next())
		if (*node == (Node<T> &)n)
			break;
	return node;
}
template <typename T>
void LinkedList<T>::Print(shared_ptr<Node<T>> node)
{
	for (shared_ptr<Node<T>> n = node ? node : m_head; n; n = n->Next())
		cout << n->Item() << " ";
	cout << endl;
}
template <typename T>
void LinkedList<T>::ToVector(vector<T> &data)
{
	for (shared_ptr<Node<T>> n = m_head; n; n = n->Next())
		data.push_back(n->Item());
}

template <typename T>
void LinkedList<T>::SplitList(shared_ptr<Node<T>> &even, shared_ptr<Node<T>> &odd)
{
	shared_ptr<Node<T>> evenTail, oddTail;
	even = odd = nullptr;
	size_t i = 0;
	for (shared_ptr<Node<T>> n = m_head; n; n = n->Next(), i++)
	{
		shared_ptr<Node<T>> node = make_shared<Node<T>>(n);
		if (!(i % 2))
		{
			if (!even)
				even = node;
			else
			{
				evenTail->SetNext(node);
				node->SetPrevious(evenTail);
			}
			evenTail = node;
		}
		else
		{
			if (!odd)
				odd = node;
			else
			{
				oddTail->SetNext(node);
				node->SetPrevious(oddTail);
			}
			oddTail = node;
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
template <typename T>
size_t LinkedList<T>::Join(LinkedList<T> &other)
{
	if (*this == other)
		throw runtime_error("LinkedList Cannot join itself!");
	shared_ptr<Node<T>> tail = Tail();
	if (tail)
		tail->SetNext(other.Head());
	other.SetHead(nullptr);
	return Length();
}
template <typename T>
size_t LinkedList<T>::Length() const
{
	size_t length = 0;
	for (shared_ptr<Node<T>> node = m_head; node; node = node->Next(), length++)
		;
	return length;
}
template <typename T>
bool LinkedList<T>::operator==(LinkedList<T> &other)
{
	return Head() == other.Head() && Tail() == other.Tail() && Length() == other.Length();
}
template <typename T>
bool LinkedList<T>::operator!=(LinkedList<T> &other)
{
	return !(*this == other);
}
template <typename T>
bool LinkedList<T>::operator<(LinkedList<T> &other)
{
	return Length() < other.Length();
}
template <typename T>
bool LinkedList<T>::operator>(LinkedList<T> &other)
{
	return Length() > other.Length();
}
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::operator[](size_t index) const
{
	size_t i = 0;
	shared_ptr<Node<T>> node = m_head;
	for (; node && i != index; node = node->Next(), i++)
		;
	return node;
}
template <typename T>
void LinkedList<T>::Clear()
{
	for (shared_ptr<Node<T>> n = m_head; n;)
	{
		shared_ptr<Node<T>> tmp = n;
		n = n->Next();
		tmp.reset();
	}
	m_head.reset();
}
template <typename T>
void LinkedList<T>::MoveHead2Tail()
{
	if (m_head)
	{
		shared_ptr<Node<T>> newHead = m_head->Next();
		shared_ptr<Node<T>> tail = Tail();
		if (newHead && tail)
		{
			tail->SetNext(m_head);
			m_head->SetPrevious(tail);
			m_head->SetNext(nullptr);
			m_head = newHead;
		}
	}
}
template <typename T>
void LinkedList<T>::MoveItem2Tail(T item)
{
	shared_ptr<Node<T>> n = Find(Node<T>{item});
	shared_ptr<Node<T>> tail = Tail();
	if (tail && n != tail)
	{
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
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::AddItem(T item)
{
	shared_ptr<Node<T>> n = make_shared<Node<T>>(item);
	if (!m_head)
		m_head = n;
	else
	{
		shared_ptr<Node<T>> tail = Tail();
		tail->SetNext(n);
		n->SetPrevious(tail);
	}
	return n;
}
template <typename T>
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
template <typename T>
void LinkedList<T>::Reverse(size_t start, size_t end)
{
	shared_ptr<Node<T>> it = m_head, head = nullptr, startNode, tail;
	for (size_t i = 0; it && end > start && i <= end; i++, it = it->Next())
	{
		if (start > 0 && i == start - 1)
			startNode = it;
		if (i >= start)
		{
			if (!head)
			{
				head = make_shared<Node<T>>(it->Item());
				tail = head;
			}
			else
			{
				shared_ptr<Node<T>> tmp = head;
				head = make_shared<Node<T>>(it->Item());
				head->SetNext(tmp);
				tmp->SetPrevious(head);
			}
		}
		if (i == end)
		{
			if (startNode)
				startNode->SetNext(head); // Connects the node before the reversed sublist to the head of the reversed sublist
			tail->SetNext(it->Next());
			if (!start)
				m_head = head;
		}
	}
}
/* https://leetcode.com/problems/rotate-list/
 * 100%
 */
template <typename T>
void LinkedList<T>::RotateRight(size_t k)
{
	if (m_head)
	{
		size_t count = 0;
		// Count how many nodes in the list to eliminate loops
		for (shared_ptr<Node<T>> n = m_head; n; n = n->Next(), count++)
			;
		if (count > 1)
		{
			// Eliminate loops
			k %= count;
			for (; k > 0; k--)
			{
				shared_ptr<Node<T>> n = m_head, prev = nullptr;
				for (; n->Next(); prev = n, n = n->Next())
					;
				prev->SetNext(nullptr);
				n->SetNext(m_head);
				m_head = n;
			}
		}
	}
}
/* https://leetcode.com/problems/sort-list/
 * 100%
 * Use bottom-up merge sort
 */
template <typename T>
void LinkedList<T>::Sort()
{
	if (m_head && m_head->Next())
	{
		size_t size = Length();
		shared_ptr<Node<T>> dummy = make_unique<Node<T>>(numeric_limits<T>::max());
		dummy->SetNext(m_head);
		shared_ptr<Node<T>> n, left, right, tail;
		/*
		 * dummy->5->1->3->2
		 * width: 1
		 * (tail) l  r  n
		 * dummy->1->5(tail)
		 *       3->2
		 *  		l  r n=null
		 * dummy->1->5->2->3(tail)
		 * width: 2
		 * (tail) l  l  r  r n=null
		 * dummy->1->2->3->5(tail)
		 */
		for (size_t width = 1; width < size; width *= 2)
		{
			n = dummy->Next();
			tail = dummy;
			while (n)
			{
				left = n;
				right = Split(left, width);
				n = Split(right, width);
				Merge(left, right, tail);
			}
		}
		m_head = dummy->Next();
		m_head->SetPrevious(nullptr);
	}
}
/*
 * Splits the list into 2. First list contains size nodes.
 * Returns head of the second list.
 */
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::Split(shared_ptr<Node<T>> first, size_t size)
{
	shared_ptr<Node<T>> second = nullptr;
	for (size_t i = 1; i < size && first; i++, first = first->Next())
		;
	if (first)
	{
		second = first->Next();
		first->SetNext(nullptr);
	}
	return second;
}
/*
 * Merge left and right lists into dest sorted list.
 */
template <typename T>
void LinkedList<T>::Merge(shared_ptr<Node<T>> &left, shared_ptr<Node<T>> &right, shared_ptr<Node<T>> &dest)
{
	for (; left && right;)
	{
		if (left->Item() < right->Item())
		{
			dest->SetNext(left);
			dest = left;
			left = left->Next();
		}
		else
		{
			dest->SetNext(right);
			dest = right;
			right = right->Next();
		}
	}
	dest->SetNext(left ? left : right);
	for (; dest->Next(); dest = dest->Next())
		;
}
/*
 * Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 * Return the linked list sorted as well.
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->3->4->5
 */
template <typename T>
void LinkedList<T>::RemoveDuplicates()
{
	for (shared_ptr<Node<T>> c = m_head; c; c = c->Next())
	{
		for (shared_ptr<Node<T>> prev = c, it = c->Next(); it; it = it->Next())
		{
			// 1(c,prev) 1(it) 1
			if (it->Item() == c->Item())
			{
				prev->SetNext(it->Next());
				// 1(c, prev) 1 1(it)
			}
			else
			{
				prev = prev->Next();
			}
		}
	}
}
/*
 * Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
 * Return the linked list sorted as well.
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->5
 */
template <typename T>
void LinkedList<T>::RemoveAllDuplicates()
{
	bool foundDuplicate = false;
	shared_ptr<Node<T>> previous = nullptr, head = nullptr;
	// 1,1,1,2,3
	// 1,0,0,3,4
	// 1,0,0,3,3
	for (shared_ptr<Node<T>> it = m_head; it; it = it->Next())
	{
		if (it->Next() && it->Item() != it->Next()->Item())
		{
			if (foundDuplicate)
			{
				foundDuplicate = false;
			}
			else
			{
				if (!head)
				{
					head = make_shared<Node<T>>(it->Item());
					m_head = head;
					previous = head;
				}
				else
				{
					shared_ptr<Node<T>> tmp = previous;
					previous = make_shared<Node<T>>(it->Item());
					tmp->SetNext(previous);
				}
			}
		}
		else if (it->Next())
			foundDuplicate = true;
		else if (!foundDuplicate && !it->Next())
		{ // Last unique Node
			if (!head)
			{
				head = make_shared<Node<T>>(it->Item());
				m_head = head;
				previous = head;
			}
			else
				previous->SetNext(it);
		}
	}
	if (!head && foundDuplicate)
		m_head = nullptr;
}
/*
 * 0->1->2->3->4->5->6->7->8->9
 * 10 9  8  7  6  5  4  3  2  1
 */
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::NthElementFromBack(long n) // n starts from 1
{
	shared_ptr<Node<T>> p1 = m_head;
	shared_ptr<Node<T>> p2 = m_head; // Serves as guard / offset
	for (long i = 0; i < n - 1 && p2; i++, p2 = p2->Next())
		;
	if (!p2)
		return nullptr;
	while (p2->Next())
	{
		p1 = p1->Next();
		p2 = p2->Next();
	}
	return p1;
}
/*
 * 0->1->2->3->4->5->6->7->8->9
 * 10 9  8  7  6  5  4  3  2  1
 * Return the nth element from the back after successful removal
 */
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::RemoveNthElementFromBack(long n) // n starts from 1
{
	shared_ptr<Node<T>> prev = nullptr;
	shared_ptr<Node<T>> p1 = m_head; // to remove
	shared_ptr<Node<T>> p2 = m_head; // Serves as guard / offset
	for (long i = 0; i < n - 1 && p2; i++, p2 = p2->Next())
		;
	if (!p2)
		return nullptr;
	while (p2->Next())
	{
		prev = p1;
		p1 = p1->Next();
		p2 = p2->Next();
	}
	if (p1 == m_head)
	{
		m_head = m_head->Next();
		return m_head;
	}
	prev->SetNext(p1->Next());
	return prev;
}
/* Input:
 *   p1:   3 -> 1 -> 5
 *   p2:   5 -> 9 -> 2
 * Output: 8 -> 0 -> 8
 */
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::AddNumbers(shared_ptr<Node<T>> p1, shared_ptr<Node<T>> p2, T carry)
	requires integral_type<T>
{
	if (p1 || p2 || carry > T())
	{
		shared_ptr<Node<T>> result = make_shared<Node<T>>(carry);
		if (p1)
			result->SetItem(result->Item() + p1->Item());
		if (p2)
			result->SetItem(result->Item() + p2->Item());
		carry = result->Item() / 10;
		result->SetItem(fmod(result->Item(), 10));
		result->SetNext(AddNumbers(p1 ? p1->Next() : nullptr, p2 ? p2->Next() : nullptr, carry));
		return result;
	}
	return nullptr;
}
template <typename T>
shared_ptr<Node<T>> LinkedList<T>::AddNumbers(LinkedList<T> &ll)
	requires integral_type<T>
{
	return AddNumbers(m_head, ll.Head(), T());
}