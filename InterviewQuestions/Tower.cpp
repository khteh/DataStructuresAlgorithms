#include "StdAfx.h"
#include "Tower.h"

Tower::Tower(int index)
	:m_index(index)
{
}

Tower::~Tower()
{
}

int Tower::Index()
{ 
	return m_index; 
}

void Tower::Add(int disk) 
{
	if (!m_disks.isEmpty() && m_disks.peek() <= disk)
	{
		stringstream ss;
		ss << "Cannot stack bigger disk " << disk << " on smaller disk";
		throw ss.str();
	} else
		m_disks.push(disk);
}

void Tower::MoveTopTo(Tower *t)
{
	int top = m_disks.pop();
	t->Add(top);
}

void Tower::print()
{
	cout << "Tower " << m_index << " content: " << endl;
	m_disks.PrintStack();
	cout << endl;
}

// http://en.wikipedia.org/wiki/Tower_of_Hanoi
// label the pegs A, B, C — these labels may move at different steps
// let n be the total number of discs
// number the discs from 1 (smallest, topmost) to n (largest, bottommost)
// The above is a recursive algorithm, to carry out steps 1 and 3, apply the same algorithm again for n−1. 
// The entire procedure is a finite number of steps, since at some point the algorithm will be required for n = 1. 
// This step, moving a single disc from peg A to peg B, is trivial.
void Tower::MoveDisks(int n, Tower *dest, Tower *buffer)
{
	if (n > 0) { // 1 (smallest, topmost)
		MoveDisks(n - 1, buffer, dest); // 1. move n−1 discs from A to B. This leaves disc n alone on peg A
		MoveTopTo(dest); // 2. move disc n from A to C
		buffer->MoveDisks(n - 1, dest, this); // 3. move n−1 discs from B to C so they sit on disc n
	}
}