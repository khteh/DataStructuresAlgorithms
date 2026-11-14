#include "pch.h"
#include "Edge.h"
template class Edge<size_t, int32_t>;
template class Edge<size_t, int64_t>;
#if defined(_MSC_VER)
template class Edge<size_t, long>;
#endif
#ifdef __SIZEOF_INT128__
template class Edge<size_t, int128_t>;
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
