#include "pch.h"
#include "Kruskal.h"
// Instantiations: TTag is the vertex type, TWeight the edge weight type
template class KruskalResult<int, int>;
template class KruskalResult<int, long>;
template class KruskalResult<int, size_t>;
template class KruskalResult<int, double>;
template class KruskalResult<uint32_t, int>;
template class KruskalResult<uint32_t, long>;
template class KruskalResult<uint32_t, size_t>;
template class KruskalResult<uint32_t, double>;
template class KruskalResult<long, int>;
template class KruskalResult<long, long>;
template class KruskalResult<long, size_t>;
template class KruskalResult<long, double>;
template class KruskalResult<size_t, int>;
template class KruskalResult<size_t, long>;
template class KruskalResult<size_t, size_t>;
template class KruskalResult<size_t, double>;

template class Kruskal<int, int>;
template class Kruskal<int, long>;
template class Kruskal<int, size_t>;
template class Kruskal<int, double>;
template class Kruskal<uint32_t, int>;
template class Kruskal<uint32_t, long>;
template class Kruskal<uint32_t, size_t>;
template class Kruskal<uint32_t, double>;
template class Kruskal<long, int>;
template class Kruskal<long, long>;
template class Kruskal<long, size_t>;
template class Kruskal<long, double>;
template class Kruskal<size_t, int>;
template class Kruskal<size_t, long>;
template class Kruskal<size_t, size_t>;
template class Kruskal<size_t, double>;

#ifdef __SIZEOF_INT128__
template class KruskalResult<int, int128_t>;
template class KruskalResult<uint32_t, int128_t>;
template class KruskalResult<long, int128_t>;
template class KruskalResult<size_t, int128_t>;

template class Kruskal<int, int128_t>;
template class Kruskal<uint32_t, int128_t>;
template class Kruskal<long, int128_t>;
template class Kruskal<size_t, int128_t>;
#endif
template <typename TTag, arithmetic_type TWeight>
Kruskal<TTag, TWeight>::Kruskal(vector<TTag> const &from, vector<TTag> const &to, vector<TWeight> const &weight)
{
	if (from.size() != to.size() || from.size() != weight.size())
	{
		ostringstream oss;
		oss << "from, to and weight must be the same length: " << from.size() << ", " << to.size() << " and " << weight.size();
		throw invalid_argument(oss.str());
	}
	// Sort the graph edges by weight. stable_sort keeps edges of equal weight in input order, with one allocation instead of one per edge as in a multiset.
	_edges.reserve(weight.size());
	for (size_t i = 0; i < weight.size(); i++)
		_edges.emplace_back(from[i], to[i], weight[i]);
	stable_sort(_edges.begin(), _edges.end());
	/*
	Create a forest (a set of trees) initially consisting of a separate single-vertex tree for each vertex in the input graph.
	*/
	_disjointSet.MakeSet(from); // Every vertex is a disjoint set
	_disjointSet.MakeSet(to);
	set<TTag> vertices(from.begin(), from.end());
	vertices.insert(to.begin(), to.end());
	_vertices = vertices.size();
}
template <typename TTag, arithmetic_type TWeight>
Kruskal<TTag, TWeight>::~Kruskal()
{
	Reset();
}
template <typename TTag, arithmetic_type TWeight>
void Kruskal<TTag, TWeight>::Reset()
{
	_edges.clear();
	_disjointSet.Reset();
	_vertices = 0;
}
template <typename TTag, arithmetic_type TWeight>
KruskalResult<TTag, TWeight> Kruskal<TTag, TWeight>::MST()
{
	// The forest starts with one tree per vertex, and each edge taken merges two trees into one
	KruskalResult<TTag, TWeight> result{0, _vertices, {}};
	for (typename vector<Edge<TTag, TWeight>>::const_iterator it = _edges.cbegin(); it != _edges.cend() && result.trees > 1; it++) // 1 tree: complete, every other edge would close a cycle
		if (_disjointSet.Find(it->node1) != _disjointSet.Find(it->node2))														   // Test whether adding the edge to the current forest would create a cycle.
		{
			/*
			 * If the two ends have different roots, they’re in different trees. The edge joins them without closing a loop, so it’s added: sum += weight, and Union merges the two trees.
			 * If they have the same root, they’re already connected by cheaper edges. Adding this edge would close a cycle, so it’s skipped. A self-loop (node1 == node2) is always skipped.
			 */
			result.weight += it->weight;
			_disjointSet.Union(it->node1, it->node2);
			result.edges.push_back(*it);
			result.trees--;
		}
	return result;
}