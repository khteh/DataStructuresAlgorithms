#include "StdAfx.h"
#include "SuffixTree.h"

SuffixTree::SuffixTree()
{
	m_root = make_shared<SuffixTreeNode>();
}

SuffixTree::SuffixTree(string const &str)
{
	m_root = make_shared<SuffixTreeNode>();
	InsertString(str);
}

SuffixTree::~SuffixTree()
{
	Clear();
}

void SuffixTree::Clear()
{
	m_root.reset();
}
size_t SuffixTree::Count()
{
	return m_root ? m_root->Count() : 0;
}

void SuffixTree::InsertString(string const &str)
{
	if (!m_root)
		m_root = make_shared<SuffixTreeNode>();
	for (size_t i = 0; i < str.size(); i++)
		m_root->InsertString(str.substr(i), i);
}
void SuffixTree::RemoveString(string const &str)
{
	m_root->RemoveString(str);
}
const vector<size_t> SuffixTree::GetIndexes(string const &s)
{
	return m_root->GetIndexes(s);
}
const size_t SuffixTree::GetSubstrings(size_t n)
{
	// (0 1 2) (5 6 7)
	bool used = false;
	set<size_t> result = m_root->GetSubstrings();
	size_t max = 0, count = 1;
	long lastIndex = -1, lastValue = -1;
	for (set<size_t>::iterator it = result.begin(); it != result.end(); it++) {
		if (lastValue != -1) {
			if (*it != (lastValue + 1)) {
				size_t diff = *it - lastValue - 1;
				if (diff == n) {
					count += (n + 1);
					used = true;
				}
				else {
					if (count > max)
						max = count;
					count = 1;
				}
			}
			else
				count++;
		}
		lastValue = *it;
	}
	if (count > max)
		max = count;
	if (!used)
		max += n;
	return max;
}
SuffixTreeNode::~SuffixTreeNode()
{
	m_children.clear();
	m_indexes.clear();
}
size_t SuffixTreeNode::Count()
{
	size_t count = m_children.size();
	for (map<char, shared_ptr<SuffixTreeNode>>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			assert(false, "Bogus node!!!");
	return count;
}
// Amazon
// Neha Aman
void SuffixTreeNode::InsertString(string const &str, size_t index)
{
	m_indexes.push_back(index);
	if (!str.empty()) {
		pair<map<char, shared_ptr<SuffixTreeNode>>::iterator, bool> result = m_children.emplace(str[0], make_shared<SuffixTreeNode>());
		result.first->second->InsertString(str.substr(1), index);
	}
}
void SuffixTreeNode::RemoveString(string const &str)
{
	if (str.length() && m_children.find(str[0]) != m_children.end())
	{
		m_children[str[0]]->RemoveString(str.substr(1));
		m_children.erase(str[0]);
	}
}
// Returns the indexes recorded by the last matched charater
const vector<size_t> SuffixTreeNode::GetIndexes(string const &str)
{
	vector<size_t> result;
	if (!str.length())
		result = m_indexes; // End of search string. Return indexes of this node.
	if (m_children.find(str[0]) != m_children.end())
		result = m_children[str[0]]->GetIndexes(str.substr(1));
	return result;
}
// Returns the length of the longest matching substrings
const set<size_t> SuffixTreeNode::GetSubstrings()
{
	// abcd, bbca
	/*
						root
		a <3>   b          c     d
		b       c      b   d  a <3>
		c       d  a   c  <2><2>
		d      <1> <1> a
		<0>           <0>
	*/
	set<size_t> result;
	if (m_indexes.size() > 1 && accumulate(m_indexes.begin(), m_indexes.end(), true, [first = m_indexes[0]](bool acc, int b) {
		return acc && (b == first);
		}))
		result.insert(m_indexes[0]);
	for (map<char, shared_ptr<SuffixTreeNode>>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		set<size_t> tmp = it->second->GetSubstrings();
		result.insert(tmp.begin(), tmp.end());
	}
	return result;
}