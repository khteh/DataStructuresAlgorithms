#pragma once
#include "Vertex.h"
using namespace std;
namespace ranges = std::ranges;
template <typename T>
class DEdge;
template <typename T>
class DVertex
{
private:
    T _value;
    set<DEdge<T>> _edges;
    weak_ptr<DVertex<T>> _previous;
    long _cost; // Accumulated cost up to this vertex
    void Swap(DVertex<T> &);

public:
    explicit DVertex(T);
    DVertex(const DVertex &);     // Copy constructor
    DVertex(DVertex &&) noexcept; // Move constructor
    DVertex(T, long);
    DVertex(weak_ptr<DVertex<T>>, long);
    void AddEdge(shared_ptr<DVertex<T>>, long);
    void ClearEdges(); // Break shared_ptr cycles between connected vertices
    void UpdatePreviousVertex(shared_ptr<DVertex<T>>, long);
    void UpdateCost(long);
    bool operator==(const DVertex<T> &) const; // const member, const param. it works for const and non-const objects alike
    // By value, as ==. !=, <, <=, > and >= are rewritten from == and <=>. The result type is T's: strong_ordering for integers and strings
    compare_three_way_result_t<T> operator<=>(const DVertex<T> &) const;
    typedef typename set<DEdge<T>>::const_iterator IteratorType;
    shared_ptr<DVertex<T>> PreviousVertex() const;
    T Value() const;
    long Cost() const;
    IteratorType EdgeStart() const;
    IteratorType EdgeEnd() const;
};
template <typename T>
class DEdge
{
private:
    shared_ptr<DVertex<T>> _vertex;
    long _cost;
    void Swap(DEdge<T> &);

public:
    DEdge(const DEdge &);     // Copy constructor
    DEdge(DEdge &&) noexcept; // Move constructor
    DEdge(shared_ptr<DVertex<T>>, long);
    shared_ptr<DVertex<T>> NextVertex() const;
    long Cost() const;
    void UpdateCost(long);
    // By the vertex pointer, as before. These replace a const operator< and non-const ==, !=, < and > that did the same
    bool operator==(const DEdge<T> &) const;
    strong_ordering operator<=>(const DEdge<T> &) const;
};
template <typename T>
class Dijkstra
{
public:
    Dijkstra();
    Dijkstra(vector<T> const &);
    virtual ~Dijkstra();
    size_t Count() const;
    void Clear();
    void InitVertices();
    void AddVertices(vector<T> const &);
    void AddVertex(T);
    void AddUndirectedEdge(T, T, long);
    long ShortestPath(T, T, vector<shared_ptr<DVertex<T>>> &);
    long ShortestPathStateless(T, T, vector<shared_ptr<DVertex<T>>> &);

private:
    map<T, shared_ptr<DVertex<T>>> _vertices;
    vector<shared_ptr<DVertex<T>>> _result;
};