#include "pch.h"
#include "DiamondProblem.h"
DiamondBase::DiamondBase()
{
	//cout << "DiamondBase::DiamondBase()" << endl;
}
DiamondBase::DiamondBase(string str)
	:value_(str)
{
	//cout << "DiamondBase::DiamondBase(" << str << ")" << endl;
}
DiamondBase::~DiamondBase()
{
	//cout << "DiamondBase::~DiamondBase()" << endl;
}
void DiamondBase::Write()
{
	//cout << "DiamondBase::Write() value: " << value_ << endl;
}
void DiamondBase::Write(string str)
{
	//cout << "DiamondBase::Write() value: " << value_ << ", str: " << str << endl;
	value_ = str;
}
string DiamondBase::Read()
{
	//cout << "DiamondBase::Read() value: " << value_ << endl;
	return value_;
}
Transmitter::Transmitter()
	:DiamondBase("")
{
	//cout << "Transmitter::Transmitter()" << endl;
}
Transmitter::Transmitter(string str)
	: DiamondBase(str)
{
	//cout << "Transmitter::Transmitter(" << str << ")" << endl;
}
Transmitter::~Transmitter()
{
	//cout << "Transmitter::~Transmitter()" << endl;
}
void Transmitter::Write()
{
	//cout << "Transmitter::Write() value: " << value_ << endl;
	value_ = Read();
	//cout << "Transmitter::Write() value: " << value_ << endl;
}
Receiver::Receiver()
	:DiamondBase("")
{
	//cout << "Receiver::Receiver()" << endl;
}
Receiver::Receiver(string str)
	: DiamondBase(str)
{
	//cout << "Receiver::Receiver(" << str << ")" << endl;
}
Receiver::~Receiver()
{
	//cout << "Receiver::~Receiver()" << endl;
}
string Receiver::Read()
{
	//cout << "Receiver::Read() value: " << value_ << endl;
	return "Receiver: " + value_;
}
Radio::Radio()
{
}
Radio::Radio(string str)
	:DiamondBase(str)
	, Transmitter(str)
	, Receiver(str)
{
}
Radio::~Radio()
{
}