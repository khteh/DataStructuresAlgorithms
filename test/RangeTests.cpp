#include "pch.h"
using namespace std;
template <typename T1, typename T2>
class RangeTestFixture1
{
public:
	void SetUp(T1 expected, vector<T2> data)
	{
		_expected = expected;
		_data = data;
	}

protected:
	Range _rangeObj;
	vector<T2> _data;
	T1 _expected;
};

template <typename T1, typename T2, typename T3>
class RangeTestFixture2
{
public:
	void SetUp(T1 expected, T2 param, vector<T3> data)
	{
		_expected = expected;
		_param = param;
		_data = data;
	}

protected:
	Range _rangeObj;
	vector<T3> _data;
	T2 _param;
	T1 _expected;
};
class SumPairsTestFixture : public RangeTestFixture2<size_t, size_t, size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture2::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t SumPairsTest()
	{
		return _rangeObj.SumPairs(_param, _data);
	}
};
TEST_P(SumPairsTestFixture, SumPairsTests)
{
	ASSERT_EQ(this->_expected, this->SumPairsTest());
}
INSTANTIATE_TEST_SUITE_P(
	SumPairsTests,
	SumPairsTestFixture,
	::testing::Values(make_tuple(2, 8, vector<size_t>{1, 2, 3, 4, 5, 6, 5}),
					  make_tuple(3, 12, vector<size_t>{5, 7, 9, 13, 11, 6, 6, 3, 3}),
					  make_tuple(4, 10, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
class MinimumLossTestFixture : public RangeTestFixture1<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	long MinimumLossTest()
	{
		return _rangeObj.MinimumLoss(_data);
	}
};
TEST_P(MinimumLossTestFixture, MinimumLossTests)
{
	ASSERT_EQ(this->_expected, this->MinimumLossTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinimumLossTests,
	MinimumLossTestFixture,
	::testing::Values(make_tuple(2, vector<long>{5, 10, 3}),
					  make_tuple(2, vector<long>{20, 7, 8, 2, 5}),
					  make_tuple(1, vector<long>{2, 3, 4, 1})));
class MinSumSubSequenceTestFixture : public RangeTestFixture2<size_t, size_t, size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture2::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t MinSumSubSequenceTest()
	{
		return _rangeObj.MinSumSubSequence(_param, _data);
	}
};
TEST_P(MinSumSubSequenceTestFixture, MinSumSubSequenceTests)
{
	ASSERT_EQ(this->_expected, this->MinSumSubSequenceTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinSumSubSequenceTests,
	MinSumSubSequenceTestFixture,
	::testing::Values(make_tuple(2, 7, vector<size_t>{2, 3, 1, 2, 4, 3}), make_tuple(-1, 1, vector<size_t>{}), make_tuple(2, 5, vector<size_t>{1, 4, 4}), make_tuple(1, 4, vector<size_t>{1, 4, 4})));
class StockMaxTestFixture : public RangeTestFixture1<size_t, long>, public testing::TestWithParam<tuple<size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t StockMaxTest()
	{
		return _rangeObj.StockMax(_data);
	}
};
class GreaterThanSumPairsTestFixture : public RangeTestFixture2<size_t, size_t, size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture2::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t GreaterThanSumPairsTest()
	{
		return _rangeObj.GreaterThanSumPairs(_param, _data);
	}
};
class StockMaxProfitTestFixture : public RangeTestFixture1<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	long StockMaxProfitTest()
	{
		return _rangeObj.StockMaxProfit(_data);
	}
};
TEST_P(StockMaxProfitTestFixture, StockMaxProfitTests)
{
	ASSERT_EQ(this->_expected, this->StockMaxProfitTest());
}
INSTANTIATE_TEST_SUITE_P(
	StockMaxProfitTests,
	StockMaxProfitTestFixture,
	::testing::Values(make_tuple(6, vector<long>{1, 2, 3, 0, 2, 5}), make_tuple(6, vector<long>{1, 2, 3, 0, 1, 5}), make_tuple(9, vector<long>{1, 2, 6, 0, 1, 5})));
class StockMaxProfit2TestFixture : public RangeTestFixture1<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	long StockMaxProfit2Test()
	{
		return _rangeObj.StockMaxProfit2(_data);
	}
};
TEST_P(StockMaxProfit2TestFixture, StockMaxProfit2Tests)
{
	ASSERT_EQ(this->_expected, this->StockMaxProfit2Test());
}
INSTANTIATE_TEST_SUITE_P(
	StockMaxProfit2Tests,
	StockMaxProfit2TestFixture,
	::testing::Values(make_tuple(7, vector<long>{7, 1, 5, 3, 6, 4}), make_tuple(4, vector<long>{1, 2, 3, 4, 5}), make_tuple(0, vector<long>{5, 4, 3, 2, 1}),
					  make_tuple(1, vector<long>{1, 2}), make_tuple(0, vector<long>{1, 1})));

class SherlockAndCostTestFixture : public RangeTestFixture1<size_t, size_t>, public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t SherlockAndCostTest()
	{
		return _rangeObj.SherlockAndCost(_data);
	}
};
class VectorEqualSplitTestFixture : public RangeTestFixture1<size_t, int>, public testing::TestWithParam<tuple<size_t, vector<int>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t VectorEqualSplitTest()
	{
		return _rangeObj.VectorEqualSplit(_data);
	}
};
TEST_P(VectorEqualSplitTestFixture, VectorEqualSplitTests)
{
	ASSERT_EQ(this->_expected, this->VectorEqualSplitTest());
}
/*
 * [3, 2, 3, 2, 2, 2, 2]:
 *
 * (1) [3 2 3] [2 2 2 2]
 * (2) [2 2] [2 2]
 * (3) [2] [2]
 *
 * [0, 0, 0, 0, 0]:
 *
 * (1) [0] [0 0 0 0]
 * (2) [0] [0 0 0]
 * (3) [0] [0 0]
 * (4) [0] [0]
 */
INSTANTIATE_TEST_SUITE_P(
	VectorEqualSplitTests,
	VectorEqualSplitTestFixture,
	::testing::Values(make_tuple(0, vector<int>{1}), make_tuple(0, vector<int>{1, 2}), make_tuple(1, vector<int>{1, 1}), make_tuple(1, vector<int>{0, 0}),
					  make_tuple(2, vector<int>{0, 0, 0}), make_tuple(0, vector<int>{1, 1, 1}), make_tuple(0, vector<int>{2, 2, 2}), make_tuple(0, vector<int>{1, 1, 1, 1, 1}),
					  make_tuple(0, vector<int>{2, 2, 2, 2, 2}), make_tuple(2, vector<int>{1, 1, 1, 1}), make_tuple(1, vector<int>{1, 1, 1, 1, 1, 1}),
					  make_tuple(0, vector<int>{1, 2, 1}), make_tuple(1, vector<int>{1, 2, 1, 2}), make_tuple(2, vector<int>{2, 2, 2, 3, 3}),
					  make_tuple(3, vector<int>{3, 2, 3, 2, 2, 2, 2}), make_tuple(2, vector<int>{1, 1, 1, 1}), make_tuple(3, vector<int>{4, 1, 0, 1, 1, 0, 1}),
					  make_tuple(4, vector<int>{16384, 8192, 8192, 16384, 8192, 8192, 32768, 32768}),
					  make_tuple(1, vector<int>{8760958, 8760957, 547560, 547560, 547560, 273780, 273780, 2190239, 4380479, 4380479, 4380478}),
					  make_tuple(4, vector<int>{0, 0, 0, 0, 0})));
class MaxProductOfNonOverlappingWordLengthsTestFixture : public RangeTestFixture1<size_t, string>, public testing::TestWithParam<tuple<size_t, vector<string>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	size_t MaxProductOfNonOverlappingWordLengthsTest()
	{
		return _rangeObj.MaxProductOfNonOverlappingWordLengths(_data);
	}
};
TEST_P(MaxProductOfNonOverlappingWordLengthsTestFixture, MaxProductOfNonOverlappingWordLengthsTests)
{
	ASSERT_EQ(this->_expected, this->MaxProductOfNonOverlappingWordLengthsTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxProductOfNonOverlappingWordLengthsTests,
	MaxProductOfNonOverlappingWordLengthsTestFixture,
	::testing::Values(make_tuple(16, vector<string>{"abcw", "baz", "foo", "bar", "xtfn", "abcdef"}), // "abcw", "xtfn"
					  make_tuple(4, vector<string>{"a", "ab", "abc", "d", "cd", "bcd", "abcd"}),	 // "ab", "cd"
					  make_tuple(0, vector<string>{"a", "aa", "aaa", "aaaa"})));
class AlmostSortedTestFixture : public RangeTestFixture1<string, long>, public testing::TestWithParam<tuple<string, vector<long>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	string AlmostSortedTest()
	{
		return _rangeObj.AlmostSorted(_data);
	}
};
TEST_P(AlmostSortedTestFixture, AlmostSortedTests)
{
	ASSERT_EQ(this->_expected, this->AlmostSortedTest());
}
INSTANTIATE_TEST_SUITE_P(
	AlmostSortedTests,
	AlmostSortedTestFixture,
	::testing::Values(make_tuple("swap 1 2", vector<long>{4, 2}), // Index starts from 1, not 0.
					  make_tuple("no", vector<long>{3, 1, 2}),
					  make_tuple("reverse 2 5", vector<long>{1, 5, 4, 3, 2, 6}),
					  make_tuple("no", vector<long>{43, 65, 1, 98, 99, 101})));
class PickNumbersFromRangeTestFixture : public RangeTestFixture1<size_t, long>, public testing::TestWithParam<tuple<size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()));
	}
	long PickNumbersFromRangeTest()
	{
		return _rangeObj.PickNumbersFromRange(_data);
	}
};
TEST_P(PickNumbersFromRangeTestFixture, PickNumbersFromRangeTests)
{
	ASSERT_EQ(this->_expected, this->PickNumbersFromRangeTest());
}
INSTANTIATE_TEST_SUITE_P(
	PickNumbersFromRangeTests,
	PickNumbersFromRangeTestFixture,
	::testing::Values(make_tuple(5, vector<long>{1, 1, 2, 2, 4, 4, 5, 5, 5}), make_tuple(3, vector<long>{4, 6, 5, 3, 3, 1}), make_tuple(5, vector<long>{1, 2, 2, 3, 1, 2})));
class MaxNonDivisableSubsetTestFixture : public RangeTestFixture2<size_t, size_t, size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture2::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t MaxNonDivisableSubsetTest()
	{
		return _rangeObj.MaxNonDivisableSubset(_data, _param);
	}
};
TEST_P(MaxNonDivisableSubsetTestFixture, MaxNonDivisableSubsetTests)
{
	ASSERT_EQ(this->_expected, this->MaxNonDivisableSubsetTest());
}
INSTANTIATE_TEST_SUITE_P(
	MaxNonDivisableSubsetTests,
	MaxNonDivisableSubsetTestFixture,
	::testing::Values(make_tuple(3, 3, vector<size_t>{1, 2, 3, 4, 5, 6}),
					  make_tuple(8, 6, vector<size_t>{12, 6, 1, 9, 13, 15, 10, 21, 14, 32, 5, 8, 23, 19}),
					  make_tuple(3, 3, vector<size_t>{1, 7, 2, 4})));
class HackerlandRadioTransmittersTestFixture : public RangeTestFixture2<size_t, size_t, size_t>, public testing::TestWithParam<tuple<size_t, size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		RangeTestFixture2::SetUp(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	}
	size_t HackerlandRadioTransmittersTest()
	{
		return _rangeObj.HackerlandRadioTransmitters(_data, _param);
	}
};

TEST_P(HackerlandRadioTransmittersTestFixture, HackerlandRadioTransmittersTests)
{
	ASSERT_EQ(this->_expected, this->HackerlandRadioTransmittersTest());
}
INSTANTIATE_TEST_SUITE_P(
	HackerlandRadioTransmittersTests,
	HackerlandRadioTransmittersTestFixture,
	::testing::Values(make_tuple(3, 1, vector<size_t>{1, 2, 3, 5, 9}),
					  make_tuple(2, 1, vector<size_t>{1, 2, 3, 4, 5}),
					  make_tuple(3, 2, vector<size_t>{7, 2, 4, 6, 5, 9, 12, 11}),
					  make_tuple(4, 2, vector<size_t>{9, 5, 4, 2, 6, 15, 12})));
class ConsecutiveMaximumSumTestFixture : public testing::TestWithParam<tuple<long, vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_expectedCollection = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	long ConsecutiveMaximumSumTest()
	{
		return _rangeObj.ConsecutiveMaximumSum(_data, _collectionResult);
	}

protected:
	Range _rangeObj;
	long _expected;
	vector<long> _data, _expectedCollection, _collectionResult;
};
TEST_P(ConsecutiveMaximumSumTestFixture, ConsecutiveMaximumSumTests)
{
	ASSERT_EQ(this->_expected, this->ConsecutiveMaximumSumTest());
	ASSERT_EQ(this->_expectedCollection, this->_collectionResult);
}
INSTANTIATE_TEST_SUITE_P(
	ConsecutiveMaximumSumTests,
	ConsecutiveMaximumSumTestFixture,
	::testing::Values(make_tuple(5, vector<long>{2, 3}, vector<long>{2, 3, -6}),
					  make_tuple(15, vector<long>{4, 5, 6}, vector<long>{2, 3, -6, 4, 5, 6, -20}),
					  make_tuple(1, vector<long>{0, 0, 1}, vector<long>{0, -1, 0, 0, 1, 0, -1, -1}),
					  make_tuple(2, vector<long>{1, 1}, vector<long>{-1, -1, -1, -1, -1, -1, 1, 1}),
					  make_tuple(7, vector<long>{4, -1, -2, 1, 5}, vector<long>{-2, -3, 4, -1, -2, 1, 5, -3})));
class ConsecutiveMaximumSumModuloTestFixture : public testing::TestWithParam<tuple<size_t, size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_modulo = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	size_t ConsecutiveMaximumSumModuloTest()
	{
		return _rangeObj.ConsecutiveMaximumSumModulo(_data, _modulo);
	}

protected:
	Range _rangeObj;
	size_t _expected, _modulo;
	vector<long> _data;
};
TEST_P(ConsecutiveMaximumSumModuloTestFixture, ConsecutiveMaximumSumModuloTests)
{
	ASSERT_EQ(this->_expected, this->ConsecutiveMaximumSumModuloTest());
}
INSTANTIATE_TEST_SUITE_P(
	ConsecutiveMaximumSumModuloTests,
	ConsecutiveMaximumSumModuloTestFixture,
	::testing::Values(make_tuple(1, 2, vector<long>{1, 2, 3}),
					  make_tuple(6, 7, vector<long>{3, 3, 9, 9, 5}),
					  make_tuple(14, 15, vector<long>{1, 2, -5, 4, -8, 6, 7, 3, -7, 11, 12}),
					  make_tuple(1802192837, 1804289384, vector<long>{846930887, 1681692778, 1714636916, 1957747794, 424238336, 719885387, 1649760493, 596516650, 1189641422, 1025202363, 1350490028, 783368691, 1102520060, 2044897764, 1967513927, 1365180541, 1540383427, 304089173, 1303455737, 35005212, 521595369, 294702568, 1726956430, 336465783, 861021531, 278722863, 233665124, 2145174068, 468703136, 1101513930, 1801979803, 1315634023, 635723059, 1369133070, 1125898168, 1059961394, 2089018457, 628175012, 1656478043, 1131176230, 1653377374, 859484422, 1914544920, 608413785, 756898538, 1734575199, 1973594325, 149798316, 2038664371, 1129566414})));
class ConsecutiveLargestProductTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long ConsecutiveLargestProductTest()
	{
		return _rangeObj.ConsecutiveLargestProduct(_data);
	}

protected:
	Range _rangeObj;
	long _expected;
	vector<long> _data;
};
TEST_P(ConsecutiveLargestProductTestFixture, ConsecutiveLargestProductTests)
{
	ASSERT_EQ(this->_expected, this->ConsecutiveLargestProductTest());
}
INSTANTIATE_TEST_SUITE_P(
	ConsecutiveLargestProductTests,
	ConsecutiveLargestProductTestFixture,
	::testing::Values(make_tuple(6, vector<long>{2, 3, -2, 4}),
					  make_tuple(0, vector<long>{-2, 0, -1}),
					  make_tuple(2, vector<long>{-2, -1, 0}),
					  make_tuple(3, vector<long>{-3, -1, -1}),
					  make_tuple(2, vector<long>{0, 2}),
					  make_tuple(4, vector<long>{3, -1, 4}),
					  make_tuple(1, vector<long>{-1, -1}),
					  make_tuple(6, vector<long>{0, -2, -3}),
					  make_tuple(24, vector<long>{2, -5, -2, -4, 3}),
					  make_tuple(2, vector<long>{2, 0, -3, 2, 1, 0, 1, -2})));
class LongestNonNegativeSumSliceTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	long LongestNonNegativeSumSliceTest()
	{
		return _rangeObj.LongestNonNegativeSumSlice(_data);
	}

protected:
	Range _rangeObj;
	long _expected;
	vector<long> _data;
};
TEST_P(LongestNonNegativeSumSliceTestFixture, LongestNonNegativeSumSliceTests)
{
	ASSERT_EQ(this->_expected, this->LongestNonNegativeSumSliceTest());
}
INSTANTIATE_TEST_SUITE_P(
	LongestNonNegativeSumSliceTests,
	LongestNonNegativeSumSliceTestFixture,
	::testing::Values(make_tuple(7, vector<long>{-1, -1, 1, -1, 1, 0, 1, -1, -1}),
					  make_tuple(4, vector<long>{1, 1, -1, -1, -1, -1, -1, 1, 1}),
					  make_tuple(6, vector<long>{0, -1, 0, 0, 1, 0, -1, -1}),
					  make_tuple(4, vector<long>{-1, -1, -1, -1, -1, -1, 1, 1})));
class LongestUpDownAlternatingSubSequenceTestFixture : public testing::TestWithParam<tuple<size_t, vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_expectedCollection = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	size_t LongestUpDownAlternatingSubSequenceTest()
	{
		return _rangeObj.LongestUpDownAlternatingSubSequence(_data, _collectionResult);
	}

protected:
	Range _rangeObj;
	size_t _expected;
	vector<long> _data, _expectedCollection, _collectionResult;
};
TEST_P(LongestUpDownAlternatingSubSequenceTestFixture, LongestUpDownAlternatingSubSequenceTests)
{
	ASSERT_EQ(this->_expected, this->LongestUpDownAlternatingSubSequenceTest());
	ASSERT_EQ(this->_expectedCollection, this->_collectionResult);
}
INSTANTIATE_TEST_SUITE_P(
	LongestUpDownAlternatingSubSequenceTests,
	LongestUpDownAlternatingSubSequenceTestFixture,
	::testing::Values(make_tuple(9, vector<long>{2, 51, 50, 60, 55, 70, 68, 80, 76}, vector<long>{1, 2, 51, 50, 60, 55, 70, 68, 80, 76, 75, 12, 45})));

TEST_P(GreaterThanSumPairsTestFixture, GreaterThanSumPairsTests)
{
	ASSERT_EQ(this->_expected, this->GreaterThanSumPairsTest());
}
INSTANTIATE_TEST_SUITE_P(
	GreaterThanSumPairsTests,
	GreaterThanSumPairsTestFixture,
	::testing::Values(make_tuple(35, 8, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
					  make_tuple(45, 8, vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10})));

class TripletsZeroSumTestFixture : public testing::TestWithParam<tuple<vector<vector<long>>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<vector<long>> TripletsZeroSumTest()
	{
		return _rangeObj.TripletsZeroSum(_data);
	}

protected:
	Range _rangeObj;
	vector<vector<long>> _expected;
	vector<long> _data;
	long _sum;
};
TEST_P(TripletsZeroSumTestFixture, TripletsZeroSumTests)
{
	ASSERT_EQ(this->_expected, this->TripletsZeroSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	TripletsZeroSumTests,
	TripletsZeroSumTestFixture,
	::testing::Values(make_tuple(vector<vector<long>>{{-1, -1, 2}, {-1, 0, 1}}, vector<long>{-1, 0, 1, 2, -1, -4}),
					  make_tuple(vector<vector<long>>{{0, 0, 0}}, vector<long>{0, 0, 0})));
class QuadrupletsSumTestFixture : public testing::TestWithParam<tuple<vector<vector<long>>, long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_sum = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	vector<vector<long>> QuadrupletsSumTest()
	{
		return _rangeObj.QuadrupletsSum(_sum, _data);
	}

protected:
	Range _rangeObj;
	vector<vector<long>> _expected;
	vector<long> _data;
	long _sum;
};
TEST_P(QuadrupletsSumTestFixture, QuadrupletsSumTests)
{
	ASSERT_EQ(this->_expected, this->QuadrupletsSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	QuadrupletsSumTests,
	QuadrupletsSumTestFixture,
	::testing::Values(make_tuple(vector<vector<long>>{{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}}, 0, vector<long>{1, 0, -1, 0, -2, 2}),
					  make_tuple(vector<vector<long>>{{-3, -1, 2, 4}}, 2, vector<long>{-3, -1, 0, 2, 4, 5})));
class NumberDiffPairsTestFixture : public testing::TestWithParam<tuple<size_t, long, set<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_sum = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	size_t NumberDiffPairsTest()
	{
		return _rangeObj.NumberDiffPairs(_sum, _data);
	}

protected:
	Range _rangeObj;
	size_t _expected;
	set<long> _data;
	long _sum;
};
TEST_P(NumberDiffPairsTestFixture, NumberDiffPairsTests)
{
	ASSERT_EQ(this->_expected, this->NumberDiffPairsTest());
}
INSTANTIATE_TEST_SUITE_P(
	NumberDiffPairsTests,
	NumberDiffPairsTestFixture,
	::testing::Values(make_tuple(6, 3, set<long>{1, 2, 3, 5, 6, 8, 9, 11, 12, 13}),
					  make_tuple(3, 2, set<long>{1, 5, 3, 4, 2}),
					  make_tuple(5, 2, set<long>{1, 3, 5, 8, 6, 4, 2}),
					  make_tuple(3, 2, set<long>{1, 5, 3, 4, 2}),
					  make_tuple(5, 2, set<long>{1, 3, 5, 8, 6, 4, 2})));
TEST_P(StockMaxTestFixture, StockMaxTests)
{
	ASSERT_EQ(this->_expected, this->StockMaxTest());
}
INSTANTIATE_TEST_SUITE_P(
	StockMaxTests,
	StockMaxTestFixture,
	::testing::Values(make_tuple(0, vector<long>{5, 3, 2}),
					  make_tuple(197, vector<long>{1, 2, 100}), // (100 - 1 = 99) + (100 - 2 = 98) = 197
					  make_tuple(3, vector<long>{1, 3, 1, 2})));

TEST(RangeTests, MaxProfitTest)
{
	Range range;
	vector<long> a = {23171, 21011, 21123, 21366, 21013, 21367};
	ASSERT_EQ(356, range.MaxProfit(a));
}
TEST_P(SherlockAndCostTestFixture, SherlockAndCostTests)
{
	ASSERT_EQ(this->_expected, this->SherlockAndCostTest());
}
INSTANTIATE_TEST_SUITE_P(
	SherlockAndCostTests,
	SherlockAndCostTestFixture,
	::testing::Values(make_tuple(2, vector<size_t>{1, 2, 3}),
					  make_tuple(12, vector<size_t>{4, 7, 9}),
					  make_tuple(36, vector<size_t>{10, 1, 10, 1, 10})));
TEST(RangeTests, ClimbLeaderboardTest)
{
	vector<long> a = {100, 100, 50, 40, 40, 20, 10};
	vector<long> b = {5, 25, 50, 120};
	vector<size_t> expected = {6, 4, 2, 1};
	ASSERT_EQ(expected, ClimbLeaderBoard(a, b));
}
class WiggleMaxLengthTestFixture : public testing::TestWithParam<tuple<vector<long>, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	vector<long> WiggleMaxLengthTest()
	{
		return _rangeObj.WiggleMaxLength(_data);
	}

protected:
	Range _rangeObj;
	vector<long> _expected;
	vector<long> _data;
};
TEST_P(WiggleMaxLengthTestFixture, WiggleMaxLengthTests)
{
	ASSERT_EQ(this->_expected, this->WiggleMaxLengthTest());
}
INSTANTIATE_TEST_SUITE_P(
	WiggleMaxLengthTests,
	WiggleMaxLengthTestFixture,
	::testing::Values(make_tuple(vector<long>{1, 7, 4, 9, 2, 5}, vector<long>{1, 7, 4, 9, 2, 5}),
					  make_tuple(vector<long>{0}, vector<long>{0}),
					  make_tuple(vector<long>{0}, vector<long>{0, 0}),
					  make_tuple(vector<long>{3, 2, 5}, vector<long>{3, 3, 3, 2, 5}),
					  make_tuple(vector<long>{1, 17, 5, 15, 5, 16, 8}, vector<long>{1, 17, 5, 10, 13, 15, 10, 5, 16, 8}),
					  make_tuple(vector<long>{1, 17, 5, 15, 5, 16, 8}, vector<long>{1, 17, 5, 15, 5, 16, 8}),
					  make_tuple(vector<long>{1, 17, 5, 15, 5, 16, 8}, vector<long>{1, 17, 5, 10, 13, 15, 12, 5, 16, 8}),
					  make_tuple(vector<long>{1, 17, 5, 13, 11, 12, 5, 16, 8}, vector<long>{1, 17, 5, 10, 13, 11, 12, 5, 16, 8})));
class ContainsNearbyAlmostDuplicateTestFixture : public testing::TestWithParam<tuple<bool, vector<long>, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_param = get<2>(GetParam());
		_t = get<3>(GetParam());
	}
	bool ContainsNearbyAlmostDuplicateTest()
	{
		return _rangeObj.ContainsNearbyAlmostDuplicate(_data, _param, _t);
	}

protected:
	Range _rangeObj;
	long _param, _t;
	bool _expected;
	vector<long> _data;
};
TEST_P(ContainsNearbyAlmostDuplicateTestFixture, ContainsNearbyAlmostDuplicateTests)
{
	ASSERT_EQ(this->_expected, this->ContainsNearbyAlmostDuplicateTest());
}
INSTANTIATE_TEST_SUITE_P(
	ContainsNearbyAlmostDuplicateTests,
	ContainsNearbyAlmostDuplicateTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 2, 3, 1}, 3, 0),
					  make_tuple(true, vector<long>{1, 0, 1, 1}, 1, 2),
					  make_tuple(false, vector<long>{1, 5, 9, 1, 5, 9}, 2, 3),
					  make_tuple(false, vector<long>{1, 5, 9, 1, 5, 9}, 0, 0),
					  make_tuple(false, vector<long>{1, 5, 9, 1, 5, 9}, 0, 1),
					  make_tuple(true, vector<long>{1, 5, 9, 1, 5, 9}, 3, 0),
					  make_tuple(false, vector<long>{1, 5, 9, 1, 5, 9}, 2, 0),
					  make_tuple(false, vector<long>{1, 5, 9, 1, 5, 9}, -1, -1),
					  make_tuple(true, vector<long>{1, 2, 1}, 2, 0),
					  make_tuple(false, vector<long>{2147483647, -1, 2147483647}, 1, 2147483647),
					  make_tuple(true, vector<long>{2147483647, -1, 2147483647}, 1, 2147483648),
					  make_tuple(false, vector<long>{2147483647, -1, 2147483647}, 1, -2147483647L),
					  make_tuple(false, vector<long>{-2147483648L, 2147483647}, 1, 1),
					  make_tuple(true, vector<long>{4, 1, -1, 6, 5}, 3, 1),
					  make_tuple(true, vector<long>{4, 1, -1, 6, 5}, 3, 2),
					  make_tuple(true, vector<long>{4, 1, -1, 6, 5}, 3, 3),
					  make_tuple(true, vector<long>{4, 1, -1, 6, 5}, 3, 4),
					  make_tuple(true, vector<long>{4, 1, -1, 6, 5}, 3, 5)));
class MinimumBribesTestFixture : public testing::TestWithParam<tuple<long, size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_bribes = get<1>(GetParam());
		_data = get<2>(GetParam());
	}
	long MinimumBribesTest()
	{
		return _rangeObj.MinimumBribes(_bribes, _data);
	}

protected:
	Range _rangeObj;
	long _expected;
	size_t _bribes;
	vector<long> _data;
};
TEST_P(MinimumBribesTestFixture, MinimumBribesTests)
{
	ASSERT_EQ(this->_expected, this->MinimumBribesTest());
}
INSTANTIATE_TEST_SUITE_P(
	MinimumBribesTests,
	MinimumBribesTestFixture,
	::testing::Values(make_tuple(3, 2, vector<long>{2, 1, 5, 3, 4}), make_tuple(-1, 2, vector<long>{2, 5, 1, 3, 4}), make_tuple(4, 3, vector<long>{2, 5, 1, 3, 4}),
					  make_tuple(5, 4, vector<long>{5, 2, 1, 3, 4}), make_tuple(7, 2, vector<long>{1, 2, 5, 3, 7, 8, 6, 4})));
class LastNumbersTestFixture : public testing::TestWithParam<tuple<vector<long>, size_t, long, long>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_n = get<1>(GetParam());
		_a = get<2>(GetParam());
		_b = get<3>(GetParam());
	}
	vector<long> LastNumbersTest()
	{
		return _rangeObj.LastNumbers(_n, _a, _b);
	}

protected:
	Range _rangeObj;
	vector<long> _expected;
	size_t _n;
	long _a, _b;
};
TEST_P(LastNumbersTestFixture, LastNumbersTests)
{
	ASSERT_EQ(this->_expected, this->LastNumbersTest());
}
INSTANTIATE_TEST_SUITE_P(
	LastNumbersTests,
	LastNumbersTestFixture,
	::testing::Values(make_tuple(vector<long>{2, 3, 4}, 3, 1, 2), make_tuple(vector<long>{30, 120, 210, 300}, 4, 10, 100)));

class SherlockAndMinimaxTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>, size_t, size_t>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_p = get<2>(GetParam());
		_q = get<3>(GetParam());
	}
	size_t SherlockAndMinimaxTest()
	{
		return _rangeObj.SherlockAndMinimax(_data, _p, _q);
	}

protected:
	Range _rangeObj;
	size_t _expected, _p, _q;
	vector<size_t> _data;
};
TEST_P(SherlockAndMinimaxTestFixture, SherlockAndMinimaxTests)
{
	ASSERT_EQ(this->_expected, this->SherlockAndMinimaxTest());
}
INSTANTIATE_TEST_SUITE_P(
	SherlockAndMinimaxTests,
	SherlockAndMinimaxTestFixture,
	::testing::Values(make_tuple(4, vector<size_t>{5, 8, 14}, 4, 9),
					  make_tuple(6, vector<size_t>{3, 5, 7, 9}, 6, 8),
					  make_tuple(173959056, vector<size_t>{263044060, 323471968, 60083128, 764550014, 209332334, 735326740, 558683912, 626871620, 232673588, 428805364, 221674872, 261029278, 139767646, 146996700, 200921412, 121542678, 96223500, 239197414, 407346706, 143348970, 60722446, 664904326, 352123022, 291011666, 594294166, 397870656, 60694236, 376586636, 486260888, 114933906, 493037208, 5321608, 90019990, 601686988, 712093982, 575851770, 411329684, 462785470, 563110618, 232790384, 511246848, 521904074, 550301294, 142371172, 241067834, 14042944, 249208926, 36834004, 69321106, 467588012, 92173320, 360474676, 221615472, 340320496, 62541478, 360772498, 372355942, 445408968, 342087972, 685617022, 307398890, 437939090, 720057720, 718957462, 387059594, 583359512, 589920332, 500463226, 770726204, 434976772, 567860154, 510626506, 614077600, 620953322, 570332092, 623026436, 502427638, 640333172, 370673998}, 70283784, 302962359)));

class ChiefHopperChallengeTestFixture : public testing::TestWithParam<tuple<size_t, vector<size_t>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t ChiefHopperChallengeTest()
	{
		return _rangeObj.ChiefHopper(_data);
	}

protected:
	Range _rangeObj;
	vector<size_t> _data;
	size_t _expected;
};
TEST_P(ChiefHopperChallengeTestFixture, ChiefHopperChallengeTests)
{
	ASSERT_EQ(this->_expected, this->ChiefHopperChallengeTest());
}
INSTANTIATE_TEST_SUITE_P(
	ChiefHopperChallengeTests,
	ChiefHopperChallengeTestFixture,
	::testing::Values(make_tuple(3, vector<size_t>{2, 3, 4, 3, 2}), make_tuple(4, vector<size_t>{3, 4, 3, 2, 4}), make_tuple(4, vector<size_t>{4, 4, 4}), make_tuple(3, vector<size_t>{1, 6, 4})));