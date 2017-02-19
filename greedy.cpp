#include "player.h"
#include <cmath>
#include <iostream>

using namespace std;

/* konstanta gerakan : {1 - up, 2 - left, 3 - right, 4 - down, 5 - bomb, 6 - trigger, 7 - nothing } */
const int atas = 1;
const int kiri = 2;
const int kanan = 3;
const int bawah = 4;
const int putbomb = 5;
const int trigger = 6;
const int nothing = 7;

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
    return (Peta[x][y] == '+'); //yx?
}

int IsPowerUp(int x, int y, char** Peta)
{
    if (Peta[x][y] == '$'){
        return 3;
    }
    else if (Peta[x][y] == '!'){
        return 2;
    }
    else if (Peta[x][y] == '&'){
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

void JarakPowerUp(string Key, player P[], char** Peta, int MapSize, int move[])
{
    bool ada = false;
    int radius = 1;
    int i = P[KeyToIdx(Key)].GetLocX() - radius; 
    int j;
    int ret;
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

    //cek move
    if (!ada)
    {
        ret = -1;
    }
    else
    {
        int x = P[KeyToIdx(Key)].GetLocX() - i; 
        int y = P[KeyToIdx(Key)].GetLocY() - j; 
        
        if(x > 0 && y < 0) //powerup di kiri bawah
        {
            if(x > abs(y))
            {
                ret = kiri;
            } else
            {
                ret = bawah;
            }
        } else
        if(x > 0 && y > 0) //powerup di kiri atas
        {
            if(x > y)
            {
                ret = kiri;
            } else
            {
                ret = atas;
            }
        }else
        if(x < 0 && y < 0) //powerup di kanan bawah
        {
            if(abs(x) > abs(y))
            {
                ret = kanan;
            } else 
            {
                ret = bawah;
            }
        }
        else
        if(x < 0 && y > 0) //powerup di kanan atas
        {
            if(abs(x) > y)
            {
                ret = kanan;
            } else 
            {
                ret = atas;
            }
        }
        move[ret] += 20;
    }
}

bool IsTembokUndes(int x, int y, char** Peta)
{
    cout << x << " " << y << endl;
    cout << Peta[y][x] << endl;
    return (Peta[y][x] == '#');
}

bool IsBomb(int x, int y, char** Peta)
{
    return (Peta[y][x] == 1 || Peta[y][x] == 2 || Peta[y][x] == 3 || Peta[y][x] == 4 || Peta[y][x] == 5 || Peta[y][x] == 6 || Peta[y][x] == 7 || Peta[y][x] == 8 || Peta[y][x] == 9);  
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
    if (i == 2)
    {
        ret = 4;
    }
    if (i == 3)
    {
        ret = 2;
    }
    if (i == 4)
    {
        ret = 3;
    }
    return ret;
}

void TaruhBomb(string Key, player P[], char** Peta, int move[]) //Bomb ga untuk membunuh, bomb untuk menghancurkan TembokDes
{
    if (P[KeyToIdx(Key)].GetBombBag() > 0) //cek punya bom atau ga
    {
        if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(), Peta) || IsTembokDes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(), Peta) || IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta) || IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta)) 
        {
            move[5] += 15; // Nilai belom fix
        }
        else
        {
            move[5] -= 15; //Belom fix
        }
    }
    else
    {
        move[5] = -1000;
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

void eval(int move[],int Neff, string Key, player P[], char **Peta, int MapSize)
{
    //PowerUp && Destructable wall 
    JarakPowerUp(Key,P,Peta,MapSize,move); //+ 20
    int idx;
    //Cegah jalan ke bom
    if (IsRadiusBomb(1,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(2,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombY() < P[KeyToIdx(Key)].GetLocY())
            {
                move[2] += 50;
            } 
            else
            {
                move[1] += 50;
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
                move[4] += 50;
            } 
            else
            {
                move[3] += 50;
            }
        }
        move[3] -= 500; 
    }
    if (IsRadiusBomb(4,Neff,Key,P,Peta,idx))
    {
        move[4] -= 500; 
    }
    if (IsRadiusBomb(0,Neff,Key,P,Peta,idx))
    {
        move[1] += 10;
        move[2] += 10;
        move[3] += 10;
        move[4] += 10;
    }

    //Taro Bomb
    TaruhBomb(Key,P,Peta,move); //15 point

    //Trigger Bomb
    if (P[KeyToIdx(Key)].GetBombX() != (-1))
    {
        if (IsRadiusBombMusuh(0,Neff,Key,P,Peta))
        {
            move[6] += 20;//TBD
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
        move[2] = -999; 
    } 
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta))
    {
        move[1] = -999; 
    } 
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta))
    {
        move[4] = -999; 
    } 
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta))
    {
        move[3] = -999; 
    }


}


























