#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class LongestCommonSubsequence
{
public:
	static size_t LCSLength(string&, string&);
	static size_t LCSLength(vector<vector<size_t>>&, string&, string&);
	static string LCSBackTrack(vector<vector<size_t>>&, string&, string&, size_t, size_t);
	static size_t LCSLength(vector<T>&, vector<T>&);
	static size_t LCSLength(vector<vector<size_t>>&, vector<T>&, vector<T>&);
	static vector<T> LCSBackTrack(vector<vector<size_t>>&, vector<T>&, vector<T>&, size_t, size_t);
	static void LCSPrintDiff(vector<vector<size_t>>&, string&, string&, long, long);
	static void LCSPrintDiff(vector<vector<size_t>>&, vector<T>&, vector<T>&, long, long);
};