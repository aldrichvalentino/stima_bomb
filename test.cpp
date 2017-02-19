#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "greedy.h"
#include <tchar.h>

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
        Peta = new char* [MapSize+1];
        for(int i = 1; i <= MapSize; ++i)
        {
            Peta[i] = new char [MapSize+1];
        }

        char inputchar;
        for(int j = 1; j <= MapSize; ++j)
        {
            for(int k = 1; k <= MapSize; ++k)
            {
                myfile.get(inputchar);
                Peta[j][k] = inputchar;
            }
            myfile.get(inputchar); //buang enter
        }


        //print peta
        for(int i = 1; i <= MapSize; ++i)
        {
            for(int j = 1; j <= MapSize; ++j)
            {
                cout << Peta[i][j];
            }
            cout << endl;
        }

        char temp;
        player P[12];
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
            if (MyString.length() > 7){
                P[i].SetBombX(MyString.substr(10)); 
                if (P[i].GetBombX() < 10){
                    P[i].SetBombY(MyString.substr(14)); 
                    if (P[i].GetBombY() < 10){
                        P[i].SetFuse(MyString.substr(21));
                    }
                    else
                    {
                        P[i].SetFuse(MyString.substr(22));
                    }
                }
                else
                {
                    P[i].SetBombY(MyString.substr(15));
                    if (P[i].GetBombY() < 10){
                        P[i].SetFuse(MyString.substr(22));
                    }
                    else
                    {
                        P[i].SetFuse(MyString.substr(23));
                    }
                }

            }
            else
            {
                P[i].SetBombX("-1");
                P[i].SetBombY("-1");
                P[i].SetFuse("-1");
            }
            getline(myfile,MyString);
            P[i].SetBombBag(MyString.substr(9));
            getline(myfile,MyString);
            P[i].SetBlast(MyString.substr(13));
            myfile >> MyString;
            myfile >> MyString; //buang garis
            i++;
        }
        i--;
        for (int j = 0;j <= i;j++)
        {
            for (int k = 1;k <= MapSize;k++)
            {
                for (int l = 1;l <= MapSize;l++)
                {
                    if (Peta[k][l] == 65+j || Peta[k][l] == 97+j)
                    {
                        P[j].SetLoc(l,k);
                    }
                }
            }
        }
        
        cout << JarakPowerUp("A",P,Peta,MapSize,move);

        cout << "daftar nilai move" << endl;
        cout << move[1] << endl;
        cout << move[2] << endl;
        cout << move[3] << endl;
        cout << move[4] << endl;
        cout << move[5] << endl;
        cout << move[6] << endl;
        cout << move[7] << endl;


        cout << "location: "<< endl <<P[KeyToIdx("B")].GetLocX() << endl;
        cout <<P[KeyToIdx("B")].GetLocY() << endl;
        //int x = JarakPowerUp("A",P,Peta,MapSize);

        //cout << x << endl;

        //GERAKAN YG DITARO KE txt
        int gerak = GerakFinal(move);
        cout << gerak << endl;
       
        //cout << Peta[P[1].GetBombY()][P[1].GetBombX()] << endl;
        /*cout << i << endl;
        cout << KeyToIdx("B") << endl;
        if (IsRadiusBomb(4,i,"A",P,Peta))
        {
            cout << "test" << endl;
        }

        if (IsRadiusBombMusuh(0,i,"B",P,Peta))
        {
            cout << "radius bom" << endl;
        }
        cout << JarakKeMusuh("A","B",P);*/
        myfile.close();
}
