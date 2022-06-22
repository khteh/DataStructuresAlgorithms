#include "pch.h"
using namespace std;
TEST(ListPermutationTests, ListPermutationTest)
{
	set<vector<long>> permutations;
	vector<long> data{1, 2, 3};
	permutations = permute(data);
	ASSERT_EQ(6, permutations.size());
	cout << "permutations of List of {1,2,3} are:" << endl;
	for (set<vector<long>>::iterator it = permutations.begin(); it != permutations.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<long>(cout, " "));
		cout << endl;
	}
	permutations.clear();
	data.clear();
	data = {1, 2, 3, 4, 5};
	permutations = permute(data);
	ASSERT_EQ(120, permutations.size());
	cout << "permutations of List of {1,2,3, 4, 5} are:" << endl;
	for (set<vector<long>>::iterator it = permutations.begin(); it != permutations.end(); it++)
	{
		ranges::copy(*it, ostream_iterator<long>(cout, " "));
		cout << endl;
	}
	permutations.clear();
}