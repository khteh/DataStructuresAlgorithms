#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <map>
using namespace std;
template <typename T>
class DisJointSet
{
private:
	unordered_map<T, T> _sets;
	unordered_map<T, size_t> _rank;

public:
	DisJointSet(vector<T> &);
	void MakeSet(vector<T> &);
	T Find(T);
	size_t Rank(T);
	T Union(T, T);
	void Print(vector<T> const &, size_t linesize = numeric_limits<size_t>::max());
	void GetSets(vector<T> const &data, map<T, vector<T>> &);
};