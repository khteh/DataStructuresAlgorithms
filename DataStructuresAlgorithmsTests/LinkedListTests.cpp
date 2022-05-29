#include "pch.h"
using namespace std;
TEST(LinkedListTests, SplitLinkedListTest) {
	vector<long> a, b;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	ranges:generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	a.clear();
	a.resize(10);
	ranges::generate(a, [&] { return uniformDistribution(engine); });
	LinkedList<long> ll(a);
	ASSERT_EQ(10, ll.Length());
	b.clear();
	ll.ToVector(b);
	ASSERT_EQ(a.size(), b.size());
	ASSERT_EQ(a, b);
	shared_ptr<Node<long>> odd = nullptr, even = nullptr;
	ll.SplitList(even, odd);
	ASSERT_EQ(10, ll.Length());
	ASSERT_TRUE(odd);
	ASSERT_TRUE(even);
	shared_ptr<Node<long>> node = even;
	for (size_t i = 0; node; node = node->Next(), i += 2)
		ASSERT_EQ(a[i], node->Item());
	node = odd;
	for (size_t i = 1; node; node = node->Next(), i += 2)
		ASSERT_EQ(a[i], node->Item());
}
TEST(LinkedListTests, LinkedListNthElementFromBackTest) {
	vector<long> a;
	a.resize(10);
	ranges::generate(a, [n = 0]() mutable { return n++; });
	// 0->1->2->3->4->5->6->7->8->9
	// 10 9  8  7  6  5  4  3  2  1
	LinkedList<long> ll(a);
	ASSERT_EQ(10, ll.Length());
	// Implement an algorithm to find the nth to last element of a singly linked list.
	shared_ptr<Node<long>> lptr = ll.NthElementFromBack(3);
	ASSERT_TRUE(lptr);
	ASSERT_EQ(7, lptr->Item());
	lptr = ll.NthElementFromBack(10);
	ASSERT_TRUE(lptr);
	ASSERT_EQ(0, lptr->Item());
	lptr = ll.NthElementFromBack(11);
	ASSERT_FALSE(lptr);
}
TEST(LinkedListTests, LinkedListRemoveNthElementFromBackTest) {
	vector<long> a;
	a.resize(10);
	ranges::generate(a, [n = 0]() mutable { return n++; });
	// 0->1->2->3->4->5->6->7->8->9
	// 10 9  8  7  6  5  4  3  2  1
	LinkedList<long> ll(a);
	ASSERT_EQ(10, ll.Length());
	shared_ptr<Node<long>> lptr = ll.RemoveNthElementFromBack(4);
	ASSERT_EQ(9, ll.Length());
	a.clear();
	a = { 0, 1, 2, 3, 4, 5, 7, 8, 9 };
	for (size_t i = 0; i < ll.Length(); i++, lptr = lptr->Next())
		ASSERT_EQ(a[i], lptr->Item());
	// 0->1->2->3->4->5->7->8->9
	// 9  8  7  6  5  4  3  2  1
	lptr = ll.RemoveNthElementFromBack(7);
	ASSERT_EQ(8, ll.Length());
	a.clear();
	a = { 0, 1, 3, 4, 5, 7, 8, 9 };
	for (size_t i = 0; i < ll.Length(); i++, lptr = lptr->Next())
		ASSERT_EQ(a[i], lptr->Item());
	// 0->1->3->4->5->7->8->9
	// 8  7  6  5  4  3  2  1
	lptr = ll.RemoveNthElementFromBack(8);
	ASSERT_EQ(7, ll.Length());
	a.clear();
	a = { 1, 3, 4, 5, 7, 8, 9 };
	for (size_t i = 0; i < ll.Length(); i++, lptr = lptr->Next())
		ASSERT_EQ(a[i], lptr->Item());
}
TEST(LinkedListTests, LinkedListArithmeticTest) {
	vector<long> a;
	a.push_back(1); // LSB
	a.push_back(2);
	a.push_back(3); // MSB
	LinkedList<long> lla(a);
	ASSERT_EQ(3, lla.Length());
	ASSERT_TRUE(lla.Find(Node<long>(2)));
	lla.Print();
	a.clear();
	a.push_back(7); // LSB
	a.push_back(8);
	a.push_back(9); // MSB
	LinkedList<long> llb(a);
	ASSERT_EQ(3, llb.Length());
	llb.Print();
	a.clear();
	a.push_back(8); // LSB
	a.push_back(0);
	a.push_back(3);
	a.push_back(1);	// MSB
	LinkedList<long> listAdditionResult = lla.AddNumbers(lla.Head(), llb.Head()); // 987 + 321 = 1308 List in reverse order. Head points to LSB
	ASSERT_EQ(4, listAdditionResult.Length());
	listAdditionResult.Print();
	size_t i = 0;
	for (shared_ptr<Node<long>> n = listAdditionResult.Head(); n; n = n->Next(), i++)
		ASSERT_EQ(a[i], n->Item());
	vector<long> listAdditionResultVector;
	listAdditionResult.ToVector(listAdditionResultVector);
	ASSERT_EQ(4, listAdditionResultVector.size());
	ASSERT_EQ(a, listAdditionResultVector);
}
TEST(LinkedListTests, LinkedListJoinTest) {
	vector<long> a, b;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	ranges:generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	a.resize(10);
	b.resize(10);
	ranges::generate(a, [&] { return uniformDistribution(engine); });
	ranges::generate(b, [&] { return uniformDistribution(engine); });
	LinkedList<long> lla(a), llb(b);
	ASSERT_EQ(10, lla.Length());
	ASSERT_EQ(10, llb.Length());
	lla.Join(llb);
	ASSERT_EQ(20, lla.Length());
	ASSERT_EQ(0, llb.Length());
}
TEST(LinkedListTests, LinkedListReversalTest) {
	vector<long> a, b;
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> ll(a);
	ASSERT_EQ(5, ll.Length());
	ll.Reverse(1, 3);
	ASSERT_EQ(5, ll.Length());
	a.clear();
	b.clear();
	b = { 1, 4, 3, 2, 5 };
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> ll1(a);
	ASSERT_EQ(5, ll1.Length());
	ll1.Reverse(0, 4);
	ASSERT_EQ(5, ll1.Length());
	b.clear();
	b = { 5, 4, 3, 2, 1 };
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> ll2(a);
	ASSERT_EQ(5, ll2.Length());
	ll2.Reverse(0, 3);
	ASSERT_EQ(5, ll2.Length());
	b.clear();
	b = { 4, 3, 2, 1, 5 };
	a.clear();
	ll2.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> ll3(a);
	ASSERT_EQ(5, ll3.Length());
	ll3.Reverse(1, 4);
	ASSERT_EQ(5, ll3.Length());
	b.clear();
	b = { 1, 5, 4, 3, 2 };
	a.clear();
	ll3.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> ll4(a);
	ASSERT_EQ(5, ll4.Length());
	ll4.Reverse(1, 1);
	ASSERT_EQ(5, ll4.Length());
	b.clear();
	b = { 1, 2, 3, 4, 5 };
	a.clear();
	ll4.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2 };
	LinkedList<long> ll5(a);
	ASSERT_EQ(2, ll5.Length());
	ll5.Reverse(0, 1);
	ASSERT_EQ(2, ll5.Length());
	b.clear();
	b = { 2, 1 };
	a.clear();
	ll5.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, LinkedListRemoveDuplicatesTest) {
	vector<long> a, b;
	a = { 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> ll(a);
	ASSERT_EQ(7, ll.Length());
	ll.RemoveDuplicates();
	ASSERT_EQ(5, ll.Length());
	b.clear();
	b = { 1, 2, 3, 4, 5 };
	a.clear();
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> ll1(a);
	ASSERT_EQ(7, ll1.Length());
	ll1.RemoveAllDuplicates();
	ASSERT_EQ(3, ll1.Length());
	b.clear();
	b = { 1, 2, 5 };
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> ll2(a);
	ASSERT_EQ(8, ll2.Length());
	ll2.RemoveDuplicates();
	ASSERT_EQ(5, ll2.Length());
	b.clear();
	b = { 1, 2, 3, 4, 5 };
	a.clear();
	ll2.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1 };
	LinkedList<long> ll3(a);
	ASSERT_EQ(1, ll3.Length());
	ll3.RemoveDuplicates();
	ASSERT_EQ(1, ll3.Length());
	b.clear();
	b = { 1 };
	a.clear();
	ll3.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1 };
	LinkedList<long> ll4(a);
	ASSERT_EQ(2, ll4.Length());
	ll4.RemoveDuplicates();
	ASSERT_EQ(1, ll4.Length());
	b.clear();
	b = { 1 };
	a.clear();
	ll4.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 2, 2 };
	LinkedList<long> ll5(a);
	ASSERT_EQ(3, ll5.Length());
	ll5.RemoveDuplicates();
	ASSERT_EQ(2, ll5.Length());
	b.clear();
	b = { 1, 2 };
	a.clear();
	ll5.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1, 1, 2 };
	LinkedList<long> ll6(a);
	ASSERT_EQ(4, ll6.Length());
	ll6.RemoveDuplicates();
	ASSERT_EQ(2, ll6.Length());
	b.clear();
	b = { 1, 2 };
	a.clear();
	ll6.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1, 1, 2, 3 };
	LinkedList<long> ll7(a);
	ASSERT_EQ(5, ll7.Length());
	ll7.RemoveDuplicates();
	ASSERT_EQ(3, ll7.Length());
	b.clear();
	b = { 1, 2, 3 };
	a.clear();
	ll7.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { -1, 0, 0, 0, 0, 3, 3 };
	LinkedList<long> ll8(a);
	ASSERT_EQ(7, ll8.Length());
	ll8.RemoveDuplicates();
	ASSERT_EQ(3, ll8.Length());
	b.clear();
	b = { -1, 0, 3 };
	a.clear();
	ll8.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, LinkedListRemoveALLDuplicatesTest) {
	vector<long> a, b;
	a = { 1, 1, 2, 3, 3, 4, 4, 5 };
	LinkedList<long> ll(a);
	ASSERT_EQ(8, ll.Length());
	ll.RemoveAllDuplicates();
	ASSERT_EQ(2, ll.Length());
	b.clear();
	b = { 2, 5 };
	a.clear();
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1 };
	LinkedList<long> ll1(a);
	ASSERT_EQ(1, ll1.Length());
	ll1.RemoveAllDuplicates();
	ASSERT_EQ(1, ll1.Length());
	b.clear();
	b = { 1 };
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1 };
	LinkedList<long> ll2(a);
	ASSERT_EQ(2, ll2.Length());
	ll2.RemoveAllDuplicates();
	ASSERT_EQ(0, ll2.Length());

	a.clear();
	a = { 1, 2, 2 };
	LinkedList<long> ll3(a);
	ASSERT_EQ(3, ll3.Length());
	ll3.RemoveAllDuplicates();
	ASSERT_EQ(1, ll3.Length());
	b.clear();
	b = { 1 };
	a.clear();
	ll3.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1, 1, 2 };
	LinkedList<long> ll4(a);
	ASSERT_EQ(4, ll4.Length());
	ll4.RemoveAllDuplicates();
	ASSERT_EQ(1, ll4.Length());
	b.clear();
	b = { 2 };
	a.clear();
	ll4.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1, 1, 1, 2, 3 };
	LinkedList<long> lla25(a);
	ASSERT_EQ(5, lla25.Length());
	lla25.RemoveAllDuplicates();
	ASSERT_EQ(2, lla25.Length());
	b.clear();
	b = { 2, 3 };
	a.clear();
	lla25.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { -1, 0, 0, 0, 0, 3, 3 };
	LinkedList<long> lla27(a);
	ASSERT_EQ(7, lla27.Length());
	lla27.RemoveAllDuplicates();
	ASSERT_EQ(1, lla27.Length());
	b.clear();
	b = { -1 };
	a.clear();
	lla27.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, LinkedListRemoveSortTest) {
	vector<long> a, b;
	a = { 2, 1 };
	LinkedList<long> ll(a);
	ASSERT_EQ(2, ll.Length());
	ll.Sort();
	ASSERT_EQ(2, ll.Length());
	ll.ToVector(b);
	a = { 1, 2 };
	ASSERT_EQ(2, b.size());
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = { 4, 2, 1, 3 };
	LinkedList<long> ll1(a);
	ASSERT_EQ(4, ll1.Length());
	ll1.Sort();
	ASSERT_EQ(4, ll1.Length());
	ll1.ToVector(b);
	a = { 1,2,3,4 };
	ASSERT_EQ(4, b.size());
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = { -1, 5, 3, 4, 0 };
	LinkedList<long> ll2(a);
	ASSERT_EQ(5, ll2.Length());
	ll2.Sort();
	ASSERT_EQ(5, ll2.Length());
	ll2.ToVector(b);
	a = { -1,0,3,4,5 };
	ASSERT_EQ(5, b.size());
	ASSERT_EQ(a, b);
}
TEST(LinkedListTests, LinkedListRotateRightTest) {
	vector<long> a, b;
	a = { 1, 2, 3, 4, 5 };
	LinkedList<long> ll(a);
	ASSERT_EQ(5, ll.Length());
	ll.RotateRight(2);
	ASSERT_EQ(5, ll.Length());
	a.clear();
	b = { 4, 5, 1, 2, 3 };
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	b.clear();
	a = { 1, 2, 3 };
	LinkedList<long> ll1(a);
	ASSERT_EQ(3, ll1.Length());
	ll1.RotateRight(2000000000);
	ASSERT_EQ(3, ll1.Length());
	b = { 2, 3, 1 };
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = { 1 };
	LinkedList<long> ll2(a);
	ASSERT_EQ(1, ll2.Length());
	ll2.RotateRight(1);
	ASSERT_EQ(1, ll2.Length());
	b.clear();
	b = { 1 };
	a.clear();
	ll2.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, ConnectedCellsInAGridTest) {
	vector<vector<long>> grid = { {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0} };
	ASSERT_EQ(5, ConnectedCellsInAGridLinkedList(grid));

	grid = { {0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0} };
	ASSERT_EQ(8, ConnectedCellsInAGridLinkedList(grid));

	grid = { {1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1} };
	ASSERT_EQ(5, ConnectedCellsInAGridLinkedList(grid));

	grid = { {0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0} };
	ASSERT_EQ(15, ConnectedCellsInAGridLinkedList(grid));

	grid = { {1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0} };
	ASSERT_EQ(9, ConnectedCellsInAGridLinkedList(grid));

	grid = { {1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0} };
	ASSERT_EQ(1, ConnectedCellsInAGridLinkedList(grid));
}