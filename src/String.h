#pragma once
#include "MyStack.h"
#include "Permutation.h"
typedef struct BuildLargestNumber_comparator
{
    bool operator()(string lhs, string rhs) const
    {
        ostringstream oss1, oss2;
        oss1 << lhs << rhs;
        oss2 << rhs << lhs;
        // True: lhs goes before rhs; False: lhs goes after rhs
        // lhsrhs < rhslhs : lhs goes after rhs
        // lhsrhs > rhslhs : lhs goes before rhs
        return oss1.str() > oss2.str();
    }
} BuildLargestNumber_comparator_t;

typedef struct LongestMatchingWordWithDeletionState
{
    size_t index; // The number refers to the number of characters in w that have already been found in input string.
    string word;
    LongestMatchingWordWithDeletionState(size_t i, string const &w) : index(i), word(w) {}
    bool operator<(const LongestMatchingWordWithDeletionState &other) const
    {
        return word < other.word;
    }
    bool operator>(const LongestMatchingWordWithDeletionState &other) const
    {
        return word > other.word;
    }
} longestmatchingwordwithdeletion_state_t;

class String
{
private:
    void _Parentheses(vector<string> &, string &, size_t, long, long);
    vector<string> _WordBreakDFS(string const &, set<string> const &, map<string, vector<string>> &);

public:
    void Parentheses(vector<string> &, size_t);
    void PhoneKeyLetters(string const &, vector<string> &);
    void RemoveDuplicateCharacters(string &);
    void RemoveDuplicateCharactersLexicographicalOrder(string &);
    void WordsLadder(string const &, string const &, set<string> &, vector<string> &);
    void Z(vector<size_t> &, string const &);
    bool SherlockValidString(string const &);
    bool AreRotatedStrings(string const &, string const &, size_t);
    bool IsValidParentheses(string const &);
    bool HappyLadyBugs(string const &);
    long BasicCalculator(string const &);
    long LongestValidParentheses(string const &);
    size_t AlternateChars(string const &);
    size_t LengthOfLongestSubstring(string const &);
    size_t LengthOfLongestUniqueSubstring(string const &);
    size_t LongestStringWithCharacterReplacement(string const &, size_t);
    size_t SteadyGene(string const &);
    size_t MaxProductOfNonOverlappingWordLengths(vector<string> const &);
    string BuildLargestNumber(vector<size_t> const &);
    string Cipher(size_t, size_t, string const &);
    string DecryptPassword(string const &);
    string DecodeString(string const &);
    string GetHint(string const &, string const &);
    string MorganAndString(string const &, string const &);
    string NextBiggerString(string &);
    string TwentyFourHourTimeConversion(string const &);
    string ZigZagConvert(string const &, size_t);
    string LongestMatchingWordWithDeletion(string const &, set<string> const &);
    string SuperReducedString(string const &);
    string LongestCommonPrefix(vector<string> const &);
    vector<string> WordBreakDFS(string const &, set<string> const &);
    vector<bool> WeightedUniformStrings(string const &, vector<size_t> const &);
};