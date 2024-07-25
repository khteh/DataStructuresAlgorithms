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
class FindAnagramsTestFixture : public testing::TestWithParam<tuple<vector<vector<string>>, vector<string>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<vector<string>> FindAnagramsTest()
	{
		vector<vector<string>> result;
		FindAnagrams(_data, result);
		return result;
	}

protected:
	vector<vector<string>> _expected;
	vector<string> _data;
};
TEST_P(FindAnagramsTestFixture, FindAnagramsTests)
{
	ASSERT_EQ(this->_expected, this->FindAnagramsTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindAnagramsTests,
	FindAnagramsTestFixture,
	::testing::Values(make_tuple(vector<vector<string>>{{"car", "arc"}, {"star", "rats"}, {"dog", "god"}}, vector<string>{"star", "dog", "car", "rats", "arc", "god"})));
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
