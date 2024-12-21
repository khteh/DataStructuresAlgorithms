#include "stdafx.h"
#include "DisJointSet.h"
template class DisJointSet<int>;
template class DisJointSet<long>;
template <typename T>
DisJointSet<T>::DisJointSet(vector<T> const &data)
{
	MakeSet(data);
}
template <typename T>
void DisJointSet<T>::MakeSet(vector<T> const &data)
{
	// perform makeset operation by creating n disjoint sets
	for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
		_sets.emplace(*it, *it); // Key: current item; Value: parent of the current item
}
template <typename T>
T DisJointSet<T>::Find(T item)
{
	// C++ map will insert non-existing key silently
	if (!_sets.count(item))
	{
		ostringstream oss;
		oss << item << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << item << ");";
		throw runtime_error(oss.str());
	}
	// Find the root of the set in which element belongs
	if (_sets[item] == item)
		return item;
	else
	{
		/*
		 * Performing a Find operation presents an important opportunity for improving the forest. The time in a Find operation is spent chasing parent pointers, so a flatter tree leads to faster Find operations.
		 * When a Find is executed, there is no faster way to reach the root than by following each parent pointer in succession. However, the parent pointers visited during this search can be updated to point closer to the root.
		 * Because every element visited on the way to a root is part of the same set, this does not change the sets stored in the forest. But it makes future Find operations faster, not only for the nodes between the query node and the root, but also for their descendants.
		 * This updating is an important part of the disjoint-set forest's amortized performance guarantee.
		 */
		T root = Find(_sets[item]);
		_sets[item] = root;
		return root;
	}
}
template <typename T>
size_t DisJointSet<T>::Rank(T item)
{
	return _rank[Find(item)];
}
template <typename T>
T DisJointSet<T>::Union(T x, T y)
{
	/* Unites the set that includes x
	 * and the set that includes y
	 */
	T rootX = Find(x);
	T rootY = Find(y);
	if (rootX == numeric_limits<T>::min())
	{
		ostringstream oss;
		oss << x << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << x << ");";
		throw runtime_error(oss.str());
	}
	if (rootY == numeric_limits<T>::min())
	{
		ostringstream oss;
		oss << y << " is not a disjoint tree! It can be made a disjoint tree by calling DisJointSet.MakeSet(" << y << ");";
		throw runtime_error(oss.str());
	}
	T root = T();
	if (rootX != rootY)
	{
		// Put smaller ranked item under bigger ranked item if ranks are different. Copying of smaller ranked item saves time!
		if (_rank[rootX] < _rank[rootY])
		{
			_sets[rootX] = rootY;
			root = rootY;
		}
		else if (_rank[rootY] < _rank[rootX])
		{
			_sets[rootY] = rootX;
			root = rootX;
		}
		else
		{
			// If ranks are same, increment the rank
			_sets[rootX] = rootY;
			root = rootY;
			_rank[rootY]++;
		}
	}
	else
		root = numeric_limits<T>::min(); // Already joined
	return root;
}
template <typename T>
void DisJointSet<T>::Print(vector<T> const &data, size_t linesize)
{
	size_t i = 1;
	for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++, i++)
	{
		cout << Find(*it);
		if (linesize > 0 && !(i % linesize))
			cout << endl;
		else
			cout << ", ";
	}
	cout << endl;
}
template <typename T>
void DisJointSet<T>::GetSets(vector<T> const &data, map<T, vector<T>> &sets)
{
	for (typename vector<T>::const_iterator it = data.begin(); it != data.end(); it++)
		sets[Find(*it)].push_back(*it);
}