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
Tree<T>::Tree(Node<T> *node)
{
	map<Node<T>*, Node<T>*> copied;
	m_root = Copy(node, copied);
}

template<class T>
Tree<T>::Tree(Tree<T>& tree)
{
	map<Node<T>*, Node<T>*> copied;
	m_root = Copy(tree.Root(), copied);
}

template<class T>
Tree<T>::Tree(vector<T>& v)
{
	if (!v.empty())
		m_root = AddToTree(nullptr, v, 0, v.size() - 1);
}

template<class T>
Node<T>* Tree<T>::AddToTree(Node<T> *parent, vector<T>& v, int begin, int end)
{
	if (end < begin)
		return nullptr;
	int middle = begin + (end - begin) / 2 + (end - begin) % 2;
	Node<T> *node = new Node<T>(v[middle]);
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
		map<Node<T>*, Node<T>*> copied;
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
Node<T> *Tree<T>::Copy(Node<T> *node, map<Node<T>*, Node<T>*>& copied)
{
	if (node) {
		if (copied.find(node) != copied.end())
			return copied[node];
		Node<T> *n = new Node<T>(node);
		copied.emplace(node, n); // Map original tree node to new tree node
		n->SetLeft(Copy(node->Left(), copied));
		n->SetRight(Copy(node->Right(), copied));
		return n;
	} else
		return nullptr;
}

template<class T>
Node<T> *Tree<T>::Root()
{
	return m_root;
}

template<class T>
void Tree<T>::Clear(Node<T> *node)
{
	if (node) {
		Clear(node->Left());
		Clear(node->Right());
		delete node;
		node = nullptr;
	}
}

template<class T>
void Tree<T>::InsertItem(T item)
{
	Node<T> *node = new Node<T>(item);
	if (!m_root) {
		m_root = node;
	} else
		InsertNode(m_root, node);
}

// 50(root), -100, 0
template<class T>
void Tree<T>::InsertNode(Node<T> *root, Node<T> *node) // This will produce a Binary Search Tree
{
	if (root->Item() == node->Item()) { // No duplicate!
		delete node;
		node = nullptr;
	} else if (root->Item() > node->Item()) {
		if (root->Left())
			InsertNode(root->Left(), node);
		else {
			root->SetLeft(node);
			node->SetNext(root);
		}
	} else {
		if (root->Right())
			InsertNode(root->Right(), node);
		else {
			root->SetRight(node);
			node->SetNext(root);
		}
	}
}

template<class T>
void Tree<T>::Serialize(Node<T>* node, vector<T>& result) // In-Order serialization
{
	if (!node)
		return;
	Serialize(node->Left(), result);
	result.push_back(node->Item());
	Serialize(node->Right(), result);
}

template<class T>
Node<T>* Tree<T>::FindNode(T item)
{
	return m_root ? FindNode(m_root, item) : nullptr;
}

template<class T>
Node<T>* Tree<T>::FindNode(Node<T> *node, T item)
{
	Node<T> *p = nullptr;
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
Node<T>* Tree<T>::CommonAncestor(Node<T>* p, Node<T>* q)
{
	Node<T> *node;
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
bool Tree<T>::covers(Node<T>* node, Node<T>* p)
{
	if (!node || !p)
		return false;
	if (node == p)
		return true;
	return covers(node->Left(), p) || covers(node->Right(), p);
}

#if 0
template<class T>
Node<T>* Tree<T>::CommonAncestor1(Node<T>* node, Node<T>* p, Node<T>* q)
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
bool Tree<T>::SubTree(Node<T> *parent, Node<T> *child)
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
bool Tree<T>::MatchTree(Node<T> *p, Node<T> *q)
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
void Tree<T>::FindSum(Node<T>* node, long sum, vector<string>& result)
{
	vector<long> values;
	if (!node)
		return;
	FindSum(node, sum, 0, values, result); 
}

template<class T>
void Tree<T>::FindSum(Node<T>* node, long sum, long level, vector<long> values, vector<string>& result)
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
size_t Tree<T>::Count(Node<T> *node)
{
	return node ? 1 + Count(node->Left()) + Count(node->Right()) : 0;
}
template<class T>
size_t Tree<T>::Count()
{
	return m_root ? 1 + Count(m_root->Left()) + Count(m_root->Right()) : 0;
}
template<class T>
void Tree<T>::GetNodes(map<unsigned long, vector<Node<T>*>>& result, unsigned long lvl) // Typical Breadth-First-Search algorithm
{
	unsigned long level = 0;
	vector<Node<T>*> nodes;
	nodes.push_back(m_root);
	result.emplace(level, nodes);
	while (!nodes.empty() && (lvl == -1 || level <= lvl)) {
		nodes.clear();
		for (vector<Node<T>*>::const_iterator it = result[level].begin(); it != result[level].end(); it++) {
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
Node<T>* Tree<T>::InOrderSuccessor(Node<T>* node)
{
	if (node) {
		if (node->Right())
			return LeftMostChild(node->Right());
		else {
			for (Node<T>* p = node->Next(); p; node = p) {
				if (p->Left() == node)
					return p;
			}
		}
	}
	return nullptr;
}

template<class T>
Node<T>* Tree<T>::LeftMostChild(Node<T>* node)
{
	while (node && node->Left())
		node = node->Left();
	return node;
}

template<class T>
unsigned long Tree<T>::MinDepth(Node<T> *node)
{
	return node ? 1 + min(MinDepth(node->Left()), MinDepth(node->Right())) : 0;
}

template<class T>
unsigned long Tree<T>::MaxDepth(Node<T> *node)
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
T Tree<T>::MinDiffInBST(Node<T>* current, Node<T>* previous)
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
void Tree<T>::PrintColumns(Node<T> *node, long column, map<long, vector<T>*>& columns)
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
	vector<Node<T>*> nodes;
	map<long, vector<Node<T>*>> levels;
	nodes.push_back(m_root);
	levels.emplace(level, nodes);
	while (!nodes.empty()) {
		nodes.clear();
		for (vector<Node<T>*>::const_iterator it = levels[level].begin(); it != levels[level].end(); it++) {
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
	for (map<long, vector<Node<T>*>>::const_iterator it = levels.begin(); it != levels.end(); it++) {
		printOnce = true;
		for (vector<Node<T>*>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++) {
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
void Tree<T>::PrintNodeIterative(Node<T> *node)
{
	if (node) {
		stack<Node<T>*> nodes;
		stack<Node<T>*> toVisit;
		toVisit.push(node);
		while (!toVisit.empty())
		{
			Node<T> *n = toVisit.top();
			nodes.push(n);
			toVisit.pop();
			
		}
	}
}
#endif