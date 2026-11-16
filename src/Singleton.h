#pragma once
class Singleton
{
public:
	static Singleton *Instance();
	void Print(string);

protected:
	Singleton() = default;
	virtual ~Singleton();

private:
	static Singleton *_instance;
};