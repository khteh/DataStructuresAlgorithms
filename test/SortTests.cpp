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

class OrderArrayIntoNegativePositiveSeriesTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<long> OrderArrayIntoNegativePositiveSeriesTest()
	{
		OrderArrayIntoNegativePositiveSeries(_data);
		return _data;
	}

protected:
	vector<long> _expected, _data;
	Sort<long> _sort;
};
TEST_P(OrderArrayIntoNegativePositiveSeriesTestFixture, OrderArrayIntoNegativePositiveSeriesTests)
{
	ASSERT_EQ(this->_expected, this->OrderArrayIntoNegativePositiveSeriesTest());
}
INSTANTIATE_TEST_SUITE_P(
	OrderArrayIntoNegativePositiveSeriesTests,
	OrderArrayIntoNegativePositiveSeriesTestFixture,
	::testing::Values(make_tuple(vector<long>{2, -1, 9, -3, 5, -7, -8, -5, -7}, vector<long>{2, -1, -3, -7, -8, 9, 5, -5, -7}), make_tuple(vector<long>{-1, 9, -3, 5, -7, 2, -8, -5, -7}, vector<long>{-1, -3, -7, -8, 9, 5, -5, -7, 2}),
					  make_tuple(vector<long>{2, -1, 9, -3, 5, -7, -8, -5, -7}, vector<long>{2, -1, -3, -7, -8, 9, 5, -5, -7}), make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, 9, 5, 3, 2, 1, -1, -3, -7, -8, -5, -7}),
					  make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, -1, -3, -7, -8, -5, -7, 9, 5, 3, 2, 1}), make_tuple(vector<long>{2, -1, 9, -3, 5, -7, 3, -8, 2, -5, 1, -7}, vector<long>{2, -1, -3, -7, 9, 5, 3, 2, 1, -8, -5, -7}),
					  make_tuple(vector<long>{-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1}, vector<long>{-1, -3, -7, 2, 9, 5, 3, 2, 1, -8, -5, -7}), make_tuple(vector<long>{-1, 2, -3, 9, -7, 5, -8, 3, -5, 2, -7, 1}, vector<long>{-1, -3, -7, -8, -5, -7, 2, 9, 5, 3, 2, 1})));

TEST(SortTests, BubbleSortTest)
{
	Sort<long> sort;
	// Test Sorting algorithms
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	vector<long> a;
	a = {1, 0, -1};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.BubbleSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.BubbleSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
}
TEST(SortTests, QuickSortTest)
{
	Sort<long> sort;
	vector<long> a;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 3, 0, 2};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.QuickSort(a, 0, a.size() - 1);
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	a = {1, 0, -1};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.QuickSort(a, 0, a.size() - 1);
	ASSERT_TRUE(ranges::is_sorted(a));
	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.QuickSort(a, 0, a.size() - 1);
	ASSERT_TRUE(ranges::is_sorted(a));
}
TEST(SortTests, SelectionSortTest)
{
	Sort<long> sort;
	vector<long> a;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 0, -1};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.SelectionSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.SelectionSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
}
TEST(SortTests, InsertionSortTest)
{
	Sort<long> sort;
	vector<long> a;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 0, -1};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.InsertionSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.InsertionSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
}
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
TEST(SortTests, HeapSortTest)
{
	Sort<long> sort;
	vector<long> a;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 0, -1};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.HeapSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	a.resize(100);
	ranges::generate(a, [&]
					 { return uniformDistribution(engine); });
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.HeapSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));
}
TEST(SortTests, CountingSortTest)
{
	Sort<long> sort;
	vector<long> a;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 0, 2};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.CountingSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	a = {456, 789, 123};
	ASSERT_FALSE(ranges::is_sorted(a));
	sort.CountingSort(a);
	ASSERT_TRUE(ranges::is_sorted(a));

	vector<vector<string>> strSort{
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
		{"1250", "the"}};
	ASSERT_EQ(sort.StringCountingSort(strSort), "to be or not to be - that is the question");

	strSort.clear();
	strSort = {{"100", "!!!"}, {"55", "Hello"}, {"10", "Hey,"}, {"55", "World"}};
	ASSERT_EQ(sort.StringCountingSort(strSort), "Hey, Hello World !!!");
}
TEST(SortTests, WiggleSortTest)
{
	Sort<long> sort;
	vector<long> a, b;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 5, 1, 1, 6, 4};
	b = {1, 6, 1, 5, 1, 4};
	sort.WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = {1, 3, 2, 2, 3, 1};
	b = {2, 3, 1, 3, 1, 2};
	sort.WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = {1, 1, 2, 1, 2, 2, 1};
	b = {1, 2, 1, 2, 1, 2, 1};
	sort.WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = {5, 3, 1, 2, 6, 7, 8, 5, 5};
	b = {5, 8, 5, 7, 3, 6, 2, 5, 1};
	sort.WiggleSort(a);
	ASSERT_EQ(a, b);
}
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
TEST(SortTests, TopDownMergeSortCountConversionsTest)
{
	Sort<long> sort;
	vector<long> a, b;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = {1, 5, 3, 7};
	b = a;
	ASSERT_FALSE(ranges::is_sorted(a));
	ASSERT_EQ(1, sort.TopDownMergeSortCountConversions(b, a, 0, a.size()));
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	b.clear();
	a = {7, 5, 3, 1};
	b = a;
	ASSERT_FALSE(ranges::is_sorted(a));
	ASSERT_EQ(6, sort.TopDownMergeSortCountConversions(b, a, 0, a.size()));
	ASSERT_TRUE(ranges::is_sorted(a));

	a.clear();
	b.clear();
	a = {2, 1, 3, 1, 2};
	b = a;
	ASSERT_FALSE(ranges::is_sorted(a));
	ASSERT_EQ(4, sort.TopDownMergeSortCountConversions(b, a, 0, a.size()));
	ASSERT_TRUE(ranges::is_sorted(a));
}
class SortSwapCountTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long SortSwapCountTest()
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
	SortTests,
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