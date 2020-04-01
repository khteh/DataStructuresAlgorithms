#pragma once
class Edge
{
public:
	long weight;
	long node1, node2;
	explicit Edge(long w, long n1, long n2);
	bool operator< (const Edge const&) const;
};