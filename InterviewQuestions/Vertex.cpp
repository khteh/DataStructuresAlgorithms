#include "stdafx.h"
#include "Vertex.h"

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
Vertex<T>::Vertex(T tag, map<T, Vertex> neighbours)
{
	tag_ = tag;
	neighbours_ = neighbours;
}
template<class T>
Vertex<T>::~Vertex()
{
}
