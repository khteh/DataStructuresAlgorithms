#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "MyStack.h"
using namespace std;

class Tower
{
private:
	int m_index;
	MyStack<int> m_disks;
	void MoveTopTo(Tower *);
public:
	Tower(int index);
	~Tower();
	int Index();
	void Add(int disk);
	void print();
	void MoveDisks(int, Tower*, Tower*);
};