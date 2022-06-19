#include "pch.h"
using namespace std;
TEST(LRUCacheTests, LRUCacheTest)
{
	LRUCache<long, long> lruCache(2);
	lruCache.Put(1, 1);
	lruCache.Put(2, 2);
	assert(lruCache.Get(1) == 1);
	lruCache.Put(3, 3);
	assert(lruCache.Get(2) == -1);
	lruCache.Put(4, 4);
	assert(lruCache.Get(1) == -1);
	assert(lruCache.Get(3) == 3);
	assert(lruCache.Get(4) == 4);

	LRUCache<long, long> lruCache1(3);
	lruCache1.Put(1, 1);
	lruCache1.Put(2, 2);
	lruCache1.Put(3, 3);		   // 1,2,3
	lruCache1.Put(4, 4);		   // 2,3,4
	assert(lruCache1.Get(4) == 4); // 2,3,4
	assert(lruCache1.Get(3) == 3); // 2,4,3
	assert(lruCache1.Get(2) == 2); // 4,3,2
	assert(lruCache1.Get(1) == -1);
	lruCache1.Put(5, 5);
	assert(lruCache1.Get(1) == -1);
	assert(lruCache1.Get(2) == 2);
	assert(lruCache1.Get(3) == 3);
	assert(lruCache1.Get(4) == -1);
	assert(lruCache1.Get(5) == 5);

	LRUCache<long, long> lruCache2(1);
	lruCache2.Put(2, 1);
	assert(lruCache2.Get(2) == 1);
	lruCache2.Put(3, 2);
	assert(lruCache2.Get(2) == -1);
	assert(lruCache2.Get(3) == 2);
}