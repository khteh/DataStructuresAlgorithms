#include "pch.h"
#include "Graph.h"
template class Graph<int, int>;
template class FurthestNode<int, int>;
template class Graph<uint32_t, uint32_t>;
template class FurthestNode<uint32_t, uint32_t>;
template class Graph<long, long>;
template class FurthestNode<long, long>;
template class Graph<uint64_t, uint64_t>;
template class FurthestNode<uint64_t, uint64_t>;
#ifdef __SIZEOF_INT128__
template class Graph<uint128_t, uint128_t>;
template class FurthestNode<uint128_t, uint128_t>;
#endif
#if defined(_MSC_VER)
// The following are duplicates of int64_t on GNUC / GNUG
template class Graph<size_t, size_t>;
template class FurthestNode<size_t, size_t>;
#endif

template <typename TTag, typename TItem>
FurthestNode<TTag, TItem>::FurthestNode() : distance(0), vertex(nullptr) {}
template <typename TTag, typename TItem>
FurthestNode<TTag, TItem>::FurthestNode(shared_ptr<Vertex<TTag, TItem>> v, long d) : vertex(move(v)), distance(d) {}

template <typename TTag, typename TItem>
Graph<TTag, TItem>::Graph() : _totalCost(0)
{
}
template <typename TTag, typename TItem>
Graph<TTag, TItem>::Graph(vector<TItem> &data) : _totalCost(0)
{
	AddVertices(data);
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddVertices(vector<TItem> &data)
{
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
	_totalCost = 0;
	// Vertices hold shared_ptrs to each other (every undirected edge is a 2-cycle). Break those cycles first,
	// otherwise clearing the map only drops the graph's references and the vertices keep each other alive.
	for (auto &[tag, vertex] : _vertices)
		if (vertex)
			vertex->ClearNeighbours();
	_vertices.clear();
}
template <typename TTag, typename TItem>
size_t Graph<TTag, TItem>::Count() const
{
	return _vertices.size();
}
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::TotalCost() const
{
	return _totalCost;
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
	if (!_vertices.count(from->GetTag()))
		_vertices.emplace(from->GetTag(), from);
	if (!_vertices.count(to->GetTag()))
		_vertices.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
	_totalCost += cost;
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddDirectedEdge(TTag from, TTag to, long cost)
{
	if (!_vertices.count(from))
		_vertices.emplace(from, make_shared<Vertex<TTag, TItem>>(from, from));
	if (!_vertices.count(to))
		_vertices.emplace(to, make_shared<Vertex<TTag, TItem>>(to, to));
	_vertices[from]->AddNeighbour(_vertices[to], cost);
	_totalCost += cost;
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddUndirectedEdge(shared_ptr<Vertex<TTag, TItem>> from, shared_ptr<Vertex<TTag, TItem>> to, long cost)
{
	if (!_vertices.count(from->GetTag()))
		_vertices.emplace(from->GetTag(), from);
	if (!_vertices.count(to->GetTag()))
		_vertices.emplace(to->GetTag(), to);
	from->AddNeighbour(to, cost);
	to->AddNeighbour(from, cost);
	_totalCost += cost * 2;
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::AddUndirectedEdge(TTag from, TTag to, long cost)
{
	if (!_vertices.count(from))
		_vertices.emplace(from, make_shared<Vertex<TTag, TItem>>(from, from)); // Tag == Item. XXX This will have undesired behaviour if there are duplicate tag values in the graph OR funtions expect TItem but tag value is used here!
	if (!_vertices.count(to))
		_vertices.emplace(to, make_shared<Vertex<TTag, TItem>>(to, to)); // Tag == Item. XXX This will have undesired behaviour if there are duplicate tag values in the graph OR funtions expect TItem but tag value is used here!
	_vertices[from]->AddNeighbour(_vertices[to], cost);
	_vertices[to]->AddNeighbour(_vertices[from], cost);
	_totalCost += cost * 2;
}
template <typename TTag, typename TItem>
bool Graph<TTag, TItem>::HasVertex(TTag tag) const
{
	return _vertices.count(tag);
}
template <typename TTag, typename TItem>
shared_ptr<Vertex<TTag, TItem>> Graph<TTag, TItem>::GetVertex(TTag tag)
{
	return _vertices.count(tag) ? _vertices[tag] : nullptr;
}
template <typename TTag, typename TItem>
bool Graph<TTag, TItem>::Remove(TTag tag)
{
	shared_ptr<Vertex<TTag, TItem>> vertex;
	if (!_vertices.count(tag))
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
void Graph<TTag, TItem>::Print() const
{
	if (!_vertices.empty())
		Print(_vertices.begin()->second);
}

template <typename TTag, typename TItem>
void Graph<TTag, TItem>::Print(shared_ptr<Vertex<TTag, TItem>> vertex) const
{
	ostringstream oss;
	string uni = "-->";
	string multi = "<-->";
	if (!vertex)
		throw invalid_argument("Invalid vertex to start printing from!");
	vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
	oss << vertex->GetTag() << "(" << vertex->GetItem() << ") ";
	cout << oss.str();
	if (neighbours.empty())
		cout << endl;
	shared_ptr<Vertex<TTag, TItem>> previous = vertex;
	bool space = false;
	for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::const_iterator it = neighbours.begin(); it != neighbours.end(); it++, space = true)
		if (space)
			cout << setw(oss.str().size()) << " " << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << " " << (*it)->GetTag() << "(" << (*it)->GetItem() << ") "
				 << " [" << previous->GetCost(*it) << "] " << endl;
		else
			cout << ((*it)->HasNeighbour(previous->GetTag()) ? multi : uni) << " " << (*it)->GetTag() << "(" << (*it)->GetItem() << ") "
				 << " [" << previous->GetCost(*it) << "] " << endl;
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
			//  If v is not in MST and weight of (u,v) is smaller than current cost of v
			if (!inMST.count(v->first->GetTag()) && (!costs.count(v->first->GetTag()) || costs[v->first->GetTag()] > v->second)) // v->second is edge cost from u to v
			{
				// Updating cost of v
				costs[v->first->GetTag()] = v->second;
				priorityQueue.emplace(v->second, v->first);
				parents.emplace(v->first->GetTag(), u);
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
			/* v is (*it); u is vertex.
			 * Update cost[v] iff:
			 * (1) is not in spt set
			 * (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			 * (3) and total cost of path from src to v through u is smaller than current value of cost[v]
			 */
			if (!spt.count(*it))
			{
				long uCost = vertex->GetCost(*it);
				long vCost = costs.count(*it) ? costs[*it] : numeric_limits<long>::max();
				if (costs[vertex] + uCost < vCost)
				{
					costs[*it] = costs[vertex] + uCost;
					/*
					Every vertex in this graph is owned by _vertices, and neighbour lists hold the same shared_ptrs. So the entry in costsPQ and *it point to the same object, and you can compare the pointers directly:
					This is an identity check, which is cheaper and arguably more correct for Dijkstra. You want to remove that vertex’s stale queue entry, not any vertex that happens to have an equal tag and item. The rest of the function already works this way, since spt.count(*it) and costs[*it] are keyed on the shared_ptr itself.
					Use the value comparison only if you could have two distinct Vertex objects that should count as the same node. Note that *it1.second == **it requires Vertex::operator== to be callable on non-const operands, or better, declared as bool operator==(const Vertex&) const.
					*/
					erase_if(costsPQ, [it](const auto &it1)
							 { return it1.second == *it; });
					costsPQ.emplace(costs[*it] /* + heuristic value in A-Star algorithm */, *it);
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
			/* v is (*it); u is vertex.
			 * Update cost[v] iff:
			 * (1) is not in sptSet
			 * (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			 * (3) and total cost of path from src to v through u is smaller than current value of cost[v]
			 */
			if (!spt.count(*it))
			{
				long uCost = vertex->GetCost(*it);
				long vCost = costs.count(*it) ? costs[*it] : numeric_limits<long>::max();
				if (costs[vertex] + uCost < vCost)
				{
					costs[*it] = costs[vertex] + uCost;
					/*
					Every vertex in this graph is owned by _vertices, and neighbour lists hold the same shared_ptrs. So the entry in costsPQ and *it point to the same object, and you can compare the pointers directly:
					This is an identity check, which is cheaper and arguably more correct for Dijkstra. You want to remove that vertex’s stale queue entry, not any vertex that happens to have an equal tag and item. The rest of the function already works this way, since spt.count(*it) and costs[*it] are keyed on the shared_ptr itself.
					Use the value comparison only if you could have two distinct Vertex objects that should count as the same node. Note that *it1.second == **it requires Vertex::operator== to be callable on non-const operands, or better, declared as bool operator==(const Vertex&) const.
					*/
					erase_if(costsPQ, [it](const auto &it1)
							 { return it1.second == *it; });
					costsPQ.emplace(costs[*it] /* + heuristic value in A-Star algorithm */, *it);
				}
			}
	}
	return vertex && vertex == destination && costs.count(vertex) ? costs[vertex] : -1;
}
/*
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * 100%
 */
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::Dijkstra(TTag src, vector<long> &distances)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt; // spt: Shortest Path Tree
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(src);
	multimap<long, shared_ptr<Vertex<TTag, TItem>>> costsPQ; // Priority Queue with min cost at *begin()
	assert(vertex);
	map<shared_ptr<Vertex<TTag, TItem>>, long> costs;
	costs.emplace(vertex, 0);
	costsPQ.emplace(0, vertex);
	for (; !costsPQ.empty();)
	{
		vertex = costsPQ.begin()->second;
		costsPQ.erase(costsPQ.begin());
		spt.emplace(vertex);
		// Update cost of the adjacent vertices of the picked vertex.
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
			/* v is (*it); u is vertex.
			 * Update cost[v] only if it:
			 * (1) is not in sptSet
			 * (2) there is an edge from u to v (This is always true in this implementation since we get all the neighbours of the current vertex)
			 * (3) and total cost of path from src to v through u is smaller than current value of cost[v]
			 */
			if (!spt.count(*it))
			{
				long uCost = vertex->GetCost(*it);
				long vCost = costs.count(*it) ? costs[*it] : numeric_limits<long>::max();
				if (costs[vertex] + uCost < vCost)
				{
					costs[*it] = costs[vertex] + uCost;
					/*
					Every vertex in this graph is owned by _vertices, and neighbour lists hold the same shared_ptrs. So the entry in costsPQ and *it point to the same object, and you can compare the pointers directly:
					This is an identity check, which is cheaper and arguably more correct for Dijkstra. You want to remove that vertex’s stale queue entry, not any vertex that happens to have an equal tag and item. The rest of the function already works this way, since spt.count(*it) and costs[*it] are keyed on the shared_ptr itself.
					Use the value comparison only if you could have two distinct Vertex objects that should count as the same node. Note that *it1.second == **it requires Vertex::operator== to be callable on non-const operands, or better, declared as bool operator==(const Vertex&) const.
					*/
					erase_if(costsPQ, [it](const auto &it1)
							 { return it1.second == *it; });
					costsPQ.emplace(costs[*it] /* + heuristic value in A-Star algorithm */, *it);
				}
			}
	}
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = costs.begin(); it != costs.end(); it++)
		if (it->first->GetTag() != src)
		{
			if (_vertices.count(0))
				distances[it->first->GetTag() < src ? it->first->GetTag() : it->first->GetTag() - 1] = it->second;
			else
				distances[it->first->GetTag() < src ? it->first->GetTag() - 1 : it->first->GetTag() - 2] = it->second;
		}
}
/*
 * https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
Floyd–Warshall works on an undirected graph as long as all its edge weights are non-negative. The algorithm itself never asks whether the graph is directed.
It only sees a matrix where distances[u][v] is the cost of going from u to v. An undirected edge u – v with cost w is just two directed edges, u → v and v → u, both with cost w.
That’s exactly how the Wikipedia Dijkstra test builds its graph: every edge is added in both directions, {0, 1, 7}, {1, 0, 7}, ….
The result is a symmetric matrix, distances[i][j] == distances[j][i], which you can see in that test’s expected values.

The catch is negative weights. If an undirected edge u – v has cost w < 0, its two directions form the directed 2-cycle u → v → u with cost 2w < 0.
Floyd–Warshall then sees a negative cycle and marks everything around it as −∞. With the patched code, a single undirected edge of cost −1 makes FloydWarshallDistances return false.
So on undirected graphs:

Edge weights	Floyd–Warshall on an undirected graph
All ≥ 0			Correct. Results are symmetric.
Any < 0			Every negative edge counts as a negative cycle, so pairs that can reach it are −∞

Whether that −∞ is the “right” answer depends on what you mean by a path:

(1) If a path may reuse an edge (a walk), going back and forth over a negative edge really does lower the cost without limit, so −∞ is correct.
(2) If you want simple paths, which never reuse an edge or vertex, the problem is well defined but much harder. Floyd–Warshall, Bellman–Ford and Dijkstra can’t solve it. It needs matching-based methods, known as the T-join approach.

So it’s more accurate to say that Floyd–Warshall supports directed graphs with negative edges but no negative cycles, and undirected graphs with non-negative weights. Treating an undirected graph as edges in both directions, as the test does, is the standard approach.

 * distances[i][j]: the shortest distance from i to j.
 *   numeric_limits<long>::max(): no path from i to j.
 *   numeric_limits<long>::min(): no shortest path, because a path from i to j can pass through a negative cycle,
 *   and going round it again always gives a shorter path (-infinity). FloydWarshallPath then gives an empty path.
 * Returns false if the graph has a negative cycle. A vertex k is on one exactly when distances[k][k] < 0.
 */
template <typename TTag, typename TItem>
bool Graph<TTag, TItem>::FloydWarshallDistances(vector<vector<long>> &distances)
{
	constexpr long noPath = numeric_limits<long>::max(), minusInfinity = numeric_limits<long>::min();
	size_t vertices = _vertices.size();
	distances = vector<vector<long>>(vertices, vector<long>(vertices, noPath));																	 // 0-based index!
	_FloydWarshallPaths = vector<vector<shared_ptr<Vertex<TTag, TItem>>>>(vertices, vector<shared_ptr<Vertex<TTag, TItem>>>(vertices, nullptr)); // Holds the penultimate vertex on the path from u to Values(v1, v2, v3)
	TTag minTag = _vertices.begin()->first, maxTag = _vertices.rbegin()->first;
	for (typename map<TTag, shared_ptr<Vertex<TTag, TItem>>>::const_iterator it = _vertices.begin(); it != _vertices.end(); it++)
	{
		distances[it->first][it->first] = 0;
		_FloydWarshallPaths[it->first][it->first] = it->second;
		map<shared_ptr<Vertex<TTag, TItem>>, long> neighbours = it->second->GetNeighboursWithCost();
		for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::iterator v = neighbours.begin(); v != neighbours.end(); v++)
			if (v->second < distances[it->first][v->first->GetTag()]) // A self-loop costing >= 0 doesn't beat the distance 0 from a vertex to itself
			{
				distances[it->first][v->first->GetTag()] = v->second;
				_FloydWarshallPaths[it->first][v->first->GetTag()] = it->second; // [u][v] = u
			}
	}
	/*
	 * XXX: This and the input parameter format vector<vector<long>> &distances limit the data type of graph vertices' tags to numerical data types!
	 */
	for (TTag k = minTag; k <= maxTag; k++)
		for (TTag i = minTag; i <= maxTag; i++)
			for (TTag j = minTag; j <= maxTag; j++)
				if (distances[i][k] != noPath && distances[k][j] != noPath)
				{
					/*
					 * add_sat (C++26 <numeric>) stops at numeric_limits<long>::min() instead of overflowing. With a negative cycle,
					 * distances can roughly double on every pass of k, as two negative distances are added together, so plain + would
					 * overflow a long (undefined behaviour) in larger graphs.
					 */
					long through = add_sat(distances[i][k], distances[k][j]);
					if (distances[i][j] > through)
					{
						distances[i][j] = through;
						_FloydWarshallPaths[i][j] = _FloydWarshallPaths[k][j];
					}
				}
	/*
	 * A vertex k is on a negative cycle exactly when its distance to itself is negative: going round the cycle costs less than staying.
	 * Every pair (i, j) where i can reach k and k can reach j then has no shortest path. Mark it -infinity, with no path to rebuild,
	 * so that FloydWarshallPath gives an empty path instead of following the predecessors round the cycle forever.
	 * Pairs that can't reach a negative cycle keep their distances.
	 */
	bool negativeCycle = false;
	for (TTag k = minTag; k <= maxTag; k++)
		if (distances[k][k] < 0)
		{
			negativeCycle = true;
			for (TTag i = minTag; i <= maxTag; i++)
				for (TTag j = minTag; j <= maxTag; j++)
					if (distances[i][k] != noPath && distances[k][j] != noPath) // 1. i reaches k, and 2. k reaches j and k is in a negative loop.
					{
						/*
						2 conditions for the pair (i, j) to have no shortest path, meaning distances[i][j] is −∞:

						i can reach k: there is a path from i to some vertex k on the negative cycle.
						k can reach j: there is a path from that k to j.

						Only when both hold can a walk from i to j make a detour round the cycle as many times as it likes, lowering the cost by the same amount each time.
						If either one fails, the cycle can’t affect that pair, and distances[i][j] keeps its ordinary value, or noPath.
						*/
						distances[i][j] = minusInfinity;
						_FloydWarshallPaths[i][j] = nullptr;
					}
		}
	return !negativeCycle;
}
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::FloydWarshallPath(TTag start, TTag end, vector<TTag> &path)
{
	if (_vertices.count(start) && _vertices.count(end) && _FloydWarshallPaths[start][end])
	{
		shared_ptr<Vertex<TTag, TItem>> startV = _vertices[start], endV = _vertices[end];
		for (shared_ptr<Vertex<TTag, TItem>> n = endV; n && n != startV; n = _FloydWarshallPaths[start][n->GetTag()])
			path.insert(path.begin(), n->GetTag());
	}
}
/*
 * https://www.hackerrank.com/challenges/rust-murderer/problem
 * Fails with timeout for 3 test cases. The timeouts come from the containers.
 * What makes it slow
 *
 * 1. nodes.erase(nodes.begin()) is O(N) per pop. Erasing the first element of a vector shifts every remaining element down one place.
 *    Because the graph is sparse, the village-road graph is dense: from the source, almost every city is one village road away, so the queue quickly holds about 150,000 cities.
 *    Popping them one at a time from the front moves about N²/2 elements, roughly 10¹⁰ moves. This is the main cause.
 * 2. set and map everywhere. visited, nodes1, nodes2, costs and adjacency_list are all tree-based. Every lookup, insert and erase is O(log N) and allocates or frees a node.
 *    Since the cities are numbered 1 to N, a vector indexed by city does the same job in O(1) with no allocations.
 * 3. nodes1 = nodes2 copies a set, which means allocating a fresh copy of every node each time.
 */
template <typename TTag, typename TItem>
void Graph<TTag, TItem>::UnbeatenPathsDijkstra(TTag src, vector<long> &distances)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt, nodes1, nodes2;
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(src);
	vector<shared_ptr<Vertex<TTag, TItem>>> nodes;
	map<shared_ptr<Vertex<TTag, TItem>>, long> costs;
	assert(vertex);
	nodes.push_back(vertex);
	costs.emplace(vertex, 0);
	for (typename map<TTag, shared_ptr<Vertex<TTag, TItem>>>::const_iterator it = _vertices.begin(); it != _vertices.end(); it++)
		if (it->first != src)
			nodes1.emplace(it->second);
	for (; !nodes.empty();)
	{
		vertex = nodes.front();
		nodes.erase(nodes.begin());
		spt.emplace(vertex);
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours(); // Nodes directly connected to vertex by main roads. Therefore, they are NOT directly connect to vertex by unbeaten paths.
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
			/*
			 * nodes1 contains nodes that are directly connected to the current source by an unbeaten path (as they could not be reached by main roads)
			 * nodes2 contains nodes that are NOT directly connected by an unbeaten path to the current source.
			 */
			if (!spt.count(*it))
			{
				nodes1.erase(*it);
				nodes2.emplace(*it);
			}
		// Enqueue all the nodes in nodes1 and mark them as grey as we already know their distance from the source.
		for (typename set<shared_ptr<Vertex<TTag, TItem>>>::iterator it = nodes1.begin(); it != nodes1.end(); it++)
		{
			nodes.push_back(*it);
			spt.insert(*it);
			costs[*it] = costs[vertex] + 1;
		}
		nodes1.clear();
		swap(nodes1, nodes2); // nodes1 takes nodes2's contents; nodes2 gets nodes1's, which were just cleared
	}
	for (typename map<shared_ptr<Vertex<TTag, TItem>>, long>::const_iterator it = costs.begin(); it != costs.end(); it++)
		if (it->first->GetTag() != src)
		{
			if (_vertices.count(0))
				distances[it->first->GetTag() < src ? it->first->GetTag() : it->first->GetTag() - 1] = it->second;
			else
				distances[it->first->GetTag() < src ? it->first->GetTag() - 1 : it->first->GetTag() - 2] = it->second;
		}
}
/*
 * https://www.hackerrank.com/challenges/rust-murderer/problem
 * 100%
 * Note: The graph/map of the city is ensured to be a sparse graph.
 * A sparse graph is a graph in which the number of edges (E) is close to the number of vertices (V), or O(V),
 * which is significantly lower than the maximum possible number of edges.
 *
 * Cities: [1, N]: 1-based index
 * Roads: M
 *
 * BFS on the complement graph: village roads exist exactly where main roads don't.
 * Keep the cities not reached yet. From city u, every unreached city that is NOT a main-road
 * neighbour of u is one village road away. Each unreached city is either removed (at most n in total)
 * or kept because it is a main-road neighbour of u (at most 2M in total), so the BFS is O(N + M).
 *
 * 2M: It counts how many times a city can be kept in unvisited (the stillUnvisited.push_back(v) branch), over the whole BFS.
 * When the BFS processes city u, a city v stays in unvisited only if there’s a main road between u and v.
 * So every “keep” is tied to one specific main road, u–v, used while processing u.
 * Each main road can cause at most two keeps
 *
 * A main road u–v can only cause a keep when one of its two endpoints is being processed:
 * - while processing u, it can keep v
 * - while processing v, it can keep u
 *
 * Each city is processed once, since it’s popped from the queue only once. So each main road causes at most 2 keeps, one from each end. With m main roads, that’s at most 2m keeps in total.
 * Another way to say the same thing: while processing u, at most deg(u) cities can be kept, where deg(u) is the number of main roads at u. Adding up the degrees of all cities gives exactly 2m, because each road is counted once from each of its two ends. That’s the “handshake lemma”.
 * Example:
 * Cities 1–4, source 1, with main roads 1–2 and 2–3 (m = 2):
 * process 1: unvisited {2, 3, 4} → 2 kept (road 1–2), 3 and 4 reached
 * process 3: unvisited {2}       → 2 kept (road 2–3)
 * process 4: unvisited {2}       → 2 reached
 * That’s 2 keeps, within the limit of 2m = 4.
 *
 * O(M+N): The scan of unvisited happens once for every city processed, and unvisited can start with almost n cities.
 * A quick estimate would be n passes × n cities = O(n²). The previous answer shows why it’s much less: a city stays in unvisited for another pass only because of a main road,
 * and there are only 2m of those “reasons” in the whole run. Every other city is removed the first time it’s looked at, and a removed city is never looked at again.
 *
 * swap(unvisited, stillUnvisited) is O(1):
 * Because it doesn’t move any elements. It only swaps three pointers inside the two vector objects.
 * A vector doesn’t hold its elements itself. The elements live in a separate block of heap memory, and the vector object only stores where that block is:

vector object (24 bytes)              heap memory
┌──────────────────────┐
│ begin   ─────────────┼──────────►  [ e0 | e1 | e2 | ... | e(size-1) | spare ... ]
│ end     (begin+size) │
│ capacity end         │
└──────────────────────┘

 * swap(unvisited, stillUnvisited) calls vector’s member swap, which exchanges those three pointers between the two objects.
 * Each vector now points to the other one’s block. That’s the same small amount of work whether the vectors hold 2 elements or a million, so it’s O(1).
 *
 * The queue is a vector with a head index. Popping is just head++, so nothing is shifted.
 * neighbourOf marks u’s main-road neighbours by storing u in their slots. There’s no need to clear it between cities: a slot that holds a different city’s number simply doesn’t count as a neighbour of u.
 * unvisited / stillUnvisited play the roles of your nodes1 / nodes2. swap exchanges them in O(1) instead of copying.
 * No visited set is needed. A city leaves unvisited the moment it gets its distance, so it can’t be reached twice.
 * The loop stops as soon as unvisited is empty. With a dense village-road graph, that’s usually after the first few cities.
 *
 * If the graph is dense:
 * The formula stays O(n + m), but in a dense graph m is about n², so it becomes O(n²).
 * A graph with n cities can have at most n(n − 1)/2 roads. “Dense” means m is a constant fraction of that, for example half of all possible roads. Then:
 * O(n + m) = O(n + n²/4) = O(n²)
 *
 * Even for a dense graph, you can’t do better than O(n + m), because just reading the m roads already takes O(m). So the algorithm is optimal at any density.
 * A dense input is simply a big input: 4,000 cities at 99% density is almost 8 million roads.
 *
 * The cost does shift between the parts of the algorithm:
 *
 * Marking neighbours costs 2m in total, so it grows to O(n²).
 * Keeping cities in unvisited: with almost every pair connected by a main road, most cities are kept on each pass rather than removed. The 2m limit on keeps is now large, about n².
 * The BFS goes deeper. With few village roads, paths are longer: in the 99% case, the furthest city was 3 to 4 village roads away, compared with 2 for the sparse graphs.
 * Compared with building the village roads explicitly

 * The obvious alternative is to build the village-road graph, the complement, and run an ordinary BFS on it. Building the complement means checking all n(n − 1)/2 pairs of cities, which is O(n²) whatever m is:

 * Main-road graph	This algorithm	Build the complement, then BFS
 * Sparse (m ≈ n)	O(n)			O(n²)
 * Dense (m ≈ n²)	O(n²)			O(n²)
 */
template <typename TTag, typename TItem>
vector<long> Graph<TTag, TItem>::UnbeatenPaths(size_t n, vector<vector<size_t>> &roads, size_t source)
{
	// Main roads, as an adjacency list indexed by city (1-based)
	vector<vector<size_t>> adjacency(n + 1);
	for (vector<size_t> const &road : roads)
	{
		adjacency[road[0]].push_back(road[1]);
		adjacency[road[1]].push_back(road[0]);
	}
	vector<long> distances(n + 1, -1);
	distances[source] = 0;
	vector<size_t> unvisited, stillUnvisited; // Cities not reached yet
	unvisited.reserve(n);
	for (size_t city = 1; city <= n; city++)
		if (city != source)
			unvisited.push_back(city);
	vector<size_t> neighbourOf(n + 1, 0); // neighbourOf[v] == u: v is a main-road neighbour of u
	vector<size_t> queue{source};		  // BFS queue: a vector with a read index, so popping is O(1)
	queue.reserve(n);
	for (size_t head = 0; head < queue.size() && !unvisited.empty(); head++)
	{
		size_t u = queue[head];
		for (size_t v : adjacency[u])
			neighbourOf[v] = u; // O(2*M) in sparse graph. O(M^2) in dense graph.
		stillUnvisited.clear();
		for (size_t v : unvisited)
			if (neighbourOf[v] == u)
				stillUnvisited.push_back(v); // Main road: no village road u - v, try again from a later city
			else
			{
				distances[v] = distances[u] + 1; // Village road u - v
				queue.push_back(v);
			}
		swap(unvisited, stillUnvisited);
	}
	vector<long> result;
	result.reserve(n - 1);
	for (size_t city = 1; city <= n; city++)
		if (city != source)
			result.push_back(distances[city]);
	return result;
}

template <typename TTag, typename TItem>
FurthestNode<TTag, TItem> Graph<TTag, TItem>::Diameter(TTag src)
{
	set<shared_ptr<Vertex<TTag, TItem>>> spt; // spt: Shortest Path Tree
	shared_ptr<Vertex<TTag, TItem>> vertex = GetVertex(src);
	map<shared_ptr<Vertex<TTag, TItem>>, long> costs;
	assert(vertex);
	costs.emplace(vertex, 0);
	FurthestNode<TTag, TItem> result(vertex, 0);
	for (; !costs.empty();)
	{
		long distance = costs.begin()->second;
		vertex = costs.begin()->first;
		costs.erase(costs.begin());
		spt.emplace(vertex);
		vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = vertex->GetNeighbours();
		for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
			if (!spt.count(*it))
			{
				long d = distance + vertex->GetCost(*it);
				costs.emplace(*it, d);
				if (d > result.distance)
				{
					result.distance = d;
					result.vertex = *it;
				}
			}
	}
	return result;
}
/*
Get the longest distance from src to anywhere in the tree using DFS.
This only works for the requirement N cities and N-1 roads. It will NOT work if there is a circle/loop of nodes!
*/
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::Diameter()
{
	FurthestNode<TTag, TItem> result;
	if (!_vertices.empty())
	{
		result = Diameter(_vertices.begin()->second->GetTag());
		result = Diameter(result.vertex->GetTag());
	}
	return result.distance;
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
			result.push_back(!distances.count(i) ? -1 : distances[i]);
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
				if (*parent && !visited.count(*parent))
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
			if (!spt.count(*it))
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
		throw invalid_argument("from, to and weight data point counts must match!");
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
	return GetVertex(root)->MinSubGraphsDifference(root, GetSubGraphSum(root));
}
/*
Prune tree of leaf nodes which are in nodes input parameter.
Return the total path costs pruned.
*/
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::Prune(set<TTag> const &nodes, set<TTag> &removed)
{
	long cost = 0;
	for (typename map<TTag, shared_ptr<Vertex<TTag, TItem>>>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
		if (!removed.count(it->first) && it->second->NeighbourCount() == 1 && nodes.count(it->second->GetTag()))
		{
			vector<shared_ptr<Vertex<TTag, TItem>>> leafs{it->second};
			size_t size = leafs.size();
			for (size_t i = 0; i < size; i++)
			{
				removed.emplace(leafs[i]->GetTag());
				vector<shared_ptr<Vertex<TTag, TItem>>> neighbours = leafs[i]->GetNeighbours();
				for (typename vector<shared_ptr<Vertex<TTag, TItem>>>::const_iterator neighbour = neighbours.begin(); neighbour != neighbours.end(); neighbour++)
					if ((*neighbour)->HasNeighbour(leafs[i]->GetTag()))
					{
						// Undirected graph
						cost += (*neighbour)->GetCost(leafs[i]) * 2;
						_totalCost -= (*neighbour)->GetCost(leafs[i]) * 2;
						(*neighbour)->RemoveNeighbour(leafs[i]);
						if ((*neighbour)->NeighbourCount() == 1 && nodes.count((*neighbour)->GetTag()))
						{
							leafs.push_back(*neighbour);
							size++;
						}
					}
					else
					{
						// Directed graph
						cost += (*neighbour)->GetCost(leafs[i]);
						_totalCost -= (*neighbour)->GetCost(leafs[i]);
					}
			}
		}
	for (typename set<TTag>::const_iterator it = removed.begin(); it != removed.end(); it++)
		_vertices.erase(*it);
	return cost;
}
/*
 * Given a binary tree with edge weights, remove all leaf nodes from the root. A cut can be made anywhere in the tree, removing the corresponding leaf/subtree.
 * The cost of removing all the leaf nodes is the sum of the weights of the edges being cut. Find the minimum total cost.
 *
	Value inside bracket denotes cost.
 *
 *			5
		  3(1)
		1(2) 4(3) -> Cut node 3: cost = 1
	 6(4)   7(5)

*			 5
		   3(3)
		1(1) 4(1) -> Cut nodes 1 and 2: cost = 2
	 6(2)


			0
	  1(1)
  2(2)      3(3)
	   4(4,5)		<- Node(4) is connected to both Node(2) and Node(3)

*/
template <typename TTag, typename TItem>
long Graph<TTag, TItem>::PruneMinCost(size_t root, vector<TTag> &from, vector<TTag> &to, vector<long> &weight)
{
	if (from.size() != to.size() || from.size() != weight.size())
		throw invalid_argument("from, to and weight data point counts must match!");
	for (size_t i = 0; i < from.size(); i++)
		AddDirectedEdge(from[i], to[i], weight[i]);
	shared_ptr<Vertex<TTag, TItem>> node = GetVertex(root);
	if (!node)
		throw invalid_argument("Root node not found in graph!");
	return node->GetMinPruneCost();
}