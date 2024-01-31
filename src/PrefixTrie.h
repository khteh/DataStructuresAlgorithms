#pragma once
#include <set>
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
	PrefixTrie();
	PrefixTrie(vector<string> &);
	~PrefixTrie();
	void Clear();
	void InsertString(string const &);
	void RemoveString(string const &);
	PrefixTrieNode *GetNode(string const &);
	vector<string> GetNodes();
	bool Find(string const &);
	vector<string> StartsWith(string const &);
	string LongestCommonPrefix(string const &);
	size_t Count() const;
};

class PrefixTrieNode
{
private:
	string m_key;
	map<char, unique_ptr<PrefixTrieNode>> m_children;
	string ExtendPrefix();

public:
	PrefixTrieNode();
	~PrefixTrieNode();
	string Value();
	size_t Count() const;
	void InsertString(string, size_t);
	void RemoveString(string);
	vector<string> GetNodes();
	PrefixTrieNode *GetNode(string const &, size_t);
	bool Find(string const &); // Exact match
	vector<string> StartsWith(string const &, size_t);
	string LongestCommonPrefix(string const &);
};