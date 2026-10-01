#pragma once
template <typename TTag, typename TItem> // TTag is used as a unique ID. Graph vertices can have duplicate values of TItem
class Vertex : public enable_shared_from_this<Vertex<TTag, TItem>>
{
private:
	void Swap(Vertex<TTag, TItem> &);
	void ResetTotalCost();
	bool HasNeighbour(TTag, TItem) const;

public:
	Vertex();
	explicit Vertex(TTag);
	explicit Vertex(TTag, TItem);
	Vertex(const Vertex<TTag, TItem> &);	 // Copy constructor
	Vertex(Vertex<TTag, TItem> &&) noexcept; // Move constructor
	Vertex(const shared_ptr<Vertex<TTag, TItem>>);
	virtual ~Vertex();

	Vertex(TTag, TItem, map<shared_ptr<Vertex<TTag, TItem>>, long>);
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
	void ClearNeighbours(); // Break shared_ptr cycles between neighbouring vertices
	size_t EvenForestDescendentsCount(TTag, set<string> &) const;
	// Vertex<TTag, TItem> &operator=(const Vertex<TTag, TItem> &); // Copy assignment operator https://stackoverflow.com/questions/72345198/c20-unable-to-satisfy-constraint-for-rangesremove-if
	// Vertex<TTag, TItem> &operator=(Vertex<TTag, TItem> &&) noexcept; // Move assignment operator
	/*
	https://stackoverflow.com/questions/64378721/what-is-the-difference-between-the-copy-constructor-and-move-constructor-in-c
	The above 2 operators can be implemented as 1 operator, like below.
	This allows the caller to decide whether to construct the rhs parameter
	using its copy constructor or move constructor...
	*/
	Vertex<TTag, TItem> &operator=(Vertex<TTag, TItem>);
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