#include "pch.h"
using namespace std;
/*
 * https://www.hackerrank.com/challenges/kruskalmstrsub/problem
 * Kruskal(from, to, weight): from[i] - to[i] is an undirected edge of weight weight[i]
 */
class KruskalTestFixture : public testing::TestWithParam<tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expectedWeight = get<0>(GetParam());
		_expectedTrees = get<1>(GetParam());
		_from = get<2>(GetParam());
		_to = get<3>(GetParam());
		_weights = get<4>(GetParam());
	}
	KruskalResult<size_t, long> KruskalTest()
	{
		return Kruskal(_from, _to, _weights);
	}

protected:
	long _expectedWeight;
	size_t _expectedTrees;
	vector<size_t> _from, _to;
	vector<long> _weights;
};
TEST_P(KruskalTestFixture, KruskalTests)
{
	KruskalResult<size_t, long> result = this->KruskalTest();
	ASSERT_EQ(this->_expectedWeight, result.weight);
	ASSERT_EQ(this->_expectedTrees, result.trees);
	ASSERT_EQ(this->_expectedTrees <= 1, result.Connected());
	set<size_t> vertices(this->_from.begin(), this->_from.end());
	vertices.insert(this->_to.begin(), this->_to.end());
	ASSERT_EQ(vertices.size() - result.trees, result.edges.size()); // Each edge taken merges two trees into one
}
// Columns: expected total weight, expected number of trees (1: connected), from, to, weight
INSTANTIATE_TEST_SUITE_P(
	KruskalTests,
	KruskalTestFixture,
	::testing::Values(make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(12, 1, vector<size_t>{1, 1, 4, 2, 3, 3}, vector<size_t>{2, 3, 1, 4, 2, 4}, vector<long>{5, 3, 6, 7, 4, 5}),
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(200, 1, vector<size_t>{1, 3, 4, 1, 3}, vector<size_t>{2, 2, 3, 4, 1}, vector<long>{1, 150, 99, 100, 200}),
					  // No edges: no vertices, so no trees
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(0, 0, vector<size_t>{}, vector<size_t>{}, vector<long>{}),
					  // A single edge is the whole tree
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(7, 1, vector<size_t>{1}, vector<size_t>{2}, vector<long>{7}),
					  // Parallel edges: the cheaper one is taken, and the other would close a cycle
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(3, 1, vector<size_t>{1, 1}, vector<size_t>{2, 2}, vector<long>{5, 3}),
					  // A self-loop never joins two trees, so even a very cheap one is skipped
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(4, 1, vector<size_t>{1, 1}, vector<size_t>{1, 2}, vector<long>{-10, 4}),
					  // Negative weights are fine: there is no cycle to go round in a tree
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(-4, 1, vector<size_t>{1, 2, 1}, vector<size_t>{2, 3, 3}, vector<long>{-3, -1, 2}),
					  // Disconnected: the minimum spanning forest, one tree per part (1 - 2 and 3 - 4)
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(3, 2, vector<size_t>{1, 3}, vector<size_t>{2, 4}, vector<long>{1, 2}),
					  // Ties: any 3 of the 4 equal edges of the square 1 - 2 - 3 - 4 - 1 make a tree
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(3, 1, vector<size_t>{1, 2, 3, 4}, vector<size_t>{2, 3, 4, 1}, vector<long>{1, 1, 1, 1}),
					  // Wikipedia's Kruskal example, with vertices A .. G renumbered 1 .. 7
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(39, 1, vector<size_t>{1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 6}, vector<size_t>{2, 4, 3, 4, 5, 5, 5, 6, 6, 7, 7}, vector<long>{7, 5, 8, 9, 7, 5, 15, 6, 8, 9, 11}),
					  // Roads in HackerLand sample, with weights 2^C: the tree is 4 - 5 (1), 3 - 2 (2), 4 - 2 (4) and 2 - 1 (8)
					  make_tuple<long, size_t, vector<size_t>, vector<size_t>, vector<long>>(15, 1, vector<size_t>{1, 4, 2, 3, 4, 4}, vector<size_t>{3, 5, 1, 2, 3, 2}, vector<long>{32, 1, 8, 2, 16, 4})));
static vector<tuple<size_t, size_t, long>> Edges(vector<Edge<size_t, long>> const &tree)
{
	vector<tuple<size_t, size_t, long>> result;
	for (Edge<size_t, long> const &edge : tree)
		result.emplace_back(edge.node1, edge.node2, edge.weight);
	return result;
}
// The chosen edges, cheapest first
TEST(KruskalTests, KruskalTreeTest)
{
	KruskalResult<size_t, long> result = Kruskal<size_t, long>({1, 4, 2, 3, 4, 4}, {3, 5, 1, 2, 3, 2}, {32, 1, 8, 2, 16, 4});
	ASSERT_EQ((vector<tuple<size_t, size_t, long>>{{4, 5, 1}, {3, 2, 2}, {4, 2, 4}, {2, 1, 8}}), Edges(result.edges));
	// Equal weights keep their input order: 1 - 2 (5) is considered before 3 - 4 (5), and skipped because 1 and 2 are already joined
	result = Kruskal<size_t, long>({1, 1, 4, 2, 3, 3}, {2, 3, 1, 4, 2, 4}, {5, 3, 6, 7, 4, 5});
	ASSERT_EQ((vector<tuple<size_t, size_t, long>>{{1, 3, 3}, {3, 2, 4}, {3, 4, 5}}), Edges(result.edges));
	// A forest: one tree per connected part, so 4 vertices in 2 parts give 2 edges, not 3
	result = Kruskal<size_t, long>({1, 3}, {2, 4}, {1, 2});
	ASSERT_FALSE(result.Connected());
	ASSERT_EQ((vector<tuple<size_t, size_t, long>>{{1, 2, 1}, {3, 4, 2}}), Edges(result.edges));
	// Three parts: 1 - 2, 3 on its own (only a self-loop) and 4 - 5
	result = Kruskal<size_t, long>({1, 3, 4}, {2, 3, 5}, {1, 1, 1});
	ASSERT_EQ(3, result.trees);
	ASSERT_EQ(2, result.weight);
}
// The weight type is the caller's, independent of the vertex type: signed, unsigned, floating point or 128-bit
TEST(KruskalTests, KruskalWeightTypesTest)
{
	KruskalResult<int, int> ints = Kruskal(vector<int>{-1, 0, -1}, vector<int>{0, 1, 1}, vector<int>{-5, -2, 3});
	ASSERT_EQ(-7, ints.weight);
	ASSERT_TRUE(ints.Connected());
	KruskalResult<size_t, size_t> unsignedWeights = Kruskal(vector<size_t>{1, 2, 1}, vector<size_t>{2, 3, 3}, vector<size_t>{10, 20, 15});
	ASSERT_EQ(25, unsignedWeights.weight);
	KruskalResult<size_t, double> doubles = Kruskal(vector<size_t>{1, 2, 1}, vector<size_t>{2, 3, 3}, vector<double>{0.5, 0.25, 1.0});
	ASSERT_DOUBLE_EQ(0.75, doubles.weight);
#ifdef __SIZEOF_INT128__
	// Weights far beyond 64 bits: 2^100 + 2^101
	int128_t two100 = (int128_t)1 << 100;
	KruskalResult<size_t, int128_t> big = Kruskal(vector<size_t>{1, 2, 1}, vector<size_t>{2, 3, 3}, vector<int128_t>{two100, two100 * 2, two100 * 4});
	ASSERT_TRUE(big.weight == two100 * 3);
#endif
}
// from, to and weight must be the same length. Before, a shorter from or to was read out of bounds
TEST(KruskalTests, KruskalMismatchedSizesTest)
{
	ASSERT_THROW((Kruskal<size_t, long>({1, 2}, {2}, {1, 1})), invalid_argument);
	ASSERT_THROW((Kruskal<size_t, long>({1}, {2}, {1, 1})), invalid_argument);
	ASSERT_THROW((Kruskal<size_t, long>({1, 2}, {2, 3}, {1})), invalid_argument);
}
