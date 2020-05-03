#include "StdAfx.h"
#include "Tree.h"
#include <iostream>
using namespace std;
/*
 3 types of tree traversal:
 In-Order: Left node, current node, Right node
 Pre-Order: Current node, Left node, Right node
 Post-Prder: Left node, right node, current node
 */
/*
			Binary Tree:	  
				  50
			  -100   60 
			     0      100
			-50    10  75   150
			
			Binary Search Tree:
					50
				0			100
			-50	   10	75		150
		-100			60
 */
template class Tree<int>;
template class Tree<long>;

template<class T>
Tree<T>::Tree()
	: m_root(nullptr)
{
}

template<class T>
Tree<T>::Tree(T item)
	: m_root(new Node<T>(item))
{
}

template<class T>
Tree<T>::Tree(shared_ptr<Node<T>>node)
{
	map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> copied;
	m_root = Copy(node, copied);
}

template<class T>
Tree<T>::Tree(Tree<T>& tree)
{
	map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> copied;
	m_root = Copy(tree.Root(), copied);
}

template<class T>
Tree<T>::Tree(vector<T>& v)
{
	if (!v.empty())
		m_root = AddToTree(nullptr, v, 0, v.size() - 1);
}

template<class T>
shared_ptr<Node<T>> Tree<T>::AddToTree(shared_ptr<Node<T>>parent, vector<T>& v, long begin, long end)
{
	if (end < begin)
		return nullptr;
	long middle = begin + (end - begin) / 2 + (end - begin) % 2;
	shared_ptr<Node<T>>node = make_shared<Node<T>>(v[middle]);
	node->SetLeft(AddToTree(node, v, begin, middle - 1));
	node->SetRight(AddToTree(node, v, middle + 1, end));
	node->SetNext(parent);
	return node;
}

template<class T>
Tree<T>::~Tree()
{
	Clear(m_root);
}

template<class T>
Tree<T> &Tree<T>::operator=(Tree<T>& tree)
{
	if (this != &tree) {
		map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> copied;
		m_root = Copy(tree.Root(), copied);
	}
	return *this;
}

template<class T>
bool Tree<T>::operator==(Tree<T>& tree)
{
	return MatchTree(m_root, tree.Root());
}

template<class T>
shared_ptr<Node<T>> Tree<T>::Copy(shared_ptr<Node<T>>node, map<shared_ptr<Node<T>>, shared_ptr<Node<T>>>& copied)
{
	if (node) {
		if (copied.find(node) != copied.end())
			return copied[node];
		shared_ptr<Node<T>> n = make_shared<Node<T>>(node);
		copied.emplace(node, n); // Map original tree node to new tree node
		n->SetLeft(Copy(node->Left(), copied));
		n->SetRight(Copy(node->Right(), copied));
		return n;
	} else
		return nullptr;
}

template<class T>
shared_ptr<Node<T>> Tree<T>::Root()
{
	return m_root;
}

template<class T>
void Tree<T>::Clear(shared_ptr<Node<T>>node)
{
	if (node) {
		Clear(node->Left());
		Clear(node->Right());
		node.reset();
	}
}

template<class T>
void Tree<T>::InsertItem(T item)
{
	shared_ptr<Node<T>>node = make_shared<Node<T>>(item);
	if (!m_root)
		m_root = node;
	else
		InsertNode(m_root, node);
}

// 50(root), -100, 0
template<class T>
void Tree<T>::InsertNode(shared_ptr<Node<T>> parent, shared_ptr<Node<T>> node) // This will produce a Binary Search Tree
{
	if (parent->Item() == node->Item()) // No duplicate!
		node.reset();
	else if (parent->Item() > node->Item()) {
		if (parent->Left())
			InsertNode(parent->Left(), node);
		else {
			parent->SetLeft(node);
			node->SetNext(parent);
		}
	} else {
		if (parent->Right())
			InsertNode(parent->Right(), node);
		else {
			parent->SetRight(node);
			node->SetNext(parent);
		}
	}
}

template<class T>
void Tree<T>::Serialize(shared_ptr<Node<T>> node, vector<T>& result) // In-Order serialization
{
	if (!node)
		return;
	Serialize(node->Left(), result);
	result.push_back(node->Item());
	Serialize(node->Right(), result);
}

template<class T>
shared_ptr<Node<T>> Tree<T>::FindNode(T item)
{
	return m_root ? FindNode(m_root, item) : nullptr;
}

template<class T>
shared_ptr<Node<T>> Tree<T>::FindNode(shared_ptr<Node<T>>node, T item)
{
	shared_ptr<Node<T>> p = nullptr;
	if (node) {
		// Use Pre-Order traversal to find a match
		if (node->Item() == item)
			return node;
		p = FindNode(node->Left(), item);
		if (p)
			return p;
		p = FindNode(node->Right(), item);
	}
	return p;
}

template<class T>
shared_ptr<Node<T>> Tree<T>::CommonAncestor(shared_ptr<Node<T>> p, shared_ptr<Node<T>> q)
{
	shared_ptr<Node<T>>node;
	if (!p || !q)
		return nullptr;
	if (p->Next() == q->Next())
		return p->Next();
	else if (p->Next() == q)
		return q;
	else if (q->Next() == p)
		return p;
	for (node = p; node; node = node->Next())
		if (node == q)
			return q;
	for (node = q; node; node = node->Next())
		if (node == p)
			return p;
	return CommonAncestor(p->Next(), q->Next());
}

template<class T>
bool Tree<T>::covers(shared_ptr<Node<T>> node, shared_ptr<Node<T>> p)
{
	if (!node || !p)
		return false;
	if (node == p)
		return true;
	return covers(node->Left(), p) || covers(node->Right(), p);
}

#if 0
template<class T>
shared_ptr<Node<T>> Tree<T>::CommonAncestor1(shared_ptr<Node<T>> node, shared_ptr<Node<T>> p, shared_ptr<Node<T>> q)
{
	bool flags[4];
	flags[0] = covers(node->Left(), p);
	flags[1] = covers(node->Left(), q);
	if (flags[0] & flags[1])
		CommonAncestor1(node->Left(), p, q);

	flags[2] = covers(node->Right(), p);
	flags[3] = covers(node->Right(), q);
	if (flags[2] & flags[3])
		CommonAncestor1(node->Right(), p, q);
	if (!(flags[0] | flags[1] | flags[2] | flags[3]))
		return nullptr;
	return node;
}
#endif

template<class T>
bool Tree<T>::SubTree(shared_ptr<Node<T>>parent, shared_ptr<Node<T>>child)
{
	if (!parent && !child)
		return true;
	if (!parent)
		return false;
	if (!child)
		return true;
	//if (*parent == *child && MatchTree(parent, child)) Don't compare parent/next node
	if (parent->Item() == child->Item() && MatchTree(parent, child))
		return true;
	return SubTree(parent->Left(), child) || SubTree(parent->Right(), child);
}

template<class T>
bool Tree<T>::MatchTree(shared_ptr<Node<T>>p, shared_ptr<Node<T>>q)
{
	if (!p && !q)
		return true; // Nothing left in the subtree
	if (!p)
		return false; // Big tree empty and subtree still not found
	if (!q)
		return true; // Finished matching all the subtree nodes
	//if (*p != *q) Don't compare parent/next node
	if (p->Item() != q->Item())
		return false;  // Stop condition: current nodes do NOT match
	return MatchTree(p->Left(), q->Left()) && MatchTree(p->Right(), q->Right());
}

template<class T>
void Tree<T>::FindSum(shared_ptr<Node<T>> node, long sum, vector<string>& result)
{
	vector<long> values;
	if (!node)
		return;
	FindSum(node, sum, 0, values, result); 
}

template<class T>
void Tree<T>::FindSum(shared_ptr<Node<T>> node, long sum, long level, vector<long> values, vector<string>& result)
{
	ostringstream oss;
	if (!node)
		return;
	long tmp = sum;
	values.push_back(node->Item());
	for (long i = level; i >= 0	; i--) { // From leaf to root
		tmp -= values[i];
		if (!tmp) {
			for (long j = i; j <= level; j++) {// From root to leaf
				oss << values[j];
				if (j != level)
					oss << " ";
			}
			result.push_back(oss.str());
			oss.str("");
		}
	}
	FindSum(node->Left(), sum, level + 1, values, result);
	FindSum(node->Right(), sum, level + 1, values, result);
}

template<class T>
size_t Tree<T>::Count(shared_ptr<Node<T>>node)
{
	return node ? 1 + Count(node->Left()) + Count(node->Right()) : 0;
}
template<class T>
size_t Tree<T>::Count()
{
	return m_root ? 1 + Count(m_root->Left()) + Count(m_root->Right()) : 0;
}
template<class T>
void Tree<T>::GetNodes(map<size_t, vector<shared_ptr<Node<T>>>>& result, long lvl) // Typical Breadth-First-Search algorithm
{
	unsigned long level = 0;
	vector<shared_ptr<Node<T>>> nodes;
	nodes.push_back(m_root);
	result.emplace(level, nodes);
	while (!nodes.empty() && (lvl == -1 || level <= lvl)) {
		nodes.clear();
		for (vector<shared_ptr<Node<T>>>::const_iterator it = result[level].begin(); it != result[level].end(); it++) {
			if (*it) {
				if ((*it)->Left())
					nodes.push_back((*it)->Left());
				if ((*it)->Right())
					nodes.push_back((*it)->Right());
			}
		}
		level++;
		if (!nodes.empty())
			result.emplace(level, nodes);
	}
}
// In-Order: Traverse left node, current node, then right [usually used for binary search trees]
// Pre - Order: Traverse current node, then left node, then right node.
// Post - Order : Traverse left node, then right node, then current node.
template<class T>
shared_ptr<Node<T>> Tree<T>::InOrderSuccessor(shared_ptr<Node<T>> node)
{
	/*
Binary Tree content:
Level 0:                50
Level 1:      -100(50)        60(50)
Level 2:            0(-100)         100(60)
Level 3:       -50(0)     10(0)  75(100)   150(100)
	*/
	if (node) {
		if (node->Right()) // If node as right child, the in-order successor must be on the right side of the node
			return LeftMostChild(node->Right()); // Then the left-most child must be the first node visisted in that subtree
		else {
			for (shared_ptr<Node<T>> n = node->Next(); n; node = n, n = n->Next())
				if (n->Left() == node) // If node is the left child of n, then n must be the in-order successor of node.
					return n;
		}
	}
	return nullptr;
}

template<class T>
shared_ptr<Node<T>> Tree<T>::LeftMostChild(shared_ptr<Node<T>> node)
{
	while (node && node->Left())
		node = node->Left();
	return node;
}

template<class T>
unsigned long Tree<T>::MinDepth(shared_ptr<Node<T>>node)
{
	return node ? 1 + min(MinDepth(node->Left()), MinDepth(node->Right())) : 0;
}

template<class T>
unsigned long Tree<T>::MaxDepth(shared_ptr<Node<T>>node)
{
	return node ? 1 + max(MaxDepth(node->Left()), MaxDepth(node->Right())) : 0;
}

template<class T>
bool Tree<T>::IsBalancedTree()
{
	return MaxDepth(m_root) - MinDepth(m_root) <= 1;
}

template<class T>
T Tree<T>::MinDiffInBST()
{
	return m_root ? MinDiffInBST(m_root, nullptr) : -1;
}
template<class T>
T Tree<T>::MinDiffInBST(shared_ptr<Node<T>> current, shared_ptr<Node<T>> previous)
{
	T minimum = LONG_MAX;
	// Use In-Order traversal to find min diff between any 2 nodes
	if (current) {
		minimum = MinDiffInBST(current->Left(), current);
		if (previous)
			minimum = min(minimum, abs(current->Item() - previous->Item()));
		minimum = min(minimum, MinDiffInBST(current->Right(), current));
	}
	return minimum;
}
template<class T>
void Tree<T>::PrintTreeColumns()
{
	map<long, vector<T>*> columns;
	// Use In-Order traversal to print node values
	if (m_root) {
		vector<T>* list = new vector<T>();
		list->push_back(m_root->Item());
		columns.emplace(0, list);
		PrintColumns(m_root, 0, columns);
		for (map<long, vector<T>*>::iterator it = columns.begin(); it != columns.end(); it++)
			for (vector<T>::iterator it1 = it->second->begin(); it1 != it->second->end(); it1++)
				cout << *it1 << ", ";
		cout << endl;
	}
}
template<class T>
void Tree<T>::AddToColumn(T value, long column, map<long, vector<T>*>& columns)
{
	if (columns.find(column) == columns.end())
	{
		vector<T>* list = new vector<T>();
		list->push_back(value);
		columns.emplace(column, list);
	} else
		columns[column]->push_back(value);
}
template<class T>
void Tree<T>::PrintColumns(shared_ptr<Node<T>>node, long column, map<long, vector<T>*>& columns)
{
	// Use Pre-Order traversal
	if (node) {
		if (node->Left())
			AddToColumn(node->Left()->Item(), column - 1, columns);
		if (node->Right())
			AddToColumn(node->Right()->Item(), column + 1, columns);
		PrintColumns(node->Left(), column - 1, columns);
		PrintColumns(node->Right(), column + 1, columns);
	}
}
template<class T>
void Tree<T>::PrintTree()
{
	// Use Pre-Order traversal to print node values
	if (!m_root) {
		cout << "Empty tree!" << endl;
		return;
	}
	unsigned long level = 0;
	vector<shared_ptr<Node<T>>> nodes;
	map<long, vector<shared_ptr<Node<T>>>> levels;
	nodes.push_back(m_root);
	levels.emplace(level, nodes);
	while (!nodes.empty()) {
		nodes.clear();
		for (vector<shared_ptr<Node<T>>>::const_iterator it = levels[level].begin(); it != levels[level].end(); it++) {
			if (*it) {
				if ((*it)->Left())
					nodes.push_back((*it)->Left());
				if ((*it)->Right())
					nodes.push_back((*it)->Right());
			}
		}
		level++;
		if (!nodes.empty())
			levels.emplace(level, nodes);
	}
	long lvl = 0;
	bool printOnce = true;
	for (map<long, vector<shared_ptr<Node<T>>>>::const_iterator it = levels.begin(); it != levels.end(); it++) {
		printOnce = true;
		for (vector<shared_ptr<Node<T>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++) {
			if (printOnce) {
				cout << "Level " << lvl << ": ";
				for (size_t i = 0; i < level; i++)
					cout << "\t";
				printOnce = false;
				level--;
				lvl++;
			}
			cout << (*it1)->Item();
			if ((*it1)->Next())
				cout << "(" << (*it1)->Next()->Item() << ") ";
			cout << "\t";
		}
		cout << endl;
	}
}
#if 0
template<class T>
void Tree<T>::PrintNodeIterative(shared_ptr<Node<T>>node)
{
	if (node) {
		stack<shared_ptr<Node<T>>> nodes;
		stack<shared_ptr<Node<T>>> toVisit;
		toVisit.push(node);
		while (!toVisit.empty())
		{
			shared_ptr<Node<T>>n = toVisit.top();
			nodes.push(n);
			toVisit.pop();
			
		}
	}
}
#endif