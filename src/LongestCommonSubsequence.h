#pragma once
template <typename T>
class LongestCommonSubsequence
{
private:
	size_t LCSLength(vector<vector<size_t>> &, string &, string &);
	size_t LCSLength(vector<vector<size_t>> &, vector<T> &, vector<T> &);
	string LCSBackTrack(vector<vector<size_t>> &, string &, string &, size_t, size_t);
	vector<T> LCSBackTrack(vector<vector<size_t>> &, vector<T> &, vector<T> &, size_t, size_t);

public:
	size_t LCSLength(string &, string &);
	size_t LCSLength(vector<T> &, vector<T> &);
	tuple<size_t, string> LCSLengthWithBackTrack(string &, string &);
	tuple<size_t, vector<T>> LCSLengthWithBackTrack(vector<T> &, vector<T> &);
	void LCSPrintDiff(vector<vector<size_t>> &, string &, string &, long, long);
	void LCSPrintDiff(vector<vector<size_t>> &, vector<T> &, vector<T> &, long, long);
};