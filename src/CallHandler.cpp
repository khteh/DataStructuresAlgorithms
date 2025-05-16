#include "pch.h"
#include "CallHandler.h"
#include "Call.h"
#include "Employee.h"
using namespace std;

CallHandler::CallHandler(void)
{
}

CallHandler::~CallHandler(void)
{
}

bool CallHandler::dispatch(Call& call)
{
	for (int rank = (int)call.rank(); rank <= (int)Employee::Rank::MANAGER; rank++) {
		for (vector<Employee>::iterator it = employees_[rank].begin(); it != employees_[rank].end(); it++)
			if (it->ReceiveCall(call))
				return true;
	}
	pendingCalls_[(int)call.rank()].push(&call);
	return false;
}

Call* CallHandler::nextCall(Employee &e)
{
	Call *call(nullptr);
	if (!pendingCalls_[(int)e.rank()].empty()) {
		call = pendingCalls_[(int)e.rank()].front();
		pendingCalls_[(int)e.rank()].pop();
	}
	return call;
}