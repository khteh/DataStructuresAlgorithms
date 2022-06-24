#include "pch.h"
using namespace std;
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
TEST(SortTests, SortSwapCountTest)
{
	Sort<size_t> sort;
	vector<size_t> udata;
	udata = {2, 5, 3, 1};
	ASSERT_EQ(2, sort.SortSwapCount(udata));

	udata.clear();
	udata = {3, 4, 2, 5, 1};
	ASSERT_EQ(2, sort.SortSwapCount(udata));
}
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