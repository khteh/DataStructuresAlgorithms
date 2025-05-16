#include "pch.h"
#include "Tower.h"
template class Tower<size_t>;
template class Tower<long>;

template <typename T>
Tower<T>::Tower(size_t index)
	: _index(index)
{
}

template <typename T>
Tower<T>::~Tower()
{
}

template <typename T>
size_t Tower<T>::Index() const
{
	return _index;
}
template <typename T>
size_t Tower<T>::DiscCount() const
{
	return _discs.size();
}
template <typename T>
bool Tower<T>::isEmpty() const
{
	return _discs.isEmpty();
}
template <typename T>
void Tower<T>::Clear()
{
	_discs.clear();
}
template <typename T>
T Tower<T>::TopDisc() const
{
	return _discs.peek();
}
template <typename T>
void Tower<T>::Add(T disc)
{
	if (!_discs.isEmpty() && _discs.peek() <= disc)
	{
		ostringstream oss;
		oss << "Cannot stack bigger disc " << disc << " on smaller disc";
		throw invalid_argument(oss.str());
	}
	else
		_discs.push(disc);
}

template <typename T>
void Tower<T>::MoveTopTo(shared_ptr<Tower<T>> &t)
{
	t->Add(_discs.pop());
}

template <typename T>
bool Tower<T>::operator<(Tower<T> &rhs) const
{
	return !isEmpty() && TopDisc() < rhs.TopDisc();
}
template <typename T>
bool Tower<T>::operator>(Tower<T> &rhs) const
{
	return isEmpty() || TopDisc() > rhs.TopDisc();
}

template <typename T>
void Tower<T>::print()
{
	cout << "Tower " << _index << " content: ";
	_discs.PrintStack();
}

// http://en.wikipedia.org/wiki/Tower_of_Hanoi
// label the pegs A, B, C — these labels may move at different steps
// let n be the total number of discs
// number the discs from 1 (smallest, topmost) to n (largest, bottommost)
// The above is a recursive algorithm, to carry out steps 1 and 3, apply the same algorithm again for n−1.
// The entire procedure is a finite number of steps, since at some point the algorithm will be required for n = 1.
// This step, moving a single disc from peg A to peg B, is trivial.
template <typename T>
size_t Tower<T>::MoveDiscs(T n, shared_ptr<Tower<T>> &dest, shared_ptr<Tower<T>> &buffer)
{
	size_t moves = 0;
	if (n > 0 && !isEmpty())
	{											 // 1 (smallest, topmost)
		moves += MoveDiscs(n - 1, buffer, dest); // 1. move n−1 discs from A to B. This leaves disc n alone on peg A
		MoveTopTo(dest);						 // 2. move disc n from A to C
		moves++;
		shared_ptr<Tower<T>> bufferTower = this->shared_from_this(); // A non-const reference parameter, such as an int&, can only refer to an "lvalue," which is a named variable.
		moves += buffer->MoveDiscs(n - 1, dest, bufferTower);		 // 3. move n−1 discs from B to C so they sit on disc n
	}
	return moves;
}