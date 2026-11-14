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
#ifdef __SIZEOF_INT128__
template class Edge<uint128_t, uint128_t>;
template class Edge<uint128_t, int128_t>;
template class Edge<size_t, uint128_t>;
template class Edge<size_t, int128_t>;
template class Edge<uint32_t, uint128_t>;
template class Edge<uint32_t, int128_t>;
#endif
template <typename TTag, arithmetic_type TItem>
Edge<TTag, TItem>::Edge(TTag n1, TTag n2, TItem w)
	: node1(n1), node2(n2), weight(w)
{
}
template <typename TTag, arithmetic_type TItem>
bool Edge<TTag, TItem>::operator<(const Edge &other) const
{
	return weight < other.weight;
}