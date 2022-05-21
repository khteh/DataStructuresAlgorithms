#include "pch.h"
using namespace std;
TEST(StringPermutationTests, StringPermutationTest) {
	set<string> permutations;
	permutations = permute("abc");
	ASSERT_EQ(6, permutations.size());
	ASSERT_NE(permutations.find("abc"), permutations.end());
	ASSERT_NE(permutations.find("bac"), permutations.end());
	ASSERT_NE(permutations.find("bca"), permutations.end());
	ASSERT_NE(permutations.find("acb"), permutations.end());
	ASSERT_NE(permutations.find("cba"), permutations.end());
	ASSERT_NE(permutations.find("cab"), permutations.end());
	cout << "permutations of \"abc\" are: ";
	copy(permutations.begin(), permutations.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	permutations.clear();

	OrderedMergedCombinations(permutations, string("Hey"), string("Bob"), string(""));
	cout << "Ordered permutations of \"HeyBob\" are: ";
	copy(permutations.begin(), permutations.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	ASSERT_EQ(20, permutations.size());
	ASSERT_NE(permutations.find("HeBoby"), permutations.end());
	ASSERT_NE(permutations.find("HeBoyb"), permutations.end());
	ASSERT_NE(permutations.find("HeByob"), permutations.end());
	ASSERT_NE(permutations.find("HeyBob"), permutations.end());
	ASSERT_NE(permutations.find("HBoeby"), permutations.end());
	ASSERT_NE(permutations.find("HBoeyb"), permutations.end());
	ASSERT_NE(permutations.find("HBobey"), permutations.end());
	ASSERT_NE(permutations.find("HBeoby"), permutations.end());
	ASSERT_NE(permutations.find("HBeoyb"), permutations.end());
	ASSERT_NE(permutations.find("HBeyob"), permutations.end());
	ASSERT_NE(permutations.find("BoHeby"), permutations.end());
	ASSERT_NE(permutations.find("BoHeyb"), permutations.end());
	ASSERT_NE(permutations.find("BoHbey"), permutations.end());
	ASSERT_NE(permutations.find("BobHey"), permutations.end());
	ASSERT_NE(permutations.find("BHoeby"), permutations.end());
	ASSERT_NE(permutations.find("BHoeyb"), permutations.end());
	ASSERT_NE(permutations.find("BHobey"), permutations.end());
	ASSERT_NE(permutations.find("BHeoby"), permutations.end());
	ASSERT_NE(permutations.find("BHeoyb"), permutations.end());
	ASSERT_NE(permutations.find("BHeyob"), permutations.end());
}