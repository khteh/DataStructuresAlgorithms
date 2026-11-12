#pragma once
using namespace std;
using namespace chrono;
/* https://leetcode.com/problems/design-twitter/
 * 100%
 */
template <typename TUserID, typename TTweetID>
class TweetItem
{
private:
	TTweetID _id;
	TUserID _user;
	uint64_t _timestamp;

public:
	TweetItem(TUserID, TTweetID);
	TTweetID ID() const;
	TUserID UserID() const;
	uint64_t TimeStamp() const;
	bool operator==(const TweetItem<TUserID, TTweetID> &) const;
	// By timestamp only, while == compares all the fields: tweets with the same timestamp are equivalent, not equal.
	// !=, <, <=, > and >= are rewritten from == and <=>
	weak_ordering operator<=>(const TweetItem<TUserID, TTweetID> &) const;
};
template <typename TUserID, typename TTweetID>
class Twitter
{
private:
	map<TUserID, set<TUserID>> _follows;
	map<TUserID, set<TweetItem<TUserID, TTweetID>, greater<TweetItem<TUserID, TTweetID>>>> _tweets;										 // Key: timestamp. Does not guarantee uniqueness based on User and Tweet IDs.
	map<TUserID, map<TTweetID, typename set<TweetItem<TUserID, TTweetID>, greater<TweetItem<TUserID, TTweetID>>>::iterator>> _tweetsMap; // Used to locate tweet in _tweets
public:
	virtual ~Twitter();
	void PostTweet(TUserID, TTweetID);
	vector<TTweetID> GetNewsFeed(TUserID, size_t size = 10);
	vector<TTweetID> GetFromLastNewsFeed(TUserID, TTweetID, size_t size = 10);
	void Follow(TUserID, TUserID);
	void UnFollow(TUserID, TUserID);
	void Clear();
};