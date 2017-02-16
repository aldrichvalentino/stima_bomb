#include <fstream>
#include <string>
#include <iostream>
#include "player.h"
using namespace std;

int main ()
{
        ifstream myfile ("map.txt");

        string MyString;
        int MapSize = 0;

        while(myfile >> MyString && MyString != "PlayerBounty:")
        {
            if(MyString == "Width:")
            {
                myfile >> MapSize;
            }
        }
        myfile >> MyString; //buang value playerBounty
        myfile.get(); //buang enter


        /* Pembacaan Peta */
        char **Peta;
        Peta = new char* [MapSize];
        for(int i = 0; i < MapSize; ++i)
        {
            Peta[i] = new char [MapSize];
        }

        char inputchar;
        for(int j = 0; j < MapSize; ++j)
        {
            for(int k = 0; k < MapSize; ++k)
            {
                myfile.get(inputchar);
                Peta[j][k] = inputchar;
            }
            myfile.get(inputchar); //buang enter
        }


        //print peta
        for(int i = 0; i < MapSize; ++i)
        {
            for(int j = 0; j < MapSize; ++j)
            {
                cout << Peta[i][j];
            }
            cout << endl;
        }

        char temp;
        player P1;

        myfile >> MyString; //buang garis
        myfile.get(temp);
        getline(myfile,MyString);
        P1.SetName(MyString.substr(13));
        getline(myfile,MyString);
        P1.SetKey(MyString.substr(5));
        getline(myfile,MyString);
        P1.SetPoints(MyString.substr(8));
        getline(myfile,MyString);
        P1.SetStatus(MyString.substr(8));
        getline(myfile,MyString);
        //P1.SetBombX(MyString.substr()); //gatau
        //P1.SetBombY(MyString.substr()); //gatau
        getline(myfile,MyString);
        P1.SetBombBag(MyString.substr(9));
        getline(myfile,MyString);
        P1.SetBlast(MyString.substr(13));
        myfile >> MyString;
        
        myfile.close();
}
