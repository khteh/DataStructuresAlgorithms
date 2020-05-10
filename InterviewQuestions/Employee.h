#pragma once
class Call;

class Employee
{
public:
	enum class Rank : int { FRESHER = 0, LEAD, MANAGER };
	enum class Status { FREE, BUSY };
	Employee(Rank r = Rank::FRESHER);
	virtual ~Employee(void);
	bool ReceiveCall(Call &);
	Rank rank();
	bool isAvailable();
private:
	Rank rank_;
	Status status_;
};