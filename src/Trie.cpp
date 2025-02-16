#include "stdafx.h"
#include "Trie.h"
template class Trie<int>;

template <typename T>
Trie<T>::Trie()
	: _root(make_unique<TrieNode<T>>())
{
}

template <typename T>
Trie<T>::Trie(string const &str, T value)
	: Trie()
{
	Insert(str, value);
}

template <typename T>
Trie<T>::~Trie()
{
	Clear();
}

template <typename T>
void Trie<T>::Clear()
{
	_root.reset();
}
template <typename T>
void Trie<T>::Insert(string const &str, T value)
{
	if (!_root)
		_root = make_unique<TrieNode<T>>();
	_root->InsertString(str, value);
}
template <typename T>
void Trie<T>::InsertFast(string const &str, T value)
{
	if (!_root)
		_root = make_unique<TrieNode<T>>();
	shared_ptr<TrieNode<T>> n = _root;
	for (string::const_iterator it = str.cbegin(); it != str.cend(); it++)
		n = n->AddNode(*it);
	n->SetKey(value);
}
template <typename T>
void Trie<T>::RemoveString(string const &str)
{
	if (_root)
		_root->RemoveString(str);
}
template <typename T>
T Trie<T>::Find(string const &key)
{
	return _root ? _root->Find(key) : numeric_limits<T>::min();
}
template <typename T>
T Trie<T>::FindFast(string const &key)
{
	shared_ptr<TrieNode<T>> n = _root;
	return n ? FindFast(key, n) : numeric_limits<T>::min();
}
template <typename T>
T Trie<T>::FindFast(string const &key, shared_ptr<TrieNode<T>> &n)
{
	for (size_t i = 0; i < key.size() && n; i++)
	{
		if (key[i] != '.')
			n = n->Node(key[i]);
		else
		{
			for (typename TrieNode<T>::IteratorType it = n->ChildrenStart(); it != n->ChildrenEnd(); it++)
			{
				string str = key.substr(i + 1);
				shared_ptr<TrieNode<T>> next = it->second;
				T key = FindFast(str, next);
				if (key != numeric_limits<T>::min())
					return key;
			}
			return numeric_limits<T>::min(); // prefix is longer than the current trie
		}
	}
	return n ? n->Key() : numeric_limits<T>::min();
}
template <typename T>
size_t Trie<T>::Count() const
{
	return _root ? _root->Count() : 0;
}

template <typename T>
TrieNode<T>::TrieNode()
	: _key(numeric_limits<T>::min())
{
	_children.clear();
}

template <typename T>
TrieNode<T>::TrieNode(T value)
	: _key(value)
{
	_children.clear();
}

template <typename T>
TrieNode<T>::~TrieNode()
{
	_children.clear();
}

template <typename T>
void TrieNode<T>::InsertString(string const &str, T value)
{
	if (!str.empty())
	{
		pair<typename map<char, shared_ptr<TrieNode<T>>>::iterator, bool> result = _children.emplace(str[0], make_shared<TrieNode<T>>());
		result.first->second->InsertString(str.substr(1), value);
	}
	else
		_key = value; // Store the value at the leaf node.
}
template <typename T>
T TrieNode<T>::Find(string const &prefix)
{
	if (!prefix.empty())
		if (prefix[0] == '.')
		{
			for (typename map<char, shared_ptr<TrieNode<T>>>::iterator it = _children.begin(); it != _children.end(); it++)
			{
				T key = it->second->Find(prefix.substr(1));
				if (key != numeric_limits<T>::min())
					return key;
			}
			return numeric_limits<T>::min(); // prefix is longer than the current trie
		}
		else // Nodes with common prefix
			return _children.count(prefix[0]) ? _children[prefix[0]]->Find(prefix.substr(1)) : numeric_limits<T>::min();
	// Either Leaf node (!_key.empty()) or prefix not found
	return _key;
}
template <typename T>
shared_ptr<TrieNode<T>> TrieNode<T>::Node(char c)
{
	return _children.count(c) ? _children[c] : nullptr;
}
template <typename T>
shared_ptr<TrieNode<T>> TrieNode<T>::AddNode(char c)
{
	_children.emplace(c, make_shared<TrieNode<T>>());
	return _children[c];
}
template <typename T>
T TrieNode<T>::Key() const
{
	return _key;
}
template <typename T>
void TrieNode<T>::SetKey(T key)
{
	_key = key;
}
template <typename T>
typename map<char, shared_ptr<TrieNode<T>>>::const_iterator TrieNode<T>::ChildrenStart() const
{
	return _children.cbegin();
}
template <typename T>
typename map<char, shared_ptr<TrieNode<T>>>::const_iterator TrieNode<T>::ChildrenEnd() const
{
	return _children.cend();
}
template <typename T>
void TrieNode<T>::RemoveString(string const &str)
{
	if (!str.empty() && _children.count(str[0]))
	{
		_children[str[0]]->RemoveString(str.substr(1));
		_children.erase(str[0]);
	}
}
template <typename T>
size_t TrieNode<T>::Count() const
{
	size_t count = _children.size();
	for (typename map<char, shared_ptr<TrieNode<T>>>::const_iterator it = _children.begin(); it != _children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			throw runtime_error("Bogus node!!!");
	return count;
}