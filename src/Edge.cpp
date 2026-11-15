#include "pch.h"
#include "Edge.h"
template class Edge<int, int>;
template class Edge<long, long>;
template class Edge<uint32_t, uint32_t>;
template class Edge<uint64_t, uint64_t>;
template class Edge<size_t, long>;
template class Edge<uint32_t, long>;
template class Edge<size_t, int32_t>;
#ifdef _MSC_VER
template class Edge<size_t, long>;
#endif
// The rest of the TTag and TWeight combinations Kruskal.cpp instantiates (the ones above cover the others)
template class Edge<int, long>;
template class Edge<int, size_t>;
template class Edge<int, double>;
template class Edge<uint32_t, int>;
template class Edge<uint32_t, size_t>;
template class Edge<uint32_t, double>;
template class Edge<long, int>;
template class Edge<long, size_t>;
template class Edge<long, double>;
template class Edge<size_t, double>;
#ifdef __SIZEOF_INT128__
template class Edge<uint128_t, uint128_t>;
template class Edge<uint128_t, int128_t>;
template class Edge<size_t, uint128_t>;
template class Edge<size_t, int128_t>;
template class Edge<uint32_t, uint128_t>;
template class Edge<uint32_t, int128_t>;
template class Edge<int, int128_t>;
template class Edge<long, int128_t>;
#endif
template <typename TTag, arithmetic_type TWeight>
Edge<TTag, TWeight>::Edge(TTag n1, TTag n2, TWeight w)
	: node1(n1), node2(n2), weight(w)
{
}
template <typename TTag, arithmetic_type TWeight>
bool Edge<TTag, TWeight>::operator<(const Edge &other) const
{
	return weight < other.weight;
}