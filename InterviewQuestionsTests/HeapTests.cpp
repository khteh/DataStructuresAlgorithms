#include "pch.h"
using namespace std;
TEST(HeapTests, MaxHeapTest) {
	vector<long> result;
	Heap<long> heap(50, HeapType::MaxHeap);
	heap.InsertItem(-100);
	heap.InsertItem(0);
	heap.InsertItem(10);
	heap.InsertItem(-50);
	heap.InsertItem(60);
	heap.InsertItem(100);
	heap.InsertItem(75);
	heap.InsertItem(150);
	ASSERT_EQ(9, heap.Count());
	ASSERT_EQ(4, heap.MaxDepth(heap.Root())/* Change this assertion number if items are added/removed*/);
	cout << "MaxHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	ASSERT_FALSE(nodes.empty());
	cout << "MaxHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	size_t heapCount = heap.Count();
	heap.Serialize(result);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(0, heap.Count());
	ASSERT_EQ(heapCount, result.size());
	cout << "Serialized Max Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
		if (it != result.begin())
			if (*it > *(it - 1))
			{
				throw runtime_error("Heap building failed!");
				break;
			}
	}
}
TEST(HeapTests, MinMaxHeapTest) {
	vector<long> result;
	Heap<long> heap(50, HeapType::MinMaxHeap);
	heap.InsertItem(-100);
	heap.InsertItem(0);
	heap.InsertItem(10);
	heap.InsertItem(-50);
	heap.InsertItem(60);
	heap.InsertItem(100);
	heap.InsertItem(75);
	heap.InsertItem(150);
	ASSERT_EQ(9, heap.Count());
	ASSERT_EQ(4, heap.MaxDepth(heap.Root())/* Change this assertion number if items are added/removed*/);
	cout << "MinMaxHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	ASSERT_FALSE(nodes.empty());
	cout << "MinMaxHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	size_t heapCount = heap.Count();
	heap.Serialize(result);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(0, heap.Count());
	ASSERT_EQ(heapCount, result.size());
	cout << "Serialized MinMax Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
		if (it != result.begin())
			if (*it < *(it - 1))
			{
				throw runtime_error("Heap building failed!");
				break;
			}
	}
}
TEST(HeapTests, MinHeapTest) {
	vector<long> result;
	Heap<long> heap(50);
	heap.InsertItem(-100);
	heap.InsertItem(0);
	heap.InsertItem(10);
	heap.InsertItem(-50);
	heap.InsertItem(60);
	heap.InsertItem(100);
	heap.InsertItem(75);
	heap.InsertItem(150);
	ASSERT_EQ(9, heap.Count());
	ASSERT_EQ(4, heap.MaxDepth(heap.Root())/* Change this assertion number if items are added/removed*/);
	cout << "MinHeap content: " << endl;
	heap.PrintTree();
	cout << endl;
	map<size_t, vector<shared_ptr<Node<long>>>> nodes;
	heap.GetNodes(nodes);
	ASSERT_FALSE(nodes.empty());
	cout << "MinHeap content by level:" << endl;
	for (map<size_t, vector<shared_ptr<Node<long>>>>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		cout << "Level " << it->first << ": ";
		for (vector<shared_ptr<Node<long>>>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
			cout << (*it1)->Item() << " ";
		cout << endl;
	}
	size_t heapCount = heap.Count();
	heap.Serialize(result);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(0, heap.Count());
	ASSERT_EQ(heapCount, result.size());
	cout << "Serialized Min Heap: ";
	for (vector<long>::const_iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
		if (it != result.begin())
		{
			if (*it < *(it - 1))
			{
				throw runtime_error("Heap building failed!");
				break;
			}
		}
	}
}