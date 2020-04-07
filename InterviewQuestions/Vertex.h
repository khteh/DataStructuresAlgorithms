#pragma once
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;
template<class T>
class Vertex
{
public:
	Vertex();
	Vertex(T tag);
	Vertex(T tag, map<T, shared_ptr<Vertex<T>>>);
	virtual ~Vertex();
	T GetTag();
	long GetCost(shared_ptr<Vertex<T>>);
	void AddNeighbour(shared_ptr<Vertex<T>>, long);
	void RemoveNeighbour(shared_ptr<Vertex<T>>);
	vector<shared_ptr<Vertex<T>>> GetNeighbours();
	bool HasNeighbours();
	bool HasNeighbour(T);
	bool HasNeighbour(shared_ptr<Vertex<T>>);
	size_t NeighbourCount();
	Vertex<T>& operator=(Vertex<T>&);
	bool operator==(Vertex<T>&);
	bool operator!=(Vertex<T>&);
	bool operator<(Vertex<T>&);
	bool operator>(Vertex<T>&);
protected:
	T tag_;
	map<T, shared_ptr<Vertex<T>>> neighbours_;
	map<shared_ptr<Vertex<T>>, long> costs_;
};