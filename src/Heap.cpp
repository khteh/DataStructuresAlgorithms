#include "pch.h"
#include "Heap.h"
#include <assert.h>
using namespace std;
template class Heap<int>;
template class Heap<long>;
template class Heap<size_t>;
template class Heap<float>;
template class Heap<double>;
template class Heap<string>;
// http://en.wikipedia.org/wiki/Binary_heap

template <typename T>
Heap<T>::Heap(HeapType t)
	: _type(t)
{
}

template <typename T>
Heap<T>::Heap(T item, HeapType t)
	: _type(t), Tree<T>::Tree(item)
{
}

template <typename T>
Heap<T>::Heap(shared_ptr<Node<T>> &node, HeapType t)
	: _type(t), Tree<T>::Tree(node)
{
}
template <typename T>
Heap<T>::Heap(vector<T> &data, HeapType type)
	: _type(type)
{
	for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
		InsertItem(*it);
}
template <typename T>
void Heap<T>::InsertNode(shared_ptr<Node<T>> &root, shared_ptr<Node<T>> &node)
{
	if (node)
	{
		shared_ptr<Node<T>> p = FindEmptyLeafParent();
		assert(p);
		if (p)
		{
			if (!p->Left())
			{
				p->SetLeft(node);
				node->SetNext(p);
			}
			else
			{
				p->SetRight(node);
				node->SetNext(p);
			}
			HeapifyUp(node, MaxDepth(_root) - 1 /* 0-based */);
		}
	}
}

// MinHeap/MinMaxHeap: Remove min
// MaxHeap: Remove max
template <typename T>
shared_ptr<Node<T>> Heap<T>::pop()
{
	shared_ptr<Node<T>> result(nullptr), node(nullptr);
	if (_root)
	{
		result = make_shared<Node<T>>(_root->Item());
		node = FindLastLeaf();
		if (node && node != _root)
		{
			swap(node, _root);
			shared_ptr<Node<T>> p(node->Next());
			if (p)
			{ // If not the only node left (= _root)
				if (p->Left() == node)
					p->SetLeft(nullptr);
				else if (p->Right() == node)
					p->SetRight(nullptr);
				else
					assert(false);
			}
			node.reset();
		}
		else if (_root)
			_root.reset();
		if (_root)
			HeapifyDown(_root);
	}
	return result;
}

template <typename T>
shared_ptr<Node<T>> Heap<T>::front()
{
	return _root;
}

template <typename T>
void Heap<T>::Serialize(vector<T> &result)
{
	shared_ptr<Node<T>> node;
	while (node = pop())
		result.push_back(node->Item());
}

template <typename T>
void Heap<T>::swap(shared_ptr<Node<T>> &n, shared_ptr<Node<T>> &m)
{
	T tmp(n->Item());
	n->SetItem(m->Item());
	m->SetItem(tmp);
}

template <typename T>
void Heap<T>::HeapifyUp(shared_ptr<Node<T>> &node, unsigned long level)
{
	if (node && level >= 0)
	{
		switch (_type)
		{
		case HeapType::MinHeap:
			if (node->Next() && *node < *node->Next())
			{
				shared_ptr<Node<T>> n(node->Next());
				swap(node, n);
				n = node->Next();
				HeapifyUp(n);
			}
			break;
		case HeapType::MaxHeap:
			if (node->Next() && *node > *node->Next())
			{
				shared_ptr<Node<T>> n(node->Next());
				swap(node, n);
				n = node->Next();
				HeapifyUp(n);
			}
			break;
		case HeapType::MinMaxHeap: // http://en.wikipedia.org/wiki/Min-max_heap
		{
			bool isMaxLevel = level % 2;
			shared_ptr<Node<T>> grandparent = nullptr;
			if (isMaxLevel)
			{ // parent is at Min Level
				if (node->Next() && *node < *node->Next())
				{
					// Item is smaller than parent(Min) and all items at Max levels. Only need to check the Min levels
					shared_ptr<Node<T>> n(node->Next());
					swap(node, n);
					n = node->Next();
					HeapifyUp(n, --level);
				}
				else if (node->Next())
				{
					// Item is greater than parent => Check with Max levels
					if (node->Next()->Next())
						grandparent = node->Next()->Next();
					if (grandparent && *node > *grandparent)
					{
						swap(node, grandparent);
						level -= 2;
						HeapifyUp(grandparent, level);
					}
				}
			}
			else
			{ // Min Level. Parent at Max Level.
				if (node->Next() && *node > *node->Next())
				{
					// Item is greater than parent and all items at Min levels. Only need to check the Max levels
					shared_ptr<Node<T>> n(node->Next());
					swap(node, n);
					n = node->Next();
					HeapifyUp(n, --level);
				}
				else if (node->Next())
				{
					// Item is smaller than parent => Check with the Min levels.
					if (node->Next()->Next())
						grandparent = node->Next()->Next();
					if (grandparent && *node < *grandparent)
					{
						swap(node, grandparent);
						level -= 2;
						HeapifyUp(grandparent, level);
					}
				}
				else
				{ // Root of the tree (Min level) in a Min-Max Heap
					if (node->Left() && *node > *node->Left())
					{
						shared_ptr<Node<T>> n(node->Left());
						swap(node, n);
					}
					else if (node->Right() && *node > *node->Right())
					{
						shared_ptr<Node<T>> n(node->Right());
						swap(node, n);
					}
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

template <typename T>
void Heap<T>::HeapifyDown(shared_ptr<Node<T>> &node)
{
	if (node)
	{
		switch (_type)
		{
		case HeapType::MinHeap:
			if (node->Left() && *node > *node->Left())
			{ // Next minimum must come from the left branch since the tree is filled from left to right
				shared_ptr<Node<T>> n(node->Left());
				swap(node, n);
				n = node->Left();
				HeapifyDown(n);
			}
			if (node->Right() && *node > *node->Right())
			{ // Next minimum must come from the left branch since the tree is filled from left to right
				shared_ptr<Node<T>> n(node->Right());
				swap(node, n);
				n = node->Right();
				HeapifyDown(n);
			}
			break;
		case HeapType::MaxHeap:
			if (node->Left() && *node < *node->Left())
			{ // Next minimum must come from the left branch since the tree is filled from left to right
				shared_ptr<Node<T>> n(node->Left());
				swap(node, n);
				n = node->Left();
				HeapifyDown(n);
			}
			if (node->Right() && *node < *node->Right())
			{ // Next minimum must come from the left branch since the tree is filled from left to right
				shared_ptr<Node<T>> n(node->Right());
				swap(node, n);
				n = node->Right();
				HeapifyDown(n);
			}
			break;
		case HeapType::MinMaxHeap: // http://en.wikipedia.org/wiki/Min-max_heap
			// Find minimum
			// 1. x.key <= h[m].key. x must be inserted into the root. (x is already at root position when this function is called)
			// 2. x.key > h[m].key and m is child of the root.since m is in max level, it has no descendants.So the element h[m] is moved to the root and x is inserted into node m.
			// 3. x.key > h[m].key and m is grandchild of the root.So the element h[m] is moved to the root.Let p be parent of m. if x.key > h[p].key then h[p] and x are interchanged.
			if (MaxDepth(node) == 2)
			{ // Condition 2
				if (node->Left() && *node > *node->Left())
				{
					shared_ptr<Node<T>> n(node->Left());
					swap(node, n);
				}
				if (node->Right() && *node > *node->Right())
				{
					shared_ptr<Node<T>> n(node->Right());
					swap(node, n);
				}
			}
			else if (MaxDepth(node) > 2)
			{ // Condition 3
				shared_ptr<Node<T>> min(node);
				map<size_t, vector<shared_ptr<Node<T>>>> nodes;
				GetNodes(nodes, 2);
				assert(!nodes[2].empty());
				for (typename vector<shared_ptr<Node<T>>>::iterator it = nodes[2].begin(); it != nodes[2].end(); it++)
				{
					if (*min > *(*it))
						min = *it;
				}
				if (*node > *min)
				{
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

template <typename T>
shared_ptr<Node<T>> Heap<T>::FindEmptyLeafParent() // Use Breath-First-Search to find empty leaf
{
	unsigned long level = 0;
	map<unsigned long, vector<shared_ptr<Node<T>>>> levelNodes;
	if (!_root)
		return _root;
	levelNodes.emplace(0, vector<shared_ptr<Node<T>>>{_root});
	for (; !levelNodes[level].empty(); level++)
	{
		vector<shared_ptr<Node<T>>> nodes;
		for (typename vector<shared_ptr<Node<T>>>::iterator it = levelNodes[level].begin(); it != levelNodes[level].end(); it++)
		{
			assert(*it);
			if (*it)
			{
				if ((*it)->Right() && !(*it)->Left())
					throw runtime_error("Cannot have right child without left child. This violates the Heap shape property!");
				if (!(*it)->Left())
					return *it;
				nodes.push_back((*it)->Left());
				if (!(*it)->Right())
					return *it;
				nodes.push_back((*it)->Right());
			}
		}
		if (!nodes.empty())
			levelNodes.emplace(level + 1, nodes);
	}
	return nullptr;
}

template <typename T>
shared_ptr<Node<T>> Heap<T>::FindLastLeaf() // Use Breadth-First-Search to find empty leaf
{
	shared_ptr<Node<T>> result(nullptr);
	unsigned long level = 0;
	map<unsigned long, vector<shared_ptr<Node<T>>>> levelNodes;
	if (!_root)
		return _root;
	levelNodes.emplace(0, vector<shared_ptr<Node<T>>>{_root});
	for (; !levelNodes[level].empty(); level++)
	{
		vector<shared_ptr<Node<T>>> nodes;
		for (typename vector<shared_ptr<Node<T>>>::iterator it = levelNodes[level].begin(); it != levelNodes[level].end(); it++)
		{
			if (*it)
			{
				if ((*it)->Left())
				{
					result = (*it)->Left();
					nodes.push_back((*it)->Left());
				}
				if ((*it)->Right())
				{
					result = (*it)->Right();
					nodes.push_back((*it)->Right());
				}
			}
		}
		if (!nodes.empty())
			levelNodes.emplace(level + 1, nodes);
	}
	return result;
}