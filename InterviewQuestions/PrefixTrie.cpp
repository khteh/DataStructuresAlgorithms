#include "stdafx.h"
#include "PrefixTrie.h"
PrefixTrie::PrefixTrie()
	:m_root(make_unique<PrefixTrieNode>())
{}
PrefixTrie::PrefixTrie(vector<string>& str)
	: PrefixTrie()
{
	for (vector<string>::const_iterator it = str.begin(); it != str.end(); it++)
		m_root->InsertString(*it, 0);
}

PrefixTrie::~PrefixTrie()
{
	Clear();
}
size_t PrefixTrie::Count()
{
	return m_root ? m_root->Count() : 0;
}
void PrefixTrie::InsertString(string const& str)
{
	if (!m_root)
		m_root = make_unique<PrefixTrieNode>();
	m_root->InsertString(str, 0);
}
void PrefixTrie::RemoveString(string const &str)
{
	if (m_root)
		m_root->RemoveString(str);
}
bool PrefixTrie::Find(string const& prefix)
{
	return m_root && !prefix.empty() ? m_root->Find(prefix) : false;
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
void PrefixTrie::Clear()
{
	m_root.reset();
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
	return m_key;
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
		m_key = str; // Store the prefix string at the leaf node.
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
	else if (m_children.empty() && !m_key.empty() && m_key.substr(0, prefix.size()) == prefix) // Leaf node
		result.push_back(m_key);
	else {
		if (!m_key.empty() && m_key.substr(0, prefix.size()) == prefix)
			result.push_back(m_key); // All descendants of this node have common prefix of the string associated with this node. Ex: "to", "topple"
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
/* Find exact string with '.' wildcard character
*/
bool PrefixTrieNode::Find(string const& prefix)
{
	/* m_key = abc
	* prefix = ab.
	* root: ab.
	* 'a': b.
	* 'b': .
	* 
	* prefix = ab..
	* root: ab..
	* 'a': b..
	* 'b': ..
	* 'c': .
	* 
	* m_key = runner
	* prefix = ru.n.e
	* root: ru.n.e
	* r: u.n.e
	* u: .n.e
	* *: n.e
	* n: .e
	* *: e
	* 
	*/
	if (!prefix.empty())
		if (prefix[0] == '.') {
			for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = m_children.begin(); it != m_children.end(); it++)
				if (it->second->Find(prefix.substr(1)))
					return true;
			return false; // prefix is longer than the current tree
		} else // Nodes with common prefix
			return m_children.find(prefix[0]) != m_children.end() ? m_children[prefix[0]]->Find(prefix.substr(1)) : false;
	// Either Leaf node (!m_key.empty()) or prefix not found
	return !m_key.empty();
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
	if (m_key == "" && m_children.size() == 1)
		oss << m_children.begin()->first << m_children.begin()->second->ExtendPrefix();
	return oss.str();
}
string PrefixTrieNode::LongestCommonPrefix(string const& prefix)
{
	string prefix1(prefix);
	PrefixTrieNode* node = GetNode(prefix, 0);
	return node ? prefix1.append(node->ExtendPrefix()) : "";
}