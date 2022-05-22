#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "MyStack.h"
using namespace std;

template <typename T>
class Tower
{
private:
	size_t m_index;
	MyStack<T> m_disks;
	void MoveTopTo(Tower *);

public:
	Tower(size_t);
	~Tower();
	size_t Index();
	bool isEmpty();
	T TopDisk();
	void Clear();
	void Add(T);
	void print();
	size_t MoveDisks(T, Tower *, Tower *);
};