//File : player.cpp
#include "player.h"

player :: player()
{
	size = 4;
	data_ = new pData[size];

	for(int i = 0; i<this->size; i++) {
		data_[i].Key = '?';
		data_[i].Killed = false;
		data_[i].BombBag = -1;
		data_[i].BombRadius = -1;
		data_[i].LocX = -1;
		data_[i].LocY = -1;
	}
}

player :: ~player()
{
	delete [] this->data_;
	this->size = 0;
}

	int player :: GetSize()
	{
		return size;
	}
	char player :: GetKey(int i)
	{
		return data_[i].Key;
	}
	bool player :: GetKilled(int i)
	{
		return data_[i].Killed;
	}
	int player:: GetBombBag(int i)
	{
		return data_[i].BombBag;
	}
	int player :: GetBombRadius(int i)
	{
		return data_[i].BombRadius;
	}
	int player :: GetLocX(int i)
	{
		return data_[i].LocX;
	}
	int player :: GetLocY(int i)
	{
		return data_[i].LocY;
	}
	
	void player :: SetKey(int i, char c)
	{
		data_[i].Key = c;
	}
	
	void player :: SetKilled(int i, bool b)
	{
		data_[i].Killed = b;
	}
	
	void player :: SetBombBag(int i, int x)
	{
		data_[i].BombBag = x;
	}
	
	void player :: SetBombRadius(int i, int x)
	{
		data_[i].BombRadius = x;
	}
	
	void player :: SetLocX(int i, int x)
	{
		data_[i].LocX = x;
	}
	
	void player :: SetLocY(int i, int x)
	{
		data_[i].LocY = x;
	}
	
	
	
	
	
	
	
	
	
	
	
	
