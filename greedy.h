//File : greedy.h
#ifndef GREEDY_H
#define GREEDY_H

#include <string>
#include "player.h"


using namespace std;

/*  1=up
    2=down
    3=left
    4=right
    5=place
    6=trigger
    7=nothing*/

int KeyToIdx(string k);

//kasus dalam radius bomb (prekondisi tiap player bomnya 1, )
bool IsRadiusBomb(int dir,int Neff, string key, player P[], char** Peta, int &idx);

int IsPowerUp(int x, int y, char** Peta);

float JarakKeMusuh(string Key, string KeyMusuh, player P[]);

void JarakPowerUp(string Key, player P[], char** Peta, int MapSize, int move[]);

bool IsTembokUndes(int x, int y, char** Peta);

bool IsTembokDes(int x, int y, char** Peta);

int GerakFinal(int move[]);

void TaruhBomb(string Key, player P[], char** Peta, int move[]); //Bomb ga untuk membunuh, bomb untuk menghancurkan TembokDes

bool IsRadiusBombMusuh(int dir, int Neff, string Key, player P[], char **Peta);

void TriggerBomb(int move[],int dir, int Neff, string Key, player P[], char **Peta);

bool IsAlive(player P[], string Key);

void eval(int move[],int Neff, string Key, player P[], char **Peta, int MapSize);

#endif