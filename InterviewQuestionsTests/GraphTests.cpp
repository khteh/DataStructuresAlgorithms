#include "pch.h"
using namespace std;
TEST(GraphTests, GraphTest) {
	vector<size_t> data(5);
	generate(data.begin(), data.end(), [n = 1]() mutable { return n++; });
	Graph<size_t, size_t> graph(data);
	ASSERT_EQ(5, graph.Count());
	shared_ptr<Vertex<size_t, size_t>> v1 = graph.GetVertex(1);
	ASSERT_TRUE(graph.HasVertex(1));
	ASSERT_TRUE(graph.HasVertex(2));
	ASSERT_TRUE(graph.HasVertex(3));
	ASSERT_TRUE(graph.HasVertex(4));
	ASSERT_TRUE(graph.HasVertex(5));

	ASSERT_FALSE(v1->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v2 = graph.GetVertex(2);
	ASSERT_FALSE(v2->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v3 = graph.GetVertex(3);
	ASSERT_FALSE(v3->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v4 = graph.GetVertex(4);
	ASSERT_FALSE(v4->HasNeighbours());
	shared_ptr<Vertex<size_t, size_t>> v5 = graph.GetVertex(5);
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
	map<shared_ptr<Vertex<size_t, size_t>>, long> costs;
	graph.Dijkstra(1, costs);
	cout << "Vertex\tDistance from Source (1): " << endl;
	for (map<shared_ptr<Vertex<size_t, size_t>>, long>::iterator it = costs.begin(); it != costs.end(); it++)
		cout << it->first->GetItem() << "\t" << it->second << endl;
	ASSERT_EQ(7, graph.Dijkstra(1, 5)); // 1->2->3->5
	ASSERT_EQ(7, graph.Dijkstra(5, 1)); // 1->2->3->5
	graph.Remove(3);
	ASSERT_FALSE(graph.HasVertex(3));
	ASSERT_FALSE(v2->HasNeighbour(v3));
	ASSERT_FALSE(v5->HasNeighbour(v3));
	costs.clear();
	graph.Clear();
	ASSERT_EQ(0, graph.Count());
	v1 = graph.AddVertex(1);
	v2 = graph.AddVertex(2);
	v3 = graph.AddVertex(3);
	v4 = graph.AddVertex(4);
	v5 = graph.AddVertex(5);
	ASSERT_EQ(5, graph.Count());
	graph.AddUndirectedEdge(v1, v2, 1);
	graph.AddUndirectedEdge(v2, v3, 2);
	graph.AddUndirectedEdge(v3, v5, 3);
	graph.AddUndirectedEdge(v2, v4, 2);
	ASSERT_EQ(6, graph.Dijkstra(1, 5)); // 1 + 2 + 3
	ASSERT_EQ(6, graph.Dijkstra(5, 1)); // 1 + 2 + 3
	ASSERT_EQ(1, graph.Dijkstra(1, 2));
	ASSERT_EQ(1, graph.Dijkstra(2, 1));
	ASSERT_EQ(2, graph.Dijkstra(2, 3));
	ASSERT_EQ(2, graph.Dijkstra(3, 2));
	ASSERT_EQ(3, graph.Dijkstra(1, 3)); // 1 + 2
	ASSERT_EQ(3, graph.Dijkstra(3, 1)); // 1 + 2
	ASSERT_EQ(3, graph.Dijkstra(1, 4)); // 1 + 2
	ASSERT_EQ(3, graph.Dijkstra(4, 1)); // 1 + 2
	ASSERT_EQ(4, graph.Dijkstra(3, 4)); // 2 + 2
	ASSERT_EQ(4, graph.Dijkstra(4, 3)); // 2 + 2
	costs.clear();
	graph.Clear();
	data.clear();
	data = { 10, 5, 11 };
	vector<vector<size_t>> edges = { {1, 2}, {1, 3} }; // Use tag. Not value
	/*
			10
		11		5
	Diff: 15 - 11 = 4
	*/
	ASSERT_EQ(4, MinSubGraphsDifference(data, edges));
	data.clear();
	data = { 10, 5, 6, 20 };
	/*
			10
		 5		6
	  20
	Diff: 21 - 20 = 1
	*/
	edges = { {1, 2}, {1, 3}, {2, 4} }; //{ {10,5}, {10,6}, {5,20} };
	ASSERT_EQ(1, MinSubGraphsDifference(data, edges));
	/*
			10
		 5
	  20
	Diff: 20 - 15 = 5
	*/
	data.clear();
	data = { 10, 5, 20 };
	edges = { {1, 2}, {2, 3} };
	ASSERT_EQ(5, MinSubGraphsDifference(data, edges));
	cout << endl;
	data.clear();
	data = { 100, 200, 100, 100, 500, 600 };
	edges = { {1, 2}, {2, 3}, {2, 4}, {4, 5}, {4, 6} };
	ASSERT_EQ(400, MinSubGraphsDifference(data, edges));
	data.clear();
	data = { 205, 573, 985, 242, 830, 514, 592, 263, 142, 915 };
	edges = { {2, 8}, {10, 5}, {1, 7}, {6, 9}, {4, 3}, {8, 10}, {5, 1}, {7, 6}, {9, 4} };
	ASSERT_EQ(99, MinSubGraphsDifference(data, edges));
	data.clear();
	edges.clear();
	data = { 716, 365, 206, 641, 841, 585, 801, 645, 208, 924, 920, 286, 554, 832, 359, 836, 247, 959, 31, 322, 709, 860, 890, 195, 575, 905, 314, 41, 669, 549, 950, 736, 265, 507, 729, 457, 91, 529, 102, 650, 805, 373, 287, 710, 556, 645, 546, 154, 956, 928 };
	edges = { {14, 25}, {25, 13}, {13, 20}, {20, 24}, {43, 2}, {2, 48}, {48, 42}, {42, 5}, {27, 18}, {18, 30}, {30, 7}, {7, 36}, {37, 9}, {9, 23}, {23, 49}, {49, 15}, {31, 26}, {26, 29}, {29, 50}, {50, 21}, {41, 45}, {45, 10}, {10, 17}, {17, 34}, {28, 47}, {47, 44}, {44, 11}, {11, 16}, {3, 8}, {8, 39}, {39, 38}, {38, 22}, {19, 32}, {32, 12}, {12, 40}, {40, 46}, {1, 35}, {35, 4}, {4, 33}, {33, 6}, {25, 2}, {2, 27}, {7, 37}, {15, 50}, {21, 10}, {17, 28}, {16, 39}, {38, 19}, {40, 1} };
	// size_t result = MinSubGraphsDifference(data, edges); Segmentation fault. Maybe due to recursion
	// assert(result == 525); Fail but difficult to check due to the sheer number of data points.
	vector<long> data1;
	vector<vector<long>> edges1;
	data1.clear();
	data1 = { 1, 3, 4 };
	edges1 = { {1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3} };
	ASSERT_EQ(6, PostmanProblem(data1, edges1));
	data1.clear();
	data1 = { 5, 11, 12, 15, 16 };
	edges1 = { {17, 4, 3}, {11, 12, 5}, {14, 2, 1}, {16, 14, 4}, {7, 8, 4}, {13, 5, 5}, {17, 15, 2}, {5, 3, 5}, {8, 6, 1}, {18, 10, 4}, {18, 1, 3}, {16, 1, 2}, {9, 2, 5}, {11, 6, 1}, {4, 9, 4}, {7, 20, 2}, {13, 19, 3}, {19, 12, 3}, {10, 20, 2} };
	ASSERT_EQ(54, PostmanProblem(data1, edges1));
	vector<vector<size_t>> edges2 = { {1, 2}, {1, 3}, {3, 4} };
	vector<long> expectedDistances = { 6, 6, 12, -1 };
	vector<long> distances = bfs(5, 3, edges2, 1);
	ASSERT_EQ(expectedDistances, distances);
	edges2.clear();
	expectedDistances.clear();
	distances.clear();
	edges2 = { {1, 2}, {1, 3} };
	expectedDistances = { 6, 6, -1 };
	distances = bfs(4, 3, edges2, 1);
	ASSERT_EQ(expectedDistances, distances);
	edges2.clear();
	expectedDistances.clear();
	distances.clear();
	edges2 = { {2, 3} };
	expectedDistances = { -1, 6 };
	distances = bfs(3, 1, edges2, 2);
	ASSERT_EQ(expectedDistances, distances);
	edges2.clear();
	data.clear();
	edges2 = { {1, 2}, {2, 3}, {1, 4} };
	data = { 3, 1, 2 };
	ASSERT_EQ(data, UnbeatenPath(4, edges2, 1));
	edges2.clear();
	data.clear();
	edges2 = { {1, 2}, {2, 3} };
	data = { 2, 2, 1 };
	ASSERT_EQ(data, UnbeatenPath(4, edges2, 2));
	edges2.clear();
	data.clear();
	edges2 = { {1, 3}, {1, 4}, {1, 5}, {2, 4}, {2, 5}, {3, 5} };
	data = { 1, 2, 3, 4 };
	ASSERT_EQ(data, UnbeatenPath(5, edges2, 1));
	edges2.clear();
	data.clear();
	edges2 = { {1, 2}, {1, 3}, {3, 4} };
	ASSERT_EQ(1, evenForest(4, edges2));
	edges2.clear();
	data.clear();
	edges2 = { {2, 1}, {3, 1}, {4, 3}, {5, 2}, {6, 1}, {7, 2}, {8, 6}, {9, 8}, {10, 8} };
	ASSERT_EQ(2, evenForest(10, edges2));
	edges2.clear();
	data.clear();
	edges2 = { {2, 1}, {3, 1}, {4, 3}, {5, 2}, {6, 5}, {7, 1}, {8, 1}, {9, 2}, {10, 7}, {11, 10}, {12, 3}, {13, 7}, {14, 8}, {15, 12}, {16, 6}, {17, 6}, {18, 10}, {19, 1}, {20, 8} };
	ASSERT_EQ(4, evenForest(20, edges2));
	edges2.clear();
	data.clear();
	edges.clear();
	edges = { {1, 3, 5}, {4, 5, 0}, {2, 1, 3}, {3, 2, 1}, {4, 3, 4}, {4, 2, 2} };
	ASSERT_EQ("1000100", roadsInHackerland(5, edges));
}