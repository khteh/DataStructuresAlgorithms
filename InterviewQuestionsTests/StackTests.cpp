#include "pch.h"
using namespace std;
TEST(StackTests, StackTest) {
	MyStack<int> stack, sortedStack;
	stack.push(100);
	stack.push(-100);
	stack.push(0);
	stack.push(-50);
	stack.push(50);
	stack.push(-1);
	stack.push(1);
	stack.push(-75);
	stack.push(75);
	stack.push(25);
	cout << "Stack content: ";
	stack.PrintStack();

	MyStack<int> unSortedStack(stack);
	MyStack<int>::SortStack(stack, sortedStack, sort_order_t::SORT_ASCENDING);
	cout << "Stack content (Ascending): ";
	sortedStack.PrintStack();
	sortedStack.clear();
	MyStack<int>::SortStack(unSortedStack, sortedStack, sort_order_t::SORT_DESCENDING);
	cout << "Stack content (Descending): ";
	sortedStack.PrintStack();
}