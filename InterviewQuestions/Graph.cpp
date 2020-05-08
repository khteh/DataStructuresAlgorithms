#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <set>
#include <iostream>
using namespace std;
template class Graph<long, long>;
template class Graph<size_t, size_t>;
template<typename TTag, typename TItem>
Graph<TTag, TItem>::Graph()
{
}
template<typename TTag, typename TItem>
Graph<TTag, TItem>::Graph(vector<TItem>& data)
{
	for (vector<TItem>::iterator it = data.begin(); it != data.end(); it++)
		AddVertex(*it, *it); // tag = item
}
template<typename TTag, typename TItem>
Graph<TTag, TItem>::~Graph()
{
	Clear();
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::Clear()
{
	vertices_.clear();
}
template<typename TTag, typename TItem>
size_t Graph<TTag, TItem>::Count()
{
	return vertices_.size();
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::AddVertex(shared_ptr<Vertex<TTag, TItem>> v)
{
	vertices_.emplace(v->GetTag(), v);
}
template<typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::AddVertex(TTag tag)
{
	vertices_.emplace(tag, make_shared<Vertex<TTag, TItem>>(tag));
	return vertices_[tag];
}
template<typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::AddVertex(TTag tag, TItem item)
{
	vertices_.emplace(tag, make_shared<Vertex<TTag, TItem>>(tag, item));
	return vertices_[tag];
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::AddDirectedEdge(shared_ptr<Vertex<TTag, TItem>> from, shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (vertices_.find(from->GetTag()) == vertices_.end())
		vertices_.emplace(from->GetTag(), from);
	if (vertices_.find(to->GetTag()) == vertices_.end())
		vertices_.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::AddUndirectedEdge(shared_ptr<Vertex<TTag, TItem>> from, shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (vertices_.find(from->GetTag()) == vertices_.end())
		vertices_.emplace(from->GetTag(), from);
	if (vertices_.find(to->GetTag()) == vertices_.end())
		vertices_.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
	to->AddNeighbour(from, cost);
}
template<typename TTag, typename TItem>
bool Graph<TTag, TItem>::HasVertex(TTag tag)
{
	return vertices_.find(tag) != vertices_.end();
}
template<typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::GetVertex(TTag tag)
{
	return vertices_.find(tag) != vertices_.end() ? vertices_[tag] : nullptr;
}
template<typename TTag, typename TItem>
bool Graph<TTag, TItem>::Remove(TTag tag)
{
	shared_ptr<Vertex<TTag, TItem>> vertex;
	if (vertices_.find(tag) == vertices_.end())
		return false;
	vertex = vertices_[tag];
	vertices_.erase(tag);
	for (map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices_.begin(); it != vertices_.end(); it++)
		if (it->second->HasNeighbour(tag))
			it->second->RemoveNeighbour(vertex);
	return true;
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::Print(shared_ptr<Vertex<TTag, TItem>> vertex)
{
	ostringstream oss;
	string uni = "-->";
	string multi = "<-->";
	vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
	oss << vertex->GetTag() << "(" << vertex->GetItem() << ") ";
	cout << oss.str();
	if (neighbours.empty())
		cout << endl;
	shared_ptr<Vertex<TTag, TItem>> previous = vertex;
	bool space = false;
	for (vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); *it++, space = true) {
		if (space)
			cout << setw(oss.str().size()) << " " << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << " " << (*it)->GetTag() << "(" << (*it)->GetItem() << ") " << " [" << previous->GetCost(*it) << "] " << endl;
		else
			cout << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << " " << (*it)->GetTag() << "(" << (*it)->GetItem() << ") " << " [" << previous->GetCost(*it) << "] " << endl;
	}
}
// https://www.hackerrank.com/challenges/primsmstsub/problem
// https://en.wikipedia.org/wiki/Prim%27s_algorithm
// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
// 2 cases with 1000 vertices and 10,000 edges failed
template<typename TTag, typename TItem>
size_t Graph<TTag, TItem>::PrimMinimumSpanningTree(shared_ptr<Vertex<TTag, TItem>> start)
{
	// Create a priority queue to store vertices that are part of MST (Minimum Spanning Tree).
	multimap<size_t, shared_ptr<Vertex<TTag, TItem>>> priorityQueue;
	// Create a vector for keys and initialize all keys as infinite (INF) 
	map<TTag, long> keys;

	// To store parent array which in turn store MST 
	//vector<shared_ptr<Vertex<TTag, TItem>>> parents(vertices_.size(), nullptr);
	map<TTag, shared_ptr<Vertex<TTag, TItem>>> parents;

	// To keep track of vertices included in MST 
	map<TTag, bool> inMST;

	// Insert source itself in priority queue and initialize its key as 0. 
	priorityQueue.emplace(0, start);
	keys.emplace(start->GetTag(), 0);
	while (!priorityQueue.empty()) {
		pair<size_t, shared_ptr<Vertex<TTag, TItem>>> entry = *(priorityQueue.begin());
		shared_ptr<Vertex<TTag, TItem>> u = entry.second;
		priorityQueue.erase(entry.first);
		inMST[u->GetTag()] = true; // Include vertex in MST
		map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours = u->GetNeighboursWithCost();
		for (map<shared_ptr<Vertex<TTag, TItem>>, long>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
			//  If v is not in MST and weight of (u,v) is smaller than current key of v 
			if (!inMST[it->first->GetTag()] && (keys.find(it->first->GetTag()) == keys.end() || keys[it->first->GetTag()] > it->second))
			{
				// Updating key of v 
				keys[it->first->GetTag()] = it->second;
				priorityQueue.emplace(keys[it->first->GetTag()], it->first);
				//parents[it->first->GetTag()] = u;
				parents.emplace(it->first->GetTag(), u);
			}
		}
	}
	// Print edges of MST using parent array
	for (map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = parents.begin(); it != parents.end(); it++)
		cout << it->second->GetTag() << " - " << it->first << endl;
	size_t sum = accumulate(keys.begin(), keys.end(), 0, [](size_t value, const map<TTag, long>::value_type& p) { return value + p.second; });
	return sum;
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::Dijkstra(TTag source, set<shared_ptr<Vertex<TTag, TItem>>>& spt)// spt: Shortest Path Tree
{
	//set<shared_ptr<Vertex<TTag, TItem>>> spt; 
	set<shared_ptr<Vertex<TTag, TItem>>> vertices;
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(source);
	assert(vertex);
	for (map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices_.begin(); it != vertices_.end(); it++)
		it->second->ResetTotalCost();
	vertex->SetTotalCost(0);
	for (; vertex;) {
		spt.emplace(vertex);
		// Update dist value of the adjacent vertices of the picked vertex. 
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
			// Update dist[v] only if it:
			// (1) is not in sptSet
			// (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			// (3) and total weight of path from src to v through u is smaller than current value of dist[v]
			if (spt.find(*it) == spt.end() && vertex->GetTotalCost() + vertex->GetCost(*it) < (*it)->GetTotalCost())
				(*it)->SetTotalCost(vertex->GetTotalCost() + vertex->GetCost(*it));
			if (spt.find(*it) == spt.end())
				vertices.insert(*it);
		}
		vertex = nullptr;
		long min = numeric_limits<long>::max();
		for (set<shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices.begin(); it != vertices.end(); it++)
			if ((*it)->GetTotalCost() < min) {
				min = (*it)->GetTotalCost();
				vertex = *it;
			}
		if (vertex)
			vertices.erase(vertex);
	}
}
template<typename TTag, typename TItem>
long Graph<TTag, TItem>::Dijkstra(TTag src, TTag dest)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt; 
	set<shared_ptr<Vertex<TTag, TItem>>> vertices;
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(src);
	shared_ptr<Vertex<TTag, TItem>> destination = GetVertex(dest);
	assert(vertex);
	assert(destination);
	for (map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices_.begin(); it != vertices_.end(); it++)
		it->second->ResetTotalCost();
	vertex->SetTotalCost(0);
	for (; vertex && destination && vertex != destination;) {
		spt.emplace(vertex);
		// Update dist value of the adjacent vertices of the picked vertex. 
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
			// Update dist[v] only if it:
			// (1) is not in sptSet
			// (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			// (3) and total weight of path from src to v through u is smaller than current value of dist[v]
			if (spt.find(*it) == spt.end() && vertex->GetTotalCost() + vertex->GetCost(*it) < (*it)->GetTotalCost())
				(*it)->SetTotalCost(vertex->GetTotalCost() + vertex->GetCost(*it));
			if (spt.find(*it) == spt.end())
				vertices.insert(*it);
		}
		vertex = nullptr;
		long min = numeric_limits<long>::max();
		for (set<shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices.begin(); it != vertices.end(); it++)
			if ((*it)->GetTotalCost() < min) {
				min = (*it)->GetTotalCost();
				vertex = *it;
			}
		if (vertex)
			vertices.erase(vertex);
	}
	return vertex ? vertex->GetTotalCost() : -1;
}
// https://www.hackerrank.com/challenges/rust-murderer/problem
// 3/7 test cases failed :(
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::UnbeatenPath(TTag start, vector<size_t>& paths)
{
	for (TTag destination = 1; destination <= (TTag)vertices_.size(); destination++) {
		shared_ptr<Vertex<TTag, TItem>> v = GetVertex(start);
		if (destination == start)
			continue;
		size_t count = 0;
		for (TTag hop = start + 1; ; ) {
			if (!v->HasNeighbour(destination)) {
				count++;
				break;
			}
			if (!v->HasNeighbour(hop)) {
				count++;
				v = GetVertex(hop);
			}
			if (++hop > (TTag)vertices_.size())
				hop = 1;
			if (hop == destination) {
				if (!v->HasNeighbour(hop))
					count++;
				break;
			}
		}
		paths.push_back(count);
	}
}
template<typename TTag, typename TItem>
void Graph<TTag, TItem>::GetBFSNodes(map<size_t, vector<shared_ptr<Vertex<TTag, TItem>>>>& result, shared_ptr<Vertex<TTag, TItem>>& start)
{
	if (start) {
		unsigned long level = 0;
		vector<shared_ptr<Vertex<TTag, TItem>>> vertices;
		vertices.push_back(start);
		result.emplace(level, vertices);
		while (!vertices.empty()) {
			vertices.clear();
			for (vector<shared_ptr<Vertex<TTag, TItem>>>::const_iterator it = result[level].begin(); it != result[level].end(); it++) {
				if (*it) {
					vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = (*it)->GetNeighbours();
					if (level > 0) { // Don't insert the parents. This happens for UnDirected Graph
						for (vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it1 = neighbours.begin(); it1 != neighbours.end(); it1++) {
							bool isBackPointer = false;
							for (vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it2 = result[level - 1].begin(); it2 != result[level - 1].end(); it2++)
								if (*it2 == *it1) {
									isBackPointer = true;
									break;
								}
							if (!isBackPointer)
								vertices.push_back(*it1);
						}
					} else
						vertices.insert(vertices.end(), neighbours.begin(), neighbours.end());
				}
			}
			level++;
			if (!vertices.empty())
				result.emplace(level, vertices);
		}
	}
}
// https://www.hackerrank.com/challenges/jack-goes-to-rapture/problem
// Timeout! for test cases with 50000 nodes
template<typename TTag, typename TItem>
long Graph<TTag, TItem>::GetPathsCosts(set<shared_ptr<Vertex<TTag, TItem>>>& spt, shared_ptr<Vertex<TTag, TItem>> vertex, shared_ptr<Vertex<TTag, TItem>> destination)
{
	set<shared_ptr<Vertex<TTag, TItem>>> vertices;
	vertex->SetTotalCost(0);
	for (; vertex && destination && vertex != destination;) {
		spt.emplace(vertex);
		// Update dist value of the adjacent vertices of the picked vertex. 
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
			// Update dist[v] only if it:
			// (1) is not in sptSet
			// (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			// (3) and total weight of path from src to v through u is smaller than current value of dist[v]
			long cost = vertex->GetTotalCost();
			long cost1 = vertex->GetCost(*it);
			long nextHopCost = cost1 - cost;
			long newTotalCost = nextHopCost > 0 ? cost + nextHopCost : cost;
			if (spt.find(*it) == spt.end() && newTotalCost < (*it)->GetTotalCost())
				(*it)->SetTotalCost(newTotalCost);
			if (spt.find(*it) == spt.end())
				vertices.insert(*it);
		}
		vertex = nullptr;
		long min = numeric_limits<long>::max();
		for (set<shared_ptr<Vertex<TTag, TItem>>>::iterator it = vertices.begin(); it != vertices.end(); it++)
			if ((*it)->GetTotalCost() < min) {
				min = (*it)->GetTotalCost();
				vertex = *it;
			}
		if (vertex)
			vertices.erase(vertex);
	}
	if (vertex)
		spt.emplace(vertex);
	return vertex ? vertex->GetTotalCost() : -1;
}
template<typename TTag, typename TItem>
TItem Graph<TTag, TItem>::MinSubTreesDifference(shared_ptr<Vertex<TTag, TItem>> node)
{
	set<TTag> visited;
	return node ? node->MinSubGraphDifference(visited) : 0;
}