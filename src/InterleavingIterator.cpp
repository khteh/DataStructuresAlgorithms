#include "stdafx.h"
#include "InterleavingIterator.h"
using namespace std;

template <typename T>
InterleavingIterator<T>::InterleavingIterator(vector<vector<T>> &containers)
	: containers_(containers),
	  current_(0),
	  size_(0)
{
	for (typename vector<vector<T>>::const_iterator it = containers_.begin(); it != containers_.end(); it++)
		size += it->size();
}

template <typename T>
InterleavingIterator<T>::~InterleavingIterator()
{
}

template <typename T>
bool InterleavingIterator<T>::HasNext()
{
	return current_ < size_;
}

template <typename T>
T InterleavingIterator<T>::Next()
{
	size_t x, y;
	for (; current_ < size_; current_++)
	{
		x = current_ / containers_.size();
		y = current_ % containers_.size();
		if (x < containers_[y].size())
			break;
	}
	return containers_[y][x];
}