#pragma once
#include <map>
#include <set>
#include "Vertex.h"
#include "VertexEdge.h"
using namespace std;
template<class T>
class Graph
{
public:
	Graph();
	virtual ~Graph();
	size_t Count();
	void AddVertex(VertexEdge<T>);
	VertexEdge<T>* AddVertex(T);
	void AddDirectedEdge(VertexEdge<T>, VertexEdge<T>, long);
	void AddUndirectedEdge(VertexEdge<T>, VertexEdge<T>, long);
	bool HasVertex(T);
	bool Remove(T);
	void Print(VertexEdge<T>* vertex, set<T> visited);
private:
	map<T, Vertex<T>*> vertices_;
};