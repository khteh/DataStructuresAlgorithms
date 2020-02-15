#include "stdafx.h"
#include "PrefixTrie.h"

PrefixTrie::PrefixTrie(vector<string>& str)
{
	m_root = new PrefixTrieNode();
	for (vector<string>::const_iterator it = str.begin(); it != str.end(); it++)
		m_root->InsertString(*it, 0);
}

PrefixTrie::~PrefixTrie()
{
	delete m_root;
	m_root = nullptr;
}
size_t PrefixTrie::Count()
{
	return m_root ? m_root->Count() : 0;
}
void PrefixTrie::RemoveString(string const &str)
{
	if (m_root)
		m_root->RemoveString(str);
}
vector<string> PrefixTrie::Find(string const& prefix)
{
	return m_root && !prefix.empty() ? m_root->Find(prefix, 0) : vector<string>();
}
PrefixTrieNode* PrefixTrie::GetNode(string const& prefix)
{
	return m_root && !prefix.empty() ? m_root->GetNode(prefix, 0) : nullptr;
}
string PrefixTrie::LongestCommonPrefix(string const& prefix)
{
	return m_root && !prefix.empty() ? m_root->LongestCommonPrefix(prefix) : "";
}
PrefixTrieNode::PrefixTrieNode()
{
}
PrefixTrieNode::PrefixTrieNode(string str)
{
	m_value = str;
}
PrefixTrieNode::~PrefixTrieNode()
{
	m_children.clear();
}
string PrefixTrieNode::Value()
{
	return m_value;
}
size_t PrefixTrieNode::Count()
{
	size_t count = m_children.size();
	for (map<char, PrefixTrieNode*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			assert(false, "Bogus node!!!");
	return count;
}
void PrefixTrieNode::InsertString(string str, size_t index)
{
	if (index < str.size()) {
		pair<map<char, PrefixTrieNode*>::iterator, bool> result = m_children.emplace(str[index], new PrefixTrieNode());
		result.first->second->InsertString(str, index + 1);
	} else
		m_value = str;
}
void PrefixTrieNode::RemoveString(string str)
{
	if (str.length() && m_children.find(str[0]) != m_children.end())
	{
		m_children[str[0]]->RemoveString(str.substr(1));
		m_children.erase(str[0]);
	}
}
vector<string> PrefixTrieNode::Find(string const& prefix, size_t index)
{
	vector<string> result;
	if (index < prefix.size() && m_children.find(prefix[index]) != m_children.end())
		result = m_children[prefix[index]]->Find(prefix, index + 1);
	else if (m_children.empty())
		result.push_back(m_value);
	else {
		if (!m_value.empty())
			result.push_back(m_value);
		for (map<char, PrefixTrieNode*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		{
			vector<string> tmp = it->second->Find(prefix, index + 1);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
	return result;
}
PrefixTrieNode* PrefixTrieNode::GetNode(string const& prefix, size_t index)
{
	if (index < prefix.size() && m_children.find(prefix[index]) != m_children.end())
		return m_children[prefix[index]]->GetNode(prefix, index + 1);
	else if (m_children.empty() || index == prefix.size())
		return this;
	return nullptr;
}
string PrefixTrieNode::ExtendPrefix()
{
	ostringstream oss;
	if (m_value == "" && m_children.size() == 1)
		oss << m_children.begin()->first << m_children.begin()->second->ExtendPrefix();
	return oss.str();
}
string PrefixTrieNode::LongestCommonPrefix(string const& prefix)
{
	string prefix1(prefix);
	PrefixTrieNode* node = GetNode(prefix, 0);
	return node ? prefix1.append(node->ExtendPrefix()) : "";
}