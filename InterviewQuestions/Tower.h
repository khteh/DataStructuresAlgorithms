#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "MyStack.h"
using namespace std;

class Tower
{
private:
	size_t m_index;
	MyStack<size_t> m_disks;
	void MoveTopTo(Tower *);

public:
	Tower(size_t);
	~Tower();
	int Index();
	void Add(size_t);
	void print();
	void MoveDisks(size_t, Tower *, Tower *);
};