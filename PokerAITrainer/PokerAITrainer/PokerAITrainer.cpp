// Firstc++AI.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//


#include "Trainer.h"

int stop;
string heslo;

void zastav() {
	stop = 101;
}

void vstup() {
	while (true)
	{
		getline(cin, heslo);
		if (heslo == "poker")
		{
			zastav();
			cout << "program byl ukoncen na druhem vlakne" << endl;
		}
	}

}

int main()
{
	
	cout << "Hello World!\n";

	srand(time(NULL));

	//pole botu kteri se budou trenovat
	vector <NN> boti;
	Ref mozek;
	int pocetbotu = 50;
	//sestaveni NN a urceni topologie
	vector <unsigned> topology;
	topology.push_back(9);
	for (int i = 0; i < 50; i++)
	{
		topology.push_back(30);
	}
	topology.push_back(10);
	topology.push_back(4);
	cout << "Topologie NN ma strukturu " << topology[0] << " " << topology[1] << " " << topology[2] << endl;
	
	//vygenerovani botu s danou toppologii
	//prida jim zakladni vklad ke stollu a to je 1000
	//na treninku maji limit 1000, abz boti nehazeli neuveritelne satzky, ale aby se furt trenovali, tak kdyz prohrajou tak se jim prictou dalsi penize ale furt budou v minusu
	
	vytvorenibota(boti, topology,pocetbotu);
	//ulozdoknihovny(boti);

	vector<double> input(9), target(3),  results(4); 
	for (int i = 0; i < input.size(); i++)
	{
		input[i] = 0;
	}

	//zakladni drheho threadu ktery bude se koukat pro input
	thread t1(vstup);
	t1.detach();

	clock_t start;
	double duration;
	start = clock();
	int opakovani = 1;
	int pocether = 1;
	//trenink NN
	for (stop = 1; stop <= 100; stop++)
	{
		//tri pary ktery se budou stridat
		for (int a = 0; a < pocetbotu/2; a++)
		{
			cout << "par cislo: " << a << endl;

			mozek.big = -a;
		
			for (int b = 1; b <= 10; b++)
			{
				int akce = 0;
				cout << "Hra cislo: " << b << endl;
				int tah = 2 * mozek.big;

				// PREFLOP
				mozek.rozdani();
				//big small,zakladni vklad
				mozek.sazka(boti[abs(tah)], 10);
				mozek.sazka(boti[abs(tah - 1)], 5);

				//reset reise, protoze pred dalsim kolim muzou pak zase prikladat
				reset_raise(boti);

				/*input_2.push_back(mozek.hrac_2[0]);
				input_2.push_back(mozek.hrac_2[1]);
				for (int i = 0; i < 5; i++)
				{
					input_2.push_back(0);
				}
				input_2.push_back(boti[1].mena);*/


				//----------PREFLOP-----------
				//2 je pocet hracu, muze se to menit
				cout << "PREFLOP" << endl;

				akce_hracu(input, results, mozek, tah, boti,akce);

				cout << "FLOP" << endl;

				reset_raise(boti);
				tah = 2 * mozek.big;
				//-----------FLOP-------------

				if (mozek.tah != "end")
				{
					akce++;
					mozek.cards_flop();
					if (mozek.tah != "allin")
					{
						akce_hracu(input, results, mozek, tah, boti,akce);
					}
				}

				cout << "TURN" << endl;

				reset_raise(boti);
				tah = 2 * mozek.big;
				//-----------TURN----------
				if (mozek.tah != "end")
				{
					akce++;
					mozek.cards_turn_river();

					if (mozek.tah != "allin")
					{
						akce_hracu(input, results, mozek, tah, boti,akce);
					}
				}

				cout << "RIVER" << endl;

				reset_raise(boti);
				tah = 2 * mozek.big;
				//------------RIVER----------
				if (mozek.tah != "end")
				{
					akce++;
					mozek.cards_turn_river();

					if (mozek.tah != "allin")
					{
						akce_hracu(input, results, mozek, tah, boti,akce);
					}
				}
				tah = 2 * mozek.big;

				//hodnoceni kdyz oba dohrajou na konec stolu
				if (mozek.tah != "end")
				{

					int vyherce = mozek.kombinace(5,4);
					if (vyherce == 1)
					{
						mozek.vyhra(boti[2 * a], boti[2 * a + 1], vyherce, boti[2*a].profit, boti[2 * a + 1].profit);
						cout << "vyhral bot c "<<2*a << " a vyhral stul v hodnote: " << mozek.pot << endl;
						//Trenuj(boti[2 * a + 1], topology);
					}
					else if (vyherce == 2)
					{
						mozek.vyhra(boti[2 * a + 1], boti[2 * a], vyherce, boti[2 * a + 1].profit, boti[2 * a].profit);
						cout << "vyhral bot c "<<2*a+1<<" a vyhral stul v hodnote: " << mozek.pot << endl;
						//Trenuj(boti[2 * a], topology);
					}
					else
					{
						mozek.vyhra(boti[2 * a], boti[2 * a + 1], vyherce, boti[2 * a].profit, boti[2 * a + 1].profit);
						cout << "remiza stul v hodnote: " << mozek.pot << endl;
					}
				}
				//hodnoceni kdyz jeden slozi 
				else if (boti[2 * a + 1].slozil == true)
				{
					mozek.vyhra(boti[2 * a], boti[2 * a + 1], 4, boti[2 * a].profit, boti[2 * a + 1].profit);
					cout << "vyhral bot c "<< 2*a<< " vyhral stul v hodnote: " << mozek.pot << endl;
					//Trenuj(boti[2 * a + 1], topology);
				}
				else if (boti[2 * a].slozil == true)
				{
					mozek.vyhra(boti[2 * a + 1], boti[2 * a], 4, boti[2 * a + 1].profit, boti[2 * a].profit);
					cout << "vyhral bot c "<< 2*a+1<<" a vyhral stul v hodnote: " << mozek.pot << endl;
					//Trenuj(boti[2*a], topology);
				}
				//hodmoceni kdyz jeden je v all inu
				else if (boti[2 * a + 1].allin == true)
				{
					mozek.vyhra(boti[2 * a], boti[2 * a + 1], 4, boti[2 * a].profit, boti[2 * a + 1].profit);
					cout << "vyhral bot c " << 2 * a << " vyhral stul v hodnote: " << mozek.pot << endl;
					//Trenuj(boti[2 * a + 1], topology);
				}
				else if (boti[2 * a].allin == true)
				{
					mozek.vyhra(boti[2 * a + 1], boti[2 * a], 4, boti[2 * a + 1].profit, boti[2 * a].profit);
					cout << "vyhral bot c " << 2 * a + 1 << " a vyhral stul v hodnote: " << mozek.pot << endl;
					//Trenuj(boti[2*a], topology);
				}
				else
				{
					cout << "Chyba pri vypisu kdo vyhral p slozeni" << endl;
				}
				if (boti[2*a].mena == 0 || boti[2*a+1].mena == 0)
				{
					b = 11;
				}
				pocether++;
				mozek.newgame(boti ,tah, a);
			}
			cout << endl;
			cout << endl;
			cout << endl;
		}

		//trenink
		//polovina nejlepsich prezije druha polovina se prekrizi s nejlepsim a jednims  prezivsim
		Trenuj(boti, topology);

		//nastaveni hry do puvodniho stavu
		stats_reset(boti);

		if (stop == 101)
		{
			vector <double> info;
			string ahoj;
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			start = clock();
			//ulozi hodnoty kolik je nadefinovano botu max, kolik se odehralo her a cas jak dlouho uz to jde
			for (int c = 0; c < 2; c++)
			{
				fstream myfile;
				if (c == 0)
				{
					myfile.open("saves/info.txt", ios::in | ios::app);
					for (int b = 0; b < 3; b++)
					{
						if (b == 1)
						{
							info.push_back(50);
						}
						else
						{
							info.push_back(0);
						}
						getline(myfile, ahoj);
						if (ahoj != "")
						{
							info[b] = stod(ahoj);
						}
					}
					myfile.close();
				}
				else
				{
					myfile.open("saves/info.txt", ios::out);
					myfile.precision(11);
					myfile << info[0] + pocether << endl << info[1] << endl << info[2] + duration << endl;
					myfile.close();
				}
			}
		}
		else if (stop == 100) { stop = 1; }

		//udelat a vypsat input
		//myNet.input(input);

		//vypsat vysledek
		//myNet.vysledek(results);
		//vypis("Vysledek: ", results);;

		//spravnej(input, target);
		//vypis("Spravnej vysledek: ", target);
		//cout << "Spravnej vysledek: " << target[0] << endl;


		//myNet.generace(target);

		//cout << "NN prumerny error:	" << myNet.getRecentAverageError() << endl << endl;
		opakovani++;
	}


	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << endl;
	cout << endl;

	cout << "Hotovo!!! V case:" << duration << "s" << endl;


}

// Spuštění programu: Ctrl+F5 nebo nabídka Ladit > Spustit bez ladění
// Ladění programu: F5 nebo nabídka Ladit > Spustit ladění

// Tipy pro zahájení práce:
//   1. K přidání nebo správě souborů použijte okno Průzkumník řešení.
//   2. Pro připojení ke správě zdrojového kódu použijte okno Team Explorer.
//   3. K zobrazení výstupu sestavení a dalších zpráv použijte okno Výstup.
//   4. K zobrazení chyb použijte okno Seznam chyb.
//   5. Pokud chcete vytvořit nové soubory kódu, přejděte na Projekt > Přidat novou položku. Pokud chcete přidat do projektu existující soubory kódu, přejděte na Projekt > Přidat existující položku.
//   6. Pokud budete chtít v budoucnu znovu otevřít tento projekt, přejděte na Soubor > Otevřít > Projekt a vyberte příslušný soubor .sln.
