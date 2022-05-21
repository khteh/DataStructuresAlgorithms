#include "stdafx.h"
#include "LongestCommonSubsequence.h"
template class LongestCommonSubsequence<size_t>;
template class LongestCommonSubsequence<char>;

/* https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
* https://www.hackerrank.com/challenges/common-child/problem
* 100%
* 		j:0	j:1	j:2	j:3	j:4	j:5
		\0'	H	A	R	R	Y
i:0	\0'	0	0	0	0	0	0
i:1	S	0	0	0	0	0	0
i:2	A	0	0	1	1	1	1
i:3	L	0	0	1	1	1	1
i:4	L	0	0	1	1	1	1
i:5	Y	0	0	1	1	1	2
*/
template<typename T>
size_t LongestCommonSubsequence<T>::LCSLength(string &s1, string &s2)
{
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	for (size_t i = 1; i < s1.size(); i++)
		for (size_t j = 1; j < s2.size(); j++)
			table[i][j] = s1[i] == s2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[s1.size() - 1][s2.size() - 1];
}
template<typename T>
size_t LongestCommonSubsequence<T>::LCSLength(vector<vector<size_t>>& table, string& s1, string& s2)
{
	for (size_t i = 1; i < s1.size(); i++)
		for (size_t j = 1; j < s2.size(); j++)
			table[i][j] = s1[i] == s2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[s1.size() - 1][s2.size() - 1];
}
template <typename T>
size_t LongestCommonSubsequence<T>::LCSLength(vector<T>& n1, vector<T>& n2)
{
	n1.insert(n1.begin(), 0);
	n2.insert(n2.begin(), 0);
	vector<vector<size_t>> table(n1.size(), vector<size_t>(n2.size())); // Defaults to zero initial value
	for (size_t i = 1; i < n1.size(); i++)
		for (size_t j = 1; j < n2.size(); j++)
			table[i][j] = n1[i] == n2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[n1.size() - 1][n2.size() - 1];
}
template <typename T>
size_t LongestCommonSubsequence<T>::LCSLength(vector<vector<size_t>>& table, vector<T>& n1, vector<T>& n2)
{
	for (size_t i = 1; i < n1.size(); i++)
		for (size_t j = 1; j < n2.size(); j++)
			table[i][j] = n1[i] == n2[j] ? table[i - 1][j - 1] + 1 : max(table[i - 1][j], table[i][j - 1]);
	return table[n1.size() - 1][n2.size() - 1];
}
template <typename T>
string LongestCommonSubsequence<T>::LCSBackTrack(vector<vector<size_t>>& table, string& s1, string& s2, size_t i, size_t j)
{
	if (!i || !j)
		return "";
	if (s1[i] == s2[j])
		return LCSBackTrack(table, s1, s2, i - 1, j - 1) + s1[i];
	return table[i][j - 1] > table[i - 1][j] ? LCSBackTrack(table, s1, s2, i, j - 1) : LCSBackTrack(table, s1, s2, i - 1, j);
}
template <typename T>
vector<T> LongestCommonSubsequence<T>::LCSBackTrack(vector<vector<size_t>>& table, vector<T>& n1, vector<T>& n2, size_t i, size_t j)
{
	vector<T> result;
	if (!i || !j)
		return result;
	if (n1[i] == n2[j])
	{
		result = LCSBackTrack(table, n1, n2, i - 1, j - 1);
		result.push_back(n1[i]);
		return result;
	}
	return table[i][j - 1] > table[i - 1][j] ? LCSBackTrack(table, n1, n2, i, j - 1) : LCSBackTrack(table, n1, n2, i - 1, j);
}
template <typename T>
void LongestCommonSubsequence<T>::LCSPrintDiff(vector<vector<size_t>>& table, string& s1, string& s2, long i, long j)
{
	if (i > 0 && j > 0 && s1[i] == s2[j])
	{
		LCSPrintDiff(table, s1, s2, i - 1, j - 1);
		cout << s1[i];
	}
	else if (j > 0 && (!i || (table[i][j - 1] >= table[i - 1][j])))
	{
		LCSPrintDiff(table, s1, s2, i, j - 1);
		cout << "+" << s2[j];
	}
	else if (i > 0 && (!j || (table[i][j - 1] < table[i - 1][j])))
	{
		LCSPrintDiff(table, s1, s2, i - 1, j);
		cout << "-" << s1[i];
	}
}
template <typename T>
void LongestCommonSubsequence<T>::LCSPrintDiff(vector<vector<size_t>>& table, vector<T>& n1, vector<T>& n2, long i, long j)
{
	if (i > 0 && j > 0 && n1[i] == n2[j])
	{
		LCSPrintDiff(table, n1, n2, i - 1, j - 1);
		cout << n1[i];
	}
	else if (j > 0 && (!i || (table[i][j - 1] >= table[i - 1][j])))
	{
		LCSPrintDiff(table, n1, n2, i, j - 1);
		cout << "+" << n2[j];
	}
	else if (i > 0 && (!j || (table[i][j - 1] < table[i - 1][j])))
	{
		LCSPrintDiff(table, n1, n2, i - 1, j);
		cout << "-" << n1[i];
	}
}
