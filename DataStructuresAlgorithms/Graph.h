#pragma once
#include <assert.h>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include "Vertex.h"
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
using namespace tbb;
#endif

template <typename TTag, typename TItem> // TTag is used as a unique ID. Graph vertices can have duplicate values of TItem
class Graph
{
public:
	Graph();
	Graph(vector<TItem> &);
	virtual ~Graph();
	size_t Count() const;
	void Clear();
	void AddVertex(shared_ptr<Vertex<TTag, TItem>>);
	shared_ptr<Vertex<TTag, TItem>> AddVertex(TTag);
	shared_ptr<Vertex<TTag, TItem>> AddVertex(TTag, TItem);
	void AddDirectedEdge(shared_ptr<Vertex<TTag, TItem>>, shared_ptr<Vertex<TTag, TItem>>, long);
	void AddUndirectedEdge(shared_ptr<Vertex<TTag, TItem>>, shared_ptr<Vertex<TTag, TItem>>, long);
	bool HasVertex(TTag);
	shared_ptr<Vertex<TTag, TItem>> GetVertex(TTag);
	bool Remove(TTag);
	size_t PrimMinimumSpanningTree(shared_ptr<Vertex<TTag, TItem>>);
	void Dijkstra(TTag, map<shared_ptr<Vertex<TTag, TItem>>, long> &);
	long Dijkstra(TTag, TTag);
	void GetBFSNodes(map<size_t, vector<shared_ptr<Vertex<TTag, TItem>>>> &, shared_ptr<Vertex<TTag, TItem>> &);
	long GetPathsCosts(set<shared_ptr<Vertex<TTag, TItem>>> &, shared_ptr<Vertex<TTag, TItem>>, shared_ptr<Vertex<TTag, TItem>>);
	TItem MinSubGraphsDifference(TTag, TItem);
	long EvenForest(TTag);
	void Print(TTag);
	void Print(shared_ptr<Vertex<TTag, TItem>>);

private:
	map<TTag, shared_ptr<Vertex<TTag, TItem>>> vertices_;
};