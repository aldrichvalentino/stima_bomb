// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
using namespace std;

void readStateFile(string filePath, string ckey);
void writeMoveFile(string filePath);

int _tmain(int argc, _TCHAR* argv[])
{
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

    string CPlayer(argv[1]); //mencatat current player key

	readStateFile(filePath,CPlayer);
	writeMoveFile(filePath);
	return 0;
}

void readStateFile(string filePath, string ckey)
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

        myfile.get(inputchar);

        /////////////////////////////////////////
		myfile.close();
	}
}

void writeMoveFile(string filePath)
{
	cout << "Writing move file " << filePath + "/" + "move.txt" << std::endl;
	ofstream outfile(filePath + "/" + "move.txt");

	if (outfile.is_open())
	{
        srand(time(NULL));
        int i = rand() % 7 + 1;

		outfile << i << std::endl;
		outfile.close();
	}
}
