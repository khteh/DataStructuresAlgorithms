#include "pch.h"
#include "DiamondProblem.h"
DiamondBase::DiamondBase(string str)
	: value_(move(str))
{
}
void DiamondBase::Write()
{
}
void DiamondBase::Write(string str)
{
	value_ = move(str);
}
string DiamondBase::Read()
{
	return value_;
}
Transmitter::Transmitter()
	: DiamondBase("")
{
}
Transmitter::Transmitter(string str)
	: DiamondBase(move(str))
{
}
void Transmitter::Write()
{
	value_ = Read();
}
Receiver::Receiver()
	: DiamondBase("")
{
}
Receiver::Receiver(string str)
	: DiamondBase(move(str))
{
}
string Receiver::Read()
{
	return "Receiver: " + value_;
}
Radio::Radio(string str)
	: DiamondBase(str), Transmitter(str), Receiver(str)
{
}
