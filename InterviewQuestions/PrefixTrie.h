#pragma once
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <assert.h>
using namespace std;
class PrefixTrieNode;

class PrefixTrie
{
private:
	unique_ptr<PrefixTrieNode> m_root;
public:
	PrefixTrie(vector<string>&);
	~PrefixTrie();
	void RemoveString(string const &);
	PrefixTrieNode* GetNode(string const&);
	vector<string> GetNodes();
	vector<string> Find(string const&);
	string LongestCommonPrefix(string const&);
	size_t Count();
};

class PrefixTrieNode
{
private:
	string m_value;
	map<char, unique_ptr<PrefixTrieNode>> m_children;
	string ExtendPrefix();
public:
	PrefixTrieNode();
	PrefixTrieNode(string);
	~PrefixTrieNode();
	string Value();
	size_t Count();
	void InsertString(string, size_t);
	void RemoveString(string);
	vector<string> GetNodes();
	PrefixTrieNode* GetNode(string const&, size_t);
	vector<string> Find(string const&, size_t);
	string LongestCommonPrefix(string const&);
};