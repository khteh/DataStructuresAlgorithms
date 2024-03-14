#pragma once
#include <limits>
#include <memory>
#include <utility>
#include <thread>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <queue>
#include <set>
#include <unordered_set>
#include <bitset>
#include <iomanip>
#include <regex>
#include <exception>
#include <cstring>
#include <ranges>
#include <variant>
#include <typeinfo>
#ifdef _MSC_VER
#include <ppl.h>
using namespace concurrency;
#elif defined(__GNUC__) || defined(__GNUG__)
#include <tbb/parallel_reduce.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
using namespace tbb;
#endif
#include <limits.h>
#include <cmath>
#include <chrono>
#include <concepts>
#include "Arithmetic.h"
#include "NameHidingExample.h"
#include "Singleton.h"
#include "Graph.h"
#include "Tower.h"
#include "MyStack.h"
#include "MyQueue.h"
#include "Tree.h"
#include "KDTree.h"
#include "Heap.h"
#include "Node.h"
#include "Trie.h"
#include "SuffixTree.h"
#include "PrefixTrie.h"
#include "PriorityQueueMedian.h"
#include "DiamondProblem.h"
#include "Error.h"
#include "LinkedList.h"
#include "CircularLinkedList.h"
#include "Square.h"
#include "TreasureGame.h"
#include "FunctionObject.h"
#include "IntervalMap.h"
#include "DisJointSet.h"
#include "Edge.h"
#include "LRUCache.h"
#include "Search.h"
#include "Twitter.h"
#include "Matrix.h"
#include "ListRangeSum.h"
#include "LongestCommonSubsequence.h"
#include "Knapsack.h"
#include "Range.h"
#include "Sort.h"
#include "Poker.h"
#include "VariantVisitor.h"
using namespace std;
#ifdef _MSC_VER
using namespace concurrency;
#endif
using namespace chrono;
typedef union
{
	long l;
	float f;
} thirty_two_bit;
typedef union
{
	long long ll;
	double d;
} sixty_four_bit;
typedef struct ZeroFactors
{
	long two, five, value, minValue;
	bool operator>(const ZeroFactors &other) const
	{
		return max(two, five) == max(other.two, other.five) ? value > other.value : max(two, five) > max(other.two, other.five);
		// return minValue == other.minValue ? value > other.value : minValue > other.minValue;
	}
	bool operator<(const ZeroFactors &other) const
	{
		return min(two, five) == min(other.two, other.five) ? value < other.value : min(two, five) < min(other.two, other.five);
	}
} zerofactors_t;
typedef struct ZeroFactorsTwoCount
{
	long count, fives, value, index;
	bool operator>(const ZeroFactorsTwoCount &other) const
	{
		if (count == other.count)
			return (fives == other.fives) ? value > other.value : fives > other.fives;
		else
			return count > other.count;
	}
} zerofactorstwocount_t;
typedef struct ZeroFactorsFiveCount
{
	long count, twos, value, index;
	bool operator>(const ZeroFactorsFiveCount &other) const
	{
		if (count == other.count)
			return (twos == other.twos) ? value > other.value : twos > other.twos;
		else
			return count > other.count;
	}
} zerofactorsfivecount_t;
typedef struct Position
{
	Position() : row(-1), col(-1) {}
	Position(size_t r, size_t c) : row(r), col(c) {}
	size_t row;
	size_t col;
} position_t;
typedef struct ZigZagEscape
{
	size_t index;
	int value;
	ZigZagEscape(size_t i, int v) : index(i), value(v) {}
	bool operator<(const ZigZagEscape &other) const
	{
		return value < other.value;
	}
	bool operator>(const ZigZagEscape &other) const
	{
		return value < other.value;
	}
} zigzag_t;
typedef struct buildmax_comparator
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
} buildmax_comparator_t;
float MachineEpsilon(float value);
float FloatMachineEpsilonApproximation();
double MachineEpsilon(double value);
double MachineEpsilonApproximation();
void testPointerReference(int *&);
long Min(long, long);
long Max(long, long);
long gcd(long a, long b);
long gcd_euclidean(long a, long b);
long lcm(long a, long b);
unsigned long long _atoull(string, char base = 10);
double _atod(string, char base = 10);
long _atoi(string);
double round(double num, int n);
bool isUniqueString(string const &);
vector<string> findUnique(vector<string> const &, vector<string> const &);
bool CanShuffleWithoutRepeat(string &);
long ConsecutiveLargestSumOfFactors(vector<zerofactors_t> &data, vector<zerofactors_t> &result, int value);
size_t CountDistinctSlices(vector<long> &);
size_t CountTriangles(vector<long> &);
// Greedy Algorithms
size_t MaxNonOverlappingSegments(vector<size_t> &, vector<size_t> &);
size_t TieRopes(vector<size_t> &, size_t);
long MinAbsSum(vector<long> &);
long NumberSolitaire(vector<long> &);
long MaxProfit(vector<long> &);
long MinimumLoss(vector<long>&);
string decimal_to_binary(long);
long binary_to_decimal(const string &);
void decimal_to_binary(long, vector<bool> &, size_t);
size_t binary_gap(long);
void reverse(string &);
void reverseWords(string &);
void reverseWordsTrimmed(string &);
void RemoveDuplicateCharacters(string &);
void RemoveDuplicateCharactersLexicographicalOrder(string &);
bool isAdditiveNumber(const string &);
bool checkIfAdditiveSequence(size_t, size_t, const string &);
bool areAnagrams(string const &, string const &);
size_t FindAnagrams(vector<string> const &, vector<vector<string>> &);
bool SherlockValidString(string const &);
size_t sherlockAndAnagrams(string const &);
bool isPalindrome(string const &);
bool isPalindrome1(string const &);
bool isPalindrome2(string const &);
string FindBiggestPalindromeSubstring(string const &);
void FindPalindromeSubstrings(string const &, set<string> &);
size_t PalindromeAnagramCount(string const &);
size_t PalindromeAnagramCount1(string const &);
bool AreRotatedStrings(string const &, string const &, size_t);
bool SolvabilityOfTheTilesGame(vector<size_t> &);
void RotateRightArray(vector<int> &, int);
vector<int> RotateLeftArray(vector<int> &, int);
vector<size_t> FindSubString(string const &, string const);
void copy_on_write_string();
unsigned long long fibonacci(long);
unsigned long long fibonacciDynamicProgramming(long);
string fibonacciModified(long, long, long);
string fibonacciModifiedDynamicProgramming(long, long, long);
unsigned long long factorial(long);
unsigned long long factorialDynamicProgramming(long);
long SequenceSum(long n);
void MultiplesCount(int, long &, long &);
long FactorialTrailingZeroesCount(long);
long MaxZeroProductBruteForce(vector<int> const &);
long MaxZeroProduct(vector<int> const &, size_t count = 3);
set<string> permute(string const &);
set<vector<long>> permute(vector<long> &);
void BitCombinations(size_t, vector<long> &);
vector<size_t> grayCode(size_t);
void OrderedMergedCombinations(set<string> &, const string &, const string &, string);
void numberCombinations1(size_t, size_t, size_t, vector<size_t> &, vector<vector<size_t>> &);
void numberCombinations(size_t, size_t, vector<vector<size_t>> &);
string insertCharAt(char, string, size_t);
vector<long> insertItemAt(long, vector<long> &, size_t);
void findDistinct(vector<long> &, vector<long> &);
void findPrimes(unsigned long, vector<long> &);
bool isPrime(unsigned long);
size_t CommonPrimeDivisors(vector<long> &, vector<long> &);
unsigned long long findMax(vector<unsigned long long> const &);
void Merge(vector<long> &, vector<long> &);
void parentheses(vector<string> &, size_t);
void parentheses(vector<string> &, string &, size_t, long, long);
long LongestValidParentheses(const string &);
long LongestValidParenthesesWithFixes(const string &, size_t k);
vector<long> diffWaysToCompute(string);
void KDTreeTests();
template <typename URNG>
void TestURNG(URNG &);
void TestRandom();
void MinHeapifyDown(vector<long> &, size_t);
void MaxHeapifyDown(vector<long> &, size_t);
long countInversions(vector<long> &);
size_t MergeCountInversions(vector<long> &, vector<long> &, size_t, size_t, size_t);
void DutchPartitioning(vector<long> &, long);
long **my2DAlloc(long, long);
long ***my3DAlloc(long, long, long);
string NumberStringSum(const string &, const string &);
string NumberStringMultiplication(string &, string &);
void shuffleCards(vector<long> &);
void randomSubset(vector<long> &, size_t, vector<long> &);
size_t countDigits(char, size_t);
size_t countNumbersWithUniqueDigits(size_t);
size_t Count1Bits(long);
void WordsLadder(const string &, const string &, set<string> &, vector<string> &);
void GetPermutations(string &);
void trim(string &);
size_t minDiffPairs(vector<long> &, long);
size_t greaterthansumpairs(vector<long> &, long);
string uncompress(string const &);
size_t findLongestContiguousPattern(string &, char);
string GetRange(vector<long> &);
vector<vector<long>> MergeIntervals(vector<vector<long>> &);
bool isSparseNumber(long);
long NextSparseNumber(long);
long KthNumberWith357PrimeFactors(long);
typedef struct PathResult
{
	PathResult() : sum(0), path("") {}
	unsigned long sum;
	string path;
} pathResult_t;
pathResult_t FindMaxPath(vector<vector<size_t>> &, size_t, size_t);
bool PathExists(vector<vector<char>> &, size_t, size_t, size_t, size_t, queue<string> &, char);
vector<string> findShortestPath(int, int, int, int, int);
bool FindShortestPath(vector<vector<char>> &, size_t, size_t, queue<string> &, char, char);
size_t ConnectedCellsInAGridLinkedList(vector<vector<long>> &);
size_t ConnectedCellsInAGrid(vector<vector<long>> &);
bool WordExistsInGrid(vector<vector<char>> &, const string &);
bool WordExistsInGrid(vector<vector<char>> &, const string &, long, long, size_t);
void OrderArrayIntoNegativePositiveSeries(vector<long> &);
// End of Sort numbers into consecutive positive/negative numbers
void EqualAverageDivide(vector<long> &, vector<long> &);
bool GetSum(vector<long> &, size_t K, long sum, size_t index, vector<long> &);
bool match(const string &, const string &);
string EncodeString(string);
string cipher(size_t, size_t, const string &);
void FindPattern(string, set<string> &, set<string> &);
string subtract(istream &, istream &);
set<string> intersectionNgram(const string &, const string &, int n);
vector<int> Increment(vector<int> &);
void *alignedMalloc(size_t bytes, size_t alignment);
void alignedFree(void **p);
vector<string> numbersegments(vector<long> &);
long concat(vector<long> &);
string buildmax(vector<size_t> &);
bool JSONValidation(string);
vector<char> AddVectors(vector<char> &, vector<char> &);
long MaxLengths(vector<string> &);
void ExceptionTest();
void PlayTreasureGame();
size_t countPaths(size_t, size_t, size_t, size_t, size_t);
vector<shared_ptr<Node<string>>> shortest_cycle_path(shared_ptr<Node<string>>);
int findMinFlip(vector<int> &);
bool IsValidMatrix(vector<vector<char>> const &);
size_t ZigZagEscape(vector<long> &);
size_t ZigZagEscape(vector<long> &, set<string> &);
vector<string> ZigZagEscape(vector<long> &, vector<long> &, size_t lIndex, size_t rIndex, long current, bool dir);
int IncreasingSequences(vector<long> &, vector<long> &);
size_t LongestIncreasingSubsequence(vector<size_t> &);
size_t LongestIncreasingSubsequenceNlogN(vector<size_t> &);
bool increasingTriplet(vector<size_t> &);
size_t FindSubsequenceRecursive(const string &, const string &);
size_t FindSubsequenceDynamicProgramming(const string &, const string &);
size_t shortPalindrome(const string &);
void cpluplus17();
long MaxProductOfThree(vector<long> &);
size_t CountDiv(size_t, size_t, size_t);
long ChocolatesByNumbers(long, long);
size_t getMinimumCost(size_t, vector<size_t> &);
size_t maxMin(size_t, vector<size_t> &);
vector<int> freqQuery(vector<vector<int>> &);
string encryption(string &);
vector<size_t> ClimbLeaderBoard(vector<long> &, vector<long> &);
long calculateMedian(vector<long> &);
string timeInWords(int, int);
size_t BeautifulQuadruples(long, long, long, long);
long kruskals(int, vector<long> &, vector<long> &, vector<long> &);
long getLowestPathCost(size_t g_nodes, vector<long> &, vector<long> &, vector<long> &);
size_t SurfaceArea3D(vector<vector<long>> &);
size_t MinSubGraphsDifference(vector<size_t> &, vector<vector<size_t>> &);
long PostmanProblem(vector<long> &, vector<vector<long>> &);
string DecryptPassword(const string &);
unsigned long long substrings(const string &);
size_t TwoCrosses(vector<string> &);
vector<long> absolutePermutation(size_t, size_t);
vector<string> bomberMan(size_t, vector<string> &);
size_t SnakesAndLaddersGame(vector<vector<size_t>> &, vector<vector<size_t>> &);
size_t SnakesAndLaddersGameFast(vector<vector<size_t>> &, vector<vector<size_t>> &);
size_t LengthOfLongestUniqueSubstring(const string &);
string zigzagconvert(const string &, size_t);
string numberToRoman(size_t);
double median(vector<long> &, vector<long> &);
long ReversePolishNotation(vector<string> &);
long BasicCalculator(const string &);
vector<long> productExceptSelf(vector<long> &);
size_t hIndex(vector<size_t> &);
vector<string> PhoneKeyLetters(const string &);
bool WordBreakDynamicProgramming(const string &, set<string> &);
void WordBreakDynamicProgramming(const string &, set<string> &, vector<string> &);
vector<string> wordBreakDFS(const string &, set<string> &);
vector<string> wordBreakDFS(string, set<string> &, map<string, vector<string>> &);
string getHint(const string &, const string &);
bool IsValidPreOrderTreeSerialization(const string &);
size_t LargestNumberCompositionProductWithDynamicProgramming(size_t);
vector<string> findItinerary(vector<vector<string>> &, const string &);
void EulerianPath(string, map<string, multiset<string>> &, vector<string> &);
size_t eggDrops(size_t, size_t);
vector<string> fizzBuzz(size_t);
vector<long> bfs(size_t, size_t, vector<vector<size_t>> &, size_t);
vector<size_t> UnbeatenPaths(size_t, vector<vector<size_t>> &, size_t);
string roadsInHackerland(size_t, vector<vector<size_t>> &);
bool Abbreviation(string &, string &);
void cpp20readonlyranges();
void cpp20ranges();
void cpp20variants();
size_t MoveDisksToTowerOfHanoi1(size_t, vector<long> &);
long double VectorSlicesSum(vector<long double> &);
long SteadyGene(string const &);
size_t IntervalSelection(vector<vector<size_t>> &);
string TwentyFourHourTimeConversion(string &);
vector<long> KaprekarNumbers(long, long);
size_t kMarsh(vector<string> &);
size_t MatrixPerimeter(vector<vector<size_t>> &, vector<string> &);
size_t NormalPlayNim(vector<size_t> &);
vector<size_t> ShortestPaths(size_t, vector<vector<size_t>> &, size_t);
bool CounterGame(long);
size_t EqualDistribution(vector<long> &);
bool HappyLadyBugs(string &);
size_t MaxNonDivisableSubset(vector<size_t> &, size_t);
size_t QueensAttack(size_t, size_t/*[1,rows]*/, size_t/*[1,cols]*/, vector<vector<size_t>>&);