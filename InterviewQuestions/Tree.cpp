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
template class Tree<size_t>;
template<typename T>
Tree<T>::Tree()
	: m_root(nullptr)
{
}

template<typename T>
Tree<T>::Tree(T item)
	: m_root(make_shared<Node<T>>(item))
{
}

template<typename T>
Tree<T>::Tree(shared_ptr<Node<T>>& node)
{
	map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> copied;
	m_root = Copy(node, copied);
}

template<typename T>
Tree<T>::Tree(Tree<T>& tree)
{
	map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> copied;
	m_root = Copy(tree.Root(), copied);
}

template<typename T>
Tree<T>::Tree(vector<T>& v, TreeType type)
{
	if (!v.empty()) {
		switch (type) {
		case TreeType::BinarySearch:
			sort(v.begin(), v.end());
			m_root = AddToTree(nullptr, v, 0, v.size() - 1);
			break;
		case TreeType::Binary:
			m_root = AddToTree(v);
			break;
		default:
			throw runtime_error("Invalid Tree type!");
		}
		for (shared_ptr<Node<T>> n = m_root; n; minStack.push(n), n = n->Left());
		for (shared_ptr<Node<T>> n = m_root; n; maxStack.push(n), n = n->Right());
	}
}
template<typename T>
Tree<T>::Tree(TraversalType type, vector<T>& inorder, vector<T>& otherorder)
{
	if (!otherorder.empty() && !inorder.empty() && otherorder.size() == inorder.size()) {
		switch (type) {
		case TraversalType::PreOrder:
			m_root = BuildTreePreOrder(inorder, otherorder, 0, 0, inorder.size() - 1);
			break;
		case TraversalType::PostOrder:
			m_root = BuildTreePostOrder(inorder, otherorder, otherorder.size() - 1, 0, inorder.size() - 1);
			break;
		default:
			throw runtime_error("Invalid traversal type!");
			break;
		}
	}
}
template<typename T>
Tree<T>::~Tree()
{
	Clear();
}
/* https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
* 100%
*/
template<typename T>
shared_ptr<Node<T>> Tree<T>::BuildTreePreOrder(vector<T>& inorder, vector<T>& preorder, long prestart, long instart, long inend)
{
	shared_ptr<Node<T>> root = nullptr;
	if (instart == inend)
		return make_shared<Node<T>>(inorder[instart]);
	else if (prestart < preorder.size() && inend >= 0 && inend > instart) {
		vector<T>::iterator it = find(inorder.begin() + instart, inorder.begin() + instart + (inend - instart) + 1, preorder[prestart]);
		if (it == (inorder.begin() + instart + (inend - instart) + 1))
			throw runtime_error("Invalid tree input parameters! No root found!");
		root = make_shared<Node<T>>(preorder[prestart]);
		size_t middle = distance(inorder.begin(), it);
		/*
		*             0   1   2  3  4   5  6
		* preorder = [{3},<9>,5,10,<20>,15,7]
		* inorder  = [5,  9, 10,{3},15,20, 7]
		*		 3
		*	<9>      <20>
		* 5    10  15    7
		*/
		shared_ptr<Node<T>> left = BuildTreePreOrder(inorder, preorder, prestart + 1, instart, middle - 1);
		shared_ptr<Node<T>> right = BuildTreePreOrder(inorder, preorder, prestart + middle - instart + 1, middle + 1, inend);
		root->SetLeft(left);
		root->SetRight(right);
		if (left)
			left->SetNext(root);
		if (right)
			right->SetNext(root);
	}
	return root;
}
/* https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
* 100%
*/
template<typename T>
shared_ptr<Node<T>> Tree<T>::BuildTreePostOrder(vector<T>& inorder, vector<T>& postorder, long pstart, long instart, long inend)
{
	shared_ptr<Node<T>> root = nullptr;
	if (instart == inend)
		return make_shared<Node<T>>(inorder[instart]);
	else if (pstart >= 0 && inend >= 0 && inend > instart) {
		vector<T>::iterator it = find(inorder.begin() + instart, inorder.begin() + instart + (inend - instart) + 1, postorder[pstart]);
		if (it == inorder.begin() + instart + (inend - instart) + 1)
			throw runtime_error("Invalid tree input parameters! No root found!");
		root = make_shared<Node<T>>(postorder[pstart]);
		size_t middle = distance(inorder.begin(), it);
		/*
		*              0   1    2  3    4
		* postorder = [<9>,15,  7,<20>,{3}] => left offset: 4 - 3 - 1 = 0
		* inorder   = [9,  {3},15,20,   7]	=> right size: 5 - 1 -1 = 3
		*       3
		*   <9>   <20>
		*       15   7
		* 
		*              0  1  2    3   4
		* postorder = [7,15,<9>,<20>,{3}] => left offset: 4 - 1 - 1 = 2	 ;
		* inorder   = [7,9, 15,  {3},20] => right size: 5 - 3 - 1 = 1    ; 0 -
		*       3
		*   <9>   <20>
		* 7    15
		*              0 1  2   3
		* portorder = [2,1,<3>,{4}] => left offset: 3 - 2 = 2; 2 - 1 = 1
		* inorder   = [1,2, 3, {4}]	=> right size: 4 - 3 = 1; 3 - 2 = 1
		*        4
		*    3
		*  1
		*    2
		*/
		size_t rightSize = inend - middle + 1;
		size_t leftOffset = pstart - rightSize;
		shared_ptr<Node<T>> left = BuildTreePostOrder(inorder, postorder, leftOffset, instart, middle - 1);
		shared_ptr<Node<T>> right = BuildTreePostOrder(inorder, postorder, pstart - 1, middle + 1, inend);
		root->SetLeft(left);
		root->SetRight(right);
		if (left)
			left->SetNext(root);
		if (right)
			right->SetNext(root);
	}
	return root;
}
/*
* Use this to construct BST using In-Order traversal.
*/
template<typename T>
shared_ptr<Node<T>> Tree<T>::AddToTree(shared_ptr<Node<T>> parent, vector<T>& v, long begin, long end)
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
/*
* Use this to construct a Binary Tree where left child = 2i + 1 and right child = 2i + 2 (0-based index)
* Use numeric_limit<T>::min() to indicate null child.
*/
template<typename T>
shared_ptr<Node<T>> Tree<T>::AddToTree(vector<T>& v)
{
	map<long, shared_ptr<Node<T>>> nodes;
	long maxIndex = (v.size() - 2) / 2;
	for (long i = 0; i <= maxIndex; i++) {
		if (v[i] != numeric_limits<T>::min()) {
			if (nodes.find(i) == nodes.end())
				nodes.emplace(i, make_shared<Node<T>>(v[i]));
			long left = 2 * i + 1;
			if (v[left] != numeric_limits<T>::min()) {
				if (nodes.find(left) == nodes.end())
					nodes.emplace(left, make_shared<Node<T>>(v[left]));
				nodes[i]->SetLeft(nodes[left]);
				nodes[left]->SetNext(nodes[i]);
			}
			long right = 2 * i + 2;
			if (right < v.size()) {
				if (v[right] != numeric_limits<T>::min()) {
					if (nodes.find(right) == nodes.end())
						nodes.emplace(right, make_shared<Node<T>>(v[right]));
					nodes[i]->SetRight(nodes[right]);
					nodes[right]->SetNext(nodes[i]);
				}
			}
		}
	}
	return !v.empty() ? nodes[0] : nullptr;
}
template<typename T>
Tree<T> &Tree<T>::operator=(Tree<T>& tree)
{
	if (this != &tree) {
		map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> copied;
		m_root = Copy(tree.Root(), copied);
	}
	return *this;
}

template<typename T>
bool Tree<T>::operator==(Tree<T>& tree)
{
	return MatchTree(m_root, tree.Root());
}

template<typename T>
shared_ptr<Node<T>> Tree<T>::Copy(shared_ptr<Node<T>>& node, map<shared_ptr<Node<T>>, shared_ptr<Node<T>>>& copied)
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
template<typename T>
shared_ptr<Node<T>> Tree<T>::Root()
{
	return m_root;
}
template<typename T>
void Tree<T>::Clear()
{
	for (; !minStack.empty(); minStack.pop());
	for (; !maxStack.empty(); maxStack.pop());
	if (m_root) {
		Clear(m_root->Left());
		Clear(m_root->Right());
		m_root.reset();
	}
}
template<typename T>
void Tree<T>::Clear(shared_ptr<Node<T>>& node)
{
	if (node) {
		Clear(node->Left());
		Clear(node->Right());
		node.reset();
	}
}
template<typename T>
void Tree<T>::InsertItem(T item)
{
	shared_ptr<Node<T>>node = make_shared<Node<T>>(item);
	if (!m_root)
		m_root = node;
	else
		InsertNode(m_root, node);
}

// 50(root), -100, 0
template<typename T>
void Tree<T>::InsertNode(shared_ptr<Node<T>>& parent, shared_ptr<Node<T>>& node) // This will produce a Binary Search Tree
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

template<typename T>
void Tree<T>::Serialize(shared_ptr<Node<T>>& node, vector<T>& result) // In-Order serialization
{
	if (!node)
		return;
	Serialize(node->Left(), result);
	result.push_back(node->Item());
	Serialize(node->Right(), result);
}

template<typename T>
shared_ptr<Node<T>> Tree<T>::FindNode(T item)
{
	return m_root ? FindNode(m_root, item) : nullptr;
}

template<typename T>
shared_ptr<Node<T>> Tree<T>::FindNode(shared_ptr<Node<T>>& node, T item)
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

template<typename T>
shared_ptr<Node<T>> Tree<T>::CommonAncestor(shared_ptr<Node<T>>& p, shared_ptr<Node<T>>& q)
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

template<typename T>
bool Tree<T>::covers(shared_ptr<Node<T>>& node, shared_ptr<Node<T>>& p)
{
	if (!node || !p)
		return false;
	if (node == p)
		return true;
	return covers(node->Left(), p) || covers(node->Right(), p);
}

#if 0
template<typename T>
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

template<typename T>
bool Tree<T>::SubTree(shared_ptr<Node<T>>& parent, shared_ptr<Node<T>>& child)
{
	if (!parent && !child)
		return true;
	if (!parent)
		return false;
	if (!child)
		return true;
	//if (*parent == *child && MatchTree(parent, child)) Don't compare parent/next node, i.e, "upstream" nodes
	if (parent->Item() == child->Item() && MatchTree(parent, child))
		return true;
	return SubTree(parent->Left(), child) || SubTree(parent->Right(), child);
}

template<typename T>
bool Tree<T>::MatchTree(shared_ptr<Node<T>>& p, shared_ptr<Node<T>>& q)
{
	if (!p && !q)
		return true; // Nothing left in the subtree
	if (!p)
		return false; // Big tree empty and subtree still not found
	if (!q)
		return true; // Finished matching all the subtree nodes
	//if (*p != *q) Don't compare parent/next node, i.e, "upstream" nodes
	if (p->Item() != q->Item())
		return false;  // Stop condition: current nodes do NOT match
	return MatchTree(p->Left(), q->Left()) && MatchTree(p->Right(), q->Right());
}

template<typename T>
void Tree<T>::FindSum(shared_ptr<Node<T>>& node, long sum, vector<string>& result)
{
	vector<long> values;
	if (node)
		FindSum(node, sum, 0, values, result); 
}

template<typename T>
void Tree<T>::FindSum(shared_ptr<Node<T>>& node, long sum, long level, vector<long> values, vector<string>& result)
{
	/*
Binary Tree content:
Level 0:                50
Level 1:      -100(50)        60(50)
Level 2:            0(-100)         100(60)
Level 3:       -50(0)     10(0)  75(100)   150(100)
	*/
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
		}
	}
	FindSum(node->Left(), sum, level + 1, values, result);
	FindSum(node->Right(), sum, level + 1, values, result);
}
/* https://leetcode.com/problems/sum-root-to-leaf-numbers/
* 100%
*/
template<typename T>
T Tree<T>::SumRoot2LeafNumbers()
{
	if (m_root) {
		vector<string> result = GetRoot2LeafNumbers(m_root);
		T sum = 0;
		for (vector<string>::iterator it = result.begin(); it != result.end(); it++) {
			T tmp;
			istringstream (*it) >> tmp;
			sum += tmp;
		}
		return sum;
	}
	return T();
}
template<typename T>
vector<string> Tree<T>::GetRoot2LeafNumbers(shared_ptr<Node<T>>& node)
{
	vector<string> result;
	if (node) {
		vector<string> left = GetRoot2LeafNumbers(node->Left());
		if (!left.empty()) {
			for (vector<string>::iterator it = left.begin(); it != left.end(); it++) {
				string str = to_string(node->Item());
				result.push_back(str.append(*it));
			}
		}
		vector<string> right = GetRoot2LeafNumbers(node->Right());
		if (!right.empty()) {
			for (vector<string>::iterator it = right.begin(); it != right.end(); it++) {
				string str = to_string(node->Item());
				result.push_back(str.append(*it));
			}
		}
		if (left.empty() && right.empty())
			result.push_back(to_string(node->Item()));
	}
	return result;
}
template<typename T>
size_t Tree<T>::Count(shared_ptr<Node<T>>& node)
{
	return node ? 1 + Count(node->Left()) + Count(node->Right()) : 0;
}
template<typename T>
size_t Tree<T>::Count()
{
	return m_root ? 1 + Count(m_root->Left()) + Count(m_root->Right()) : 0;
}
template<typename T>
void Tree<T>::GetNodes(map<size_t, vector<shared_ptr<Node<T>>>>& result, long lvl) // Typical Breadth-First-Search algorithm
{
	long level = 0;
	result.emplace(level, vector<shared_ptr<Node<T>>>{m_root});
	for (; !result[level].empty() && (lvl == -1 || level <= lvl); level++) {
		vector<shared_ptr<Node<T>>> nodes;
		for (vector<shared_ptr<Node<T>>>::const_iterator it = result[level].begin(); it != result[level].end(); it++) {
			if (*it) {
				if ((*it)->Left())
					nodes.push_back((*it)->Left());
				if ((*it)->Right())
					nodes.push_back((*it)->Right());
			}
		}
		if (!nodes.empty())
			result.emplace(level + 1, nodes);
	}
}
// In-Order: Traverse left node, current node, then right [usually used for binary search trees]
// Pre - Order: Traverse current node, then left node, then right node.
// Post - Order : Traverse left node, then right node, then current node.
template<typename T>
shared_ptr<Node<T>> Tree<T>::InOrderSuccessor(shared_ptr<Node<T>>& node)
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

template<typename T>
shared_ptr<Node<T>> Tree<T>::LeftMostChild(shared_ptr<Node<T>>& node)
{
	while (node && node->Left())
		node = node->Left();
	return node;
}

template<typename T>
size_t Tree<T>::MinDepth(shared_ptr<Node<T>>& node)
{
	return node ? 1 + min(MinDepth(node->Left()), MinDepth(node->Right())) : 0;
}

template<typename T>
size_t Tree<T>::MaxDepth(shared_ptr<Node<T>>& node)
{
	return node ? 1 + max(MaxDepth(node->Left()), MaxDepth(node->Right())) : 0;
}

template<typename T>
bool Tree<T>::IsBalancedTree()
{
	return MaxDepth(m_root) - MinDepth(m_root) <= 1;
}

template<typename T>
T Tree<T>::MinDiffInBST()
{
	return m_root ? MinDiffInBST(nullptr, m_root) : -1;
}
template<typename T>
T Tree<T>::MinDiffInBST(shared_ptr<Node<T>> previous, shared_ptr<Node<T>> current)
{
	T minimum = numeric_limits<T>::max();
	// Use In-Order traversal to find min diff between any 2 nodes
	if (current) {
		minimum = MinDiffInBST(current, current->Left());
		if (previous)
			minimum = min((long)minimum, abs((long)current->Item() - (long)previous->Item()));
		minimum = min(minimum, MinDiffInBST(current, current->Right()));
	}
	return minimum;
}
template<typename T>
T Tree<T>::MinSubTreesDifference()
{
	return m_root ? m_root->MinSubTreesDifference() : 0;
}
template<typename T>
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
template<typename T>
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
template<typename T>
void Tree<T>::PrintColumns(shared_ptr<Node<T>>& node, long column, map<long, vector<T>*>& columns)
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
template<typename T>
void Tree<T>::PrintTree()
{
	// Use Pre-Order traversal to print node values
	if (!m_root) {
		cout << "Empty tree!" << endl;
		return;
	}
	map<size_t, vector<shared_ptr<Node<T>>>> levels;
	GetNodes(levels);
	if (!levels.empty()) {
		long lvl = 0;
		map<size_t, vector<shared_ptr<Node<T>>>>::reverse_iterator maxKeyIterator = levels.rbegin();
		size_t level = maxKeyIterator->first;
		for (map<size_t, vector<shared_ptr<Node<T>>>>::const_iterator it = levels.begin(); it != levels.end(); it++) {
			bool printOnce = true;
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
}
template<typename T>
T Tree<T>::GetMin()
{
	return m_root ? GetMin(m_root) : numeric_limits<T>::max();
}
template<typename T>
T Tree<T>::GetMin(shared_ptr<Node<T>>& n)
{
	T minimum = numeric_limits<T>::max();
	if (n) {
		minimum = min(n->Item(), GetMin(n->Left()));
		minimum = min(minimum, GetMin(n->Right()));
	}
	return minimum;
}
template<typename T>
vector<size_t> Tree<T>::GetLevelNodeCount()
{
	return GetLevelNodeCount(m_root, 0);
}
template<typename T>
vector<size_t> Tree<T>::GetLevelNodeCount(shared_ptr<Node<T>>& n, size_t level)
{
	if (n) {
		if (levelNodeCount.empty() || levelNodeCount.size() - 1 < level)
			levelNodeCount.push_back(1);
		else
			levelNodeCount[level]++;
		GetLevelNodeCount(n->Left(), level + 1);
		GetLevelNodeCount(n->Right(), level + 1);
	}
	return levelNodeCount;
}
template<typename T>
T Tree<T>::NextMin()
{
	shared_ptr<Node<T>> n = minStack.top();
	if (n) {
		minStack.pop();
		T item = n->Item();
		for (n = n->Right(); n; minStack.push(n), n = n->Left());
		return item;
	}
	return numeric_limits<T>::max();
}
template<typename T>
T Tree<T>::NextMax()
{
	shared_ptr<Node<T>> n = maxStack.top();
	if (n) {
		maxStack.pop();
		T item = n->Item();
		for (n = n->Left(); n; maxStack.push(n), n = n->Right());
		return item;
	}
	return numeric_limits<T>::min();
}
template<typename T>
bool Tree<T>::HasNextMin()
{
	return !minStack.empty();
}
template<typename T>
bool Tree<T>::HasNextMax()
{
	return !maxStack.empty();
}
template<typename T>
void Tree<T>::ToLinkedList()
{
	ToLinkedList(m_root);
}
/* https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
* 100%
*/
template<typename T>
shared_ptr<Node<T>> Tree<T>::ToLinkedList(shared_ptr<Node<T>>& n)
{
	if (n) {
		shared_ptr<Node<T>> left = ToLinkedList(n->Left());
		shared_ptr<Node<T>> right = ToLinkedList(n->Right());
		if (left && right) {
			if (left->Right()) { // Move the right subtree to the right-most leaf of the left subtree. This condition is reached when the left node is already flattened to linked list.
				/*
				*       5(n)
				*     3	    7
				*  2    6(rightMost)
				* 
				*      5(n)
				*    3     
				*  2    6(rightMost)
				*          7
				*/
				shared_ptr<Node<T>> rightMost = left;
				for (; rightMost->Right(); rightMost = rightMost->Right());
				rightMost->SetRight(right);
				right->SetNext(rightMost);
			} else { // Simple case of adding right to the left node
				/*
				*    3(n)
				*  2   6
				* 
				*    3(n)
				*  2
				*    6
				*/
				left->SetRight(right);
				right->SetNext(left);
			}
			/* Now, move everything:
			*      5(n)
			*    3     
			*  2    6(rightMost)
			*          7
			* 
			*      5(n)
			*         3
			*       2    6
			*               7
			* 
			*     5(n)
			*   3
			* 2   6
			* 
			*     5(n)
			*          3
			*        2   6
			*/
			n->SetRight(left);
			left->SetNext(n);
			n->SetLeft(nullptr);
		} else if (left && !right) {
			n->SetRight(left);
			n->SetLeft(nullptr);
		}
	}
	return n;
}
#if 0
template<typename T>
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