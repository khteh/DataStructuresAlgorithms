#include "pch.h"
using namespace std;
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
