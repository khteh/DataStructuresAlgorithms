#include "stdafx.h"
#include "Heap.h"
#include <assert.h>
using namespace std;
template class Heap<int>;
template class Heap<long>;
// http://en.wikipedia.org/wiki/Binary_heap

template<class T>
Heap<T>::Heap(HeapType t)
	: type_(t)
{
}

template<class T>
Heap<T>::Heap(T item, HeapType t)
	: type_(t)
	, Tree(item)
{
}

template<class T>
Heap<T>::Heap(shared_ptr<Node<T>> node, HeapType t)
	: type_(t)
	, Tree(node)
{
}
template<class T>
Heap<T>::Heap(vector<T>& data, HeapType type)
	: type_(type)
{
	for (vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
		InsertItem(*it);
}
template<class T>
void Heap<T>::InsertNode(shared_ptr<Node<T>> root, shared_ptr<Node<T>> node)
{
	if (node) {
		shared_ptr<Node<T>> p = FindEmptyLeafParent();
		assert(p);
		if (p) {
			if (!p->Left()) {
				p->SetLeft(node);
				node->SetNext(p);
			} else {
				p->SetRight(node);
				node->SetNext(p);
			}
			HeapifyUp(node, MaxDepth(m_root) - 1 /* 0-based */);
		}
	}
}

// MinHeap/MinMaxHeap: Remove min
// MaxHeap: Remove max
template<class T>
shared_ptr<Node<T>> Heap<T>::pop()
{
	shared_ptr<Node<T>> result(nullptr), node(nullptr);
	if (m_root) {
		result = make_shared<Node<T>>(m_root->Item());
		node = FindLastLeaf();
		if (node && node != m_root) {
			swap(node, m_root);
			shared_ptr<Node<T>> p(node->Next());
			if (p) { // If not the only node left (= m_root)
				if (p->Left() == node)
					p->SetLeft(nullptr);
				else if (p->Right() == node)
					p->SetRight(nullptr);
				else
					assert(false);
			}
			node.reset();
		} else if (m_root)
			m_root.reset();
		if (m_root)
			HeapifyDown(m_root);
	}
	return result;
}

template<class T>
shared_ptr<Node<T>> Heap<T>::front()
{
	return m_root;
}

template<class T>
void Heap<T>::Serialize(vector<T>& result)
{
	shared_ptr<Node<T>> node;
	while (node = pop())
		result.push_back(node->Item());
}

template<class T>
void Heap<T>::swap(shared_ptr<Node<T>> n, shared_ptr<Node<T>> m)
{
	T tmp;
	tmp = n->Item();
	n->SetItem(m->Item());
	m->SetItem(tmp);
}

template<class T>
void Heap<T>::HeapifyUp(shared_ptr<Node<T>> node, unsigned long level)
{
	if (node && level >= 0) {
		switch (type_) {
		case HeapType::MinHeap:
			if (node->Next() && *node < *node->Next()) {
				swap(node, node->Next());
				HeapifyUp(node->Next());
			}
			break;
		case HeapType::MaxHeap:
			if (node->Next() && *node > *node->Next()) {
				swap(node, node->Next());
				HeapifyUp(node->Next());
			}
			break;
		case HeapType::MinMaxHeap: // http://en.wikipedia.org/wiki/Min-max_heap
			{
				bool isMaxLevel = level % 2;
				shared_ptr<Node<T>> grandparent = nullptr;
				if (isMaxLevel) { // parent is at Min Level
					if (node->Next() && *node < *node->Next()) {
						// Item is smaller than parent(Min) and all items at Max levels. Only need to check the Min levels
						swap(node, node->Next());
						HeapifyUp(node->Next(), --level);
					} else if (node->Next()) {
						// Item is greater than parent => Check with Max levels
						if (node->Next()->Next())
							grandparent = node->Next()->Next();
						if (grandparent && *node > *grandparent) {
							swap(node, grandparent);
							level -= 2;
							HeapifyUp(grandparent, level);
						}
					}
				} else { // Min Level. Parent at Max Level.
					if (node->Next() && *node > *node->Next()) {
						// Item is greater than parent and all items at Min levels. Only need to check the Max levels
						swap(node, node->Next());
						HeapifyUp(node->Next(), --level);
					} else if (node->Next()) {
						if (node->Next()->Next())
							grandparent = node->Next()->Next();
						if (grandparent && *node < *grandparent) {
							swap(node, grandparent);
							level -= 2;
							HeapifyUp(grandparent, level);
						}
					} else { // Root of the tree (Min level) in a Min-Max Heap
						if (node->Left() && *node > *node->Left())
							swap(node, node->Left());
						else if (node->Right() && *node > *node->Right())
							swap(node, node->Right());
					}
				}
			}
			break;
		default:
			throw runtime_error("Invalid Heap Type!");
			break;
		}
	}
}

template<class T>
void Heap<T>::HeapifyDown(shared_ptr<Node<T>> node)
{
	if (node) {
		switch (type_) {
		case HeapType::MinHeap:
			if (node->Left() && *node > *node->Left()) { // Next minimum must come from the left branch since the tree is filled from left to right
				swap(node, node->Left());
				HeapifyDown(node->Left());
			}
			if (node->Right() && *node > *node->Right()) { // Next minimum must come from the left branch since the tree is filled from left to right
				swap(node, node->Right());
				HeapifyDown(node->Right());
			}
			break;
		case HeapType::MaxHeap:
			if (node->Left() && *node < *node->Left()) { // Next minimum must come from the left branch since the tree is filled from left to right
				swap(node, node->Left());
				HeapifyDown(node->Left());
			} 
			if (node->Right() && *node < *node->Right()) { // Next minimum must come from the left branch since the tree is filled from left to right
				swap(node, node->Right());
				HeapifyDown(node->Right());
			}
			break;
		case HeapType::MinMaxHeap: // http://en.wikipedia.org/wiki/Min-max_heap
			// Find minimum
			//1. x.key <= h[m].key. x must be inserted into the root. (x is already at root position when this function is called)
			//2. x.key > h[m].key and m is child of the root.since m is in max level, it has no descendants.So the element h[m] is moved to the root and x is inserted into node m.
			//3. x.key > h[m].key and m is grandchild of the root.So the element h[m] is moved to the root.Let p be parent of m. if x.key > h[p].key then h[p] and x are interchanged.
			if (MaxDepth(node) == 2) { // Condition 2
				if (node->Left() && *node > *node->Left())
					swap(node, node->Left());
				if (node->Right() && *node > *node->Right())
					swap(node, node->Right());
			} else if (MaxDepth(node) > 2) { // Condition 3
				shared_ptr<Node<T>> min(node);
				map<size_t, vector<shared_ptr<Node<T>>>> nodes;
				GetNodes(nodes, 2);
				assert(!nodes[2].empty());
				for (vector<shared_ptr<Node<T>>>::iterator it = nodes[2].begin(); it != nodes[2].end(); it++) {
					if (*min > *(*it))
						min = *it;
				}
				if (*node > *min) {
					shared_ptr<Node<T>> p(min->Next());
					swap(node, min); // Min is moved to the root
					// node has min; min has original node value
					if (*min > *p)
						swap(min, p);
				}
			}
			break;
		default:
			throw runtime_error("Invalid Heap Type!");
			break;
		}
	}
}

template<class T>
shared_ptr<Node<T>> Heap<T>::FindEmptyLeafParent() // Use Breath-First-Search to find empty leaf
{
	unsigned long level = 0;
	vector<shared_ptr<Node<T>>> nodes;
	map<unsigned long, vector<shared_ptr<Node<T>>>> levelNodes;
	if (!m_root)
		return m_root;
	nodes.push_back(m_root);
	levelNodes.emplace(0, nodes);
	while (!nodes.empty()) {
		nodes.clear();
		for (vector<shared_ptr<Node<T>>>::iterator it = levelNodes[level].begin(); it != levelNodes[level].end(); it++) {
			assert(*it);
			if (*it) {
				if ((*it)->Right() && !(*it)->Left())
					assert(false);
				if (!(*it)->Left())
					return *it;
				nodes.push_back((*it)->Left());
				if (!(*it)->Right())
					return *it;
				nodes.push_back((*it)->Right());
			}
		}
		level++;
		if (!nodes.empty())
			levelNodes.emplace(level, nodes);
	}
	return nullptr;
}

template<class T>
shared_ptr<Node<T>> Heap<T>::FindLastLeaf() // Use Breadth-First-Search to find empty leaf
{
	shared_ptr<Node<T>> result(nullptr);
	unsigned long level = 0;
	vector<shared_ptr<Node<T>>> nodes;
	map<unsigned long, vector<shared_ptr<Node<T>>>> levelNodes;
	if (!m_root)
		return m_root;
	nodes.push_back(m_root);
	levelNodes.emplace(0, nodes);
	while (!nodes.empty()) {
		nodes.clear();
		for (vector<shared_ptr<Node<T>>>::iterator it = levelNodes[level].begin(); it != levelNodes[level].end(); it++) {
			if (*it) {
				if ((*it)->Left())
					result = (*it)->Left();
				nodes.push_back((*it)->Left());
				if ((*it)->Right())
					result = (*it)->Right();
				nodes.push_back((*it)->Right());
			}
		}
		level++;
		if (!nodes.empty())
			levelNodes.emplace(level, nodes);
	}
	return result;
}