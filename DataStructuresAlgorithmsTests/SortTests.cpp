#include "pch.h"
using namespace std;
TEST(SortTests, SortTest) {
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
	sort(buffer.begin(), buffer.end());
	BubbleSort(sortData);
	ASSERT_EQ(sortData, buffer);
	sortData.clear();
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
	sort(buffer.begin(), buffer.end());
	QuickSort(sortData, 0, sortData.size() - 1);
	ASSERT_EQ(sortData, buffer);

	sortData.clear();
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
	sort(buffer.begin(), buffer.end());
	SelectionSort(sortData);
	ASSERT_EQ(sortData, buffer);

	sortData.clear();
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
	sort(buffer.begin(), buffer.end());
	InsertionSort(sortData);
	ASSERT_EQ(sortData, buffer);

	sortData.clear();
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
	sort(a.begin(), a.end());
	buffer.clear();
	buffer = sortData;
	TopDownMergeSort(buffer, sortData, 0, sortData.size());
	ASSERT_EQ(a, sortData);

	sortData.clear();
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
	sort(a.begin(), a.end());
	buffer = sortData;
	BottomUpMergeSort(sortData, buffer);
	ASSERT_EQ(a, sortData);

	sortData.clear();
	sortData = { 1, 0, -1 };
	HeapSort(sortData);
	ASSERT_EQ(-1, sortData[0]);
	ASSERT_EQ(0, sortData[1]);
	ASSERT_EQ(1, sortData[2]);

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

	sortData.clear();
	sortData.resize(100);
	ranges::generate(sortData, [&] { return uniformDistribution(engine); });
	buffer.clear();
	buffer.assign(sortData.begin(), sortData.end());
	sort(buffer.begin(), buffer.end());
	HeapSort(sortData);
	ASSERT_EQ(sortData, buffer);

	a.clear();
	a.resize(10);
	b.resize(20);
	ranges::generate(a, [&] { return uniformDistribution(engine); });
	ranges::generate(b, [&] { return uniformDistribution(engine); });
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
	{
		if (it != a.begin())
			if (*it < *(it - 1))
			{
				throw runtime_error("Merge 2 sorted lists failed!");
				break;
			}
	}
	a.resize(20);
	b.resize(10);
	ranges::generate(a, [&] { return uniformDistribution(engine); });
	ranges::generate(b, [&] { return uniformDistribution(engine); });
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	Merge(a, b);
	for (vector<long>::iterator it = a.begin(); it != a.end(); it++)
	{
		if (it != a.begin())
			if (*it < *(it - 1))
			{
				cout << "Merge 2 sorted lists failed!";
				assert(false);
				break;
			}
	}
	a.clear();
	b.clear();
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
	udata.clear();
	udata = { 2, 5, 3, 1 };
	ASSERT_EQ(2, SortSwapCount(udata));
	udata.clear();
	udata = { 3, 4, 2, 5, 1 };
	ASSERT_EQ(2, SortSwapCount(udata));

	udata.clear();
	udata = { 2, 0, 2, 1, 1, 0 };
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = { 0, 0, 1, 1, 2, 2 };
	ASSERT_EQ(udata, udata1);

	udata.clear();
	udata = { 0 };
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = { 0 };
	ASSERT_EQ(udata, udata1);

	udata.clear();
	udata = { 1 };
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = { 1 };
	ASSERT_EQ(udata, udata1);

	udata.clear();
	udata = { 2 };
	DutchPartitioning(udata, 1);
	udata1.clear();
	udata1 = { 2 };
	ASSERT_EQ(udata, udata1);

	a.clear();
	a = { 1, 5, 1, 1, 6, 4 };
	WiggleSort(a);
	b.clear();
	b = { 1, 6, 1, 5, 1, 4 };
	ASSERT_EQ(a, b);

	a.clear();
	a = { 1, 3, 2, 2, 3, 1 };
	WiggleSort(a);
	b.clear();
	b = { 2, 3, 1, 3, 1, 2 };
	ASSERT_EQ(a, b);

	a.clear();
	a = { 1, 1, 2, 1, 2, 2, 1 };
	b.clear();
	b = { 1, 2, 1, 2, 1, 2, 1 };
	WiggleSort(a);
	ASSERT_EQ(a, b);

	a.clear();
	a = { 5, 3, 1, 2, 6, 7, 8, 5, 5 };
	b.clear();
	b = { 5, 8, 5, 7, 3, 6, 2, 5, 1 };
	WiggleSort(a);
	ASSERT_EQ(a, b);
}