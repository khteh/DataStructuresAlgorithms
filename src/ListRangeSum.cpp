#include "stdafx.h"
#include "ListRangeSum.h"
template class ListRangeSum<long>;
/* https://leetcode.com/problems/range-sum-query-mutable/
* 100%
* List range sum using bottom-up dynamic programming
*
i:    0	 1	2
data: 1	 3	5
_data:1	 4	9

Update(1, 2)		diff = [i] - [i-1] - val = 4 - 1 - 2 = 1
i:    0	 1	2
data: 1	 2	5 (new data)
_data:1	 3	8 (target _data)

Update(1, 5)		diff = [i] - [i-1] - val = 4 - 1 - 5 = -2
i:    0	 1	2
data: 1	 5	5  (new data)
_data:1	 6	11 (target _data)
*/
template <typename T>
ListRangeSum<T>::ListRangeSum(vector<T> &data)
{
	for (size_t i = 0; i < data.size(); i++)
		_data.push_back(i ? data[i] + _data[i - 1] : data[i]);
}
template <typename T>
void ListRangeSum<T>::Update(size_t i, T val)
{
	if (i >= 0 && i < _data.size())
	{
		T diff = i ? _data[i] - _data[i - 1] - val : _data[i] - val;
		for (; i < _data.size(); i++)
			_data[i] -= diff;
	}
}
template <typename T>
T ListRangeSum<T>::Sum(size_t i, size_t j)
{
	if (i >= 0 && i < _data.size() && j >= 0 && j < _data.size() && i <= j)
		return i ? _data[j] - _data[i - 1] : _data[j];
	return 0;
}