#pragma once
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
using namespace std;
template<class T>
class Vertex
{
public:
	Vertex();
	Vertex(T tag);
	Vertex(T tag, map<shared_ptr<Vertex<T>>, long>);
	virtual ~Vertex();
	T GetTag() const;
	long GetCost(shared_ptr<Vertex<T>>);
	long GetTotalCost();
	void ResetTotalCost();
	void SetTotalCost(long);
	void AddNeighbour(shared_ptr<Vertex<T>>, long);
	void RemoveNeighbour(shared_ptr<Vertex<T>>);
	vector<shared_ptr<Vertex<T>>> GetNeighbours();
	map<shared_ptr<Vertex<T>>, long> GetNeighboursWithCost();
	bool HasNeighbours() const;
	bool HasNeighbour(T) const;
	bool HasNeighbour(shared_ptr<Vertex<T>>) const;
	size_t NeighbourCount() const;
	Vertex<T>& operator=(Vertex<T>&);
	bool operator==(Vertex<T>&);
	bool operator!=(Vertex<T>&);
	bool operator<(Vertex<T>&);
	bool operator>(Vertex<T>&);
protected:
	T tag_;
	long cost_;
	map<shared_ptr<Vertex<T>>, long> neighbours_; // neighbours and costs from this vertex to them
};