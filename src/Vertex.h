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
class Vertex : public enable_shared_from_this<Vertex<TTag, TItem>>
{
private:
	void ResetTotalCost();
	bool HasNeighbour(TTag, TItem) const;

public:
	Vertex();
	explicit Vertex(TTag);
	explicit Vertex(TTag, TItem);
	Vertex(TTag, TItem, map<shared_ptr<Vertex<TTag, TItem>>, long>);
	virtual ~Vertex();
	TTag GetTag() const;
	TItem GetItem() const;
	size_t NeighbourCount() const;
	TItem GetSubGraphSum(TTag);
	long GetCost(shared_ptr<Vertex<TTag, TItem>>);
	long GetTotalCost() const;
	void SetTotalCost(long);
	TItem MinSubGraphsDifference(TTag, TItem) const;
	bool HasNeighbours() const;
	bool HasNeighbour(TTag) const;
	bool HasNeighbour(shared_ptr<Vertex<TTag, TItem>>) const;
	vector<shared_ptr<Vertex<TTag, TItem>>> GetNeighbours();
	void AddNeighbour(shared_ptr<Vertex<TTag, TItem>>, long);
	map<shared_ptr<Vertex<TTag, TItem>>, long> GetNeighboursWithCost();
	void RemoveNeighbour(shared_ptr<Vertex<TTag, TItem>>);
	size_t EvenForestDescendentsCount(TTag, set<string> &) const;
	Vertex<TTag, TItem> &operator=(Vertex<TTag, TItem> &);
	bool operator<(const Vertex<TTag, TItem> &) const;
	bool operator==(Vertex<TTag, TItem> &);
	bool operator!=(Vertex<TTag, TItem> &);
	bool operator<(Vertex<TTag, TItem> &);
	bool operator>(Vertex<TTag, TItem> &);

protected:
	TTag _tag;
	TItem _item, _sum;
	long _cost;
	map<shared_ptr<Vertex<TTag, TItem>>, long> _neighbours; // neighbours and costs from this vertex to them
};