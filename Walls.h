#ifndef WALLS_H
#define WALLS_H

#include "Position.h"
#include <vector>
using std::vector;

class Walls
{
public:
    Walls();
    void addRocks(Position dotPos, int dir);
    void chooseRocks(Position dotPos, int dir);
    vector<Position> rocks;
};

#endif // WALLS_H
