#include "pch.h"
#include "Square.h"


Square::Square()
{
}

Square::Square(int x1, int y1, size_t width1, size_t height1)
	: x(x1)
	, y(y1)
	, width(width1)
	, height(height1)
{
}
Square::~Square()
{
}

bool Square::IsOverlappig(Square &other)
{
	bool result1 = other.x >= x && other.y >= y && other.x <= (long)(x + width) && other.y <= (long)(y + height); // other's top left falls within this area
	bool result2 = other.x >= x && other.y <= y && other.x <= (long)(x + width) && (long)(other.y + other.height) <= (long)(y + height); // other's bottom left falls within this area
	bool result3 = other.x <= x && other.y >= y && (long)(other.x + other.width) <= (long)(x + width) && other.y <= (long)(y + height); // other's top right falls within this area
	bool result4 = other.x <= x && other.y <= y && (long)(other.x + other.width) >= x && (long)(other.y + other.height) >= y; // other's bottom right falls within this area
	return result1 | result2 | result3 | result4;
}

void Square::SetCoordinates(int x1, int y1)
{
	x = x1;
	y = y1;
}
void Square::SetWidth(size_t w)
{
	width = w;
}
void Square::SetHeight(size_t h)
{
	height = h;
}