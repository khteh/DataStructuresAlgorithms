#include "stdafx.h"
#include "Dijkstra.h"
#include <string>
#include <set>
#include <iostream>
#include <limits>
using namespace std;
namespace ranges = std::ranges;
#if defined(__GNUC__) || defined(__GNUG__)
using namespace tbb;
#endif
template class Dijkstra<long, long>;
template class Dijkstra<size_t, size_t>;

template <typename TTag, typename TItem>
Dijkstra<TTag, TItem>::Dijkstra()
{
}
template <typename TTag, typename TItem>
Dijkstra<TTag, TItem>::Dijkstra(vector<TItem> &data)
{
    AddVertices(data);
}
template <typename TTag, typename TItem>
void Dijkstra<TTag, TItem>::AddVertices(vector<TItem> &data)
{
    for (typename vector<TItem>::iterator it = data.begin(); it != data.end(); it++)
        AddVertex(*it); // tag = item
}
template <typename TTag, typename TItem>
void Dijkstra<TTag, TItem>::AddVertex(TItem v)
{
    _vertices.emplace(v, PreviousVertex<TTag, TItem>(nullptr, numeric_limits<long>::max()));
}
template <typename TTag, typename TItem>
Dijkstra<TTag, TItem>::~Dijkstra()
{
    Clear();
}
template <typename TTag, typename TItem>
void Dijkstra<TTag, TItem>::Clear()
{
    _vertices.clear();
}
template <typename TTag, typename TItem>
size_t Dijkstra<TTag, TItem>::Count() const
{
    return _vertices.size();
}
template <typename TTag, typename TItem>
long Dijkstra<TTag, TItem>::ShortestPath(TItem start, TItem end, vector<PreviousVertex<TTag, TItem>> &result)
{
    // Init the start node at 0 cost
    if (_vertices.find(start) == _vertices.end() || _vertices.find(end) == _vertices.end())
        return -1;
    _vertices[start].Previous = nullptr;
    _vertices[start].Cost = 0;
    map<TItem, long> costs;
    costs.emplace(start, 0);
    for (map<TItem, long>::iterator it = costs.begin(); it != costs.end(); it++)
    {
        TItem current = map
    }
    return 0;
}