#pragma once
#include <compare>
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
    /*
     * Compares row first, then col, in member declaration order. Defaulting <=> also defaults ==,
     * and !=, <, <=, > and >= are rewritten from those two.
     * This replaces operator>, which was wrong: its "row == row" was always true, so {0,5} > {1,0} was true.
     */
    auto operator<=>(Position const &) const = default;
    // The operator must be a non-member friend function
    friend ostream &operator<<(ostream &os, const Position &pos)
    {
        return os << "[" << pos.row << "," << pos.col << "]";
    }
} position_t;