#include "pch.h"
using namespace std;
TEST(BinaryTreeTests, BinaryTreeTest) {
	vector<string> result;
	Tree<long> tree(50);
	tree.InsertItem(-100);
	tree.InsertItem(0);
	tree.InsertItem(10);
	tree.InsertItem(-50);
	tree.InsertItem(60);
	tree.InsertItem(100);
	tree.InsertItem(75);
	tree.InsertItem(150);
	ASSERT_EQ(9, tree.Count());
	Tree<long> subtree((long)0);
	subtree.InsertItem(-50);
	subtree.InsertItem(10);

	Tree<long> subtree1((long)0);
	subtree1.InsertItem(50);
	subtree1.InsertItem(60);

	Tree<long> subtree2(50);
	subtree2.InsertItem(-100);
	subtree2.InsertItem(60);

	cout << "Binary Tree content: " << endl;
	tree.PrintTree();
	cout << endl;

	cout << "SubTree content: " << endl;
	subtree.PrintTree();
	cout << endl;
	cout << (tree.SubTree(tree.Root(), subtree.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "SubTree1 content: " << endl;
	subtree1.PrintTree();
	cout << endl;
	cout << (tree.SubTree(tree.Root(), subtree1.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "SubTree2 content: " << endl;
	subtree2.PrintTree();
	cout << endl;
	cout << (tree.SubTree(tree.Root(), subtree2.Root()) ? "Subtree" : "Not subtree") << endl;

	cout << "MinDepth: " << tree.MinDepth(tree.Root()) << ", MaxDepth: " << tree.MaxDepth(tree.Root()) << " " << (tree.IsBalancedTree() ? "balanced" : "Unbalanced") << endl;
	tree.PrintTreeColumns();
	tree.FindSum(tree.Root(), -100, result);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(3, result.size()); //"-100" "-100 0" "-50 0 -100 50"
	cout << "Sum -100 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << quoted(*it) << " ";
	cout << endl;
	result.clear();

	tree.FindSum(tree.Root(), 110, result);
	ASSERT_EQ(1, result.size());
	cout << "Sum 110 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << quoted(*it) << " ";
	cout << endl;
	result.clear();

	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	tree.GetNodes(nodes);
	ASSERT_FALSE(nodes.empty());
	cout << "Binary Tree content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	nodes.clear();
	/*
Binary Tree content:
Level 0:                50
Level 1:      -100(50)        60(50)
Level 2:            0(-100)         100(60)
Level 3:       -50(0)     10(0)  75(100)   150(100)
	*/
	shared_ptr<Node<long>> node = tree.FindNode(-50), node1, node2, node3;
	ASSERT_TRUE(node);
	ASSERT_EQ(0, tree.InOrderSuccessor(node)->Item());
	node = tree.FindNode(50);
	ASSERT_TRUE(node);
	ASSERT_EQ(60, tree.InOrderSuccessor(node)->Item());
	node = tree.FindNode(10);
	ASSERT_TRUE(node);
	ASSERT_EQ(50, tree.InOrderSuccessor(node)->Item());

	node = tree.FindNode(-50);
	ASSERT_TRUE(node);
	node1 = tree.FindNode(10);
	ASSERT_TRUE(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_EQ(0, node2->Item());
	ASSERT_EQ(0, node3->Item());
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node1 = tree.FindNode(75);
	ASSERT_TRUE(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_EQ(50, node2->Item());
	ASSERT_EQ(50, node3->Item());
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;
	node = tree.FindNode(60);
	ASSERT_TRUE(node);
	node1 = tree.FindNode(75);
	ASSERT_TRUE(node1);
	node2 = tree.CommonAncestor(node, node1);
	node3 = tree.CommonAncestor1(node, node1);
	ASSERT_TRUE(node2);
	ASSERT_TRUE(node3);
	ASSERT_EQ(60, node2->Item());
	ASSERT_EQ(60, node3->Item());
	cout << node->Item() << " and " << node1->Item() << " common ancestor is " << node2->Item() << endl;

	Tree<long> tree1(tree);
	ASSERT_EQ(tree, tree1);
	cout << "Tree1 content (= Tree): " << endl;
	tree1.PrintTree();

	tree.Clear();
	tree.InsertItem(2);
	tree.InsertItem(3);
	tree.InsertItem(-4);
	tree.InsertItem(3);
	tree.InsertItem(1);
	tree.InsertItem(2);
	result.clear();
	cout << "Tree content (= Tree): " << endl;
	tree.PrintTree();
	tree.FindSum(tree.Root(), 5, result);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(1, result.size());
	cout << "Sum 5 path: ";
	for (vector<string>::const_iterator it = result.begin(); it != result.end(); it++)
		cout << quoted(*it) << " ";
	cout << endl;
	result.clear();
	vector<size_t> data = { 10, 5, 11 };
	vector<vector<size_t>> links = { {10, 5}, {10, 11} };

	vector<long> a, b;
	a.clear();
	b.clear();
	a = { 1, 2, 3, 4, 5 };
	Tree<long> tree2(a, TreeType::Binary);
	ASSERT_EQ(5, tree2.Count());
	cout << "Binary Tree content: " << endl;
	tree2.PrintTree();
	cout << endl;
	result.clear();
	tree2.Serialize(tree2.Root(), b);
	ASSERT_FALSE(b.empty());
	ASSERT_EQ(b.size(), a.size());
	tree2.PrintTreeColumns();
	cout << endl;

	a.clear();
	a = { 1, 2, 3 };
	Tree<long> tree3(a, TreeType::Binary);
	ASSERT_EQ(3, tree3.Count());
	ASSERT_EQ(25, tree3.SumRoot2LeafNumbers());

	a.clear();
	a = { 4, 9, 0, 5, 1 };
	Tree<long> tree4(a, TreeType::Binary);
	ASSERT_EQ(5, tree4.Count());
	ASSERT_EQ(1026, tree4.SumRoot2LeafNumbers());

	a.clear();
	a = { 5, 3, 2, 7, 0, 6, numeric_limits<long>::min(), numeric_limits<long>::min(), numeric_limits<long>::min(), 0 };
	Tree<long> tree5(a, TreeType::Binary);
	tree5.PrintTree();
	ASSERT_EQ(7, tree5.Count());
	ASSERT_EQ(6363, tree5.SumRoot2LeafNumbers());

	a.clear();
	a = { 1, 2, 5, 3, 4, numeric_limits<long>::min(), 6 };
	Tree<long> tree6(a, TreeType::Binary);
	tree6.ToLinkedList();
	tree6.PrintTree();

	a.clear();
	b.clear();
	a = { 1, 3 };
	b = { 3, 1 };
	Tree<long> tree7(TraversalType::PreOrder, a, b);
	ASSERT_EQ(2, tree7.Count());
	tree7.PrintTree();

	a.clear();
	b.clear();
	a = { 3, 1 };
	b = { 3, 1 };
	Tree<long> tree8(TraversalType::PreOrder, a, b);
	ASSERT_EQ(2, tree8.Count());
	tree8.PrintTree();

	a.clear();
	b.clear();
	a = { 9, 3, 15, 20, 7 };
	b = { 3, 9, 20, 15, 7 };
	/*
	* 		3
		 9     20
			15     7
	*/
	Tree<long> tree9(TraversalType::PreOrder, a, b);
	ASSERT_EQ(5, tree9.Count());
	ASSERT_FALSE(tree9.isValidBST());
	tree9.PrintTree();

	a.clear();
	b.clear();
	a = { 3, 2, 1 };
	b = { 1, 2, 3 };
	/*
	*    1
	   2
	 3
	*/
	Tree<long> tree10(TraversalType::PreOrder, a, b);
	ASSERT_EQ(3, tree10.Count());
	ASSERT_FALSE(tree10.isValidBST());
	tree10.PrintTree();

	a.clear();
	b.clear();
	a = { 1, 2, 3 };
	b = { 1, 2, 3 };
	/*
	*    1
		   2
			 3
	*/
	Tree<long> tree11(TraversalType::PreOrder, a, b);
	ASSERT_EQ(3, tree11.Count());
	ASSERT_TRUE(tree11.isValidBST());
	tree11.PrintTree();

	a.clear();
	b.clear();
	a = { 2, 3, 1 };
	b = { 1, 2, 3 };
	/*
	*     1
		2
		  3
	*/
	Tree<long> tree12(TraversalType::PreOrder, a, b);
	ASSERT_EQ(3, tree12.Count());
	ASSERT_FALSE(tree12.isValidBST());
	tree12.PrintTree();

	a.clear();
	b.clear();
	a = { 1, 2, 3, 4 };
	b = { 4, 3, 1, 2 };
	/*
	*      4
		3
		  1
			 2
	*/
	Tree<long> tree13(TraversalType::PreOrder, a, b);
	ASSERT_EQ(4, tree13.Count());
	ASSERT_TRUE(tree13.isValidBST());
	tree13.PrintTree();

	a.clear();
	b.clear();
	a = { 4, 2, 1, 3 };
	b = { 4, 3, 1, 2 };
	/*
	*        4
				 3
			   1
			 2
	*/
	Tree<long> tree14(TraversalType::PreOrder, a, b);
	ASSERT_EQ(4, tree14.Count());
	ASSERT_FALSE(tree14.isValidBST());
	tree14.PrintTree();

	a.clear();
	b.clear();
	a = { 9, 3, 15, 20, 7 };
	b = { 9, 15, 7, 20, 3 };
	/*
	*     3
		 / \
		9  20
		  /  \
		 15   7
	*/
	Tree<long> tree15(TraversalType::PostOrder, a, b);
	ASSERT_EQ(5, tree15.Count());
	ASSERT_FALSE(tree15.isValidBST());
	tree15.PrintTree();

	a.clear();
	b.clear();
	a = { 1, 2, 3, 4 };
	b = { 2, 1, 3, 4 };
	/*
	*      4
		3
	  1
		 2
	*/
	Tree<long> tree16(TraversalType::PostOrder, a, b);
	tree16.PrintTree();
	ASSERT_EQ(4, tree16.Count());
	ASSERT_TRUE(tree16.isValidBST());
}