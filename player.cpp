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
    Points = stoi(x);
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
    Bomb[0] = stoi(i);
}

void player::SetBombY(string i)
{
    Bomb[1] = stoi(i);
}

void player::SetBombBag(string j)
{
    BombBag = stoi(j);
}

void player::SetBlast(string y)
{
    BlastRadius = stoi(y);
}


