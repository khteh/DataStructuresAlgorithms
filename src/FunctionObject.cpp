#include "pch.h"
#include "FunctionObject.h"
struct Foo {
	Foo(int num) : num_(num) {}
	void print_add(int i) const { cout << num_ + i << '\n'; }
	int num_;
};

void print_num(int i)
{
	cout << i << '\n';
}

struct PrintNum {
	void operator()(int i) const
	{
		cout << i << '\n';
	}
};

FunctionObject::FunctionObject()
{
	cout << "Function object demo: " << endl;
	// store a free function
	function<void(int)> f_display = print_num;
	f_display(-9);

	// store a lambda
	function<void()> f_display_42 = []() { print_num(42); };
	f_display_42();

	// store the result of a call to bind
	function<void()> f_display_31337 = bind(print_num, 31337);
	f_display_31337();

	// store a call to a member function
	function<void(const Foo&, int)> f_add_display = &Foo::print_add;
	const Foo foo(314159);
	f_add_display(foo, 1);
	f_add_display(12345, 1);

	// store a call to a data member accessor
	function<int(Foo const&)> f_num = &Foo::num_;
	cout << "num_: " << f_num(foo) << '\n';

	// store a call to a member function and object
	using placeholders::_1;
	function<void(int)> f_add_display2 = bind(&Foo::print_add, foo, _1);
	f_add_display2(2);

	// store a call to a member function and object ptr
	function<void(int)> f_add_display3 = bind(&Foo::print_add, &foo, _1);
	f_add_display3(3);

	// store a call to a function object
	function<void(int)> f_display_obj = PrintNum();
	f_display_obj(18);
}

