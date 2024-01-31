#include "stdafx.h"
#include "Twitter.h"
template class TweetItem<size_t, size_t>;
template class Twitter<size_t, size_t>;
/* https://leetcode.com/problems/design-twitter/
* 100%
*/
template<typename TUserID, typename TTweetID>
TweetItem<TUserID, TTweetID>::TweetItem(TUserID user, TTweetID tweetID)
    :_id(tweetID), _user(user), _timestamp(system_clock::now().time_since_epoch().count())
{
}
template<typename TUserID, typename TTweetID>
TUserID TweetItem<TUserID, TTweetID>::UserID() const
{
    return _user;
}
template<typename TUserID, typename TTweetID>
TTweetID TweetItem<TUserID, TTweetID>::ID() const
{
    return _id;
}
template<typename TUserID, typename TTweetID>
unsigned long long TweetItem<TUserID, TTweetID>::TimeStamp() const
{
    return _timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator<(const TweetItem<TUserID, TTweetID>& other) const
{
    return _timestamp < other._timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator>(const TweetItem<TUserID, TTweetID>& other) const
{
    return _timestamp > other._timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator==(const TweetItem<TUserID, TTweetID>& other) const
{
    return _id == other._id && _user == other._user && _timestamp == other._timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator!=(const TweetItem<TUserID, TTweetID>& other) const
{
    return _id != other._id || _user != other._user || _timestamp != other._timestamp;
}
template<typename TUserID, typename TTweetID>
Twitter<TUserID, TTweetID>::~Twitter()
{
    Clear();
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::Clear()
{
    _follows.clear();
    _tweets.clear();
    _tweetsMap.clear();
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::PostTweet(TUserID userId, TTweetID tweetId)
{
    typename set<TweetItem<TUserID, TTweetID>>::iterator newFeed = _tweets[userId].emplace(userId, tweetId).first;
    _tweetsMap[userId][tweetId] = newFeed;
    for (typename map<TUserID, set<TUserID>>::iterator it = _follows.begin(); it != _follows.end(); it++)
        if (it->second.find(userId) != it->second.end()) {
            _tweets[it->first].insert(*newFeed);
            _tweetsMap[it->first][tweetId] = _tweets[it->first].find(*newFeed);
        }
}
template<typename TUserID, typename TTweetID>
vector<TTweetID> Twitter<TUserID, TTweetID>::GetNewsFeed(TUserID userId, size_t size)
{
    vector<TTweetID> result;
    typename set<TweetItem<TUserID, TTweetID>, greater<TweetItem<TUserID, TTweetID>>>::iterator start = _tweets[userId].begin(), end = start;
    advance(end, min(size, _tweets[userId].size()));
    ranges::transform(start, 
        end, 
        back_inserter(result),
        [](const TweetItem<TUserID, TTweetID>& tweet) { return tweet.ID(); });
    return result;
}
template<typename TUserID, typename TTweetID>
vector<TTweetID> Twitter<TUserID, TTweetID>::GetFromLastNewsFeed(TUserID userId, TTweetID tweetId, size_t size)
{
    vector<TTweetID> result;
    if (_tweetsMap[userId].find(tweetId) != _tweetsMap[userId].end() && _tweetsMap[userId][tweetId] != _tweets[userId].begin()) {
        typename set<TweetItem<TUserID, TTweetID>, greater<TweetItem<TUserID, TTweetID>>>::iterator start = _tweets[userId].begin(), end = _tweetsMap[userId][tweetId];
        size_t counts = distance(_tweets[userId].begin(), _tweetsMap[userId][tweetId]);
        if (counts > size)
            advance(start, counts - size);
        ranges::transform(start,
            end,
            back_inserter(result),
            [](const TweetItem<TUserID, TTweetID>& tweet) { return tweet.ID(); });
    }
    return result;
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::Follow(TUserID user, TUserID followed)
{
    if (user != followed && _follows[user].find(followed) == _follows[user].end()) {
        _follows[user].insert(followed);
        for (typename set<TweetItem<TUserID, TTweetID>, greater<TweetItem<TUserID, TTweetID>>>::const_iterator it = _tweets[followed].cbegin(); it != _tweets[followed].cend(); it++)
            if (it->UserID() == followed && _tweetsMap[user].find(it->ID()) == _tweetsMap[user].end()) {
                _tweets[user].insert(*it);
                _tweetsMap[user].emplace(it->ID(), _tweets[user].find(*it));
            }
    }
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::UnFollow(TUserID user, TUserID followed)
{
    if (user != followed && _follows[user].find(followed) != _follows[user].end()) {
        _follows[user].erase(followed);
        for (typename set<TweetItem<TUserID, TTweetID>, greater<TweetItem<TUserID, TTweetID>>>::const_iterator it = _tweets[user].cbegin(); it != _tweets[user].cend(); )
            if (it->UserID() == followed) {
                _tweetsMap[user].erase(it->ID());
                it = _tweets[user].erase(it);
            } else
                it++;
    }
}