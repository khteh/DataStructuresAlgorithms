#pragma once
#include "Vertex.h"
#include <vector>
using namespace std;
template<class T>
class VertexEdge : public Vertex<T>
{
public:
	VertexEdge();
	VertexEdge(T);
	VertexEdge(T, map<T, Vertex>);
	virtual ~VertexEdge();
	T GetTag();
	void AddNeighbour(VertexEdge<T> to, long cost);
	void RemoveNeighbour(VertexEdge<T> to);
	vector<VertexEdge<T>*> GetNeighbours();
	bool HasNeighbours();
	bool HasNeighbour(T);
	size_t NeighbourCount();
private:
	map<VertexEdge<T>*, long> costs_;
};