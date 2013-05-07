#include "Walls.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

Walls::Walls()
{
    rocks.clear();
}

void Walls::chooseRocks(Position dotPos, int dir)
{
    std::cout << dir << std::endl;
    int tx=dotPos.x,ty=dotPos.y;
    int value[25][25];
    for ( int p=0; p<25; p++ )
        for ( int q=0; q<25; q++ )
            value[p][q]=0;
    for ( int p=0; p<25; p++ )
    {
        for ( int q=0; q<25; q++ )
        {

        }

        //for ( int q=0; q<25; q++ ) value[p][q] += abs(p-12)>=abs(q-12)?abs(p-12):abs(q-12);

    }

    switch (dir) {
    case 1:
    {
        for( int s=0; s<dotPos.y; s++ )
        {
            for( int r=0; r<25; r++ )
                value[r][s] += 50-abs(tx-r) + 50 - abs(abs(ty-s)-8) ;
        }
        break;
    }
    case 2:
    {
        for( int r=24; r>dotPos.x; r-- )
        {
            for( int s=0; s<25; s++ )
                value[r][s] += 50-abs(ty-s) + 50 - abs(abs(tx-r)-8) ;
        }
        break;
    }
    case 3:
    {
        for( int s=24; s>dotPos.y; s-- )
        {
            for( int r=0; r<25; r++ )
                value[r][s] += 50-abs(tx-r) + 50 - abs(abs(ty-s)-8) ;
        }
        break;
    }
    case 4:
    {
        for( int r=0; r<dotPos.x; r++ )
        {
            for( int s=0; s<25; s++ )
                value[r][s] += 50-abs(ty-s) + 50 - abs(abs(tx-r)-8) ;
        }
        break;
    }
    default:
        break;
    }


    for (int p=0; p<25; p++)
    {
        for (int q=0; q<25; q++)
        {
            for (int i=0; i<rocks.size(); i++)
            {
                if (rocks[i].x==p && rocks[i].y==q)
                    value[p][q]=0;
                //if (rocks[i].x==p && (rocks[i].y-q)*(rocks[i].y-dotPos.y)>0) value[p][q]=0;
                //if (rocks[i].y==q && (rocks[i].x-p)*(rocks[i].x-dotPos.x)>0) value[p][q]=0;
            }
        }
    }


    int tmpx=0;
    int tmpy=0;
    int tmpmax=value[0][0];
    for ( int q=0; q<25; q++ )
    {
        for ( int p=0; p<25; p++ )
        {
            std::cout << value[p][q] << " ";
            if ( value[p][q]>tmpmax )
            {
                tmpmax=value[p][q];
                tmpx=p;
                tmpy=q;
            }
        }
        std::cout << std::endl;
    }
    std::cout << tmpx << "," << tmpy << "^" <<value[tmpx][tmpy] << std::endl;
    Position nRpos(tmpx,tmpy);
    rocks.push_back(nRpos);
}

void Walls::addRocks(Position dotPos, int dir)
{

\
    chooseRocks(dotPos,dir);
}
