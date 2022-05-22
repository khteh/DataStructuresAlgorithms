#include "stdafx.h"
#include "ListRangeSum.h"
template class ListRangeSum<long>;
/* https://leetcode.com/problems/range-sum-query-mutable/
* 100%
* List range sum using bottom-up dynamic programming
* 
0	1	2
1	3	5
		
0	1	2
1	4	9
		
Update(1,2)		diff = [i] - [i-1] - val
0	1	2
1	2	5
		
0	1	2
1	3	8
*/
template<typename T>
ListRangeSum<T>::ListRangeSum(vector<T>& data)
{
	for (size_t i = 0; i < data.size(); i++) {
		_data.push_back(data[i]);
		if (i)
			_data[i] += _data[i - 1];
	}
}
template<typename T>
void ListRangeSum<T>::Update(size_t i, T val)
{
	if (i >= 0 && i < _data.size()) {
		T diff = i ? _data[i] - _data[i - 1] - val : _data[i] - val;
		for (; i < _data.size(); i++)
			_data[i] -= diff;
	}
}
template<typename T>
T ListRangeSum<T>::Sum(size_t i, size_t j)
{
	if (i >= 0 && i < _data.size() && j >= 0 && j < _data.size() && i <= j) {
		T sum = _data[j];
		if (i)
			sum -= _data[i - 1];
		return sum;
	}
	return 0;
}