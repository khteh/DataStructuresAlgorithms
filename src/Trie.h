#pragma once
#include "pch.h"
using namespace std;
template <typename T>
class TrieNode;
template <typename T>
class Trie
{
private:
	shared_ptr<TrieNode<T>> _root;
	T FindFast(string const &, shared_ptr<TrieNode<T>> &);

public:
	Trie();
	Trie(string const &, T);
	~Trie();
	void Insert(string const &, T);
	void InsertFast(string const &, T);
	void RemoveString(string const &);
	T Find(string const &);
	T FindFast(string const &);
	void Clear();
	size_t Count() const;
};

template <typename T>
class TrieNode : enable_shared_from_this<TrieNode<T>>
{
private:
	T _key;
	map<char, shared_ptr<TrieNode<T>>> _children;

public:
	typedef typename map<char, shared_ptr<TrieNode<T>>>::const_iterator IteratorType;
	TrieNode();
	TrieNode(T);
	~TrieNode();
	T Key() const;
	void SetKey(T);
	void InsertString(string const &, T);
	void RemoveString(string const &);
	T Find(string const &);
	shared_ptr<TrieNode<T>> Node(char);
	shared_ptr<TrieNode<T>> AddNode(char);
	IteratorType ChildrenStart() const;
	IteratorType ChildrenEnd() const;
	size_t Count() const;
};