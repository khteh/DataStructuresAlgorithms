#include "pch.h"
using namespace std;
TEST(AnagramTests, AnagramTest) {
	string str, str1;
	vector<string> strings;
	str = "Hello World!!!";
	str1 = "World Hello!!!";
	ASSERT_TRUE(areAnagrams(str, str1));
	cout << quoted(str) << " and " << quoted(str1) << " -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "World!!! Hello";
	ASSERT_TRUE(areAnagrams(str, str1));
	cout << quoted(str) << " and " << quoted(str1) << " -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "!HWr ole!d!lol";
	ASSERT_TRUE(areAnagrams(str, str1));
	cout << quoted(str) << " and " << quoted(str1) << " -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "World Hello!!! ";
	ASSERT_FALSE(areAnagrams(str, str1));
	cout << quoted(str) << " and " << quoted(str1) << " -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "world hello!!!";
	ASSERT_FALSE(areAnagrams(str, str1));
	cout << quoted(str) << " and " << quoted(str1) << " -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
	str1 = "Good Morning!!!";
	ASSERT_FALSE(areAnagrams(str, str1));
	cout << quoted(str) << " and " << quoted(str1) << " -> " << (areAnagrams(str, str1) ? "Anagram" : "Not anagram") << endl;
}
TEST(AnagramTests, FindAnagramsTest) {
	vector<string> strings;
	strings.push_back("star"); // "arst" : "star"
	strings.push_back("dog");  // "dgo" : "dog"
	strings.push_back("car");  // "acr" : "car"
	strings.push_back("rats"); // "arst" : rats
	strings.push_back("arc");  // "acr" : "arc"
	strings.push_back("god");  // "dgo" : "god"
	vector<vector<string>> anagrams;
	ASSERT_EQ(3, FindAnagrams(strings, anagrams));
	for (vector<vector<string>>::const_iterator it = anagrams.begin(); it != anagrams.end(); it++)
	{
		cout << "( ";
		ranges::copy(*it, ostream_iterator<string>(cout, " "));
		cout << "), ";
	}
}
TEST(AnagramTests, sherlockAndAnagramsChallengeTest) {
  ASSERT_EQ(2, sherlockAndAnagrams("mom"));
  ASSERT_EQ(4, sherlockAndAnagrams("abba"));
  ASSERT_EQ(0, sherlockAndAnagrams("abcd"));
  ASSERT_EQ(5, sherlockAndAnagrams("cdcd"));
  ASSERT_EQ(10, sherlockAndAnagrams("kkkk"));
  ASSERT_EQ(3, sherlockAndAnagrams("ifailuhkqq"));
  ASSERT_EQ(166650, sherlockAndAnagrams("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
  ASSERT_EQ(399, sherlockAndAnagrams("ifailuhkqqhucpoltgtyovarjsnrbfpvmupwjjjfiwwhrlkpekxxnebfrwibylcvkfealgonjkzwlyfhhkefuvgndgdnbelgruel"));
}