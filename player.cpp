//File : player.cpp
#include "player.h"
#include <string>
#include <iostream>
using namespace std;

player :: player() {}

player :: ~player() {}

string player::GetName()
{
    return PName;
}

string player::GetKey()
{
    return Key;
}

int player::GetPoints()
{
    return Points;
}

bool player::GetStatus()
{
    return Status;
}

int player::GetBombX()
{
    return Bomb[0];
}

int player::GetBombY()
{
    return Bomb[1];
}

int player::GetBombBag()
{
    return BombBag;
}

int player::GetBlastRadius()
{
    return BlastRadius;
}

int player::GetLocX()
{
    return LocX;
}

int player::GetLocY()
{
    return LocY;
}

int player::GetFuse()
{
    return Fuse;
}
void player::SetName(string name)
{
    PName = name;
}

void player::SetKey(string a)
{
    Key = a;
}

void player::SetPoints(string x)
{
    Points = stoi(x,nullptr,10);
}

void player::SetStatus(string _status)
{
    if(_status == "Alive"){
        Status = true;
    } else {
        Status = false;
    }
}

void player::SetBombX(string i)
{
    Bomb[0] = stoi(i,nullptr,10);
}

void player::SetBombY(string i)
{
    Bomb[1] = stoi(i,nullptr,10);
}

void player::SetBombBag(string j)
{
    BombBag = stoi(j,nullptr,10);
}

void player::SetBlast(string y)
{
    BlastRadius = stoi(y,nullptr,10);
}

void player :: SetLoc(int x, int y)
{
    LocX = x;
    LocY = y;
}

void player :: SetFuse(string f)
{
    Fuse = stoi(f,nullptr,10);
}



