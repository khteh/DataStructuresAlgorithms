#pragma once
class Square
{
private:
	long x, y;
	size_t width, height;

public:
	Square() = default;
	Square(int, int, size_t, size_t);
	void SetCoordinates(int, int);
	void SetWidth(size_t);
	void SetHeight(size_t);
	virtual ~Square() = default;
	bool IsOverlappig(Square &);
};
