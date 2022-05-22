#include "stdafx.h"
#include "Employee.h"

Employee::Employee(Rank r)
	: rank_(r)
{
}

Employee::~Employee(void)
{
}

Employee::Rank Employee::rank()
{
	return rank_;
}

bool Employee::ReceiveCall(Call &call)
{
	if (isAvailable()) {
		status_ = Status::BUSY;
		return true;
	}
	return false;
}

bool Employee::isAvailable()
{
	return status_ == Status::FREE;
}