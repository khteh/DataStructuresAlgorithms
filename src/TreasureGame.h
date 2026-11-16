#pragma once
class Room;
class Door
{
public:
	Door(Room *, int);
	virtual ~Door() = default;
	Room *next_;
	int lock_;
};
class Room
{
public:
	Room(bool);
	Room(int);
	virtual ~Room() = default;
	void addDoor(Room *, int key = -1);
	bool hasTreasure_;
	int lock_ = -1;
	vector<Door> doors_;
};
class TreasureGame
{
public:
	TreasureGame() = default;
	virtual ~TreasureGame() = default;
	bool hasTreasure(Room const *);
};