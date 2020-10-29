#pragma once
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;
/* https://leetcode.com/problems/design-twitter/
* 100%
*/
template<typename TUserID, typename TTweetID>
class TweetItem {
private:
	TTweetID _id;
	TUserID _user;
	unsigned long long _timestamp;
public:
	TweetItem(TUserID, TTweetID);
	TTweetID ID() const;
	TUserID UserID() const;
	long TimeStamp() const;
	bool operator<(const TweetItem&) const;
	bool operator==(const TweetItem&) const;
	bool operator!=(const TweetItem&) const;
};
template<typename TUserID, typename TTweetID>
class Twitter
{
private:
	map<TUserID, set<TUserID>> _follows;
	map<TUserID, vector<TweetItem<TUserID, TTweetID>>> _tweets;
	long _lastSequence;
public:
	virtual ~Twitter();
	void PostTweet(TUserID, TTweetID);
	vector<TTweetID> GetNewsFeed(TUserID, size_t size = 10);
	void Follow(TUserID, TUserID);
	void UnFollow(TUserID, TUserID);
	void Clear();
};