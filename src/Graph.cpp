#include "stdafx.h"
#include <string>
#include <set>
#include <iostream>
#include <limits>
#include "Graph.h"
template class Graph<long, long>;
template class Graph<size_t, size_t>;
template <typename TTag, typename TItem>
Graph<TTag, TItem>::Graph()
{
}
template <typename TTag, typename TItem>
Graph<TTag, TItem>::Graph(vector<TItem> &data)
{
	AddVertices(data);
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddVertices(vector<TItem> &data)
{
	// for (typename vector<TItem>::iterator it = data.begin(); it != data.end(); it++)
	for (size_t i = 0; i < data.size(); i++)
		AddVertex(i, data[i]); // Use index as Tag in case there are duplicate values in data
}
template <typename TTag, typename TItem>
Graph<TTag, TItem>::~Graph()
{
	Clear();
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::Clear()
{
	_vertices.clear();
}
template <typename TTag, typename TItem>
size_t Graph<TTag, TItem>::Count() const
{
	return _vertices.size();
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddVertex(shared_ptr<Vertex<TTag, TItem>> v)
{
	_vertices.emplace(v->GetTag(), v);
}
template <typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::AddVertex(TTag tag)
{
	_vertices.emplace(tag, make_shared<Vertex<TTag, TItem>>(tag));
	return _vertices[tag];
}
template <typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::AddVertex(TTag tag, TItem item)
{
	_vertices.emplace(tag, make_shared<Vertex<TTag, TItem>>(tag, item));
	return _vertices[tag];
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddDirectedEdge(shared_ptr<Vertex<TTag, TItem>> from, shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (_vertices.find(from->GetTag()) == _vertices.end())
		_vertices.emplace(from->GetTag(), from);
	if (_vertices.find(to->GetTag()) == _vertices.end())
		_vertices.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddDirectedEdge(TTag from, TTag to, long cost)
{
	if (_vertices.find(from) == _vertices.end())
		_vertices.emplace(from, make_shared<Vertex<TTag, TItem>>(from, from));
	if (_vertices.find(to) == _vertices.end())
		_vertices.emplace(to, make_shared<Vertex<TTag, TItem>>(to, to));
	_vertices[from]->AddNeighbour(_vertices[to], cost);
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddUndirectedEdge(shared_ptr<Vertex<TTag, TItem>> from, shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (_vertices.find(from->GetTag()) == _vertices.end())
		_vertices.emplace(from->GetTag(), from);
	if (_vertices.find(to->GetTag()) == _vertices.end())
		_vertices.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
	to->AddNeighbour(from, cost);
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddUndirectedEdge(TTag from, TTag to, long cost)
{
	if (_vertices.find(from) == _vertices.end())
		_vertices.emplace(from, make_shared<Vertex<TTag, TItem>>(from, from)); // Tag == Item
	if (_vertices.find(to) == _vertices.end())
		_vertices.emplace(to, make_shared<Vertex<TTag, TItem>>(to, to)); // Tag == Item
	_vertices[from]->AddNeighbour(_vertices[to], cost);
	_vertices[to]->AddNeighbour(_vertices[from], cost);
}

template <typename TTag, typename TItem>
bool Graph<TTag, TItem>::HasVertex(TTag tag) const
{
	return _vertices.find(tag) != _vertices.end();
}
template <typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::GetVertex(TTag tag)
{
	return _vertices.find(tag) != _vertices.end() ? _vertices[tag] : nullptr;
}
template <typename TTag, typename TItem>
bool Graph<TTag, TItem>::Remove(TTag tag)
{
	shared_ptr<Vertex<TTag, TItem>> vertex;
	if (_vertices.find(tag) == _vertices.end())
		return false;
	vertex = _vertices[tag];
	_vertices.erase(tag);
	for (typename map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
		if (it->second->HasNeighbour(tag))
			it->second->RemoveNeighbour(vertex);
	return true;
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::Print(TTag tag)
{
	if (HasVertex(tag))
		Print(GetVertex(tag));
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::Print(shared_ptr<Vertex<TTag, TItem>> vertex) const
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
	for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); *it++, space = true)
	{
		if (space)
			cout << setw(oss.str().size()) << " " << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << " " << (*it)->GetTag() << "(" << (*it)->GetItem() << ") "
				 << " [" << previous->GetCost(*it) << "] " << endl;
		else
			cout << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << " " << (*it)->GetTag() << "(" << (*it)->GetItem() << ") "
				 << " [" << previous->GetCost(*it) << "] " << endl;
	}
}
/* https://www.hackerrank.com/challenges/primsmstsub/problem
   https://en.wikipedia.org/wiki/Prim%27s_algorithm
   https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
   https://stackoverflow.com/questions/1195872/when-should-i-use-kruskal-as-opposed-to-prim-and-vice-versa
   Use Prim's algorithm when you have a graph with lots of edges, i.e., if the number of edges to vertices is high.
   Prim's algorithm is significantly faster in the limit when you've got a really dense graph with many more edges than vertices.
   100%
*/
template <typename TTag, typename TItem>
size_t Graph<TTag, TItem>::PrimMinimumSpanningTree(shared_ptr<Vertex<TTag, TItem>> start)
{
	// Create a priority queue to store vertices that are part of MST (Minimum Spanning Tree).
	multimap<long, shared_ptr<Vertex<TTag, TItem>>> priorityQueue; // key: cost. Vertices to be processed
	// Create a vector for keys and initialize all keys as infinite (INF)
	map<TTag, long> costs;

	// To store parent array which in turn store MST. Key: v, Value: u
	map<TTag, shared_ptr<Vertex<TTag, TItem>>> parents;

	// To keep track of vertices included in MST
	set<TTag> inMST; // Assumption: Every vertex has a unique tag

	// Insert source itself in priority queue and initialize its cost as 0.
	priorityQueue.emplace(0, start);
	costs.emplace(start->GetTag(), 0);
	while (!priorityQueue.empty())
	{
		typename multimap<long, shared_ptr<Vertex<TTag, TItem>>>::iterator vertex = priorityQueue.begin();
		shared_ptr<Vertex<TTag, TItem>> u = vertex->second;
		priorityQueue.erase(vertex);
		inMST.emplace(u->GetTag()); // Include vertex in MST
		map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours = u->GetNeighboursWithCost();
		for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::iterator v = neighbours.begin(); v != neighbours.end(); v++)
		{
			//  If v is not in MST and weight of (u,v) is smaller than current cost of v
			if (inMST.find(v->first->GetTag()) == inMST.end() && (costs.find(v->first->GetTag()) == costs.end() || costs[v->first->GetTag()] > v->second)) // v->second is edge cost from u to v
			{
				// Updating cost of v
				costs[v->first->GetTag()] = v->second;
				priorityQueue.emplace(v->second, v->first);
				parents.emplace(v->first->GetTag(), u);
			}
		}
	}
	// Print edges of MST using parent array
	cout << __FUNCTION__ << " edges of Minimum Spanning Tree: " << endl;
	for (typename map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = parents.begin(); it != parents.end(); it++)
		cout << it->second->GetTag() << " -> " << it->first << endl;
	return accumulate(costs.begin(), costs.end(), 0, [](long value, const typename map<TTag, long>::value_type &p)
					  { return value + p.second; });
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::Dijkstra(TTag source, map<shared_ptr<Vertex<TTag, TItem>>, long> &costs)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt; // spt: Shortest Path Tree
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(source);
	multimap<long, shared_ptr<Vertex<TTag, TItem>>> costsPQ; // Priority Queue with min cost at *begin()
	assert(vertex);
	costs.emplace(vertex, 0);
	costsPQ.emplace(0, vertex);
	for (; !costsPQ.empty();)
	{
		vertex = costsPQ.begin()->second;
		costsPQ.erase(costsPQ.begin());
		spt.emplace(vertex);
		// Update dist value of the adjacent vertices of the picked vertex.
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			/* v is (*it); u is vertex.
			 * Update cost[v] only if it:
			 * (1) is not in sptSet
			 * (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			 * (3) and total cost of path from src to v through u is smaller than current value of cost[v]
			 */
			if (spt.find(*it) == spt.end())
			{
				long uCost = vertex->GetCost(*it);
				long vCost = costs.find(*it) == costs.end() ? numeric_limits<long>::max() : costs[*it];
				if (costs[vertex] + uCost < vCost)
				{
					costs[*it] = costs[vertex] + uCost;
					erase_if(costsPQ, [it](const auto &it1)
							 { return it1.second->GetTag() == (*it)->GetTag() && it1.second->GetItem() == (*it)->GetItem(); });
					costsPQ.emplace(costs[vertex] + uCost, *it);
				}
			}
		}
	}
}
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::Dijkstra(TTag src, TTag dest)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt; // spt: Shortest Path Tree
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(src);
	shared_ptr<Vertex<TTag, TItem>> destination = GetVertex(dest);
	multimap<long, shared_ptr<Vertex<TTag, TItem>>> costsPQ; // Priority Queue with min cost at *begin()
	assert(vertex);
	assert(destination);
	map<shared_ptr<Vertex<TTag, TItem>>, long> costs;
	costs.emplace(vertex, 0);
	costsPQ.emplace(0, vertex);
	for (; !costsPQ.empty() && vertex != destination;)
	{
		vertex = costsPQ.begin()->second;
		costsPQ.erase(costsPQ.begin());
		spt.emplace(vertex);
		// Update cost of the adjacent vertices of the picked vertex.
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			/* v is (*it); u is vertex.
			 * Update cost[v] only if it:
			 * (1) is not in sptSet
			 * (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			 * (3) and total cost of path from src to v through u is smaller than current value of cost[v]
			 */
			if (spt.find(*it) == spt.end())
			{
				long uCost = vertex->GetCost(*it);
				long vCost = costs.find(*it) == costs.end() ? numeric_limits<long>::max() : costs[*it];
				if (costs[vertex] + uCost < vCost)
				{
					costs[*it] = costs[vertex] + uCost;
					erase_if(costsPQ, [it](const auto &it1)
							 { return it1.second->GetTag() == (*it)->GetTag() && it1.second->GetItem() == (*it)->GetItem(); });
					costsPQ.emplace(costs[vertex] + uCost, *it);
				}
			}
		}
	}
	return vertex && vertex == destination && costs.find(vertex) != costs.end() ? costs[vertex] : -1;
}
/*
 * https://www.hackerrank.com/challenges/bfsshortreach
 * 100%
 */
template <typename TTag, typename TItem>
vector<long> Graph<TTag, TItem>::BFSShortestPaths(size_t nodecount, vector<vector<TTag>> &edges, TTag s)
{
	for (typename vector<vector<TTag>>::iterator it = edges.begin(); it != edges.end(); it++)
		AddUndirectedEdge((*it)[0], (*it)[1], 6);
	// assert(Count() == nodecount); Some nodes are not coneected.
	map<size_t, vector<shared_ptr<Vertex<TTag, TItem>>>> vertices; // Get BFS vertices
	GetBFSNodes(vertices, _vertices[s]);
	assert(!vertices.empty());
	cout << "Graph content by level:" << endl;
	map<TTag, long> distances;
	for (typename map<size_t, vector<shared_ptr<Vertex<TTag, TItem>>>>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			cout << (*it1)->GetItem() << " ";
			distances.emplace((*it1)->GetItem(), (it->first) * 6);
			cout << " (distance: " << distances[(*it1)->GetItem()] << "), ";
		}
		cout << endl;
	}
	vector<long> result;
	for (size_t i = 1; i <= nodecount; i++)
		if (i != s)
			result.push_back(distances.find(i) == distances.end() ? -1 : distances[i]);
	return result;
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::GetBFSNodes(map<size_t, vector<shared_ptr<Vertex<TTag, TItem>>>> &result, shared_ptr<Vertex<TTag, TItem>> &start)
{
	if (start)
	{
		unsigned long level = 0;
		result.emplace(level, vector<shared_ptr<Vertex<TTag, TItem>>>{start});
		set<shared_ptr<Vertex<TTag, TItem>>> visited;
		for (; !result[level].empty(); level++)
		{
			vector<shared_ptr<Vertex<TTag, TItem>>> vertices;
			for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::const_iterator parent = result[level].begin(); parent != result[level].end(); parent++)
			{
				if (*parent && visited.find(*parent) == visited.end())
				{
					visited.emplace(*parent);
					vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = (*parent)->GetNeighbours();
					if (level > 0)
					{ // Don't insert the parents. This happens for UnDirected Graph
						for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator child = neighbours.begin(); child != neighbours.end(); child++)
						{
							bool isBackPointer = false;
							for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it2 = result[level - 1].begin(); it2 != result[level - 1].end(); it2++)
								if (*it2 == *child)
								{
									isBackPointer = true;
									break;
								}
							if (!isBackPointer)
								vertices.push_back(*child);
						}
					}
					else
						vertices.insert(vertices.end(), neighbours.begin(), neighbours.end());
				}
			}
			if (!vertices.empty())
				result.emplace(level + 1, vertices);
		}
	}
}
/* https://www.hackerrank.com/challenges/jack-goes-to-rapture/problem
 * 100%
 */
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::GetPathsCosts(shared_ptr<Vertex<TTag, TItem>> vertex, shared_ptr<Vertex<TTag, TItem>> destination)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt;
	multimap<long, shared_ptr<Vertex<TTag, TItem>>> vertices;
	vertex->SetTotalCost(0);
	for (; vertex && destination && vertex != destination;)
	{
		spt.emplace(vertex);
		// Update dist value of the adjacent vertices of the picked vertex.
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			if (spt.find(*it) == spt.end())
			{
				// Update dist[v] only if it:
				// (1) is not in sptSet
				// (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
				// (3) and total weight of path from src to v through u is smaller than current value of dist[v]
				// long cost = vertex->GetCost(*it);
				long cost = vertex->GetTotalCost();
				long cost1 = vertex->GetCost(*it);
				long nextHopCost = cost1 - cost;
				long newTotalCost = nextHopCost > 0 ? cost + nextHopCost : cost;
				if (newTotalCost < (*it)->GetTotalCost())
					(*it)->SetTotalCost(newTotalCost);
				vertices.emplace(newTotalCost, *it);
			}
		}
		vertex = vertices.empty() ? nullptr : vertices.begin()->second;
		if (!vertices.empty())
			vertices.erase(vertices.begin());
	}
	return vertex ? vertex->GetTotalCost() : -1;
}
/* https://www.hackerrank.com/challenges/jack-goes-to-rapture/problem
 * 100%
 */
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::GetLowestPathCost(size_t nodecount, vector<TTag> &from, vector<TTag> &to, vector<long> &weight)
{
	if (from.size() != to.size() || from.size() != weight.size())
		throw runtime_error("from, to and weight data point counts must match!");
	for (size_t i = 0; i < from.size(); i++)
		AddUndirectedEdge(from[i], to[i], weight[i]);
	assert(Count() == nodecount);
	return GetPathsCosts(_vertices[1], _vertices[nodecount]);
}
/*
 * https://www.hackerrank.com/challenges/even-tree/problem
 * 100%
 */
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::EvenForest(TTag root)
{
	ostringstream oss;
	set<string> cuts;
	vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = GetVertex(root)->GetNeighbours();
	for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
	{
		size_t descendents = (*it)->EvenForestDescendentsCount(root, cuts);
		if (!(descendents % 2))
		{
			oss.str("");
			oss << root << "-" << (*it)->GetTag();
			cuts.emplace(oss.str());
		}
	}
	return cuts.size();
}
template <typename TTag, typename TItem>
TItem Graph<TTag, TItem>::GetSubGraphSum(TTag root)
{
	return GetVertex(root)->GetSubGraphSum(root);
}
/* https://www.hackerrank.com/challenges/cut-the-tree/problem
			10
		11		5
	Diff: 15 - 11 = 4

			10
		 5		6
	  20
	Diff: 21 - 20 = 1

			10
		 5
	  20
	Diff: 20 - 15 = 5

		100(0)
			200(1)
		100(2)    100(4)
				500(3) 600(5)
* 100%
*/
template <typename TTag, typename TItem>
TItem Graph<TTag, TItem>::MinSubGraphsDifference(TTag root)
{
	TItem sum = GetSubGraphSum(root);
	return GetVertex(root)->MinSubGraphsDifference(root, sum);
}