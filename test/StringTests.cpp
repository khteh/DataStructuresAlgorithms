#include "pch.h"
using namespace std;
template <typename T1, typename T2>
class StringTestFixture
{
public:
    void SetUp(T1 expected, T2 var1)
    {
        _expected = expected;
        _var1 = var1;
    }

protected:
    T1 _expected;
    T2 _var1;
};

class PhoneKeyLettersTestFixture : public StringTestFixture<vector<string>, string>, public testing::TestWithParam<tuple<vector<string>, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    vector<string> PhoneKeyLettersTest()
    {
        vector<string> result;
        PhoneKeyLetters(_var1, result);
        return result;
    }
};
TEST_P(PhoneKeyLettersTestFixture, PhoneKeyLettersTests)
{
    ASSERT_EQ(this->_expected, this->PhoneKeyLettersTest());
}
INSTANTIATE_TEST_SUITE_P(
    PhoneKeyLettersTests,
    PhoneKeyLettersTestFixture,
    ::testing::Values(make_tuple(vector<string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}, "23"), make_tuple(vector<string>(), ""), make_tuple(vector<string>{"a", "b", "c"}, "2"), make_tuple(vector<string>{"djt", "dkt", "dlt", "ejt", "ekt", "elt", "fjt", "fkt", "flt", "dju", "dku", "dlu", "eju", "eku", "elu", "fju", "fku", "flu", "djv", "dkv", "dlv", "ejv", "ekv", "elv", "fjv", "fkv", "flv"}, "358")));
class BasicCalculatorTestFixture : public StringTestFixture<long, string>, public testing::TestWithParam<tuple<long, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long BasicCalculatorTest()
    {
        return BasicCalculator(_var1);
    }
};
TEST_P(BasicCalculatorTestFixture, BasicCalculatorTests)
{
    ASSERT_EQ(this->_expected, this->BasicCalculatorTest());
}
INSTANTIATE_TEST_SUITE_P(
    BasicCalculatorTests,
    BasicCalculatorTestFixture,
    ::testing::Values(make_tuple(6, "3+2*2-1"), make_tuple(5, "3+2"), make_tuple(7, "10-3"), make_tuple(8, "3*2+2"), make_tuple(-15, "3+2-4*5"), make_tuple(7, "3*2+5/4")));
class TwentyFourHourTimeConversionTestFixture : public StringTestFixture<string, string>, public testing::TestWithParam<tuple<string, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    string TwentyFourHourTimeConversionTest()
    {
        return TwentyFourHourTimeConversion(_var1);
    }
};
TEST_P(TwentyFourHourTimeConversionTestFixture, TwentyFourHourTimeConversionTests)
{
    ASSERT_EQ(this->_expected, this->TwentyFourHourTimeConversionTest());
}
INSTANTIATE_TEST_SUITE_P(
    TwentyFourHourTimeConversionTests,
    TwentyFourHourTimeConversionTestFixture,
    ::testing::Values(make_tuple("19:05:45", "07:05:45PM"), make_tuple("07:05:45", "07:05:45AM"), make_tuple("23:59:30", "11:59:30PM")));
class MorganAndStringTestFixture : public testing::TestWithParam<tuple<string, string, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data1 = get<1>(GetParam());
        _data2 = get<2>(GetParam());
    }
    string MorganAndStringTest()
    {
        return MorganAndString(_data1, _data2);
    }

protected:
    string _expected;
    string _data1, _data2;
};
TEST_P(MorganAndStringTestFixture, MorganAndStringTests)
{
    ASSERT_EQ(this->_expected, this->MorganAndStringTest());
}
INSTANTIATE_TEST_SUITE_P(
    MorganAndStringTests,
    MorganAndStringTestFixture,
    ::testing::Values(make_tuple("ABCACF", "ACA", "BCF"), make_tuple("BABB", "BB", "BA"), make_tuple("BABC", "BA", "BC"), make_tuple("BAB", "BA", "B"), make_tuple("BAB", "B", "BA"), make_tuple("BBC", "BC", "B"), make_tuple("BBC", "B", "BC"), make_tuple("CABCAB", "CAB", "CAB"), make_tuple("DAJACKNIEL", "JACK", "DANIEL"), make_tuple("AABABACABACABA", "ABACABA", "ABACABA")));

class SherlockValidStringTestFixture : public StringTestFixture<bool, string>, public testing::TestWithParam<tuple<bool, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    bool SherlockValidStringTest()
    {
        return SherlockValidString(_var1);
    }
};
TEST_P(SherlockValidStringTestFixture, SherlockValidStringTests)
{
    ASSERT_EQ(this->_expected, this->SherlockValidStringTest());
}
INSTANTIATE_TEST_SUITE_P(
    SherlockValidStringTests,
    SherlockValidStringTestFixture,
    ::testing::Values(make_tuple(true, "abcdefghhgfedecba"), make_tuple(false, "aabbcd"), make_tuple(false, "aaaabbcc"), make_tuple(false, "xxxaabbccrry"), make_tuple(true, "ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd")));

class AreRotatedStringsTestFixture : public testing::TestWithParam<tuple<bool, size_t, string, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _offset = get<1>(GetParam());
        _data1 = get<2>(GetParam());
        _data2 = get<3>(GetParam());
    }
    bool AreRotatedStringsTest()
    {
        return AreRotatedStrings(_data1, _data2, _offset);
    }

protected:
    bool _expected;
    size_t _offset;
    string _data1, _data2;
};
TEST_P(AreRotatedStringsTestFixture, AreRotatedStringsTests)
{
    ASSERT_EQ(this->_expected, this->AreRotatedStringsTest());
}
INSTANTIATE_TEST_SUITE_P(
    AreRotatedStringsTests,
    AreRotatedStringsTestFixture,
    ::testing::Values(make_tuple(true, 2, "Hello World !!!", "llo World !!!He")));

class ParenthesesTestFixture : public StringTestFixture<vector<string>, size_t>, public testing::TestWithParam<tuple<vector<string>, size_t>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    vector<string> ParenthesesTest()
    {
        vector<string> result;
        Parentheses(result, _var1);
        return result;
    }
};
TEST_P(ParenthesesTestFixture, ParenthesesTests)
{
    ASSERT_EQ(this->_expected, this->ParenthesesTest());
}
INSTANTIATE_TEST_SUITE_P(
    ParenthesesTests,
    ParenthesesTestFixture,
    ::testing::Values(make_tuple(vector<string>{"(())", "()()"}, 2), make_tuple(vector<string>{"((()))", "(()())", "(())()", "()(())", "()()()"}, 3)));

class LongestValidParenthesesTestFixture : public StringTestFixture<long, string>, public testing::TestWithParam<tuple<long, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long LongestValidParenthesesTest()
    {
        return LongestValidParentheses(_var1);
    }
};
TEST_P(LongestValidParenthesesTestFixture, LongestValidParenthesesTests)
{
    ASSERT_EQ(this->_expected, this->LongestValidParenthesesTest());
}
INSTANTIATE_TEST_SUITE_P(
    LongestValidParenthesesTests,
    LongestValidParenthesesTestFixture,
    ::testing::Values(make_tuple(0, "("), make_tuple(2, "((()"), make_tuple(2, "())()"), make_tuple(2, "()(()"), make_tuple(4, ")()())"), make_tuple(6, "()(()))))"), make_tuple(0, ")))((("), make_tuple(4, ")()()(((()"), make_tuple(2, "))()(()(()"), make_tuple(6, ")())((()))"), make_tuple(8, "(()))))(()((()))")));

class CipherChallengeTestFixture : public testing::TestWithParam<tuple<string, size_t, size_t, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _n = get<1>(GetParam());
        _k = get<2>(GetParam());
        _data = get<3>(GetParam());
    }
    string CipherChallengeTest()
    {
        return Cipher(_n, _k, _data);
    }

protected:
    string _expected;
    size_t _n, _k;
    string _data;
};
TEST_P(CipherChallengeTestFixture, CipherChallengeTests)
{
    ASSERT_EQ(this->_expected, this->CipherChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
    CipherChallengeTests,
    CipherChallengeTestFixture,
    ::testing::Values(make_tuple("1001011", 7, 4, "1110101001"), make_tuple("1010", 4, 5, "11000110")));

class DecryptPasswordTestFixture : public StringTestFixture<string, string>, public testing::TestWithParam<tuple<string, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    string DecryptPasswordTest()
    {
        return DecryptPassword(_var1);
    }
};
TEST_P(DecryptPasswordTestFixture, DecryptPasswordTests)
{
    ASSERT_EQ(this->_expected, this->DecryptPasswordTest());
}
INSTANTIATE_TEST_SUITE_P(
    DecryptPasswordTests,
    DecryptPasswordTestFixture,
    ::testing::Values(make_tuple("hAck3rr4nk", "43Ah*ck0rr0nk"), make_tuple("aP1pL5e", "51Pa*0Lp*0e")));
class LengthOfLongestUniqueSubstringTestFixture : public StringTestFixture<size_t, string>, public testing::TestWithParam<tuple<size_t, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    size_t LengthOfLongestUniqueSubstringTest()
    {
        return LengthOfLongestUniqueSubstring(_var1);
    }
};
TEST_P(LengthOfLongestUniqueSubstringTestFixture, LengthOfLongestUniqueSubstringTests)
{
    ASSERT_EQ(this->_expected, this->LengthOfLongestUniqueSubstringTest());
}
INSTANTIATE_TEST_SUITE_P(
    LengthOfLongestUniqueSubstringTests,
    LengthOfLongestUniqueSubstringTestFixture,
    ::testing::Values(make_tuple(3, "abcabc"), make_tuple(1, "aaa"), make_tuple(6, "abcdef"), make_tuple(3, "dvdf"), make_tuple(3, "abcabcbb"), make_tuple(5, "tmmzuxt"), make_tuple(3, "pwwkew"), make_tuple(6, "ohvhjdml"), make_tuple(4, "vqblqcb")));

class ZigZagConvertTestFixture : public testing::TestWithParam<tuple<string, string, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
        _numRows = get<2>(GetParam());
    }
    string ZigZagConvertTest()
    {
        return ZigZagConvert(_data, _numRows);
    }

protected:
    string _expected;
    string _data;
    size_t _numRows;
};
TEST_P(ZigZagConvertTestFixture, ZigZagConvertTests)
{
    ASSERT_EQ(this->_expected, this->ZigZagConvertTest());
}
INSTANTIATE_TEST_SUITE_P(
    ZigZagConvertTests,
    ZigZagConvertTestFixture,
    ::testing::Values(make_tuple("PAHNAPLSIIGYIR", "PAYPALISHIRING", 3), make_tuple("AB", "AB", 1)));

class WordBreakDFSFixture : public testing::TestWithParam<tuple<vector<string>, string, set<string>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _str1 = get<1>(GetParam());
        _strs = get<2>(GetParam());
    }
    vector<string> WordBreakDFSTest()
    {
        return WordBreakDFS(_str1, _strs);
    }

protected:
    string _str1;
    set<string> _strs;
    vector<string> _expected;
};
TEST_P(WordBreakDFSFixture, WordBreakDFSTests)
{
    ASSERT_EQ(this->_expected, this->WordBreakDFSTest());
}
INSTANTIATE_TEST_SUITE_P(
    WordBreakDFSTests,
    WordBreakDFSFixture,
    ::testing::Values(make_tuple(vector<string>{"Hello World"}, "HelloWorld", set<string>{"Hello", "World"}),
                      make_tuple(vector<string>{}, "catsandog", set<string>{"cats", "dog", "sand", "and", "cat"}),
                      make_tuple(vector<string>{"cat sand dog", "cats and dog"}, "catsanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
                      make_tuple(vector<string>{"cat and dog"}, "catanddog", set<string>{"cats", "dog", "sand", "and", "cat"}),
                      make_tuple(vector<string>{"apple pen apple"}, "applepenapple", set<string>{"apple", "pen"}),
                      make_tuple(vector<string>{"aaa aaaa", "aaaa aaa"}, "aaaaaaa", set<string>{"aaaa", "aaa"})));

class HappyLadyBugsChallengeTestFixture : public StringTestFixture<bool, string>, public testing::TestWithParam<tuple<bool, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    bool HappyLadyBugsChallengeTest()
    {
        return HappyLadyBugs(_var1);
    }
};
TEST_P(HappyLadyBugsChallengeTestFixture, HappyLadyBugsChallengeTests)
{
    ASSERT_EQ(this->_expected, this->HappyLadyBugsChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
    HappyLadyBugsChallengeTests,
    HappyLadyBugsChallengeTestFixture,
    ::testing::Values(make_tuple(true, "_"), make_tuple(false, "RBRB"), make_tuple(true, "aaaa"), make_tuple(true, "aaa"), make_tuple(true, "aa"), make_tuple(false, "a"), make_tuple(true, "aa_")));
class GetHintChallengeTestFixture : public testing::TestWithParam<tuple<string, string, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _secret = get<1>(GetParam());
        _guess = get<2>(GetParam());
    }
    string GetHintChallengeTest()
    {
        return GetHint(_secret, _guess);
    }

protected:
    string _expected, _secret, _guess;
};
TEST_P(GetHintChallengeTestFixture, GetHintChallengeTests)
{
    ASSERT_EQ(this->_expected, this->GetHintChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
    GetHintChallengeTests,
    GetHintChallengeTestFixture,
    ::testing::Values(make_tuple("2A2B", "6244988279", "3819888600"), make_tuple("1A3B", "1807", "7810"), make_tuple("1A1B", "1123", "0111")));
class SteadyGeneChallengeTestFixture : public StringTestFixture<long, string>, public testing::TestWithParam<tuple<long, string>>
{
public:
    void SetUp() override
    {
        StringTestFixture::SetUp(get<0>(GetParam()), get<1>(GetParam()));
    }
    long SteadyGeneChallengeTest()
    {
        return SteadyGene(_var1);
    }
};
TEST_P(SteadyGeneChallengeTestFixture, SteadyGeneChallengeTests)
{
    ASSERT_EQ(this->_expected, this->SteadyGeneChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
    SteadyGeneChallengeTests,
    SteadyGeneChallengeTestFixture,
    ::testing::Values(make_tuple(1, "ACGTCCGT"), make_tuple(0, "AAGTGCCT"), make_tuple(2, "ACTGAAAG")));
class WordsLadderTestFixture : public testing::TestWithParam<tuple<vector<string>, string, string, set<string>>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _start = get<1>(GetParam());
        _finish = get<2>(GetParam());
        _dictionary = get<3>(GetParam());
    }
    vector<string> WordsLadderTest()
    {
        vector<string> result;
        WordsLadder(_start, _finish, _dictionary, result);
        return result;
    }

protected:
    vector<string> _expected;
    string _start, _finish;
    set<string> _dictionary;
};
TEST_P(WordsLadderTestFixture, WordsLadderTests)
{
    ASSERT_EQ(this->_expected, this->WordsLadderTest());
}
INSTANTIATE_TEST_SUITE_P(
    WordsLadderTests,
    WordsLadderTestFixture,
    ::testing::Values(make_tuple(vector<string>{"LIKE", "LIME", "LIMP", "LAMP", "DAMP"}, "DAMP", "LIKE", set<string>{"DAMP", "LAMP", "LIMP", "LIME", "LIKE", "LAKE"}), make_tuple(vector<string>{}, "DAMP", "Like", set<string>{"DAMP", "LAMP", "LIMP", "LIME", "LIKE", "LAKE"}), make_tuple(vector<string>{"Cog", "Dog", "Dot", "Hot", "Hit"}, "Hit", "Cog", set<string>{"Hot", "Dot", "Dog", "Lot", "Log", "Cog"}), make_tuple(vector<string>{}, "Hit", "Hat", set<string>{"Hot", "Dot", "Dog", "Lot", "Log", "Cog"})));
