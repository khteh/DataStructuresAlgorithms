#pragma once
class Employee;
class Call;

class CallHandler
{
public:
	CallHandler(void);
	virtual ~CallHandler(void);
	bool dispatch(Call &);
	Call *nextCall(Employee &);

private:
	std::vector<std::vector<Employee>> employees_;
	std::vector<std::queue<Call *>> pendingCalls_;
};