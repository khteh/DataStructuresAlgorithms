#include "stdafx.h"
#include "Dijkstra.h"
template class DEdge<long>;
template class DEdge<size_t>;
template class DEdge<string>;
template class DVertex<long>;
template class DVertex<size_t>;
template class DVertex<string>;
template class Dijkstra<long>;
template class Dijkstra<size_t>;
template class Dijkstra<string>;

/*
 * Idea from https://andrewlock.net/implementing-dijkstras-algorithm-for-finding-the-shortest-path-between-two-nodes-using-priorityqueue-in-dotnet-9/
 */
////////////////////////////////// DVertex<T> //////////////////////////////////////////////////
template <typename T>
DVertex<T>::DVertex(T value) : _value(value), _cost(numeric_limits<long>::max()), _previous(nullptr)
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
    typename set<DEdge<T>>::const_iterator it = _edges.find(edge);
    if (it == _edges.end())
        _edges.emplace(edge);
    else if (it->Cost() > cost)
    {
        _edges.erase(it);
        _edges.emplace(edge);
    }
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
void DVertex<T>::UpdatePreviousVertex(shared_ptr<DVertex<T>> previous, long cost)
{
    _previous = previous;
    _cost = cost;
}
template <typename T>
void DVertex<T>::UpdateCost(long cost)
{
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
bool DEdge<T>::operator<(const DEdge<T> &rhs) const
{
    return _vertex < rhs._vertex;
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
    _vertices.emplace(v, make_shared<DVertex<T>>(v));
}
template <typename T>
void Dijkstra<T>::AddUndirectedEdge(T from, T to, long cost)
{
    if (!_vertices.count(from))
        AddVertex(from);
    if (!_vertices.count(to))
        AddVertex(to);
    _vertices[from]->AddEdge(_vertices[to], cost);
    _vertices[to]->AddEdge(_vertices[from], cost);
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
    // hops.clear();
}
template <typename T>
size_t Dijkstra<T>::Count() const
{
    return _vertices.size();
}
template <typename T>
void Dijkstra<T>::InitVertices()
{
    for (typename map<T, shared_ptr<DVertex<T>>>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
        (*it).second->UpdatePreviousVertex(nullptr, numeric_limits<int>::max());
}
template <typename T>
long Dijkstra<T>::ShortestPath(T start, T end, vector<shared_ptr<DVertex<T>>> &result)
{
    if (!_vertices.count(start) || !_vertices.count(end))
        return -1;
    InitVertices();
    set<shared_ptr<DVertex<T>>> visited;
    multimap<long, shared_ptr<DVertex<T>>> costs; // Priority Queue with min cost at *begin()
    _vertices[start]->UpdateCost(0);              // San Fran, null, 0
    costs.emplace(0, _vertices[start]);           // San Fran, 0
    for (; !costs.empty();)
    {
        shared_ptr<DVertex<T>> current = costs.begin()->second; // San Fran
        costs.erase(costs.begin());
        if (!visited.count(current))
        {
            visited.emplace(current);
            if (current->Value() == end)
            {
                result.insert(result.begin(), current);
                for (shared_ptr<DVertex<T>> n = current->PreviousVertex(); n; n = n->PreviousVertex())
                    result.insert(result.begin(), n);
                return current->Cost();
            }
            long currentCost = current->Cost();
            for (typename set<DEdge<T>>::const_iterator it = current->EdgeStart(); it != current->EdgeEnd(); it++)
            {
                // Current shortest distance to the connected node
                shared_ptr<DVertex<T>> nextVertex = it->NextVertex(); // L.A
                // Get current min cost to the connected vertex
                long cost = nextVertex->Cost(); // Default to Max
                // New accumulated cost to the next vertex
                long newCost = currentCost + it->Cost(); // 347
                if (newCost < cost)
                {
                    nextVertex->UpdatePreviousVertex(current, newCost);
                    // Update the costs queue of the next Vertex
                    erase_if(costs, [nextVertex](const auto &it1)
                             { return it1.second->Value() == nextVertex->Value(); });
                    costs.emplace(newCost, nextVertex);
                }
            }
        }
    }
    return -1;
}
template <typename T>
long Dijkstra<T>::ShortestPathStateless(T start, T end, vector<shared_ptr<DVertex<T>>> &result)
{
    if (!_vertices.count(start) || !_vertices.count(end))
        return -1;
    map<T, shared_ptr<DVertex<T>>> hops;
    // Initialize all the costs to max, and the "previous" vertex to null
    for (typename map<T, shared_ptr<DVertex<T>>>::iterator it = _vertices.begin(); it != _vertices.end(); it++)
        hops.emplace(it->first, make_shared<DVertex<T>>(it->first)); // Value is NOT important. Only the previous vertex pointer and MAX cost are important!
    set<shared_ptr<DVertex<T>>> visited;
    hops[start]->UpdateCost(0);                   // = DVertex<T>(nullptr, 0);
    multimap<long, shared_ptr<DVertex<T>>> costs; // Priority Queue with min cost at *begin()
    costs.emplace(0, _vertices[start]);           // San Fran, 0
    for (; !costs.empty();)
    {
        shared_ptr<DVertex<T>> current = costs.begin()->second; // San Fran
        costs.erase(costs.begin());
        if (!visited.count(current))
        {
            visited.emplace(current);
            if (current->Value() == end)
            {
                result.insert(result.begin(), current);
                for (shared_ptr<DVertex<T>> n = hops[end]->PreviousVertex(); n; n = n->PreviousVertex())
                    result.insert(result.begin(), n);
                return hops[end]->Cost();
            }
            long currentCost = hops[current->Value()]->Cost(); // 0
            for (typename set<DEdge<T>>::const_iterator it = current->EdgeStart(); it != current->EdgeEnd(); it++)
            {
                // Current shortest distance to the connected node
                shared_ptr<DVertex<T>> nextVertex = it->NextVertex(); // L.A
                // Get current min cost to the connected vertex
                long cost = hops[nextVertex->Value()]->Cost(); // MaxValue
                // New accumulated cost to the next vertex
                long newCost = currentCost + it->Cost(); // 347
                if (newCost < cost)
                {
                    hops[nextVertex->Value()]->UpdatePreviousVertex(current, newCost);
                    //  Update the costs queue of the next Vertex
                    erase_if(costs, [nextVertex](const auto &it1)
                             { return it1.second->Value() == nextVertex->Value(); });
                    costs.emplace(newCost, nextVertex);
                }
            }
        }
    }
    return -1;
}