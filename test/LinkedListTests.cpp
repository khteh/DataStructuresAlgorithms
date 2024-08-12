#include "pch.h"
using namespace std;
TEST(LinkedListTests, SplitLinkedListTest)
{
	vector<long> a, b;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	a.clear();
	a.resize(10);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
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
template <typename T>
class LinkedListTestFixture
{
public:
	void SetUp(T expected, T var1, vector<T> data)
	{
		_expected = expected;
		_var1 = var1;
		_data = data;
		_ll.LoadData(_data);
	}

protected:
	LinkedList<T> _ll;
	T _expected, _var1;
	vector<T> _data;
};
class LinkedListNthElementFromBackTestFixture : public LinkedListTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		LinkedListTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t LinkedListNthElementFromBackTest()
	{
		// 0->1->2->3->4->5->6->7->8->9
		// 10 9  8  7  6  5  4  3  2  1
		shared_ptr<Node<size_t>> lptr = _ll.NthElementFromBack(_var1);
		return lptr ? lptr->Item() : 0;
	}
};
TEST_P(LinkedListNthElementFromBackTestFixture, LinkedListNthElementFromBackTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListNthElementFromBackTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListNthElementFromBackTests,
	LinkedListNthElementFromBackTestFixture,
	::testing::Values(make_tuple(0, 10, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), make_tuple(7, 3, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), make_tuple(0, 11, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
class LinkedListIndexSubscriptOperatorTestFixture : public LinkedListTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		LinkedListTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t LinkedListIndexSubscriptOperatorTest()
	{
		// 0->1->2->3->4->5->6->7->8->9
		shared_ptr<Node<size_t>> lptr = _ll[_var1];
		return lptr ? lptr->Item() : 0;
	}
};
TEST_P(LinkedListIndexSubscriptOperatorTestFixture, LinkedListIndexSubscriptOperatorTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListIndexSubscriptOperatorTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListIndexSubscriptOperatorTests,
	LinkedListIndexSubscriptOperatorTestFixture,
	::testing::Values(make_tuple(3, 3, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), make_tuple(5, 5, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), make_tuple(0, 10, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
class LinkedListRemoveNthElementFromBackTestFixture : public LinkedListTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		LinkedListTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t LinkedListRemoveNthElementFromBackTest()
	{
		// 0->1->2->3->4->5->6->7->8->9
		// 10 9  8  7  6  5  4  3  2  1
		shared_ptr<Node<size_t>> lptr = _ll.RemoveNthElementFromBack(_var1);
		return lptr ? lptr->Item() : 0;
	}
};
TEST_P(LinkedListRemoveNthElementFromBackTestFixture, LinkedListRemoveNthElementFromBackTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListRemoveNthElementFromBackTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListRemoveNthElementFromBackTests,
	LinkedListRemoveNthElementFromBackTestFixture,
	::testing::Values(make_tuple(5, 4, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), make_tuple(2, 7, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), make_tuple(1, 8, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
class LinkedListArithmeticTestFixture : public testing::TestWithParam<tuple<vector<size_t>, vector<size_t>, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
		_ll1.LoadData(_data1);
		_ll2.LoadData(_data2);
	}
	vector<size_t> LinkedListArithmeticTest()
	{
		// 0->1->2->3->4->5->6->7->8->9
		LinkedList<size_t> listAdditionResult = _ll1.AddNumbers(_ll2);
		vector<size_t> listAdditionResultVector;
		listAdditionResult.ToVector(listAdditionResultVector);
		return listAdditionResultVector;
	}

protected:
	LinkedList<size_t> _ll1, _ll2;
	vector<size_t> _expected;
	vector<size_t> _data1, _data2;
};
TEST_P(LinkedListArithmeticTestFixture, LinkedListArithmeticTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListArithmeticTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListArithmeticTests,
	LinkedListArithmeticTestFixture,
	::testing::Values(make_tuple(vector<size_t>{8 /*LSB*/, 0, 3, 1 /*MSB*/}, vector<size_t>{1 /*LSB*/, 2, 3 /*MSB*/}, vector<size_t>{7 /*LSB*/, 8, 9 /*MSB*/})));

TEST(LinkedListTests, LinkedListJoinTest)
{
	vector<long> a, b;
	random_device device;
	vector<unsigned int> seeds;
	seeds.resize(mt19937_64::state_size);
	ranges::generate_n(seeds.begin(), mt19937_64::state_size, ref(device));
	seed_seq sequence(seeds.begin(), seeds.end());
	mt19937_64 engine(sequence);
	uniform_int_distribution<long> uniformDistribution;
	a.resize(10);
	b.resize(10);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ranges::generate(b, [&]
					 { return uniformDistribution(engine); });
	LinkedList<long> lla(a), llb(b);
	ASSERT_EQ(10, lla.Length());
	ASSERT_EQ(10, llb.Length());
	lla.Join(llb);
	ASSERT_EQ(20, lla.Length());
	ASSERT_EQ(0, llb.Length());
}
TEST(LinkedListTests, LinkedListReversalTest)
{
	vector<long> a, b;
	a = {1, 2, 3, 4, 5};
	LinkedList<long> ll(a);
	ASSERT_EQ(5, ll.Length());
	ll.Reverse(1, 3);
	ASSERT_EQ(5, ll.Length());
	a.clear();
	b.clear();
	b = {1, 4, 3, 2, 5};
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> ll1(a);
	ASSERT_EQ(5, ll1.Length());
	ll1.Reverse(0, 4);
	ASSERT_EQ(5, ll1.Length());
	b.clear();
	b = {5, 4, 3, 2, 1};
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> ll2(a);
	ASSERT_EQ(5, ll2.Length());
	ll2.Reverse(0, 3);
	ASSERT_EQ(5, ll2.Length());
	b.clear();
	b = {4, 3, 2, 1, 5};
	a.clear();
	ll2.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> ll3(a);
	ASSERT_EQ(5, ll3.Length());
	ll3.Reverse(1, 4);
	ASSERT_EQ(5, ll3.Length());
	b.clear();
	b = {1, 5, 4, 3, 2};
	a.clear();
	ll3.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2, 3, 4, 5};
	LinkedList<long> ll4(a);
	ASSERT_EQ(5, ll4.Length());
	ll4.Reverse(1, 1);
	ASSERT_EQ(5, ll4.Length());
	b.clear();
	b = {1, 2, 3, 4, 5};
	a.clear();
	ll4.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2};
	LinkedList<long> ll5(a);
	ASSERT_EQ(2, ll5.Length());
	ll5.Reverse(0, 1);
	ASSERT_EQ(2, ll5.Length());
	b.clear();
	b = {2, 1};
	a.clear();
	ll5.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, LinkedListRemoveDuplicatesTest)
{
	vector<long> a, b;
	a = {1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> ll(a);
	ASSERT_EQ(7, ll.Length());
	ll.RemoveDuplicates();
	ASSERT_EQ(5, ll.Length());
	b.clear();
	b = {1, 2, 3, 4, 5};
	a.clear();
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> ll1(a);
	ASSERT_EQ(7, ll1.Length());
	ll1.RemoveAllDuplicates();
	ASSERT_EQ(3, ll1.Length());
	b.clear();
	b = {1, 2, 5};
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> ll2(a);
	ASSERT_EQ(8, ll2.Length());
	ll2.RemoveDuplicates();
	ASSERT_EQ(5, ll2.Length());
	b.clear();
	b = {1, 2, 3, 4, 5};
	a.clear();
	ll2.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1};
	LinkedList<long> ll3(a);
	ASSERT_EQ(1, ll3.Length());
	ll3.RemoveDuplicates();
	ASSERT_EQ(1, ll3.Length());
	b.clear();
	b = {1};
	a.clear();
	ll3.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1};
	LinkedList<long> ll4(a);
	ASSERT_EQ(2, ll4.Length());
	ll4.RemoveDuplicates();
	ASSERT_EQ(1, ll4.Length());
	b.clear();
	b = {1};
	a.clear();
	ll4.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 2, 2};
	LinkedList<long> ll5(a);
	ASSERT_EQ(3, ll5.Length());
	ll5.RemoveDuplicates();
	ASSERT_EQ(2, ll5.Length());
	b.clear();
	b = {1, 2};
	a.clear();
	ll5.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1, 1, 2};
	LinkedList<long> ll6(a);
	ASSERT_EQ(4, ll6.Length());
	ll6.RemoveDuplicates();
	ASSERT_EQ(2, ll6.Length());
	b.clear();
	b = {1, 2};
	a.clear();
	ll6.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1, 1, 2, 3};
	LinkedList<long> ll7(a);
	ASSERT_EQ(5, ll7.Length());
	ll7.RemoveDuplicates();
	ASSERT_EQ(3, ll7.Length());
	b.clear();
	b = {1, 2, 3};
	a.clear();
	ll7.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {-1, 0, 0, 0, 0, 3, 3};
	LinkedList<long> ll8(a);
	ASSERT_EQ(7, ll8.Length());
	ll8.RemoveDuplicates();
	ASSERT_EQ(3, ll8.Length());
	b.clear();
	b = {-1, 0, 3};
	a.clear();
	ll8.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, LinkedListRemoveALLDuplicatesTest)
{
	vector<long> a, b;
	a = {1, 1, 2, 3, 3, 4, 4, 5};
	LinkedList<long> ll(a);
	ASSERT_EQ(8, ll.Length());
	ll.RemoveAllDuplicates();
	ASSERT_EQ(2, ll.Length());
	b.clear();
	b = {2, 5};
	a.clear();
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1};
	LinkedList<long> ll1(a);
	ASSERT_EQ(1, ll1.Length());
	ll1.RemoveAllDuplicates();
	ASSERT_EQ(1, ll1.Length());
	b.clear();
	b = {1};
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1};
	LinkedList<long> ll2(a);
	ASSERT_EQ(2, ll2.Length());
	ll2.RemoveAllDuplicates();
	ASSERT_EQ(0, ll2.Length());

	a.clear();
	a = {1, 2, 2};
	LinkedList<long> ll3(a);
	ASSERT_EQ(3, ll3.Length());
	ll3.RemoveAllDuplicates();
	ASSERT_EQ(1, ll3.Length());
	b.clear();
	b = {1};
	a.clear();
	ll3.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1, 1, 2};
	LinkedList<long> ll4(a);
	ASSERT_EQ(4, ll4.Length());
	ll4.RemoveAllDuplicates();
	ASSERT_EQ(1, ll4.Length());
	b.clear();
	b = {2};
	a.clear();
	ll4.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1, 1, 1, 2, 3};
	LinkedList<long> lla25(a);
	ASSERT_EQ(5, lla25.Length());
	lla25.RemoveAllDuplicates();
	ASSERT_EQ(2, lla25.Length());
	b.clear();
	b = {2, 3};
	a.clear();
	lla25.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {-1, 0, 0, 0, 0, 3, 3};
	LinkedList<long> lla27(a);
	ASSERT_EQ(7, lla27.Length());
	lla27.RemoveAllDuplicates();
	ASSERT_EQ(1, lla27.Length());
	b.clear();
	b = {-1};
	a.clear();
	lla27.ToVector(a);
	ASSERT_EQ(b, a);
}
TEST(LinkedListTests, LinkedListRemoveSortTest)
{
	vector<long> a, b;
	a = {2, 1};
	LinkedList<long> ll(a);
	ASSERT_EQ(2, ll.Length());
	ll.Sort();
	ASSERT_EQ(2, ll.Length());
	ll.ToVector(b);
	a = {1, 2};
	ASSERT_EQ(2, b.size());
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = {4, 2, 1, 3};
	LinkedList<long> ll1(a);
	ASSERT_EQ(4, ll1.Length());
	ll1.Sort();
	ASSERT_EQ(4, ll1.Length());
	ll1.ToVector(b);
	a = {1, 2, 3, 4};
	ASSERT_EQ(4, b.size());
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = {-1, 5, 3, 4, 0};
	LinkedList<long> ll2(a);
	ASSERT_EQ(5, ll2.Length());
	ll2.Sort();
	ASSERT_EQ(5, ll2.Length());
	ll2.ToVector(b);
	a = {-1, 0, 3, 4, 5};
	ASSERT_EQ(5, b.size());
	ASSERT_EQ(a, b);
}
TEST(LinkedListTests, LinkedListRotateRightTest)
{
	vector<long> a, b;
	a = {1, 2, 3, 4, 5};
	LinkedList<long> ll(a);
	ASSERT_EQ(5, ll.Length());
	ll.RotateRight(2);
	ASSERT_EQ(5, ll.Length());
	a.clear();
	b = {4, 5, 1, 2, 3};
	ll.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	b.clear();
	a = {1, 2, 3};
	LinkedList<long> ll1(a);
	ASSERT_EQ(3, ll1.Length());
	ll1.RotateRight(2000000000);
	ASSERT_EQ(3, ll1.Length());
	b = {2, 3, 1};
	a.clear();
	ll1.ToVector(a);
	ASSERT_EQ(b, a);

	a.clear();
	a = {1};
	LinkedList<long> ll2(a);
	ASSERT_EQ(1, ll2.Length());
	ll2.RotateRight(1);
	ASSERT_EQ(1, ll2.Length());
	b.clear();
	b = {1};
	a.clear();
	ll2.ToVector(a);
	ASSERT_EQ(b, a);
}
class ConnectedCellsInAGridLinkedListTestFixture : public testing::TestWithParam<tuple<size_t, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_grid = get<1>(GetParam());
	}
	size_t ConnectedCellsInAGridLinkedListTest()
	{
		return ConnectedCellsInAGridLinkedList(_grid);
	}

protected:
	vector<vector<long>> _grid;
	size_t _expected;
};
TEST_P(ConnectedCellsInAGridLinkedListTestFixture, ConnectedCellsInAGridLinkedListTests)
{
	ASSERT_EQ(this->_expected, this->ConnectedCellsInAGridLinkedListTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListTests,
	ConnectedCellsInAGridLinkedListTestFixture,
	::testing::Values(make_tuple(5, vector<vector<long>>{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}}),
					  make_tuple(8, vector<vector<long>>{{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}),
					  make_tuple(5, vector<vector<long>>{{1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1}}),
					  make_tuple(15, vector<vector<long>>{{0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0}}),
					  make_tuple(9, vector<vector<long>>{{1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0}}),
					  make_tuple(1, vector<vector<long>>{{1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0}})));