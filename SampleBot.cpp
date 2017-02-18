// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
using namespace std;

void readStateFile(string filePath, string ckey, int& move);
void writeMoveFile(string filePath,int move);

int _tmain(int argc, _TCHAR* argv[])
{
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

    string CPlayer(argv[1]); //mencatat current player key
    int gerak;
	readStateFile(filePath,CPlayer,gerak);
	writeMoveFile(filePath,gerak);
	return 0;
}

void readStateFile(string filePath, string ckey, int& move) //ckey current KEY
{
	cout << "Reading state file " << filePath + "/" + "map.txt" << std::endl;
	string fileContent;
	string line;
	ifstream myfile(filePath + "/" + "map.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			fileContent += line += "\n";
			cout << fileContent;
		}
		///////////////////////////////////////
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
                    if (Peta[k][l] == 65+j)
                    {
                        P[j].SetLoc(l,k);
                    }
                }
            }
        }
        int Movement[8] = {0};
        int idx;
       
        //Eval Output terbaik
        eval(Movement,i,"A",P,Peta,MapSize,idx);
        //Ouput Move
        move = GerakFinal(Movement);

        /////////////////////////////////////////
		myfile.close();
	}
}

void writeMoveFile(string filePath, int move)
{
	cout << "Writing move file " << filePath + "/" + "move.txt" << std::endl;
	ofstream outfile(filePath + "/" + "move.txt");

	if (outfile.is_open())
	{
		outfile << move << std::endl;
		outfile.close();
	}
}

