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
template class DEdge<long>;
template class DEdge<size_t>;
template class DVertex<long>;
template class DVertex<size_t>;

////////////////////////////////// DVertex<T> //////////////////////////////////////////////////
template <typename T>
DVertex<T>::DVertex() : _cost(numeric_limits<long>::max()), _previous(nullptr)
{
}
template <typename T>
DVertex<T>::DVertex(T value, long cost) : _cost(cost), _previous(nullptr), _value(value)
{
}

template <typename T>
DVertex<T>::DVertex(shared_ptr<DVertex<T>> previous, long cost) : _cost(cost), _previous(previous)
{
}
template <typename T>
void DVertex<T>::AddEdge(shared_ptr<DVertex<T>> vertex, long cost)
{
    DEdge<T> edge(vertex, cost);
    if (_edges.find(edge) == _edges.end())
        _edges.emplace(edge);
}
template <typename T>
bool DVertex<T>::operator<(const DVertex<T> &other) const
{
    return _value < other._value;
}

template <typename T>
bool DVertex<T>::operator==(DVertex<T> &rhs)
{
    return _value == rhs._value;
}

template <typename T>
bool DVertex<T>::operator!=(DVertex<T> &rhs)
{
    return !(*this == rhs);
}

template <typename T>
bool DVertex<T>::operator<(DVertex<T> &rhs)
{
    return _value < rhs._value;
}

template <typename T>
bool DVertex<T>::operator>(DVertex<T> &rhs)
{
    return _value > rhs._value;
}
template <typename T>
typename set<DEdge<T>>::const_iterator DVertex<T>::EdgeStart() const
{
    return _edges.cbegin();
}
template <typename T>
typename set<DEdge<T>>::const_iterator DVertex<T>::EdgeEnd() const
{
    return _edges.cend();
}
template <typename T>
void DVertex<T>::UpdatePreviousVertex(DVertex<T> previous, long cost)
{
    _previous = make_shared<DVertex<T>>(previous);
    _cost = cost;
}
template <typename T>
shared_ptr<DVertex<T>> DVertex<T>::PreviousVertex() const
{
    return _previous;
}
template <typename T>
long DVertex<T>::Cost() const
{
    return _cost;
}
template <typename T>
T DVertex<T>::Value() const
{
    return _value;
}

////////////////////////////////// DEdge<T> //////////////////////////////////////////////////
template <typename T>
DEdge<T>::DEdge(shared_ptr<DVertex<T>> v, long cost) : _cost(cost), _vertex(v)
{
}
template <typename T>
long DEdge<T>::Cost() const
{
    return _cost;
}
template <typename T>
void DEdge<T>::UpdateCost(long cost)
{
    _cost = cost;
}
template <typename T>
shared_ptr<DVertex<T>> DEdge<T>::NextVertex() const
{
    return _vertex;
}
template <typename T>
bool DEdge<T>::operator<(const DEdge<T> &other) const
{
    return _vertex < other._vertex;
}

template <typename T>
bool DEdge<T>::operator==(DEdge<T> &rhs)
{
    return _vertex == rhs._vertex;
}

template <typename T>
bool DEdge<T>::operator!=(DEdge<T> &rhs)
{
    return !(*this == rhs);
}

template <typename T>
bool DEdge<T>::operator<(DEdge<T> &rhs)
{
    return _vertex < rhs._vertex;
}

template <typename T>
bool DEdge<T>::operator>(DEdge<T> &rhs)
{
    return _vertex > rhs._vertex;
}

////////////////////////////////// Dijkstra<T> //////////////////////////////////////////////////
template <typename T>
Dijkstra<T>::Dijkstra()
{
}
template <typename T>
Dijkstra<T>::Dijkstra(vector<T> &data)
{
    AddVertices(data);
}
template <typename T>
void Dijkstra<T>::AddVertices(vector<T> &data)
{
    for (typename vector<T>::iterator it = data.begin(); it != data.end(); it++)
        AddVertex(*it); // tag = item
}
template <typename T>
void Dijkstra<T>::AddVertex(T v)
{
    _vertices.emplace(v, DVertex<T>(v));
}
template <typename T>
void Dijkstra<T>::AddUndirectedEdge(T from, T to, long cost)
{
    if (_vertices.find(from) == _vertices.end())
        AddVertex(from);
    if (_vertices.find(to) == _vertices.end())
        AddVertex(to);
    _vertices[from].AddEdge(make_shared<DVertex<T>>(to), cost);
}
template <typename T>
Dijkstra<T>::~Dijkstra()
{
    Clear();
}
template <typename T>
void Dijkstra<T>::Clear()
{
    _vertices.clear();
    //_hops.clear();
}
template <typename T>
size_t Dijkstra<T>::Count() const
{
    return _vertices.size();
}
template <typename T>
long Dijkstra<T>::ShortestPath(T start, T end, vector<shared_ptr<DVertex<T>>> &result)
{
    if (_vertices.find(start) == _vertices.end() || _vertices.find(end) == _vertices.end())
        return -1;
    // Initialize all the costs to max, and the "previous" vertex to null
    // for (typename map<T, DVertex<T>>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
    //    _hops.emplace(it->second, DVertex<T>());
    set<shared_ptr<DVertex<T>>> visited;
    //_hops[DVertex<T>(start)] = DVertex<T>(nullptr, 0);
    multimap<long, shared_ptr<DVertex<T>>> costs; // Priority Queue wich min cost at *begin()
    costs.emplace(0, make_shared<DVertex<T>>(start, 0));
    for (; !costs.empty() && !end;)
    {
        typename multimap<long, shared_ptr<DVertex<T>>>::iterator currentIt = costs.begin();
        shared_ptr<DVertex<T>> current = currentIt->second;
        if (visited.find(current) == visited.end())
        {
            visited.empalce(current);
            if (current->Value() == end)
            {
                result.insert(result.begin(), current);
                for (shared_ptr<DVertex<T>> n = current->PreviousVertex(); n; n = n->PreviousVertex())
                    result.insert(result.begin(), n);
                break;
            }
            long currentCost = current->Cost(); //_hops[current->second].Cost;
            for (typename vector<DEdge<T>>::const_iterator it = current->EdgeStart(); it != current->EdgeEnd(); it++)
            {
                shared_ptr<DVertex<T>> nextVertex = it->NextVertex();
                // Get current min cost to the connected vertex
                long cost = nextVertex->Cost(); //_hops[it->NextVertex()].Cost;
                // New accumulated cost to the next vertex
                long newCost = currentCost + it->Cost();
                if (newCost < cost)
                {
                    //_hops[it->NextVertex()].UpdatePreviousVertex(current->second, newCost);
                    nextVertex->UpdatePreviousVertex(current, newCost);
                    // Update the costs queue of the next Vertex
                    typename multimap<long, shared_ptr<DVertex<T>>>::iterator it1 = ranges::find_if(costs, [nextVertex](const auto &it2)
                                                                                                    { return it2->second->Value() == nextVertex->Value(); }); // Look for element <= data[i]
                    if (it1 != costs.end())
                    {
                        costs.erase(it1);
                        costs.emplace(newCost, nextVertex);
                    }
                }
            }
        }
    }
    return 0;
}