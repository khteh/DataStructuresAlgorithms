#include "stdafx.h"
#include "Graph.h"
#include <string>
#include <set>
#include <iostream>
using namespace std;
template class Graph<long>;
template<class T>
Graph<T>::Graph()
{
}
template<class T>
Graph<T>::Graph(vector<T>& data)
{
	for (vector<T>::iterator it = data.begin(); it != data.end(); it++)
		AddVertex(*it);
}
template<class T>
Graph<T>::~Graph()
{
	vertices_.clear();
}
template<class T>
size_t Graph<T>::Count()
{
	return vertices_.size();
}

template<class T>
void Graph<T>::AddVertex(shared_ptr<Vertex<T>> v)
{
	vertices_.emplace(v->GetTag(), v);
}
template<class T>
shared_ptr<Vertex<T>> Graph<T>::AddVertex(T tag)
{
	vertices_.emplace(tag, make_shared<Vertex<T>>(tag));
	return vertices_[tag];
}
template<class T>
void Graph<T>::AddDirectedEdge(shared_ptr<Vertex<T>> from, shared_ptr<Vertex<T>> to, long cost)
{
	if (vertices_.find(from->GetTag()) == vertices_.end())
		vertices_.emplace(from->GetTag(), from);
	if (vertices_.find(to->GetTag()) == vertices_.end())
		vertices_.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
}
template<class T>
void Graph<T>::AddUndirectedEdge(shared_ptr<Vertex<T>> from, shared_ptr<Vertex<T>> to, long cost)
{
	if (vertices_.find(from->GetTag()) == vertices_.end())
		vertices_.emplace(from->GetTag(), from);
	if (vertices_.find(to->GetTag()) == vertices_.end())
		vertices_.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
	to->AddNeighbour(from, cost);
}
template<class T>
bool Graph<T>::HasVertex(T tag)
{
	return vertices_.find(tag) != vertices_.end();
}
template<class T>
shared_ptr<Vertex<T>> Graph<T>::GetVertex(T tag)
{
	return vertices_.find(tag) != vertices_.end() ? vertices_[tag] : nullptr;
}
template<class T>
bool Graph<T>::Remove(T tag)
{
	shared_ptr<Vertex<T>> vertex;
	if (vertices_.find(tag) == vertices_.end())
		return false;
	vertex = vertices_[tag];
	vertices_.erase(tag);
	for (map<T, shared_ptr<Vertex<T>>>::iterator it = vertices_.begin(); it != vertices_.end(); it++)
		if (it->second->HasNeighbour(tag))
			it->second->RemoveNeighbour(vertex);
	return true;
}
template<class T>
void Graph<T>::Print(shared_ptr<Vertex<T>> vertex)
{
	string uni = "-->";
	string multi = "<-->";
	vector<shared_ptr<Vertex<T>>> neighbours = vertex->GetNeighbours();
	cout << vertex->GetTag();
	shared_ptr<Vertex<T>> previous = vertex;
	bool space = false;
	for (vector<shared_ptr<Vertex<T>>>::iterator it = neighbours.begin(); it != neighbours.end(); *it++, space = true)
		cout << (space ? " " : "") << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << (*it)->GetTag() << " [" << previous->GetCost(*it) << "] " << endl;
}
// https://www.hackerrank.com/challenges/primsmstsub/problem
// https://en.wikipedia.org/wiki/Prim%27s_algorithm
// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
// 2 cases with 1000 vertices and 10,000 edges failed
template<class T>
size_t Graph<T>::PrimMinimumSpanningTree(shared_ptr<Vertex<T>> start)
{
	// Create a priority queue to store vertices that are part of MST.
	multimap<size_t, shared_ptr<Vertex<T>>> priorityQueue;
	// Create a vector for keys and initialize all keys as infinite (INF) 
	map<T, T> keys;

	// To store parent array which in turn store MST 
	//vector<shared_ptr<Vertex<T>>> parents(vertices_.size(), nullptr);
	map<T, shared_ptr<Vertex<T>>> parents;

	// To keep track of vertices included in MST 
	map<T, bool> inMST;

	// Insert source itself in priority queue and initialize its key as 0. 
	priorityQueue.emplace(0, start);
	keys.emplace(start->GetTag(), 0);
	while (!priorityQueue.empty()) {
		pair<size_t, shared_ptr<Vertex<long>>> entry = *(priorityQueue.begin());
		shared_ptr<Vertex<long>> u = entry.second;
		priorityQueue.erase(entry.first);
		inMST[u->GetTag()] = true; // Include vertex in MST
		map<shared_ptr<Vertex<T>>, long> neighbours = u->GetNeighboursWithCost();
		for (map<shared_ptr<Vertex<T>>, long>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
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
	for (map<T, shared_ptr<Vertex<T>>>::iterator it = parents.begin(); it != parents.end(); it++)
		cout << it->second->GetTag() << " - " << it->first << endl;
	size_t sum = accumulate(keys.begin(), keys.end(), 0, [](size_t value, const map<T, T>::value_type& p) { return value + p.second; });
	return sum;
}
// https://www.hackerrank.com/challenges/rust-murderer/problem
// 3/7 test cases failed :(
template<class T>
void Graph<T>::UnbeatenPath(T start, vector<T>& paths)
{
	for (T destination = 1; destination <= vertices_.size(); destination++) {
		shared_ptr<Vertex<T>> v = GetVertex(start);
		if (destination == start)
			continue;
		size_t count = 0;
		for (T hop = start + 1; ; ) {
			if (!v->HasNeighbour(destination)) {
				count++;
				break;
			}
			if (!v->HasNeighbour(hop)) {
				count++;
				v = GetVertex(hop);
			}
			if (++hop > vertices_.size())
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