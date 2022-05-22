#pragma once
#include "Node.h"
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stack>
#include <limits>
#include <limits.h>
#include <memory>
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
enum class TreeType
{
	Binary,
	BinarySearch
};
enum class TraversalType
{
	PreOrder,
	PostOrder
};
template <typename T>
class Tree
{
protected:
	vector<size_t> levelNodeCount;
	shared_ptr<Node<T>> m_root;
	stack<shared_ptr<Node<T>>> minStack, maxStack;
	void Clear(shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> AddToTree(shared_ptr<Node<T>>, vector<T> &, long, long);
	shared_ptr<Node<T>> AddToTree(vector<T> &);
	shared_ptr<Node<T>> FindNode(const shared_ptr<Node<T>> &, T item);
	void PrintColumns(const shared_ptr<Node<T>> &, long, map<long, shared_ptr<vector<T>>> &);
	void AddToColumn(T, long, map<long, shared_ptr<vector<T>>> &);
	T MinDiffInBST(shared_ptr<Node<T>>, shared_ptr<Node<T>>) const;
	shared_ptr<Node<T>> Copy(const shared_ptr<Node<T>> &, map<shared_ptr<Node<T>>, shared_ptr<Node<T>>> &);
	shared_ptr<Node<T>> LeftMostChild(shared_ptr<Node<T>> &);
	bool covers(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
	void FindSum(const shared_ptr<Node<T>> &, long, long, vector<long>, vector<string> &);
	vector<string> GetRoot2LeafNumbers(const shared_ptr<Node<T>> &);
	size_t Count(const shared_ptr<Node<T>> &) const;
	T Min(const shared_ptr<Node<T>> &) const;
	T Max(const shared_ptr<Node<T>> &) const;
	bool isValidBST(const shared_ptr<Node<T>> &) const;
	vector<size_t> GetLevelNodeCount(const shared_ptr<Node<T>> &, size_t);
	shared_ptr<Node<T>> ToLinkedList(const shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> BuildTreePreOrder(vector<T> &, vector<T> &, long, long, long);
	shared_ptr<Node<T>> BuildTreePostOrder(vector<T> &, vector<T> &, long, long, long);
	shared_ptr<Node<T>> CommonAncestor(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
public:
	Tree();
	Tree(Tree<T> &);
	explicit Tree(T);
	Tree(vector<T> &, TreeType);
	Tree(TraversalType, vector<T> &preorder, vector<T> &inorder);
	Tree(shared_ptr<Node<T>> &);
	virtual ~Tree();
	void Clear();
	Tree<T> &operator=(Tree<T> &);
	bool operator==(const Tree<T> const &) const;
	void Serialize(const shared_ptr<Node<T>> &, vector<T> &);
	shared_ptr<Node<T>> Root() const;
	void InsertItem(T);
	virtual void InsertNode(shared_ptr<Node<T>> &, shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> FindNode(T);
	void GetNodes(map<size_t, vector<shared_ptr<Node<T>>>> &, long level = -1 /* Get nodes of all levels by default*/) const;
	shared_ptr<Node<T>> InOrderSuccessor(shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> CommonAncestor(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
	shared_ptr<Node<T>> CommonAncestor1(shared_ptr<Node<T>> &, shared_ptr<Node<T>> &);
	void FindSum(const shared_ptr<Node<T>> &, long, vector<string> &);
	T SumRoot2LeafNumbers();
	bool SubTree(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &);
	bool MatchTree(const shared_ptr<Node<T>> &, const shared_ptr<Node<T>> &) const;
	size_t MinDepth(const shared_ptr<Node<T>> &) const;
	size_t MaxDepth(const shared_ptr<Node<T>> &) const;
	T NextMin();
	T NextMax();
	T kthSmallest(size_t);
	T kthLargest(size_t);
	bool HasNextMin() const;
	bool HasNextMax() const;
	T Min() const;
	T Max() const;
	T MinSubTreesDifference() const;
	bool IsBalancedTree() const;
	T MinDiffInBST() const;
	size_t Count() const;
	virtual void PrintTree() const;
	void PrintTreeColumns();
	vector<size_t> GetLevelNodeCount();
	void ToLinkedList();
	bool isValidBST() const;
	T TreeArithmeticTotal(shared_ptr<Node<string>>);
};