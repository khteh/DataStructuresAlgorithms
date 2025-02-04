#include "pch.h"
using namespace std;
template <typename T>
class PalindromeTestFixture
{
public:
	void SetUp(T expected, string data)
	{
		_expected = expected;
		_data = data;
	}

protected:
	Palindrome _palindrome;
	T _expected;
	string _data;
};

class FindBiggestPalindromeSubstringTestFixture : public PalindromeTestFixture<string>, public testing::TestWithParam<tuple<string, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	string FindBiggestPalindromeSubstringTest()
	{
		return _palindrome.FindBiggestPalindromeSubstring(_data);
	}
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

class PalindromeAnagramCountTestFixture : public PalindromeTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t PalindromeAnagramCountTest()
	{
		return _palindrome.PalindromeAnagramCount(_data);
	}
};
TEST_P(PalindromeAnagramCountTestFixture, PalindromeAnagramCountTests)
{
	ASSERT_EQ(this->_expected, this->PalindromeAnagramCountTest());
}
INSTANTIATE_TEST_SUITE_P(
	PalindromeAnagramCountTests,
	PalindromeAnagramCountTestFixture,
	::testing::Values(make_tuple(11, "02002")));
class PalindromeAnagramCount1TestFixture : public PalindromeTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t PalindromeAnagramCount1Test()
	{
		return _palindrome.PalindromeAnagramCount1(_data);
	}
};
TEST_P(PalindromeAnagramCount1TestFixture, PalindromeAnagramCount1Tests)
{
	ASSERT_EQ(this->_expected, this->PalindromeAnagramCount1Test());
}
INSTANTIATE_TEST_SUITE_P(
	PalindromeAnagramCount1Tests,
	PalindromeAnagramCount1TestFixture,
	::testing::Values(make_tuple(11, "02002")));

class FindPalindromeSubstringsTestFixture : public PalindromeTestFixture<set<string>>, public testing::TestWithParam<tuple<set<string>, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	set<string> FindPalindromeSubstringsTest()
	{
		set<string> result;
		_palindrome.FindPalindromeSubstrings(_data, result);
		return result;
	}
};
TEST_P(FindPalindromeSubstringsTestFixture, FindPalindromeSubstringsTests)
{
	ASSERT_EQ(this->_expected, this->FindPalindromeSubstringsTest());
}
INSTANTIATE_TEST_SUITE_P(
	FindPalindromeSubstringsTests,
	FindPalindromeSubstringsTestFixture,
	::testing::Values(make_tuple(set<string>{}, "a"), make_tuple(set<string>{"aa"}, "aa"), make_tuple(set<string>{"aa", "aaa"}, "aaa"), make_tuple(set<string>{"aba"}, "aba"), make_tuple(set<string>{"aa", "aaa", "aazaa", "aza", "ee", "eeggee", "egge", "gg", "keeggeek", "skeeggeeks"}, "aaazaaksforskeeggeeks")));

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
		_palindrome.HighestValuePalindrome(_data, _k);
	}

protected:
	Palindrome _palindrome;
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

class IsPalindromeTestFixture : public PalindromeTestFixture<bool>, public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool IsPalindromeTest()
	{
		return _palindrome.IsPalindrome(_data);
	}
};
TEST_P(IsPalindromeTestFixture, IsPalindromeTests)
{
	ASSERT_EQ(this->_expected, this->IsPalindromeTest());
}
class IsPalindrome1TestFixture : public PalindromeTestFixture<bool>, public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	bool IsPalindrome1Test()
	{
		return _palindrome.IsPalindrome1(_data);
	}
};

TEST_P(IsPalindrome1TestFixture, IsPalindrome1Tests)
{
	ASSERT_EQ(this->_expected, this->IsPalindrome1Test());
}
class IsPalindrome2TestFixture : public PalindromeTestFixture<bool>, public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	// https://en.wikipedia.org/wiki/Palindrome
	bool IsPalindrome2Test()
	{
		return _palindrome.IsPalindrome2(_data);
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
class ShortPalindromeTestFixture : public PalindromeTestFixture<size_t>, public testing::TestWithParam<tuple<size_t, string>>
{
public:
	void SetUp() override
	{
		PalindromeTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t ShortPalindromeTest()
	{
		return _palindrome.ShortPalindrome(_data);
	}
};

TEST_P(ShortPalindromeTestFixture, ShortPalindromeTests)
{
	ASSERT_EQ(this->_expected, this->ShortPalindromeTest());
}

INSTANTIATE_TEST_SUITE_P(
	ShortPalindromeTests,
	ShortPalindromeTestFixture,
	::testing::Values(make_tuple(15, "kkkkkkz"),
					  make_tuple(4, "ghhggh"),
					  make_tuple(4, "abbaab"),
					  make_tuple(2, "akakak"),
					  make_tuple(242745, "cbbdcacccdaddbaabbaacbacacaaddaaacdbccccccbbadbbcdddddddaccbdbddcbacaaadbbdcbcbcdabdddbbcdccaacdccab")));
class MaxSizePalindromeCountTestFixture : public testing::TestWithParam<tuple<long, string, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_l = get<2>(GetParam());
		_r = get<3>(GetParam());
	}
	long double MaxSizePalindromeCountTest()
	{
		return _palindrome.MaxSizePalindromeCount(_data, _l, _r);
	}

protected:
	Palindrome _palindrome;
	string _data;
	long _expected;
	size_t _l, _r;
};
TEST_P(MaxSizePalindromeCountTestFixture, MaxSizePalindromeCountTests)
{
	ASSERT_EQ(this->_expected, this->MaxSizePalindromeCountTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxSizePalindromeCountTests,
	MaxSizePalindromeCountTestFixture,
	::testing::Values(make_tuple(2, "week", 0, 3),
					  make_tuple(1, "week", 1, 2),
					  make_tuple(2, "abab", 0, 3),
					  make_tuple(1, "wuhmbspjnfviogqzldrcxtaeyk", 20, 20),
					  make_tuple(2, "wuhmbspjnfviogqzldrcxtaeyk", 3, 4),
					  make_tuple(2, "daadabbadcabacbcccbdcccdbcccbbaadcbabbdaaaabbbdabdbbdcadaaacaadadacddabbbbbdcccbaabbbacacddbbbcbbdbd", 13, 16),
					  make_tuple(8, "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz", 30, 37),
					  make_tuple(3, "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz", 28, 32),
					  make_tuple(60480, "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz", 12, 33),
					  make_tuple(1995840, "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz", 1, 29),
					  make_tuple(740299127, "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz", 2, 40),
					  make_tuple(556755193, "wldsfubcsxrryqpqyqqxrlffumtuwymbybnpemdiwyqz", 5, 41),
					  make_tuple(1, "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", 0, 0),
					  make_tuple(1, "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", 0, 1),
					  make_tuple(1, "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", 0, 2),
					  make_tuple(249346542, "cstniwwvbkyrxzvjpegpgtwwxkdujwbmsqrmkurdprzfftazyonxmawydyjgmipyassxnafluvaouoiuxrqrbrjmzisptfhqqaxq", 4, 99),
					  make_tuple(922261429, "cstniwwvbkyrxzvjpegpgtwwxkdujwbmsqrmkurdprzfftazyonxmawydyjgmipyassxnafluvaouoiuxrqrbrjmzisptfhqqaxq", 19, 81)));
