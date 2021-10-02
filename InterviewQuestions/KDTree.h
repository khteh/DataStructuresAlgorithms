#pragma once
#include "Tree.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <memory>
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
	shared_ptr<KDNode<T>> left_, right_;
public:
	KDNode(vector<T>&, long, long, shared_ptr<KDNode<T>>, shared_ptr<KDNode<T>>);
	void PrintLocation();
	shared_ptr<KDNode<T>> Left();
	shared_ptr<KDNode<T>> Right();
	long Axis();
	long Depth();
};
template<class T>
class KDTree
{
private:
	shared_ptr<KDNode<T>> m_root;
	shared_ptr<KDNode<T>> Construct(vector<vector<T>> data, long depth = 0);
public:
	KDTree(vector<vector<T>>&, long depth = 0);
	virtual ~KDTree();
	virtual void PrintTree();
};