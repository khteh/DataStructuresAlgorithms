#pragma once
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <sstream>
#include <limits>
using namespace std;
template <typename TTag, typename TItem> // TTag is used as a unique ID. Graph vertices can have duplicate values of TItem
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
	TItem MinSubGraphsDifference(TTag, TItem, set<TItem> &) const;
	long GetTotalCost() const;
	void SetTotalCost(long);
	void ResetTotalCost();
	void AddNeighbour(shared_ptr<Vertex<TTag, TItem>>, long);
	void RemoveNeighbour(shared_ptr<Vertex<TTag, TItem>>);
	vector<shared_ptr<Vertex<TTag, TItem>>> GetNeighbours();
	map<shared_ptr<Vertex<TTag, TItem>>, long> GetNeighboursWithCost();
	bool HasNeighbours() const;
	bool HasNeighbour(TTag) const;
	bool HasNeighbour(TTag, TItem) const;
	bool HasNeighbour(shared_ptr<Vertex<TTag, TItem>>) const;
	size_t NeighbourCount() const;
	size_t EvenForestDescendentsCount(TTag, set<string> &) const;
	Vertex<TTag, TItem> &operator=(Vertex<TTag, TItem> &);
	bool operator<(const Vertex<TTag, TItem> &) const;
	bool operator==(Vertex<TTag, TItem> &);
	bool operator!=(Vertex<TTag, TItem> &);
	bool operator<(Vertex<TTag, TItem> &);
	bool operator>(Vertex<TTag, TItem> &);

protected:
	TTag _tag;
	TItem _item;
	long _cost;
	map<shared_ptr<Vertex<TTag, TItem>>, long> _neighbours; // neighbours and costs from this vertex to them
};