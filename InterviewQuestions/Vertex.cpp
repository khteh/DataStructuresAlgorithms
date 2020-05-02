#include "stdafx.h"
#include "Vertex.h"
template class Vertex<long>;
template class Vertex<size_t>;
template<class T>
Vertex<T>::Vertex()
	: tag_(T()), cost_(numeric_limits<T>::max())
{
}
template<class T>
Vertex<T>::Vertex(T tag)
	: tag_(tag), cost_(numeric_limits<T>::max())
{
}
template<class T>
Vertex<T>::Vertex(T tag, map<shared_ptr<Vertex<T>>, long> neighbours)
	: tag_(tag), cost_(numeric_limits<T>::max()), neighbours_(neighbours)
{
}
template<class T>
Vertex<T>::~Vertex()
{
	neighbours_.clear();
}
template<class T>
T Vertex<T>::GetTag() const
{
	return tag_;
}
template<class T>
void Vertex<T>::AddNeighbour(shared_ptr<Vertex<T>> to, long cost)
{
	if (neighbours_.find(to) == neighbours_.end())
		neighbours_.emplace(to, cost);
	else if (neighbours_[to] > cost)
		neighbours_[to] = cost;
}
template<class T>
void Vertex<T>::RemoveNeighbour(shared_ptr<Vertex<T>> to)
{
	neighbours_.erase(to);
}
template<class T>
vector<shared_ptr<Vertex<T>>> Vertex<T>::GetNeighbours()
{
	vector<shared_ptr<Vertex<T>>> vertices;
	transform(
		neighbours_.begin(),
		neighbours_.end(),
		back_inserter(vertices),
		[](const map<shared_ptr<Vertex<T>>, long>::value_type& pair) {return pair.first; });
	return vertices;
}
template<class T>
map<shared_ptr<Vertex<T>>, long> Vertex<T>::GetNeighboursWithCost()
{
	return neighbours_;
}
template<class T>
bool Vertex<T>::HasNeighbours() const
{
	return !neighbours_.empty();
}
template<class T>
bool Vertex<T>::HasNeighbour(T tag) const
{
	for (map<shared_ptr<Vertex<T>>, long>::const_iterator it = neighbours_.begin(); it != neighbours_.end(); it++)
		if (it->first->GetTag() == tag)
			return true;
	return false;
}
template<class T>
bool Vertex<T>::HasNeighbour(shared_ptr<Vertex<T>> v) const
{
	return neighbours_.find(v) != neighbours_.end();
}
template<class T>
size_t Vertex<T>::NeighbourCount() const
{
	return neighbours_.size();
}
template<class T>
long Vertex<T>::GetCost(shared_ptr<Vertex<T>> v)
{
	if (v->GetTag() == GetTag())
		return 0;
	return neighbours_.find(v) != neighbours_.end() ? neighbours_[v] : -1;
}
template<class T>
long Vertex<T>::GetTotalCost()
{
	return cost_;
}
template<class T>
void Vertex<T>::ResetTotalCost()
{
	cost_ = numeric_limits<T>::max();
}
template<class T>
void Vertex<T>::SetTotalCost(long cost)
{
	cost_ = cost;
}
template<class T>
Vertex<T>& Vertex<T>::operator=(Vertex<T>& rhs)
{
	tag_ = rhs.tag_;
	return *this;
}

template<class T>
bool Vertex<T>::operator==(Vertex<T>& rhs)
{
	return tag_ == rhs.tag_;
}

template<class T>
bool Vertex<T>::operator!=(Vertex<T>& rhs)
{
	return !(*this == rhs);
}

template<class T>
bool Vertex<T>::operator<(Vertex<T>& rhs)
{
	return tag_ < rhs.tag_;
}

template<class T>
bool Vertex<T>::operator>(Vertex<T>& rhs)
{
	return tag_ > rhs.tag_;
}