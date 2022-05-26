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
	a = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	Tree<long> tree0(a, TreeType::BinarySearch);
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
TEST(BinarySearchTreeTests, BinarySearchTreeFindSumTest)
{
	vector<long> a;
	vector<string> result, expected;
	a = {50, -100, 0, 10, -50, 60, 100, 75, 150};
	Tree<long> tree(a, TreeType::BinarySearch);
	ASSERT_TRUE(tree.isValidBST());
	ASSERT_EQ(9, tree.Count());
	ASSERT_EQ(-100, tree.Min());
	ASSERT_EQ(150, tree.Max());
	/*
Binary Search Tree (tree1) content:
Level 0:                              50
Level 1:                        0(50)            100(50)
Level 2:                -50(0)     10(0)   75(100)       150(100)
Level 3:        -100(-50)               60(75)
	*/
	tree.FindSum(tree.Root(), -100, result);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());
	expected.clear();
	expected = {"-100", "50 0 -50 -100"};
	ASSERT_EQ(expected, result);

	result.clear();
	tree.FindSum(tree.Root(), 150, result);
	ASSERT_FALSE(result.empty());
	expected.clear();
	expected = {"50 100", "150"};
	ASSERT_EQ(expected, result);
	result.clear();

	result.clear();
	tree.FindSum(tree.Root(), 110, result);
	ASSERT_TRUE(result.empty());
	expected.clear();
	ASSERT_EQ(expected, result);
	result.clear();
}
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
TEST(BinarySearchTreeTests, BinarySearchTreekthSmallestAndLargestTests)
{
	vector<long> a;
	shared_ptr<Node<long>> node, node1, node2, node3;
	a = {50, -100, 0, 10, -50, 60, 100, 75, 150};
	Tree<long> tree(a, TreeType::BinarySearch);
	ASSERT_TRUE(tree.isValidBST());
	ASSERT_EQ(9, tree.Count());
	ASSERT_EQ(-100, tree.Min());
	ASSERT_EQ(150, tree.Max());
	// 50,-100,0,10,-50,60,100,75,150
	// -100,-50,0,10,50,60,75,100,150
	ASSERT_EQ(0, tree.kthSmallest(3));
	ASSERT_EQ(75, tree.kthLargest(3));
	cout << "Tree2 content (= Tree1): " << endl;
	tree.PrintTree();
	cout << endl;
}