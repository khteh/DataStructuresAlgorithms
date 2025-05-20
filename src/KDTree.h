#pragma once
#include "Tree.h"
// https://en.wikipedia.org/wiki/K-d_tree
template <typename T>
class KDTreeCompare
{
private:
	size_t dimension_;

public:
	KDTreeCompare(size_t dimension);
	bool operator()(const std::vector<T> &lhs, const std::vector<T> &rhs) const;
};
template <typename T>
class KDNode
{
private:
	long axis_, depth_;
	vector<T> location_;
	shared_ptr<KDNode<T>> left_, right_;

public:
	KDNode(vector<T> &, long, long, shared_ptr<KDNode<T>>, shared_ptr<KDNode<T>>);
	void PrintLocation();
	shared_ptr<KDNode<T>> Left();
	shared_ptr<KDNode<T>> Right();
	long Axis();
	long Depth();
};
template <typename T>
class KDTree
{
private:
	shared_ptr<KDNode<T>> _root;
	shared_ptr<KDNode<T>> Construct(vector<vector<T>> data, long depth = 0);

public:
	KDTree(vector<vector<T>> &, long depth = 0);
	virtual ~KDTree();
	virtual void PrintTree();
};