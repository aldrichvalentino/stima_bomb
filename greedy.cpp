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

bool IsTembokUndes(int x, int y, char** Peta)
{
    return (Peta[y][x] == '#');
}

bool IsTembokDes(int x, int y, char** Peta)
{
    return (Peta[y][x] == '+');
}

bool IsTembok(int x, int y, char** Peta)
{
    return (IsTembokDes(x,y,Peta) || IsTembokUndes(x,y,Peta));
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



bool IsBomb(int x, int y, char** Peta)
{
    return (Peta[y][x] == 'a' || Peta[y][x] == 'b' || Peta[y][x] == 'c' || Peta[y][x] == 'd' || Peta[y][x] == 'e' ||  Peta[y][x] == 'f' || Peta[y][x] == 'g' || Peta[y][x] == 'h' || Peta[y][x] == 'i' || Peta[y][x] == 'j' || Peta[y][x] == 'k' || Peta[y][x] == 'l' || Peta[y][x] == '1' || Peta[y][x] == '2' || Peta[y][x] == '3' || Peta[y][x] == '4' || Peta[y][x] == '5' || Peta[y][x] == '6' || Peta[y][x] == '7' || Peta[y][x] == '8' || Peta[y][x] == '9');
}



int GerakFinal(int move[])
{
    int max = move[1];
    int i;
    int ret = 1;
    for (i = 2;i < 8;i++)//trigger bomb gamasuks
    {
        if (max < move[i])
        {
            if (i != 6)
            {
                ret = i;
                max = move[i];
            }
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
            move[5] += 45; // Nilai belom fix
        }
        else
        {
            move[5] -= 45; //Belom fix
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
    if ((Peta[y][x] == '!') || (Peta[y][x] == '$') || (Peta[y][x] == '&')) move[atas] = 45;
    if (Peta[y][x] == ' ') {
            radius=1;
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
    if ((Peta[y][x] == '!') || (Peta[y][x] == '$') || (Peta[y][x] == '&')) move[kiri] = 45;
    if (Peta[y][x] == ' ') {
            radius=1;
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
    if ((Peta[y][x] == '!') || (Peta[y][x] == '$') || (Peta[y][x] == '&')) move[kanan] = 45;
    if (Peta[y][x] == ' ') {
            radius=1;
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
    if ((Peta[y][x] == '!') || (Peta[y][x] == '$') || (Peta[y][x] == '&')) move[bawah] = 45;
    if (Peta[y][x] == ' ') {
            radius=1;
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

bool IsRadiusBomb(int dir, int Neff, string key, player P[], char** Peta, int MapSize) {
    bool kena = false;
    bool tembok = false;
    int i = 0;
    int j;
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
    else if (dir == 0)
    {
        x = P[KeyToIdx(key)].GetLocX();
        y = P[KeyToIdx(key)].GetLocY();
    }

    while (i <= Neff && !kena)
    {
        tembok = false;
        j = 0;
        if (P[i].GetBombX() != -1 && P[i].GetFuse() <= 10)
        {
            while (j <= P[i].GetBlastRadius() && !kena && !tembok)
            {
                if (IsTembok(x+j,y,Peta))
                {
                    tembok = true;
                }
                if (IsBomb(x+j,y,Peta))
                {
                    kena = true;
                }
                j++;
            }
            j = 0;
            tembok = false;
            while (j <= P[i].GetBlastRadius() && !kena && !tembok)
            {
                if (IsTembok(x-j,y,Peta))
                {
                    tembok = true;
                }
                if (IsBomb(x-j,y,Peta))
                {
                    kena = true;
                }
                j++;
            }
            j = 0;
            tembok = false;
            while (j <= P[i].GetBlastRadius() && !kena && !tembok)
            {
                if (IsTembok(x,y+j,Peta))
                {
                    tembok = true;
                }
                if (IsBomb(x,y+j,Peta))
                {
                    kena = true;
                }
                j++;
            }
            j = 0;
            tembok = false;
            while (j <= P[i].GetBlastRadius() && !kena && !tembok)
            {
                if (IsTembok(x,y-j,Peta))
                {
                    tembok = true;
                }
                if (IsBomb(x,y-j,Peta))
                {
                    kena = true;
                }
                j++;
            }
        }
        i++;
    }
    return kena;
}

void RunFromBomb (string Key, int Neff, player P[], char** Peta, int MapSize, int move[]) {
    int i,j;
    move[5] = -999;
    move[6] = -999;
    move[7] = -999;
    i = 1;
    int idx;
    bool stop;
    int x1 = P[KeyToIdx(Key)].GetLocX();
    int y1 = P[KeyToIdx(Key)].GetLocY();
    int x2 = P[KeyToIdx(Key)].GetLocX();
    int y2 = P[KeyToIdx(Key)].GetLocY();
    int x3 = P[KeyToIdx(Key)].GetLocX();
    int y3 = P[KeyToIdx(Key)].GetLocY();
    int x4 = P[KeyToIdx(Key)].GetLocX();
    int y4 = P[KeyToIdx(Key)].GetLocY();
    //kasus 1
    while (!IsTembok(x1,y1,Peta))
    {
        y1 -= 1;
        move[1]++;
        if (IsBomb(x1,y1,Peta))
        {
            break;
        }
    }
    if (IsBomb(x1,y1,Peta))
    {
        move[1] = -100;
    }
    //kasus 2
    while (!IsTembok(x2,y2,Peta))
    {
        x2 -= 1;
        move[2]++;
        if (IsBomb(x2,y2,Peta))
        {
            break;
        }
    }
    if (IsBomb(x2,y2,Peta))
    {
        move[2] = -100;
    }
    //kasus 3
    while (!IsTembok(x3,y3,Peta))
    {
        x3 += 1;
        move[3]++;
        if (IsBomb(x3,y3,Peta))
        {
            break;
        }
    }
    if (IsBomb(x3,y3,Peta))
    {
        move[3] = -100;
    }
    //kasus 4
    while (!IsTembok(x4,y4,Peta))
    {
        y4 += 1;
        move[4]++;
        if (IsBomb(x4,y4,Peta))
        {
            break;
        }
    }
    if (IsBomb(x4,y4,Peta))
    {
        move[4] = -100;
    }
    
}
void eval(int move[],int Neff, string Key, player P[], char **Peta, int MapSize)
{
    //Kalo di radius bomb
    int idx;
    if (IsRadiusBomb(0,Neff,Key,P,Peta,MapSize) || IsRadiusBomb(1,Neff,Key,P,Peta,MapSize) || IsRadiusBomb(2,Neff,Key,P,Peta,MapSize) || IsRadiusBomb(3,Neff,Key,P,Peta,MapSize) || IsRadiusBomb(4,Neff,Key,P,Peta,MapSize))
    {
        RunFromBomb(Key,Neff,P,Peta,MapSize,move);
        if (!IsRadiusBomb(kiri,Neff,Key,P,Peta,MapSize) && !IsTembok(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta))
        {
            move[kiri] += 2;
        }
        if (!IsRadiusBomb(kanan,Neff,Key,P,Peta,MapSize) && !IsTembok(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta))
        {
            move[kanan] += 2;
        }
        if (!IsRadiusBomb(atas,Neff,Key,P,Peta,MapSize) && !IsTembok(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta))
        {
            move[atas] += 2;
        }
        if (!IsRadiusBomb(bawah,Neff,Key,P,Peta,MapSize) && !IsTembok(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta))
        {
            move[bawah] += 2;
        }
    }
    else
    {
        EntityTerdekat(Key,P,Peta,MapSize,move);
        int idx;
        //Taro Bomb
        TaruhBomb(Key,P,Peta,move); //45 point

        //Trigger Bomb
        
        if (P[KeyToIdx(Key)].GetBombX() != (-1))
        {
            if (IsRadiusBombMusuh(0,Neff,Key,P,Peta))
            {
                move[trigger] += 5;//TBD
            }
            else
            {
                move[trigger] = -1000;
            }
        }
        else
        {
            move[trigger] = -1000;
        }
        //Gerak relatif thdp bom

        //Gerak gaakan ke tembok
        if (IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()+1,Peta))
        {
            move[bawah] = -200;
        }
        if (IsTembokDes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX(),P[KeyToIdx(Key)].GetLocY()-1,Peta))
        {
            move[atas] = -200;
        }
        if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()+1,P[KeyToIdx(Key)].GetLocY(),Peta))
        {
            move[kanan] = -200;
        }
        if (IsTembokDes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta) || IsTembokUndes(P[KeyToIdx(Key)].GetLocX()-1,P[KeyToIdx(Key)].GetLocY(),Peta))
        {
            move[kiri] = -200;
        }
    }
    //PowerUp && Destructable wall
    
    //JarakPowerUp(Key,P,Peta,MapSize,move); //+ 20
    
    //Cegah jalan ke bom
    /*if (IsRadiusBomb(atas,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(bawah,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombY() < P[KeyToIdx(Key)].GetLocY())
            {
                move[bawah] += 25; //+25
            }
            else
            {
                move[atas] += 25; //+25
            }
        }
        move[atas] -= 100;//-100
    }
    if (IsRadiusBomb(kiri,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(kanan,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombX() < P[KeyToIdx(Key)].GetLocX())
            {
                move[kanan] += 25;//+25
            }
            else
            {
                move[kiri] += 25;//+25
            }
        }
        move[kiri] -= 100;//-100
    }
    if (IsRadiusBomb(bawah,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(atas,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombY() < P[KeyToIdx(Key)].GetLocY())
            {
                move[bawah] += 25;
            }
            else
            {
                move[atas] += 25;
            }
        }
        move[bawah] -= 100;
    }
    if (IsRadiusBomb(kanan,Neff,Key,P,Peta,idx))
    {
        if (IsRadiusBomb(kiri,Neff,Key,P,Peta,idx))
        {
            if (P[idx].GetBombX() < P[KeyToIdx(Key)].GetLocX())
            {
                move[kanan] += 25;
            }
            else
            {
                move[kiri] += 25;
            }
        }
        move[kanan] -= 100;
    }

    if (IsRadiusBomb(0,Neff,Key,P,Peta,idx))
    {
        move[atas] += 10;
        move[bawah] += 10;
        move[kiri] += 10;
        move[kanan] += 10;
    }*/

    
}