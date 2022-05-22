#pragma once
#include <string>
using namespace std;
class Error
{
public:
	Error(string msg);
	Error(const Error&);
	virtual ~Error();
	string msg_;
};

class ErrorDerived : public Error
{
public:
	ErrorDerived(string msg);
	ErrorDerived(const ErrorDerived&);
	virtual ~ErrorDerived();
};