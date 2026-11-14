#pragma once
#include "DisJointSet.h"
#include "Edge.h"
using namespace std;
/* https://www.hackerrank.com/challenges/kruskalmstrsub/problem
   https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
   https://stackoverflow.com/questions/1195872/when-should-i-use-kruskal-as-opposed-to-prim-and-vice-versa
   Kruskal can have better performance if the edges can be sorted in linear time, or are already sorted
   100%
Worked example: the first test case. The edges are 1–2 (5), 1–3 (3), 4–1 (6), 2–4 (7), 3–2 (4) and 3–4 (5), and the expected total is 12.
Edge (weight)	Trees before	Same root?	Action							Sum
1–3 (3)			{1} {2} {3} {4}	no			take, union						3
3–2 (4)			{1, 3} {2} {4}	no			take, union						7
1–2 (5)			{1, 2, 3} {4}	yes			skip: it would close 1–3–2–1	7
3–4 (5)			{1, 2, 3} {4}	no			take, union						12
4–1 (6)			{1, 2, 3, 4}	yes			skip							12
2–4 (7)			{1, 2, 3, 4}	yes			skip							12 ✓
*/
template <typename TTag, arithmetic_type TWeight>
struct KruskalResult
{
	TWeight weight;					  // Total weight of the minimum spanning tree, or of the minimum spanning forest
	size_t trees;					  // Connected parts: 1 means a spanning tree; more means a forest, one tree per part
	vector<Edge<TTag, TWeight>> edges; // The chosen edges, cheapest first: (vertices - trees) of them
	bool Connected() const { return trees <= 1; } // 0 trees: no vertices at all
};
/*
 * from[i] - to[i] is an undirected edge of weight weight[i]. The vertices are the ones the edges name.
 * TWeight is the caller's: signed, unsigned or floating point, deduced from weight.
 * Returns the minimum spanning tree: its total weight, the number of trees (1 if the edges connect every vertex;
 * otherwise a minimum spanning forest, one tree per connected part) and the chosen edges.
 * Throws invalid_argument if from, to and weight are not the same length.
 * Defined in Kruskal.cpp, which instantiates it for the common TTag and TWeight types. For any other, add a line there,
 * and an Edge<TTag, TWeight> line in Edge.cpp if it isn't listed already.
 */
template <typename TTag, arithmetic_type TWeight>
KruskalResult<TTag, TWeight> Kruskal(vector<TTag> const &, vector<TTag> const &, vector<TWeight> const &);
