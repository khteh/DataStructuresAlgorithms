#include "pch.h"
using namespace std;
TEST(PrefixTrieTests, PrefixTrieTest)
{
	vector<string> result;
	PrefixTrie prefixTrie;
	cout << "Prefix-Trie tests..." << endl;
	prefixTrie.InsertString("apple");	   // 5
	prefixTrie.InsertString("appendix");   // 5 ("app" common not included)
	prefixTrie.InsertString("appetite");   // 4 ("appe" common not included)
	prefixTrie.InsertString("to");		   // 2
	prefixTrie.InsertString("topple");	   // 4 ("to" common not included)
	prefixTrie.InsertString("tea");		   // 2 ("t" common not included)
	prefixTrie.InsertString("ted");		   // 1 ("te" common not included)
	prefixTrie.InsertString("ten");		   // 1 ("te" common not included)
	prefixTrie.InsertString("in");		   // 2
	prefixTrie.InsertString("inn");		   // 1 ("in" common not included)
	prefixTrie.InsertString("intrinsics"); // 8 ("in" common not included)
	ASSERT_EQ(35, prefixTrie.Count());
	ASSERT_TRUE(prefixTrie.Find(string("apple")));
	result = prefixTrie.StartsWith(string("apple"));
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(1, result.size());
	ASSERT_EQ("apple", result[0]);

	ASSERT_FALSE(prefixTrie.Find(string("app")));
	result = prefixTrie.StartsWith(string("app"));
	ASSERT_EQ(3, result.size());
	ASSERT_EQ("appendix", result[0]);
	ASSERT_EQ("appetite", result[1]);
	ASSERT_EQ("apple", result[2]);

	ASSERT_TRUE(prefixTrie.Find(string("to")));
	result = prefixTrie.StartsWith(string("to"));
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(2, result.size());

	ASSERT_TRUE(prefixTrie.Find(string("in")));
	result = prefixTrie.StartsWith(string("in"));
	ASSERT_EQ(3, result.size());

	ASSERT_FALSE(prefixTrie.Find(string("a")));
	result = prefixTrie.StartsWith(string("a"));
	ASSERT_EQ(3, result.size()); // appendix, appetite, apple
	ASSERT_EQ("appendix", result[0]);
	ASSERT_EQ("appetite", result[1]);
	ASSERT_EQ("apple", result[2]);

	ASSERT_FALSE(prefixTrie.Find(string("i")));
	result = prefixTrie.StartsWith(string("i"));
	ASSERT_EQ(3, result.size()); // in inn intrinsics
	ASSERT_EQ("in", result[0]);
	ASSERT_EQ("inn", result[1]);
	ASSERT_EQ("intrinsics", result[2]);

	ASSERT_FALSE(prefixTrie.Find(string("t")));
	result = prefixTrie.StartsWith(string("t"));
	ASSERT_EQ(5, result.size()); //  tea ted ten to topple
	ASSERT_EQ("tea", result[0]);
	ASSERT_EQ("ted", result[1]);
	ASSERT_EQ("ten", result[2]);
	ASSERT_EQ("to", result[3]);
	ASSERT_EQ("topple", result[4]);

	ASSERT_FALSE(prefixTrie.Find(string("te")));
	result = prefixTrie.StartsWith(string("te"));
	ASSERT_EQ(3, result.size()); // tea ted ten
	ASSERT_EQ("tea", result[0]);
	ASSERT_EQ("ted", result[1]);
	ASSERT_EQ("ten", result[2]);

	PrefixTrieNode *node = prefixTrie.GetNode("apple");
	ASSERT_TRUE(node);
	ASSERT_EQ("apple", node->Value());

	node = prefixTrie.GetNode("app");
	ASSERT_TRUE(node);
	ASSERT_EQ("", node->Value());

	node = prefixTrie.GetNode("to");
	ASSERT_TRUE(node);
	ASSERT_EQ("to", node->Value());

	node = prefixTrie.GetNode("in");
	ASSERT_TRUE(node);
	ASSERT_EQ("in", node->Value());

	node = prefixTrie.GetNode("a");
	ASSERT_TRUE(node);
	ASSERT_EQ("", node->Value());

	node = prefixTrie.GetNode("i");
	ASSERT_TRUE(node);
	ASSERT_EQ("", node->Value());

	node = prefixTrie.GetNode("t");
	ASSERT_TRUE(node);
	ASSERT_EQ("", node->Value());

	node = prefixTrie.GetNode("te");
	ASSERT_TRUE(node);
	ASSERT_EQ("", node->Value());

	result = prefixTrie.GetNodes();
	ASSERT_FALSE(result.empty());

	string longestCommonPrefix = prefixTrie.LongestCommonPrefix("a");
	ASSERT_EQ("app", longestCommonPrefix);

	longestCommonPrefix = prefixTrie.LongestCommonPrefix("i");
	ASSERT_EQ("in", longestCommonPrefix);
	prefixTrie.InsertString("intrinsics");
	ASSERT_EQ(35, prefixTrie.Count()); // Assert no duplicate nodes
	result = prefixTrie.StartsWith(string("apple"));
	ASSERT_EQ(1, result.size());
	ASSERT_EQ("apple", result[0]);

	prefixTrie.Clear();
	ASSERT_FALSE(prefixTrie.Find(string("a")));
	result = prefixTrie.StartsWith(string("a"));
	ASSERT_TRUE(result.empty());

	prefixTrie.InsertString("Hello");
	ASSERT_EQ(5, prefixTrie.Count());
	ASSERT_TRUE(prefixTrie.Find("Hello"));
	ASSERT_FALSE(prefixTrie.Find("Hell"));
	result = prefixTrie.StartsWith(string("Hel"));
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(1, result.size());
	result = prefixTrie.StartsWith(string("Hello"));
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(1, result.size());
	result = prefixTrie.StartsWith(string("Helloa"));
	ASSERT_TRUE(result.empty());
	result = prefixTrie.StartsWith(string("e"));
	ASSERT_TRUE(result.empty());
	ASSERT_TRUE(prefixTrie.Find("Hello"));
	ASSERT_FALSE(prefixTrie.Find("Hell"));
	ASSERT_TRUE(prefixTrie.Find("Hell."));
	ASSERT_TRUE(prefixTrie.Find(".ello"));
	ASSERT_TRUE(prefixTrie.Find("....."));
	ASSERT_FALSE(prefixTrie.Find("...."));
	ASSERT_FALSE(prefixTrie.Find("......"));
	ASSERT_FALSE(prefixTrie.Find("Hell.."));

	prefixTrie.InsertString("Hello"); // Assert no duplicates!
	ASSERT_EQ(5, prefixTrie.Count());
	result = prefixTrie.StartsWith(string("Hel"));
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(1, result.size());
	result = prefixTrie.StartsWith(string("Hello"));
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(1, result.size());
	prefixTrie.Clear();
}