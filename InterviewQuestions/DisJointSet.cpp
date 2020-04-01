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
size_t DisJointSet<T>::Size(T item)
{
	return _parent[item] == item ? 1 : 1 + Size(item);
}
template<class T>
size_t DisJointSet<T>::Rank(T item)
{
	return _rank[Find(item)];
}
template<class T>
void DisJointSet<T>::Union(T x, T y)
{
	// Unites the set that includes x
	// and the set that includes y
	T i = Find(x);
	T j = Find(y);
	if (i == T()) {
		ostringstream oss;
		oss << x << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << x << ");";
		throw runtime_error(oss.str());
	}
	if (j == T()) {
		ostringstream oss;
		oss << y << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << y << ");";
		throw runtime_error(oss.str());
	}
	if (i != j) {
		// Put smaller ranked item under bigger ranked item if ranks are different 
		if (_rank[i] < _rank[j])
			_parent[i] = j;
		else if (_rank[i] > _rank[j])
			_parent[j] = i;
		// If ranks are same, increment the rank
		else {
			_parent[i] = j;
			_rank[j]++;
		}
	}
}
template<class T>
void DisJointSet<T>::Print(vector<T> const& data)
{
	for (vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
		cout << Find(*it) << ", ";
	cout << endl;
}