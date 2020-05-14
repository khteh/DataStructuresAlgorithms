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
	using DiamondBase::Write; // https://en.cppreference.com/w/cpp/language/using_declaration
	void Write(); // Transmitter::Write(int) overrides DiamondBase::Write(int)
};

class Receiver : public virtual DiamondBase
{
public:
	Receiver();
	Receiver(string);
	~Receiver();
	string Read();
};

class Radio : public Transmitter, public Receiver
{
public:
	Radio();
	Radio(string);
	~Radio();
};