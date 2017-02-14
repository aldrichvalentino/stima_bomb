#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main ()
{
	ifstream i;
	i.open("map.txt");

	string MyString;
	int MapSize = 0;

	while(i >> MyString && MyString != "PlayerBounty:")
    {
        if(MyString == "Width:")
        {
            i >> MapSize;
        }
    }
    i >> MyString; //buang value playerBounty
    i.get(); //buang enter


    /* Pembacaan Peta */
    char gameBlocks[MapSize][MapSize];
    char inputchar;
    for(int j = 0; j < MapSize; ++j)
    {
        for(int k = 0; k < MapSize; ++k)
        {
            i.get(inputchar);
            gameBlocks[j][k] = inputchar;
        }
        i.get(inputchar); //buang enter
    }

    for(int j=0; j < MapSize; ++j)
    {
        for(int k = 0; k < MapSize; ++k)
        {
            cout << gameBlocks[j][k];
        }
        cout << endl;
    }


	i.close();

    return 0;
}
