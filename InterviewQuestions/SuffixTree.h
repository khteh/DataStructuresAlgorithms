#pragma once
#include <map>
#include <vector>
#include <string>
#include <assert.h>
using namespace std;
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
	SuffixTreeNode *m_root;
public:
	SuffixTree();
	SuffixTree(string const &);
	~SuffixTree();
	void InsertString(string const &);
	void RemoveString(string const &);
	const vector<size_t> GetIndexes(string const & s);
	void Clear();
	size_t Count();
};

class SuffixTreeNode
{
private:
	map<char, SuffixTreeNode*> m_children;
	vector<size_t> m_indexes;
public:
	~SuffixTreeNode();
	void InsertString(string const &, size_t);
	void RemoveString(string const &);
	const vector<size_t> GetIndexes(string const &);
	size_t Count();
};