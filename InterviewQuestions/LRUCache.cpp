#include "stdafx.h"
#include "LRUCache.h"
template class LRUCache<long, long>;

template<typename TKey, typename TValue>
LRUCache<TKey, TValue>::LRUCache(size_t capacity)
	:_capacity(capacity)
{
}
template<typename TKey, typename TValue>
void LRUCache<TKey, TValue>::RefreshCacheLine(TKey key)
{
    _list.MoveItem2Tail(key);
}
template<typename TKey, typename TValue>
TValue LRUCache<TKey, TValue>::Get(TKey key)
{
    if (_cache.find(key) == _cache.end())
        return -1;
    else {
        RefreshCacheLine(key);
        return _cache[key];
    }
}
template<typename TKey, typename TValue>
void LRUCache<TKey, TValue>::Put(TKey key, TValue value)
{
    if (_cache.find(key) != _cache.end()) {
        _cache[key] = value;
        RefreshCacheLine(key);
    } else {
        if (_cache.size() >= _capacity) {
            // Evicts cache line
            shared_ptr<Node<TKey>> toRemove = _list.RemoveHead();
            if (toRemove)
                _cache.erase(toRemove->Item());
        }
        shared_ptr<Node<TKey>> n = _list.AddItem(key);
        _cache.emplace(key, value);
    }
}
template<typename TKey, typename TValue>
size_t LRUCache<TKey, TValue>::Size()
{
    return _cache.size();
}