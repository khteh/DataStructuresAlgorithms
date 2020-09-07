#include "stdafx.h"
#include "KDTree.h"
template class KDTreeCompare<long>;
template class KDNode<long>;
template class KDTree<long>;
using namespace std;
// https://en.wikipedia.org/wiki/K-d_tree
template<class T>
KDTreeCompare<T>::KDTreeCompare(size_t dimension)
	:dimension_(dimension)
{
}
template<class T>
bool KDTreeCompare<T>::operator()(const vector<T>& lhs, const vector<T>& rhs) const
{
	return lhs[dimension_] < rhs[dimension_];
}
template<class T>
KDNode<T>::KDNode(vector<T>& location, long axis, long depth, KDNode<T>*left, KDNode<T>*right)
	:location_(location)
	,axis_(axis)
	,depth_(depth)
	,left_(left)
	,right_(right)
{
}
template<class T>
long KDNode<T>::Axis()
{
	return axis_;
}
template<class T>
long KDNode<T>::Depth()
{
	return depth_;
}
template<class T>
void KDNode<T>::PrintLocation()
{
	cout << "(";
	copy(location_.begin(), location_.end(), ostream_iterator<T>(cout, ", "));
	cout << ")";
}
template<class T>
KDNode<T> *KDNode<T>::Left()
{
	return left_;
}
template<class T>
KDNode<T> *KDNode<T>::Right()
{
	return right_;
}

template<class T>
KDTree<T>::KDTree(vector<vector<T>>& data, long depth)
{
	m_root = Construct(data, depth);
}

template<class T>
KDTree<T>::~KDTree()
{
}

template<class T>
KDNode<T>* KDTree<T>::Construct(vector<vector<T>> data, long depth)
{
	if (!data.size())
		return nullptr;
	// Select axis based on depth so that axis cycles through all valid values
	// Assume all points have the same dimension
	long axis = depth % data[0].size();
	sort(data.begin(), data.end(), [axis](const std::vector<T>& a, const std::vector<T>& b) { return a[axis] < b[axis]; });
	long median = data.size() / 2;
	vector<vector<T>> left, right;
	if (median)
		left.assign(data.begin(), data.begin() + median);
	if ((data.size() - (median + 1)) > 0)
		right.assign(data.begin() + median + 1, data.end());
	return new KDNode<T>(data[median], axis, depth, Construct(left, depth + 1), Construct(right, depth + 1));
}
template<class T>
void KDTree<T>::PrintTree()
{
	// Use Pre-Order traversal to print node values
	if (!m_root) {
		cout << "Empty tree!" << endl;
		return;
	}
	unsigned long level = 0;
	map<long, vector<KDNode<T>*>> levels;
	levels.emplace(level, vector<KDNode<T>*>{m_root});
	for (; !levels[level].empty(); level++) {
		vector<KDNode<T>*> nodes;
		for (vector<KDNode<T>*>::const_iterator it = levels[level].begin(); it != levels[level].end(); it++) {
			if (*it) {
				if ((*it)->Left())
					nodes.push_back((*it)->Left());
				if ((*it)->Right())
					nodes.push_back((*it)->Right());
			}
		}
		if (!nodes.empty())
			levels.emplace(level + 1, nodes);
	}
	bool printOnce = true;
	for (map<long, vector<KDNode<T>*>>::const_iterator it = levels.begin(); it != levels.end(); it++) {
		printOnce = true;
		for (vector<KDNode<T>*>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++) {
			if (printOnce) {
				cout << "Axis " << (*it1)->Axis() << ": ";
				for (size_t i = 0; i < level; i++)
					cout << "\t";
				printOnce = false;
				level--;
			}
			(*it1)->PrintLocation();
			cout << "\t";
		}
		cout << endl;
	}
}