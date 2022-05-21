#include "pch.h"
using namespace std;
TEST(TrieTests, TrieTest) {
	Trie<int> trie;					   // Node count:
	trie.InsertFast("Amy", 12);		   // 3
	trie.InsertFast("Christine", 34);  // 9
	trie.InsertFast("Tom", 56);		   // 3
	trie.InsertFast("Robert", 78);	   // 6
	trie.InsertFast("Kristy", 90);	   // 6
	trie.InsertFast("apple", 1);	   // 5
	trie.InsertFast("appendix", 2);	   // 5 ("app" common nodes)
	trie.InsertFast("appetite", 3);	   // 4 ("appe" common nodes)
	trie.InsertFast("to", 4);		   // 2
	trie.InsertFast("topple", 5);	   // 4 ("to" common nodes)
	trie.InsertFast("tea", 6);		   // 2 ("t" common node)
	trie.InsertFast("ted", 7);		   // 1 ("te" common nodes)
	trie.InsertFast("ten", 8);		   // 1 ("te" common nodes)
	trie.InsertFast("in", 9);		   // 2
	trie.InsertFast("inn", 10);		   // 1 ("in" common nodes)
	trie.InsertFast("intrinsics", 11); // 8 ("in" common nodes)
	ASSERT_EQ(12, trie.Find("Amy"));
	ASSERT_EQ(12, trie.FindFast("Amy"));
	ASSERT_EQ(34, trie.Find("Christine"));
	ASSERT_EQ(34, trie.FindFast("Christine"));
	ASSERT_EQ(56, trie.Find("Tom"));
	ASSERT_EQ(56, trie.FindFast("Tom"));
	ASSERT_EQ(78, trie.Find("Robert"));
	ASSERT_EQ(78, trie.FindFast("Robert"));
	ASSERT_EQ(90, trie.Find("Kristy"));
	ASSERT_EQ(90, trie.FindFast("Kristy"));
	ASSERT_EQ(1, trie.Find("apple"));
	ASSERT_EQ(1, trie.FindFast("apple"));
	ASSERT_EQ(2, trie.Find("appendix"));
	ASSERT_EQ(2, trie.FindFast("appendix"));
	ASSERT_EQ(3, trie.Find("appetite"));
	ASSERT_EQ(3, trie.FindFast("appetite"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("app"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("app")); // not found
	ASSERT_EQ(1, trie.Find("ap..e"));
	ASSERT_EQ(1, trie.FindFast("ap..e"));
	ASSERT_EQ(1, trie.Find("ap..."));
	ASSERT_EQ(1, trie.FindFast("ap..."));
	ASSERT_EQ(4, trie.Find("to"));
	ASSERT_EQ(4, trie.FindFast("to"));
	ASSERT_EQ(5, trie.Find("topple"));
	ASSERT_EQ(5, trie.FindFast("topple"));
	ASSERT_EQ(6, trie.Find("tea"));
	ASSERT_EQ(6, trie.FindFast("tea"));
	ASSERT_EQ(7, trie.Find("ted"));
	ASSERT_EQ(7, trie.FindFast("ted"));
	ASSERT_EQ(8, trie.Find("ten"));
	ASSERT_EQ(8, trie.FindFast("ten"));
	ASSERT_EQ(9, trie.Find("in"));
	ASSERT_EQ(9, trie.FindFast("in"));
	ASSERT_EQ(10, trie.Find("inn"));
	ASSERT_EQ(10, trie.FindFast("inn"));
	ASSERT_EQ(11, trie.Find("intrinsics"));
	ASSERT_EQ(11, trie.FindFast("intrinsics"));
	ASSERT_EQ(11, trie.Find("in........"));
	ASSERT_EQ(11, trie.FindFast("in........"));
	ASSERT_EQ(11, trie.Find(".........."));
	ASSERT_EQ(11, trie.FindFast(".........."));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("in........."));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("in........."));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("ABC"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("ABC"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("tee"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("tee"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("t"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("t"));
	size_t count = trie.Count();
	ASSERT_EQ(62, count);
	cout << "Trie has " << count << " nodes" << endl;
	trie.InsertFast("intrinsics", 12);
	ASSERT_EQ(count, trie.Count()); // Assert no duplicates! Only the value changes
	ASSERT_EQ(12, trie.Find("intrinsics"));
	ASSERT_EQ(12, trie.FindFast("intrinsics"));
	trie.RemoveString("Amy");
	trie.RemoveString("Christine");
	trie.RemoveString("Tom");
	trie.RemoveString("Robert");
	trie.RemoveString("Kristy");
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("Amy"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("Christine"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("Tom"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("Robert"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("Kristy"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.Find("ABC"));

	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("Amy"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("Christine"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("Tom"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("Robert"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("Kristy"));
	ASSERT_EQ(numeric_limits<int>::min(), trie.FindFast("ABC"));
	trie.Clear();
}