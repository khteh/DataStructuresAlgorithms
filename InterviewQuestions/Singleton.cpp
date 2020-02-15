#include "stdafx.h"
#include "Singleton.h"
#include <iostream>
using namespace std;

Singleton::Singleton(void)
{
}

Singleton::~Singleton(void)
{
}

Singleton& Singleton::instance()
{
	static Singleton instance_;
	return instance_;
}

void Singleton::print()
{
	cout << "[" << __FUNCTION__ << " " << __LINE__ << "]" << endl;
}