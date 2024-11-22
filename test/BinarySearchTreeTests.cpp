#include "pch.h"
using namespace std;
TEST(BinarySearchTreeTests, BinarySearchTreeTest)
{
	vector<long> a, b;
	vector<string> result, expected;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	Tree<long> subtree((long)0);
	subtree.InsertItem(-50);
	subtree.InsertItem(10);

	Tree<long> subtree1((long)0);
	subtree1.InsertItem(50);
	subtree1.InsertItem(60);

	Tree<long> subtree2(50);
	subtree2.InsertItem(-100);
	subtree2.InsertItem(60);

	a.clear();
	b.clear();
	a = ranges::iota_view(0, 9) | ranges::to<vector<long>>();
	Tree<long>
		tree0(a, TreeType::BinarySearch);
	ASSERT_TRUE(tree0.isValidBST());
	ASSERT_EQ(9, tree0.Count());
	ASSERT_EQ(0, tree0.Min());
	ASSERT_EQ(8, tree0.Max());
	for (size_t i = tree0.Min(); i <= tree0.Max(); i++)
		ASSERT_EQ(i, tree0.NextMin());
	ASSERT_FALSE(tree0.HasNextMin());
	for (long i = tree0.Max(); i >= tree0.Min(); i--)
		ASSERT_EQ(i, tree0.NextMax());
	ASSERT_FALSE(tree0.HasNextMax());
	result.clear();
	vector<size_t> levelNodeCount = tree0.GetLevelNodeCount();
	ASSERT_FALSE(levelNodeCount.empty());
	ASSERT_EQ(4, levelNodeCount.size());
	ASSERT_EQ(1, levelNodeCount[0]); // 4
	ASSERT_EQ(2, levelNodeCount[1]); // 2 7
	ASSERT_EQ(4, levelNodeCount[2]); // 1 3 6 8
	ASSERT_EQ(2, levelNodeCount[3]); // 0 5
	tree0.Serialize(tree0.Root(), b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(b.size(), a.size());
	ASSERT_EQ(b, a);
	cout << "Binary Search Tree content: " << endl;
	tree0.PrintTree();
	cout << endl;
	tree0.PrintTreeColumns();

	a.clear();
	b.clear();
	a = {50, -100, 0, 10, -50, 60, 100, 75, 150};
	Tree<long> tree1(a, TreeType::BinarySearch);
	ASSERT_TRUE(tree1.isValidBST());
	ASSERT_EQ(9, tree1.Count());
	ASSERT_EQ(-100, tree1.Min());
	ASSERT_EQ(150, tree1.Max());
	result.clear();
	tree1.Serialize(tree1.Root(), b);
	levelNodeCount = tree1.GetLevelNodeCount();
	ASSERT_FALSE(levelNodeCount.empty());
	ASSERT_EQ(4, levelNodeCount.size());
	ASSERT_EQ(1, levelNodeCount[0]); // 50
	ASSERT_EQ(2, levelNodeCount[1]); // 0 100
	ASSERT_EQ(4, levelNodeCount[2]); // -50 10 75 150
	ASSERT_EQ(2, levelNodeCount[3]); // -100 60
	ASSERT_EQ(-100, tree1.NextMin());
	ASSERT_EQ(-50, tree1.NextMin());
	ASSERT_EQ(0, tree1.NextMin());
	ASSERT_EQ(10, tree1.NextMin());
	ASSERT_EQ(50, tree1.NextMin());
	ASSERT_EQ(60, tree1.NextMin());
	ASSERT_EQ(75, tree1.NextMin());
	ASSERT_EQ(100, tree1.NextMin());
	ASSERT_EQ(150, tree1.NextMin());
	ASSERT_FALSE(tree1.HasNextMin());
	ASSERT_EQ(150, tree1.NextMax());
	ASSERT_EQ(100, tree1.NextMax());
	ASSERT_EQ(75, tree1.NextMax());
	ASSERT_EQ(60, tree1.NextMax());
	ASSERT_EQ(50, tree1.NextMax());
	ASSERT_EQ(10, tree1.NextMax());
	ASSERT_EQ(0, tree1.NextMax());
	ASSERT_EQ(-50, tree1.NextMax());
	ASSERT_EQ(-100, tree1.NextMax());
	ASSERT_FALSE(tree1.HasNextMax());
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(b.size(), a.size());
	ASSERT_EQ(b, a);
	cout << "Binary Search Tree (tree1) content: " << endl;
	tree1.PrintTree();
	cout << endl;
	tree1.PrintTreeColumns();
	long min = tree1.MinDiffInBST();
	ASSERT_EQ(10, min);
	cout << "Subtree (subtree) content: " << endl;
	subtree.PrintTree();
	ASSERT_TRUE(tree1.SubTree(tree1.Root(), subtree.Root()));

	cout << "Subtree1 content: " << endl;
	subtree1.PrintTree();
	cout << endl;
	ASSERT_FALSE(tree1.SubTree(tree1.Root(), subtree1.Root()));

	cout << "Subtree2 content: " << endl;
	subtree2.PrintTree();
	cout << endl;
	ASSERT_FALSE(tree1.SubTree(tree1.Root(), subtree2.Root()));

	ASSERT_EQ(3, tree1.MinDepth(tree1.Root()));
	ASSERT_EQ(4, tree1.MaxDepth(tree1.Root()));
	ASSERT_TRUE(tree1.IsBalancedTree());
}
class BinarySearchTreeFindSumTestFixture : public testing::TestWithParam<tuple<vector<string>, long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_sum = get<1>(GetParam());
		_data = get<2>(GetParam());
		_tree.LoadData(_data, TreeType::BinarySearch);
	}
	/*
Binary Search Tree (tree1) content:
Level 0:                              50
Level 1:                        0(50)            100(50)
Level 2:                -50(0)     10(0)   75(100)       150(100)
Level 3:        -100(-50)               60(75)
	*/
	vector<string> BinarySearchTreeFindSumTest()
	{
		vector<string> result;
		_tree.FindSum(_tree.Root(), _sum, result);
		return result;
	}

protected:
	Tree<long> _tree;
	vector<string> _expected;
	vector<long> _data;
	long _sum;
};
TEST_P(BinarySearchTreeFindSumTestFixture, BinarySearchTreeFindSumTests)
{
	ASSERT_TRUE(this->_tree.isValidBST());
	ASSERT_EQ(this->_data.size(), this->_tree.Count());
	ASSERT_EQ(*ranges::min_element(this->_data), this->_tree.Min());
	ASSERT_EQ(*ranges::max_element(this->_data), this->_tree.Max());
	ASSERT_EQ(this->_expected, this->BinarySearchTreeFindSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	BinarySearchTreeFindSumTests,
	BinarySearchTreeFindSumTestFixture,
	::testing::Values(make_tuple(vector<string>{"-100", "50 0 -50 -100"}, -100, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150}), make_tuple(vector<string>{"50 100", "150"}, 150, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150}), make_tuple(vector<string>{}, 110, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150})));

TEST(BinarySearchTreeTests, BinarySearchTreeInOrderSuccessorTest)
{
	vector<long> a, b;
	vector<string> result, expected;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	a = {50, -100, 0, 10, -50, 60, 100, 75, 150};
	Tree<long> tree(a, TreeType::BinarySearch);
	ASSERT_TRUE(tree.isValidBST());
	ASSERT_EQ(9, tree.Count());
	ASSERT_EQ(-100, tree.Min());
	ASSERT_EQ(150, tree.Max());
	tree.GetNodes(nodes);
	ASSERT_FALSE(nodes.empty());
	cout << "Binary Search Tree content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	/*
Binary Search Tree (tree1) content:
Level 0:                                50
Level 1:                        0(50)          100(50)
Level 2:                -50(0)     10(0)   75(100)       150(100)
Level 3:        -100(-50)               60(75)
	*/
	shared_ptr<Node<long>> node;
	node = tree.FindNode(-50);
	ASSERT_TRUE(node);
	ASSERT_EQ(0, tree.InOrderSuccessor(node)->Item());
	node = tree.FindNode(50);
	ASSERT_TRUE(node);
	ASSERT_EQ(60, tree.InOrderSuccessor(node)->Item());
	nodes.clear();
}
TEST(BinarySearchTreeTests, BinarySearchTreeCommonAncestorTest)
{
	vector<long> a;
	shared_ptr<Node<long>> node, node1, node2, node3;
	a = {50, -100, 0, 10, -50, 60, 100, 75, 150};
	Tree<long> tree(a, TreeType::BinarySearch);
	ASSERT_TRUE(tree.isValidBST());
	ASSERT_EQ(9, tree.Count());
	ASSERT_EQ(-100, tree.Min());
	ASSERT_EQ(150, tree.Max());
	node = tree.FindNode(-50);
	ASSERT_TRUE(node);
	node1 = tree.FindNode(10);
	ASSERT_TRUE(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_EQ(node2, node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree.FindNode(75);
	ASSERT_TRUE(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_EQ(node2, node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree.FindNode(60);
	ASSERT_TRUE(node);
	node1 = tree.FindNode(75);
	ASSERT_TRUE(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_EQ(node2, node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
}
template <typename T>
class BinarySearchTreekthSmallestLargestTestFixture
{
public:
	void SetUp(T expected, size_t k, vector<T> data)
	{
		_expected = expected;
		_data = data;
		_k = k;
		_tree.LoadData(_data, TreeType::BinarySearch);
	}

protected:
	Tree<long> _tree;
	T _expected;
	size_t _k;
	vector<T> _data;
};

class BinarySearchTreekthSmallestTestFixture : public BinarySearchTreekthSmallestLargestTestFixture<long>, public testing::TestWithParam<tuple<long, size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		BinarySearchTreekthSmallestLargestTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	/*
Binary Search Tree (tree1) content:
Level 0:                              50
Level 1:                        0(50)            100(50)
Level 2:                -50(0)     10(0)   75(100)       150(100)
Level 3:        -100(-50)               60(75)
	// 50,-100,0,10,-50,60,100,75,150
	// -100,-50,0,10,50,60,75,100,150
	*/
	long BinarySearchTreekthSmallestTest()
	{
		return _tree.kthSmallest(_k);
	}
};
TEST_P(BinarySearchTreekthSmallestTestFixture, BinarySearchTreekthSmallestTests)
{
	ASSERT_TRUE(this->_tree.isValidBST());
	ASSERT_EQ(this->_data.size(), this->_tree.Count());
	ASSERT_EQ(*ranges::min_element(this->_data), this->_tree.Min());
	ASSERT_EQ(*ranges::max_element(this->_data), this->_tree.Max());
	ASSERT_EQ(this->_expected, this->BinarySearchTreekthSmallestTest());
}
INSTANTIATE_TEST_SUITE_P(
	BinarySearchTreekthSmallestTests,
	BinarySearchTreekthSmallestTestFixture,
	::testing::Values(make_tuple(0, 3, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150}), make_tuple(50, 5, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150}), make_tuple(75, 7, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150})));
class BinarySearchTreekthLargestTestFixture : public BinarySearchTreekthSmallestLargestTestFixture<long>, public testing::TestWithParam<tuple<long, size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		BinarySearchTreekthSmallestLargestTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	/*
Binary Search Tree (tree1) content:
Level 0:                              50
Level 1:                        0(50)            100(50)
Level 2:                -50(0)     10(0)   75(100)       150(100)
Level 3:        -100(-50)               60(75)
	// 50,-100,0,10,-50,60,100,75,150
	// -100,-50,0,10,50,60,75,100,150
	*/
	long BinarySearchTreekthLargestTest()
	{
		return _tree.kthLargest(_k);
	}
};
TEST_P(BinarySearchTreekthLargestTestFixture, BinarySearchTreekthLargestTests)
{
	ASSERT_TRUE(this->_tree.isValidBST());
	ASSERT_EQ(this->_data.size(), this->_tree.Count());
	ASSERT_EQ(*ranges::min_element(this->_data), this->_tree.Min());
	ASSERT_EQ(*ranges::max_element(this->_data), this->_tree.Max());
	ASSERT_EQ(this->_expected, this->BinarySearchTreekthLargestTest());
}
INSTANTIATE_TEST_SUITE_P(
	BinarySearchTreekthLargestTests,
	BinarySearchTreekthLargestTestFixture,
	::testing::Values(make_tuple(75, 3, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150}), make_tuple(50, 5, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150}), make_tuple(0, 7, vector<long>{50, -100, 0, 10, -50, 60, 100, 75, 150})));
