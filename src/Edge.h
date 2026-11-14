#pragma once
#include "GenericConstraints.h"
template <typename TTag, arithmetic_type TItem>
class Edge
{
public:
	TTag node1, node2;
	TItem weight;
	explicit Edge(TTag, TTag n2, TItem);
	bool operator<(const Edge &) const;
};