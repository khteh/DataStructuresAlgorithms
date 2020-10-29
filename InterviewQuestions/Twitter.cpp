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
long TweetItem<TUserID, TTweetID>::TimeStamp() const
{
    return _timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator<(const TweetItem& other) const
{
    return _timestamp < other._timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator==(const TweetItem& other) const
{
    return _id == other._id && _user == other._user && _timestamp == other._timestamp;
}
template<typename TUserID, typename TTweetID>
bool TweetItem<TUserID, TTweetID>::operator!=(const TweetItem& other) const
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
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::PostTweet(TUserID userId, TTweetID tweetId)
{
    TweetItem<TUserID, TTweetID> tweet = TweetItem<TUserID, TTweetID>(userId, tweetId);
    _tweets[userId].push_back(tweet);
    for (map<TUserID, set<TUserID>>::iterator it = _follows.begin(); it != _follows.end(); it++)
        if (it->second.find(userId) != it->second.end())
            _tweets[it->first].push_back(tweet);
}
template<typename TUserID, typename TTweetID>
vector<TTweetID> Twitter<TUserID, TTweetID>::GetNewsFeed(TUserID userId, size_t size)
{
    vector<TTweetID> result;
    transform(_tweets[userId].rbegin(), 
        _tweets[userId].rbegin() + min((long)size, (long)_tweets[userId].size()), 
        back_inserter(result),
        [](const TweetItem<TUserID, TTweetID>& tweet) { return tweet.ID(); });
    return result;
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::Follow(TUserID user, TUserID followed)
{
    if (user != followed) {
        _follows[user].insert(followed);
        set<TweetItem<TUserID, TTweetID>> userTweets(_tweets[user].begin(), _tweets[user].end());
        copy_if(_tweets[followed].cbegin(), _tweets[followed].cend(), back_inserter(_tweets[user]), [&userTweets, &followed](const TweetItem<TUserID, TTweetID> &tweet) {
            return tweet.UserID() == followed && userTweets.find(tweet) == userTweets.end();
        });
        sort(_tweets[user].begin(), _tweets[user].end());
    }
}
template<typename TUserID, typename TTweetID>
void Twitter<TUserID, TTweetID>::UnFollow(TUserID user, TUserID followed)
{
    if (user != followed) {
        _follows[user].erase(followed);
        _tweets[user].erase(remove_if(_tweets[user].begin(), _tweets[user].end(), [&followed](const TweetItem<TUserID, TTweetID>& tweet) {return tweet.UserID() == followed; }), _tweets[user].end());
    }
}