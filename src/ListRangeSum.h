#pragma once
template <typename T>
class ListRangeSum
{
private:
	vector<T> _data;

public:
	ListRangeSum(vector<T> &);
	T Sum(size_t, size_t);
	void Update(size_t, T);
};