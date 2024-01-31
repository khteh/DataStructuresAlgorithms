#include "stdafx.h"
#include "Poker.h"

Poker::Poker(int v, Suit s)
	: Card(v % 52, s)
{
}

Poker::~Poker(void)
{
}