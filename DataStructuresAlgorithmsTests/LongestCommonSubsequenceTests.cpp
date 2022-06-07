#include "pch.h"
using namespace std;
TEST(LongestCommonSubsequenceTests, LongestCommonSubsequenceTest)
{
	LongestCommonSubsequence<char> lcs;
	LongestCommonSubsequence<size_t> lcs1;
	vector<char> chars1, chars2;
	vector<size_t> num1, num2, result;
	string s1, s2;
	s1 = "HARRY";
	s2 = "SALLY";
	ASSERT_EQ(2, lcs.LCSLength(s1, s2));
	s1 = "HARRY";
	s2 = "SALLY";
	chars1.insert(chars1.end(), s1.begin(), s1.end());
	chars2.insert(chars2.end(), s2.begin(), s2.end());
	ASSERT_EQ(2, lcs.LCSLength(chars1, chars2));
	s1 = "SHINCHAN";
	s2 = "NOHARAAA";
	ASSERT_EQ(3, lcs.LCSLength(s1, s2));
	s1 = "ABCDEF";
	s2 = "FBDAMN";
	ASSERT_EQ(2, lcs.LCSLength(s1, s2));
	s1 = "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS";
	s2 = "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC";
	ASSERT_EQ(15, lcs.LCSLength(s1, s2));
	s1 = "HARRY";
	s2 = "SALLY";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	ASSERT_EQ(2, lcs.LCSLength(table, s1, s2));
	ASSERT_EQ("AY", lcs.LCSBackTrack(table, s1, s2, s1.size() - 1, s2.size() - 1));
	lcs.LCSPrintDiff(table, s1, s2, s1.size() - 1, s2.size() - 1);
	cout << endl;
	s1 = "SHINCHAN";
	s2 = "NOHARAAA";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table1(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	ASSERT_EQ(3, lcs.LCSLength(table1, s1, s2));
	ASSERT_EQ("NHA", lcs.LCSBackTrack(table1, s1, s2, s1.size() - 1, s2.size() - 1));
	s1 = "ABCDEF";
	s2 = "FBDAMN";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table2(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	ASSERT_EQ(2, lcs.LCSLength(table2, s1, s2));
	ASSERT_EQ("BD", lcs.LCSBackTrack(table2, s1, s2, s1.size() - 1, s2.size() - 1));
	s1 = "aa";
	s2 = "baaa";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table3(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	ASSERT_EQ(2, lcs.LCSLength(table3, s1, s2));
	ASSERT_EQ("aa", lcs.LCSBackTrack(table3, s1, s2, s1.size() - 1, s2.size() - 1));
	lcs.LCSPrintDiff(table3, s1, s2, s1.size() - 1, s2.size() - 1);
	cout << endl;
	s1 = "WEWOUCUIDGCGTRMEZEPXZFEJWISRSBBSYXAYDFEJJDLEBVHHKS";
	s2 = "FDAGCXGKCTKWNECHMRXZWMLRYUCOCZHJRRJBOAJOQJZZVUYXIC";
	s1.insert(0, 1, 0);
	s2.insert(0, 1, 0);
	vector<vector<size_t>> table4(s1.size(), vector<size_t>(s2.size())); // Defaults to zero initial value
	ASSERT_EQ(15, lcs.LCSLength(table4, s1, s2));
	ASSERT_EQ("DGCGTRMZJRBAJJV", lcs.LCSBackTrack(table4, s1, s2, s1.size() - 1, s2.size() - 1));
	chars1.clear();
	chars2.clear();
	chars1.insert(chars1.end(), s1.begin(), s1.end());
	chars2.insert(chars2.end(), s2.begin(), s2.end());
	vector<vector<size_t>> table5(chars1.size(), vector<size_t>(chars2.size())); // Defaults to zero initial value
	ASSERT_EQ(15, lcs.LCSLength(table5, chars1, chars2));
	chars1 = lcs.LCSBackTrack(table5, chars1, chars2, chars1.size() - 1, chars2.size() - 1);
	s1.clear();
	s1.insert(s1.end(), chars1.begin(), chars1.end());
	ASSERT_EQ(s1, "DGCGTRMZJRBAJJV");
	num1 = {1, 2, 3, 4, 1};
	num2 = {3, 4, 1, 2, 1, 3};
	ASSERT_EQ(3, lcs1.LCSLength(num1, num2)); // "1 2 3", "1 2 1", "3 4 1" are all correct answers
	num1 = {1, 2, 3, 4, 1};
	num2 = {3, 4, 1, 2, 1, 3};
	num1.insert(num1.begin(), 0);
	num2.insert(num2.begin(), 0);
	vector<vector<size_t>> table6(num1.size(), vector<size_t>(num2.size())); // Defaults to zero initial value
	ASSERT_EQ(3, lcs1.LCSLength(table6, num1, num2));						 // "1 2 3", "1 2 1", "3 4 1" are all correct answers
	result = lcs1.LCSBackTrack(table6, num1, num2, num1.size() - 1, num2.size() - 1);
	ASSERT_EQ(3, result.size());
	ASSERT_EQ(1, result[0]);
	ASSERT_EQ(2, result[1]);
	ASSERT_EQ(3, result[2]);
	lcs1.LCSPrintDiff(table6, num1, num2, num1.size() - 1, num2.size() - 1);
	cout << endl;
}