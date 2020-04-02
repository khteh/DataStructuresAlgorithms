#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;

template<class T>
class DisJointSet
{
private:
	unordered_map<T, T> _parent;
	unordered_map<T, size_t> _rank;
public:
	DisJointSet(vector<T>&);
	void MakeSet(vector<T>&);
	T Find(T);
	size_t Rank(T);
	T Union(T, T);
	void Print(vector<T> const&, size_t linesize = numeric_limits<size_t>::max());
};