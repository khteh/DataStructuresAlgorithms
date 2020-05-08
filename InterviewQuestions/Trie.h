#pragma once
#include "stdafx.h"
#include <map>
#include <string>
#include <vector>
#include <assert.h>
#include <memory>
#include <stdexcept>
using namespace std;
template<typename T>
class TrieNode;

template<typename T>
class Trie
{
private:
	shared_ptr<TrieNode<T>> m_root;
public:
	Trie();
	Trie(string const &, T);
	~Trie();
	void Insert(string const &, T);
	void RemoveString(string const &str);
	T Find(string const &);
	void Clear();
	size_t Count();
};

template<typename T>
class TrieNode
{
private:
	T m_value;
	map<char, shared_ptr<TrieNode<T>>> m_children;
public:
	TrieNode();
	TrieNode(T value);
	~TrieNode<T>();
	void InsertString(string const &str, T value);
	void RemoveString(string const &str);
	T Find(string const &str);
	size_t Count();
};