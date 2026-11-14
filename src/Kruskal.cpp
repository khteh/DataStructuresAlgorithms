#include "pch.h"
#include "Kruskal.h"
// Instantiations: TTag is the vertex type, TWeight the edge weight type
template KruskalResult<int, int> Kruskal(vector<int> const &, vector<int> const &, vector<int> const &);
template KruskalResult<int, long> Kruskal(vector<int> const &, vector<int> const &, vector<long> const &);
template KruskalResult<int, size_t> Kruskal(vector<int> const &, vector<int> const &, vector<size_t> const &);
template KruskalResult<int, double> Kruskal(vector<int> const &, vector<int> const &, vector<double> const &);
template KruskalResult<uint32_t, int> Kruskal(vector<uint32_t> const &, vector<uint32_t> const &, vector<int> const &);
template KruskalResult<uint32_t, long> Kruskal(vector<uint32_t> const &, vector<uint32_t> const &, vector<long> const &);
template KruskalResult<uint32_t, size_t> Kruskal(vector<uint32_t> const &, vector<uint32_t> const &, vector<size_t> const &);
template KruskalResult<uint32_t, double> Kruskal(vector<uint32_t> const &, vector<uint32_t> const &, vector<double> const &);
template KruskalResult<long, int> Kruskal(vector<long> const &, vector<long> const &, vector<int> const &);
template KruskalResult<long, long> Kruskal(vector<long> const &, vector<long> const &, vector<long> const &);
template KruskalResult<long, size_t> Kruskal(vector<long> const &, vector<long> const &, vector<size_t> const &);
template KruskalResult<long, double> Kruskal(vector<long> const &, vector<long> const &, vector<double> const &);
template KruskalResult<size_t, int> Kruskal(vector<size_t> const &, vector<size_t> const &, vector<int> const &);
template KruskalResult<size_t, long> Kruskal(vector<size_t> const &, vector<size_t> const &, vector<long> const &);
template KruskalResult<size_t, size_t> Kruskal(vector<size_t> const &, vector<size_t> const &, vector<size_t> const &);
template KruskalResult<size_t, double> Kruskal(vector<size_t> const &, vector<size_t> const &, vector<double> const &);
#ifdef __SIZEOF_INT128__
template KruskalResult<int, int128_t> Kruskal(vector<int> const &, vector<int> const &, vector<int128_t> const &);
template KruskalResult<uint32_t, int128_t> Kruskal(vector<uint32_t> const &, vector<uint32_t> const &, vector<int128_t> const &);
template KruskalResult<long, int128_t> Kruskal(vector<long> const &, vector<long> const &, vector<int128_t> const &);
template KruskalResult<size_t, int128_t> Kruskal(vector<size_t> const &, vector<size_t> const &, vector<int128_t> const &);
#endif

template <typename TTag, arithmetic_type TWeight>
KruskalResult<TTag, TWeight> Kruskal(vector<TTag> const &from, vector<TTag> const &to, vector<TWeight> const &weight)
{
	if (from.size() != to.size() || from.size() != weight.size())
	{
		ostringstream oss;
		oss << "from, to and weight must be the same length: " << from.size() << ", " << to.size() << " and " << weight.size();
		throw invalid_argument(oss.str());
	}
	// Sort the graph edges by weight. stable_sort keeps edges of equal weight in input order, with one allocation instead of one per edge as in a multiset.
	vector<Edge<TTag, TWeight>> edges;
	edges.reserve(weight.size());
	for (size_t i = 0; i < weight.size(); i++)
		edges.emplace_back(from[i], to[i], weight[i]);
	stable_sort(edges.begin(), edges.end());
	/*
	Create a forest (a set of trees) initially consisting of a separate single-vertex tree for each vertex in the input graph.
	*/
	DisJointSet<TTag> disjointSet(from); // Every vertex is a disjoint set
	disjointSet.MakeSet(to);
	set<TTag> vertices(from.begin(), from.end());
	vertices.insert(to.begin(), to.end());
	// The forest starts with one tree per vertex, and each edge taken merges two trees into one
	KruskalResult<TTag, TWeight> result{0, vertices.size(), {}};
	for (typename vector<Edge<TTag, TWeight>>::const_iterator it = edges.cbegin(); it != edges.cend() && result.trees > 1; it++) // 1 tree: complete, every other edge would close a cycle
		if (disjointSet.Find(it->node1) != disjointSet.Find(it->node2))															 // Test whether adding the edge to the current forest would create a cycle.
		{
			/*
			 * If the two ends have different roots, they’re in different trees. The edge joins them without closing a loop, so it’s added: sum += weight, and Union merges the two trees.
			 * If they have the same root, they’re already connected by cheaper edges. Adding this edge would close a cycle, so it’s skipped. A self-loop (node1 == node2) is always skipped.
			 */
			result.weight += it->weight;
			disjointSet.Union(it->node1, it->node2);
			result.edges.push_back(*it);
			result.trees--;
		}
	return result;
}