#pragma once
#include <string>
#include <iostream>
using namespace std;
class DiamondBase
{
public:
	DiamondBase();
	DiamondBase(string);
	virtual ~DiamondBase();
	virtual void Write();
	virtual void Write(string);
	virtual string Read();// = 0;
protected:
	string value_;
};

class Transmitter : public virtual DiamondBase
{
public:
	Transmitter();
	Transmitter(string);
	~Transmitter();
	using DiamondBase::Write;
	void Write();
};

class Receiver : public virtual DiamondBase
{
public:
	Receiver();
	Receiver(string);
	~Receiver();
	string Read(void);
};

class Radio : public Transmitter, public Receiver
{
public:
	Radio();
	Radio(string);
	~Radio();
};