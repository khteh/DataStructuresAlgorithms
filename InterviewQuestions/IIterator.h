#pragma once
template<class T>
class IIterator
{
public:
	virtual bool HasNext() = 0;
	virtual T Next() = 0;
	virtual T Remove() = 0;
};