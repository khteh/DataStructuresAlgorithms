#include "pch.h"
using namespace std;
TEST(SuffixTreeTests, SuffixTreeTest)
{
	SuffixTree sTree("Mississippi");
	vector<size_t> indexes;
	vector<string> subStrings{"Mississippi", "M", "m", "i", "s", "p", "is", "si", "sip", "hi", "sis", "pi", "ppi", "ssi", "issi"};
	size_t count = sTree.Count();
	ASSERT_EQ(53, count);
	cout << "Suffix tree of \"Mississippi\" has " << count << " nodes" << endl;
	for (vector<string>::iterator it = subStrings.begin(); it != subStrings.end(); it++)
	{
		cout << "Suffix index of substring " << *it << ": ";
		indexes = sTree.GetIndexes(*it);
		if (!indexes.empty())
			ranges::copy(indexes, ostream_iterator<size_t>(cout, " "));
		else
			cout << quoted(*it) << " not found!";
		cout << endl;
	}
	vector<size_t> indices1 = sTree.GetIndexes("is");
	ASSERT_EQ(2, indices1.size()); // ississippi, issippi
	ASSERT_EQ(1, indices1[0]);
	ASSERT_EQ(4, indices1[1]);
	indices1 = sTree.GetIndexes("si");
	ASSERT_EQ(2, indices1.size()); // sissippi, sippi
	ASSERT_EQ(3, indices1[0]);
	ASSERT_EQ(6, indices1[1]);
	indices1 = sTree.GetIndexes("ssi");
	ASSERT_EQ(2, indices1.size()); // ssissippi, ssippi
	ASSERT_EQ(2, indices1[0]);
	ASSERT_EQ(5, indices1[1]);
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("issi", subStrings[0]);
	sTree.InsertString("sister");
	indices1 = sTree.GetIndexes("sis");
	ASSERT_EQ(2, indices1.size());
	ASSERT_EQ(3, indices1[0]);
	ASSERT_EQ(string("Mississippi").size(), indices1[1]);
	indices1 = sTree.GetIndexes("sister");
	ASSERT_EQ(1, indices1.size());
	ASSERT_EQ(string("Mississippi").size(), indices1[0]);
	sTree.Clear();
	ASSERT_FALSE(sTree.Count());
	sTree.InsertString("Amazon");
	sTree.InsertString("Neha Aman");
	sTree.InsertString("+6591785484");
	/*
						root
	A     m     a          z  o  n    N    e   h   <sp>
	m     a     z <sp> n   o  n <5,8> e    h   a    A
	a     z n   o   A  <7> n <4>      h    a  <sp>  m
	z n   o <6> n   m     <3>         a  <sp>  A    a
	o <5> n    <2>  a                <sp>  A   m    n
	n    <1>        n                 A    m   a    <4>
	<0>            <3>                m    a   n
									  a	   n   <2>
									  n   <1>
									 <0>
	*/
	indexes = sTree.GetIndexes("Ama");
	ASSERT_EQ(2, indexes.size());
	ASSERT_EQ(0, indexes[0]);
	ASSERT_EQ(11, indexes[1]);
	subStrings.clear();
	indexes = sTree.GetIndexes("+6591785484");
	ASSERT_EQ(1, indexes.size());
	ASSERT_EQ(15, indexes[0]);
	indexes = sTree.GetIndexes("91785484");
	ASSERT_EQ(1, indexes.size());
	ASSERT_EQ(18, indexes[0]);
	sTree.RemoveString("Amazon");
	sTree.RemoveString("Neha Aman");
	sTree.RemoveString("+6591785484");
	indexes = sTree.GetIndexes("Amazon");
	ASSERT_TRUE(indexes.empty());
	indexes = sTree.GetIndexes("Neha Aman");
	ASSERT_TRUE(indexes.empty());
	indexes = sTree.GetIndexes("+6591785484");
	ASSERT_TRUE(indexes.empty());
	sTree.Clear();
	ASSERT_FALSE(sTree.Count());

	sTree.Clear();
	sTree.InsertString("abc.pqr.google.com");
	sTree.InsertString("pqr.google.com");
	sTree.InsertString("pqr.google.net");
	sTree.InsertString("yahoo.com");
	sTree.InsertString("abc.yahoo.com");
	indexes = sTree.GetIndexes("google.com");
	ASSERT_EQ(2, indexes.size());
	ASSERT_EQ(8, indexes[0]);
	ASSERT_EQ(22, indexes[1]);
	sTree.Clear();
	sTree.InsertString("a");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_TRUE(subStrings.empty());
	sTree.Clear();
	sTree.InsertString("aa");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_TRUE(!subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("a", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("aaa");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("aa", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("ABABABA");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("ABABA", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("abcd1234cd12");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("cd12", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("abcd1234abcd");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("abcd", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("abcdabcd1234");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("abcd", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("abcd12341234");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("1234", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("aaaa_11111_bbbb");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("1111", subStrings[0]);
	sTree.Clear();
	sTree.InsertString("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(2, subStrings.size());
	ASSERT_EQ("AAAAACCCCC", subStrings[0]);
	ASSERT_EQ("CCCCCAAAAA", subStrings[1]);
	sTree.Clear();
	sTree.InsertString("GAGAGAGAGAGAG");
	subStrings = sTree.LongestRepeatedSubstring();
	ASSERT_FALSE(subStrings.empty());
	ASSERT_EQ(1, subStrings.size());
	ASSERT_EQ("GAGAGAGAGAG", subStrings[0]);

	sTree.Clear();
	size_t match;
	sTree.InsertString("abcd");
	sTree.InsertString("adbc");
	match = sTree.LongestCommonSubstring(0); // bc
	ASSERT_EQ(2, match);
	match = sTree.LongestCommonSubstring(1);
	ASSERT_EQ(3, match);
	sTree.Clear();
	sTree.InsertString("helloworld");
	sTree.InsertString("yellomarin");
	match = sTree.LongestCommonSubstring(0); // ello
	ASSERT_EQ(4, match);
	match = sTree.LongestCommonSubstring(3);
	ASSERT_EQ(8, match);
	sTree.Clear();
	sTree.InsertString("abacba");
	sTree.InsertString("abcaba");
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(3, match);
	// match = sTree.LongestCommonSubstring(1); // 'abaxba'
	// assert(match == 4);
	sTree.Clear();
	sTree.InsertString("tabriz");
	sTree.InsertString("torino");
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(2, match);
	match = sTree.LongestCommonSubstring(2);
	ASSERT_EQ(4, match);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbcabcghijmnopq"); // match "ghij"
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(4, match);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bmnobcdeijkq"); // match "bcde"
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(4, match);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbijkmnopqrstuv"); // match "bcde" with first string
	sTree.InsertString("ijklmnopqrst");	   // match "ijk" with all other strings
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(3, match);
	match = sTree.LongestCommonSubstring(1);
	ASSERT_EQ(4, match);
	sTree.Clear();
	sTree.InsertString("abcdefghijkl");
	sTree.InsertString("bbcfghiopqrstuv");
	sTree.InsertString("ijklmnopfghistuvw");
	sTree.InsertString("fghimnopqrstuv"); // match "fghi" with all other strings
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(4, match);
	match = sTree.LongestCommonSubstring(1);
	ASSERT_EQ(5, match);
	sTree.Clear();
	sTree.InsertString("abcdewxyzjkl");
	sTree.InsertString("bbcwxyzoijkq");
	sTree.InsertString("ijklmnopwxyzstuv");
	sTree.InsertString("wxyzmnopqrst");
	sTree.InsertString("abcdmnopqrstwxyz"); // match "wxyz" with all other strings
	match = sTree.LongestCommonSubstring(0);
	ASSERT_EQ(4, match);
	match = sTree.LongestCommonSubstring(1);
	ASSERT_EQ(5, match);

	sTree.Clear();
	sTree.InsertString("Mississippi");
	ASSERT_EQ(53, sTree.Count());
	sTree.InsertString("Mississippi");
	ASSERT_EQ(53, sTree.Count()); // Assert no duplicates!
	indices1 = sTree.GetIndexes("is");
	ASSERT_EQ(2, indices1.size()); // ississippi, issippi
	ASSERT_EQ(1, indices1[0]);
	ASSERT_EQ(4, indices1[1]);
}