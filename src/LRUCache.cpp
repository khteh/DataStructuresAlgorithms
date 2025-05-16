#include "pch.h"
#include "LRUCache.h"
template class LRUCache<long, long>;

template <typename TKey, typename TValue>
LRUCache<TKey, TValue>::LRUCache(size_t capacity)
    : _capacity(capacity)
{
}
template <typename TKey, typename TValue>
void LRUCache<TKey, TValue>::RefreshCacheLine(TKey key)
{
    _entries.erase(_cache[key].first);
    _entries.push_front(key);
    _cache[key].first = _entries.begin();
}
template <typename TKey, typename TValue>
TValue LRUCache<TKey, TValue>::Get(TKey key)
{
    if (!_cache.count(key))
        return -1;
    else
    {
        RefreshCacheLine(key);
        return _cache[key].second;
    }
}
template <typename TKey, typename TValue>
void LRUCache<TKey, TValue>::Put(TKey key, TValue value)
{
    if (_cache.count(key))
    {
        _cache[key].second = value;
        RefreshCacheLine(key);
    }
    else
    {
        if (_cache.size() >= _capacity)
        {
            // Evicts cache line
            _cache.erase(_entries.back());
            _entries.pop_back();
        }
        _entries.push_front(key);
        _cache.emplace(key, make_pair(_entries.begin(), value));
    }
}
template <typename TKey, typename TValue>
size_t LRUCache<TKey, TValue>::Size()
{
    return _cache.size();
}