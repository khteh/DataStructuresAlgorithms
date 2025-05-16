#include "pch.h"
#include "Error.h"
#include <string>
#include <iostream>
using namespace std;
Error::Error(string msg)
{
	msg_ = msg;
	cout << "Error() @" << this << endl;
}
Error::Error(const Error& other)
{
	msg_ = other.msg_;
	cout << "Error(const Error&) this@" << this << " that@" << &other << endl;
}
Error::~Error()
{
	cout << "~Error() @" << this << endl;
}
ErrorDerived::ErrorDerived(string msg)
	: Error(msg)
{
	cout << "ErrorDerived() @" << this << endl;
}
ErrorDerived::ErrorDerived(const ErrorDerived& other)
	: Error(other)
{
	cout << "ErrorDerived(const ErrorDerived&) this@" << this << " that@" << &other << endl;
}
ErrorDerived::~ErrorDerived()
{
	cout << "~ErrorDerived() @" << this << endl;
}