#pragma once
class NameHidingExample
{
protected:
	long var_;
public:
	NameHidingExample(void);
	explicit NameHidingExample(long);
	virtual ~NameHidingExample(void) = default;
	void Print(long);
	virtual void Print(long, long);
};

class NameHidingExampleDerived : public NameHidingExample
{
public:
	NameHidingExampleDerived(void) = default;
	explicit NameHidingExampleDerived(long);
	virtual ~NameHidingExampleDerived(void) = default;
	void Print(long);
	//virtual void Hide(long, long);
};