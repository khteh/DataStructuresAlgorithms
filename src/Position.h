#pragma once
#include <ranges>
#include <sstream>
using namespace std;
namespace ranges = std::ranges;
typedef struct Position
{
    Position() : row(0), col(0) {}
    Position(long r, long c) : row(r), col(c) {}
    long row;
    long col;
    Position &operator=(Position rhs)
    {
        row = rhs.row;
        col = rhs.col;
        return *this;
    }
    bool operator==(Position rhs) const { return row == rhs.row && col == rhs.col; }
    bool operator!=(Position const &rhs) const { return !(*this == rhs); }
    bool operator<(Position const &rhs) const { return row < rhs.row || (row == rhs.row && col < rhs.col); }
    bool operator>(Position const &rhs) const { return row > rhs.row || (row == row && col > rhs.col); }
    // The operator must be a non-member friend function
    friend ostream &operator<<(ostream &os, const Position &pos)
    {
        return os << "[" << pos.row << "," << pos.col << "]";
    }
} position_t;