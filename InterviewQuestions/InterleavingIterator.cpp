#include "stdafx.h"
#include "InterleavingIterator.h"
using namespace std;

template<class T>
InterleavingIterator<T>::InterleavingIterator(vector<vector<T>>& containers)
:	containers_(containers),
	current_(0),
	size(0)
{
	for (vector<vector<T>>::const_iterator it = containers_.begin(); it != containers_.end(); it++)
		size += it->size();
}

template<class T>
InterleavingIterator<T>::~InterleavingIterator()
{
}

template<>
bool InterleavingIterator<T>::HasNext()
{
	current_ < size_;
}

template<class T>
T InterleavingIterator<T>::Next()
{
	size_t x, y;
	for (; current_ < size_; current_++) {
		x = current_ / containers_.size();
		y = current_ % containers_.size();
		if (x < containers_[y].size())
			break;
	}
	return containers_[y][x];
}