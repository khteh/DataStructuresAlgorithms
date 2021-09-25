#include "stdafx.h"
#include "Trie.h"
template class Trie<int>;

template<typename T>
Trie<T>::Trie()
	:m_root(make_unique<TrieNode<T>>())
{
}

template<typename T>
Trie<T>::Trie(string const &str, T value)
	:Trie()
{
	Insert(str, value);
}

template<typename T>
Trie<T>::~Trie()
{
	Clear();
}

template<typename T>
void Trie<T>::Clear()
{
	m_root.reset();
}
template<typename T>
void Trie<T>::Insert(string const &str, T value)
{
	if (!m_root)
		m_root = make_unique<TrieNode<T>>();
	m_root->InsertString(str, value);
}
template<typename T>
void Trie<T>::InsertFast(string const& str, T value)
{
	if (!m_root)
		m_root = make_unique<TrieNode<T>>();
	shared_ptr<TrieNode<T>> n = m_root;
	for (string::const_iterator it = str.cbegin(); it != str.cend(); it++)
		n = n->AddNode(*it);
	n->SetKey(value);
}
template<typename T>
void Trie<T>::RemoveString(string const &str)
{
	if (m_root)
		m_root->RemoveString(str);
}
template<typename T>
T Trie<T>::Find(string const &key)
{
	return m_root ? m_root->Find(key) : numeric_limits<T>::min();
}
template<typename T>
T Trie<T>::FindFast(string const& key)
{
	shared_ptr<TrieNode<T>> n = m_root;
	return n ? FindFast(key, n) : numeric_limits<T>::min();
}
template<typename T>
T Trie<T>::FindFast(string const& key, shared_ptr<TrieNode<T>>& n)
{
	for (size_t i = 0; i < key.size() && n; i++) {
		if (key[i] != '.')
			n = n->Node(key[i]);
		else {
			for (typename TrieNode<T>::IteratorType it = n->ChildrenStart(); it != n->ChildrenEnd(); it++) {
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
template<typename T>
size_t Trie<T>::Count()
{
	return m_root ? m_root->Count() : 0;
}

template<typename T>
TrieNode<T>::TrieNode()
	:m_key(numeric_limits<T>::min())
{
	m_children.clear();
}

template<typename T>
TrieNode<T>::TrieNode(T value)
	: m_key(value)
{
	m_children.clear();
}

template<typename T>
TrieNode<T>::~TrieNode()
{
	m_children.clear();
}

template<typename T>
void TrieNode<T>::InsertString(string const &str, T value)
{
	if (!str.empty()) {
		pair<typename map<char, shared_ptr<TrieNode<T>>>::iterator, bool> result = m_children.emplace(str[0], make_shared<TrieNode<T>>());
		result.first->second->InsertString(str.substr(1), value);
	} else
		m_key = value; // Store the value at the leaf node.
}
template<typename T>
T TrieNode<T>::Find(string const &prefix)
{
	if (!prefix.empty())
		if (prefix[0] == '.') {
			for (typename map<char, shared_ptr<TrieNode<T>>>::iterator it = m_children.begin(); it != m_children.end(); it++) {
				T key = it->second->Find(prefix.substr(1));
				if (key != numeric_limits<T>::min())
					return key;
			}
			return numeric_limits<T>::min(); // prefix is longer than the current trie
		} else // Nodes with common prefix
			return m_children.find(prefix[0]) != m_children.end() ? m_children[prefix[0]]->Find(prefix.substr(1)) : numeric_limits<T>::min();
	// Either Leaf node (!m_key.empty()) or prefix not found
	return m_key;
}
template<typename T>
shared_ptr<TrieNode<T>> TrieNode<T>::Node(char c)
{
	return m_children.find(c) != m_children.end() ? m_children[c] : nullptr;
}
template<typename T>
shared_ptr<TrieNode<T>> TrieNode<T>::AddNode(char c)
{
	m_children.emplace(c, make_shared<TrieNode<T>>());
	return m_children[c];
}
template<typename T>
T TrieNode<T>::Key() const
{
	return m_key;
}
template<typename T>
void TrieNode<T>::SetKey(T key)
{
	m_key = key;
}
template<typename T>
typename map<char, shared_ptr<TrieNode<T>>>::const_iterator TrieNode<T>::ChildrenStart() const
{
	return m_children.cbegin();
}
template<typename T>
typename map<char, shared_ptr<TrieNode<T>>>::const_iterator TrieNode<T>::ChildrenEnd() const
{
	return m_children.cend();
}
template<typename T>
void TrieNode<T>::RemoveString(string const &str)
{
	if (!str.empty() && m_children.find(str[0]) != m_children.end())
	{
		m_children[str[0]]->RemoveString(str.substr(1));
		m_children.erase(str[0]);
	}
}
template<typename T>
size_t TrieNode<T>::Count()
{
	size_t count = m_children.size();
	for (typename map<char, shared_ptr<TrieNode<T>>>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			throw runtime_error("Bogus node!!!");
	return count;
}