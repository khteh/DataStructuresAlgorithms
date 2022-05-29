#include "pch.h"
using namespace std;
TEST(TreeTests, TreeArithmeticTotalDoubleTest) {
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
	ASSERT_EQ(-3, tree.TreeArithmeticTotal<double>(multiplier));
	adder->SetLeft(num5);
	adder->SetRight(num6);
	minus->SetLeft(num7);
	minus->SetRight(num8);
	// (1.2 + 2.3) * (3.4 - 4.5) = 3.5 * -1.1 = -3.85
	double expected = (1.2 + 2.3) * (3.4 - 4.5);
	ASSERT_LT(fabs(tree.TreeArithmeticTotal<double>(multiplier) - expected), numeric_limits<double>::epsilon());
}