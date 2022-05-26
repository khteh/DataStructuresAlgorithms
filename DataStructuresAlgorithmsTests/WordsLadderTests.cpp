#include "pch.h"
using namespace std;
TEST(WordsLadderTests, WordsLadderTest)
{
	vector<string> strings, expected;
	// Test single-character string permutations
	set<string> dictionary = {"DAMP", "LAMP", "LIMP", "LIME", "LIKE", "LAKE"};
	expected = {"LIKE", "LIME", "LIMP", "LAMP", "DAMP"};
	strings.clear();
	WordsLadder(string("DAMP"), string("LIKE"), dictionary, strings);
	ASSERT_TRUE(!strings.empty());
	cout << "Single-character transformation from \"DAMP\" to \"LIKE\": ";
	// DAMP LAMP LIMP LIME LIKE
	ASSERT_EQ(5, strings.size());
	ASSERT_EQ(expected, strings);
	ranges::reverse_copy(strings, ostream_iterator<string>(cout, " "));
	cout << endl;
	strings.clear();
	expected.clear();
	WordsLadder(string("DAMP"), string("Like"), dictionary, strings);
	ASSERT_TRUE(strings.empty()); // "LICK" is not in the dictionary
	ASSERT_EQ(expected, strings);
	dictionary.clear();
	strings.clear();
	expected.clear();
	dictionary = {"Hot", "Dot", "Dog", "Lot", "Log", "Cog"};
	expected = {"Cog", "Dog", "Dot", "Hot", "Hit"};
	WordsLadder(string("Hit"), string("Cog"), dictionary, strings);
	ASSERT_TRUE(!strings.empty());
	ASSERT_EQ(5, strings.size());
	ASSERT_EQ(expected, strings);
	cout << "Single-character transformation from \"Hit\" to \"Cog\": ";
	ranges::reverse_copy(strings, ostream_iterator<string>(cout, " "));
	cout << endl;
	strings.clear();
	expected.clear();
	WordsLadder(string("Hit"), string("Hat"), dictionary, strings);
	ASSERT_TRUE(strings.empty()); // "HAT" is not in the dictionary
	ASSERT_EQ(expected, strings);
}