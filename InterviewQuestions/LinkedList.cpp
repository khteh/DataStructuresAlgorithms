#include "stdafx.h"
#include "LinkedList.h"
template class LinkedList<int>;
template class LinkedList<long>;

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
size_t LinkedList<T>::Length()
{
	size_t length = 0;
	for (Node<T>* node = m_head; node; node = node->Next())
		length++;
	return length;
}