#include "stdafx.h"
#include "DiamondProblem.h"
DiamondBase::DiamondBase()
{
	cout << "DiamondBase::DiamondBase()" << endl;
}
DiamondBase::DiamondBase(string str)
	:value_(str)
{
	cout << "DiamondBase::DiamondBase(" << str << ")" << endl;
}
DiamondBase::~DiamondBase()
{
	cout << "DiamondBase::~DiamondBase()" << endl;
}
void DiamondBase::Write()
{
	cout << "DiamondBase::Write()" << endl;
}
void DiamondBase::Write(string str)
{
	value_ = str;
}
string DiamondBase::Read()
{
	return value_;
}
Transmitter::Transmitter()
	:DiamondBase("")
{
	cout << "Transmitter::Transmitter()" << endl;
}
Transmitter::Transmitter(string str)
	: DiamondBase(str)
{
	cout << "Transmitter::Transmitter(" << str << ")" << endl;
}

Transmitter::~Transmitter()
{
	cout << "Transmitter::~Transmitter()" << endl;
}
void Transmitter::Write()
{
	value_ = Read();
}
Receiver::Receiver()
	:DiamondBase("")
{
	cout << "Receiver::Receiver()" << endl;
}
Receiver::Receiver(string str)
	: DiamondBase(str)
{
	cout << "Receiver::Receiver(" << str << ")" << endl;
}

Receiver::~Receiver()
{
	cout << "Receiver::~Receiver()" << endl;
}

string Receiver::Read()
{
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