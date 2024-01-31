#include "pch.h"
using namespace std;
TEST(TweeterAPITests, TweeterAPITest) {
	vector<size_t> feeds, feeds1;
	Twitter<size_t, size_t> twitter;
	twitter.PostTweet(1, 5);
	feeds = twitter.GetNewsFeed(1);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(1, feeds.size());
	twitter.Follow(1, 2);
	twitter.PostTweet(2, 6);
	feeds = twitter.GetNewsFeed(1);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(2, feeds.size());
	ASSERT_EQ(6, feeds[0]);
	ASSERT_EQ(5, feeds[1]);
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(1, feeds.size());
	twitter.UnFollow(1, 2);
	feeds = twitter.GetNewsFeed(1);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(1, feeds.size());
	ASSERT_EQ(5, feeds[0]);
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(1, feeds.size());
	ASSERT_EQ(6, feeds[0]);
	twitter.Clear();
	twitter.PostTweet(1, 5);
	twitter.Follow(1, 2);
	twitter.Follow(2, 1);
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty()); // 5
	ASSERT_EQ(5, feeds[0]);
	twitter.PostTweet(2, 6);
	feeds = twitter.GetNewsFeed(1);	 // 5, 6(2)
	feeds1 = twitter.GetNewsFeed(2); // 5(1), 6
	ASSERT_FALSE(feeds.empty());
	ASSERT_FALSE(feeds1.empty());
	ASSERT_EQ(2, feeds.size());
	ASSERT_EQ(2, feeds1.size());
	ASSERT_EQ(feeds, feeds1);
	twitter.UnFollow(2, 1); // 1: 5, 6(2) 2: 6
	feeds = twitter.GetNewsFeed(1);
	feeds1 = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_FALSE(feeds1.empty());
	ASSERT_EQ(2, feeds.size());
	ASSERT_EQ(1, feeds1.size());
	twitter.Clear();
	twitter.PostTweet(2, 5);   // 2: 5
	twitter.PostTweet(1, 3);   // 1: 3
	twitter.PostTweet(1, 101); // 1: {3, 101}
	twitter.PostTweet(2, 13);  // 2: {5, 13}
	twitter.PostTweet(2, 10);  // 2: {5, 13, 10}
	twitter.PostTweet(1, 2);   // 1: {3, 101, 2}
	twitter.PostTweet(2, 94);  // 2: {5, 13, 10, 94}
	twitter.PostTweet(2, 505); // 2: {5, 13, 10, 94, 505}
	twitter.PostTweet(1, 333); // 1: {3, 101, 2, 333}
	twitter.PostTweet(1, 22);  // 1: {3, 101, 2, 333, 22}
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(5, feeds.size());
	feeds1 = { 505, 94, 10, 13, 5 };
	ASSERT_EQ(feeds1, feeds);
	twitter.Follow(2, 1); // 2: {5, 13, 10, 94, 505, 3, 101, 2, 133, 22}
	/* [22,333,505,94,2,10,13,101,3,5]
	1: {3, 101, 2, 333, 22}
	2: {5, 13, 10, 94, 505}
	*/
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(10, feeds.size());
	feeds1 = { 22, 333, 505, 94, 2, 10, 13, 101, 3, 5 };
	ASSERT_EQ(feeds1, feeds);
	twitter.Clear();
	twitter.PostTweet(1, 6765); // 1: {6765}
	twitter.PostTweet(5, 671);	// 5: {671}
	twitter.PostTweet(3, 2868); // 3: {2868}
	twitter.PostTweet(4, 8148); // 4: {8148}
	twitter.PostTweet(4, 386);	// 4: {8148, 386}
	twitter.PostTweet(3, 6673); // 3: {2868, 6673}
	twitter.PostTweet(3, 7946); // 3: {2868, 6673, 7946}
	twitter.PostTweet(3, 1445); // 3: {2868, 6673, 7946, 1445}
	twitter.PostTweet(4, 4822); // 4: {8148, 386, 4822}
	twitter.PostTweet(1, 3781); // 1: {6765, 3781}
	twitter.PostTweet(4, 9038); // 4: {8148, 386, 4822, 9038}
	twitter.PostTweet(1, 9643); // 1: {6765, 3781, 9643}
	twitter.PostTweet(3, 5917); // 3: {2868, 6673, 7946, 1445, 5917}
	twitter.PostTweet(2, 8847); // 2: {8847}
	feeds = twitter.GetNewsFeed(1);
	feeds1 = { 9643, 3781, 6765 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(2);
	feeds1 = { 8847 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(3);
	feeds1 = { 5917, 1445, 7946, 6673, 2868 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(4);
	feeds1 = { 9038, 4822, 386, 8148 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(5);
	feeds1 = { 671 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);

	twitter.Follow(1, 3); // 1: {6765, 3781, 9643} 3: {2868, 6673, 7946, 1445, 5917}
	feeds = twitter.GetNewsFeed(1);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(8, feeds.size());
	twitter.Follow(1, 4); // 1: {6765, 3781, 9643} 3: {2868, 6673, 7946, 1445, 5917} 4: {8148, 386, 4822, 9038}
	feeds = twitter.GetNewsFeed(1);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(10, feeds.size()); // Limit to 10 items. Actual result is 12.
	feeds = twitter.GetNewsFeed(1, 20);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(12, feeds.size()); // Limit to 10 items. Actual result is 12.
	twitter.Follow(4, 2);		// 4: {8148, 386, 4822, 9038} 2: {8847}
	feeds = twitter.GetNewsFeed(4);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(5, feeds.size());
	twitter.Follow(4, 1); // 4: {8148, 386, 4822, 9038} 2: {8847} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(4);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(8, feeds.size());
	twitter.Follow(3, 2); // 3: {2868, 6673, 7946, 1445, 5917} 2: {8847}
	feeds = twitter.GetNewsFeed(3);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(6, feeds.size());
	twitter.Follow(3, 5); // 3: {2868, 6673, 7946, 1445, 5917} 2: {8847} 5: {671}
	feeds = twitter.GetNewsFeed(3);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(7, feeds.size());
	twitter.Follow(3, 1); // 3: {2868, 6673, 7946, 1445, 5917} 2: {8847} 5: {671} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(3);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(10, feeds.size());
	twitter.Follow(2, 3); // 2: {8847} 3: {2868, 6673, 7946, 1445, 5917}
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(6, feeds.size());
	twitter.Follow(2, 1); // 2: {8847} 3: {2868, 6673, 7946, 1445, 5917} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(9, feeds.size());
	twitter.Follow(2, 5); // 2: {8847} 3: {2868, 6673, 7946, 1445, 5917} 1: {6765, 3781, 9643} 5: {671}
	feeds = twitter.GetNewsFeed(2);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(10, feeds.size());
	twitter.Follow(5, 1); // 5: {671} 1: {6765, 3781, 9643}
	feeds = twitter.GetNewsFeed(5);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(4, feeds.size());
	twitter.Follow(5, 2); // 5: {671} 1: {6765, 3781, 9643} 2: {8847}
	feeds = twitter.GetNewsFeed(5);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(5, feeds.size());

	feeds = twitter.GetNewsFeed(1);
	feeds1 = { 5917, 9643, 9038, 3781, 4822, 1445, 7946, 6673, 386, 8148 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(2);
	feeds1 = { 8847, 5917, 9643, 3781, 1445, 7946, 6673, 2868, 671, 6765 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(3);
	feeds1 = { 8847, 5917, 9643, 3781, 1445, 7946, 6673, 2868, 671, 6765 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(4);
	feeds1 = { 8847, 9643, 9038, 3781, 4822, 386, 8148, 6765 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetNewsFeed(5);
	feeds1 = { 8847, 9643, 3781, 671, 6765 };
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(feeds1, feeds);

	twitter.Clear();
	twitter.PostTweet(1, 1);
	twitter.PostTweet(1, 2);
	twitter.PostTweet(1, 3);
	twitter.PostTweet(1, 4);
	twitter.PostTweet(1, 5);
	twitter.PostTweet(1, 6);
	twitter.PostTweet(1, 7);
	twitter.PostTweet(1, 8);
	twitter.PostTweet(1, 9);
	twitter.PostTweet(1, 10);
	feeds = twitter.GetNewsFeed(1);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(10, feeds.size());
	feeds1 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetFromLastNewsFeed(1, 5);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(5, feeds.size());
	feeds1 = { 10, 9, 8, 7, 6 };
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetFromLastNewsFeed(1, 5, 3);
	ASSERT_FALSE(feeds.empty());
	ASSERT_EQ(3, feeds.size());
	feeds1 = { 8, 7, 6 };
	ASSERT_EQ(feeds1, feeds);
	feeds = twitter.GetFromLastNewsFeed(1, 10);
	ASSERT_TRUE(feeds.empty());
}