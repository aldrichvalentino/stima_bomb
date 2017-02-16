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
        player P[4];
        int i = 0;

        myfile >> MyString; //buang garis
        while(!myfile.eof()){
            myfile.get(temp);
            getline(myfile,MyString);
            P[i].SetName(MyString.substr(13));
            getline(myfile,MyString);
            P[i].SetKey(MyString.substr(5));
            getline(myfile,MyString);
            P[i].SetPoints(MyString.substr(8));
            getline(myfile,MyString);
            P[i].SetStatus(MyString.substr(8));
            getline(myfile,MyString);
            //P1.SetBombX(MyString.substr()); //gatau
            //P1.SetBombY(MyString.substr()); //gatau
            getline(myfile,MyString);
            P[i].SetBombBag(MyString.substr(9));
            getline(myfile,MyString);
            P[i].SetBlast(MyString.substr(13));
            myfile >> MyString;
            myfile >> MyString; //buang garis
            i++;
        }
        
        cout << P[1].GetName() << endl;
        cout << P[0].GetKey() << endl;
        cout << P[2].GetPoints() << endl;
        cout << P[3].GetStatus() << endl;
        
        myfile.close();
}
