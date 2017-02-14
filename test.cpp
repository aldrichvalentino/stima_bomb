#include "json.hpp"
#include <fstream>
using namespace std;
using nlohmann::json;

int main ()
{
	ifstream i ("state.json");
	json j;
	i >> j;
	/*for (json::iterator it = j.begin(); it != j.end(); ++it)
	{
		if(it.key() == "GameBlocks")
		{
			cout << j["/GameBlocks/0/0/Entity/Location"_json_pointer] << endl;
		}
	}*/

	//Tiap GameBlocks punya 6 komponen
	cout << j["/GameBlocks/1/1/Bomb"_json_pointer] << endl;
	cout << j["/GameBlocks/1/1/Entity/$type"_json_pointer] << endl;
	cout << j["/GameBlocks/1/1/Entity/Location"_json_pointer] << endl; //milik $type, klo null ini gaada
	cout << j["/GameBlocks/1/1/PowerUp"_json_pointer] << endl;
	cout << j["/GameBlocks/1/1/Exploding"_json_pointer] << endl;
	cout << j["/GameBlocks/1/1/Location"_json_pointer] << endl;

	//Buat bomb klo ga null ada tambahan : owner, bombradius, bomb timer, isexploding, location


	//cout << j["/RegisteredPlayerEntities/0/Key"_json_pointer] << endl;

	/*
	string myName;
	myName = j["RegisteredPlayerEntries:Name"].get<string>();
	cout << myName << endl;
	*/

	return 0;
}
