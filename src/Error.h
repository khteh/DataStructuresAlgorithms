#pragma once
using namespace std;
class Error
{
public:
	explicit Error(string msg);
	Error(const Error &);
	virtual ~Error();
	string msg_;
};

class ErrorDerived : public Error
{
public:
	explicit ErrorDerived(string msg);
	ErrorDerived(const ErrorDerived &);
	virtual ~ErrorDerived();
};