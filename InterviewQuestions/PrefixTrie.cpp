#include "stdafx.h"
#include "PrefixTrie.h"
PrefixTrie::PrefixTrie()
	:m_root(nullptr)
{}
PrefixTrie::PrefixTrie(vector<string>& str)
{
	m_root = make_unique<PrefixTrieNode>();
	for (vector<string>::const_iterator it = str.begin(); it != str.end(); it++)
		m_root->InsertString(*it, 0);
}

PrefixTrie::~PrefixTrie()
{
	m_root.reset();
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
bool PrefixTrie::Find(string const& prefix)
{
	return m_root && !prefix.empty() ? m_root->Find(prefix, 0) : false;
}
vector<string> PrefixTrie::StartsWith(string const& prefix)
{
	return m_root ? m_root->StartsWith(prefix, 0) : vector<string>();
}
vector<string> PrefixTrie::GetNodes()
{
	return m_root ? m_root->GetNodes() : vector<string>();
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
	for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			throw runtime_error("Bogus node!!!");
	return count;
}
void PrefixTrieNode::InsertString(string str, size_t index)
{
	if (index < str.size()) {
		pair<map<char, unique_ptr<PrefixTrieNode>>::iterator, bool> result = m_children.emplace(str[index], make_unique<PrefixTrieNode>());
		result.first->second->InsertString(str, index + 1);
	} else
		m_value = str; // Store the prefix string at the leaf node.
}
void PrefixTrieNode::RemoveString(string str)
{
	if (str.length() && m_children.find(str[0]) != m_children.end())
	{
		m_children[str[0]]->RemoveString(str.substr(1));
		m_children.erase(str[0]);
	}
}
vector<string> PrefixTrieNode::GetNodes()
{
	ostringstream oss;
	vector<string> result;
	for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		vector<string> tmp = it->second->GetNodes();
		string str(1, it->first);
		if (tmp.empty())
			result.push_back(str);
		for (vector<string>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++) {
			oss << it->first << *it1;
			result.push_back(oss.str());
			oss.str("");
		}
	}
	return result;
}
vector<string> PrefixTrieNode::StartsWith(string const& prefix, size_t index)
{
	vector<string> result;
	if (index < prefix.size() && m_children.find(prefix[index]) != m_children.end())
		result = m_children[prefix[index]]->StartsWith(prefix, index + 1); // Nodes with common prefix
	else if (m_children.empty() && !m_value.empty() && m_value.find(prefix) != string::npos) // Leaf node
		result.push_back(m_value);
	else {
		if (!m_value.empty() && m_value.find(prefix) != string::npos)
			result.push_back(m_value); // All descendants of this node as common prefix of the string associated with with this node. Ex: "to", "topple"
		/*
			apple, appendix, appetite
			prefix: app
			index: 3
			m_children contains 'l', 'e' but ordered to 'e', 'l' as std::map is ordered
		*/
		for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = m_children.begin(); it != m_children.end(); it++)
		{
			vector<string> tmp = it->second->StartsWith(prefix, index + 1);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
	return result;
}
bool PrefixTrieNode::Find(string const& prefix, size_t index)
{
	return (index < prefix.size() && m_children.find(prefix[index]) != m_children.end()) ?
		m_children[prefix[index]]->Find(prefix, index + 1) // Nodes with common prefix
		: m_value == prefix; // Leaf node
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