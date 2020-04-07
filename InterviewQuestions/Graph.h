#pragma once
#include <map>
#include <set>
#include "Vertex.h"
using namespace std;
template<class T>
class Graph
{
public:
	Graph();
	Graph(vector<T>&);
	virtual ~Graph();
	size_t Count();
	void AddVertex(shared_ptr<Vertex<T>>);
	shared_ptr<Vertex<T>> AddVertex(T);
	void AddDirectedEdge(shared_ptr<Vertex<T>>, shared_ptr<Vertex<T>>, long);
	void AddUndirectedEdge(shared_ptr<Vertex<T>>, shared_ptr<Vertex<T>>, long);
	bool HasVertex(T);
	shared_ptr<Vertex<T>> GetVertex(T);
	bool Remove(T);
	void Print(shared_ptr<Vertex<T>>);
private:
	map<T, shared_ptr<Vertex<T>>> vertices_;
};