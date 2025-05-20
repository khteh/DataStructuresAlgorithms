#pragma once
class Room;
class Door
{
public:
	Door(Room *, int);
	virtual ~Door();
	Room *next_;
	int lock_;
};
class Room
{
public:
	Room(bool);
	Room(int);
	virtual ~Room();
	void addDoor(Room *, int key = -1);
	bool hasTreasure_;
	int lock_ = -1;
	vector<Door> doors_;
};
class TreasureGame
{
public:
	TreasureGame();
	virtual ~TreasureGame();
	bool hasTreasure(Room const *);
};