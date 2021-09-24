#pragma once
#include "Card.h"

class Poker :	public Card
{
public:
	Poker(int, Suit);
	virtual ~Poker(void);
};