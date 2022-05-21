#include "pch.h"
using namespace std;
template <typename T>
void SortStack(MyStack<T>& src, MyStack<T>& dest, sort_order_t order)
{
	T item;
	while (!src.isEmpty())
	{
		item = src.pop();
		switch (order)
		{
		case SortOrder::SORT_ASCENDING: // Value grows from bottom of stack to top of stack
			while (!dest.isEmpty() && item < dest.peek())
				src.push(dest.pop());
			break;
		case SortOrder::SORT_DESCENDING: // Value shrinks from bottom of stack to top of stack
			while (!dest.isEmpty() && item > dest.peek())
				src.push(dest.pop());
			break;
		default:
			throw runtime_error("Invalid sort order");
			break;
		}
		dest.push(item);
	}
}

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
	SortStack<int>(stack, sortedStack, sort_order_t::SORT_ASCENDING);
	cout << "Stack content (Ascending): ";
	sortedStack.PrintStack();
	sortedStack.clear();
	SortStack<int>(unSortedStack, sortedStack, sort_order_t::SORT_DESCENDING);
	cout << "Stack content (Descending): ";
	sortedStack.PrintStack();
}