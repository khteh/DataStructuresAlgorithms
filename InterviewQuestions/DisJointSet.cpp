#include "stdafx.h"
#include "DisJointSet.h"
template class DisJointSet<long>;
template<class T>
DisJointSet<T>::DisJointSet(vector<T>& data)
{
	MakeSet(data);
}
template<class T>
void DisJointSet<T>::MakeSet(vector<T>& data)
{
	//perform makeset operation	by creating n disjoint sets
	for (vector<T>::iterator it = data.begin(); it != data.end(); it++)
		_parent.emplace(*it, *it);
}
template<class T>
T DisJointSet<T>::Find(T item)
{
	// C++ map will insert non-existing key silently
	if (_parent.find(item) == _parent.end()) {
		ostringstream oss;
		oss << item << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << item << ");";
		throw runtime_error(oss.str());
	}
	// Find the root of the set in which element l belongs
	if (_parent[item] == item)
		return item;
	else {
		T root = Find(_parent[item]);
		// We cache the result by moving i’s node 
		// directly under the representative of this
		// set
		_parent[item] = root;
		return root;
	}
}
template<class T>
size_t DisJointSet<T>::Rank(T item)
{
	return _rank[Find(item)];
}
template<class T>
T DisJointSet<T>::Union(T x, T y)
{
	// Unites the set that includes x
	// and the set that includes y
	T rootX = Find(x);
	T rootY = Find(y);
	if (rootX == T()) {
		ostringstream oss;
		oss << x << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << x << ");";
		throw runtime_error(oss.str());
	}
	if (rootY == T()) {
		ostringstream oss;
		oss << y << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << y << ");";
		throw runtime_error(oss.str());
	}
	T root;
	if (rootX != rootY) {
		// Put smaller ranked item under bigger ranked item if ranks are different. Copying of smaller ranked item saves time!
		if (_rank[rootX] < _rank[rootY]) {
			_parent[rootX] = rootY;
			root = rootY;
		}
		else if (_rank[rootY] < _rank[rootX]) {
			_parent[rootY] = rootX;
			root = rootX;
		}
		else {
			// If ranks are same, increment the rank
			_parent[rootX] = rootY;
			root = rootY;
			_rank[rootY]++;
		}
	}
	else
		root = T(); // Already joined
	return root;
}
template<class T>
void DisJointSet<T>::Print(vector<T> const& data, size_t linesize)
{
	size_t i = 1;
	for (vector<T>::const_iterator it = data.begin(); it != data.end(); it++, i++) {
		cout << Find(*it);
		if (!(i % linesize))
			cout << endl;
		else
			cout << ", ";
	}
	cout << endl;
}