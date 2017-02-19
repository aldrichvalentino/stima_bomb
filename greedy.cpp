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
    if (dir == atas){
        x = P[KeyToIdx(key)].GetLocX();
        y = P[KeyToIdx(key)].GetLocY()-1;
    }
    else if (dir == bawah)
    {
        x = P[KeyToIdx(key)].GetLocX();
        y = P[KeyToIdx(key)].GetLocY()+1;
    }
    else if(dir == kiri)
    {
        x = P[KeyToIdx(key)].GetLocX()-1;
        y = P[KeyToIdx(key)].GetLocY();
    }
    else if (dir == kanan)
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

void MoveToEntity(string Key, player P[], char** Peta, int MapSize, int move[])
//Mengestimasi gerakan mana yang diambil bila di sekitarnya ada entitas power up dan TembokDes
//Radius pencarian = 5
{
    bool ada = false;
    int radius = 1;
    int i = P[KeyToIdx(Key)].GetLocX() - radius;
    int imax = P[KeyToIdx(Key)].GetLocX() + radius;
    int j;
    int jmax = P[KeyToIdx(Key)].GetLocY() + radius;
    int ret;
    while (!ada && i<=imax)
    {
        if (i >= 1 && i <= MapSize)
        {
            j = P[KeyToIdx(Key)].GetLocY() - radius;
            while (!ada && j<=jmax)
            {
                if (j >= 1 && j <= MapSize)
                {
                    if (IsPowerUp(i,j,Peta) == 1 || IsPowerUp(i,j,Peta) == 2 || IsPowerUp(i,j,Peta) == 3 || IsTembokDes(i,j,Peta))
                    {
                        ada = true;
                    }
                }
                if (!ada) j++;
            }
        }
        if (!ada) i++;
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
        }else
        if(x != 0 && y == 0) //powerup segaris sama player
        {
            if(x < 0)
            {
                ret = kanan;
            } else
            {
                ret = kiri;
            }

        }
        else   //powerup segaris y sama player
        {
            if(y > 0 )
            {
                ret = atas;
            } else
            {
                ret = bawah;
            }
        }
        move[ret] += 20;
    }
}

bool IsTembokUndes(int x, int y, char** Peta)
{
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
            if (dir == atas)
            {
                x = P[KeyToIdx(temp)].GetLocX();
                y = P[KeyToIdx(temp)].GetLocY()-1;
            }
            else if (dir == bawah)
            {
                x = P[KeyToIdx(temp)].GetLocX();
                y = P[KeyToIdx(temp)].GetLocY()+1;
            }
            else if(dir == kiri)
            {
                x = P[KeyToIdx(temp)].GetLocX()-1;
                y = P[KeyToIdx(temp)].GetLocY();
            }
            else if (dir == kanan)
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

void EntityTerdekat(string Key, player P[], char** Peta, int MapSize, int move[]) {
    bool found;
    int x,y,a,b;
	int radius;

    //Nyari di atas
    found = false;
    x = P[KeyToIdx(Key)].GetLocX();
    y = P[KeyToIdx(Key)].GetLocY()-1;
    if (Peta[y][x] == ' ') {
            radius=1;
            y -= radius;
        while((!(found)) && (y>1) && ((x+radius<MapSize) || (x-radius>1))) {
            if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta)))  {
                found = true;
            } else {
                a = x - radius;
                if (a<1) a=2;

                b = x + radius;
                if (b>MapSize) b=MapSize-1;

                while ((!(found)) && (a<=b)) {
                    if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) found = true;
                    a++;
                }
            }
            radius++;
            y--;
        }
    }

    if (found) {
        move[atas] = MapSize - radius;
    }

    //Nyari di kiri
    found = false;
    x = P[KeyToIdx(Key)].GetLocX()-1;
    y = P[KeyToIdx(Key)].GetLocY();
    if (Peta[y][x] == ' ') {
            radius=1;
            x -= radius;
        while((!(found)) && (x>1) && ((y+radius<MapSize) || (y-radius>1))) {
            if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) {
                found = true;
            } else {
                a = y - radius;
                if (a<1) a=2;

                b = y + radius;
                if (b>MapSize) b=MapSize-1;

                while ((!(found)) && (a<=b)) {
                    if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) found = true;
                    a++;
                }
            }
            radius++;
            x--;
        }
    }

    if (found) {
        move[kiri] = MapSize - radius;
    }

    //Nyari di kanan
    found = false;
    x = P[KeyToIdx(Key)].GetLocX()+1;
    y = P[KeyToIdx(Key)].GetLocY();
    if (Peta[y][x] == ' ') {
            radius=1;
            x += radius;
        while((!(found)) && (x<MapSize) && ((y+radius<MapSize) || (y-radius>1))) {
            if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) {
                found = true;
            } else {
                a = y - radius;
                if (a<1) a=2;

                b = y + radius;
                if (b>MapSize) b=MapSize-1;

                while ((!(found)) && (a<=b)) {
                    if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) found = true;
                    a++;
                }
            }
            radius++;
            x++;
        }
    }

    if (found) {
        move[kanan] = MapSize - radius;
    }

    //Nyari di bawah
    found = false;
    x = P[KeyToIdx(Key)].GetLocX();
    y = P[KeyToIdx(Key)].GetLocY()+1;
    if (Peta[y][x] == ' ') {
            radius=1;
            y += radius;
        while((!(found)) && (y<MapSize) && ((x+radius<MapSize) || (x-radius>1))) {
            if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) {
                found = true;
            } else {
                a = x - radius;
                if (a<1) a=2;

                b = x + radius;
                if (b>MapSize) b=MapSize-1;

                while ((!(found)) && (a<=b)) {
                    if ((IsPowerUp(x,y,Peta)) || (IsTembokDes(x,y,Peta))) found = true;
                    a++;
                }
            }
            radius++;
            y++;
        }
    }

    if (found) {
        move[bawah] = MapSize - radius;
    }

}

void eval(int move[],int Neff, string Key, player P[], char **Peta, int MapSize)
{
    //PowerUp && Destructable wall
    EntityTerdekat(Key,P,Peta,MapSize,move);
    //JarakPowerUp(Key,P,Peta,MapSize,move); //+ 20
    int idx;
    //Cegah jalan ke bom
    if (IsRadiusBomb(atas,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(bawah,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombY() < P[KeyToIdx(Key)].GetLocY())
            {
                move[bawah] += 50;
            }
            else
            {
                move[atas] += 50;
            }
        }
        move[atas] -= 500;
    }
    if (IsRadiusBomb(kiri,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(kanan,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombX() < P[KeyToIdx(Key)].GetLocX())
            {
                move[kanan] += 50;
            }
            else
            {
                move[kiri] += 50;
            }
        }
        move[kiri] -= 500;
    }
    if (IsRadiusBomb(bawah,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(atas,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombY() < P[KeyToIdx(Key)].GetLocY())
            {
                move[bawah] += 50;
            }
            else
            {
                move[atas] += 50;
            }
        }
        move[bawah] -= 500;
    }
    if (IsRadiusBomb(kanan,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(kiri,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombX() < P[KeyToIdx(Key)].GetLocX())
            {
                move[kanan] += 50;
            }
            else
            {
                move[kiri] += 50;
            }
        }
        move[kanan] -= 500;
    }

    if (IsRadiusBomb(0,Neff,Key,P,Peta,idx))
    {
        move[atas] += 10;
        move[bawah] += 10;
        move[kiri] += 10;
        move[kanan] += 10;
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
        move[bawah] = -999;
    }
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta))
    {
        move[atas] = -999;
    }
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta))
    {
        move[kanan] = -999;
    }
    if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta))
    {
        move[kiri] = -999;
    }
}