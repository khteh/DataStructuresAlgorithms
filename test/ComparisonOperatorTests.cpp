#include "pch.h"
using namespace std;
/*
 * Comparisons of the types whose operators were replaced by operator<=> (and operator==).
 * <, <=, > and >= are rewritten from <=>, and != from ==, so each test checks they all agree.
 */
TEST(ComparisonOperatorTests, PositionTest)
{
	// Row first, then column
	Position a(0, 5), b(1, 0), c(1, 0);
	ASSERT_TRUE(a < b);
	ASSERT_FALSE(a > b); // Was true: the old operator> compared row == row, which is always true
	ASSERT_TRUE(b > a);
	ASSERT_TRUE(a <= b);
	ASSERT_TRUE(b >= a);
	ASSERT_TRUE(b == c);
	ASSERT_FALSE(b != c);
	ASSERT_TRUE(a != b);
	ASSERT_TRUE(Position(1, 2) < Position(1, 3)); // Same row: the column decides
	ASSERT_EQ(strong_ordering::equal, b <=> c);
	set<position_t> positions{{1, 0}, {0, 5}, {0, 1}, {1, 0}};
	ASSERT_EQ((vector<position_t>{{0, 1}, {0, 5}, {1, 0}}), vector<position_t>(positions.begin(), positions.end()));
}
TEST(ComparisonOperatorTests, ZigZagEscapeTest)
{
	// By value only
	zigzag_t one(0, 1), two(1, 2), anotherOne(5, 1);
	ASSERT_TRUE(one < two);
	ASSERT_FALSE(one > two); // Was true: the old operator> returned value < other.value
	ASSERT_TRUE(two > one);
	ASSERT_EQ(weak_ordering::equivalent, one <=> anotherOne); // Same value, different index
}
TEST(ComparisonOperatorTests, ZeroFactorsTest)
{
	// By min(two, five), the trailing zeros the value contributes, then by value
	zerofactors_t a{1, 3, 0}, b{2, 2, 0}, c{2, 5, 7}, d{5, 2, 9};
	ASSERT_TRUE(a < b);
	ASSERT_TRUE(b > a); // Was false: the old operator> compared max(two, five)
	ASSERT_FALSE(a > b);
	ASSERT_TRUE(c < d); // Same min(two, five): the value decides
	ASSERT_TRUE(d > c);
	ASSERT_EQ(weak_ordering::equivalent, (zerofactors_t{1, 3, 4} <=> zerofactors_t{3, 1, 4}));
}
TEST(ComparisonOperatorTests, TowerTest)
{
	// By top disc. An empty tower is greater than any non-empty one: any disc can be moved onto it
	Tower<long> small(0), large(1), empty(2), anotherEmpty(3), anotherSmall(4);
	large.Add(5);
	large.Add(3);
	small.Add(1);
	anotherSmall.Add(4);
	anotherSmall.Add(1);
	ASSERT_TRUE(small < large);
	ASSERT_TRUE(large > small);
	ASSERT_TRUE(small < empty); // Was false: the old operator< treated an empty rhs as never greater
	ASSERT_TRUE(empty > small);
	ASSERT_FALSE(empty < small);
	ASSERT_TRUE(large < empty);
	ASSERT_EQ(weak_ordering::equivalent, empty <=> anotherEmpty);
	ASSERT_EQ(weak_ordering::equivalent, small <=> anotherSmall); // Same top disc, different discs below
}
TEST(ComparisonOperatorTests, TweetItemTest)
{
	// <=> by timestamp only, while == compares all the fields
	TweetItem<size_t, size_t> first(1, 100);
	this_thread::sleep_for(1ms); // The timestamp comes from the system clock
	TweetItem<size_t, size_t> second(1, 200);
	ASSERT_TRUE(first < second);
	ASSERT_TRUE(second > first);
	ASSERT_TRUE(first <= second);
	ASSERT_TRUE(first == first);
	ASSERT_TRUE(first != second);
	set<TweetItem<size_t, size_t>, greater<TweetItem<size_t, size_t>>> latestFirst{first, second}; // As in Twitter::_tweets
	ASSERT_EQ(200, latestFirst.begin()->ID());
}
TEST(ComparisonOperatorTests, VertexTest)
{
	// <=> by item only, while == also compares the tag
	Vertex<long, long> a(1, 5), b(2, 5), c(3, 7), d(1, 5);
	ASSERT_TRUE(a < c);
	ASSERT_TRUE(c > a);
	ASSERT_FALSE(a < b);
	ASSERT_FALSE(a > b);
	ASSERT_EQ(weak_ordering::equivalent, a <=> b); // Same item, different tag...
	ASSERT_TRUE(a != b);						   // ...so equivalent, but not equal
	ASSERT_TRUE(a == d);
}
TEST(ComparisonOperatorTests, NodeTest)
{
	Node<long> three(3), five(5), anotherThree(3);
	ASSERT_TRUE(three < five);
	ASSERT_TRUE(five > three);
	ASSERT_TRUE(three <= anotherThree);
	ASSERT_TRUE(three == anotherThree);
	ASSERT_TRUE(three != five);
	// For double, the comparison is partial: NaN is unordered with everything
	Node<double> nan(numeric_limits<double>::quiet_NaN()), one(1.0);
	ASSERT_EQ(partial_ordering::unordered, nan <=> one);
	ASSERT_FALSE(nan < one);
	ASSERT_FALSE(nan > one);
	ASSERT_TRUE(Node<double>(0.5) < one);
}
TEST(ComparisonOperatorTests, DijkstraTest)
{
	DVertex<long> three(3), five(5), anotherThree(3);
	ASSERT_TRUE(three < five);
	ASSERT_TRUE(five >= three);
	ASSERT_TRUE(three == anotherThree);
	ASSERT_TRUE(three != five);
	// DEdge compares the vertex it points to, by pointer
	shared_ptr<DVertex<long>> vertex = make_shared<DVertex<long>>(1), other = make_shared<DVertex<long>>(1);
	DEdge<long> edge(vertex, 10), sameVertex(vertex, 20), otherVertex(other, 10);
	ASSERT_TRUE(edge == sameVertex); // Same vertex, different cost
	ASSERT_TRUE(edge != otherVertex); // Equal values, but a different vertex object
	ASSERT_EQ(vertex < other, edge < otherVertex);
	ASSERT_EQ(vertex > other, edge > otherVertex);
	set<DEdge<long>> edges{edge, sameVertex, otherVertex}; // As in DVertex::_edges: unique by vertex
	ASSERT_EQ(2, edges.size());
}
TEST(ComparisonOperatorTests, LinkedListTest)
{
	// <=> by length only, while == compares the head, tail and length
	LinkedList<long> shortList(vector<long>{1, 2}), longList(vector<long>{1, 2, 3}), sameLength(vector<long>{7, 8});
	ASSERT_TRUE(shortList < longList);
	ASSERT_TRUE(shortList <= longList);
	ASSERT_TRUE(longList > shortList);
	ASSERT_TRUE(longList >= shortList);
	ASSERT_EQ(weak_ordering::equivalent, shortList <=> sameLength);
	ASSERT_TRUE(shortList <= sameLength);
	ASSERT_TRUE(shortList >= sameLength);
	ASSERT_TRUE(shortList != sameLength); // Different nodes
	ASSERT_TRUE(shortList == shortList);
}
TEST(ComparisonOperatorTests, LongestMatchingWordWithDeletionStateTest)
{
	// By word only
	longestmatchingwordwithdeletion_state_t able(0, "able"), ale(3, "ale"), anotherAble(2, "able");
	ASSERT_TRUE(able < ale);
	ASSERT_TRUE(ale > able);
	ASSERT_EQ(weak_ordering::equivalent, able <=> anotherAble);
}
TEST(ComparisonOperatorTests, GCDExtendedEuclideanResultTest)
{
	// Defaulted ==: compares gcd, x and y
	ASSERT_TRUE((GCDExtendedEuclideanResult<long>(1, 2, 3) == GCDExtendedEuclideanResult<long>(1, 2, 3)));
	ASSERT_TRUE((GCDExtendedEuclideanResult<long>(1, 2, 3) != GCDExtendedEuclideanResult<long>(1, 2, 4)));
	ASSERT_TRUE((GCDExtendedEuclideanResult<long>(1, 2, 3) != GCDExtendedEuclideanResult<long>(9, 2, 3)));
}
