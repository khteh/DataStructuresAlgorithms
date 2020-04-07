#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <set>
#include <iostream>
using namespace std;
template class Graph<long>;
template<class T>
Graph<T>::Graph()
{
}
template<class T>
Graph<T>::Graph(vector<T>& data)
{
	for (vector<T>::iterator it = data.begin(); it != data.end(); it++)
		AddVertex(*it);
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
void Graph<T>::AddVertex(shared_ptr<Vertex<T>> v)
{
	vertices_.emplace(v->GetTag(), v);
}
template<class T>
shared_ptr<Vertex<T>> Graph<T>::AddVertex(T tag)
{
	vertices_.emplace(tag, make_shared<Vertex<T>>(tag));
	return vertices_[tag];
}
template<class T>
void Graph<T>::AddDirectedEdge(shared_ptr<Vertex<T>> from, shared_ptr<Vertex<T>> to, long cost)
{
	from->AddNeighbour(to, cost);
}
template<class T>
void Graph<T>::AddUndirectedEdge(shared_ptr<Vertex<T>> from, shared_ptr<Vertex<T>> to, long cost)
{
	from->AddNeighbour(to, cost);
	to->AddNeighbour(from, cost);
}
template<class T>
bool Graph<T>::HasVertex(T tag)
{
	return vertices_.find(tag) != vertices_.end();
}
template<class T>
shared_ptr<Vertex<T>> Graph<T>::GetVertex(T tag)
{
	return vertices_.find(tag) != vertices_.end() ? vertices_[tag] : nullptr;
}
template<class T>
bool Graph<T>::Remove(T tag)
{
	shared_ptr<Vertex<T>> vertex;
	if (vertices_.find(tag) == vertices_.end())
		return false;
	vertex = vertices_[tag];
	vertices_.erase(tag);
	for (map<T, shared_ptr<Vertex<T>>>::iterator it = vertices_.begin(); it != vertices_.end(); it++)
		if (it->second->HasNeighbour(tag))
			it->second->RemoveNeighbour(vertex);
	return true;
}
template<class T>
void Graph<T>::Print(shared_ptr<Vertex<T>> vertex)
{
	string uni = "-->";
	string multi = "<-->";
	vector<shared_ptr<Vertex<T>>> neighbours = vertex->GetNeighbours();
	if (neighbours.size() > 0)
		cout << vertex->GetTag();
	shared_ptr<Vertex<T>> previous = vertex;
	bool space = false;
	for (vector<shared_ptr<Vertex<T>>>::iterator it = neighbours.begin(); it != neighbours.end(); *it++, space = true)
		cout << (space ? " " : "") << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << (*it)->GetTag() << " [" << previous->GetCost(*it) << "] " << endl;
}