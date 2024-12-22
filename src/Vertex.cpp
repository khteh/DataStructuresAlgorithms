#include "stdafx.h"
#include "Vertex.h"
template class Vertex<int, int>;
template class Vertex<long, long>;
template class Vertex<size_t, size_t>;
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex()
	: _tag(TTag()), _item(TItem()), _cost(numeric_limits<long>::max()), _sum(TItem())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag)
	: _tag(tag), _item(TItem()), _cost(numeric_limits<long>::max()), _sum(TItem())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag, TItem item)
	: _tag(tag), _item(item), _cost(numeric_limits<long>::max()), _sum(TItem())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag, TItem item, map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours)
	: _tag(tag), _item(item), _cost(numeric_limits<long>::max()), _neighbours(neighbours), _sum(TItem())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::~Vertex()
{
	_neighbours.clear();
}
template <typename TTag, typename TItem>
TTag Vertex<TTag, TItem>::GetTag() const
{
	return _tag;
}
template <typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::GetItem() const
{
	return _item;
}
template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::AddNeighbour(shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (!_neighbours.count(to))
		_neighbours.emplace(to, cost);
	else if (_neighbours[to] > cost)
		_neighbours[to] = cost;
}
template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::RemoveNeighbour(shared_ptr<Vertex<TTag, TItem>> to)
{
	if (to && _neighbours.count(to))
	{
		// to->RemoveNeighbour(this->shared_from_this()); // This will result in circular call tree
		_neighbours.erase(to);
	}
}
template <typename TTag, typename TItem>
vector<shared_ptr<Vertex<TTag, TItem>>> Vertex<TTag, TItem>::GetNeighbours()
{
	vector<shared_ptr<Vertex<TTag, TItem>>> vertices;
	ranges::transform(
		_neighbours,
		back_inserter(vertices),
		[](const typename map<shared_ptr<Vertex<TTag, TItem>>, long>::value_type &pair)
		{ return pair.first; });
	return vertices;
}
template <typename TTag, typename TItem>
map<shared_ptr<Vertex<TTag, TItem>>, long> Vertex<TTag, TItem>::GetNeighboursWithCost()
{
	return _neighbours;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbours() const
{
	return !_neighbours.empty();
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(TTag tag) const
{
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = _neighbours.begin(); it != _neighbours.end(); it++)
		if (it->first->GetTag() == tag)
			return true;
	return false;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(TTag tag, TItem item) const
{
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = _neighbours.begin(); it != _neighbours.end(); it++)
		if (it->first->GetTag() == tag && it->first->GetItem() == item)
			return true;
	return false;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(shared_ptr<Vertex<TTag, TItem>> v) const
{
	return _neighbours.count(v);
}
template <typename TTag, typename TItem>
size_t Vertex<TTag, TItem>::NeighbourCount() const
{
	return _neighbours.size();
}
template <typename TTag, typename TItem>
size_t Vertex<TTag, TItem>::EvenForestDescendentsCount(TTag parent, set<string> &cuts) const
{
	ostringstream oss;
	size_t count = 1; // Include itself
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = _neighbours.begin(); it != _neighbours.end(); it++)
		if (it->first->GetTag() != parent)
		{
			size_t descendents = it->first->EvenForestDescendentsCount(GetTag(), cuts);
			if (!(descendents % 2))
			{
				oss.str("");
				oss << GetTag() << "-" << it->first->GetTag();
				cuts.emplace(oss.str());
			}
			else
				count += descendents;
		}
	return count;
}
template <typename TTag, typename TItem>
long Vertex<TTag, TItem>::GetCost(shared_ptr<Vertex<TTag, TItem>> v)
{
	if (v->GetTag() == GetTag() && v->GetItem() == GetItem())
		return 0;
	return _neighbours.count(v) ? _neighbours[v] : -1;
}
template <typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::GetSubGraphSum(TTag parent)
{
	if (_sum == TItem())
	{
		_sum = _item;
		if (_neighbours.empty())
			return _sum;
		for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = _neighbours.begin(); it != _neighbours.end(); it++)
			if (it->first->GetTag() != parent) // Undirected graph
				_sum += it->first->GetSubGraphSum(GetTag());
	}
	return _sum;
}
/* https://www.hackerrank.com/challenges/cut-the-tree/problem
			10
		11		5
	Diff: 15 - 11 = 4

			10
		 5		6
	  20
	Diff: 21 - 20 = 1

			10
		 5
	  20
	Diff: 20 - 15 = 5

		100(0)
			200(1)
		100(2)    100(4)
				500(3) 600(5)
* 100%
*/
template <typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::MinSubGraphsDifference(TTag parent, TItem sum) const
{
	TItem minDiff = numeric_limits<TItem>::max();
	if (_neighbours.empty())
		return sum;
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = _neighbours.begin(); it != _neighbours.end(); it++)
		if (it->first->GetTag() != parent) // Undirected graph
		{
			TItem sum1 = it->first->GetSubGraphSum(GetTag());
			TItem sum2 = sum - sum1;
			TItem diff1 = it->first->MinSubGraphsDifference(GetTag(), sum);
			TItem diff2 = abs((long)sum1 - (long)sum2);
			minDiff = min(minDiff, min(diff1, diff2));
		}
	return minDiff;
}
template <typename TTag, typename TItem>
long Vertex<TTag, TItem>::GetTotalCost() const
{
	return _cost;
}

template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::SetTotalCost(long cost)
{
	_cost = cost;
}

template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::ResetTotalCost()
{
	_cost = numeric_limits<long>::max();
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem> &Vertex<TTag, TItem>::operator=(Vertex<TTag, TItem> &rhs)
{
	_tag = rhs._tag;
	_item = rhs._item;
	return *this;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator<(const Vertex<TTag, TItem> &other) const
{
	return _item < other._item;
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator==(Vertex<TTag, TItem> &rhs)
{
	return _item == rhs._item && _tag == rhs._tag;
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator!=(Vertex<TTag, TItem> &rhs)
{
	return !(*this == rhs);
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator<(Vertex<TTag, TItem> &rhs)
{
	return _item < rhs._item;
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator>(Vertex<TTag, TItem> &rhs)
{
	return _item > rhs._item;
}