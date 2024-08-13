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
		LinkedList<size_t> listAdditionResult(_ll1.AddNumbers(_ll2));
		_data1.clear();
		listAdditionResult.ToVector(_data1);
		return _data1;
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
class LinkedListReversalTestFixture : public testing::TestWithParam<tuple<vector<size_t>, size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_start = get<1>(GetParam());
		_end = get<2>(GetParam());
		_data = get<3>(GetParam());
		_ll.LoadData(_data);
	}
	vector<size_t> LinkedListReversalTest()
	{
		_ll.Reverse(_start, _end);
		_data.clear();
		_ll.ToVector(_data);
		return _data;
	}

protected:
	LinkedList<size_t> _ll;
	size_t _start, _end;
	vector<size_t> _expected;
	vector<size_t> _data;
};
TEST_P(LinkedListReversalTestFixture, LinkedListReversalTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListReversalTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListReversalTests,
	LinkedListReversalTestFixture,
	::testing::Values(make_tuple(vector<size_t>{1, 4, 3, 2, 5}, 1, 3, vector<size_t>{1, 2, 3, 4, 5}), make_tuple(vector<size_t>{5, 4, 3, 2, 1}, 0, 4, vector<size_t>{1, 2, 3, 4, 5}), make_tuple(vector<size_t>{4, 3, 2, 1, 5}, 0, 3, vector<size_t>{1, 2, 3, 4, 5}), make_tuple(vector<size_t>{1, 5, 4, 3, 2}, 1, 4, vector<size_t>{1, 2, 3, 4, 5}), make_tuple(vector<size_t>{1, 2, 3, 4, 5}, 1, 1, vector<size_t>{1, 2, 3, 4, 5}), make_tuple(vector<size_t>{2, 1}, 0, 1, vector<size_t>{1, 2})));
class LinkedListRemoveDuplicatesTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_ll.LoadData(_data);
	}
	vector<long> LinkedListRemoveDuplicatesTest()
	{
		_ll.RemoveDuplicates();
		_data.clear();
		_ll.ToVector(_data);
		return _data;
	}

protected:
	LinkedList<long> _ll;
	vector<long> _expected;
	vector<long> _data;
};
TEST_P(LinkedListRemoveDuplicatesTestFixture, LinkedListRemoveDuplicatesTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListRemoveDuplicatesTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListRemoveDuplicatesTests,
	LinkedListRemoveDuplicatesTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 2, 3, 4, 5}, vector<long>{1, 2, 3, 3, 4, 4, 5}), make_tuple(vector<long>{1, 2, 3, 4, 5}, vector<long>{1, 1, 2, 3, 3, 4, 4, 5}), make_tuple(vector<long>{1}, vector<long>{1}), make_tuple(vector<long>{1}, vector<long>{1, 1}), make_tuple(vector<long>{1, 2}, vector<long>{1, 1, 2, 2}), make_tuple(vector<long>{1, 2, 3}, vector<long>{1, 1, 1, 2, 3}), make_tuple(vector<long>{-1, 0, 3}, vector<long>{-1, 0, 0, 0, 0, 3, 3})));
class LinkedListRemoveAllDuplicatesTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_ll.LoadData(_data);
	}
	vector<long> LinkedListRemoveAllDuplicatesTest()
	{
		_ll.RemoveAllDuplicates();
		_data.clear();
		_ll.ToVector(_data);
		return _data;
	}

protected:
	LinkedList<long> _ll;
	vector<long> _expected;
	vector<long> _data;
};
TEST_P(LinkedListRemoveAllDuplicatesTestFixture, LinkedListRemoveAllDuplicatesTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListRemoveAllDuplicatesTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListRemoveAllDuplicatesTests,
	LinkedListRemoveAllDuplicatesTestFixture,
	::testing::Values(make_tuple(vector<long>{2, 5}, vector<long>{1, 1, 2, 3, 3, 4, 4, 5}), make_tuple(vector<long>{}, vector<long>{1, 1, 3, 3, 4, 4}), make_tuple(vector<long>{1}, vector<long>{1}), make_tuple(vector<long>{}, vector<long>{1, 1}), make_tuple(vector<long>{}, vector<long>{1, 1, 2, 2}), make_tuple(vector<long>{2, 3}, vector<long>{1, 1, 1, 2, 3}), make_tuple(vector<long>{-1}, vector<long>{-1, 0, 0, 0, 0, 3, 3})));

class LinkedListSortTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_ll.LoadData(_data);
	}
	vector<long> LinkedListSortTest()
	{
		_ll.Sort();
		_data.clear();
		_ll.ToVector(_data);
		return _data;
	}

protected:
	LinkedList<long> _ll;
	vector<long> _expected;
	vector<long> _data;
};
TEST_P(LinkedListSortTestFixture, LinkedListSortTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListSortTests,
	LinkedListSortTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 2}, vector<long>{2, 1}), make_tuple(vector<long>{1, 2, 3, 4}, vector<long>{4, 2, 1, 3}), make_tuple(vector<long>{-1, 0, 3, 4, 5}, vector<long>{-1, 5, 3, 4, 0})));
class LinkedListRotateRightTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_rotationCount = get<1>(GetParam());
		_data = get<2>(GetParam());
		_ll.LoadData(_data);
	}
	/*
	-1, 5, 3, 4, 0
	0, -1, 5, 3, 4 (R1)
	4, 0, -1, 5, 3 (R2)
	3, 4, 0, -1, 5 (R3)
	*/
	vector<long> LinkedListRotateRightTest()
	{
		_ll.RotateRight(_rotationCount);
		_data.clear();
		_ll.ToVector(_data);
		return _data;
	}

protected:
	LinkedList<long> _ll;
	size_t _rotationCount;
	vector<long> _expected;
	vector<long> _data;
};
TEST_P(LinkedListRotateRightTestFixture, LinkedListRotateRightTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListRotateRightTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListRotateRightTests,
	LinkedListRotateRightTestFixture,
	::testing::Values(make_tuple(vector<long>{4, 5, 1, 2, 3}, 2, vector<long>{1, 2, 3, 4, 5}), make_tuple(vector<long>{2, 3, 1}, 2000000000, vector<long>{1, 2, 3}), make_tuple(vector<long>{3, 4, 0, -1, 5}, 3, vector<long>{-1, 5, 3, 4, 0}), make_tuple(vector<long>{1}, 10, vector<long>{1})));

class LinkedListConnectedCellsInAGridTestFixture : public testing::TestWithParam<tuple<size_t, vector<vector<long>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_grid = get<1>(GetParam());
	}
	size_t LinkedListConnectedCellsInAGridTest()
	{
		return ConnectedCellsInAGridLinkedList(_grid);
	}

protected:
	vector<vector<long>> _grid;
	size_t _expected;
};
TEST_P(LinkedListConnectedCellsInAGridTestFixture, LinkedListConnectedCellsInAGridTests)
{
	ASSERT_EQ(this->_expected, this->LinkedListConnectedCellsInAGridTest());
}
INSTANTIATE_TEST_SUITE_P(
	LinkedListConnectedCellsInAGridTests,
	LinkedListConnectedCellsInAGridTestFixture,
	::testing::Values(make_tuple(5, vector<vector<long>>{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}}),
					  make_tuple(8, vector<vector<long>>{{0, 0, 1, 1}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}),
					  make_tuple(5, vector<vector<long>>{{1, 1, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {0, 1, 0, 1, 1}}),
					  make_tuple(15, vector<vector<long>>{{0, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 0, 1, 0}, {0, 1, 0, 1, 1}, {0, 1, 1, 1, 0}}),
					  make_tuple(9, vector<vector<long>>{{1, 1, 1, 0, 1}, {0, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 1, 0}}),
					  make_tuple(1, vector<vector<long>>{{1, 0, 0, 1, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 1, 0, 0}})));