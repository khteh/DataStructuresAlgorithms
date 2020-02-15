#include "stdafx.h"
#include "VertexEdge.h"
#include <vector>
using namespace std;
template<class T>
VertexEdge<T>::VertexEdge()
{
}

template<class T>
VertexEdge<T>::VertexEdge(T tag)
	: Vertex(tag)
{
}

template<class T>
VertexEdge<T>::VertexEdge(T tag, map<T, Vertex<T>> neighbours)
	: Vertex(tag, neighbours)
{

}

template<class T>
VertexEdge<T>::~VertexEdge()
{
}
template<class T>
T VertexEdge<T>::GetTag()
{
	return tag_;
}
template<class T>
void VertexEdge<T>::AddNeighbour(VertexEdge<T> to, long cost)
{
	if (neighbours_.find(to.GetTag()) == neighbours_.end()) {
		neighbours_.emplace(to.GetTag, to);
		costs_.emplace(to, cost);
	}
}
template<class T>
void VertexEdge<T>::RemoveNeighbour(VertexEdge<T> to)
{
	if (neighbours_.find(to.GetTag()) != neighbours_.end())
		neighbours_.erase(to.GetTag());
}
template<class T>
vector<VertexEdge<T>*> VertexEdge<T>::GetNeighbours()
{
	vector<VertexEdge<T>*> vertices;
	transform(neighbours_.begin(), neighbours_.end(), back_inserter(vertices), (&)(i) => return i.second);
	return vertices;
}
template<class T>
bool VertexEdge<T>::HasNeighbours()
{
	return !neighbours.size() > 0;
}
template<class T>
bool VertexEdge<T>::HasNeighbour(T tag)
{
	return neighbours_.find(tag) != neighbours_.end();
}
template<class T>
size_t VertexEdge<T>::NeighbourCount()
{
	return neighbours_.Size();
}