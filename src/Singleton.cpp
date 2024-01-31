#include "stdafx.h"
#include "Singleton.h"
#include <iostream>
using namespace std;
Singleton* Singleton::_instance = nullptr;
Singleton::Singleton()
{
}
Singleton::~Singleton()
{
	if (_instance) {
		//delete _instance; This will call Singleton::~Singleton() again! :/
		_instance = nullptr;
	}
}

Singleton* Singleton::Instance()
{
	if (!_instance)
		_instance = new Singleton();
	return _instance;
}

void Singleton::Print(string str)
{
	cout << "[" << __FUNCTION__ << " " << __LINE__ << "]: " << str << endl;
}