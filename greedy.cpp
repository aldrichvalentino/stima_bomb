#include "player.h"
#include <cmath>
#include <iostream>

using namespace std;

/*  1=up
    2=down
    3=left
    4=right
    5=place
    6=trigger
    7=nothing*/

int KeyToIdx(string k)
{
    int x;
    if (k == "A")
    {
        x = 0;
    }
    else if (k == "B")
    {
        x = 1;
    }
    else if (k == "C")
    {
        x = 2;
    }
    else if (k == "D")
    {
        x = 3;
    }
    else if (k == "E")
    {
        x = 4;
    }
    else if (k == "F")
    {
        x = 5;
    }
    else if (k == "G")
    {
        x = 6;
    }
    else if (k == "H")
    {
        x = 7;
    }
    else if (k == "I")
    {
        x = 8;
    }
    else if (k == "J")
    {
        x = 9;
    }
    else if (k == "K")
    {
        x = 10;
    }
    else if (k == "L")
    {
        x = 11;
    }
    return x;
}

//kasus dalam radius bomb (prekondisi tiap player bomnya 1)
bool IsRadiusBomb(int dir, int Neff, string key, player P[], char** Peta, int &idx) {
    bool kena = false;
    int i = 0;
    int x,y;
    if (dir == 1){
        x = P[KeyToIdx(key)].GetLocX();
        y = P[KeyToIdx(key)].GetLocY()-1;
    }
    else if (dir == 2)
    {
        x = P[KeyToIdx(key)].GetLocX();
        y = P[KeyToIdx(key)].GetLocY()+1;
    }
    else if(dir == 3)
    {
        x = P[KeyToIdx(key)].GetLocX()-1;
        y = P[KeyToIdx(key)].GetLocY();
    }
    else if (dir == 4)
    {
        x = P[KeyToIdx(key)].GetLocX()+1;
        y = P[KeyToIdx(key)].GetLocY();
    }
    else
    {
        x = P[KeyToIdx(key)].GetLocX();
        y = P[KeyToIdx(key)].GetLocY();
    }
    while ((i<=Neff) && (!(kena))) {
        if (P[i].GetBombX() != -1 && P[i].GetFuse() <= 3)
         {
                if (y == P[i].GetBombY())
                {
                    if(x<=P[i].GetBombX() + P[i].GetBlastRadius()){
                        int k = x;
                        bool stop = false;
                        while (k > P[i].GetBombX() && !stop)
                        {
                            if (Peta[P[i].GetBombY()][k] != '#' && Peta[P[i].GetBombY()][k] != '+')
                            {
                                k--;
                            }
                            else
                            {
                                stop = true;
                            }
                        }
                        if (!stop)
                        {
                            idx = i;
                            kena = true;
                        }
                    }
                        else if (x>=P[i].GetBombX() - P[i].GetBlastRadius()){
                        int k = x;
                        bool stop = false;
                        while (k < P[i].GetBombX() && !stop)
                        {
                            if (Peta[P[i].GetBombY()][k] != '#' && Peta[P[i].GetBombY()][k] != '+')
                            {
                                k++;
                            }
                            else
                            {
                                stop = true;
                            }
                        }
                        if (!stop)
                        {
                            idx = i;
                            kena = true;
                        }
                        }
                }
                if (x == P[i].GetBombX())
                {
                    if (y<=P[i].GetBombY() + P[i].GetBlastRadius()){
                        int k = y;
                        bool stop = false;
                        while (k > P[i].GetBombY() && !stop)
                        {
                            if (Peta[k][P[i].GetBombX()] != '#' && Peta[k][P[i].GetBombX()] != '+')
                            {
                                k--;
                            }
                            else
                            {
                                stop = true;
                            }
                        }
                        if (!stop)
                        {
                            idx = i;
                            kena = true;
                        }
                    }
                    else if (y>=P[i].GetBombY() - P[i].GetBlastRadius()){
                        int k = y;
                        bool stop = false;
                        while (k < P[i].GetBombY() && !stop)
                        {
                            if (Peta[k][P[i].GetBombX()] != '#' && Peta[k][P[i].GetBombX()] != '+')
                            {
                                k++;
                            }
                            else
                            {
                                stop = true;
                            }
                        }
                        if (!stop)
                        {
                            idx = i;
                            kena = true;
                        }
                    }
                } 
            
         }
            i++;
        }
        return kena;
}

bool IsTembokDes(int x, int y, char** Peta)
{
    return (Peta[y][x] == '+');
}

int IsPowerUp(int x, int y, char** Peta)
{
    if (Peta[y][x] == '$'){
        return 3;
    }
    else if (Peta[y][x] == '!'){
        return 2;
    }
    else if (Peta[y][x] == '&'){
        return 1;
    }
    else {
        return 0;
    }
}

float JarakKeMusuh(string Key, string KeyMusuh, player P[]){
    int x = P[KeyToIdx(Key)].GetLocX() - P[KeyToIdx(KeyMusuh)].GetLocX();
    int y = P[KeyToIdx(Key)].GetLocY() - P[KeyToIdx(KeyMusuh)].GetLocY();
    int tempx = x*x;
    int tempy = y*y;
    int temp = tempx+tempy;
    return (sqrt(temp));
}

int JarakPowerUp(string Key, player P[], char** Peta, int MapSize)
{
    bool ada = false;
    int radius = 5;
    int i = P[KeyToIdx(Key)].GetLocX() - radius; 
    int j;
    while (!ada && i<=P[KeyToIdx(Key)].GetLocX() + radius)
    {
        if (i >= 1 && i <= MapSize)
        {
            j = P[KeyToIdx(Key)].GetLocY() - radius;
            while (!ada && j<=P[KeyToIdx(Key)].GetLocY() + radius)
            {
                if (j >= 1 && j <= MapSize)
                {
                    if (IsPowerUp(i,j,Peta) == 1 || IsPowerUp(i,j,Peta) == 2 || IsPowerUp(i,j,Peta) == 3 || IsTembokDes(i,j,Peta)) 
                    {
                        ada = true;
                    }
                }
                if (!ada)j++;
            }
        }
        if (!ada)i++;
    }
    if (!ada)
    {
        return -1;
    }
    else
    {
        int x = i - P[KeyToIdx(Key)].GetLocX();
        int y = j - P[KeyToIdx(Key)].GetLocY();
        if (x > 0 && y > 0)
        {
            if (x <= y)
            {
                return 4;
            }
            else
            {
                return 2;
            }
        }
        else if (x > 0 && y < 0)
        {
            if (x <= abs(y))
            {
                return 4;
            }
            else
            {
                return 1;
            }
        }
        else if (x < 0 && y > 0)
        {
            if (abs(x) <= y)
            {
                return 3;
            }
            else
            {
                return 2;
            }
        }
        else if (x < 0 && y < 0)
        {
            if (abs(x) <= abs(y))
            {
                return 3;
            }
            else
            {
                return 1;
            }
        }
    }
}

bool IsTembokUndes(int x, int y, char** Peta)
{
    return (Peta[y][x] == '#');
}



int GerakFinal(int move[])
{
    int max = move[1];
    int i;
    int ret = 1;
    for (i = 2;i < 7;i++)
    {
        if (max < move[i])
        {
            ret = i;
            max = move[i];
        }
    }
    return ret;
}

void TaruhBomb(string Key, player P[], char** Peta, int move[]) //Bomb ga untuk membunuh, bomb untuk menghancurkan TembokDes
{
    if (P[KeyToIdx(Key)].GetBombBag() > 0) //cek punya bom atau ga
    {
        if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(), Peta) || IsTembokDes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(), Peta) || IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta) || IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta)) 
        {
            move[5] += 10; // Nilai belom fix
        }
        else
        {
            move[5] -= 10; //Belom fix
        }

    }
}

bool IsRadiusBombMusuh(int dir, int Neff, string Key, player P[], char **Peta)
{
    bool stop = false;
    bool kena = false;
    int i = 0;
    int RadiusXBsr = P[KeyToIdx(Key)].GetBombX() + P[KeyToIdx(Key)].GetBlastRadius(); //radius ledakan bom player kita
    int RadiusXKcl = P[KeyToIdx(Key)].GetBombX() - P[KeyToIdx(Key)].GetBlastRadius();
    int RadiusYBsr = P[KeyToIdx(Key)].GetBombY() + P[KeyToIdx(Key)].GetBlastRadius();
    int RadiusYKcl = P[KeyToIdx(Key)].GetBombY() - P[KeyToIdx(Key)].GetBlastRadius();
    int x,y;
    while (i <= Neff && !stop)
    {
        string temp = P[i].GetKey(); 
        if (temp != Key)
        {
            if (dir == 1)
            {
                x = P[KeyToIdx(temp)].GetLocX();
                y = P[KeyToIdx(temp)].GetLocY()-1;
            }
            else if (dir == 2)
            {
                x = P[KeyToIdx(temp)].GetLocX();
                y = P[KeyToIdx(temp)].GetLocY()+1;
            }
            else if(dir == 3)
            {
                x = P[KeyToIdx(temp)].GetLocX()-1;
                y = P[KeyToIdx(temp)].GetLocY();
            }
            else if (dir == 4)
            {
                x = P[KeyToIdx(temp)].GetLocX()+1;
                y = P[KeyToIdx(temp)].GetLocY();
            }
            else
            {
                x = P[KeyToIdx(temp)].GetLocX();
                y = P[KeyToIdx(temp)].GetLocY();
            }
            if (y == P[KeyToIdx(Key)].GetBombY())
            {
                if(x<=RadiusXBsr){
                    int k = x;
                    bool stop = false;
                    while (k > P[KeyToIdx(Key)].GetBombX() && !stop)
                    {
                        if (Peta[P[KeyToIdx(Key)].GetBombY()][k] != '#' && Peta[P[KeyToIdx(Key)].GetBombY()][k] != '+')
                        {
                            k--;
                        }
                        else
                        {
                            stop = true;
                        }
                    }
                    if (!stop)
                    {
                        kena = true;
                    }
                }
                else if (x>=RadiusXKcl){
                    int k = x;
                    bool stop = false;
                    while (k < P[KeyToIdx(Key)].GetBombX() && !stop)
                    {
                        if (Peta[P[KeyToIdx(Key)].GetBombY()][k] != '#' && Peta[P[KeyToIdx(Key)].GetBombY()][k] != '+')
                        {
                            k++;
                        }
                        else
                        {
                            stop = true;
                        }
                    }
                    if (!stop)
                    {
                        kena = true;
                    }
                }
            }
            if (x == P[KeyToIdx(Key)].GetBombX())
            {
                if (y<=RadiusYBsr){
                    int k = y;
                    bool stop = false;
                    while (k > P[KeyToIdx(Key)].GetBombY() && !stop)
                    {
                        if (Peta[k][P[KeyToIdx(Key)].GetBombX()] != '#' && Peta[k][P[KeyToIdx(Key)].GetBombX()] != '+')
                        {
                            k--;
                        }
                        else
                        {
                            stop = true;
                        }
                    }
                    if (!stop)
                    {
                        kena = true;
                    }
                }
                else if (y>=RadiusYKcl){
                    int k = y;
                    bool stop = false;
                    while (k < P[KeyToIdx(Key)].GetBombY() && !stop)
                    {
                        if (Peta[k][P[KeyToIdx(Key)].GetBombX()] != '#' && Peta[k][P[KeyToIdx(Key)].GetBombX()] != '+')
                        {
                            k++;
                        }
                        else
                        {
                            stop = true;
                        }
                    }
                    if (!stop)
                    {
                        kena = true;
                    }
                }
            }
        }
        i++;
    }
    return kena;
}

void TriggerBomb(int move[],int dir, int Neff, string Key, player P[], char **Peta)
{
    if (P[KeyToIdx(Key)].GetBombX() != (-1)) //cek player kita punya bomb atau ga
    {
        if (IsRadiusBombMusuh(dir,Neff,Key,P,Peta))
        {
            move[6] += 10; //val benlom fix
        }
    }
}

bool IsAlive(player P[], string Key)
{
    return (P[KeyToIdx(Key)].GetStatus());
}

void eval(int move[],int Neff, string Key, player P[], char **Peta, int MapSize, int &idx)
{
    //PowerUp && Destructable wall 
    move[JarakPowerUp(Key,P,Peta,MapSize)] += 50;//TBD
    int x;
    //Cegah jalan ke bom
    if (IsRadiusBomb(1,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(2,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombY() < P[KeyToIdx(Key)].GetLocY())
            {
                move[2] += 10;
            } 
            else
            {
                move[1] += 10;
            }
        }
        move[1] -= 500; 
    }
    if (IsRadiusBomb(2,Neff,Key,P,Peta,idx))
    {
        move[2] -= 500; 
    }
    if (IsRadiusBomb(3,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(4,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombX() < P[KeyToIdx(Key)].GetLocX())
            {
                move[4] += 10;
            } 
            else
            {
                move[3] += 10;
            }
        }
        move[3] -= 500; 
    }
    if (IsRadiusBomb(4,Neff,Key,P,Peta,idx))
    {
        cout << idx << "guys <<"<< endl;
        move[4] -= 500; 
    }

    //Taro Bomb
    TaruhBomb(Key,P,Peta,move);

    //Trigger Bomb
    if (P[KeyToIdx(Key)].GetBombX() != -1)
    {
        if (IsRadiusBombMusuh(0,Neff,Key,P,Peta))
        {
            move[6] += 100;//TBD
        }
        else
        {
            move[6] = -1000;
        }
    }
    else
    {
        move[6] = -1000;
    }
    //Gerak relatif thdp bom

    //Gerak gaakan ke tembok
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta))
    {
        move[1] = -999; 
    } 
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta))
    {
        move[2] = -999; 
    } 
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta))
    {
        move[3] = -999; 
    } 
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY()+1,Peta))
    {
        move[4] = -999; 
    }


}


























