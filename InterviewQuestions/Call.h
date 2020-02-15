#pragma once
#include "Employee.h"

class Call
{
public:
	Call(Employee::Rank = Employee::Rank::FRESHER);
	Call(Call&);
	virtual ~Call(void);
	void Connect();
	void Disconnect();
	Employee::Rank rank();
	void EscalateCall();
private:
	int rank_; // Employee rank to take the call
};