#include "pch.h"
#include "TreasureGame.h"
Door::Door(Room *r, int lock)
	: next_(r), lock_(lock)
{
}
Door::~Door()
{
}
Room::Room(bool hasTreasure)
	: hasTreasure_(hasTreasure), lock_(-1)
{
}
Room::Room(int lock)
	: hasTreasure_(false), lock_(lock)
{
}
Room::~Room()
{
}
void Room::addDoor(Room *next, int lock)
{
	if (next != this)
	{
		bool found = false;
		for (vector<Door>::iterator it = doors_.begin(); it != doors_.end(); it++)
		{
			if (it->next_ == next)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			doors_.push_back({next, lock});
			next->doors_.push_back({this, lock});
		}
	}
}
TreasureGame::TreasureGame()
{
}
TreasureGame::~TreasureGame()
{
}
// You are a game developer working on a game that randomly generates levels. A level is an undirected graph of rooms, each connected by doors. The player starts in one room, and there is a treasure in another room. Some doors are locked, and each lock is opened by a unique key. A room may contain one of those unique keys, or the treasure, or nothing.
// Implement a representation for a level and write code that, given a level and starting room, returns true if the treasure can be reached by the player�likely requiring them to find certain other keys first�or false if there is no solution.
bool TreasureGame::hasTreasure(Room const *start)
{
	map<int, vector<Room const *>> lockedRooms;
	set<int> keys = {{-1}};
	set<Room const *> visited;
	stack<Room const *> rooms{{start}};
	while (rooms.size())
	{
		Room const *r = rooms.top();
		rooms.pop();
		if (r->hasTreasure_)
			return true;
		if (!visited.count(r))
		{
			visited.insert(r);
			if (!keys.count(r->lock_))
			{
				keys.insert(r->lock_);
				map<int, vector<Room const *>>::iterator it = lockedRooms.find(r->lock_);
				if (it != lockedRooms.end())
				{
					for (vector<Room const *>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
						rooms.push(*it1);
					it->second.clear();
				}
			}
			for (vector<Door>::const_iterator it = r->doors_.begin(); it != r->doors_.end(); it++)
			{
				if (!visited.count(it->next_))
				{
					if (keys.count(it->lock_))
						rooms.push(it->next_);
					else
						lockedRooms[it->lock_].push_back(it->next_);
				}
			}
		}
	}
	return false;
}