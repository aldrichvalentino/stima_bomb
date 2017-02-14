//File : player.h <class untuk info player>
#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
	char Key;
	bool Killed;
	int BombBag;
	int BombRadius;
	int LocX;
	int LocY;
} pData;

class player {
	public :
		player(); //ctor
		
		~player(); //dtor
		
		//getter
		int GetSize();
		char GetKey(int i);
		bool GetKilled(int i);
		int GetBombBag(int i);
		int GetBombRadius(int i);
		int GetLocX(int i);
		int GetLocY(int i);
		
		//setter
		void SetKey(int i, char c);
		void SetKilled(int i, bool b);
		void SetBombBag(int i, int x);
		void SetBombRadius(int i, int x);
		void SetLocX(int i, int x);
		void SetLocY(int i, int x);
		
	private :
		int size;
		pData* data_;
		
};




#endif