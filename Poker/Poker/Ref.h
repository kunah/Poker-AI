#pragma once

//#include "Headers.h"
#include "Ai.h"
#include "HandEvaluator.h"
#include "Player.h"

using namespace System;
using namespace omp;

struct handa
{
	int prvnikarta;
	int druhakarta;
};

// classa rozhodci, ktera se bude starat o celej chod stolu

class Ref
{
public:
	Ref();
	void rozdani();
	void cards_flop();
	void cards_turn_river();
	void newgame(vector<NN>& boti, int tahh, int a);
	void vyhra(Player& vyherce, NN& loser, int deleni, int& profit_vyherce, int& profit_loser);
	void prohra(NN& vyherce, Player& loser, int deleni, int& profit_vyherce, int& profit_loser);
	void sazka(NN& hrac, int sazka);
	int kombinace(int akce,int id);
	void sazka_hrac(Player& hrac, int sazka);


	vector<int> stul;
	vector<handa> hraci;
	vector<int> ruka_vys; //pole karet ktere se budou pouzivat aby vedel co kazdej hrac ma za karty a co je na stole
	string tah; // abych vedel v jaky casti hry jsem, jestli pReflop flop turn a nebo river nebo fold
	int bigblind;  //jakej je zaklad na bigblind
	float big;  //na zacatku hry se urci kdo je big blind
	int pot; // celkova castka sazky co je na stole
	vector<int> odehrane_karty; //bude si pamatovat co za karty byly odehrany toto kolo, aby je uz nemohl dat znovu

private:
	vector<int>	balicek; //deklarace balicku, kterej je ajko zalozni a budou tam dany karty
	//vector<int>	hraci_balicek; //hraci balicek, kterym se bude hrat abz se neztratila data
	bool kdotah;  // abych vedel kdo je ted momentalne na tahu
	bool jevehre(int karta);  //zjisteni jestli dana parta byla uz hrana

};


//urci nejlepsi handu ze dvou 
//vrati nam to hodnotu co bude za operaci ci vyhra jendoho a nebo deleni
int Ref::kombinace(int akce,int id) {

	HandEvaluator eval;
	int kvalita = 0;
	Hand h = Hand::empty();
	switch (akce)
	{
		//kavlita ruky na preflopu
	case 0:
		 // Final hand must include empty() exactly once!
		h += Hand(hraci[id].prvnikarta) + Hand(hraci[id].druhakarta); // AdAs2s2h2c
		kvalita = eval.evaluate(h);
		return kvalita;
		break;
		//kavlita ruky na flopu
	case 1:
		/*Hand h = Hand::empty();*/ // Final hand must include empty() exactly once!
		h += Hand(stul[0]) + Hand(stul[1]) + Hand(stul[2]) + Hand(hraci[id].prvnikarta) + Hand(hraci[id].druhakarta); // AdAs2s2h2c
		kvalita = eval.evaluate(h);
		return kvalita;
		break;
		//kavlita ruky na turn 
	case 2:
		/*Hand h = Hand::empty();*/ // Final hand must include empty() exactly once!
		h += Hand(stul[0]) + Hand(stul[1]) + Hand(stul[2]) + Hand(stul[3]) + Hand(hraci[id].prvnikarta) + Hand(hraci[id].druhakarta); // AdAs2s2h2c
		kvalita = eval.evaluate(h);
		return kvalita;
		break;
		//kavlita ruky na riveru
	case 3:
/*		Hand h = Hand::empty();*/ // Final hand must include empty() exactly once!
		h += Hand(stul[0]) + Hand(stul[1]) + Hand(stul[2]) + Hand(stul[3]) + Hand(stul[4]) + Hand(hraci[id].prvnikarta) + Hand(hraci[id].druhakarta); // AdAs2s2h2c
		kvalita = eval.evaluate(h);
		return kvalita;
		break;
	default:
		//vydana nam cislo silny ruky, musime potom jeste rozhodnou co se pak bude dit a jak ruka je silnejsi
		//pocet hracu ktery tam jsou
		for (int i = 0; i < 2; i++)
		{
			Hand h = Hand::empty(); // Final hand must include empty() exactly once!
			h += Hand(stul[0]) + Hand(stul[1]) + Hand(stul[2]) + Hand(stul[3]) + Hand(stul[4]) + Hand(hraci[i].prvnikarta) + Hand(hraci[i].druhakarta); // AdAs2s2h2c
			ruka_vys.push_back(eval.evaluate(h)); // 28684 = 7 * 4096 + 12
		}

		//rozhodne kdo ma vyssi kombinaci
		if (ruka_vys[0] % 4096 > ruka_vys[1] % 4096)
		{
			//vyhral prvni
			return 1;
		}
		else if (ruka_vys[1] % 4096 > ruka_vys[0] % 4096)
		{
			//vyhral druhej
			return 2;
		}
		else
		{
			if (ruka_vys[0] % 4096 == 3 || ruka_vys[0] % 4096 == 7)
			{
				vector<int>	vyherce;
				//kojroluje kdo ma vetsi prvni par a podle toho urci vyhru
				for (int i = 0; i < 2; i++)
				{
					if (ruka_vys[i] >= 28673 && ruka_vys[i] < 28685)
					{
						vyherce.push_back(0);
					}
					else if ((ruka_vys[i] >= 12289 && ruka_vys[i] < 12301) || (ruka_vys[i] >= 28685 && ruka_vys[i] < 28697))
					{
						vyherce.push_back(1);
					}
					else if ((ruka_vys[i] >= 12301 && ruka_vys[i] < 12325) || (ruka_vys[i] >= 28697 && ruka_vys[i] < 28709))
					{
						vyherce.push_back(2);
					}
					else if ((ruka_vys[i] >= 12325 && ruka_vys[i] < 12361) || (ruka_vys[i] >= 28709 && ruka_vys[i] < 28721))
					{
						vyherce.push_back(3);
					}
					else if ((ruka_vys[i] >= 12361 && ruka_vys[i] < 12409) || (ruka_vys[i] >= 28721 && ruka_vys[i] < 28733))
					{
						vyherce.push_back(4);
					}
					else if ((ruka_vys[i] >= 124099 && ruka_vys[i] < 12469) || (ruka_vys[i] >= 28733 && ruka_vys[i] < 28745))
					{
						vyherce.push_back(5);
					}
					else if ((ruka_vys[i] >= 124699 && ruka_vys[i] < 12541) || (ruka_vys[i] >= 28745 && ruka_vys[i] < 28757))
					{
						vyherce.push_back(6);
					}
					else if ((ruka_vys[i] >= 12541 && ruka_vys[i] < 12625) || (ruka_vys[i] >= 28757 && ruka_vys[i] < 28769))
					{
						vyherce.push_back(7);
					}
					else if ((ruka_vys[i] >= 12625 && ruka_vys[i] < 12721) || (ruka_vys[i] >= 28769 && ruka_vys[i] < 28781))
					{
						vyherce.push_back(8);
					}
					else if ((ruka_vys[i] >= 12721 && ruka_vys[i] < 12829) || (ruka_vys[i] >= 28781 && ruka_vys[i] < 28793))
					{
						vyherce.push_back(9);
					}
					else if ((ruka_vys[i] >= 12829 && ruka_vys[i] < 12949) || (ruka_vys[i] >= 28793 && ruka_vys[i] < 28805))
					{
						vyherce.push_back(10);
					}
					else if ((ruka_vys[i] >= 12949 && ruka_vys[i] < 13081) || (ruka_vys[i] >= 28805 && ruka_vys[i] < 28817))
					{
						vyherce.push_back(11);
					}
					else if (ruka_vys[i] >= 13081 || ruka_vys[i] >= 28817)
					{
						vyherce.push_back(12);
					}
				}
				if (vyherce[0] > vyherce[1])
				{
					//vyhraje prvni
					return 1;
				}
				else if (vyherce[1] > vyherce[0])
				{
					//vyhraje druhej
					return 2;
				}
				else
				{
					//split
					return 3;
				}
			}
			else
			{
				if (ruka_vys[0] > ruka_vys[1])
				{
					//vyhral prvni
					return 1;
				}
				else if (ruka_vys[1] > ruka_vys[0])
				{
					//vyhra druhej
					return 2;
				}
				else
				{
					//split
					return 3;
				}

			}
		}
		break;
	}


}


//funkce ktera vsazi za bota
//prdani penez a odecteni penez botovi
void Ref::sazka(NN& hrac, int sazka) {
	//pokud chce dat all in
	if (sazka == 0)
	{
		hrac.vsazeno += hrac.mena;
		pot += hrac.mena;
		hrac.mena -= hrac.mena;
		hrac.allin = true;
		tah = "allin";
	}
	else {
		if (hrac.mena <= sazka)
		{
			hrac.vsazeno += hrac.mena;
			pot += hrac.mena;
			hrac.mena -= hrac.mena;
			hrac.allin = true;
			cout << "rise s all inem" << endl;
			tah = "allin";
		}
		else
		{
			hrac.mena -= sazka;
			hrac.vsazeno += sazka;
			pot += sazka;
		}
	}
	hrac.risnultohlekolo = true;
}


//sazi za hrace aby vedel kolik sazi
void Ref::sazka_hrac(Player& hrac, int sazka) {
	//pokud chce dat all in
	cout << sazka << endl;
	if (sazka == 0)
	{
		hrac.vsazeno += hrac.mena;
		pot += hrac.mena;
		hrac.mena -= hrac.mena;
		hrac.allin = true;
		tah = "allin";
	}
	else {
		if (hrac.mena <= sazka)
		{
			hrac.vsazeno += hrac.mena;
			pot += hrac.mena;
			hrac.mena -= hrac.mena;
			hrac.allin = true;
			cout << "rise s all inem" << endl;
			tah = "allin";
		}
		else
		{
			hrac.mena -= sazka;
			hrac.vsazeno += sazka;
			pot += sazka;
		}
	}
	hrac.risnultohlekolo = true;
}

//rozdeli penize tak jak ma
void Ref::vyhra(Player& vyherce, NN& loser, int deleni, int& profit_vyherce, int& profit_loser) {

	switch (deleni)
	{
	case 1:
	case 2:
		if (vyherce.vsazeno >= pot / 2)
		{
			vyherce.mena += pot;
			profit_vyherce += pot - vyherce.vsazeno;
			profit_loser -= loser.vsazeno;
		}
		else {
			vyherce.mena += vyherce.vsazeno * 2;
			loser.mena += (pot - vyherce.vsazeno*2);
			profit_vyherce += vyherce.vsazeno;
			profit_loser += (pot - vyherce.vsazeno * 2) - vyherce.vsazeno;
		}
		break;
	case 3:
		vyherce.mena += vyherce.vsazeno;
		loser.mena += loser.vsazeno;
		break;
	case 4:
		vyherce.mena += pot;
		profit_vyherce += pot - vyherce.vsazeno;
		profit_loser -= loser.vsazeno;
		break;
	default:
		cout << "Nastala chyba" << endl;
		break;
	}

	//vyresetovani pred tim nez zacne dalsi kolo
	vyherce.vsazeno = 0;
	loser.vsazeno = 0;
	vyherce.allin = false;
	loser.allin = false;
	vyherce.slozil = false;
	loser.slozil = false;
	//tah = "preflop";
}

//rozdeli penize tak jak ma
void Ref::prohra(NN& vyherce, Player& loser, int deleni, int& profit_vyherce, int& profit_loser) {

	switch (deleni)
	{
	case 1:
	case 2:
		if (vyherce.vsazeno >= pot / 2)
		{
			vyherce.mena += pot;
			profit_vyherce += pot - vyherce.vsazeno;
			profit_loser -= loser.vsazeno;
		}
		else {
			vyherce.mena += vyherce.vsazeno * 2;
			loser.mena += (pot - vyherce.vsazeno * 2);
			profit_vyherce += vyherce.vsazeno;
			profit_loser += (pot - vyherce.vsazeno * 2) - vyherce.vsazeno;
		}
		break;
	case 3:
		vyherce.mena += vyherce.vsazeno;
		loser.mena += loser.vsazeno;
		break;
	case 4:
		vyherce.mena += pot;
		profit_vyherce += pot - vyherce.vsazeno;
		profit_loser -= loser.vsazeno;
		break;
	default:
		cout << "Nastala chyba" << endl;
		break;
	}
}

//da stul do zacatecniho stavu hry a zmeni bigblinde
void Ref::newgame(vector<NN>& boti, int tahh, int a) {
	stul.clear();
	tahh = abs(tahh);
	bool transfer = false;
	if (tahh % 2 != 0)
	{
		tahh--;
		transfer = true;
	}
	for (int i = 0; i < hraci.size(); i++)
	{
		hraci[i].prvnikarta = 0;
		hraci[i].druhakarta = 0;
		//if (boti[tahh + i].mena == 0)
		//{
		//	boti[tahh + i].mena += 10000;
		//}
		boti[tahh + i].allin = false;
		boti[tahh + i].slozil = false;
		boti[tahh + i].vsazeno = 0;
	}
	odehrane_karty.clear();
	pot = 0;
	ruka_vys.clear();
	tah = "preflop";
	if (tahh % 2 == 0 && transfer == false)
	{
		big = (abs(tahh) + 1.0)/2.0;
	}
	else
	{
		big = (- tahh)/2;
	}
	
}

//roydani karet na turnu a na riveru, koukne se jestli ta karta byla rozdana ci ne
// pote je pak prida na stul jako karty
void Ref::cards_turn_river() {
	int result;

	while (true)
	{
		result = (rand() % 52);
		if (jevehre(result) == true)
		{
			break;
		}
	}
	stul.push_back(result);
	odehrane_karty.push_back(result);
}


//rozdani karet na flopu,  koukne se jestli ta hra byla zahrana ci ne
//pote je pak prida na stul jako karty
void Ref::cards_flop() {

	for (int i = 0; i < 3; i++)
	{
		int result;

		while (true)
		{
			result = (rand() % 52);
			if (jevehre(result) == true)
			{
				break;
			}
		}
		stul.push_back(result);
		odehrane_karty.push_back(result);
	}

}


// kontroluje jestli dana karta uz byla ve hre zahrana a nebo ne
bool Ref::jevehre(int karta) {
	for (unsigned i = 0; i < odehrane_karty.size(); i++)
	{
		if (odehrane_karty[i] == karta)
		{
			return false;
		}
	}
	return true;
}

//random rozdani karet mezi hrace
void Ref::rozdani() {
	for (int i = 0; i < 4; i++)
	{
		int result;

		while (true)
		{
			result = (rand() % 52);
			if (jevehre(result) == true)
			{
				break;
			}
		}
		if (i == 0 || i == 2)
		{
			if (i == 0)
			{
				hraci[0].prvnikarta = result;
				odehrane_karty.push_back(result);
			}
			else
			{
				hraci[0].druhakarta = result;
				odehrane_karty.push_back(result);
			}
		}
		else
		{
			if (i == 1)
			{
				hraci[1].prvnikarta = result;
				odehrane_karty.push_back(result);
			}
			else
			{
				hraci[1].druhakarta = result;
				odehrane_karty.push_back(result);
			}
		}
	}
	tah = "hra";
}

Ref::Ref()
{
	//udeleni ruk hracu kolik potrebujeme
	//2 je pocet hracu, muze se v budoucnu menit podle toho kolik lidi budeme chtit u stolu
	for (int i = 0; i < 2; i++)
	{
		hraci.push_back(handa());
		hraci[i].prvnikarta = -1;
		hraci[i].druhakarta = -1;
	}

	pot = 0;
	//sestaveni balicku, po barvach a kazda stovccka urcuje co je to za barvu jakoby
	//v budoucnu se nam to bude hodit na zjistovani barevnych kiombinaci
	for (int i = 0; i < 52; i++)
	{
		balicek.push_back(i);
	}
	bigblind = 10;
	big = 0;
}