#include "stdafx.h"
#include "Call.h"
#include "Employee.h"

Call::Call(Employee::Rank r)
	: rank_((int)r)
{
}

Call::Call(Call& call)
	: rank_(call.rank_)
{
}

Call::~Call(void)
{
}

Employee::Rank Call::rank()
{
	return (Employee::Rank)rank_;
}

void Call::EscalateCall()
{
	if (rank_ < (int)Employee::Rank::MANAGER)
		rank_++;
}