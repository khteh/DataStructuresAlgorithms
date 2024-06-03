#include "pch.h"
using namespace std;
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

class SherlockValidStringTestFixture : public testing::TestWithParam<tuple<bool, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data1 = get<1>(GetParam());
    }
    bool SherlockValidStringTest()
    {
        return SherlockValidString(_data1);
    }

protected:
    bool _expected;
    string _data1;
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

class ParenthesesTestFixture : public testing::TestWithParam<tuple<vector<string>, size_t>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _count = get<1>(GetParam());
    }
    vector<string> ParenthesesTest()
    {
        vector<string> result;
        Parentheses(result, _count);
        return result;
    }

protected:
    vector<string> _expected;
    size_t _count;
};
TEST_P(ParenthesesTestFixture, ParenthesesTests)
{
    ASSERT_EQ(this->_expected, this->ParenthesesTest());
}
INSTANTIATE_TEST_SUITE_P(
    ParenthesesTests,
    ParenthesesTestFixture,
    ::testing::Values(make_tuple(vector<string>{"(())", "()()"}, 2), make_tuple(vector<string>{"((()))", "(()())", "(())()", "()(())", "()()()"}, 3)));

class LongestValidParenthesesTestFixture : public testing::TestWithParam<tuple<long, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
    }
    long LongestValidParenthesesTest()
    {
        return LongestValidParentheses(_data);
    }

protected:
    long _expected;
    string _data;
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

class DecryptPasswordTestFixture : public testing::TestWithParam<tuple<string, string>>
{
public:
    void SetUp() override
    {
        _expected = get<0>(GetParam());
        _data = get<1>(GetParam());
    }
    string DecryptPasswordTest()
    {
        return DecryptPassword(_data);
    }

protected:
    string _expected;
    string _data;
};
TEST_P(DecryptPasswordTestFixture, DecryptPasswordTests)
{
    ASSERT_EQ(this->_expected, this->DecryptPasswordTest());
}
INSTANTIATE_TEST_SUITE_P(
    DecryptPasswordTests,
    DecryptPasswordTestFixture,
    ::testing::Values(make_tuple("hAck3rr4nk", "43Ah*ck0rr0nk"), make_tuple("aP1pL5e", "51Pa*0Lp*0e")));
