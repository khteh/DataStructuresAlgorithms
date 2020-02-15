#pragma once
class Card
{
public:
	enum Suit { DIAMOND, CLUB, HEART, SPADE	};
	Card(int, Suit);
	virtual ~Card(void);
	int value();
	Suit suit();

private:
	int value_;
	Suit suit_;
};

