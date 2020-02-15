#pragma once
#include "Tree.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
// https://en.wikipedia.org/wiki/K-d_tree
template<class T>
class KDTreeCompare
{
private:
	size_t dimension_;
public:
	KDTreeCompare(size_t dimension);
	bool operator()(const std::vector<T>& lhs, const std::vector<T>& rhs) const;
};
template<class T>
class KDNode
{
private:
	long axis_, depth_;
	vector<T> location_;
	KDNode<T> *left_, *right_;
public:
	KDNode(vector<T>&, long, long, KDNode<T>*, KDNode<T>*);
	void PrintLocation();
	KDNode<T> *Left();
	KDNode<T> *Right();
	long Axis();
	long Depth();
};
template<class T>
class KDTree
{
private:
	KDNode<T> *m_root;
	KDNode<T>* Construct(vector<vector<T>> data, long depth = 0);
public:
	KDTree(vector<vector<T>>&, long depth = 0);
	virtual ~KDTree();
	virtual void PrintTree();
};