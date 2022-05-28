#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <ranges>
#include <assert.h>
#include "Heap.h"
using namespace std;
namespace ranges = std::ranges;
template <typename T>
class Sort
{
private:
	void Merge(vector<T>&, vector<T>&, size_t, size_t, size_t);
	size_t Partition(vector<T>&, size_t, size_t, size_t);
	size_t MergeCountInversions(vector<T>&, vector<T>&, size_t, size_t, size_t);
public:
	void BubbleSort(vector<T>&);
	void QuickSort(vector<T>&, long, long);
	void SelectionSort(vector<T>&);
	void InsertionSort(vector<T>&);
	void HeapSort(vector<T>&);
	void CountingSort(vector<T>&);
	string StringCountingSort(vector<vector<string>>&);
	T CountingSort(vector<vector<T>>&);
	void TopDownMergeSort(vector<T>&, vector<T>&, size_t, size_t);
	void BottomUpMergeSort(vector<T>&, vector<T>&);
	void WiggleSort(vector<T>&);
	void SortNumbers(vector<T>&);
	size_t SortSwapCount(vector<T>&);
	bool CanFinishCourseTopologicalSort(size_t, vector<vector<T>>&, vector<T>&);
	size_t TopDownMergeSortCountConversions(vector<T>&, vector<T>&, size_t, size_t);
};