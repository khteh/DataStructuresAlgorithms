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

public:
	Tower(size_t);
	~Tower();
	size_t Index() const;
	bool isEmpty() const;
	T TopDisk() const;
	size_t DiskCount() const;
	void Clear();
	void Add(T);
	void print();
	void MoveTopTo(shared_ptr<Tower<T>> &);
	size_t MoveDisks(T, shared_ptr<Tower<T>> &, shared_ptr<Tower<T>> &);
	bool operator<(Tower<T> &) const;
	bool operator>(Tower<T> &) const;
};