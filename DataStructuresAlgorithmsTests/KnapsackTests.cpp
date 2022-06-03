#include "pch.h"
using namespace std;
TEST(KnapsackTests, CoinChangeTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 3, 2, 1 };
	set<vector<size_t>> combinations = knapsack.CoinChange(0, numbers);
	ASSERT_TRUE(combinations.empty());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinChange(1, numbers);
	ASSERT_EQ(1, combinations.size());
	set<vector<size_t>>::iterator it = combinations.begin();
	ASSERT_EQ(1, it->size());
	ASSERT_EQ(1, (*it)[0]);
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinChange(2, numbers);
	ASSERT_EQ(2, combinations.size());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinChange(3, numbers);
	ASSERT_EQ(3, combinations.size());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinChange(4, numbers);
	ASSERT_EQ(4, combinations.size());
	numbers.clear();
	numbers = {6, 5, 3, 2};
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinChange(10, numbers);
	ASSERT_EQ(5, combinations.size());
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
	combinations = knapsack.CoinChange(10, numbers);
	ASSERT_EQ(5, combinations.size());
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = {1, 50};
	combinations = knapsack.CoinChange(200, numbers);
	ASSERT_EQ(5, combinations.size());
	knapsack.ClearCoinChangeCache();
	// combinations1 = knapsack.CoinsChangeDynamicProgramming(166, numbers); Times out!
	// assert(!combinations1.empty());
	// combinations = knapsack.CoinChange(166, numbers); //Times out!
	// assert(combinations.size() == 96190959);
	numbers.clear();
	numbers = {3, 7, 405, 436};
	knapsack.ClearCoinChangeCache();
	//combinations = knapsack.CoinsChangeDynamicProgramming(8839, numbers); // Stack overflow! using recursive knapsack.CoinChange()
	//ASSERT_FALSE(combinations.empty());
}
TEST(KnapsackTests, CoinChangeDynamicProgrammingTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 3, 2, 1 };
	set<vector<size_t>> combinations = knapsack.CoinsChangeDynamicProgramming(0, numbers);
	ASSERT_TRUE(combinations.empty());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinsChangeDynamicProgramming(-1, numbers);
	ASSERT_TRUE(combinations.empty());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinsChangeDynamicProgramming(1, numbers);
	ASSERT_EQ(1, combinations.size());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinsChangeDynamicProgramming(2, numbers);
	ASSERT_EQ(2, combinations.size());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinsChangeDynamicProgramming(3, numbers);
	ASSERT_EQ(3, combinations.size());
	knapsack.ClearCoinChangeCache();
	combinations = knapsack.CoinsChangeDynamicProgramming(4, numbers);
	ASSERT_EQ(4, combinations.size());
	combinations = knapsack.CoinsChangeDynamicProgramming(10, numbers);
	ASSERT_FALSE(combinations.empty());
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = { 6, 5, 3, 2 };
	combinations = knapsack.CoinsChangeDynamicProgramming(10, numbers);
	ASSERT_EQ(5, combinations.size());
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	combinations = knapsack.CoinsChangeDynamicProgramming(10, numbers);
	ASSERT_EQ(5, combinations.size());
	numbers.clear();
	numbers = { 1, 50 };
	combinations = knapsack.CoinsChangeDynamicProgramming(200, numbers);
	ASSERT_EQ(5, combinations.size());
}
TEST(KnapsackTests, CoinsChangeUniqueWaysDynamicProgrammingTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 3, 2, 1 };
	set<vector<size_t>> combinations;
	ASSERT_EQ(0, knapsack.CoinsChangeUniqueWaysDynamicProgramming(0, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(1, knapsack.CoinsChangeUniqueWaysDynamicProgramming(1, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(2, knapsack.CoinsChangeUniqueWaysDynamicProgramming(2, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(3, knapsack.CoinsChangeUniqueWaysDynamicProgramming(3, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(4, knapsack.CoinsChangeUniqueWaysDynamicProgramming(4, numbers));
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = { 6, 5, 3, 2 };
	ASSERT_EQ(5, knapsack.CoinsChangeUniqueWaysDynamicProgramming(10, numbers));
	numbers.clear();
	numbers = { 2, 3, 5 };
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(2, knapsack.CoinsChangeUniqueWaysDynamicProgramming(5, numbers));	// {{2,3}, {5}}
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(2, knapsack.CoinsChangeUniqueWaysDynamicProgramming(6, numbers));	// {{2,2,2}, {3,3}}
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = { 5, 37, 8, 39, 33, 17, 22, 32, 13, 7, 10, 35, 40, 2, 43, 49, 46, 19, 41, 1, 12, 11, 28 };
	ranges::sort(numbers);
	ASSERT_EQ(96190959, knapsack.CoinsChangeUniqueWaysDynamicProgramming(166, numbers));
	knapsack.ClearCoinChangeCache();
}
TEST(KnapsackTests, CoinsChangeDuplicateWaysDynamicProgrammingTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 3, 2, 1 };
	ASSERT_EQ(0, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(0, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(1, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(1, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(2, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(2, numbers));
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(4, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(3, numbers)); // {3},{1,2},{2,1},{1,1,1}
	knapsack.ClearCoinChangeCache();
	ASSERT_EQ(7, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(4, numbers)); // {3,1},{3,1},{1,1,2},{1,2,1},{2,1,1},{2,2},{1,1,1,1}
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = { 6, 5, 3, 2 };
	ASSERT_EQ(17, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(10, numbers));
	knapsack.ClearCoinChangeCache();
	numbers.clear();
	numbers = { 2, 3, 5 };
	ASSERT_EQ(3, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(5, numbers)); //{2,3},{3,2},{5}
	ASSERT_EQ(2, knapsack.CoinsChangeDuplicateWaysDynamicProgramming(6, numbers)); //
}
TEST(KnapsackTests, CoinsChangeFewestCoinsDynamicProgrammingTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 1, 2, 5 };
	ASSERT_EQ(3, knapsack.CoinsChangeFewestCoinsDynamicProgramming(11, numbers));
	ASSERT_EQ(2, knapsack.CoinsChangeFewestCoinsDynamicProgramming(10, numbers));
	numbers.clear();
	numbers = { 2 };
	ASSERT_EQ(-1, knapsack.CoinsChangeFewestCoinsDynamicProgramming(3, numbers));
	numbers.clear();
	numbers = { 1 };
	ASSERT_EQ(0, knapsack.CoinsChangeFewestCoinsDynamicProgramming(0, numbers));
	ASSERT_EQ(1, knapsack.CoinsChangeFewestCoinsDynamicProgramming(1, numbers));
	ASSERT_EQ(2, knapsack.CoinsChangeFewestCoinsDynamicProgramming(2, numbers));
}
TEST(KnapsackTests, StairsClimbingDynamicProgrammingTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 1, 2 };
	ASSERT_EQ(13, knapsack.StairsClimbingDynamicProgramming(6, numbers));
	numbers.clear();
	numbers = { 1, 2, 3 };
	knapsack.ClearDPMemoization();
	ASSERT_EQ(24, knapsack.StairsClimbingDynamicProgramming(6, numbers));
}
TEST(KnapsackTests, StairsClimbingDynamicProgrammingBottomUpTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = { 1, 2 };
	ASSERT_EQ(13, knapsack.StairsClimbingDynamicProgrammingBottomUp(6, numbers));
	numbers.clear();
	numbers = { 1, 2, 3 };
	knapsack.ClearDPMemoization();
	ASSERT_EQ(24, knapsack.StairsClimbingDynamicProgrammingBottomUp(6, numbers));
}
TEST(KnapsackTests, UnboundedKnapsackTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = {2, 3, 4};
	ASSERT_EQ(9, knapsack.UnboundedKnapsack(9, numbers)); // [3,3,3]
	numbers.clear();
	numbers = {3, 4, 10};
	ASSERT_EQ(12, knapsack.UnboundedKnapsack(12, numbers)); // [3,3,3,3] or [4,4,4]
	ASSERT_EQ(13, knapsack.UnboundedKnapsack(13, numbers)); // [3,10]
	ASSERT_EQ(16, knapsack.UnboundedKnapsack(16, numbers)); // [4,4,4,4]
	numbers.clear();
	numbers = {2000, 2000, 2000};
	ASSERT_EQ(2000, knapsack.UnboundedKnapsack(2000, numbers)); // 2000
	numbers.clear();
	numbers = {9, 9, 9};
	ASSERT_EQ(9, knapsack.UnboundedKnapsack(9, numbers)); // 9
	ASSERT_EQ(0, knapsack.UnboundedKnapsack(8, numbers));
	numbers.clear();
	numbers = {1};
	ASSERT_EQ(9999, knapsack.UnboundedKnapsack(9999, numbers)); // 1 * 9999
	numbers.clear();
	numbers = {1, 2};
	ASSERT_EQ(9999, knapsack.UnboundedKnapsack(9999, numbers));
	numbers.clear();
	numbers = {5, 9};
	ASSERT_EQ(10, knapsack.UnboundedKnapsack(10, numbers)); // [5,5]
	ASSERT_EQ(5, knapsack.UnboundedKnapsack(8, numbers));	 // [5]
	numbers.clear();
	numbers = {9};
	ASSERT_EQ(9, knapsack.UnboundedKnapsack(10, numbers)); // [9]
	ASSERT_EQ(9, knapsack.UnboundedKnapsack(9, numbers));	// [9]
	ASSERT_EQ(0, knapsack.UnboundedKnapsack(8, numbers));	// [0]
}
TEST(KnapsackTests, BoundedKnapsackTest)
{
	Knapsack knapsack;
	vector<size_t> numbers = {10, 1, 2, 7, 6, 1, 5};
	vector<vector<size_t>> result = knapsack.BoundedKnapsack(8, numbers);
	ASSERT_FALSE(result.empty());
	ASSERT_EQ(4, result.size());
	cout << "BoundedKnapsack which sums to amount 8: ";
	for (vector<vector<size_t>>::iterator it = result.begin(); it != result.end(); it++)
	{
		cout << "[";
		ranges::copy(*it, ostream_iterator<size_t>(cout, " "));
		cout << "], ";
	}
	cout << endl;
	numbers.clear();
	numbers = {2, 3, 5};
	result = knapsack.BoundedKnapsack(6, numbers);
	ASSERT_TRUE(result.empty());
}
TEST(KnapsackTests, BoundedCombinationSumTests)
{
	Knapsack knapsack;
	set<vector<size_t>> combinations = knapsack.BoundedKnapsackCombinationSum(3, 7);
	ASSERT_EQ(1, combinations.size()); // [[1,2,4]]
	combinations = knapsack.BoundedKnapsackCombinationSum(3, 9);
	ASSERT_EQ(3, combinations.size()); // [[1,2,6],[1,3,5],[2,3,4]]
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		ASSERT_EQ(3, it->size());
	combinations = knapsack.BoundedKnapsackCombinationSum(4, 1);
	ASSERT_TRUE(combinations.empty());
	combinations = knapsack.BoundedKnapsackCombinationSum(3, 2);
	ASSERT_TRUE(combinations.empty());
	combinations = knapsack.BoundedKnapsackCombinationSum(9, 45);
	ASSERT_EQ(1, combinations.size()); // [[1,2,3,4,5,6,7,8,9]]
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		ASSERT_EQ(9, it->size());
}
TEST(KnapsackTests, BoundedCombinationSumWithMaxElementTests)
{
	Knapsack knapsack;
	set<vector<size_t>> combinations = knapsack.BoundedKnapsackCombinationSum(3, 12, 8);
	ASSERT_FALSE(combinations.empty());
	combinations = knapsack.BoundedKnapsackCombinationSum(3, 10, 3);
	ASSERT_TRUE(combinations.empty());
	combinations = knapsack.BoundedKnapsackCombinationSum(2, 9, 10);
	ASSERT_FALSE(combinations.empty());
	combinations = knapsack.BoundedKnapsackCombinationSum(1, 5, 20);
	ASSERT_FALSE(combinations.empty());
	ASSERT_EQ(1, combinations.begin()->size());
	ASSERT_EQ(5, *(combinations.begin()->begin()));
	combinations = knapsack.BoundedKnapsackCombinationSum(1, 1, 20);
	ASSERT_FALSE(combinations.empty());
	ASSERT_EQ(1, combinations.begin()->size());
	ASSERT_EQ(1, *(combinations.begin()->begin()));
#if 0
	combinations = knapsack.BoundedKnapsackCombinationSum(10, 154, 20);
	ASSERT_FALSE(combinations.empty());
	combinations = knapsack.BoundedKnapsackCombinationSum(10, 56, 20);
	ASSERT_FALSE(combinations.empty());
#endif
}