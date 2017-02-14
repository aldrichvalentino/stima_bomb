//File : state.h
#ifndef STATE_H
#define STATE_H
#include <string>
#include <iostream>

using namespace std;

typedef struct{
	string Entity;
	int Bomb;
	int PowerUp;
	bool Explode;
} sData;

class state {
	public :
		state(); //ctor
		
		~state(); //dtor
		
		//getter
		int GetBrs();
		int GetKol();
		string GetEntity(int i, int j);
		int GetBomb(int i, int j);
		int GetPowerUp(int i, int j);
		bool GetExplode(int i, int j);
		
		//setter
		void SetEntity(int i, int j, string s);
		void SetBomb(int i, int j, int x);
		void SetPowerUp(int i, int j, int x);
		void SetExplode(int i, int j, bool b);
		
	private :
		int n_brs;
		int n_kol;
		sData ** b;
};

#endif