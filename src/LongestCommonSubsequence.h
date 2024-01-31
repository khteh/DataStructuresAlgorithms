#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class LongestCommonSubsequence
{
public:
	size_t LCSLength(string &, string &);
	size_t LCSLength(vector<vector<size_t>> &, string &, string &);
	string LCSBackTrack(vector<vector<size_t>> &, string &, string &, size_t, size_t);
	size_t LCSLength(vector<T> &, vector<T> &);
	size_t LCSLength(vector<vector<size_t>> &, vector<T> &, vector<T> &);
	vector<T> LCSBackTrack(vector<vector<size_t>> &, vector<T> &, vector<T> &, size_t, size_t);
	void LCSPrintDiff(vector<vector<size_t>> &, string &, string &, long, long);
	void LCSPrintDiff(vector<vector<size_t>> &, vector<T> &, vector<T> &, long, long);
};