#pragma once
#include "GenericConstraints.h"
template <typename TTag, arithmetic_type TWeight>
class Edge
{
public:
	TTag node1, node2;
	TWeight weight;
	explicit Edge(TTag, TTag n2, TWeight);
	bool operator<(const Edge &) const;
};