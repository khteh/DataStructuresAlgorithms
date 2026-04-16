#include "pch.h"
using namespace std;
template <typename T1, typename T2>
class TreeTestFixture1
{
public:
	void SetUp(T1 expected, vector<T2> data, TreeType type)
	{
		_expected = expected;
		_data = data;
		_type = type;
		_tree = Tree(_data, _type);
	}

protected:
	TreeType _type;
	Tree<T2> _tree;
	vector<T2> _data;
	T1 _expected;
};

TEST(TreeTests, TreeArithmeticTotalDoubleTest)
{
	Tree<double> tree;
	shared_ptr<Node<string>> multiplier = make_shared<Node<string>>("*");
	shared_ptr<Node<string>> adder = make_shared<Node<string>>("+");
	shared_ptr<Node<string>> minus = make_shared<Node<string>>("-");
	shared_ptr<Node<string>> num1 = make_shared<Node<string>>("1"), num2 = make_shared<Node<string>>("2"), num3 = make_shared<Node<string>>("3"), num4 = make_shared<Node<string>>("4");
	shared_ptr<Node<string>> num5 = make_shared<Node<string>>("1.2"), num6 = make_shared<Node<string>>("2.3"), num7 = make_shared<Node<string>>("3.4"), num8 = make_shared<Node<string>>("4.5");
	adder->SetLeft(num1);
	adder->SetRight(num2);
	minus->SetLeft(num3);
	minus->SetRight(num4);
	multiplier->SetLeft(adder);
	multiplier->SetRight(minus);
	// (1 + 2) * (3 - 4) = 3 * -1 = -3
	ASSERT_EQ(-3, tree.TreeArithmeticTotal(multiplier));
	adder->SetLeft(num5);
	adder->SetRight(num6);
	minus->SetLeft(num7);
	minus->SetRight(num8);
	// (1.2 + 2.3) * (3.4 - 4.5) = 3.5 * -1.1 = -3.85
	double expected = (1.2 + 2.3) * (3.4 - 4.5);
	ASSERT_LT(fabs(tree.TreeArithmeticTotal(multiplier) - expected), numeric_limits<double>::epsilon());
}
class IsValidPreOrderTreeSerializationTestFixture : public testing::TestWithParam<tuple<bool, string>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_var = get<1>(GetParam());
	}
	bool IsValidPreOrderTreeSerializationTest()
	{
		return _tree.IsValidPreOrderTreeSerialization(_var);
	}

protected:
	Tree<string> _tree;
	bool _expected;
	string _var;
};
TEST_P(IsValidPreOrderTreeSerializationTestFixture, IsValidPreOrderTreeSerializationTests)
{
	ASSERT_EQ(this->_expected, this->IsValidPreOrderTreeSerializationTest());
}
INSTANTIATE_TEST_SUITE_P(
	IsValidPreOrderTreeSerializationTests,
	IsValidPreOrderTreeSerializationTestFixture,
	::testing::Values(make_tuple(false, "1"), make_tuple(true, "#"), make_tuple(true, "1,#,#"), make_tuple(true, "9,3,4,#,#,1,#,#,2,#,6,#,#"), make_tuple(true, "9,#,93,#,9,9,#,#,#"), make_tuple(true, "9,9,9,19,#,9,#,#,#,9,#,69,#,#,#")));
TEST(TreeTests, FenwickTreeTest)
{
	vector<size_t> udata;
	FenwickTree<size_t> fenwickTree;
	udata = {2, 1, 3, 1, 2};
	fenwickTree.Construct(udata);
	ASSERT_EQ(2, fenwickTree.Query(1)); // f(1)
	ASSERT_EQ(4, fenwickTree.Query(2)); // f(2)
	ASSERT_EQ(5, fenwickTree.Query(3)); // f(3) = f(3) + f(2) = 5

	udata.clear();
	udata = {4, 3, 2, 1};
	fenwickTree.Construct(udata);
	ASSERT_EQ(1, fenwickTree.Query(1)); // f(1)
	ASSERT_EQ(2, fenwickTree.Query(2)); // f(2)
	ASSERT_EQ(3, fenwickTree.Query(3)); // f(3) = f(3) + f(2) = 2 + 1 = 3
	ASSERT_EQ(4, fenwickTree.Query(4)); // f(2)
}
class InsertionSortShiftCountTestFixture : public testing::TestWithParam<tuple<size_t, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
	}
	size_t InsertionSortShiftCountTest()
	{
		return _tree.InsertionSortShiftCount(_data);
	}

protected:
	FenwickTree<long> _tree;
	size_t _expected;
	vector<long> _data;
};
TEST_P(InsertionSortShiftCountTestFixture, InsertionSortShiftCountTests)
{
	ASSERT_EQ(this->_expected, this->InsertionSortShiftCountTest());
}
INSTANTIATE_TEST_SUITE_P(
	InsertionSortShiftCountTests,
	InsertionSortShiftCountTestFixture,
	::testing::Values(make_tuple(0, vector<long>{1, 1, 1, 2, 2}), make_tuple(4, vector<long>{2, 1, 3, 1, 2}), make_tuple(6, vector<long>{4, 3, 2, 1}), make_tuple(4, vector<long>{9492052, 241944, 5743396, 5758608, 6053545})));

class TreeMaxPathSumTestFixture : public TreeTestFixture1<long, long>, public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		TreeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()), TreeType::Binary);
	}
	long TreeMaxPathSumTest()
	{
		_tree.PrintTree();
		return _tree.MaxPathSum();
	}
};
TEST_P(TreeMaxPathSumTestFixture, TreeMaxPathSumTests)
{
	ASSERT_EQ(this->_expected, this->TreeMaxPathSumTest());
}
INSTANTIATE_TEST_SUITE_P(
	TreeMaxPathSumTests,
	TreeMaxPathSumTestFixture,
	::testing::Values(make_tuple(-10, vector<long>{-10}), make_tuple(6, vector<long>{1, 2, 3}), make_tuple(42, vector<long>{-10, 9, 20, numeric_limits<long>::min(), numeric_limits<long>::min(), 15, 7}),
					  make_tuple(2, vector<long>{2, -1, -2}), make_tuple(48, vector<long>{5, 4, 8, 11, numeric_limits<long>::min(), 13, 4, 7, 2, numeric_limits<long>::min(), numeric_limits<long>::min(), numeric_limits<long>::min(), numeric_limits<long>::min(), 1}),
					  make_tuple(3, vector<long>{1, -2, -3, 1, 3, -2, numeric_limits<long>::min(), -1})));

class RecoverBinarySearchTreeTestFixture : public TreeTestFixture1<bool, long>, public testing::TestWithParam<tuple<bool, vector<long>>>
{
public:
	void SetUp() override
	{
		TreeTestFixture1::SetUp(get<0>(GetParam()), get<1>(GetParam()), TreeType::Binary);
	}
	bool RecoverBinarySearchTreeTest()
	{
		_tree.PrintTree();
		return _tree.RecoverBinarySearchTree();
	}
};
TEST_P(RecoverBinarySearchTreeTestFixture, RecoverBinarySearchTreeTests)
{
	ASSERT_EQ(this->_expected, this->RecoverBinarySearchTreeTest());
}
INSTANTIATE_TEST_SUITE_P(
	RecoverBinarySearchTreeTests,
	RecoverBinarySearchTreeTestFixture,
	::testing::Values(make_tuple(true, vector<long>{1, 3, numeric_limits<long>::min(), numeric_limits<long>::min(), 2}), make_tuple(true, vector<long>{3, 1, 4, numeric_limits<long>::min(), numeric_limits<long>::min(), 2}),
					  make_tuple(true, vector<long>{5, 3, 2, 10, 4, numeric_limits<long>::min(), numeric_limits<long>::min()})));
