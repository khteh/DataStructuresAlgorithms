#include "pch.h"
using namespace std;
TEST(GraphTests, BredthFirstSearchTest)
{
	vector<size_t> data(5);
	ranges::generate(data, [n = 1]() mutable
					 { return n++; }); // Item values
	Graph<size_t, size_t> graph(data); // Tag values are indices
	ASSERT_EQ(data.size(), graph.Count());
	shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(0);
	ASSERT_TRUE(graph.HasVertex(0));
	ASSERT_TRUE(graph.HasVertex(1));
	ASSERT_TRUE(graph.HasVertex(2));
	ASSERT_TRUE(graph.HasVertex(3));
	ASSERT_TRUE(graph.HasVertex(4));

	ASSERT_FALSE(v1->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(1);
	ASSERT_FALSE(v2->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v3 = graph.GetVertex(2);
	ASSERT_FALSE(v3->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v4 = graph.GetVertex(3);
	ASSERT_FALSE(v4->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v5 = graph.GetVertex(4);
	ASSERT_FALSE(v5->HasNeighbours());
	ASSERT_EQ(0, v1->GetCost(v1));
	ASSERT_EQ(0, v2->GetCost(v2));
	ASSERT_EQ(0, v3->GetCost(v3));
	ASSERT_EQ(0, v4->GetCost(v4));
	graph.AddUndirectedEdge(v1, v2, 1); // 1->2 (1)
	ASSERT_TRUE(v1->HasNeighbour(v2));
	ASSERT_EQ(1, v1->GetCost(v2));
	ASSERT_TRUE(v2->HasNeighbour(v1));
	ASSERT_EQ(1, v2->GetCost(v1));
	graph.AddUndirectedEdge(v2, v3, 2); // 2->3 (2)
	ASSERT_TRUE(v2->HasNeighbour(v3));
	ASSERT_EQ(2, v2->GetCost(v3));
	ASSERT_TRUE(v3->HasNeighbour(v2));
	ASSERT_EQ(2, v3->GetCost(v2));
	graph.AddUndirectedEdge(v2, v4, 3); // 2->4 (3)
	ASSERT_TRUE(v2->HasNeighbour(v4));
	ASSERT_EQ(3, v2->GetCost(v4));
	ASSERT_TRUE(v4->HasNeighbour(v2));
	ASSERT_EQ(3, v4->GetCost(v2));
	graph.AddUndirectedEdge(v3, v5, 4); // 3->5 (4)
	ASSERT_TRUE(v3->HasNeighbour(v5));
	ASSERT_EQ(4, v3->GetCost(v5));
	ASSERT_TRUE(v5->HasNeighbour(v3));
	ASSERT_EQ(4, v5->GetCost(v3));
	graph.AddUndirectedEdge(v4, v5, 5); // 4->5 (5)
	ASSERT_TRUE(v4->HasNeighbour(v5));
	ASSERT_EQ(5, v4->GetCost(v5));
	ASSERT_TRUE(v5->HasNeighbour(v4));
	ASSERT_EQ(5, v5->GetCost(v4));
	graph.Print(v1);
	graph.Print(v2);
	graph.Print(v3);
	graph.Print(v4);
	map<size_t, vector<shared_ptr<Vertex<size_t, size_t>>>> vertices; // Get BFS vertices
	graph.GetBFSNodes(vertices, v1);
	ASSERT_FALSE(vertices.empty());
	ASSERT_EQ(graph.Count(), vertices.size());
	cout << "Graph content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Vertex<size_t, size_t>>>>::const_iterator it = vertices.begin(); it != vertices.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Vertex<size_t, size_t>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			cout << (*it1)->GetItem() << " ";
			if ((*it1)->HasNeighbours())
			{
				vector<shared_ptr<Vertex<size_t, size_t>>> neighbours = (*it1)->GetNeighbours();
				cout << "[";
				for (vector<shared_ptr<Vertex<size_t, size_t>>>::iterator it1 = neighbours.begin(); it1 != neighbours.end(); it1++)
					cout << (*it1)->GetItem() << ",";
				cout << "] ";
			}
		}
		cout << endl;
	}
}
class BFSShortestPathsTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<vector<size_t>>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_vertices = get<1>(GetParam());
		_edges = get<2>(GetParam());
		_start = get<3>(GetParam());
	}
	vector<long> BFSShortestPathsTest()
	{
		_graph.Clear();
		return _graph.BFSShortestPaths(_vertices, _edges, _start);
	}

protected:
	Graph<size_t, size_t> _graph;
	vector<long> _expected;
	vector<vector<size_t>> _edges;
	size_t _vertices, _start;
};
TEST_P(BFSShortestPathsTestFixture, BFSShortestPathsTests)
{
	ASSERT_EQ(this->_expected, this->BFSShortestPathsTest());
}
INSTANTIATE_TEST_SUITE_P(
	BFSShortestPathsTests,
	BFSShortestPathsTestFixture,
	::testing::Values(make_tuple(vector<long>{6, 6, 12, -1}, 5, vector<vector<size_t>>{{1, 2}, {1, 3}, {3, 4}}, 1),
					  make_tuple(vector<long>{6, 6, 6, -1}, 5, vector<vector<size_t>>{{1, 2}, {1, 3}, {3, 4}, {1, 4}}, 1),
					  make_tuple(
						  vector<long>{6, 6, -1}, 4, vector<vector<size_t>>{{1, 2}, {1, 3}}, 1),
					  make_tuple(vector<long>{-1, 6}, 3, vector<vector<size_t>>{{2, 3}}, 2),
					  make_tuple(vector<long>{6, -1, -1, -1, -1, -1, 12, -1, 12}, 10, vector<vector<size_t>>{{3, 1}, {10, 1}, {10, 1}, {3, 1}, {1, 8}, {5, 2}}, 3)));

class GetLowestPathCostTestFixture : public testing::TestWithParam<tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_vertices = get<1>(GetParam());
		_from = get<2>(GetParam());
		_to = get<3>(GetParam());
		_weights = get<4>(GetParam());
	}
	long GetLowestPathCostTest()
	{
		_graph.Clear();
		return _graph.GetLowestPathCost(_vertices, _from, _to, _weights);
	}

protected:
	Graph<size_t, size_t> _graph;
	long _expected;
	size_t _vertices;
	vector<size_t> _from, _to;
	vector<long> _weights;
};
TEST_P(GetLowestPathCostTestFixture, GetLowestPathCostTests)
{
	ASSERT_EQ(this->_expected, this->GetLowestPathCostTest());
}
INSTANTIATE_TEST_SUITE_P(
	GetLowestPathCostTests,
	GetLowestPathCostTestFixture,
	::testing::Values(make_tuple(80, 5, vector<size_t>{1, 3, 1, 4, 2}, vector<size_t>{2, 5, 4, 5, 3}, vector<long>{60, 70, 120, 150, 80}),
					  make_tuple(30, 4, vector<size_t>{1, 2, 1, 3}, vector<size_t>{2, 4, 3, 4}, vector<long>{20, 30, 5, 40}),
					  make_tuple(85, 5, vector<size_t>{1, 2, 3, 4, 1, 3}, vector<size_t>{2, 3, 4, 5, 3, 5}, vector<long>{30, 50, 70, 90, 70, 85}),
					  make_tuple(-1, 4, vector<size_t>{1, 3}, vector<size_t>{2, 4}, vector<long>{10, 20}),
					  make_tuple(1196, 10, vector<size_t>{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 9}, vector<size_t>{2, 3, 4, 5, 6, 7, 8, 9, 10, 3, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 5, 6, 7, 8, 9, 10, 6, 7, 8, 9, 10, 7, 8, 9, 10, 8, 9, 10, 9, 10, 10}, vector<long>{6337, 1594, 3766, 3645, 75, 5877, 8561, 242, 6386, 3331, 4194, 8069, 3934, 101, 8536, 6963, 9303, 7639, 8512, 1330, 6458, 1180, 3913, 1565, 9488, 1369, 8066, 9439, 7510, 6833, 4215, 194, 4774, 4328, 187, 1196, 200, 8743, 1433, 2933, 2069, 1974, 7349, 2351, 8423})));

TEST(GraphTests, DijkstraTest)
{
	vector<size_t> data(5);
	vector<long> ldata;
	ranges::generate(data, [n = 1]() mutable
					 { return n++; }); // Item values
	Graph<size_t, size_t> graph(data); // Tag values are indices
	ASSERT_EQ(data.size(), graph.Count());
	shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(0);
	ASSERT_TRUE(graph.HasVertex(0));
	ASSERT_TRUE(graph.HasVertex(1));
	ASSERT_TRUE(graph.HasVertex(2));
	ASSERT_TRUE(graph.HasVertex(3));
	ASSERT_TRUE(graph.HasVertex(4));

	ASSERT_FALSE(v1->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(1);
	ASSERT_FALSE(v2->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v3 = graph.GetVertex(2);
	ASSERT_FALSE(v3->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v4 = graph.GetVertex(3);
	ASSERT_FALSE(v4->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v5 = graph.GetVertex(4);
	ASSERT_FALSE(v5->HasNeighbours());
	ASSERT_EQ(0, v1->GetCost(v1));
	ASSERT_EQ(0, v2->GetCost(v2));
	ASSERT_EQ(0, v3->GetCost(v3));
	ASSERT_EQ(0, v4->GetCost(v4));
	graph.AddUndirectedEdge(v1, v2, 1); // 1->2 (1)
	ASSERT_TRUE(v1->HasNeighbour(v2));
	ASSERT_EQ(1, v1->GetCost(v2));
	ASSERT_TRUE(v2->HasNeighbour(v1));
	ASSERT_EQ(1, v2->GetCost(v1));
	graph.AddUndirectedEdge(v2, v3, 2); // 2->3 (2)
	ASSERT_TRUE(v2->HasNeighbour(v3));
	ASSERT_EQ(2, v2->GetCost(v3));
	ASSERT_TRUE(v3->HasNeighbour(v2));
	ASSERT_EQ(2, v3->GetCost(v2));
	graph.AddUndirectedEdge(v2, v4, 3); // 2->4 (3)
	ASSERT_TRUE(v2->HasNeighbour(v4));
	ASSERT_EQ(3, v2->GetCost(v4));
	ASSERT_TRUE(v4->HasNeighbour(v2));
	ASSERT_EQ(3, v4->GetCost(v2));
	graph.AddUndirectedEdge(v3, v5, 4); // 3->5 (4)
	ASSERT_TRUE(v3->HasNeighbour(v5));
	ASSERT_EQ(4, v3->GetCost(v5));
	ASSERT_TRUE(v5->HasNeighbour(v3));
	ASSERT_EQ(4, v5->GetCost(v3));
	graph.AddUndirectedEdge(v4, v5, 5); // 4->5 (5)
	ASSERT_TRUE(v4->HasNeighbour(v5));
	ASSERT_EQ(5, v4->GetCost(v5));
	ASSERT_TRUE(v5->HasNeighbour(v4));
	ASSERT_EQ(5, v5->GetCost(v4));
	map<shared_ptr<Vertex<size_t, size_t>>, long> costs;
	graph.Dijkstra(1, costs);
	cout << "Vertex\tDistance from Source (1): " << endl;
	for (map<shared_ptr<Vertex<size_t, size_t>>, long>::iterator it = costs.begin(); it != costs.end(); it++)
		cout << it->first->GetItem() << "\t" << it->second << endl;
	ASSERT_EQ(7, graph.Dijkstra(0, 4)); // 0->1->2->4 (Using tags)
	ASSERT_EQ(7, graph.Dijkstra(4, 0)); // 0->1->2->4 (Using tags)
	graph.Remove(2);
	ASSERT_FALSE(graph.HasVertex(2));
	ASSERT_FALSE(v2->HasNeighbour(v3));
	ASSERT_FALSE(v5->HasNeighbour(v3));
	costs.clear();
	graph.Clear();
	ASSERT_EQ(0, graph.Count());
	v1 = graph.AddVertex(0);
	v2 = graph.AddVertex(1);
	v3 = graph.AddVertex(2);
	v4 = graph.AddVertex(3);
	v5 = graph.AddVertex(4);
	ASSERT_EQ(5, graph.Count());
	graph.AddUndirectedEdge(v1, v2, 1);
	graph.AddUndirectedEdge(v2, v3, 2);
	graph.AddUndirectedEdge(v3, v5, 3);
	graph.AddUndirectedEdge(v2, v4, 2);
	ASSERT_EQ(6, graph.Dijkstra(0, 4)); // 1 + 2 + 3
	ASSERT_EQ(6, graph.Dijkstra(4, 0)); // 1 + 2 + 3
	ASSERT_EQ(1, graph.Dijkstra(0, 1));
	ASSERT_EQ(1, graph.Dijkstra(1, 0));
	ASSERT_EQ(2, graph.Dijkstra(1, 2));
	ASSERT_EQ(2, graph.Dijkstra(2, 1));
	ASSERT_EQ(3, graph.Dijkstra(0, 2)); // 1 + 2
	ASSERT_EQ(3, graph.Dijkstra(2, 0)); // 1 + 2
	ASSERT_EQ(3, graph.Dijkstra(0, 3)); // 1 + 2
	ASSERT_EQ(3, graph.Dijkstra(3, 0)); // 1 + 2
	ASSERT_EQ(4, graph.Dijkstra(2, 3)); // 2 + 2
	ASSERT_EQ(4, graph.Dijkstra(3, 2)); // 2 + 2
}
class PruneTestFixture : public testing::TestWithParam<tuple<long, size_t, vector<vector<size_t>>, set<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_vertices = get<1>(GetParam());
		_edges = get<2>(GetParam());
		_prune = get<3>(GetParam());
		vector<size_t> data(_vertices);
		ranges::generate(data, [n = 1]() mutable
						 { return n++; }); // Item values
		//_graph.AddVertices(data);		   Tag values are indices which start from 0 but the test data start from 1
		for (vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_graph.AddUndirectedEdge((*it)[0], (*it)[1], (*it)[2]);
	}
	long PruneTest(set<size_t> &removed)
	{
		/*
			Since it is an undirected graph, the weight returned will be x2
		*/
		return _graph.Prune(_prune, removed);
	}

protected:
	Graph<size_t, size_t> _graph;
	long _expected;
	vector<vector<size_t>> _edges;
	size_t _vertices;
	set<size_t> _prune;
};
TEST_P(PruneTestFixture, PruneTests)
{
	set<size_t> removed;
	ASSERT_EQ(this->_vertices, _graph.Count());
	ASSERT_EQ(this->_expected, this->PruneTest(removed));
	ASSERT_TRUE(includes(this->_prune.begin(), this->_prune.end(), removed.begin(), removed.end()));
}
INSTANTIATE_TEST_SUITE_P(
	PruneTests,
	PruneTestFixture,
	::testing::Values(make_tuple(0, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}, set<size_t>{}), make_tuple(6, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}, set<size_t>{5}), make_tuple(16, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}, set<size_t>{1, 2, 3, 4, 5}),
					  make_tuple(8, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}, set<size_t>{1, 5}), make_tuple(6, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {2, 5, 3}}, set<size_t>{5}),
					  make_tuple(6, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}, set<size_t>{1, 4}), make_tuple(0, 4, vector<vector<size_t>>{{1, 2, 1}, {1, 3, 2}, {2, 4, 2}, {3, 4, 3}}, set<size_t>{1, 2, 3, 4}),
					  make_tuple(12, 6, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {2, 6, 3}}, set<size_t>{5, 6}), make_tuple(20, 7, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}, set<size_t>{5, 6, 7})));
class DiameterTestFixture : public testing::TestWithParam<tuple<long, size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_vertices = get<1>(GetParam());
		_edges = get<2>(GetParam());
		vector<size_t> data(_vertices);
		ranges::generate(data, [n = 1]() mutable
						 { return n++; }); // Item values
		//_graph.AddVertices(data);		   Tag values are indices which start from 0 but the test data start from 1
		for (vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_graph.AddUndirectedEdge((*it)[0], (*it)[1], (*it)[2]);
	}
	long DiameterTest()
	{
		return _graph.Diameter();
	}

protected:
	Graph<size_t, size_t> _graph;
	long _expected;
	vector<vector<size_t>> _edges;
	size_t _vertices;
};
TEST_P(DiameterTestFixture, DiameterTests)
{
	ASSERT_EQ(this->_vertices, _graph.Count());
	ASSERT_EQ(this->_expected, this->DiameterTest());
}
INSTANTIATE_TEST_SUITE_P(
	DiameterTests,
	DiameterTestFixture,
	::testing::Values(make_tuple(7, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}), make_tuple(5, 5, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {2, 5, 3}}),
					  make_tuple(8, 6, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {2, 6, 3}}), make_tuple(9, 7, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}),
					  make_tuple(4, 4, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}}),
					  make_tuple(0, 0, vector<vector<size_t>>{}), make_tuple(10, 2, vector<vector<size_t>>{{1, 2, 10}}), make_tuple(9, 7, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}})));
class PostmanProblemWithoutLoopTestFixture : public testing::TestWithParam<tuple<size_t, size_t, set<size_t>, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_cities = get<1>(GetParam());
		_destinations = get<2>(GetParam());
		_edges = get<3>(GetParam());
	}
	size_t PostmanProblemWithoutLoopTest()
	{
		return PostmanProblemWithoutLoop(_cities, _destinations, _edges);
	}

protected:
	size_t _expected, _cities;
	set<size_t> _destinations;
	vector<vector<size_t>> _edges;
};
TEST_P(PostmanProblemWithoutLoopTestFixture, PostmanProblemWithoutLoopTests)
{
	ASSERT_EQ(this->_expected, this->PostmanProblemWithoutLoopTest());
}
INSTANTIATE_TEST_SUITE_P(
	PostmanProblemWithoutLoopTests,
	PostmanProblemWithoutLoopTestFixture,
	::testing::Values(make_tuple(6, 5, set<size_t>{1, 3, 4}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}}), make_tuple(54, 20, set<size_t>{5, 11, 12, 16, 15}, vector<vector<size_t>>{{17, 4, 3}, {11, 12, 5}, {14, 2, 1}, {16, 14, 4}, {7, 8, 4}, {13, 5, 5}, {17, 15, 2}, {5, 3, 5}, {8, 6, 1}, {18, 10, 4}, {18, 1, 3}, {16, 1, 2}, {9, 2, 5}, {11, 6, 1}, {4, 9, 4}, {7, 20, 2}, {13, 19, 3}, {19, 12, 3}, {10, 20, 2}}),
					  make_tuple(54, 20, set<size_t>{5, 11, 12, 15, 16}, vector<vector<size_t>>{{17, 4, 3}, {11, 12, 5}, {14, 2, 1}, {16, 14, 4}, {7, 8, 4}, {13, 5, 5}, {17, 15, 2}, {5, 3, 5}, {8, 6, 1}, {18, 10, 4}, {18, 1, 3}, {16, 1, 2}, {9, 2, 5}, {11, 6, 1}, {4, 9, 4}, {7, 20, 2}, {13, 19, 3}, {19, 12, 3}, {10, 20, 2}}),
					  make_tuple(6, 7, set<size_t>{1, 3, 4}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}), make_tuple(9, 7, set<size_t>{1, 4, 5}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}),
					  make_tuple(3, 7, set<size_t>{1, 2, 4}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}), make_tuple(11, 7, set<size_t>{1, 6, 7}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}),
					  make_tuple(10, 7, set<size_t>{1, 4, 6}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}), make_tuple(2, 7, set<size_t>{2, 3}, vector<vector<size_t>>{{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}, {3, 6, 4}, {2, 7, 3}}),
					  make_tuple(1086, 300, set<size_t>{44, 137, 195, 20, 42, 75, 109, 106, 160, 125}, vector<vector<size_t>>{{114, 250, 2}, {267, 148, 6}, {19, 223, 10}, {193, 300, 4}, {12, 131, 8}, {63, 230, 7}, {226, 184, 6}, {229, 271, 1}, {273, 27, 1}, {130, 119, 3}, {175, 212, 9}, {262, 183, 1}, {254, 227, 6}, {83, 200, 9}, {37, 77, 8}, {12, 58, 6}, {197, 134, 4}, {120, 160, 10}, {69, 107, 9}, {217, 173, 4}, {126, 251, 1}, {65, 261, 1}, {264, 101, 1}, {111, 145, 1}, {96, 33, 1}, {77, 32, 1}, {89, 51, 2}, {278, 296, 10}, {181, 188, 4}, {133, 238, 10}, {113, 159, 3}, {66, 123, 5}, {121, 208, 10}, {298, 243, 3}, {53, 75, 8}, {134, 195, 7}, {196, 35, 5}, {20, 164, 10}, {281, 211, 9}, {277, 9, 7}, {245, 48, 6}, {236, 52, 9}, {20, 41, 1}, {172, 48, 9}, {283, 264, 9}, {110, 24, 9}, {46, 117, 6}, {80, 258, 9}, {92, 97, 8}, {262, 275, 6}, {218, 10, 10}, {128, 268, 8}, {158, 180, 10}, {288, 205, 10}, {141, 21, 9}, {237, 192, 8}, {99, 201, 7}, {174, 14, 3}, {189, 183, 5}, {102, 83, 7}, {107, 105, 10}, {221, 146, 7}, {234, 162, 10}, {249, 104, 3}, {244, 297, 9}, {272, 276, 6}, {94, 219, 1}, {266, 213, 3}, {270, 135, 2}, {62, 204, 9}, {53, 280, 4}, {54, 40, 7}, {259, 190, 5}, {156, 147, 3}, {42, 19, 2}, {291, 71, 7}, {241, 200, 5}, {5, 257, 1}, {250, 191, 10}, {39, 97, 5}, {245, 295, 2}, {60, 241, 10}, {169, 297, 5}, {192, 29, 3}, {69, 293, 8}, {115, 23, 7}, {100, 36, 2}, {81, 41, 2}, {59, 7, 4}, {31, 75, 8}, {93, 299, 4}, {155, 235, 3}, {254, 75, 8}, {95, 199, 8}, {228, 157, 9}, {63, 38, 9}, {16, 74, 4}, {73, 265, 3}, {25, 223, 1}, {61, 266, 5}, {161, 23, 1}, {150, 288, 10}, {294, 137, 7}, {138, 82, 9}, {225, 82, 9}, {87, 128, 10}, {8, 190, 1}, {13, 240, 5}, {269, 55, 8}, {246, 278, 7}, {252, 118, 6}, {178, 136, 7}, {18, 246, 2}, {51, 240, 6}, {242, 33, 9}, {88, 2, 2}, {129, 95, 2}, {71, 6, 10}, {215, 133, 4}, {3, 109, 2}, {136, 276, 7}, {205, 195, 7}, {125, 166, 6}, {194, 64, 6}, {54, 130, 4}, {137, 218, 10}, {157, 170, 8}, {43, 143, 7}, {214, 204, 8}, {66, 30, 3}, {42, 274, 5}, {58, 165, 6}, {292, 259, 6}, {124, 103, 6}, {24, 171, 6}, {174, 189, 4}, {282, 202, 2}, {139, 173, 10}, {47, 50, 2}, {29, 131, 2}, {49, 265, 1}, {206, 247, 6}, {92, 115, 1}, {46, 248, 7}, {140, 45, 8}, {231, 244, 6}, {127, 215, 4}, {242, 216, 10}, {185, 251, 10}, {212, 80, 1}, {220, 72, 5}, {91, 112, 1}, {295, 73, 5}, {187, 176, 5}, {274, 104, 9}, {55, 138, 2}, {37, 86, 10}, {224, 212, 8}, {188, 140, 1}, {222, 142, 10}, {132, 123, 7}, {246, 89, 9}, {228, 269, 9}, {28, 36, 3}, {299, 15, 6}, {207, 124, 7}, {279, 153, 8}, {13, 202, 8}, {52, 263, 8}, {101, 187, 9}, {158, 96, 9}, {32, 148, 8}, {287, 300, 7}, {210, 235, 10}, {94, 154, 2}, {230, 109, 6}, {273, 193, 7}, {106, 285, 2}, {151, 153, 6}, {191, 197, 7}, {208, 60, 1}, {236, 232, 6}, {249, 3, 9}, {199, 45, 4}, {76, 5, 7}, {206, 44, 7}, {298, 143, 2}, {70, 168, 5}, {294, 220, 10}, {85, 162, 9}, {170, 102, 7}, {43, 99, 3}, {239, 179, 1}, {261, 239, 1}, {163, 211, 3}, {28, 255, 1}, {116, 226, 4}, {293, 203, 5}, {201, 59, 1}, {112, 79, 2}, {253, 150, 9}, {90, 113, 5}, {152, 106, 3}, {180, 232, 3}, {57, 292, 8}, {167, 129, 7}, {85, 289, 7}, {229, 225, 9}, {257, 198, 8}, {272, 287, 9}, {177, 27, 10}, {198, 209, 5}, {114, 44, 7}, {108, 280, 8}, {177, 290, 6}, {135, 216, 9}, {79, 161, 7}, {98, 268, 8}, {118, 146, 6}, {68, 181, 5}, {209, 238, 3}, {145, 1, 1}, {252, 84, 1}, {284, 248, 2}, {175, 11, 2}, {214, 105, 10}, {286, 159, 10}, {296, 68, 5}, {47, 258, 4}, {253, 6, 8}, {267, 108, 3}, {165, 16, 4}, {194, 25, 3}, {152, 164, 3}, {81, 121, 3}, {285, 281, 5}, {50, 100, 10}, {186, 182, 10}, {286, 275, 5}, {185, 176, 10}, {9, 72, 2}, {270, 227, 8}, {70, 149, 4}, {155, 119, 3}, {222, 14, 8}, {256, 56, 7}, {4, 182, 10}, {207, 65, 3}, {217, 120, 5}, {84, 56, 1}, {179, 156, 4}, {163, 233, 6}, {87, 39, 3}, {166, 203, 4}, {243, 122, 7}, {132, 10, 7}, {168, 247, 5}, {154, 142, 3}, {26, 31, 10}, {277, 186, 8}, {233, 18, 8}, {284, 169, 3}, {234, 38, 8}, {290, 125, 8}, {168, 90, 2}, {88, 21, 1}, {155, 231, 7}, {35, 289, 1}, {221, 110, 1}, {263, 117, 9}, {61, 172, 1}, {103, 210, 7}, {139, 98, 1}, {184, 49, 7}, {67, 160, 7}, {231, 99, 3}, {151, 8, 2}, {282, 78, 3}, {213, 15, 2}, {22, 122, 4}, {93, 144, 1}, {256, 147, 1}, {255, 7, 3}, {141, 34, 8}, {34, 279, 8}, {76, 149, 2}, {291, 144, 1}, {283, 74, 7}, {4, 22, 1}, {17, 67, 5}, {126, 64, 10}, {17, 1, 6}, {91, 30, 4}, {178, 127, 1}, {237, 167, 10}, {260, 171, 9}, {40, 57, 1}, {78, 111, 9}, {26, 219, 3}}),
					  make_tuple(247, 100, set<size_t>{52, 54, 70, 92, 73, 86, 46}, vector<vector<size_t>>{{83, 92, 2}, {27, 4, 6}, {42, 44, 2}, {70, 42, 6}, {14, 91, 4}, {11, 47, 3}, {59, 36, 7}, {18, 54, 6}, {62, 22, 5}, {11, 2, 1}, {54, 66, 7}, {19, 60, 6}, {45, 100, 3}, {88, 86, 5}, {10, 83, 6}, {33, 96, 1}, {52, 80, 3}, {99, 73, 7}, {98, 82, 4}, {1, 31, 7}, {55, 85, 4}, {86, 35, 4}, {61, 50, 5}, {3, 4, 3}, {49, 60, 6}, {56, 65, 4}, {32, 65, 3}, {37, 63, 3}, {69, 25, 7}, {9, 30, 7}, {49, 84, 6}, {38, 31, 3}, {52, 66, 4}, {84, 25, 7}, {85, 71, 1}, {51, 5, 5}, {82, 67, 4}, {98, 20, 6}, {80, 38, 5}, {75, 94, 7}, {19, 70, 7}, {100, 12, 5}, {13, 47, 7}, {59, 75, 1}, {99, 17, 3}, {95, 74, 5}, {61, 53, 4}, {43, 92, 6}, {58, 69, 5}, {41, 18, 5}, {9, 93, 7}, {26, 6, 1}, {24, 90, 5}, {77, 5, 3}, {90, 40, 2}, {67, 10, 7}, {62, 88, 2}, {29, 12, 4}, {64, 36, 7}, {21, 64, 5}, {42, 57, 1}, {79, 28, 5}, {72, 68, 3}, {27, 44, 2}, {33, 68, 3}, {20, 30, 3}, {39, 40, 4}, {16, 8, 4}, {50, 21, 4}, {73, 7, 6}, {2, 6, 5}, {97, 29, 2}, {7, 15, 7}, {41, 58, 2}, {91, 81, 6}, {15, 71, 3}, {32, 43, 2}, {77, 79, 1}, {46, 17, 5}, {87, 76, 2}, {1, 11, 1}, {87, 13, 6}, {95, 97, 3}, {3, 34, 4}, {63, 8, 5}, {72, 34, 7}, {22, 24, 5}, {26, 48, 1}, {37, 46, 2}, {55, 28, 6}, {74, 16, 4}, {48, 81, 2}, {53, 78, 4}, {89, 96, 7}, {76, 35, 4}, {57, 78, 7}, {56, 89, 3}, {22, 51, 4}})));
/*
 * https://www.hackerrank.com/challenges/johnland/problem
 * Timeout!
 */
template <typename T>
class RoadsInHackerlandFixture
{
protected:
	void SetUp(string expected, size_t nodes, vector<vector<T>> edges)
	{
		_expected = expected;
		_nodes = nodes;
		_edges = edges;
	}
	string _expected;
	size_t _nodes;
	vector<vector<T>> _edges;
	Graph<T, T> _graph;
	Dijkstra<T> _dijkstra;
};
class RoadsInHackerlandTestFixture : public RoadsInHackerlandFixture<size_t>, public testing::TestWithParam<tuple<string, size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		RoadsInHackerlandFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
		vector<size_t> data(_nodes);
		ranges::generate(data, [n = 1]() mutable
						 { return n++; }); // Item values
		_graph.AddVertices(data);		   // Tag values are indices
		for (vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_graph.AddUndirectedEdge((*it)[0] - 1, (*it)[1] - 1, 1 << (*it)[2]);
	}
	string RoadsInHackerlandTest()
	{
		size_t distance = 0;
		std::mutex m;
		set<string> computed;
		parallel_for(blocked_range<size_t>(1, _nodes, 2), [&](blocked_range<size_t> r)
					 {
		m.lock();
		cout << "parallel_for blocked range [" << r.begin() << "," << r.end() << "]" << endl;
		m.unlock();
		for (size_t i = r.begin(); i < r.end(); i++)
			for (size_t j = i + 1; j <= _nodes; j++)
			{
				if (i != j)
				{
					ostringstream oss1, oss2;
					oss1 << i << "-" << j;
					oss2 << j << "-" << i;
					m.lock();
					if (!computed.count(oss1.str()) && !computed.count(oss2.str()))
					{
						computed.emplace(oss1.str());
						computed.emplace(oss2.str());
						m.unlock();
						long cost = _graph.Dijkstra(i - 1, j - 1);
						m.lock();
						if (cost >= 0)
							distance += cost;
						m.unlock();
					}
					else
						m.unlock();
				}
			} });
		string binary = decimal_to_binary(distance ? distance : -1);
		size_t offset = binary.find_first_not_of('0');
		return binary.substr(offset != string::npos ? offset : 0);
	}
};
TEST_P(RoadsInHackerlandTestFixture, RoadsInHackerlandTests)
{
	// The root of the graph is Node 1
	ASSERT_EQ(this->_nodes, _graph.Count());
	ASSERT_EQ(this->_expected, this->RoadsInHackerlandTest());
}
INSTANTIATE_TEST_SUITE_P(
	RoadsInHackerlandTests,
	RoadsInHackerlandTestFixture,
	::testing::Values(make_tuple<string, size_t, vector<vector<size_t>>>("1000100", 5, vector<vector<size_t>>{{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}}),
					  make_tuple<string, size_t, vector<vector<size_t>>>("10100011101101000001001000", 18, vector<vector<size_t>>{
																											   {5, 12, 18},
																											   {17, 2, 5},
																											   {7, 18, 3},
																											   {17, 6, 0},
																											   {15, 12, 16},
																											   {2, 3, 8},
																											   {14, 9, 20},
																											   {4, 9, 11},
																											   {13, 1, 21},
																											   {13, 12, 15},
																											   {15, 12, 10},
																											   {6, 16, 9},
																											   {11, 18, 2},
																											   {9, 16, 17},
																											   {12, 4, 4},
																											   {7, 4, 19},
																											   {17, 1, 12},
																											   {10, 14, 7},
																											   {8, 5, 13},
																											   {18, 3, 14},
																											   {4, 11, 6},
																											   {15, 3, 1},
																											   {12, 5, 22},
																										   }),
					  make_tuple<string, size_t, vector<vector<size_t>>>("1010100000000011001101110101111", 20, vector<vector<size_t>>{
																													{4, 11, 27},
																													{7, 9, 14},
																													{13, 6, 23},
																													{18, 10, 3},
																													{19, 4, 19},
																													{2, 7, 6},
																													{11, 13, 20},
																													{6, 15, 0},
																													{14, 18, 2},
																													{16, 5, 26},
																													{2, 20, 10},
																													{16, 17, 21},
																													{6, 2, 9},
																													{11, 5, 25},
																													{20, 19, 28},
																													{14, 4, 29},
																													{10, 4, 24},
																													{9, 7, 8},
																													{7, 1, 15},
																													{12, 13, 7},
																													{8, 3, 22},
																													{8, 13, 4},
																													{17, 14, 1},
																													{8, 15, 11},
																													{1, 10, 5},
																													{18, 15, 18},
																													{7, 13, 17},
																													{12, 9, 16},
																													{14, 6, 12},
																													{9, 2, 13},
																												})));

class RoadsInHackerland1TestFixture : public RoadsInHackerlandFixture<size_t>, public testing::TestWithParam<tuple<string, size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		RoadsInHackerlandFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
		vector<size_t> data(_nodes);
		ranges::generate(data, [n = 1]() mutable
						 { return n++; });
		_dijkstra.AddVertices(data);
		assert(_dijkstra.Count() == _nodes);
		for (vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_dijkstra.AddUndirectedEdge((*it)[0], (*it)[1], 1 << (*it)[2]);
	}
	string RoadsInHackerland1Test()
	{
		size_t distance = 0;
		set<string> computed;
		for (size_t i = 1; i < _nodes; i++)
			for (size_t j = i + 1; j <= _nodes; j++)
			{
				if (i != j)
				{
					ostringstream oss1, oss2;
					oss1 << i << "-" << j;
					oss2 << j << "-" << i;
					if (!computed.count(oss1.str()) && !computed.count(oss2.str()))
					{
						computed.emplace(oss1.str());
						computed.emplace(oss2.str());
						vector<shared_ptr<DVertex<size_t>>> path;
						long cost = _dijkstra.ShortestPath(i, j, path);
						_dijkstra.InitVertices(); // This prevents the routine from being used in multi-threading mode.
						distance += cost;
					}
				}
			}
		string binary = decimal_to_binary(distance ? distance : -1);
		size_t offset = binary.find_first_not_of('0');
		return binary.substr(offset != string::npos ? offset : 0);
	}
};
TEST_P(RoadsInHackerland1TestFixture, RoadsInHackerland1Tests)
{
	// The root of the graph is Node 1
	ASSERT_EQ(this->_expected, this->RoadsInHackerland1Test());
}
INSTANTIATE_TEST_SUITE_P(
	RoadsInHackerland1Tests,
	RoadsInHackerland1TestFixture,
	::testing::Values(make_tuple<string, size_t, vector<vector<size_t>>>("1000100", 5, vector<vector<size_t>>{{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}}),
					  make_tuple<string, size_t, vector<vector<size_t>>>("10100011101101000001001000", 18, vector<vector<size_t>>{
																											   {5, 12, 18},
																											   {17, 2, 5},
																											   {7, 18, 3},
																											   {17, 6, 0},
																											   {15, 12, 16},
																											   {2, 3, 8},
																											   {14, 9, 20},
																											   {4, 9, 11},
																											   {13, 1, 21},
																											   {13, 12, 15},
																											   {15, 12, 10},
																											   {6, 16, 9},
																											   {11, 18, 2},
																											   {9, 16, 17},
																											   {12, 4, 4},
																											   {7, 4, 19},
																											   {17, 1, 12},
																											   {10, 14, 7},
																											   {8, 5, 13},
																											   {18, 3, 14},
																											   {4, 11, 6},
																											   {15, 3, 1},
																											   {12, 5, 22},
																										   }),
					  make_tuple<string, size_t, vector<vector<size_t>>>("1010100000000011001101110101111", 20, vector<vector<size_t>>{
																													{4, 11, 27},
																													{7, 9, 14},
																													{13, 6, 23},
																													{18, 10, 3},
																													{19, 4, 19},
																													{2, 7, 6},
																													{11, 13, 20},
																													{6, 15, 0},
																													{14, 18, 2},
																													{16, 5, 26},
																													{2, 20, 10},
																													{16, 17, 21},
																													{6, 2, 9},
																													{11, 5, 25},
																													{20, 19, 28},
																													{14, 4, 29},
																													{10, 4, 24},
																													{9, 7, 8},
																													{7, 1, 15},
																													{12, 13, 7},
																													{8, 3, 22},
																													{8, 13, 4},
																													{17, 14, 1},
																													{8, 15, 11},
																													{1, 10, 5},
																													{18, 15, 18},
																													{7, 13, 17},
																													{12, 9, 16},
																													{14, 6, 12},
																													{9, 2, 13},
																												})));
class RoadsInHackerland2TestFixture : public RoadsInHackerlandFixture<size_t>, public testing::TestWithParam<tuple<string, size_t, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		RoadsInHackerlandFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
		vector<size_t> data(_nodes);
		ranges::generate(data, [n = 1]() mutable
						 { return n++; });
		_dijkstra.AddVertices(data);
		assert(_dijkstra.Count() == _nodes);
		for (vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_dijkstra.AddUndirectedEdge((*it)[0], (*it)[1], 1 << (*it)[2]);
	}
	string RoadsInHackerland2Test()
	{
		size_t distance = 0;
		std::mutex m;
		set<string> computed;
		parallel_for(blocked_range<size_t>(1, _nodes, 2), [&](blocked_range<size_t> r)
					 {
		m.lock();
		cout << "parallel_for blocked range [" << r.begin() << "," << r.end() << "]" << endl;
		m.unlock();
		for (size_t i = r.begin(); i < r.end(); i++)
			for (size_t j = i + 1; j <= _nodes; j++)
			{
				if (i != j)
				{
					ostringstream oss1, oss2;
					oss1 << i << "-" << j;
					oss2 << j << "-" << i;
					m.lock();
					if (!computed.count(oss1.str()) && !computed.count(oss2.str()))
					{
						computed.emplace(oss1.str());
						computed.emplace(oss2.str());
						m.unlock();
						vector<shared_ptr<DVertex<size_t>>> path;
						long cost = _dijkstra.ShortestPathStateless(i, j, path);
						m.lock();
						distance += cost;
						m.unlock();
					}
					else
						m.unlock();
				}
			} });
		string binary = decimal_to_binary(distance ? distance : -1);
		size_t offset = binary.find_first_not_of('0');
		return binary.substr(offset != string::npos ? offset : 0);
	}
};
TEST_P(RoadsInHackerland2TestFixture, RoadsInHackerland2Tests)
{
	// The root of the graph is Node 1
	ASSERT_EQ(this->_expected, this->RoadsInHackerland2Test());
}
INSTANTIATE_TEST_SUITE_P(
	RoadsInHackerland2Tests,
	RoadsInHackerland2TestFixture,
	::testing::Values(make_tuple<string, size_t, vector<vector<size_t>>>("1000100", 5, vector<vector<size_t>>{{1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2}}),
					  make_tuple<string, size_t, vector<vector<size_t>>>("10100011101101000001001000", 18, vector<vector<size_t>>{
																											   {5, 12, 18},
																											   {17, 2, 5},
																											   {7, 18, 3},
																											   {17, 6, 0},
																											   {15, 12, 16},
																											   {2, 3, 8},
																											   {14, 9, 20},
																											   {4, 9, 11},
																											   {13, 1, 21},
																											   {13, 12, 15},
																											   {15, 12, 10},
																											   {6, 16, 9},
																											   {11, 18, 2},
																											   {9, 16, 17},
																											   {12, 4, 4},
																											   {7, 4, 19},
																											   {17, 1, 12},
																											   {10, 14, 7},
																											   {8, 5, 13},
																											   {18, 3, 14},
																											   {4, 11, 6},
																											   {15, 3, 1},
																											   {12, 5, 22},
																										   }),
					  make_tuple<string, size_t, vector<vector<size_t>>>("1010100000000011001101110101111", 20, vector<vector<size_t>>{
																													{4, 11, 27},
																													{7, 9, 14},
																													{13, 6, 23},
																													{18, 10, 3},
																													{19, 4, 19},
																													{2, 7, 6},
																													{11, 13, 20},
																													{6, 15, 0},
																													{14, 18, 2},
																													{16, 5, 26},
																													{2, 20, 10},
																													{16, 17, 21},
																													{6, 2, 9},
																													{11, 5, 25},
																													{20, 19, 28},
																													{14, 4, 29},
																													{10, 4, 24},
																													{9, 7, 8},
																													{7, 1, 15},
																													{12, 13, 7},
																													{8, 3, 22},
																													{8, 13, 4},
																													{17, 14, 1},
																													{8, 15, 11},
																													{1, 10, 5},
																													{18, 15, 18},
																													{7, 13, 17},
																													{12, 9, 16},
																													{14, 6, 12},
																													{9, 2, 13},
																												})));
class MinSubGraphsDifferenceTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, vector<vector<size_t>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_edges = get<2>(GetParam()); // Use tag. Not value
	}
	size_t MinSubGraphsDifferenceTest()
	{
		_graph.AddVertices(_data);
		for (vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_graph.AddUndirectedEdge((*it)[0] - 1, (*it)[1] - 1, 0);
		return _graph.MinSubGraphsDifference(0);
	}

protected:
	Graph<size_t, size_t> _graph;
	size_t _expected;
	vector<size_t> _data;
	vector<vector<size_t>> _edges;
};
TEST_P(MinSubGraphsDifferenceTestFixture, MinSubGraphsDifferenceTests)
{
	ASSERT_EQ(this->_expected, this->MinSubGraphsDifferenceTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinSubGraphsDifferenceTests,
	MinSubGraphsDifferenceTestFixture,
	::testing::Values(make_tuple(4, vector<size_t>{10, 5, 11}, vector<vector<size_t>>{{1, 2}, {1, 3}}),
					  make_tuple(1, vector<size_t>{10, 5, 6, 20}, vector<vector<size_t>>{{1, 2}, {1, 3}, {2, 4}}),
					  make_tuple(5, vector<size_t>{10, 5, 20}, vector<vector<size_t>>{{1, 2}, {2, 3}}),
					  make_tuple(400, vector<size_t>{100, 200, 100, 500, 100, 600}, vector<vector<size_t>>{{1, 2}, {2, 3}, {2, 5}, {4, 5}, {5, 6}}),
					  make_tuple(99, vector<size_t>{205, 573, 985, 242, 830, 514, 592, 263, 142, 915}, vector<vector<size_t>>{{2, 8}, {10, 5}, {1, 7}, {6, 9}, {4, 3}, {8, 10}, {5, 1}, {7, 6}, {9, 4}}),
					  make_tuple(525, vector<size_t>{716, 365, 206, 641, 841, 585, 801, 645, 208, 924, 920, 286, 554, 832, 359, 836, 247, 959, 31, 322, 709, 860, 890, 195, 575, 905, 314, 41, 669, 549, 950, 736, 265, 507, 729, 457, 91, 529, 102, 650, 805, 373, 287, 710, 556, 645, 546, 154, 956, 928}, vector<vector<size_t>>{{14, 25}, {25, 13}, {13, 20}, {20, 24}, {43, 2}, {2, 48}, {48, 42}, {42, 5}, {27, 18}, {18, 30}, {30, 7}, {7, 36}, {37, 9}, {9, 23}, {23, 49}, {49, 15}, {31, 26}, {26, 29}, {29, 50}, {50, 21}, {41, 45}, {45, 10}, {10, 17}, {17, 34}, {28, 47}, {47, 44}, {44, 11}, {11, 16}, {3, 8}, {8, 39}, {39, 38}, {38, 22}, {19, 32}, {32, 12}, {12, 40}, {40, 46}, {1, 35}, {35, 4}, {4, 33}, {33, 6}, {25, 2}, {2, 27}, {7, 37}, {15, 50}, {21, 10}, {17, 28}, {16, 39}, {38, 19}, {40, 1}})));
class UnbeatenPathsTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<vector<size_t>>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
		_data = get<2>(GetParam());
		_source = get<3>(GetParam());
	}
	vector<long> UnbeatenPathsTest()
	{
		return UnbeatenPaths(_n, _data, _source);
	}

protected:
	vector<long> _expected;
	vector<vector<size_t>> _data;
	size_t _n, _source;
};
TEST_P(UnbeatenPathsTestFixture, UnbeatenPathsTests)
{
	ASSERT_EQ(this->_expected, this->UnbeatenPathsTest());
}
INSTANTIATE_TEST_SUITE_P(
	UnbeatenPathsTests,
	UnbeatenPathsTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 1, 1, 1, 1, 1, 1, 1, 1}, 10, vector<vector<size_t>>{}, 5), make_tuple(vector<long>{3, 1, 2}, 4, vector<vector<size_t>>{{1, 2}, {2, 3}, {1, 4}}, 1),
					  make_tuple(vector<long>{2, 2, 1}, 4, vector<vector<size_t>>{{1, 2}, {2, 3}}, 2), make_tuple(ranges::iota_view(1, 5) | ranges::to<vector<long>>(), 5, vector<vector<size_t>>{{1, 3}, {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 5}}, 1)));
template <typename T>
class AutoGeneratedVerticesGraphFixture
{
protected:
	void SetUp(size_t expected, vector<vector<T>> edges, size_t nodes, T start)
	{
		_expected = expected;
		_start = start;
		_nodes = nodes;
		_edges = edges;
		vector<T> data(_nodes);
		ranges::generate(data, [n = 1]() mutable
						 { return n++; }); // Item values
		_graph.AddVertices(data);		   // Tags are indices
		for (typename vector<vector<T>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_graph.AddUndirectedEdge((*it)[0] - 1, (*it)[1] - 1, (*it).size() == 3 ? (*it)[2] : 0);
	}
	size_t _nodes, _expected;
	T _start;
	vector<vector<T>> _edges;
	Graph<T, T> _graph;
};
class UnsignedGraphFixture : public AutoGeneratedVerticesGraphFixture<size_t>, public testing::TestWithParam<tuple<size_t, vector<vector<size_t>>, size_t, size_t>>
{
public:
	void SetUp() override
	{
		AutoGeneratedVerticesGraphFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()), get<3>(GetParam()));
	}
	size_t EvenForestTest()
	{
		return _graph.EvenForest(_start - 1);
	}
};
/*
 * https://www.hackerrank.com/challenges/even-tree/problem
 * 100%
 */
TEST_P(UnsignedGraphFixture, EvenForestTests)
{
	// The root of the graph is Node 1
	ASSERT_EQ(this->_nodes, _graph.Count());
	ASSERT_EQ(this->_expected, this->EvenForestTest());
}
INSTANTIATE_TEST_SUITE_P(
	EvenForestTests,
	UnsignedGraphFixture,
	::testing::Values(make_tuple<size_t, vector<vector<size_t>>, size_t, size_t>(1, vector<vector<size_t>>{{1, 2}, {1, 3}, {3, 4}}, 4, 1),
					  make_tuple<size_t, vector<vector<size_t>>, size_t, size_t>(2, vector<vector<size_t>>{{2, 1}, {3, 1}, {4, 3}, {5, 2}, {6, 1}, {7, 2}, {8, 6}, {9, 8}, {10, 8}}, 10, 1),
					  make_tuple<size_t, vector<vector<size_t>>, size_t, size_t>(4, vector<vector<size_t>>{{2, 1}, {3, 1}, {4, 3}, {5, 2}, {6, 5}, {7, 1}, {8, 1}, {9, 2}, {10, 7}, {11, 10}, {12, 3}, {13, 7}, {14, 8}, {15, 12}, {16, 6}, {17, 6}, {18, 10}, {19, 1}, {20, 8}}, 20, 1)));
class SignedGraphFixture : public AutoGeneratedVerticesGraphFixture<long>, public testing::TestWithParam<tuple<size_t, vector<vector<long>>, size_t, long>>
{
public:
	void SetUp() override
	{
		AutoGeneratedVerticesGraphFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()), get<3>(GetParam()));
	}
	size_t PrimMinimumSpanningTreeTest()
	{
		return _graph.PrimMinimumSpanningTree(_graph.GetVertex(_start));
	}
};
/* https://www.hackerrank.com/challenges/primsmstsub/problem
   https://en.wikipedia.org/wiki/Prim%27s_algorithm
   https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
   https://stackoverflow.com/questions/1195872/when-should-i-use-kruskal-as-opposed-to-prim-and-vice-versa
   Use Prim's algorithm when you have a graph with lots of edges, i.e., if the number of edges to vertices is high.
   Prim's algorithm is significantly faster in the limit when you've got a really dense graph with many more edges than vertices.
   100%
*/
TEST_P(SignedGraphFixture, PrimMinimumSpanningTreeTests)
{
	ASSERT_EQ(this->_expected, this->PrimMinimumSpanningTreeTest());
}
INSTANTIATE_TEST_SUITE_P(
	PrimMinimumSpanningTreeTests,
	SignedGraphFixture,
	::testing::Values(make_tuple<size_t, vector<vector<long>>, size_t, long>(15, vector<vector<long>>{{1, 2, 3}, {1, 3, 4}, {4, 2, 6}, {5, 2, 2}, {2, 3, 5}, {3, 5, 7}}, 5, 1),
					  make_tuple<size_t, vector<vector<long>>, size_t, long>(150, vector<vector<long>>{{1, 2, 20}, {1, 3, 50}, {1, 4, 70}, {1, 5, 90}, {2, 3, 30}, {3, 4, 40}, {4, 5, 60}}, 5, 2),
					  make_tuple<size_t, vector<vector<long>>, size_t, long>(1106, vector<vector<long>>{{2, 1, 1000}, {3, 4, 299}, {2, 4, 200}, {2, 4, 100}, {3, 2, 300}, {3, 2, 6}}, 4, 2)));
TEST(GraphTests, KruskalTest)
{
	vector<long> from{1, 1, 4, 2, 3, 3}, to{2, 3, 1, 4, 2, 4}, weights{5, 3, 6, 7, 4, 5};
	ASSERT_EQ(12, kruskals(4, from, to, weights));
	from.clear();
	to.clear();
	weights.clear();
	from = {1, 3, 4, 1, 3};
	to = {2, 2, 3, 4, 1};
	weights = {1, 150, 99, 100, 200};
	ASSERT_EQ(200, kruskals(4, from, to, weights));
}
/*
 * https://www.hackerrank.com/challenges/dijkstrashortreach/problem
 * 100%
 */
class ShortestPathsTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<vector<size_t>>, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_nodes = get<1>(GetParam());
		_edges = get<2>(GetParam());
		_start = get<3>(GetParam());
		for (typename vector<vector<size_t>>::iterator it = _edges.begin(); it != _edges.end(); it++)
			_graph.AddUndirectedEdge((*it)[0], (*it)[1], (*it)[2]);
	}
	vector<long> ShortestPathsTest()
	{
		vector<long> result(_nodes - 1, -1);
		_graph.Dijkstra(_start, result);
		return result;
	}

protected:
	Graph<size_t, size_t> _graph;
	vector<long> _expected;
	size_t _nodes, _start;
	vector<vector<size_t>> _edges;
};
TEST_P(ShortestPathsTestFixture, ShortestPathsTests)
{
	ASSERT_EQ(this->_expected, this->ShortestPathsTest());
}
INSTANTIATE_TEST_SUITE_P(
	ShortestPathsTests,
	ShortestPathsTestFixture,
	::testing::Values(make_tuple(vector<long>{10, 16, 8, -1}, 5, vector<vector<size_t>>{{1, 2, 10}, {1, 3, 6}, {2, 4, 8}}, 2), make_tuple(vector<long>{24, 3, 15}, 4, vector<vector<size_t>>{{1, 2, 24}, {1, 4, 20}, {3, 1, 3}, {4, 3, 12}}, 1),
					  make_tuple(vector<long>{20, 25, 25, 68, 86, 39, 22, 70, 36, 53, 91, 35, 88, 27, 30, 43, 54, 74, 41}, 20,
								 vector<vector<size_t>>{{1, 7, 45}, {2, 14, 15}, {3, 7, 29}, {4, 1, 48}, {5, 1, 66}, {6, 7, 17}, {7, 14, 15}, {8, 14, 43}, {9, 1, 27}, {10, 1, 33}, {11, 14, 64}, {12, 14, 27}, {13, 7, 66}, {14, 7, 54}, {15, 14, 56}, {16, 7, 21}, {17, 1, 20}, {18, 1, 34}, {19, 7, 52}, {20, 14, 14}, {9, 14, 9}, {15, 1, 39}, {12, 1, 24}, {9, 1, 16}, {1, 2, 33}, {18, 1, 46}, {9, 1, 28}, {15, 14, 3}, {12, 1, 27}, {1, 2, 5}, {15, 1, 34}, {1, 2, 28}, {9, 7, 16}, {3, 7, 23}, {9, 7, 21}, {9, 14, 19}, {3, 1, 20}, {3, 1, 5}, {12, 14, 19}, {3, 14, 2}, {12, 1, 46}, {3, 14, 5}, {9, 14, 44}, {6, 14, 26}, {9, 14, 16}, {9, 14, 34}, {6, 7, 42}, {3, 14, 27}, {1, 7, 9}, {1, 7, 41}, {15, 14, 19}, {12, 7, 13}, {3, 7, 10}, {1, 7, 2}}, 17)));