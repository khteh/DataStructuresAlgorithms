#pragma once
#include "IIterator.h"
template <typename T>
class InterleavingIterator : public IIterator<T>
{
private:
	std::vector<std::vector<T>> &containers_;
	size_t current_;
	size_t size_;

public:
	InterleavingIterator(std::vector<std::vector<T>> &);
	virtual ~InterleavingIterator();
	bool HasNext();
	T Next();
};