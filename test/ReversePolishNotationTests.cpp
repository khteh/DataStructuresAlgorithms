#include "pch.h"
using namespace std;
TEST(ReversePolishNotationTests, ReversePolishNotationTest)
{
	vector<string> strings;
	strings = { "2", "1", "+", "3", "*" };
	ASSERT_EQ(9, ReversePolishNotation(strings));
	strings.clear();
	strings = { "4", "13", "5", "/", "+" };
	ASSERT_EQ(6, ReversePolishNotation(strings));
	strings.clear();
	strings = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
	ASSERT_EQ(22, ReversePolishNotation(strings));
}