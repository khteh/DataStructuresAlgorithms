#include "stdafx.h"
#include "Vertex.h"
template class Vertex<int, int>;
template class Vertex<long, long>;
template class Vertex<size_t, size_t>;
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex()
	: tag_(TTag()), item_(TItem()), cost_(numeric_limits<long>::max())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag)
	: tag_(tag), item_(TItem()), cost_(numeric_limits<long>::max())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag, TItem item)
	: tag_(tag), item_(item), cost_(numeric_limits<long>::max())
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag, TItem item, map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours)
	: tag_(tag), item_(item), cost_(numeric_limits<long>::max()), neighbours_(neighbours)
{
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem>::~Vertex()
{
	neighbours_.clear();
}
template <typename TTag, typename TItem>
TTag Vertex<TTag, TItem>::GetTag() const
{
	return tag_;
}
template <typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::GetItem() const
{
	return item_;
}
template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::AddNeighbour(shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (neighbours_.find(to) == neighbours_.end())
		neighbours_.emplace(to, cost);
	else if (neighbours_[to] > cost)
		neighbours_[to] = cost;
}
template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::RemoveNeighbour(shared_ptr<Vertex<TTag, TItem>> to)
{
	neighbours_.erase(to);
}
template <typename TTag, typename TItem>
vector<shared_ptr<Vertex<TTag, TItem>>> Vertex<TTag, TItem>::GetNeighbours()
{
	vector<shared_ptr<Vertex<TTag, TItem>>> vertices;
	ranges::transform(
		neighbours_,
		back_inserter(vertices),
		[](const typename map<shared_ptr<Vertex<TTag, TItem>>, long>::value_type &pair)
		{ return pair.first; });
	return vertices;
}
template <typename TTag, typename TItem>
map<shared_ptr<Vertex<TTag, TItem>>, long> Vertex<TTag, TItem>::GetNeighboursWithCost()
{
	return neighbours_;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbours() const
{
	return !neighbours_.empty();
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(TTag tag) const
{
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
		if (it->first->GetTag() == tag)
			return true;
	return false;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(TTag tag, TItem item) const
{
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
		if (it->first->GetTag() == tag && it->first->GetItem() == item)
			return true;
	return false;
}
template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(shared_ptr<Vertex<TTag, TItem>> v) const
{
	return neighbours_.find(v) != neighbours_.end();
}
template <typename TTag, typename TItem>
size_t Vertex<TTag, TItem>::NeighbourCount() const
{
	return neighbours_.size();
}
template <typename TTag, typename TItem>
size_t Vertex<TTag, TItem>::EvenForestDescendentsCount(TTag parent, set<string> &cuts) const
{
	ostringstream oss;
	size_t count = 1; // Include itself
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
	{
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
	}
	return count;
}
template <typename TTag, typename TItem>
long Vertex<TTag, TItem>::GetCost(shared_ptr<Vertex<TTag, TItem>> v)
{
	if (v->GetTag() == GetTag() && v->GetItem() == GetItem())
		return 0;
	return neighbours_.find(v) != neighbours_.end() ? neighbours_[v] : -1;
}
template <typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::MinSubGraphsDifference(TTag parent, TItem sum, set<TItem> &diffs) const
{
	TItem localSum = item_;
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
	{
		if (it->first->GetTag() != parent)
			localSum += it->first->MinSubGraphsDifference(GetTag(), sum, diffs);
	}
	TItem balance = sum - localSum;
	diffs.emplace(abs((long)balance - (long)localSum));
	return localSum;
}
template <typename TTag, typename TItem>
long Vertex<TTag, TItem>::GetTotalCost() const { return cost_; }

template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::SetTotalCost(long cost) { cost_ = cost; }

template <typename TTag, typename TItem>
void Vertex<TTag, TItem>::ResetTotalCost()
{
	cost_ = numeric_limits<long>::max();
}
template <typename TTag, typename TItem>
Vertex<TTag, TItem> &Vertex<TTag, TItem>::operator=(Vertex<TTag, TItem> &rhs)
{
	tag_ = rhs.tag_;
	item_ = rhs.item_;
	return *this;
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator==(Vertex<TTag, TItem> &rhs)
{
	return item_ == rhs.item_ && tag_ == rhs.tag_;
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator!=(Vertex<TTag, TItem> &rhs)
{
	return !(*this == rhs);
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator<(Vertex<TTag, TItem> &rhs)
{
	return item_ < rhs.item_;
}

template <typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator>(Vertex<TTag, TItem> &rhs)
{
	return item_ > rhs.item_;
}