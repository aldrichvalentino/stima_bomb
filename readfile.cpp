#include "json.hpp"
#include <fstream>
using namespace std;
using nlohmann::json;

int main ()
{
	ifstream i ("state.json");
	json j;
	i >> j;
	for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		if(it.key() == "GameBlocks")
		{
			cout << it.key() << " : " << it.value() << endl;
		}
	}
	
	//cout << j["/RegisteredPlayerEntities/0/Key"_json_pointer] << endl;
	
	/*
	string myName;
	myName = j["RegisteredPlayerEntries:Name"].get<string>();
	cout << myName << endl;
	*/
}
