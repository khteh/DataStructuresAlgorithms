#pragma once
#include <assert.h>
#include <iomanip>
#include <map>
#include <set>
#include <numeric>
#include <sstream>
#include "Vertex.h"
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
using namespace tbb;
#endif
template <typename T>
class DEdge;
template <typename T>
class DVertex
{
public:
    DVertex(T);
    DVertex(T, long);
    DVertex(shared_ptr<DVertex<T>>, long);
    void AddEdge(shared_ptr<DVertex<T>>, long);
    void UpdatePreviousVertex(shared_ptr<DVertex<T>>, long);
    void UpdateCost(long);
    bool operator<(const DVertex<T> &) const;
    bool operator==(DVertex<T> &);
    bool operator!=(DVertex<T> &);
    bool operator<(DVertex<T> &);
    bool operator>(DVertex<T> &);
    typedef typename set<DEdge<T>>::const_iterator IteratorType;
    shared_ptr<DVertex<T>> PreviousVertex() const;
    T Value() const;
    long Cost() const;
    IteratorType EdgeStart() const;
    IteratorType EdgeEnd() const;

private:
    T _value;
    set<DEdge<T>> _edges;
    shared_ptr<DVertex<T>> _previous;
    long _cost; // Accumulated cost up to this vertex
};
template <typename T>
class DEdge
{
public:
    DEdge(shared_ptr<DVertex<T>>, long);
    shared_ptr<DVertex<T>> NextVertex() const;
    long Cost() const;
    void UpdateCost(long);
    bool operator<(const DEdge<T> &) const;
    bool operator==(DEdge<T> &);
    bool operator!=(DEdge<T> &);
    bool operator<(DEdge<T> &);
    bool operator>(DEdge<T> &);

private:
    shared_ptr<DVertex<T>> _vertex;
    long _cost;
};
template <typename T>
class Dijkstra
{
public:
    Dijkstra();
    Dijkstra(vector<T> &);
    virtual ~Dijkstra();
    size_t Count() const;
    void Clear();
    void InitVertices();
    void AddVertices(vector<T> &);
    void AddVertex(T);
    void AddUndirectedEdge(T, T, long);
    long ShortestPath(T, T, vector<shared_ptr<DVertex<T>>> &);
    long ShortestPathStateless(T, T, vector<shared_ptr<DVertex<T>>> &);

private:
    map<T, shared_ptr<DVertex<T>>> _vertices;
    vector<shared_ptr<DVertex<T>>> _result;
};