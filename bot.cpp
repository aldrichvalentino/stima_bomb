//File : bot.cpp <untuk read file state.json>
#include <fstream>
#include "json.hpp"
#include "player.h"

using namespace std;

using json = nlohmann :: json;

int main ()
{
	json j;
	ifstream i("state.json");
	i >> j;
	json player;
	json gameblocks;
	
	cout << j["MapHeight"] << endl;
	cout << j["MapWidth"] << endl;
	
	player = j["RegisteredPlayerEntities"];
	json dataplayer[player.size()];
	
	player P;
	P.SetData(Name,i,...);
	
	for (int i = 0;i < player.size();i++)
	{
		dataplayer[i] = player.at(i);
	}
	
	cout << dataplayer[0]["Key"] << endl;
	
	gameblocks = j["GameBlocks"];
	
	json state[gameblocks.size()][gameblocks.size()];
	json temp;
	
	for (int i = 0;i < gameblocks.size();i++)
	{
		temp = gameblocks.at(i);
		for (int j = 0;j < gameblocks.size();j++)
		{
			state[i][j] = temp.at(j);
		}
	}
	
	cout << state[0][0]["Entity"]["$type"] << endl;
	
}

