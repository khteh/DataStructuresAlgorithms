#include "pch.h"
#include "Call.h"

Call::Call(Employee::Rank r)
	: rank_((int)r)
{
}

Call::Call(Call &call)
	: rank_(call.rank_)
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