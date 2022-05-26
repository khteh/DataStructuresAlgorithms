#include "pch.h"
using namespace std;
TEST(KnapsackTests, CoinChangeTest)
{
	vector<size_t> numbers = {3, 2, 1};
	KnapSack::ClearCoinChangeCache();
	set<vector<size_t>> combinations = KnapSack::CoinChange(0, numbers);
	ASSERT_TRUE(combinations.empty());
	set<vector<size_t>> combinations1 = KnapSack::CoinsChangeDynamicProgramming(0, numbers);
	ASSERT_TRUE(combinations1.empty());
	ASSERT_EQ(0, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(0, numbers));
	ASSERT_EQ(0, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(0, numbers));
	KnapSack::ClearCoinChangeCache();
	combinations = KnapSack::CoinChange(1, numbers);
	ASSERT_EQ(1, combinations.size());
	set<vector<size_t>>::iterator it = combinations.begin();
	ASSERT_EQ(1, it->size());
	ASSERT_EQ(1, (*it)[0]);
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(1, numbers);
	ASSERT_EQ(1, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	ASSERT_EQ(1, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(1, numbers));
	ASSERT_EQ(1, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(1, numbers));
	KnapSack::ClearCoinChangeCache();
	combinations = KnapSack::CoinChange(2, numbers);
	ASSERT_EQ(2, combinations.size());
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(2, numbers);
	ASSERT_EQ(2, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	ASSERT_EQ(2, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(2, numbers));
	ASSERT_EQ(2, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(2, numbers));
	KnapSack::ClearCoinChangeCache();
	combinations = KnapSack::CoinChange(3, numbers);
	ASSERT_EQ(3, combinations.size());
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(3, numbers);
	ASSERT_EQ(3, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	ASSERT_EQ(3, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(3, numbers));
	ASSERT_EQ(4, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(3, numbers)); // {3},{1,2},{2,1},{1,1,1}
	KnapSack::ClearCoinChangeCache();
	combinations = KnapSack::CoinChange(4, numbers);
	ASSERT_EQ(4, combinations.size());
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(4, numbers);
	ASSERT_EQ(4, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(4, numbers));
	ASSERT_EQ(7, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(4, numbers)); // {3,1},{3,1},{1,1,2},{1,2,1},{2,1,1},{2,2},{1,1,1,1}
	ASSERT_EQ(4, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	numbers.clear();
	numbers = {6, 5, 3, 2};
	KnapSack::ClearCoinChangeCache();
	combinations = KnapSack::CoinChange(10, numbers);
	ASSERT_EQ(5, combinations.size());
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(10, numbers);
	ASSERT_EQ(5, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	ASSERT_EQ(5, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(10, numbers));
	ASSERT_EQ(17, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(10, numbers));
	KnapSack::ClearCoinChangeCache();
	numbers.clear();
	numbers = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
	combinations = KnapSack::CoinChange(10, numbers);
	ASSERT_EQ(5, combinations.size());
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(10, numbers);
	ASSERT_EQ(5, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	KnapSack::ClearCoinChangeCache();
	numbers.clear();
	numbers = {1, 50};
	combinations = KnapSack::CoinChange(200, numbers);
	ASSERT_EQ(5, combinations.size());
	combinations1 = KnapSack::CoinsChangeDynamicProgramming(200, numbers);
	ASSERT_EQ(5, combinations1.size());
	ASSERT_EQ(combinations, combinations1);
	KnapSack::ClearCoinChangeCache();
	numbers.clear();
	numbers = {2, 3, 5};
	ASSERT_EQ(2, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(5, numbers));	// {{2,3}, {5}}
	ASSERT_EQ(3, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(5, numbers)); //{2,3},{3,2},{5}
	ASSERT_EQ(2, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(6, numbers));	// {{2,2,2}, {3,3}}
	ASSERT_EQ(2, KnapSack::CoinsChangeDuplicateWaysDynamicProgramming(6, numbers)); //
	numbers.clear();
	numbers = {5, 37, 8, 39, 33, 17, 22, 32, 13, 7, 10, 35, 40, 2, 43, 49, 46, 19, 41, 1, 12, 11, 28};
	ranges::sort(numbers);
	ASSERT_EQ(96190959, KnapSack::CoinsChangeUniqueWaysDynamicProgramming(166, numbers));
	KnapSack::ClearCoinChangeCache();
	numbers.clear();
	numbers = {1, 2, 5};
	ASSERT_EQ(3, KnapSack::CoinsChangeFewestCoinsDynamicProgramming(11, numbers));
	ASSERT_EQ(2, KnapSack::CoinsChangeFewestCoinsDynamicProgramming(10, numbers));
	numbers.clear();
	numbers = {2};
	ASSERT_EQ(-1, KnapSack::CoinsChangeFewestCoinsDynamicProgramming(3, numbers));
	numbers.clear();
	numbers = {1};
	ASSERT_EQ(0, KnapSack::CoinsChangeFewestCoinsDynamicProgramming(0, numbers));
	ASSERT_EQ(1, KnapSack::CoinsChangeFewestCoinsDynamicProgramming(1, numbers));
	ASSERT_EQ(2, KnapSack::CoinsChangeFewestCoinsDynamicProgramming(2, numbers));
	numbers.clear();
	numbers = {1, 2};
	KnapSack::ClearDPMemoization();
	ASSERT_EQ(13, KnapSack::StairsClimbingDynamicProgramming(6, numbers));
	ASSERT_EQ(13, KnapSack::StairsClimbingDynamicProgrammingBottomUp(6, numbers));
	numbers.clear();
	numbers = {1, 2, 3};
	KnapSack::ClearDPMemoization();
	ASSERT_EQ(24, KnapSack::StairsClimbingDynamicProgramming(6, numbers));
	ASSERT_EQ(24, KnapSack::StairsClimbingDynamicProgrammingBottomUp(6, numbers));
	// combinations1 = KnapSack::CoinsChangeDynamicProgramming(166, numbers); Times out!
	// assert(!combinations1.empty());
	// combinations = KnapSack::CoinChange(166, numbers); //Times out!
	// assert(combinations.size() == 96190959);
	numbers.clear();
	numbers = {3, 7, 405, 436};
	KnapSack::ClearCoinChangeCache();
	// combinations1 = KnapSack::CoinsChangeDynamicProgramming(8839, numbers); // Stack overflow! using recursive KnapSack::CoinChange()
	// assert(!combinations1.empty());
}
TEST(KnapsackTests, UnboundedKnapsackTest)
{
	vector<size_t> numbers = {2, 3, 4};
	ASSERT_EQ(9, KnapSack::UnboundedKnapsack(9, numbers)); // [3,3,3]
	numbers.clear();
	numbers = {3, 4, 10};
	ASSERT_EQ(12, KnapSack::UnboundedKnapsack(12, numbers)); // [3,3,3,3] or [4,4,4]
	ASSERT_EQ(13, KnapSack::UnboundedKnapsack(13, numbers)); // [3,10]
	ASSERT_EQ(16, KnapSack::UnboundedKnapsack(16, numbers)); // [4,4,4,4]
	numbers.clear();
	numbers = {2000, 2000, 2000};
	ASSERT_EQ(2000, KnapSack::UnboundedKnapsack(2000, numbers)); // 2000
	numbers.clear();
	numbers = {9, 9, 9};
	ASSERT_EQ(9, KnapSack::UnboundedKnapsack(9, numbers)); // 9
	assert(KnapSack::UnboundedKnapsack(8, numbers) == 0);
	numbers.clear();
	numbers = {1};
	ASSERT_EQ(9999, KnapSack::UnboundedKnapsack(9999, numbers)); // 1 * 9999
	numbers.clear();
	numbers = {1, 2};
	ASSERT_EQ(9999, KnapSack::UnboundedKnapsack(9999, numbers));
	numbers.clear();
	numbers = {5, 9};
	ASSERT_EQ(10, KnapSack::UnboundedKnapsack(10, numbers)); // [5,5]
	ASSERT_EQ(5, KnapSack::UnboundedKnapsack(8, numbers));	 // [5]
	numbers.clear();
	numbers = {9};
	ASSERT_EQ(9, KnapSack::UnboundedKnapsack(10, numbers)); // [9]
	ASSERT_EQ(9, KnapSack::UnboundedKnapsack(9, numbers));	// [9]
	ASSERT_EQ(0, KnapSack::UnboundedKnapsack(8, numbers));	// [0]
}
TEST(KnapsackTests, BoundedKnapsackTest)
{
	vector<size_t> numbers = {10, 1, 2, 7, 6, 1, 5};
	vector<vector<size_t>> result = KnapSack::BoundedKnapsack(8, numbers);
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
	result = KnapSack::BoundedKnapsack(6, numbers);
	ASSERT_TRUE(result.empty());
}
TEST(KnapsackTests, CombinationSumTests)
{
	set<vector<size_t>> combinations = KnapSack::BoundedKnapsackCombinationSum(3, 7);
	ASSERT_EQ(1, combinations.size()); // [[1,2,4]]
	combinations = KnapSack::BoundedKnapsackCombinationSum(3, 9);
	ASSERT_EQ(3, combinations.size()); // [[1,2,6],[1,3,5],[2,3,4]]
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		ASSERT_EQ(3, it->size());
	combinations = KnapSack::BoundedKnapsackCombinationSum(4, 1);
	ASSERT_TRUE(combinations.empty());
	combinations = KnapSack::BoundedKnapsackCombinationSum(3, 2);
	ASSERT_TRUE(combinations.empty());
	combinations = KnapSack::BoundedKnapsackCombinationSum(9, 45);
	ASSERT_EQ(1, combinations.size()); // [[1,2,3,4,5,6,7,8,9]]
	for (set<vector<size_t>>::iterator it = combinations.begin(); it != combinations.end(); it++)
		ASSERT_EQ(9, it->size());
}