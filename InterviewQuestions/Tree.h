#pragma once
#include "Node.h"
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <stack>
#include <limits.h>
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
	Node<T> *m_root;
	Node<T>* FindNode(Node<T> *, T item);
	void PrintColumns(Node<T> *node, long column, map<long, vector<T>*>& columns);
	void AddToColumn(T value, long, map<long, vector<T>*>&);
	T MinDiffInBST(Node<T> *, Node<T>*);
	Node<T> *Copy(Node<T> *, map<Node<T>*, Node<T>*>&);
	Node<T>* LeftMostChild(Node<T>*);
	bool covers(Node<T>*, Node<T>*);
	void FindSum(Node<T>*, long, long, vector<long>, vector<string>&);
	size_t Count(Node<T>*);
public:
	Tree();
	Tree(Tree<T>&);
	explicit Tree(T);
	Tree(vector<T>&);
	Tree(Node<T> *);
	virtual ~Tree();
	Tree<T> & operator=(Tree<T>&);
	bool operator==(Tree<T>&);
	void Serialize(Node<T>*, vector<T>&);
	Node<T> *Root();
	void InsertItem(T);
	virtual void InsertNode(Node<T> *, Node<T> *);
	Node<T>* AddToTree(Node<T> *, vector<T>&, int, int);
	Node<T>* FindNode(T);
	void GetNodes(map<unsigned long, vector<Node<T>*>>&, unsigned long level = -1/* Get nodes of all levels by default*/);
	Node<T>* InOrderSuccessor(Node<T>*);
	Node<T>* CommonAncestor(Node<T>*, Node<T>*);
//	Node<T>* CommonAncestor1(Node<T>*, Node<T>*, Node<T>*); XXX: Fix Me
	void FindSum(Node<T>*, long, vector<string>&);
	bool SubTree(Node<T> *, Node<T> *);
	bool MatchTree(Node<T> *, Node<T> *);
	unsigned long MinDepth(Node<T>*);
	unsigned long MaxDepth(Node<T>*);
	bool IsBalancedTree();
	T MinDiffInBST();
	size_t Count();
	void Clear(Node<T> *);
	virtual void PrintTree();
	void PrintTreeColumns();
};