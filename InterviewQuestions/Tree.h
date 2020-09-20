#pragma once
#include "Node.h"
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <stack>
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
enum class TreeType { Binary, BinarySearch };
enum class TraversalType {PreOrder, PostOrder};
template<typename T>
class Tree
{
protected:
	vector<size_t> levelNodeCount;
	shared_ptr<Node<T>> m_root;
	stack<shared_ptr<Node<T>>> minStack, maxStack;
	void Clear(shared_ptr<Node<T>>&);
	shared_ptr<Node<T>> AddToTree(shared_ptr<Node<T>>, vector<T>&, long, long);
	shared_ptr<Node<T>> AddToTree(vector<T>&);
	shared_ptr<Node<T>> FindNode(shared_ptr<Node<T>>&, T item);
	void PrintColumns(shared_ptr<Node<T>>&, long, map<long, vector<T>*>&);
	void AddToColumn(T, long, map<long, vector<T>*>&);
	T MinDiffInBST(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	shared_ptr<Node<T>> Copy(shared_ptr<Node<T>>&, map<shared_ptr<Node<T>>, shared_ptr<Node<T>>>&);
	shared_ptr<Node<T>> LeftMostChild(shared_ptr<Node<T>>&);
	bool covers(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	void FindSum(shared_ptr<Node<T>>&, long, long, vector<long>, vector<string>&);
	vector<string> GetRoot2LeafNumbers(shared_ptr<Node<T>>&);
	size_t Count(shared_ptr<Node<T>>&);
	T Min(shared_ptr<Node<T>>&);
	T Max(shared_ptr<Node<T>>&);
	bool isValidBST(shared_ptr<Node<T>>&);
	vector<size_t> GetLevelNodeCount(shared_ptr<Node<T>>&, size_t);
	shared_ptr<Node<T>> ToLinkedList(shared_ptr<Node<T>>&);
	shared_ptr<Node<T>> BuildTreePreOrder(vector<T>&, vector<T>&, long, long, long);
	shared_ptr<Node<T>> BuildTreePostOrder(vector<T>&, vector<T>&, long, long, long);
public:
	Tree();
	Tree(Tree<T>&);
	explicit Tree(T);
	Tree(vector<T>&, TreeType);
	Tree(TraversalType, vector<T>& preorder, vector<T>& inorder);
	Tree(shared_ptr<Node<T>>&);
	virtual ~Tree();
	void Clear();
	Tree<T> & operator=(Tree<T>&);
	bool operator==(Tree<T>&);
	void Serialize(shared_ptr<Node<T>>&, vector<T>&);
	shared_ptr<Node<T>> Root();
	void InsertItem(T);
	virtual void InsertNode(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	shared_ptr<Node<T>> FindNode(T);
	void GetNodes(map<size_t, vector<shared_ptr<Node<T>>>>&, long level = -1/* Get nodes of all levels by default*/);
	shared_ptr<Node<T>> InOrderSuccessor(shared_ptr<Node<T>>&);
	shared_ptr<Node<T>> CommonAncestor(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	void FindSum(shared_ptr<Node<T>>&, long, vector<string>&);
	T SumRoot2LeafNumbers();
	bool SubTree(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	bool MatchTree(shared_ptr<Node<T>>&, shared_ptr<Node<T>>&);
	size_t MinDepth(shared_ptr<Node<T>>&);
	size_t MaxDepth(shared_ptr<Node<T>>&);
	T NextMin();
	T NextMax();
	bool HasNextMin();
	bool HasNextMax();
	T Min();
	T Max();
	T MinSubTreesDifference();
	bool IsBalancedTree();
	T MinDiffInBST();
	size_t Count();
	virtual void PrintTree();
	void PrintTreeColumns();
	vector<size_t> GetLevelNodeCount();
	void ToLinkedList();
	bool isValidBST();
};