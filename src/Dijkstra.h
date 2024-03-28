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

template <typename TTag, typename TItem> // TTag is used as a unique ID. Graph vertices can have duplicate values of TItem
class Dijkstra
{
public:
    Dijkstra();
    Dijkstra(vector<TItem> &);
    virtual ~Dijkstra();
    size_t Count() const;
    void Clear();
    void AddVertices(vector<TItem> &);
    void AddVertex(TItem);
    long ShortestPath(TItem, TItem, vector<PreviousVertex<TTag, TItem>> &);

private:
    map<TItem, PreviousVertex<TTag, TItem>> _vertices;
};