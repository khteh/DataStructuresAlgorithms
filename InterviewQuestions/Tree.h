#pragma once
#include "Node.h"
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
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
template<class T>
class Tree
{
protected:
	shared_ptr<Node<T>> m_root;
	shared_ptr<Node<T>> FindNode(shared_ptr<Node<T>>, T item);
	void PrintColumns(shared_ptr<Node<T>>node, long column, map<long, vector<T>*>& columns);
	void AddToColumn(T value, long, map<long, vector<T>*>&);
	T MinDiffInBST(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	shared_ptr<Node<T>> Copy(shared_ptr<Node<T>>, map<shared_ptr<Node<T>>, shared_ptr<Node<T>>>&);
	shared_ptr<Node<T>> LeftMostChild(shared_ptr<Node<T>>);
	bool covers(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	void FindSum(shared_ptr<Node<T>>, long, long, vector<long>, vector<string>&);
	size_t Count(shared_ptr<Node<T>>);
public:
	Tree();
	Tree(Tree<T>&);
	explicit Tree(T);
	Tree(vector<T>&);
	Tree(shared_ptr<Node<T>>);
	virtual ~Tree();
	Tree<T> & operator=(Tree<T>&);
	bool operator==(Tree<T>&);
	void Serialize(shared_ptr<Node<T>>, vector<T>&);
	shared_ptr<Node<T>> Root();
	void InsertItem(T);
	virtual void InsertNode(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	shared_ptr<Node<T>> AddToTree(shared_ptr<Node<T>>, vector<T>&, int, int);
	shared_ptr<Node<T>> FindNode(T);
	void GetNodes(map<size_t, vector<shared_ptr<Node<T>>>>&, long level = -1/* Get nodes of all levels by default*/);
	shared_ptr<Node<T>> InOrderSuccessor(shared_ptr<Node<T>>);
	shared_ptr<Node<T>> CommonAncestor(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
//	shared_ptr<Node<T>> CommonAncestor1(shared_ptr<Node<T>>, shared_ptr<Node<T>>, shared_ptr<Node<T>>); XXX: Fix Me
	void FindSum(shared_ptr<Node<T>>, long, vector<string>&);
	bool SubTree(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	bool MatchTree(shared_ptr<Node<T>>, shared_ptr<Node<T>>);
	unsigned long MinDepth(shared_ptr<Node<T>>);
	unsigned long MaxDepth(shared_ptr<Node<T>>);
	bool IsBalancedTree();
	T MinDiffInBST();
	size_t Count();
	void Clear(shared_ptr<Node<T>>);
	virtual void PrintTree();
	void PrintTreeColumns();
};