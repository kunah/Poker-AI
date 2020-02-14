#pragma once

#include "GameEngine.h"
#include <algorithm>

//struktura na porovnani id bota  a jeho profit
struct MyStruct
{
	int profit;
	int id;
};


//vrati true a nebo false jestli je vetsi a nebo mensi dany cislo, pomoc pro funkci sort
bool compareInterval(MyStruct i1, MyStruct i2)
{
	return (i1.profit > i2.profit);
}


//vyselektuje boty ktery se maji zmenit
//nakombinuje jich z poloviny ktera vyhrala
//piseme to rovnoou do slozky, aby jsme usetrili cas
void Trenuj(vector<NN>& boti,vector<unsigned> topology) {
	
	vector<MyStruct> kdo_prezije(boti.size());
	for (int i = 0; i < kdo_prezije.size(); i++)
	{
		kdo_prezije[i].profit = boti[i].profit;
		kdo_prezije[i].id = boti[i].id;
	}
	
	sort(kdo_prezije.begin(), kdo_prezije.end(), compareInterval);

	unsigned numLayers = topology.size();
	for (int c = 0; c < boti.size()/2; c++)
	{
		int id = kdo_prezije[c + boti.size() / 2].id;
		int nejlepsi_id = kdo_prezije[0].id;
		string jmeno = "saves/" + to_string(boti[id].id) + ".txt";
		ofstream remove;
		remove.open(jmeno, ios::trunc);
		remove.close();
		fstream myfile;
		myfile.open(jmeno, ios::out | ios::app);
		cout << "Krizi se bot c: " << id << " s nejlepsim botem c: " << nejlepsi_id << endl;
		for (int i = 0; i < numLayers - 1; i++)
		{

			for (int a = 0; a < topology[i]; a++)
			{
				for (int b = 0; b < topology[i + 1]; b++)
				{
					int kdo = (int)(10.0 * rand() / double(RAND_MAX));
					if (kdo == 1)
					{
						boti[id].layers[i][a].outputWeights[b].weight = boti[nejlepsi_id].layers[i][a].outputWeights[b].weight;

					}
					else if (kdo == 4 || kdo == 3)
					{
						boti[id].layers[i][a].outputWeights[b].weight = rand() / double(RAND_MAX);
					}
					myfile.precision(11);
					myfile << boti[id].layers[i][a].outputWeights[b].weight << endl;
				}
			}
		}
		myfile.close();
	}
}


////ulozi do knihovny nove boty, ktere jsme preklonovali
//void ulozdoknihovny(NN boti) {
//	for (int i = 0; i < boti.size(); i++)
//	{
//		string jmeno = "saves/" + to_string( boti[i].id) + ".txt";
//
//		fstream myfile(jmeno, ios_base::in);
//
//		//kdyz neexistuje slozka pro danyho bota, vytvori se
//		if (!myfile)
//		{
//			myfile.open(jmeno, ios_base::out);
//			cout << "slozka vytvorena" << endl;
//		}
//		else
//		{
//			cout << "existuje" << endl;
//		}
//		myfile.close();;
//	}
//}