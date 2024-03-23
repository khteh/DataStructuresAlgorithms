#include "pch.h"
using namespace std;
class FindBiggestPalindromeSubstringTestFixture : public testing::TestWithParam<tuple<string, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	string FindBiggestPalindromeSubstringTest()
	{
		return FindBiggestPalindromeSubstring(_data);
	}

protected:
	string _expected, _data;
};
TEST_P(FindBiggestPalindromeSubstringTestFixture, FindBiggestPalindromeSubstringTests)
{
	ASSERT_EQ(this->_expected, this->FindBiggestPalindromeSubstringTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindBiggestPalindromeSubstringTests,
	FindBiggestPalindromeSubstringTestFixture,
	::testing::Values(make_tuple("ABCDCBA", "AABCDCBA"),
					  make_tuple("ABCDDCBA", "AABCDDCBA"),
					  make_tuple("ABCBA", "DEFABCBAYT"),
					  make_tuple("ABCCBA", "DEFABCCBAYT")));

TEST(PalindromeTests, PalindromeTest)
{
	set<string> palindromes;
	//	assert(!IsPalindrome("aaaabbcc"));
	ASSERT_EQ(11, PalindromeAnagramCount("02002"));
	ASSERT_EQ(11, PalindromeAnagramCount1("02002"));
	FindPalindromeSubstrings("a", palindromes);
	ASSERT_TRUE(palindromes.empty());
	palindromes.clear();
	FindPalindromeSubstrings("aa", palindromes);
	ASSERT_EQ(1, palindromes.size());
	ASSERT_NE(palindromes.find("aa"), palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aaa", palindromes);
	ASSERT_EQ(2, palindromes.size());
	ASSERT_NE(palindromes.find("aa"), palindromes.end());
	ASSERT_NE(palindromes.find("aaa"), palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aba", palindromes);
	ASSERT_EQ(1, palindromes.size());
	ASSERT_NE(palindromes.find("aba"), palindromes.end());
	palindromes.clear();
	FindPalindromeSubstrings("aaazaaksforskeeggeeks", palindromes);
	ASSERT_NE(palindromes.find("skeeggeeks"), palindromes.end());
	ASSERT_NE(palindromes.find("aazaa"), palindromes.end());
}
class HighestValuePalindromeTestFixture : public testing::TestWithParam<tuple<string, string, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_k = get<2>(GetParam());
	}
	void HighestValuePalindromeTest()
	{
		HighestValuePalindrome(_data, _k);
	}

protected:
	string _expected, _data;
	size_t _k;
};
TEST_P(HighestValuePalindromeTestFixture, HighestValuePalindromeTests)
{
	this->HighestValuePalindromeTest();
	ASSERT_EQ(this->_expected, this->_data);
}
INSTANTIATE_TEST_SUITE_P(
	HighestValuePalindromeTests,
	HighestValuePalindromeTestFixture,
	::testing::Values(make_tuple("9", "1", 5),
					  make_tuple("99", "11", 5),
					  make_tuple("999", "111", 5),
					  make_tuple("9999", "1111", 5),
					  make_tuple("99999", "11111", 5),
					  make_tuple("991199", "111111", 5),
					  make_tuple("9339", "1231", 3),
					  make_tuple("3993", "3943", 1),
					  make_tuple("992299", "092282", 3),
					  make_tuple("992299", "932239", 2)));

class IsPalindromeFixture
{
public:
	void SetUp(bool expected, string data)
	{
		_expected = expected;
		_data = data;
	}

protected:
	bool _expected;
	string _data;
};

class IsPalindromeTestFixture : public IsPalindromeFixture, public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		IsPalindromeFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool IsPalindromeTest()
	{
		return IsPalindrome(_data);
	}
};
TEST_P(IsPalindromeTestFixture, IsPalindromeTests)
{
	ASSERT_EQ(this->_expected, this->IsPalindromeTest());
}
class IsPalindrome1TestFixture : public IsPalindromeFixture, public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		IsPalindromeFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool IsPalindrome1Test()
	{
		return IsPalindrome1(_data);
	}
};

TEST_P(IsPalindrome1TestFixture, IsPalindrome1Tests)
{
	ASSERT_EQ(this->_expected, this->IsPalindrome1Test());
}
class IsPalindrome2TestFixture : public IsPalindromeFixture, public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		IsPalindromeFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	// https://en.wikipedia.org/wiki/Palindrome
	bool IsPalindrome2Test()
	{
		return IsPalindrome2(_data);
	}
};

TEST_P(IsPalindrome2TestFixture, IsPalindrome2Tests)
{
	ASSERT_EQ(this->_expected, this->IsPalindrome2Test());
}

INSTANTIATE_TEST_SUITE_P(
	IsPalindromeTests,
	IsPalindromeTestFixture,
	::testing::Values(make_tuple(true, "abcdefghhgfedecba"),
					  make_tuple(false, "aabbcd"),
					  make_tuple(true, "aabbc"),
					  make_tuple(false, "xxxaabbccrry"),
					  make_tuple(true, "mmo"),
					  make_tuple(true, "yakak"),
					  make_tuple(false, "travel"),
					  make_tuple(true, "12121"),
					  make_tuple(true, "12321"),
					  make_tuple(true, "123321"),
					  make_tuple(false, "121212"),
					  make_tuple(false, "123421")));
INSTANTIATE_TEST_SUITE_P(
	IsPalindrome1Tests,
	IsPalindrome1TestFixture,
	::testing::Values(
		make_tuple(true, "mmo"),
		make_tuple(true, "yakak"),
		make_tuple(false, "travel"),
		make_tuple(true, "12121"),
		make_tuple(true, "12321"),
		make_tuple(true, "123321"),
		make_tuple(false, "121212"),
		make_tuple(false, "123421")));

// https://en.wikipedia.org/wiki/Palindrome
INSTANTIATE_TEST_SUITE_P(
	IsPalindrome2Tests,
	IsPalindrome2TestFixture,
	::testing::Values(
		make_tuple(false, "mmo"),
		make_tuple(false, "yakak"),
		make_tuple(false, "travel"),
		make_tuple(true, "12121"),
		make_tuple(true, "12321"),
		make_tuple(true, "123321"),
		make_tuple(false, "121212"),
		make_tuple(false, "123421"),
		make_tuple(true, "A man, a plan, a canal, Panama!"),
		make_tuple(true, "Amor, Roma"),
		make_tuple(true, "race car"),
		make_tuple(true, "stack cats"),
		make_tuple(true, "step on no pets"),
		make_tuple(true, "taco cat"),
		make_tuple(true, "put it up"),
		make_tuple(true, "Was it a car or a cat I saw?"),
		make_tuple(true, "No 'x' in Nixon")));
