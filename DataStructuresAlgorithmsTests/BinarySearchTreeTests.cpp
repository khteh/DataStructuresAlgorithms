#include "pch.h"
using namespace std;
TEST(BinarySearchTreeTests, BinarySearchTreeTest) {
	vector<long> a, b;
	vector<string> result;
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
	a = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
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
	a = { 50, -100, 0, 10, -50, 60, 100, 75, 150 };
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
	cout << "Binary Search Tree content: " << endl;
	tree1.PrintTree();
	cout << endl;
	tree1.PrintTreeColumns();
	long min = tree1.MinDiffInBST();
	ASSERT_EQ(10, min);
	cout << endl
		<< "Binary Search Tree minimum diff between any 2 nodes: " << min << endl;
	cout << endl;
	cout << "Subtree content: " << endl;
	subtree.PrintTree();
	cout << endl;
	ASSERT_TRUE(tree1.SubTree(tree1.Root(), subtree.Root()));
	cout << (tree1.SubTree(tree1.Root(), subtree.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "Subtree1 content: " << endl;
	subtree1.PrintTree();
	cout << endl;
	ASSERT_TRUE(tree1.SubTree(tree1.Root(), subtree1.Root()));
	cout << (tree1.SubTree(tree1.Root(), subtree1.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "Subtree2 content: " << endl;
	subtree2.PrintTree();
	cout << endl;
	ASSERT_TRUE(tree1.SubTree(tree1.Root(), subtree2.Root()));
	cout << (tree1.SubTree(tree1.Root(), subtree2.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "MinDepth: " << tree1.MinDepth(tree1.Root()) << ", MaxDepth: " << tree1.MaxDepth(tree1.Root()) << " " << (tree1.IsBalancedTree() ? "balanced" : "Unbalanced") << endl;

	tree1.FindSum(tree1.Root(), -100, result);
	cout << "Sum -100 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << quoted(*it) << " ";
	cout << endl;
	result.clear();

	tree1.FindSum(tree1.Root(), 150, result);
	cout << "Sum 150 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << quoted(*it) << " ";
	cout << endl;
	result.clear();

	tree1.GetNodes(nodes);
	ASSERT_FALSE(nodes.empty());
	cout << "Binary Search Tree content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	shared_ptr<Node<long>> node, node1, node2, node3;
	node = tree1.FindNode(-50);
	ASSERT_TRUE(node);
	// assert(tree1.InOrderSuccessor(node)->Item() == 0);
	cout << "InOrder successor of -50: " << tree1.InOrderSuccessor(node)->Item() << endl;
	node = tree1.FindNode(50);
	ASSERT_TRUE(node);
	// assert(tree1.InOrderSuccessor(node)->Item() == 100);
	cout << "InOrder successor of 50: " << tree1.InOrderSuccessor(node)->Item() << endl;
	nodes.clear();

	node = tree1.FindNode(-50);
	ASSERT_TRUE(node);
	node1 = tree1.FindNode(10);
	ASSERT_TRUE(node1);
	node2 = tree1.CommonAncestor(node, node1);
	node3 = tree1.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_TRUE(node2 == node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree1.FindNode(75);
	ASSERT_TRUE(node1);
	node2 = tree1.CommonAncestor(node, node1);
	node3 = tree1.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_TRUE(node2 == node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree1.FindNode(60);
	ASSERT_TRUE(node);
	node1 = tree1.FindNode(75);
	ASSERT_TRUE(node1);
	node2 = tree1.CommonAncestor(node, node1);
	node3 = tree1.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_TRUE(node2 == node3);
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;

	Tree<long> tree2(tree1);
	ASSERT_EQ(tree2, tree1);
	ASSERT_TRUE(tree2.isValidBST());
	ASSERT_EQ(9, tree2.Count());
	ASSERT_EQ(-100, tree2.Min());
	ASSERT_EQ(150, tree2.Max());
	// 50,-100,0,10,-50,60,100,75,150
	// -100,-50,0,10,50,60,75,100,150
	ASSERT_EQ(0, tree2.kthSmallest(3));
	ASSERT_EQ(75, tree2.kthLargest(3));
	cout << "Tree2 content (= Tree1): " << endl;
	tree2.PrintTree();
	cout << endl;
}