//File : player.h <class untuk info player>
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

class player {
	public :
		player(); //ctor
		~player(); //dtor

		//getter
		string GetName ();
		string GetKey();
		int GetPoints();
		bool GetStatus();
		int GetBombX();
		int GetBombY();
		int GetBombBag();
		int GetBlastRadius();

		//setter
		void SetName(string name);
		void SetKey(string a);
		void SetPoints(string x);
		void SetStatus(string _status);
		void SetBombX(string i);
		void SetBombY(string i);
		void SetBombBag(string j);
		void SetBlast(string y);

	private :
		string PName;
		string Key;
		int Points;
		bool Status;
		int Bomb[2]; //Buat simpan X,Y
		int BombBag;
		int BlastRadius;
};

#endif
