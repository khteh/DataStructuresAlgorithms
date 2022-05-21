#include "pch.h"
using namespace std;
TEST(LinkedListTests, LinkedListTest) {
	vector<long> a, b;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	a.clear();
	a.resize(10);
	generate(a.begin(), a.end(), [&]
		{ return uniformDistribution(engine); });
	LinkedList<long> lla1(a);
	ASSERT_EQ(10, lla1.Length());
	b.clear();
	lla1.ToVector(b);
	ASSERT_EQ(a.size(), b.size());
	ASSERT_EQ(a, b);
	shared_ptr<Node<long>> odd = nullptr, even = nullptr;
	lla1.SplitList(even, odd);
	ASSERT_EQ(10, lla1.Length());
	ASSERT_TRUE(odd);
	ASSERT_TRUE(even);
	shared_ptr<Node<long>> node = even;
	for (size_t i = 0; node; node = node->Next(), i += 2)
		ASSERT_EQ(a[i], node->Item());
	node = odd;
	for (size_t i = 1; node; node = node->Next(), i += 2)
		ASSERT_EQ(a[i], node->Item());
	lla1.Clear();
	a.clear();
	a.resize(10);
	generate(a.begin(), a.end(), [n = 0]() mutable { return n++; });
	// 0->1->2->3->4->5->6->7->8->9
	// 10 9  8  7  6  5  4  3  2  1
	LinkedList<long> lla2(a);
	ASSERT_EQ(10, lla2.Length());
	// Implement an algorithm to find the nth to last element of a singly linked list.
	shared_ptr<Node<long>> lptr = lla2.NthElementFromBack(3);
	ASSERT_TRUE(lptr);
	ASSERT_EQ(7, lptr->Item());
	lptr = lla2.NthElementFromBack(10);
	ASSERT_TRUE(lptr);
	ASSERT_EQ(0, lptr->Item());
	lptr = lla2.NthElementFromBack(11);
	ASSERT_FALSE(lptr);
	lptr = lla2.RemoveNthElementFromBack(4);
	ASSERT_TRUE(9, lla2.Length());
	a.clear();
	a = { 0, 1, 2, 3, 4, 5, 7, 8, 9 };
	for (size_t i = 0; i < lla2.Length(); i++)
	{
		ASSERT_EQ(a[i], lptr->Item());
		lptr = lptr->Next();
	}
	// 0->1->2->3->4->5->7->8->9
	// 9  8  7  6  5  4  3  2  1
	lptr = lla2.RemoveNthElementFromBack(7);
	ASSERT_EQ(8, lla2.Length());
	a.clear();
	a = { 0, 1, 3, 4, 5, 7, 8, 9 };
	for (size_t i = 0; i < lla2.Length(); i++)
	{
		ASSERT_EQ(a[i], lptr->Item());
		lptr = lptr->Next();
	}
	// 0->1->3->4->5->7->8->9
	// 8  7  6  5  4  3  2  1
	lptr = lla2.RemoveNthElementFromBack(8);
	ASSERT_EQ(7, lla2.Length());
	a.clear();
	a = { 1, 3, 4, 5, 7, 8, 9 };
	for (size_t i = 0; i < lla2.Length(); i++)
	{
		ASSERT_EQ(a[i], lptr->Item());
		lptr = lptr->Next();
	}
	lla2.Clear();
	a.clear();
	a.push_back(1); // LSB
	a.push_back(2);
	a.push_back(3); // MSB
	LinkedList<long> lla3(a);
	ASSERT_EQ(3, lla3.Length());
	ASSERT_TRUE(lla3.Find(Node<long>(2)));
	lla3.Print();
	a.clear();
	a.push_back(7); // LSB
	a.push_back(8);
	a.push_back(9); // MSB
	LinkedList<long> llb1(a);
	ASSERT_EQ(3, llb1.Length());
	llb1.Print();
	a.clear();
	a.push_back(8); // LSB
	a.push_back(0);
	a.push_back(3);
	a.push_back(1);																	 // MSB
	LinkedList<long> listAdditionResult = lla3.AddNumbers(lla3.Head(), llb1.Head()); // 987 + 321 = 1308 List in reverse order. Head points to LSB
	ASSERT_EQ(4, listAdditionResult.Length());
	listAdditionResult.Print();
	size_t i = 0;
	for (shared_ptr<Node<long>> n = listAdditionResult.Head(); n; n = n->Next(), i++)
		ASSERT_EQ(a[i], n->Item());
	vector<long> listAdditionResultVector;
	listAdditionResult.ToVector(listAdditionResultVector);
	ASSERT_EQ(4, listAdditionResultVector.size());
	ASSERT_EQ(8, listAdditionResultVector[0]);
	ASSERT_EQ(0, listAdditionResultVector[1]);
	ASSERT_EQ(3, listAdditionResultVector[2]);
	ASSERT_EQ(1, listAdditionResultVector[3]);
	listAdditionResult.Clear();
	lla3.Clear();
	llb1.Clear();
	a.clear();
	b.clear();
	a.resize(10);
	b.resize(10);
	generate(a.begin(), a.end(), [&]
		{ return uniformDistribution(engine); });
	generate(b.begin(), b.end(), [&]
		{ return uniformDistribution(engine); });
	LinkedList<long> lla4(a), llb2(b);
	ASSERT_EQ(10, lla4.Length());
	ASSERT_EQ(10, llb2.Length());
	lla4.Join(llb2);
	ASSERT_EQ(20, lla4.Length());
	ASSERT_EQ(0, llb2.Length());
	lla4.Clear();
	llb2.Clear();
	a.clear();
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

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> lla5(a);
	ASSERT_EQ(5, lla5.Length());
	lla5.Reverse(1, 3);
	ASSERT_EQ(5, lla5.Length());
	b.clear();
	b = { 1, 4, 3, 2, 5 };
	vector<long> c;
	lla5.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> lla6(a);
	ASSERT_EQ(5, lla6.Length());
	lla6.Reverse(0, 4);
	ASSERT_EQ(5, lla6.Length());
	b.clear();
	b = { 5, 4, 3, 2, 1 };
	c.clear();
	lla6.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> lla7(a);
	ASSERT_EQ(5, lla7.Length());
	lla7.Reverse(0, 3);
	ASSERT_EQ(5, lla7.Length());
	b.clear();
	b = { 4, 3, 2, 1, 5 };
	c.clear();
	lla7.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> lla8(a);
	ASSERT_EQ(5, lla8.Length());
	lla8.Reverse(1, 4);
	ASSERT_EQ(5, lla8.Length());
	b.clear();
	b = { 1, 5, 4, 3, 2 };
	c.clear();
	lla8.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> lla9(a);
	ASSERT_EQ(5, lla9.Length());
	lla9.Reverse(1, 1);
	ASSERT_EQ(5, lla9.Length());
	b.clear();
	b = { 1, 2, 3, 4, 5 };
	c.clear();
	lla9.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2 };
	LinkedList<long> lla10(a);
	ASSERT_EQ(2, lla10.Length());
	lla10.Reverse(0, 1);
	ASSERT_EQ(2, lla10.Length());
	b.clear();
	b = { 2, 1 };
	c.clear();
	lla10.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> lla11(a);
	ASSERT_EQ(7, lla11.Length());
	lla11.RemoveDuplicates();
	ASSERT_EQ(5, lla11.Length());
	b.clear();
	b = { 1, 2, 3, 4, 5 };
	c.clear();
	lla11.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> lla12(a);
	ASSERT_EQ(7, lla12.Length());
	lla12.RemoveAllDuplicates();
	ASSERT_EQ(3, lla12.Length());
	b.clear();
	b = { 1, 2, 5 };
	c.clear();
	lla12.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> lla13(a);
	ASSERT_EQ(8, lla13.Length());
	lla13.RemoveDuplicates();
	ASSERT_EQ(5, lla13.Length());
	b.clear();
	b = { 1, 2, 3, 4, 5 };
	c.clear();
	lla13.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> lla14(a);
	ASSERT_EQ(8, lla14.Length());
	lla14.RemoveAllDuplicates();
	ASSERT_EQ(2, lla14.Length());
	b.clear();
	b = { 2, 5 };
	c.clear();
	lla14.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1 };
	LinkedList<long> lla15(a);
	ASSERT_EQ(1, lla15.Length());
	lla15.RemoveDuplicates();
	ASSERT_EQ(1, lla15.Length());
	b.clear();
	b = { 1 };
	c.clear();
	lla15.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1 };
	LinkedList<long> lla16(a);
	ASSERT_EQ(1, lla16.Length());
	lla16.RemoveAllDuplicates();
	ASSERT_EQ(1, lla16.Length());
	b.clear();
	b = { 1 };
	c.clear();
	lla16.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1 };
	LinkedList<long> lla18(a);
	ASSERT_EQ(2, lla18.Length());
	lla18.RemoveDuplicates();
	ASSERT_EQ(1, lla18.Length());
	b.clear();
	b = { 1 };
	c.clear();
	lla18.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1 };
	LinkedList<long> lla19(a);
	ASSERT_EQ(2, lla19.Length());
	lla19.RemoveAllDuplicates();
	ASSERT_EQ(0, lla19.Length());

	a.clear();
	a = { 1, 2, 2 };
	LinkedList<long> lla20(a);
	ASSERT_EQ(3, lla20.Length());
	lla20.RemoveDuplicates();
	ASSERT_EQ(2, lla20.Length());
	b.clear();
	b = { 1, 2 };
	c.clear();
	lla20.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 2 };
	LinkedList<long> lla21(a);
	ASSERT_EQ(3, lla21.Length());
	lla21.RemoveAllDuplicates();
	ASSERT_EQ(1, lla21.Length());
	b.clear();
	b = { 1 };
	c.clear();
	lla21.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1, 1, 2 };
	LinkedList<long> lla22(a);
	ASSERT_EQ(4, lla22.Length());
	lla22.RemoveDuplicates();
	ASSERT_EQ(2, lla22.Length());
	b.clear();
	b = { 1, 2 };
	c.clear();
	lla22.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1, 1, 2 };
	LinkedList<long> lla23(a);
	ASSERT_EQ(4, lla23.Length());
	lla23.RemoveAllDuplicates();
	ASSERT_EQ(1, lla23.Length());
	b.clear();
	b = { 2 };
	c.clear();
	lla23.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1, 1, 2, 3 };
	LinkedList<long> lla24(a);
	ASSERT_EQ(5, lla24.Length());
	lla24.RemoveDuplicates();
	ASSERT_EQ(3, lla24.Length());
	b.clear();
	b = { 1, 2, 3 };
	c.clear();
	lla24.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 1, 1, 2, 3 };
	LinkedList<long> lla25(a);
	ASSERT_EQ(5, lla25.Length());
	lla25.RemoveAllDuplicates();
	ASSERT_EQ(2, lla25.Length());
	b.clear();
	b = { 2, 3 };
	c.clear();
	lla25.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { -1, 0, 0, 0, 0, 3, 3 };
	LinkedList<long> lla26(a);
	ASSERT_EQ(7, lla26.Length());
	lla26.RemoveDuplicates();
	ASSERT_EQ(3, lla26.Length());
	b.clear();
	b = { -1, 0, 3 };
	c.clear();
	lla26.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { -1, 0, 0, 0, 0, 3, 3 };
	LinkedList<long> lla27(a);
	ASSERT_EQ(7, lla27.Length());
	lla27.RemoveAllDuplicates();
	ASSERT_EQ(1, lla27.Length());
	b.clear();
	b = { -1 };
	c.clear();
	lla27.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 2, 1 };
	LinkedList<long> lla28(a);
	ASSERT_EQ(2, lla28.Length());
	lla28.Sort();
	ASSERT_EQ(2, lla28.Length());
	c.clear();
	lla28.ToVector(c);
	assert(c.size() == 2);
	assert(c[0] == 1);
	assert(c[1] == 2);

	a.clear();
	a = { 4, 2, 1, 3 };
	LinkedList<long> lla29(a);
	ASSERT_EQ(4, lla29.Length());
	lla29.Sort();
	ASSERT_EQ(4, lla29.Length());
	c.clear();
	lla29.ToVector(c);
	ASSERT_EQ(c.size(), 4);
	ASSERT_EQ(c[0], 1);
	ASSERT_EQ(c[1], 2);
	ASSERT_EQ(c[2], 3);
	ASSERT_EQ(c[3], 4);

	a.clear();
	a = { -1, 5, 3, 4, 0 };
	LinkedList<long> lla30(a);
	ASSERT_EQ(5, lla30.Length());
	lla30.Sort();
	ASSERT_EQ(5, lla30.Length());
	c.clear();
	lla30.ToVector(c);
	ASSERT_EQ(c.size(), 5);
	ASSERT_EQ(c[0], -1);
	ASSERT_EQ(c[1], 0);
	ASSERT_EQ(c[2], 3);
	ASSERT_EQ(c[3], 4);
	ASSERT_EQ(c[4], 5);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> lla31(a);
	ASSERT_EQ(5, lla31.Length());
	lla31.RotateRight(2);
	ASSERT_EQ(5, lla31.Length());
	b.clear();
	b = { 4, 5, 1, 2, 3 };
	c.clear();
	lla31.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1, 2, 3 };
	LinkedList<long> lla32(a);
	ASSERT_EQ(3, lla32.Length());
	lla32.RotateRight(2000000000);
	ASSERT_EQ(3, lla32.Length());
	b.clear();
	b = { 2, 3, 1 };
	c.clear();
	lla32.ToVector(c);
	ASSERT_EQ(b, c);

	a.clear();
	a = { 1 };
	LinkedList<long> lla33(a);
	ASSERT_EQ(1, lla33.Length());
	lla33.RotateRight(1);
	ASSERT_EQ(1, lla33.Length());
	b.clear();
	b = { 1 };
	c.clear();
	lla33.ToVector(c);
	ASSERT_EQ(b, c);
}