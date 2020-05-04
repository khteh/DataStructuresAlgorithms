#pragma once
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
template<typename TTag, typename TItem>	// TTag is used as a unique ID. Graph vertices can have duplicate values of TItem
class Vertex
{
public:
	Vertex();
	Vertex(TTag tag);
	Vertex(TTag tag, TItem item);
	Vertex(TTag tag, TItem item, map<shared_ptr<Vertex<TTag, TItem>>, long>);
	virtual ~Vertex();
	TTag GetTag() const;
	TItem GetItem() const;
	long GetCost(shared_ptr<Vertex<TTag, TItem>>);
	long GetTotalCost() const;
	TItem GetSum() const;
	void ResetTotalCost();
	void SetTotalCost(long);
	void AddNeighbour(shared_ptr<Vertex<TTag, TItem>>, long);
	void RemoveNeighbour(shared_ptr<Vertex<TTag, TItem>>);
	vector<shared_ptr<Vertex<TTag, TItem>>> GetNeighbours();
	map<shared_ptr<Vertex<TTag, TItem>>, long> GetNeighboursWithCost();
	bool HasNeighbours() const;
	bool HasNeighbour(TTag) const;
	bool HasNeighbour(TTag, TItem) const;
	bool HasNeighbour(shared_ptr<Vertex<TTag, TItem>>) const;
	size_t NeighbourCount() const;
	TItem MinSubGraphDifference(TItem sum = 0);
	Vertex<TTag, TItem>& operator=(Vertex<TTag, TItem>&);
	bool operator==(Vertex<TTag, TItem>&);
	bool operator!=(Vertex<TTag, TItem>&);
	bool operator<(Vertex<TTag, TItem>&);
	bool operator>(Vertex<TTag, TItem>&);
protected:
	TTag tag_;
	TItem item_;
	long cost_;
	map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours_; // neighbours and costs from this vertex to them
	TItem MinSubGraphDifference(shared_ptr<Vertex<TTag, TItem>>, TItem, TItem);
};