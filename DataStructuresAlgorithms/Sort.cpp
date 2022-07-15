#include "Sort.h"
template class Sort<int>;
template class Sort<size_t>;
template class Sort<long>;
template class Sort<string>;
template class Sort<float>;
template class Sort<double>;
template <typename T>
void Sort<T>::BubbleSort(vector<T> &data)
{
	T tmp = T();
	for (size_t lastIndex = data.size() - 1; lastIndex >= 1; lastIndex--)
	{
		for (size_t i = 0; i < lastIndex; i++)
		{
			if (data[i] > data[i + 1])
			{
				tmp = data[i];
				data[i] = data[i + 1];
				data[i + 1] = tmp;
			}
		}
	}
}
/* Quick Sort (http://en.wikipedia.org/wiki/Quicksort)
 * C=2, L=lg(N), Other: N
 * #nodes = (C^L - 1) / (C - 1) = 2^lg(N) - 1
 * TC: (2^lg(N) - 1) * N = N^2
 * Mathematics: 2^lg(N)
 * N: 8
 * ln(N) = 3 => 2^3 = 8
 * So, 2^lg(N) = N
 */
template <typename T>
void Sort<T>::QuickSort(vector<T> &data, long left, long right)
{
	size_t pivot;
	if (left >= 0 && right < (long)data.size() && left < right)
	{
		pivot = left + (right - left) / 2 + (right - left) % 2; // This overcomes integer overflow which happens if data.size() is large and naive approach of (lo + hi)/2 is used to index the middle element.
		// Worst case: N-1 calls. Each call processes the list from left to right-1 (N) => O(N^2)
		// Average case: lg(N) calls. Each level of call tree processes half the original list. Both calls processes N items => O(N*log(N)).
		pivot = Partition(data, left, right, pivot);
		QuickSort(data, left, pivot - 1);  // Either this or the call below is used in worst-case scenario
		QuickSort(data, pivot + 1, right); // Either this or the call above is used in worst-case scenario
	}
}
/* Worst case: returns original list (newPivot = left || newPivot = right)
 * Average case: Divides the original list to half. newPivot = 1/2.
 * newPivot = The final position of the pivot at the end of this partition operation.
 * Example:
 * [1,3,{0},2]: left:0, right: 3, pivot: 2
 * pivotValue: 0
 * newPivot = 0
 * [1,3,2,{0}]
 * i:0
 *		newPivot:0
 * i:1
 *		newPivot:0
 * i:2
 *		newPivot:0
 * => [0,3,2,1]
 * [0], [3,2,1] left:1, right: 3, pivot: 2
 * pivotValue: 2
 * newPivot = 1
 * [0,3,1,2]
 * i:1
 *		newPivot: 1
 * i:2
 *		[0,1,3,2]
 *		newPivot: 2
 * => [0,1,2,3]
 */
template <typename T>
size_t Sort<T>::Partition(vector<T> &data, size_t left, size_t right, size_t pivot)
{
	size_t newPivot = left; // This is used to find the final location for the pivot value
	T pivotValue = data[pivot];
	if (pivot != right)
		swap(data[pivot], data[right]);
	for (size_t i = left; i < right; i++)
		if (data[i] < pivotValue)
		{
			if (i != newPivot)
				swap(data[i], data[newPivot]);
			newPivot++;
		}
	if (newPivot != right)
		swap(data[newPivot], data[right]);
	return newPivot;
}
// Find the smallest element using a linear scan and move it to the front.
// Then, find the second smallest and move it, again doing a linear scan.
// Continue doing this until all the elements are in place. O(n^2).
template <typename T>
void Sort<T>::SelectionSort(vector<T> &data)
{
	size_t min = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		min = i;
		for (size_t j = i + 1; j < data.size(); j++)
		{ // Find the min from lower bound to end
			if (data[j] <= data[min])
				min = j;
		}
		if (min != i)
			swap(data[min], data[i]);
	}
}
template <typename T>
void Sort<T>::InsertionSort(vector<T> &data)
{
	for (size_t i = 1; i < data.size(); i++)
		for (long j = i; j > 0 && data[j] < data[j - 1]; j--)
			swap(data[j], data[j - 1]);
}
// https://en.wikipedia.org/wiki/Heapsort
template <typename T>
void Sort<T>::HeapSort(vector<T> &data)
{
	Heap<T> heap(data, HeapType::MaxHeap);
	assert(heap.Count() == data.size());
	for (long end = data.size() - 1; end >= 0; end--)
	{
		T item = heap.pop()->Item();
		swap(data[end], item);
	}
}
// https://en.wikipedia.org/wiki/Counting_sort
// each of which has a non-negative integer key whose maximum value is at most k
template <typename T>
void Sort<T>::CountingSort(vector<T> &data) requires arithmetic_type<T>
{
	vector<T> input(data);
	T min = numeric_limits<T>::max(), max = 0;
	for (typename vector<T>::iterator it = input.begin(); it != input.end(); it++)
	{
		if (*it < min)
			min = *it;
		if (*it > max)
			max = *it;
	}
	// Do NOT use map / multimap to keep the counts. map / multimap auto-sort on keys. This defeats the purpose of CountingSort
	vector<T> counts(max + 1, 0);
	for (typename vector<T>::iterator it = input.begin(); it != input.end(); it++)
		counts[*it]++;
	for (long i = min > 0 ? min : 1; i <= max; i++)
		counts[i] += counts[i - 1];
	// Use reverse_iterator for a stable sort
	for (typename vector<T>::reverse_iterator it = input.rbegin(); it != input.rend(); it++)
	{
		data[counts[*it] - 1] = *it;
		counts[*it]--;
	}
}
template <typename T>
string Sort<T>::StringCountingSort(vector<vector<string>> &data)
{
	vector<string> result;
	long min = numeric_limits<size_t>::max(), max = 0;
	for (vector<vector<string>>::iterator it = data.begin(); it != data.end(); it++)
	{
		long key;
		istringstream((*it)[0]) >> key;
		if (key < min)
			min = key;
		if (key > max)
			max = key;
	}
	// Do NOT use map / multimap to keep the counts. map / multimap auto-sort on keys. This defeats the purpose of CountingSort
	vector<size_t> counts(max + 1, 0);
	for (vector<vector<string>>::iterator it = data.begin(); it != data.end(); it++)
	{
		size_t key;
		istringstream((*it)[0]) >> key;
		counts[key]++;
	}
	for (long i = min > 0 ? min : 1; i <= max; i++)
		counts[i] += counts[i - 1];
	result.resize(counts.back());
	// Use reverse_iterator for a stable sort
	for (vector<vector<string>>::reverse_iterator it = data.rbegin(); it != data.rend(); it++)
	{
		size_t key;
		istringstream((*it)[0]) >> key;
		result[counts[key] - 1] = (*it)[1];
		counts[key]--;
	}
	ostringstream oss;
	for (size_t i = 0; i < result.size(); i++)
	{
		if (!result[i].empty())
		{
			oss << result[i];
			if (i < result.size() - 1)
				oss << " ";
		}
	}
	return oss.str();
}
template <typename T>
void Sort<T>::Merge(vector<T> &source, vector<T> &dest, size_t start, size_t middle, size_t end)
{
	size_t left = start;
	size_t right = middle;
	// While there are elements in the left or right runs...
	for (size_t i = start; i < end; i++)
		/* If left run head exists (left < middle)
		 * AND value is <= existing right run head.
		 * OR  Right run is empty (right >= end)
		 * Example:
		 * width: 1
		 * source: [0,2(R),1] dest: [] [start, middle, end] = [0,1,2)
		 * left:0, right: 1, middle: 1, end: 2
		 * dest[0] = 0, Take left. left == middle == 1
		 * dest[1] = 2 (left == middle), Take right.
		 * source: [0,2,1] dest: [0,2] [start, middle, end] = [2,3,3)
		 * left:2, right: 3, middle: 3, end: 3
		 * dest[2] = 1 (right == end), Take left. left == middle == 3
		 *
		 * width: 2
		 * source: [0,2,1(R)] dest: [0,2,1] [start, middle, end] = [0,2,3)
		 * left:0, right: 2, middle: 2, end: 3
		 * dest[0] = 0, Take left. left = 1
		 * dest[1] = 1, Take right (1 < 2). right = 3 == end [Inversion count = right - i = 2 - 1 = 1]
		 * dest[2] = 2, Take left (right == end). left = 2
		 */
		dest[i] = (left < middle && (right >= end || source[left] <= source[right])) ? source[left++] : source[right++];
}
/* http://en.wikipedia.org/wiki/Merge_sort
 * top-down merge sort algorithm that recursively splits the list (called runs in this example) into sublists
 * until sublist size is 1, then merges those sublists to produce a sorted list
 * The copy back step is avoided with alternating the direction of the merge with each level of recursion (except for an initial one time copy)
 * start: inclusive; end: exclusive
 * Example:
 * [2,1]:  A,B [0,2)
 * [2] [1] B,A [0,1), [1,2) <- Never gets into the if (end - start > 1) condition.
 * [1,2]   A,B <= Bottom of recursion. Merge into B
 * Time complexity: 1 level (log(n)), 1 comparison. 2 items. => O(n*log(n))
 *
 * [2,1,4,3]:      A,B [0:4)
 * [2,1] [4,3]	   B,A [0:2), [2:4)
 * [2] [1] [4] [3] A,B [0:1), [1,2), [2,3), [3,4) <- Never gets into the if (end - start > 1) condition.
 * [1,2] [3,4]	   B,A <= Bottom of recurssion. Merge into A. 2 comparisons. 4 items.
 * [1,2,3,4]	   A,B <= Next higher level, merge into B. 1 comparison. 4 items.
 * Time complexity: 2 levels (log(n)), 3 comparisons, 4 items. => O(n*log(n))
 * C: 2, L: lg(N), Others: N
 * #nodes = (C^L - 1) / (C - 1) = 2^lg(N) = N
 * TC = N*lg((N)
 */
template <typename T>
void Sort<T>::TopDownMergeSort(vector<T> &A /* A */, vector<T> &B /* B */, size_t start, size_t end)
{
	if (end - start > 1)
	{ // If run size == 1, consider it sorted
		// recursively split runs into two halves until run size == 1,
		// then merge them and return back up the call chain
		size_t middle = start + (end - start) / 2 + (end - start) % 2;
		TopDownMergeSort(B, A, start, middle);
		TopDownMergeSort(B, A, middle, end);
		Merge(A, B, start, middle, end);
	}
}
/* bottom-up merge sort algorithm which treats the list consisting of n sublists (called runs in this example)
 * of size 1, and iteratively merges sub-lists back and forth between two buffers
 * List A[] has the items to sort; list B[] is a work buffer
 * Example:
 * [2,1] => [1,2]
 *
 * [0,2,1]
 * [0],[2],[1]
 * => [0,2], [1] : width = 1
 * => [0,1,2] : width = 2. 1 Inversion
 *		[0,2], [1]: width = 1 => [0,2,1]
 *		[0,1,2]: width = 2.
 *			[0,1,2] Inversion between index 1 & 2
 * [0,3,1,2]
 * [0], [3], [1], [2]
 * => [0,3], [1,2] : width = 1
 * => [0,1,2,3] : width = 2. 2 Inversions: {1,2}, {2,3}
 *		[0,3], [1,2]: width = 1 => [0,3,1,2]
 *		[0,1,2,3]: width = 2.
 *			[0,1,3,2] Inversion between index 1 & 2
 *			[0,1,2,3] Inversion between index 2 & 3
 * O(lg(N) * N) = O(N * lg(N))
 */
template <typename T>
void Sort<T>::BottomUpMergeSort(vector<T> &A, vector<T> &B)
{
	size_t n = A.size();
	// Each 1-element run in data is already "sorted".
	// Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted.
	for (size_t width = 1; width < A.size(); width *= 2)
	{ // O(lg(N))
		// Array A is full of runs of length width.
		// width: 1, i(+2): 0, 2, 4, 6, 8, 10
		// width: 2, i(+4): 0, 4, 8, 12,16,20
		for (size_t i = 0; i < A.size(); i += 2 * width)			  // Range of each Merge call. Total is O(N).
																	  /* Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
																	   * width: 1
																	   *   i:0 Merge two runs: A[0:0] and A[1:1] to B[] [start, middle, end] : [0,1,2)
																	   *   i:2 Merge two runs: A[2:2] and A[3:3] to B[] [start, middle, end] : [2,3,4)
																	   *   i:4 Merge two runs: A[4:4] and A[5:5] to B[] [start, middle, end] : [4,5,6)
																	   *  width: 2
																	   *   i:0 Merge two runs: A[0:1] and A[2:3] to B[] [start, middle, end] : [0,2,4)
																	   *   i:2 Merge two runs: A[2:3] and A[4:5] to B[] [start, middle, end] : [2,4,6)
																	   *   i:4 Merge two runs: A[4:5] and A[6:7] to B[] [start, middle, end] : [4,6,8)
																	   *  or copy A[i:n-1] to B[] ( if (i+width >= n) )
																	   */
			Merge(A, B, i, min(i + width, n), min(i + 2 * width, n)); // O(N)
		// Now work array B is full of runs of length 2*width.
		// Copy array B to array A for next iteration.
		// A more efficient implementation would swap the roles of A and B.
		A = B;
		// Now array A is full of runs of length 2*width.
	}
}
/* https://leetcode.com/problems/wiggle-sort-ii/
 * 100%
 * 1 5 1 1 6 4
 * 1 1 1 [4] 5 6
 *     i  M    j
 * 1 6 1 5 1 4
 *
 * 1 3 2 2 3 1
 * 1 1 2 [2] 3 3
 *     i  M    j
 * 2 3 1 3 1 2
 *
 * 5 3 1 2 6 7 8 5 5
 * 1 2 3 5 5 [5] 6 7 8
 * 		  i  M      j
 * 5 8 5 7 3 6 2 5 1
 */
template <typename T>
void Sort<T>::WiggleSort(vector<T> &data)
{
	ranges::sort(data);
	vector<T> result;
	size_t middle = data.size() / 2 + data.size() % 2;
	int i = middle - 1, j = data.size() - 1;
	for (; i >= 0 && j >= (int)middle; i--, j--)
	{
		result.push_back(data[i]);
		result.push_back(data[j]);
	}
	if (i >= 0)
		result.push_back(data[i]);
	else if (j > (int)middle)
		result.push_back(data[j]);
	data = result;
}
// https://www.hackerrank.com/challenges/ctci-merge-sort/problem
// 100%
template <typename T>
size_t Sort<T>::TopDownMergeSortCountConversions(vector<T> &B, vector<T> &A, size_t start, size_t end)
{
	size_t inversions = 0;
	if (end - start > 1)
	{ // If run size == 1, consider it sorted
		// recursively split runs into two halves until run size == 1,
		// then merge them and return back up the call chain
		size_t middle = start + (end - start) / 2 + (end - start) % 2;
		inversions += TopDownMergeSortCountConversions(A, B, start, middle);
		inversions += TopDownMergeSortCountConversions(A, B, middle, end);
		inversions += MergeCountInversions(B, A, start, middle, end);
	}
	return inversions;
}
template <typename T>
size_t Sort<T>::MergeCountInversions(vector<T> &source, vector<T> &dest, size_t start, size_t middle, size_t end)
{
	size_t inversions = 0;
	size_t left = start;
	size_t right = middle;
	// While there are elements in the left or right runs...
	for (size_t i = start; i < end; i++)
	{
		// If left run head exists and is <= existing right run head.
		// dest[i] = (left < middle && (right >= end || source[left] <= source[right])) ? source[left++] : source[right++];
		if (left < middle && (right >= end || source[left] <= source[right]))
			dest[i] = source[left++];
		else
		{
			inversions += right - i;
			dest[i] = source[right++];
		}
	}
	return inversions;
} /*
	Count the minimum number of swaps needed to sort the data in either ascending or descending order
 data:         2 5 3 1
 sorted index: 1 3 2 0 <= 3 links (0:1 - 1:3 - 3:0) 2 swaps

 #index link #swaps
	 2		1
	 3		2
	 4		3
	 5		4
 Not optimized for big data input
 */
template <typename T>
size_t Sort<T>::SortSwapCount(vector<T> &data)
{
	size_t result = 0, resultDescend = 0;
	set<size_t> visited, visitedDescend;
	set<T> sorted(data.begin(), data.end());
	set<T, greater<T>> sortedDescend(data.begin(), data.end());
	for (size_t i = 0; i < data.size(); i++)
	{
		if (distance(sorted.begin(), sorted.find(data[i])) != i)
		{
			long offset = i;
			long cnt = 0;
			do
			{
				offset = distance(sorted.begin(), sorted.find(data[offset]));
				if (visited.find(offset) == visited.end())
				{
					cnt++;
					visited.insert(offset);
				}
			} while (offset != i);
			result += cnt > 0 ? cnt - 1 : 0;
		}
		if (distance(sortedDescend.begin(), sortedDescend.find(data[i])) != i)
		{
			long offset = i;
			size_t cnt = 0;
			do
			{
				offset = distance(sortedDescend.begin(), sortedDescend.find(data[offset]));
				if (visitedDescend.find(offset) == visitedDescend.end())
				{
					cnt++;
					visitedDescend.insert(offset);
				}
			} while (offset != i);
			resultDescend += cnt > 0 ? cnt - 1 : 0;
		}
	}
	return min(result, resultDescend);
}
/* https://leetcode.com/problems/course-schedule/
 * https://en.wikipedia.org/wiki/Topological_sorting
 * Use Kahn's algorithm
 * 100%
 */
template <typename T>
bool Sort<T>::CanFinishCourseTopologicalSort(size_t numCourses, vector<vector<T>> &courses, vector<T> &sequence) // First element depends on second element in each row
{
	map<T, size_t> dependencies;
	map<T, vector<T>> edges; // Key: Independent; Value: Dependent
	size_t edgeCount = courses.size();
	set<T> uniqueCourses;
	for (size_t i = 0; i < edgeCount; i++)
	{
		uniqueCourses.emplace(courses[i][0]);
		uniqueCourses.emplace(courses[i][1]);
		edges[courses[i][1]].push_back(courses[i][0]);
		dependencies[courses[i][0]]++;
	}
	assert(uniqueCourses.size() == numCourses);
	queue<T> independentNodes; // Set of all nodes with no incoming edge
	// for (size_t i = 0; i < numCourses; i++)
	for (typename set<T>::iterator it = uniqueCourses.begin(); it != uniqueCourses.end(); it++)
		if (dependencies.find(*it) == dependencies.end())
			independentNodes.push(*it);
	for (; !independentNodes.empty();)
	{
		T i = independentNodes.front();
		independentNodes.pop();
		sequence.push_back(i);
		if (edges.find(i) != edges.end())
			for (typename vector<T>::iterator it = edges[i].begin(); it != edges[i].end(); it++)
			{
				edgeCount--; // remove edge e from the graph
				if (dependencies.find(*it) == dependencies.end() || !--dependencies[*it])
					independentNodes.push(*it);
			}
	}
	return !edgeCount; // A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a directed acyclic graph (DAG)
}
// Sort numbers into consecutive positive/negative numbers
// http://www.careercup.com/question?id=5183920823861248
template <typename T>
void Sort<T>::SortNumbers(vector<T> &data) requires arithmetic_type<T>
{
	size_t j;
	T tmp = T();
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i] < 0 && data[i + 1] < 0)
		{ // Look for positive number
			for (j = i + 1; j < data.size() && data[j] < 0; j++)
				;
			if (j == data.size())
				break;
			// Shift i+1 to j-1
			tmp = data[j];
			for (size_t k = j; k > i; k--)
				data[k] = data[k - 1];
			data[i + 1] = tmp;
		}
		else if (data[i] > 0 && data[i + 1] > 0)
		{ // Look for positive number
			for (j = i + 1; j < data.size() && data[j] > 0; j++)
				;
			if (j == data.size())
				break;
			// Shift i+1 to j-1
			tmp = data[j];
			for (size_t k = j; k > i; k--)
				data[k] = data[k - 1];
			data[i + 1] = tmp;
		}
	}
}
template <typename T>
bool Sort<T>::LexicographicSort(string s1, string s2)
{
	size_t i, j;
	map<string, size_t> order = {{"a", 0}, {"b", 1}, {"c", 2}, {"ch", 3}, {"cz", 4}, {"d", 5}, {"e", 6}, {"f", 7}, {"g", 8}, {"h", 9}, {"i", 10}, {"j", 11}, {"k", 12}, {"l", 13}, {"m", 14}, {"n", 15}, {"o", 16}, {"p", 17}, {"q", 18}, {"r", 18}, {"s", 19}, {"t", 20}, {"u", 21}, {"v", 22}, {"w", 23}, {"x", 24}, {"y", 24}, {"z", 25}};
	map<string, size_t>::iterator s1It = order.end(), s2It = order.end();
	ranges::transform(s1, s1.begin(), ::tolower);
	ranges::transform(s2, s2.begin(), ::tolower);
	for (i = 0, j = 0; i < s1.size() && j < s2.size();)
	{
		if (i < s1.size() - 1)
		{
			s1It = order.find(s1.substr(i, 2));
			if (s1It != order.end())
				i += 2;
		}
		if (s1It == order.end())
			s1It = order.find(s1.substr(i++, 1));
		if (j < s2.size() - 1)
		{
			s2It = order.find(s2.substr(j, 2));
			if (s2It != order.end())
				j += 2;
		}
		if (s2It == order.end())
			s2It = order.find(s2.substr(j++, 1));
		if (s1It->second == s2It->second)
		{
			s1It = order.end();
			s2It = order.end();
		}
		else
			return s1It->second < s2It->second; // substring comparison
	}
	return (s1.size() - i) < (s2.size() - j); // String length comparison.
}