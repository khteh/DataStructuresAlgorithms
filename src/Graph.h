#pragma once
#include <assert.h>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include "oneapi/tbb.h"
#include "Vertex.h"
using namespace std;
namespace ranges = std::ranges;
using namespace oneapi::tbb;
template <typename TTag, typename TItem> // TTag is used as a unique ID. Graph vertices can have duplicate values of TItem
class Graph
{
private:
	map<TTag, shared_ptr<Vertex<TTag, TItem>>> _vertices;
	TItem GetSubGraphSum(TTag);
	void AddVertex(shared_ptr<Vertex<TTag, TItem>>);
	shared_ptr<Vertex<TTag, TItem>> AddVertex(TTag, TItem);
	void AddDirectedEdge(shared_ptr<Vertex<TTag, TItem>>, shared_ptr<Vertex<TTag, TItem>>, long);
	void AddDirectedEdge(TTag from, TTag to, long cost);
	long GetPathsCosts(shared_ptr<Vertex<TTag, TItem>>, shared_ptr<Vertex<TTag, TItem>>);
	void Print(TTag);

public:
	Graph();
	Graph(vector<TItem> &);
	virtual ~Graph();
	size_t Count() const;
	void Clear();
	void AddVertices(vector<TItem> &);
	shared_ptr<Vertex<TTag, TItem>> AddVertex(TTag);
	void AddUndirectedEdge(shared_ptr<Vertex<TTag, TItem>>, shared_ptr<Vertex<TTag, TItem>>, long);
	void AddUndirectedEdge(TTag from, TTag to, long cost);
	bool HasVertex(TTag) const;
	shared_ptr<Vertex<TTag, TItem>> GetVertex(TTag);
	bool Remove(TTag);
	size_t PrimMinimumSpanningTree(shared_ptr<Vertex<TTag, TItem>>);
	void Dijkstra(TTag, map<shared_ptr<Vertex<TTag, TItem>>, long> &);
	long Dijkstra(TTag, TTag);
	void Dijkstra(TTag, vector<long> &);
	vector<long> BFSShortestPaths(size_t nodecount, vector<vector<TTag>> &, TTag);
	void GetBFSNodes(map<size_t, vector<shared_ptr<Vertex<TTag, TItem>>>> &, shared_ptr<Vertex<TTag, TItem>> &);
	long GetLowestPathCost(size_t, vector<TTag> &, vector<TTag> &, vector<long> &);
	TItem MinSubGraphsDifference(TTag);
	long EvenForest(TTag);
	void Print(shared_ptr<Vertex<TTag, TItem>>) const;
};