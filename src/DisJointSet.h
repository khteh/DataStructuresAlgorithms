#pragma once
using namespace std;
template <typename T>
class DisJointSet
{
private:
	unordered_map<T, T> _sets;
	unordered_map<T, size_t> _rank;

public:
	DisJointSet(vector<T> const &);
	void MakeSet(vector<T> const &);
	T Find(T);
	size_t Rank(T);
	T Union(T, T);
	void Print(vector<T> const &, size_t linesize = 0);
	void GetSets(vector<T> const &data, map<T, vector<T>> &);
};