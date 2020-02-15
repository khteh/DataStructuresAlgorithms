#include "stdafx.h"
#include "Trie.h"
template class Trie<int>;

template<typename T>
Trie<T>::Trie()
{
	m_root = new TrieNode<T>();
}

template<typename T>
Trie<T>::Trie(string const &str, T value)
{
	m_root = new TrieNode<T>();
	Insert(str, value);
}

template<typename T>
Trie<T>::~Trie()
{
	delete m_root;
	m_root = nullptr;
}

template<typename T>
void Trie<T>::Clear()
{
	delete m_root;
	m_root = nullptr;
}

template<typename T>
void Trie<T>::Insert(string const &str, T value)
{
	if (!m_root)
		m_root = new TrieNode<T>();
	m_root->InsertString(str, value);
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
	return m_root ? m_root->Find(key) : T();
}

template<typename T>
size_t Trie<T>::Count()
{
	return m_root ? m_root->Count() : 0;
}

template<typename T>
TrieNode<T>::TrieNode()
{
	m_value = T();
	m_children.clear();
}

template<typename T>
TrieNode<T>::TrieNode(T value)
{
	m_value = value;
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
		pair<map<char, TrieNode<T>*>::iterator, bool> result = m_children.emplace(str[0], new TrieNode<T>());
		result.first->second->InsertString(str.substr(1), value);
	} else
		m_value = value;
}

template<typename T>
T TrieNode<T>::Find(string const &str)
{
	return (!str.empty() && m_children.find(str[0]) != m_children.end()) ?
		m_children[str[0]]->Find(str.substr(1)) : m_value;
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
	for (map<char, TrieNode<T>*>::iterator it = m_children.begin(); it != m_children.end(); it++)
		if (it->second)
			count += it->second->Count();
		else
			assert(false, "Bogus node!!!");
	return count;
}