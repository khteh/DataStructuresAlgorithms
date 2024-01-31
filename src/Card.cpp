#include "stdafx.h"
#include "Card.h"

Card::Card(int v, Suit s)
	: value_(v)
	, suit_(s)
{
}

Card::~Card(void)
{
}

int Card::value()
{
	return value_;
}

Card::Suit Card::suit()
{
	return suit_;
}