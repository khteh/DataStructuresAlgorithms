#include "pch.h"
#include "NameHidingExample.h"
#include <string>
#include <iostream>
using namespace std;
NameHidingExample::NameHidingExample(void)
	: var_(0)
{
}

NameHidingExample::NameHidingExample(long var)
	: var_(var)
{
}

NameHidingExample::~NameHidingExample(void)
{
}

void NameHidingExample::Print(long var)
{
	var_ = var;
	cout << "[" << __FUNCTION__ << " " << __LINE__ << "] var_: " << hex << var_ << dec << endl;
}

void NameHidingExample::Print(long var, long var1)
{
	var_ = var + var1;
	cout << "[" << __FUNCTION__ << " " << __LINE__ << "] var_: " << hex << var_ << dec << endl;
}

NameHidingExampleDerived::NameHidingExampleDerived(void)
{
}

NameHidingExampleDerived::NameHidingExampleDerived(long var)
	: NameHidingExample(var)
{
}

NameHidingExampleDerived::~NameHidingExampleDerived(void)
{
}

void NameHidingExampleDerived::Print(long var)
{
	var_ = var + 1;
	cout << "[" << __FUNCTION__ << " " << __LINE__ << "] var_: " << hex << var_ << dec << endl;
}