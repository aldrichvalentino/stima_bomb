//File : state.cpp
#include "state.h"

	state :: state() //ctor
	{
		n_brs = 21;
		n_kol = 21;
		int i,j;
		b = new sData* [n_brs];
		for (i = 0;i< n_brs;i++)
        {
            b[i] = new sData [n_kol];
        }
		for (i = 0;i < n_brs;i++)
		{
			for(j = 0; j < n_kol;j++)
			{
				b[i][j].Entity = "Kosong";
				b[i][j].Bomb = -1;
				b[i][j].PowerUp = -1;
				b[i][j].Explode = false;
			}
		}
	}
	state :: ~state() //dtor
	{
		for (int i = 0;i < n_brs;i++)
        {
            delete [] b[i];
        }
        delete [] b;
	}
	
	//getter
	int state :: GetBrs()
	{
		return n_brs;
	}
	int state :: GetKol()
	{
		return n_kol;
	}
	string state :: GetEntity(int i, int j)
	{
		return b[i][j].Entity;
	}
	int state :: GetBomb(int i, int j)
	{
		return b[i][j].Bomb;
	}
	int state :: GetPowerUp(int i, int j)
	{
		return b[i][j].PowerUp;
	}
	bool state :: GetExplode(int i, int j)
	{
		return b[i][j].Explode;
	}
	
	//setter
	void state :: SetEntity(int i, int j, string s)
	{
		b[i][j].Entity = s;
	}
	void state :: SetBomb(int i, int j, int x)
	{
		b[i][j].Bomb = x;
	}
	void state :: SetPowerUp(int i, int j, int x)
	{
		b[i][j].PowerUp = x;
	}
	void state :: SetExplode(int i, int j, bool bol)
	{
		b[i][j].Explode = bol;
	}

