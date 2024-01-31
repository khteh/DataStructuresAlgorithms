#pragma once
#include <string>
using namespace std;
class Singleton
{
public:
	static Singleton* Instance();
	void Print(string);
protected:
	Singleton();
	virtual ~Singleton();
private:
	static Singleton* _instance;
};