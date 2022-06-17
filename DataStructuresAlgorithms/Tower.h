#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include "MyStack.h"
using namespace std;

template <typename T>
class Tower : public enable_shared_from_this<Tower<T>>
{
private:
	size_t m_index;
	MyStack<T> m_disks;
	void MoveTopTo(shared_ptr<Tower<T>> &);

public:
	Tower(size_t);
	~Tower();
	size_t Index();
	bool isEmpty() const;
	T TopDisk() const;
	void Clear();
	void Add(T);
	void print();
	size_t MoveDisks(T, shared_ptr<Tower<T>> &, shared_ptr<Tower<T>> &);
	bool operator<(Tower<T> &) const;
	bool operator>(Tower<T> &) const;
};