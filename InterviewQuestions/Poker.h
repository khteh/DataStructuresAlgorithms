#pragma once
#include "card.h"

class Poker :	public Card
{
public:
	Poker(int, Suit);
	virtual ~Poker(void);
};