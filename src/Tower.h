#pragma once
#include "MyStack.h"
using namespace std;
template <typename T>
class Tower : public enable_shared_from_this<Tower<T>>
{
private:
	size_t _index;
	MyStack<T> _discs;

public:
	Tower(size_t);
	~Tower();
	size_t Index() const;
	bool isEmpty() const;
	T TopDisc() const;
	size_t DiscCount() const;
	void Clear();
	void Add(T);
	void print();
	void MoveTopTo(shared_ptr<Tower<T>> &);
	size_t MoveDiscs(T, shared_ptr<Tower<T>> &, shared_ptr<Tower<T>> &);
	// By top disc. An empty tower is greater than any non-empty one: any disc can be moved onto it
	weak_ordering operator<=>(const Tower<T> &) const;
};