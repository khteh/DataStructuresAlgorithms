#include "StdAfx.h"
#include "SuffixTree.h"

SuffixTree::SuffixTree()
{
	m_root = new SuffixTreeNode();
}

SuffixTree::SuffixTree(string const &str)
{
	m_root = new SuffixTreeNode();
	InsertString(str);
}

SuffixTree::~SuffixTree()
{
	delete m_root;
	m_root = nullptr;
}

void SuffixTree::Clear()
{
	delete m_root;
	m_root = nullptr;
}
size_t SuffixTree::Count()
{
	return m_root ? m_root->Count() : 0;
}

void SuffixTree::InsertString(string const &str)
{
	if (!m_root)
		m_root = new SuffixTreeNode();
	for (int i = 0; i < str.length(); i++)
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
SuffixTreeNode::~SuffixTreeNode()
{
	m_children.clear();
	m_indexes.clear();
}
size_t SuffixTreeNode::Count()
{
	size_t count = m_children.size();
	for (map<char, SuffixTreeNode*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			assert(false, "Bogus node!!!");
	return count;
}
void SuffixTreeNode::InsertString(string const &str, size_t index)
{
	m_indexes.push_back(index);
	if (!str.empty()) {
		pair<map<char, SuffixTreeNode*>::iterator, bool> result = m_children.emplace(str[0], new SuffixTreeNode());
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