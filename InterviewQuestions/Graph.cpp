#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <set>
#include <iostream>
using namespace std;
template<class T>
Graph<T>::Graph()
{
}

template<class T>
Graph<T>::~Graph()
{
}
template<class T>
size_t Graph<T>::Count()
{
	return vertices_.size();
}

template<class T>
void Graph<T>::AddVertex(VertexEdge<T> edge)
{
	vertices_.emplace(edge.GetTag(), edge);
}
template<class T>
VertexEdge<T>* Graph<T>::AddVertex(T tag)
{
	vertices_.emplace(tag, new VertexEdge(tag));
	return vertices_[tag];
}
template<class T>
void Graph<T>::AddDirectedEdge(VertexEdge<T> from, VertexEdge<T> to, long cost)
{
	from.AddNeighbour(to, cost);
}
template<class T>
void Graph<T>::AddUndirectedEdge(VertexEdge<T> from, VertexEdge<T> to, long cost)
{
	from.AddNeighbour(to, cost);
	to.AddNeighbour(from, cost);
}
template<class T>
bool Graph<T>::HasVertex(T tag)
{
	return vertices_.find(tag) != vertices_.end();
}
template<class T>
bool Graph<T>::Remove(T tag)
{
	if (vertices_.find(tag) == vertices_.end())
		return false;
	vertices_.erase(tag);
	for (map<T, Vertex<T>*>::iterator it = vertices_.begin(); it != vertices.end(); it++) {
		if (it->HasNeighbour(tag))
			it->RemoveNeighbour(tag);
	}
	return true;
}
template<class T>
void Graph<T>::Print(VertexEdge<T>* vertex, set<T> visited)
{
	string uni = "-->";
	string multi = "<-->";
	vector<VertexEdge<T>*> neighbours = vertex.Getneighbours();
	if (neighbours.size() > 0)
		cout << vertex;
	VertexEdge<T>* previous = vertex;
	for (vector<VertexEdge<T>*>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
		cout << (it->HasNeighbour(previous->GetTag()) ? multi : uni) << it->GetTag();
	}
}