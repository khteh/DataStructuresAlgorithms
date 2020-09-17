#pragma once
#include <vector>
#include <map>
#include "LinkedList.h"
using namespace std;
template<typename TKey, typename TValue>
class LRUCache
{
private:
	map<TKey, TValue> _cache;
	LinkedList<TValue> _list;
	size_t _capacity;
	void RefreshCacheLine(TKey);
public:
	LRUCache(size_t);
	TValue Get(TKey);
	void Put(TKey, TValue);
	size_t Size();
};