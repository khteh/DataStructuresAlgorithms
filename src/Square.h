#pragma once
class Square
{
private:
	long x, y;
	size_t width, height;
public:
	Square();
	Square(int, int, size_t, size_t);
	void SetCoordinates(int, int);
	void SetWidth(size_t);
	void SetHeight(size_t);
	virtual ~Square();
	bool IsOverlappig(Square &);
};

