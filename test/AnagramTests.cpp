#include "pch.h"
using namespace std;
class AreAnagramsTestFixture : public testing::TestWithParam<tuple<bool, string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data1 = get<1>(GetParam());
		_data2 = get<2>(GetParam());
	}
	bool AreAnagramsTest()
	{
		return AreAnagrams(_data1, _data2);
	}

protected:
	bool _expected;
	string _data1, _data2;
};
TEST_P(AreAnagramsTestFixture, AreAnagramsTests)
{
	ASSERT_EQ(this->_expected, this->AreAnagramsTest());
}
INSTANTIATE_TEST_SUITE_P(
	AreAnagramsTests,
	AreAnagramsTestFixture,
	::testing::Values(make_tuple(true, "Hello World!!!", "World Hello!!!"), make_tuple(true, "Hello World!!!", "World!!! Hello"), make_tuple(true, "Hello World!!!", "!HWr ole!d!lol"), make_tuple(false, "Hello World!!!", "World Hello!!! "), make_tuple(false, "Hello World!!!", "world hello!!!"), make_tuple(false, "Hello World!!!", "Good Morning!!!")));

TEST(AnagramTests, FindAnagramsTest)
{
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
class SherlockAndAnagramsChallengeTestFixture : public testing::TestWithParam<tuple<size_t, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t SherlockAndAnagramsChallengeTest()
	{
		return SherlockAndAnagrams(_data);
	}

protected:
	size_t _expected;
	string _data;
};
TEST_P(SherlockAndAnagramsChallengeTestFixture, SherlockAndAnagramsChallengeTests)
{
	ASSERT_EQ(this->_expected, this->SherlockAndAnagramsChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
	SherlockAndAnagramsChallengeTests,
	SherlockAndAnagramsChallengeTestFixture,
	::testing::Values(make_tuple(2, "mom"), make_tuple(4, "abba"), make_tuple(0, "abcd"), make_tuple(5, "cdcd"), make_tuple(10, "kkkk"), make_tuple(3, "ifailuhkqq"), make_tuple(166650, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), make_tuple(399, "ifailuhkqqhucpoltgtyovarjsnrbfpvmupwjjjfiwwhrlkpekxxnebfrwibylcvkfealgonjkzwlyfhhkefuvgndgdnbelgruel")));
