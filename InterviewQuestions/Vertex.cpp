#include "stdafx.h"
#include "Vertex.h"
template class Vertex<int, int>;
template class Vertex<long, long>;
template class Vertex<size_t, size_t>;
template<typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex()
	: tag_(TTag()), item_(TItem()), cost_(numeric_limits<long>::max())
{
}
template<typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag)
	: tag_(tag), item_(TItem()), cost_(numeric_limits<long>::max())
{
}
template<typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag, TItem item)
	: tag_(tag), item_(item), cost_(numeric_limits<long>::max())
{
}
template<typename TTag, typename TItem>
Vertex<TTag, TItem>::Vertex(TTag tag, TItem item, map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours)
	: tag_(tag), item_(item), cost_(numeric_limits<long>::max()), neighbours_(neighbours)
{
}
template<typename TTag, typename TItem>
Vertex<TTag, TItem>::~Vertex()
{
	neighbours_.clear();
}
template<typename TTag, typename TItem>
TTag Vertex<TTag, TItem>::GetTag() const
{
	return tag_;
}
template<typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::GetItem() const
{
	return item_;
}
template<typename TTag, typename TItem>
void Vertex<TTag, TItem>::AddNeighbour(shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (neighbours_.find(to) == neighbours_.end())
		neighbours_.emplace(to, cost);
	else if (neighbours_[to] > cost)
		neighbours_[to] = cost;
}
template<typename TTag, typename TItem>
void Vertex<TTag, TItem>::RemoveNeighbour(shared_ptr<Vertex<TTag, TItem>> to)
{
	neighbours_.erase(to);
}
template<typename TTag, typename TItem>
vector<shared_ptr<Vertex<TTag, TItem>>> Vertex<TTag, TItem>::GetNeighbours()
{
	vector<shared_ptr<Vertex<TTag, TItem>>> vertices;
	transform(
		neighbours_.begin(),
		neighbours_.end(),
		back_inserter(vertices),
		[](const map<shared_ptr<Vertex<TTag, TItem>>, long>::value_type& pair) {return pair.first; });
	return vertices;
}
template<typename TTag, typename TItem>
map<shared_ptr<Vertex<TTag, TItem>>, long> Vertex<TTag, TItem>::GetNeighboursWithCost()
{
	return neighbours_;
}
template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbours() const
{
	return !neighbours_.empty();
}
template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(TTag tag) const
{
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
		if (it->first->GetTag() == tag)
			return true;
	return false;
}
template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(TTag tag, TItem item) const
{
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
		if (it->first->GetTag() == tag && it->first->GetItem() == item)
			return true;
	return false;
}
template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::HasNeighbour(shared_ptr<Vertex<TTag, TItem>> v) const
{
	return neighbours_.find(v) != neighbours_.end();
}
template<typename TTag, typename TItem>
size_t Vertex<TTag, TItem>::NeighbourCount() const
{
	return neighbours_.size();
}
template<typename TTag, typename TItem>
long Vertex<TTag, TItem>::GetCost(shared_ptr<Vertex<TTag, TItem>> v)
{
	if (v->GetTag() == GetTag() && v->GetItem() == GetItem())
		return 0;
	return neighbours_.find(v) != neighbours_.end() ? neighbours_[v] : -1;
}
template<typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::GetSum(set<TTag> visited) const
{
	size_t sum = item_;
	visited.insert(tag_);
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
		if (visited.find(it->first->GetTag()) == visited.end())
			sum += it->first->GetSum(visited);
	return sum;
}
template<typename TTag, typename TItem>
void Vertex<TTag, TItem>::ResetTotalCost()
{
	cost_ = numeric_limits<long>::max();
}
template<typename TTag, typename TItem>
TItem Vertex<TTag, TItem>::MinSubGraphDifference(set<TTag> visited, TItem sum)
{
	/*
			10
		11		5
	Diff: 15 - 11 = 4
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	ostringstream oss;
	multimap<TItem, shared_ptr<Vertex<TTag, TItem>>> vertices;
	visited.insert(tag_);
	if constexpr (is_same_v<TItem, long> || is_same_v<TItem, int> || is_same_v<TItem, size_t>) {
		if (neighbours_.empty()) // This will always be false in an UnDirected graph as every node points to it's parent
			return abs((long)sum - (long)item_);
		else if (neighbours_.size() == 1) {
			typename map<shared_ptr<Vertex<TTag, TItem>>, long>::iterator it = neighbours_.begin();
			return visited.find(it->first->GetTag()) == visited.end() ?
					it->first->MinSubGraphDifference(visited, sum + item_) : abs((long)sum - (long)item_);
		}
		for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
			if (visited.find(it->first->GetTag()) == visited.end())
				vertices.emplace(it->first->GetSum(visited), it->first);
		if (vertices.size() == 1) {
			typename multimap<TItem, shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices.begin();
			return it->second->MinSubGraphDifference(visited, sum + item_);
		}
		typename map<TItem, shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices.begin();
		typename map<TItem, shared_ptr<Vertex<TTag, TItem>>>::reverse_iterator it1 = vertices.rbegin();
		TItem leftSum = it->first, rightSum = it1->first;
		for (size_t i = 0, j = vertices.size() - 1; i < j; ) {
			if (leftSum < rightSum) {
				++it;
				i++;
				if (i < j && it != vertices.end())
					leftSum += it->first;
			}
			if (rightSum < leftSum) {
				j--;
				it1++;
				if (i < j && it1 != vertices.rend())
					leftSum += it1->first;
			}
		}
		sum += item_;
		if (leftSum == rightSum)
			return 0;
		TItem sum1 = sum + min(leftSum, rightSum);
		TItem subgraphSum = max(leftSum, rightSum);
		if (sum1 >= subgraphSum)
			return abs((long)sum1 - (long)subgraphSum);
		shared_ptr<Vertex<TTag, TItem>> n = it1->second;
		TItem adjustedSum = subgraphSum - n->GetItem();
		if (sum1 + n->GetItem() == adjustedSum)
			return 0;
		else if (sum1 + n->GetItem() > adjustedSum)
			return abs((long)(sum1 + n->GetItem()) - (long)adjustedSum);
		else if (visited.find(n->GetTag()) == visited.end())
			return n->MinSubGraphDifference(visited, sum1);
	} else {
		oss << __FUNCTION__ << " is only applicable to integral types!";
		throw runtime_error(oss.str());
	}
	return -1;
}
template<typename TTag, typename TItem>
Vertex<TTag, TItem>& Vertex<TTag, TItem>::operator=(Vertex<TTag, TItem>& rhs)
{
	tag_ = rhs.tag_;
	item_ = rhs.item_;
	return *this;
}

template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator==(Vertex<TTag, TItem>& rhs)
{
	return item_ == rhs.item_ && tag_ == rhs.tag_;
}

template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator!=(Vertex<TTag, TItem>& rhs)
{
	return !(*this == rhs);
}

template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator<(Vertex<TTag, TItem>& rhs)
{
	return item_ < rhs.item_;
}

template<typename TTag, typename TItem>
bool Vertex<TTag, TItem>::operator>(Vertex<TTag, TItem>& rhs)
{
	return item_ > rhs.item_;
}