// SampleBot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
using namespace std;

void readStateFile(string filePath);
void writeMoveFile(string filePath);

int _tmain(int argc, _TCHAR* argv[])
{
	string filePath = argv[2];

	cout << "Args: " << argc << std::endl;
	cout << "Player Key: " << argv[1] << std::endl;
	cout << "File Path: " << argv[2] << std::endl;

	readStateFile(filePath);
	writeMoveFile(filePath);
	return 0;
}

void readStateFile(string filePath)
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
