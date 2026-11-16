#pragma once
#include "Call.h"
#include "Employee.h"
using namespace std;
class CallHandler
{
public:
	CallHandler(void) = default;
	virtual ~CallHandler(void) = default;
	bool dispatch(Call &);
	Call *nextCall(Employee &);

private:
	std::vector<std::vector<Employee>> employees_;
	std::vector<std::queue<Call *>> pendingCalls_;
};