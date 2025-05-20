#pragma once
#include "Heap.h"
namespace ranges = std::ranges;
template <typename T>
class Sort
{
private:
	void Merge(vector<T> &, vector<T> &, size_t, size_t, size_t);
	size_t Partition(vector<T> &, size_t, size_t, size_t);
	size_t MergeCountInversions(vector<T> &, vector<T> &, size_t, size_t, size_t);

public:
	void BubbleSort(vector<T> &);
	void QuickSort(vector<T> &, long, long);
	void SelectionSort(vector<T> &);
	void InsertionSort(vector<T> &);
	void HeapSort(vector<T> &);
	void CountingSort(vector<T> &)
		requires unsigned_integral<T>;
	string StringCountingSort(vector<vector<string>> &);
	void TopDownMergeSort(vector<T> &, vector<T> &, size_t, size_t);
	void BottomUpMergeSort(vector<T> &, vector<T> &);
	void WiggleSort(vector<T> &);
	void AlternateSignSortNumbers(vector<T> &)
		requires arithmetic_type<T>;
	void AlternateSignSortNumbers1(vector<T> &)
		requires arithmetic_type<T>;
	size_t SortSwapCount(vector<T> &);
	void DutchPartitioning(vector<T> &, T);
	bool CanFinishCourseTopologicalSort(size_t, vector<vector<T>> &, vector<T> &);
	size_t TopDownMergeSortCountConversions(vector<T> &, vector<T> &, size_t, size_t);
	static bool LexicographicSort(string, string);
	size_t InsertionSortShifts(vector<T> &);
};