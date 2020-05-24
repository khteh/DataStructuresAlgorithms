#include "stdafx.h"
#include "Edge.h"
Edge::Edge(long w, long n1, long n2) 
	: weight(w), node1(n1), node2(n2)
{
}
bool Edge::operator< (const Edge const& other) const
{
	return weight < other.weight;
}
