#include "Walls.h"
#include <cstdlib>

Walls::Walls()
{
    Position tryP1(5,5);
    Position tryP2(5,6);
    Position tryP3(5,7);
    Position tryP4(5,8);
    rocks.push_back(tryP1);
    rocks.push_back(tryP2);
    rocks.push_back(tryP3);
    rocks.push_back(tryP4);
}

void Walls::addRocks(Position dotPos)
{
    Position nRpos;
    int ifValid;
    do
    {
        ifValid = 1;
        nRpos.x = rand()%25;
        nRpos.y = rand()%25;


        for (int i=0; i<rocks.size(); i++)
        {\
            if (rocks[i].x==nRpos.x && rocks[i].y==nRpos.y)
            {
                ifValid = 0;
                break;
            }
        }
        if (nRpos.x==dotPos.x && nRpos.y==dotPos.y) ifValid = 0;
    } while (!ifValid);
\
    rocks.push_back(nRpos);
}
