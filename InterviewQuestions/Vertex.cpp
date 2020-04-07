#include "stdafx.h"
#include "Vertex.h"
template class Vertex<long>;
template<class T>
Vertex<T>::Vertex()
{
}
template<class T>
Vertex<T>::Vertex(T tag)
{
	tag_ = tag;
}
template<class T>
Vertex<T>::Vertex(T tag, map<T, shared_ptr<Vertex<T>>> neighbours)
{
	tag_ = tag;
	neighbours_ = neighbours;
}
template<class T>
Vertex<T>::~Vertex()
{
}
template<class T>
T Vertex<T>::GetTag()
{
	return tag_;
}
template<class T>
void Vertex<T>::AddNeighbour(shared_ptr<Vertex<T>> to, long cost)
{
	if (neighbours_.find(to->GetTag()) == neighbours_.end()) {
		neighbours_.emplace(to->GetTag(), to);
		costs_.emplace(to, cost);
	}
}
template<class T>
void Vertex<T>::RemoveNeighbour(shared_ptr<Vertex<T>> to)
{
	if (neighbours_.find(to->GetTag()) != neighbours_.end()) {
		neighbours_.erase(to->GetTag());
		costs_.erase(to);
	}
}
template<class T>
vector<shared_ptr<Vertex<T>>> Vertex<T>::GetNeighbours()
{
	vector<shared_ptr<Vertex<T>>> vertices;
	transform(
		neighbours_.begin(),
		neighbours_.end(),
		back_inserter(vertices),
		[](const map<T, shared_ptr<Vertex<T>>>::value_type& pair) {return pair.second; });
	return vertices;
}
template<class T>
bool Vertex<T>::HasNeighbours()
{
	return !neighbours_.empty();
}
template<class T>
bool Vertex<T>::HasNeighbour(T tag)
{
	return neighbours_.find(tag) != neighbours_.end();
}
template<class T>
bool Vertex<T>::HasNeighbour(shared_ptr<Vertex<T>> v)
{
	return neighbours_.find(v->GetTag()) != neighbours_.end();
}
template<class T>
size_t Vertex<T>::NeighbourCount()
{
	return neighbours_.size();
}
template<class T>
long Vertex<T>::GetCost(shared_ptr<Vertex<T>> v)
{
	return costs_.find(v) != costs_.end() ? costs_[v] : -1;
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