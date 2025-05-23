#pragma once
#include "pch.h"
class SuffixTreeNode;

/*
 http://en.wikipedia.org/wiki/Suffix_tree
					root
	M   i<10>		s				p
	i   s     p		s		i		p   i
	s   s     p     i		s   p	i  <9>
	s   i     i     s	p	s   p  <8>
	i   s  p <7>	s	p	i   i
	s   s  p		i	i	p  <6>
	s   i  i		p  <5>	p
	i   p <4>		p		i
	p   p			i	   <3>
	p   i		   <2>
	i  <1>
	<0>
	Node count = 53
 */
class SuffixTree
{
private:
	vector<string> _strings;
	unique_ptr<SuffixTreeNode> _root;
	const vector<size_t> GetIndexes();

public:
	SuffixTree();
	explicit SuffixTree(string const &);
	~SuffixTree();
	void InsertString(string const &);
	void RemoveString(string const &);
	const vector<size_t> GetIndexes(string const &);
	const vector<string> LongestRepeatedSubstring();
	const size_t LongestCommonSubstring(long); // Uses LongestRepeatedSubstring
	void Clear();
	size_t Count() const;
};

class SuffixTreeNode
{
private:
	char _char;
	map<char, unique_ptr<SuffixTreeNode>> _children;
	set<size_t> _indices;

public:
	explicit SuffixTreeNode(char);
	~SuffixTreeNode();
	void InsertString(string const &, size_t);
	void RemoveString(string const &);
	const set<size_t> GetIndexes();
	const set<size_t> GetIndexes(string const &);
	const map<string, size_t> LongestRepeatedSubstring();
	size_t Count() const;
};