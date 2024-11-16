#include "pch.h"
using namespace std;
class AlternateSignSortNumbersTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<long> AlternateSignSortNumbersTest()
	{
		_sort.AlternateSignSortNumbers(_data);
		return _data;
	}

protected:
	vector<long> _expected, _data;
	Sort<long> _sort;
};
TEST_P(AlternateSignSortNumbersTestFixture, AlternateSignSortNumbersTests)
{
	ASSERT_EQ(this->_expected, this->AlternateSignSortNumbersTest());
}
INSTANTIATE_TEST_SUITE_P(
	AlternateSignSortNumbersTests,
	AlternateSignSortNumbersTestFixture,
	::testing::Values(make_tuple(vector<long>{2, -1, 9, -3, 5, -7, -8, -5, -7}, vector<long>{2, -1, -3, -7, -8, 9, 5, -5, -7}), make_tuple(vector<long>{-1, 9, -3, 5, -7, 2, -8, -5, -7}, vector<long>{-1, -3, -7, -8, 9, 5, -5, -7, 2}),
					  make_tuple(vector<long>{2, -1, 9, -3, 5, -7, -8, -5, -7}, vector<long>{2, -1, -3, -7, -8, 9, 5, -5, -7}), make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7}),
					  make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1}), make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7}),
					  make_tuple(vector<long>{-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1}, vector<long>{-1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7}), make_tuple(vector<long>{-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1}, vector<long>{-1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1})));
class AlternateSignSortNumbers1TestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<long> AlternateSignSortNumbers1Test()
	{
		_sort.AlternateSignSortNumbers1(_data);
		return _data;
	}

protected:
	vector<long> _expected, _data;
	Sort<long> _sort;
};
TEST_P(AlternateSignSortNumbers1TestFixture, AlternateSignSortNumbers1Tests)
{
	ASSERT_EQ(this->_expected, this->AlternateSignSortNumbers1Test());
}
INSTANTIATE_TEST_SUITE_P(
	AlternateSignSortNumbers1Tests,
	AlternateSignSortNumbers1TestFixture,
	::testing::Values(make_tuple(vector<long>{2, -1, 9, -3, 5, -7, -8, -5, -7}, vector<long>{2, -1, -3, -7, -8, 9, 5, -5, -7}), make_tuple(vector<long>{-1, 9, -3, 5, -7, 2, -8, -5, -7}, vector<long>{-1, -3, -7, -8, 9, 5, -5, -7, 2}),
					  make_tuple(vector<long>{2, -1, 9, -3, 5, -7, -8, -5, -7}, vector<long>{2, -1, -3, -7, -8, 9, 5, -5, -7}), make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7}),
					  make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1}), make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7}),
					  make_tuple(vector<long>{-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1}, vector<long>{-1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7}), make_tuple(vector<long>{-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1}, vector<long>{-1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1})));
template <typename TResult, typename T>
class SortTestFixture
{
public:
	void SetUp(TResult expected, vector<T> data)
	{
		_expected = expected;
		_data = data;
	}

protected:
	Sort<T> _sort;
	TResult _expected;
	vector<T> _data;
};
class BubbleSortTestFixture : public SortTestFixture<bool, long>, public testing::TestWithParam<tuple<bool, vector<long>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool BubbleSortTest()
	{
		_sort.BubbleSort(_data);
		return ranges::is_sorted(_data);
	}
};
TEST_P(BubbleSortTestFixture, BubbleSortTests)
{
	ASSERT_EQ(this->_expected, this->BubbleSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	BubbleSortTests,
	BubbleSortTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 0, -1}), make_tuple(true, vector<long>{2, 2, 2, 1, 1, 1, 0, 0, 0, -1, -1, -1})));
class QuickSortTestFixture : public SortTestFixture<bool, long>, public testing::TestWithParam<tuple<bool, vector<long>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool QuickSortTest()
	{
		_sort.QuickSort(_data, 0, _data.size() - 1);
		return ranges::is_sorted(_data);
	}
};
TEST_P(QuickSortTestFixture, QuickSortTests)
{
	ASSERT_EQ(this->_expected, this->QuickSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	QuickSortTests,
	QuickSortTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 0, -1}), make_tuple(true, vector<long>{2, 2, 2, 1, 1, 1, 0, 0, 0, -1, -1, -1})));
class SelectionSortTestFixture : public SortTestFixture<bool, long>, public testing::TestWithParam<tuple<bool, vector<long>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool SelectionSortTest()
	{
		_sort.SelectionSort(_data);
		return ranges::is_sorted(_data);
	}
};
TEST_P(SelectionSortTestFixture, SelectionSortTests)
{
	ASSERT_EQ(this->_expected, this->SelectionSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	SelectionSortTests,
	SelectionSortTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 0, -1}), make_tuple(true, vector<long>{2, 2, 2, 1, 1, 1, 0, 0, 0, -1, -1, -1})));
class InsertionSortTestFixture : public SortTestFixture<bool, long>, public testing::TestWithParam<tuple<bool, vector<long>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool InsertionSortTest()
	{
		_sort.InsertionSort(_data);
		return ranges::is_sorted(_data);
	}
};
TEST_P(InsertionSortTestFixture, InsertionSortTests)
{
	ASSERT_EQ(this->_expected, this->InsertionSortTest());
}
TEST_P(InsertionSortTestFixture, InsertionSortTest)
{
	ASSERT_EQ(this->_expected, this->InsertionSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	InsertionSortTests,
	InsertionSortTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 0, -1}), make_tuple(true, vector<long>{2, 2, 2, 1, 1, 1, 0, 0, 0, -1, -1, -1})));
TEST(SortTests, TopDownMergeSortTest)
{
	Sort<long> sort;
	vector<long> a, b;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 0, -1};
	b = a;
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.TopDownMergeSort(b, a, 0, a.size());
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	a = {2, 1, 3, 1, 2};
	b = a;
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.TopDownMergeSort(b, a, 0, a.size());
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	b.clear();
	b.assign(a.begin(), a.end());
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.TopDownMergeSort(b, a, 0, a.size());
	ASSERT_TRUE(ranges::is_sorted(a));
}
TEST(SortTests, BottomUpMergeSortTest)
{
	Sort<long> sort;
	vector<long> a, b;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 0, -1};
	b = a;
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.BottomUpMergeSort(a, b);
	ASSERT_TRUE(ranges::is_sorted(a));
	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	b.clear();
	b.assign(a.begin(), a.end());
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.BottomUpMergeSort(a, b);
	ASSERT_TRUE(ranges::is_sorted(a));
}
class HeapSortTestFixture : public SortTestFixture<bool, long>, public testing::TestWithParam<tuple<bool, vector<long>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool HeapSortTest()
	{
		_sort.HeapSort(_data);
		return ranges::is_sorted(_data);
	}
};
TEST_P(HeapSortTestFixture, HeapSortTests)
{
	ASSERT_EQ(this->_expected, this->HeapSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	HeapSortTests,
	HeapSortTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 0, -1}), make_tuple(true, vector<long>{2, 2, 2, 1, 1, 1, 0, 0, 0, -1, -1, -1})));
class CountingSortTestFixture : public SortTestFixture<bool, size_t>, public testing::TestWithParam<tuple<bool, vector<size_t>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool CountingSortTest()
	{
		_sort.CountingSort(_data);
		return ranges::is_sorted(_data);
	}
};
TEST_P(CountingSortTestFixture, CountingSortTests)
{
	ASSERT_EQ(this->_expected, this->CountingSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	CountingSortTests,
	CountingSortTestFixture,
	::testing::Values(make_tuple(true, vector<size_t>{1, 0, 2}), make_tuple(true, vector<size_t>{2, 2, 2, 1, 1, 1, 0, 0, 0, 3, 3, 3})));
class StringCountingSortTestFixture : public testing::TestWithParam<tuple<string, vector<vector<string>>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	string StringCountingSortTest()
	{
		return _sort.StringCountingSort(_data);
	}

protected:
	Sort<string> _sort;
	string _expected;
	vector<vector<string>> _data;
};
TEST_P(StringCountingSortTestFixture, StringCountingSortTests)
{
	ASSERT_EQ(this->_expected, this->StringCountingSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	StringCountingSortTests,
	StringCountingSortTestFixture,
	::testing::Values(make_tuple("to be or not to be - that is the question", vector<vector<string>>{
																				  {"400", "not"},
																				  {"1500", "question"},
																				  {"550", "to"},
																				  {"100", "to"},
																				  {"650", "be"},
																				  {"1100", "-"},
																				  {"200", "be"},
																				  {"1234", "is"},
																				  {"1100", "that"},
																				  {"300", "or"},
																				  {"1250", "the"}}),
					  make_tuple("Hey, Hello World !!!", vector<vector<string>>{{"100", "!!!"}, {"55", "Hello"}, {"10", "Hey,"}, {"55", "World"}})));
class WiggleSortTestFixture : public SortTestFixture<vector<long>, long>, public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		SortTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	vector<long> WiggleSortTest()
	{
		_sort.WiggleSort(_data);
		return _data;
	}
};
TEST_P(WiggleSortTestFixture, WiggleSortTests)
{
	ASSERT_EQ(this->_expected, this->WiggleSortTest());
}
INSTANTIATE_TEST_SUITE_P(
	WiggleSortTests,
	WiggleSortTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 6, 1, 5, 1, 4}, vector<long>{1, 5, 1, 1, 6, 4}), make_tuple(vector<long>{2, 3, 1, 3, 1, 2}, vector<long>{1, 3, 2, 2, 3, 1}), make_tuple(vector<long>{1, 2, 1, 2, 1, 2, 1}, vector<long>{1, 1, 2, 1, 2, 2, 1}), make_tuple(vector<long>{5, 8, 5, 7, 3, 6, 2, 5, 1}, vector<long>{5, 3, 1, 2, 6, 7, 8, 5, 5})));

TEST(SortTests, LexicographicSortTest)
{
	vector<string> strings = {"abcczch", "abcchcz", "abcde", "ABCCZCH", "ABCCHCZ", "ABCDE"};
	vector<string> strings1 = {"abcchcz", "ABCCHCZ", "abcczch", "ABCCZCH", "abcde", "ABCDE"};
	ranges::sort(strings, &Sort<string>::LexicographicSort);
	ASSERT_EQ(strings1, strings);
}
TEST(SortTests, Merge2SortedListsTest)
{
	vector<long> a, b;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a.resize(10);
	b.resize(20);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ranges::generate(b, [&]
					 { return uniformDistribution(engine); });
	ranges::sort(a);
	ranges::sort(b);
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		if (it != a.begin())
			ASSERT_LT(*(it - 1), *it);
	a.resize(20);
	b.resize(10);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ranges::generate(b, [&]
					 { return uniformDistribution(engine); });
	ranges::sort(a);
	ranges::sort(b);
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		if (it != a.begin())
			ASSERT_LT(*(it - 1), *it);
}
class TopDownMergeSortCountConversionsTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, vector<size_t>, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_data1 = get<2>(GetParam());
		_start = get<3>(GetParam());
		_end = get<4>(GetParam());
	}
	size_t TopDownMergeSortCountConversionsTest()
	{
		return _sort.TopDownMergeSortCountConversions(_data, _data1, _start, _end);
	}

protected:
	Sort<size_t> _sort;
	size_t _expected, _start, _end;
	vector<size_t> _data, _data1;
};
TEST_P(TopDownMergeSortCountConversionsTestFixture, TopDownMergeSortCountConversionsTests)
{
	ASSERT_EQ(this->_expected, this->TopDownMergeSortCountConversionsTest());
	ASSERT_TRUE(ranges::is_sorted(this->_data1));
}
INSTANTIATE_TEST_SUITE_P(
	TopDownMergeSortCountConversionsTests,
	TopDownMergeSortCountConversionsTestFixture,
	::testing::Values(make_tuple(1, vector<size_t>{1, 5, 3, 7}, vector<size_t>{1, 5, 3, 7}, 0, 4),
					  make_tuple(6, vector<size_t>{7, 5, 3, 1}, vector<size_t>{7, 5, 3, 1}, 0, 4),
					  make_tuple(4, vector<size_t>{2, 1, 3, 1, 2}, vector<size_t>{2, 1, 3, 1, 2}, 0, 5)));

class SortSwapCountTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t SortSwapCountTest()
	{
		return _sort.SortSwapCount(_data);
	}

protected:
	Sort<size_t> _sort;
	size_t _expected;
	vector<size_t> _data;
};
TEST_P(SortSwapCountTestFixture, SortSwapCountTests)
{
	ASSERT_EQ(this->_expected, this->SortSwapCountTest());
}
INSTANTIATE_TEST_SUITE_P(
	SortSwapCountTests,
	SortSwapCountTestFixture,
	::testing::Values(make_tuple(2, vector<size_t>{2, 5, 3, 1}),
					  make_tuple(2, vector<size_t>{3, 4, 2, 5, 1}),
					  make_tuple(2, vector<size_t>{7, 15, 12, 3})));
TEST(SortTests, DutchPartitioningTest)
{
	vector<long> data, data1;
	data = {2, 0, 2, 1, 1, 0};
	data1 = {0, 0, 1, 1, 2, 2};
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {1, 0, 2, 1, 2, 0};
	data1 = {0, 0, 1, 2, 2, 1};
	DutchPartitioning(data, 0);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {2, 0, 1, 2, 1, 0};
	data1 = {0, 0, 2, 1, 1, 2};
	DutchPartitioning(data, 0);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {2, 0, 2, 1, 1, 0};
	data1 = {0, 1, 1, 0, 2, 2};
	DutchPartitioning(data, 2);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {-1, 0, -2, -1, -2, 0};
	data1 = {-1, -2, -1, -2, 0, 0};
	DutchPartitioning(data, 0);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {-1, 0, -2, -1, -2, 0};
	data1 = {-2, -2, -1, -1, 0, 0};
	DutchPartitioning(data, -1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {-1, 0, -2, -1, -2, 0};
	data1 = {-2, -2, -1, 0, 0, -1};
	DutchPartitioning(data, -2);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {0};
	data1 = data;
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {1};
	data1 = data;
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = {2};
	data1 = data;
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);
}
TEST(SortTests, CanFinishCourseTopologicalSortTest)
{
	Sort<size_t> sort;
	vector<vector<size_t>> grid = {{1, 0}};
	vector<size_t> data, expected;
	ASSERT_TRUE(sort.CanFinishCourseTopologicalSort(2, grid, data));
	ASSERT_FALSE(data.empty());
	ASSERT_EQ(2, data.size());
	expected = {0, 1};
	ASSERT_EQ(expected, data);
	grid.clear();
	data.clear();
	grid = {{1, 0}, {0, 1}};
	ASSERT_FALSE(sort.CanFinishCourseTopologicalSort(2, grid, data));
	ASSERT_TRUE(data.empty());
	grid.clear();
	grid = {{1, 0}, {2, 0}};
	data.clear();
	ASSERT_TRUE(sort.CanFinishCourseTopologicalSort(3, grid, data));
	ASSERT_FALSE(data.empty());
	ASSERT_EQ(3, data.size());
	expected = {0, 1, 2};
	ASSERT_EQ(expected, data);
	data.clear();
	grid.push_back(vector<size_t>{0, 2}); // Add another dependency will fail the same requirement
	ASSERT_FALSE(sort.CanFinishCourseTopologicalSort(3, grid, data));
	ASSERT_TRUE(data.empty());
	grid.clear();
	data.clear();
	grid = {{1, 0}, {0, 2}, {2, 1}};
	ASSERT_FALSE(sort.CanFinishCourseTopologicalSort(3, grid, data));
	ASSERT_TRUE(data.empty());
}