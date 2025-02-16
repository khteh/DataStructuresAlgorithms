#include "stdafx.h"
#include "PrefixTrie.h"
PrefixTrie::PrefixTrie()
	: _root(make_unique<PrefixTrieNode>())
{
}
PrefixTrie::PrefixTrie(vector<string> &str)
	: PrefixTrie()
{
	for (vector<string>::const_iterator it = str.begin(); it != str.end(); it++)
		_root->InsertString(*it, 0);
}

PrefixTrie::~PrefixTrie()
{
	Clear();
}
size_t PrefixTrie::Count() const
{
	return _root ? _root->Count() : 0;
}
void PrefixTrie::InsertString(string const &str)
{
	if (!_root)
		_root = make_unique<PrefixTrieNode>();
	_root->InsertString(str, 0);
}
void PrefixTrie::RemoveString(string const &str)
{
	if (_root)
		_root->RemoveString(str);
}
bool PrefixTrie::Find(string const &prefix)
{
	return _root && !prefix.empty() ? _root->Find(prefix) : false;
}
vector<string> PrefixTrie::StartsWith(string const &prefix)
{
	return _root ? _root->StartsWith(prefix, 0) : vector<string>();
}
vector<string> PrefixTrie::GetNodes()
{
	return _root ? _root->GetNodes() : vector<string>();
}
PrefixTrieNode *PrefixTrie::GetNode(string const &prefix)
{
	return _root && !prefix.empty() ? _root->GetNode(prefix, 0) : nullptr;
}
string PrefixTrie::LongestCommonPrefix(string const &prefix)
{
	return _root && !prefix.empty() ? _root->LongestCommonPrefix(prefix) : "";
}
void PrefixTrie::Clear()
{
	_root.reset();
}
PrefixTrieNode::PrefixTrieNode()
{
}
PrefixTrieNode::~PrefixTrieNode()
{
	_children.clear();
}
string PrefixTrieNode::Value()
{
	return _key;
}
size_t PrefixTrieNode::Count() const
{
	size_t count = _children.size();
	for (map<char, unique_ptr<PrefixTrieNode>>::const_iterator it = _children.begin(); it != _children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			throw runtime_error("Bogus node!!!");
	return count;
}
void PrefixTrieNode::InsertString(string str, size_t index)
{
	if (index < str.size())
	{
		pair<map<char, unique_ptr<PrefixTrieNode>>::iterator, bool> result = _children.emplace(str[index], make_unique<PrefixTrieNode>());
		result.first->second->InsertString(str, index + 1);
	}
	else
		_key = str; // Store the prefix string at the leaf node.
}
void PrefixTrieNode::RemoveString(string str)
{
	if (str.length() && _children.count(str[0]))
	{
		_children[str[0]]->RemoveString(str.substr(1));
		_children.erase(str[0]);
	}
}
vector<string> PrefixTrieNode::GetNodes()
{
	ostringstream oss;
	vector<string> result;
	for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = _children.begin(); it != _children.end(); it++)
	{
		vector<string> tmp = it->second->GetNodes();
		string str(1, it->first);
		if (tmp.empty())
			result.push_back(str);
		for (vector<string>::iterator it1 = tmp.begin(); it1 != tmp.end(); it1++)
		{
			oss << it->first << *it1;
			result.push_back(oss.str());
			oss.str("");
		}
	}
	return result;
}
vector<string> PrefixTrieNode::StartsWith(string const &prefix, size_t index)
{
	vector<string> result;
	if (index < prefix.size() && _children.count(prefix[index]))
		result = _children[prefix[index]]->StartsWith(prefix, index + 1);					// Nodes with common prefix
	else if (_children.empty() && !_key.empty() && _key.substr(0, prefix.size()) == prefix) // Leaf node
		result.push_back(_key);
	else
	{
		if (!_key.empty() && _key.substr(0, prefix.size()) == prefix)
			result.push_back(_key); // All descendants of this node have common prefix of the string associated with this node. Ex: "to", "topple"
		/*
			apple, appendix, appetite
			prefix: app
			index: 3
			_children contains 'l', 'e' but ordered to 'e', 'l' as std::map is ordered
		*/
		for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = _children.begin(); it != _children.end(); it++)
		{
			vector<string> tmp = it->second->StartsWith(prefix, index + 1);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
	return result;
}
/* Find exact string with '.' wildcard character
 */
bool PrefixTrieNode::Find(string const &prefix)
{
	/* Worst case time complexity: O(26x26)
	* _key = abc
	* prefix = ab.
	* root: ab.
	* 'a': b.
	* 'b': .
	*
	* prefix = a.c
	* root: a.c
	* 'a': .c
	* 'b': .

	* prefix = ab..
	* root: ab..
	* 'a': b..
	* 'b': ..
	* 'c': .
	*
	* _key = runner
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
		if (prefix[0] == '.')
		{
			for (map<char, unique_ptr<PrefixTrieNode>>::iterator it = _children.begin(); it != _children.end(); it++)
				if (it->second->Find(prefix.substr(1)))
					return true;
			return false; // prefix is longer than the current tree
		}
		else // Nodes with common prefix
			return _children.count(prefix[0]) ? _children[prefix[0]]->Find(prefix.substr(1)) : false;
	// Either Leaf node (!_key.empty()) or prefix not found
	return !_key.empty();
}
PrefixTrieNode *PrefixTrieNode::GetNode(string const &prefix, size_t index)
{
	if (index < prefix.size() && _children.count(prefix[index]))
		return _children[prefix[index]]->GetNode(prefix, index + 1);
	else if (_children.empty() || index == prefix.size())
		return this;
	return nullptr;
}
string PrefixTrieNode::ExtendPrefix()
{
	ostringstream oss;
	if (_key == "" && _children.size() == 1)
		oss << _children.begin()->first << _children.begin()->second->ExtendPrefix();
	return oss.str();
}
string PrefixTrieNode::LongestCommonPrefix(string const &prefix)
{
	string prefix1(prefix);
	PrefixTrieNode *node = GetNode(prefix, 0);
	return node ? prefix1.append(node->ExtendPrefix()) : "";
}