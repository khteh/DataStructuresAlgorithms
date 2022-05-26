#include "pch.h"
using namespace std;
TEST(CircularLinkedListTests, LoopStartTest) {
	vector<long> a;
	a = { -1, 0, 1, 2, 3, 4, 5, 0 }; // Loop starts at '0'
	CircularLinkedList<long> cll(a);
	ASSERT_EQ(7, cll.Length());
	Node<long> lNode(-1);
	shared_ptr<Node<long>> head = cll.Find(lNode);
	ASSERT_TRUE(head);
	lNode.SetItem(0);
	shared_ptr<Node<long>> loopStart = cll.Find(lNode);
	ASSERT_TRUE(loopStart);
	cll.Print();
	ASSERT_EQ(loopStart, cll.LoopStart(head));

	a.clear();
	a = { -2, -1, 0, 1, 2, 3, 4, 5, 0 }; // Loop starts at '0'
	CircularLinkedList<long> cll1(a);
	ASSERT_EQ(8, cll1.Length());
	lNode.SetItem(-2);
	head = cll1.Find(lNode);
	ASSERT_TRUE(head);
	lNode.SetItem(0);
	loopStart = cll1.Find(lNode);
	ASSERT_TRUE(loopStart);
	cll1.Print();
	ASSERT_EQ(loopStart, cll1.LoopStart(head));

	a.clear();
	a = { -3, -2, -1, 0, 1, 2, 3, 4, 5, 0 }; // Loop starts at '0'
	CircularLinkedList<long> cll2(a);
	ASSERT_EQ(9, cll2.Length());
	lNode.SetItem(-3);
	head = cll2.Find(lNode);
	ASSERT_TRUE(head);
	lNode.SetItem(0);
	loopStart = cll2.Find(lNode);
	ASSERT_TRUE(loopStart);
	cll2.Print();
	ASSERT_EQ(loopStart, cll2.LoopStart(head));

	a.clear();
	a = { -3, -2, -1, 0, 1, 2, 3, 4, 5 }; // NO loop!
	CircularLinkedList<long> cll3(a);
	ASSERT_EQ(9, cll3.Length());
	lNode.SetItem(-3);
	head = cll3.Find(lNode);
	ASSERT_TRUE(head);
	cll3.Print();
	ASSERT_FALSE(cll3.LoopStart(head));

	a.clear();
	a = { 1, 2 }; // NO loop!
	CircularLinkedList<long> cll4(a);
	ASSERT_EQ(2, cll4.Length());
	lNode.SetItem(1);
	head = cll4.Find(lNode);
	ASSERT_TRUE(head);
	cll4.Print();
	ASSERT_FALSE(cll4.LoopStart(head));

	a.clear();
	a = { 1, 2, 1 }; // Loop starts at '1'
	CircularLinkedList<long> cll5(a);
	ASSERT_EQ(2, cll5.Length());
	lNode.SetItem(1);
	head = cll5.Find(lNode);
	ASSERT_TRUE(head);
	loopStart = cll5.Find(lNode);
	ASSERT_TRUE(loopStart);
	cll5.Print();
	ASSERT_EQ(loopStart, cll5.LoopStart(head));

	a.clear();
	a = { 1 }; // NO loop!
	CircularLinkedList<long> cll6(a);
	ASSERT_EQ(1, cll6.Length());
	head = cll6.Find(lNode);
	ASSERT_TRUE(head);
	cll6.Print();
	ASSERT_FALSE(cll6.LoopStart(head));
}