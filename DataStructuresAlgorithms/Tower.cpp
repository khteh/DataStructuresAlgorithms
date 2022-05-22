#include "stdafx.h"
#include "Tower.h"
template class Tower<size_t>;

template <typename T>
Tower<T>::Tower(size_t index)
	: m_index(index)
{
}

template <typename T>
Tower<T>::~Tower()
{
}

template <typename T>
size_t Tower<T>::Index()
{
	return m_index;
}

template <typename T>
bool Tower<T>::isEmpty()
{
	return m_disks.isEmpty();
}
template <typename T>
void Tower<T>::Clear()
{
	m_disks.clear();
}
template <typename T>
T Tower<T>::TopDisk()
{
	return m_disks.peek();
}
template <typename T>
void Tower<T>::Add(T disk)
{
	if (!m_disks.isEmpty() && m_disks.peek() <= disk)
	{
		ostringstream oss;
		oss << "Cannot stack bigger disk " << disk << " on smaller disk";
		throw runtime_error(oss.str());
	}
	else
		m_disks.push(disk);
}

template <typename T>
void Tower<T>::MoveTopTo(Tower *t)
{
	T top = m_disks.pop();
	t->Add(top);
}

template <typename T>
void Tower<T>::print()
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
template <typename T>
size_t Tower<T>::MoveDisks(T n, Tower *dest, Tower *buffer)
{
	size_t moves = 0;
	if (n > 0)
	{											 // 1 (smallest, topmost)
		moves += MoveDisks(n - 1, buffer, dest); // 1. move n−1 discs from A to B. This leaves disc n alone on peg A
		MoveTopTo(dest);						 // 2. move disc n from A to C
		moves++;
		moves += buffer->MoveDisks(n - 1, dest, this); // 3. move n−1 discs from B to C so they sit on disc n
	}
	return moves;
}