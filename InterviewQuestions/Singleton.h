#pragma once

class Singleton
{
public:
	static Singleton& instance();
	void print();
protected:
	Singleton(void);
	Singleton(Singleton const&);
	void operator=(Singleton const&);
	virtual ~Singleton(void);
};