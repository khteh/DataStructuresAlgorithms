#include "pch.h"
using namespace std;
TEST(SortTests, BubbleSortTest) {
	// Test Sorting algorithms
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	vector<long> a, b, sortData, buffer;
	vector<size_t> udata, udata1;
	sortData.clear();
	sortData = { 1, 0, -1 };
	BubbleSort(sortData);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);
	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	ranges::sort(buffer);
	BubbleSort(sortData);
	ASSERT_EQ(sortData, buffer);
}
TEST(SortTests, QuickSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	sortData = { 1, 3, 0, 2 };
	QuickSort(sortData, 0, sortData.size() - 1);
	ASSERT_EQ(0, sortData[0]);
	ASSERT_EQ(1, sortData[1]);
	ASSERT_EQ(2, sortData[2]);
	ASSERT_EQ(3, sortData[3]);

	sortData.clear();
	sortData = { 1, 0, -1 };
	QuickSort(sortData, 0, sortData.size() - 1);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);
	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	ranges::sort(buffer);
	QuickSort(sortData, 0, sortData.size() - 1);
	ASSERT_EQ(sortData, buffer);
}
TEST(SortTests, SelectionSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	sortData = { 1, 0, -1 };
	SelectionSort(sortData);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);
	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	ranges::sort(buffer);
	SelectionSort(sortData);
	ASSERT_EQ(sortData, buffer);
}
TEST(SortTests, InsertionSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	sortData = { 1, 0, -1 };
	InsertionSort(sortData);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);
	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	ranges::sort(buffer);
	InsertionSort(sortData);
	ASSERT_EQ(sortData, buffer);
}
TEST(SortTests, TopDownMergeSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	sortData = { 1, 0, -1 };
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);

	sortData.clear();
	sortData = { 2, 1, 3, 1, 2 };
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	ASSERT_EQ(1, sortData[0]);
	ASSERT_EQ(1, sortData[1]);
	ASSERT_EQ(2, sortData[2]);
	ASSERT_EQ(2, sortData[3]);
	ASSERT_EQ(3, sortData[4]);

	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	a.clear();
	a.assign(sortData.begin(), sortData.end());
	ranges::sort(a);;
	buffer.clear();
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	ASSERT_EQ(a, sortData);
}
TEST(SortTests, BottomUpMergeSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	sortData = { 1, 0, -1 };
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);
	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	a.clear();
	a.assign(sortData.begin(), sortData.end());
	ranges::sort(a);;
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	ASSERT_EQ(a, sortData);
}
TEST(SortTests, HeapSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	sortData = { 1, 0, -1 };
	HeapSort(sortData);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);

	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	ranges::sort(buffer);
	HeapSort(sortData);
	ASSERT_EQ(sortData, buffer);
}
TEST(SortTests, CountingSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	vector<size_t> sortData1{ 1, 0, 2 };
	CountingSort(sortData1);
	ASSERT_EQ(0, sortData1[0]);
	ASSERT_EQ(1, sortData1[1]);
	ASSERT_EQ(2, sortData1[2]);

	sortData1.clear();
	sortData1 = { 456, 789, 123 };
	CountingSort(sortData1);
	ASSERT_EQ(123, sortData1[0]);
	ASSERT_EQ(456, sortData1[1]);
	ASSERT_EQ(789, sortData1[2]);

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
		{"1250", "the"} };
	ASSERT_EQ(CountingSort(strSort), "to be or not to be - that is the question");

	strSort.clear();
	strSort = { {"100", "!!!"}, {"55", "Hello"}, {"10", "Hey,"}, {"55", "World"} };
	ASSERT_EQ(CountingSort(strSort), "Hey, Hello World !!!");
}
TEST(SortTests, WiggleSortTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = { 1, 5, 1, 1, 6, 4 };
	b = { 1, 6, 1, 5, 1, 4 };
	WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = { 1, 3, 2, 2, 3, 1 };
	b = { 2, 3, 1, 3, 1, 2 };
	WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = { 1, 1, 2, 1, 2, 2, 1 };
	b = { 1, 2, 1, 2, 1, 2, 1 };
	WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	b.clear();
	a = { 5, 3, 1, 2, 6, 7, 8, 5, 5 };
	b = { 5, 8, 5, 7, 3, 6, 2, 5, 1 };
	WiggleSort(a);
	ASSERT_EQ(a, b);
}
TEST(SortTests, LexicographicSortTest) {
	vector<string> strings = { "abcczch", "abcchcz", "abcde", "ABCCZCH", "ABCCHCZ", "ABCDE" };
	vector<string> strings1 = { "abcchcz", "ABCCHCZ", "abcczch", "ABCCZCH", "abcde", "ABCDE" };
	ranges::sort(strings.begin(), strings.end(), LexicographicSort);
	ASSERT_EQ(strings1, strings);
}
TEST(SortTests, Merge2SortedListsTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a.resize(10);
	b.resize(20);
	ranges::generate(a, [&] { return uniformDistribution(engine); });
	ranges::generate(b, [&] { return uniformDistribution(engine); });
	ranges::sort(a);;
	ranges::sort(b);;
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		if (it != a.begin())
			ASSERT_LT(*(it - 1), *it);
	a.resize(20);
	b.resize(10);
	ranges::generate(a, [&] { return uniformDistribution(engine); });
	ranges::generate(b, [&] { return uniformDistribution(engine); });
	ranges::sort(a);;
	ranges::sort(b);;
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
		if (it != a.begin())
			ASSERT_LT(*(it - 1), *it);
}
TEST(SortTests, TopDownMergeSortCountConversionsTest) {
	vector<long> a, b, sortData, buffer;
	random_device device;
	mt19937_64 engine(device());
	uniform_int_distribution<long> uniformDistribution;
	a = { 1, 5, 3, 7 };
	b = a;
	ASSERT_EQ(1, TopDownMergeSortCountConversions(b, a, 0, a.size()));
	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(3, a[1]);
	ASSERT_EQ(5, a[2]);
	ASSERT_EQ(7, a[3]);

	a.clear();
	b.clear();
	a = { 7, 5, 3, 1 };
	b = a;
	ASSERT_EQ(6, TopDownMergeSortCountConversions(b, a, 0, a.size()));
	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(3, a[1]);
	ASSERT_EQ(5, a[2]);
	ASSERT_EQ(7, a[3]);

	a.clear();
	b.clear();
	a = { 2, 1, 3, 1, 2 };
	b = a;
	ASSERT_EQ(4, TopDownMergeSortCountConversions(b, a, 0, a.size()));
	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(1, a[1]);
	ASSERT_EQ(2, a[2]);
	ASSERT_EQ(2, a[3]);
	ASSERT_EQ(3, a[4]);
}
TEST(SortTests, SortSwapCountTest) {
	vector<size_t> udata, udata1;
	udata = { 2, 5, 3, 1 };
	ASSERT_EQ(2, SortSwapCount(udata));

	udata.clear();
	udata = { 3, 4, 2, 5, 1 };
	ASSERT_EQ(2, SortSwapCount(udata));
}
TEST(SortTests, DutchPartitioningTest) {
	vector<long> data, data1;
	data = { 2, 0, 2, 1, 1, 0 };
	data1 = { 0, 0, 1, 1, 2, 2 };
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data =  { 1, 0, 2, 1, 2, 0 };
	data1 = { 0, 0, 1, 2, 2, 1 };
	DutchPartitioning(data, 0);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data =  { 2, 0, 1, 2, 1, 0 };
	data1 = { 0, 0, 2, 1, 1, 2 };
	DutchPartitioning(data, 0);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data =  { 2, 0, 2, 1, 1, 0 };
	data1 = { 0, 1, 1, 0, 2, 2 };
	DutchPartitioning(data, 2);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data =  { -1, 0, -2, -1, -2, 0 };
	data1 = { -1, -2, -1, -2, 0, 0 };
	DutchPartitioning(data, 0);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data =  { -1, 0, -2, -1, -2, 0 };
	data1 = { -2, -2, -1, -1, 0, 0 };
	DutchPartitioning(data, -1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data =  { -1, 0, -2, -1, -2, 0 };
	data1 = { -2, -2, -1, 0, 0, -1 };
	DutchPartitioning(data, -2);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = { 0 };
	data1 = data;
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = { 1 };
	data1 = data;
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);

	data.clear();
	data1.clear();
	data = { 2 };
	data1 = data;
	DutchPartitioning(data, 1);
	ASSERT_EQ(data1, data);
}
TEST(SortTests, CanFinishCourseTopologicalSortTest)
{
	vector<vector<size_t>> grid = { {1, 0} };
	vector<size_t> data, expected;
	ASSERT_TRUE(CanFinishCourseTopologicalSort(2, grid, data));
	ASSERT_FALSE(data.empty());
	ASSERT_EQ(2, data.size());
	expected = { 0, 1 };
	ASSERT_EQ(expected, data);
	grid.clear();
	data.clear();
	grid = { {1, 0}, {0, 1} };
	ASSERT_FALSE(CanFinishCourseTopologicalSort(2, grid, data));
	ASSERT_TRUE(data.empty());
	grid.clear();
	grid = { {1, 0}, {2, 0} };
	data.clear();
	ASSERT_TRUE(CanFinishCourseTopologicalSort(3, grid, data));
	ASSERT_FALSE(data.empty());
	ASSERT_EQ(3, data.size());
	expected = {0,1,2};
	ASSERT_EQ(expected, data);
	data.clear();
	grid.push_back(vector<size_t> {0, 2}); // Add another dependency will fail the same requirement
	ASSERT_FALSE(CanFinishCourseTopologicalSort(3, grid, data));
	ASSERT_TRUE(data.empty());
	grid.clear();
	data.clear();
	grid = { {1, 0}, {0, 2}, {2, 1} };
	ASSERT_FALSE(CanFinishCourseTopologicalSort(3, grid, data));
	ASSERT_TRUE(data.empty());
}