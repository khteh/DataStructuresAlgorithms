#pragma once
#include "cout128.h"
#include "Arithmetic.h"
#include "Dijkstra.h"
#include "DynamicProgramming.h"
#include "NameHidingExample.h"
#include "Singleton.h"
#include "Graph.h"
#include "Greedy.h"
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
#include "FenwickTree.h"
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
#include "MaximizeStockProfits.h"
#include "Knapsack.h"
#include "Palindrome.h"
#include "Range.h"
#include "Sort.h"
#include "String.h"
#include "Poker.h"
#include "VariantVisitor.h"
#include "GameTheory.h"
#include "Permutation.h"
#include "Position.h"
#include "StringArithmetic.h"
#include "oneapi/tbb.h"
#include "pcg_extras.hpp"
#include "pcg_random.hpp"
#include "pcg_uint128.hpp"
#include "GenericConstraints.h"
/*
 * https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std
 * https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
 *
 * Notes on 'constexpr':
 * Without constexpr, DataStructuresAlgorithms.cpp compiles FactorialTrailingZeroesCount into a normal function and exports it.
 * In the object file it appears as a T symbol, which means “defined here, available to other files”. When Console.cpp calls it, the linker finds that symbol.
 * With constexpr, the function is implicitly inline. The rules for inline functions assume every file that uses one has its own copy of the body, so the compiler only generates code for it where it’s actually needed.
 * If a function doesn’t need to run at compile time (for example, you never use it in static_assert, a constexpr variable or a template argument), you can simply not make it constexpr.
 * Being constexpr is only useful when you actually use the result at compile time, and it costs you this restructuring.
 *
 * The accurate rule is:
 * (1) The compiler emits a copy of an inline function only when that file needs an actual call to it: the call isn’t inlined, or the function’s address is taken.
 * (2) Calling it isn’t enough. If the optimiser inlines every call, which is common at -O2 for small functions, there’s still no copy.
 * (3) Even when a copy is emitted, it’s a weak (W) symbol that exists for that file’s own use. Another file linking against it works only by coincidence, which is what happened in your -O0 build.
 * So whether another file can link against it depends on the optimisation level and the compiler’s inlining decisions. The language doesn’t guarantee it in either case. The only reliable rule is the one from before: a constexpr (or inline) function used in more than one file must have its body in a header.
 */
using namespace std;
using namespace chrono;
using namespace oneapi::tbb;
namespace ranges = std::ranges;
#ifdef __SIZEOF_INT128__
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif
typedef struct ZeroFactors
{
	size_t two, five, value;
	bool operator>(const ZeroFactors &other) const
	{
		return max(two, five) == max(other.two, other.five) ? value > other.value : max(two, five) > max(other.two, other.five);
	}
	bool operator<(const ZeroFactors &other) const
	{
		return min(two, five) == min(other.two, other.five) ? value < other.value : min(two, five) < min(other.two, other.five);
	}
} zerofactors_t;
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
class VariantException
{
public:
	explicit VariantException(long i)
	{
		throw long(i);
	}
	operator long() { throw long(123); }
};
template <typename A, typename B>
pair<B, A> flip_pair(const pair<A, B> &);
template <typename A, typename B, typename Cmp = less<B>>
multimap<B, A, Cmp> flip_map(const map<A, B> &, Cmp cmp = {});
void cpp20readonlyranges();
void cpp20ranges();
void cpp20variants();
template <floating_point_type T>
constexpr T Ulp(T);
template <floating_point_type T>
constexpr bool AlmostEqual(T a, T b, size_t ulps = 4);
template <floating_point_type T>
constexpr T MachineEpsilonApproximation();
void testPointerReference(int *&);
template <signed_integral_type T>
constexpr T MinBitTrick(T, T);
template <signed_integral_type T>
constexpr T MaxBitTrick(T, T);
uint64_t _atoull(string, char base = 10);
double _atod(string, char base = 10);
long _atoi(string);
generator<const size_t &> GenerateSequence(size_t, size_t);
generator<const size_t &> Generate2Sequence(size_t, size_t, size_t, size_t);
double round(double num, int n);
template <typename T>
constexpr T ceil_div(T, T);
template <arithmetic_type T>
constexpr T Factorial(size_t, T modulo = 0);
template <arithmetic_type T>
constexpr T FactorialRecursive(size_t, T modulo = 0);
template <arithmetic_type T>
constexpr T Fibonacci(long);
template <arithmetic_type T>
constexpr T FibonacciRecursive(long);
string FibonacciModified(size_t, size_t, size_t);
string FibonacciModifiedStringArithmetic(size_t, size_t, size_t);
string FibonacciModified_int128(size_t, size_t, size_t);
size_t FactorialTrailingZeroesCount(size_t);
constexpr long SequenceSum(long);
template <arithmetic_type T>
constexpr T BinomialCoefficients(size_t, size_t);
template <arithmetic_type T>
constexpr T BinomialCoefficientsMultiplicative(size_t, size_t);
template <arithmetic_type T>
T MultinomialCoefficients(size_t, vector<size_t> const &, T modulo = 0);
template <integral_type T>
constexpr size_t FactorsCount(T, T);
template <integral_type T>
size_t MaxZeroProductBruteForce(vector<T> const &, size_t elementCount = 3);
bool isUniqueString(string const &);
vector<string> findUnique(vector<string> const &, vector<string> const &);
bool CanShuffleWithoutRepeat(string &);
long ConsecutiveMaximumSumOfFactors(vector<zerofactors_t> &, vector<zerofactors_t> &, int);
size_t CountDistinctSlices(vector<long> &);
size_t CountTriangles(vector<long> &);
long MinAbsSum(vector<long> &);
string decimal_to_binary(long);
int64_t binary_to_decimal(string const &);
void decimal_to_binary(int64_t, vector<bool> &, size_t);
size_t binary_gap(long);
void reverse(string &);
void ReverseWords(string &);
void ReverseWordsTrimmed(string &);
int32_t ReverseInt32(int32_t);
size_t RemoveDuplicates(vector<long> &);
bool AreAnagrams(string const &, string const &);
size_t FindAnagrams(vector<string> const &, vector<vector<string>> &);
size_t SherlockAndAnagrams(string const &);
bool SolvabilityOfTheTilesGame(vector<size_t> &);
void RotateRightArray(vector<int> &, int);
vector<int> RotateLeftArray(vector<int> &, int);
vector<size_t> FindSubString(string const &, string const);
void copy_on_write_string();
void BitCombinations(size_t, vector<long> &);
vector<size_t> grayCode(size_t);
void OrderedMergedCombinations(set<string> &, string const &, string const &, string);
size_t LargestNumberCompositionProduct(size_t);
void FindDistinct(vector<long> &, vector<long> &);
void FindPrimes(unsigned long, vector<long> &);
bool IsPrime(unsigned long);
size_t CommonPrimeDivisors(vector<long> &, vector<long> &);
void Merge(vector<long> &, vector<long> &);
long LongestValidParenthesesWithFixes(string const &, size_t k);
vector<long> diffWaysToCompute(string);
void KDTreeTests();
template <typename URNG>
void TestURNG(URNG &);
void TestRandom();
void MinHeapifyDown(vector<long> &, size_t);
void MaxHeapifyDown(vector<long> &, size_t);
long countInversions(vector<long> &);
size_t MergeCountInversions(vector<long> &, vector<long> &, size_t, size_t, size_t);
long **my2DAlloc(long, long);
long ***my3DAlloc(long, long, long);
void shuffleCards(vector<long> &);
void randomSubset(vector<long> &, size_t, vector<long> &);
size_t CountDigits(char, size_t);
size_t CountNumbersWithUniqueDigits(size_t);
size_t Count1Bits(long);
size_t Count1Bits(long, set<size_t> &);
size_t BitCountOfNChoices(size_t);
size_t BitCount(size_t);
void trim(string &);
size_t minDiffPairs(vector<long> &, long);
string uncompress(string const &);
size_t FindLongestContiguousPattern(string &, char);
size_t LongestConsecutive(vector<size_t> &);
string GetRange(vector<long> &);
vector<vector<long>> MergeIntervals(vector<vector<long>> &);
bool IsSparseNumber(long);
long NextSparseNumber(long);
long KthNumberWith357PrimeFactors(long);
bool WordExistsInGrid(vector<vector<char>> &, string const &);
bool WordExistsInGrid(vector<vector<char>> &, string const &, long, long, size_t);
void EqualAverageDivide(vector<long> &, vector<long> &);
bool GetSum(vector<long> &, size_t K, long sum, size_t index, vector<long> &);
bool match(string const &, string const &);
string EncodeString(string);
void FindPattern(string, set<string> &, set<string> &);
string subtract(istream &, istream &);
set<string> intersectionNgram(string const &, string const &, int n);
vector<int> Increment(vector<int> &);
void *alignedMalloc(size_t bytes, size_t alignment);
void alignedFree(void **p);
vector<string> numbersegments(vector<long> &);
long concat(vector<long> &);
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
size_t IncreasingSequences(vector<long> &, vector<long> &);
size_t LongestIncreasingSubsequenceNlogN(vector<size_t> const &);
size_t LongestNonDecreasingSubsequenceNlogN(vector<size_t> const &);
size_t LongestNonDecreasingSubsequenceOneReplacement(vector<long> const &);
size_t LongestDecreasingSubsequenceNlogN(vector<size_t> &);
size_t LargestRussianDollStack(vector<vector<size_t>> &);
bool IncreasingTriplet(vector<size_t> &);
size_t FindSubsequenceRecursive(string const &, string const &);
void cpluplus17();
long MaxProductOfThree(vector<long> &);
size_t CountDiv(size_t, size_t, size_t);
long ChocolatesByNumbers(long, long);
vector<int> freqQuery(vector<vector<int>> &);
string encryption(string &);
vector<size_t> ClimbLeaderBoard(vector<long> &, vector<long> &);
long CalculateMedian(vector<long> &);
string TimeInWords(size_t, size_t);
size_t BeautifulQuadruples(size_t, size_t, size_t, size_t);
long kruskals(int, vector<long> &, vector<long> &, vector<long> &);
long getLowestPathCost(size_t, vector<long> &, vector<long> &, vector<long> &);
size_t PostmanProblemWithoutLoop(size_t, set<size_t> const &, vector<vector<size_t>> const &, bool print = false);
uint64_t substrings(string const &);
vector<string> BomberMan(size_t, vector<string> const &);
string NumberToRoman(size_t);
size_t RomanToNumber(string const &);
double SortedListsMedian(vector<long> &, vector<long> &);
size_t hIndex(vector<size_t> &);
vector<string> FindItinerary(vector<vector<string>> &, string const &);
void EulerianPath(string, map<string, multiset<string>> &, vector<string> &);
vector<string> fizzBuzz(size_t);
vector<long> UnbeatenPaths(size_t, vector<vector<size_t>> &, size_t);
string RoadsInHackerland(size_t, vector<vector<size_t>> &);
string RoadsInHackerland1(size_t, vector<vector<size_t>> &);
string RoadsInHackerland2(size_t, vector<vector<size_t>> &);
typedef struct TowerOfHanoiState
{
	TowerOfHanoiState() : state(0), moves(0) {}
	TowerOfHanoiState(uint64_t s, size_t m) : state(s), moves(m) {}
	uint64_t state;
	size_t moves;
} towerofhanoi_state_t;
int ResetTowerOfHanoi(size_t, vector<size_t> const &);
size_t IntervalSelection(vector<vector<size_t>> &);
vector<long> KaprekarNumbers(long, long);
size_t kMarsh(vector<string> const &);
size_t MatrixPerimeter(vector<vector<size_t>> &, vector<string> &);
size_t PowerSum(size_t, size_t, size_t i = 1);
uint64_t DistinctPairs(size_t, vector<vector<long>> const &);
size_t RoadsAndLibraries(size_t, size_t, size_t, vector<vector<size_t>> const &);
char SuperDigit(string const &, size_t);
size_t FindConnectedComponents(vector<long> &);
string LongestCommonPrefix(vector<string> const &);