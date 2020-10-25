#pragma once
#include <list>
#include <map>
using namespace std;
template<typename TKey, typename TValue>
class LRUCache
{
private:
	map<TKey, pair<typename list<TKey>::iterator, TValue>> _cache;
	list<TKey> _entries; // Front: Most recently used. Back: Least recently used
	size_t _capacity;
	void RefreshCacheLine(TKey);
public:
	LRUCache(size_t);
	TValue Get(TKey);
	void Put(TKey, TValue);
	size_t Size();
};