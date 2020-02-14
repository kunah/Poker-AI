#pragma once
// Firstc++AI.cpp : Tento soubor obsahuje funkci main. Provádìní programu se tam zahajuje a ukonèuje.
//

#include "Headers.h"

class Neuron;

typedef vector<Neuron> Layer;	// definice Layer ze se skalda z Neuron == jako Neuron[] Layer


//struktura diky ktery muzeme uschovat dve promene jako jednu
struct Connection
{
	double weight;
	double deltaWeight;
};
//class neuron ktera definuje jednotlivy funkce ktera ma kazde neuron
class Neuron
{
public:
	Neuron(unsigned numOutputs, unsigned myIndex, vector<double>& input_vals, int& line, int neuron);
	void setOutputVal(double val) { output = val; }
	double getOutputVal(void) const { return output; }
	void input(const Layer& prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer& nextLayer);
	void updateInputWeights(Layer& prevLayer);
	void Training(unsigned numOutputs);

	vector<Connection> outputWeights;

private:
	static double eta;
	static double alpha;
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double randomWeight(void) { return rand() / double(RAND_MAX); }
	double sumDOW(const Layer& nextLayer);
	double output;
	//double n_input;
	unsigned c_myIndex;
	double gradient;

};

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

void Neuron::updateInputWeights(Layer& prevLayer) {
	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		Neuron& neuron = prevLayer[n];
		double oldDeltaWeight = neuron.outputWeights[c_myIndex].deltaWeight;
		double newDeltaWeight = eta * neuron.getOutputVal() * gradient + alpha * oldDeltaWeight;
		neuron.outputWeights[c_myIndex].deltaWeight = newDeltaWeight;
		neuron.outputWeights[c_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::sumDOW(const Layer& nextLayer) {
	double sum = 0.0;
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += outputWeights[n].weight * nextLayer[n].gradient;
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer& nextLayer) {
	double dow = sumDOW(nextLayer);
	gradient = dow * Neuron::transferFunctionDerivative(output);
}

void Neuron::calcOutputGradients(double targetVal) {
	double delta = targetVal - output;
	gradient = delta * Neuron::transferFunctionDerivative(output);
}

//vyda nam to vysledek mezi -1 a 1
double Neuron::transferFunction(double x) {
	return tanh(x);
}

//derivace tanh funkce y transferfunction
double Neuron::transferFunctionDerivative(double x) {
	return 1.0 - x * x;
}

//matematickej vypocet ktery nam vyda vysledek toho neuronu
void Neuron::input(const Layer& prevLayer) {

	double sum = 0.0;

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutputVal() * prevLayer[n].outputWeights[c_myIndex].weight;
	}
	//n_input = sum;
	output = Neuron::transferFunction(sum);
}


//vytvori konekce s kazdym jinym neuronem s nadchazejici rady
Neuron::Neuron(unsigned numOutputs, unsigned myIndex, vector<double>& input_vals,int& line, int neuron) {

	for (int i = 0; i < numOutputs; i++)
	{
		outputWeights.push_back(Connection());

		if (line >= input_vals.size())
		{
			outputWeights.back().weight = randomWeight();
		}
		else
		{
			outputWeights.back().weight = input_vals[line];
		}
		line++;
	}

	c_myIndex = myIndex;
}

//struktura NN
// defubuce promenych a funkci v class NN(neuronova sit)
class NN
{
public:
	NN(const vector<unsigned>& topology, int idd);
	void input(const vector<double>& input);
	void vysledek(vector<double>& results) const;


	int mena; //pocet penez kolik ma dany hrac
	int vsazeno; // kolik vsadil behem toho kolo, pomuze nam to pri rozdelovani
	bool allin;
	int id;
	bool risnultohlekolo;
	bool slozil;
	int profit;
	vector<double> input_vals;
	vector<Layer> layers;		// definice layers, skalda se z Layzers == layers[layerNum][neuronNum]


};

void NN::vysledek(vector<double>& results) const {
	results.clear();
	for (unsigned n = 0; n < layers.back().size() - 1; ++n)
	{
		results.push_back(layers.back()[n].getOutputVal());
	}
}



//priradi input k jednotlivzm hodnotam neuron v prvni vrstve
void NN::input(const vector<double>& input) {
	assert(input.size() == layers[0].size() - 1);

	for (unsigned i = 0; i < input.size(); ++i)
	{
		layers[0][i].setOutputVal(input[i]);
	}

	for (unsigned layerNum = 1; layerNum < layers.size(); ++layerNum)
	{
		Layer& prevLayer = layers[layerNum - 1];
		for (unsigned n = 0; n < layers[layerNum].size() - 1; ++n)
		{
			layers[layerNum][n].input(prevLayer);
		}
	}
}


//vytvoreni NN podle topologie kterou jsme si zadli
//pro debug to vypise kolikaty a jakej neuron je vytvoren a na jakym miste
//pro kazdej layer vztvorime jeden neuron navic, kterej sa nazyva bios
NN::NN(const vector<unsigned>& topology, int idd)
{
	id = idd;

	string jmeno = "saves/" + to_string(id) + ".txt";
	fstream myfile;
	myfile.open(jmeno, ios::in | ios::app);
	while (!myfile.eof())
	{
		string ahoj;
		getline(myfile, ahoj);
		if (ahoj == "")
		{
			break;
		}
		input_vals.push_back(stod(ahoj));
	}

	unsigned numLayers = topology.size();

	int line = 0;
	int neuron = 0;
	//udelani radku topologie
	for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		//vutvoreni jednotlivych neuronu v Layer
		if (layerNum == 48)
		{
			cout << "ahoj"<<endl;
		}
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			neuron++;
			layers.back().push_back(Neuron(numOutputs, neuronNum, input_vals, line,neuron));
			/*cout << "Vytvoreni neuronu!!\n";
			cout << "Neuron cislo: " << neuron << "\n";
			cout << "Layer: " << layerNum << " a cislo neuronu v Layeru: " << neuronNum + 1 << endl;*/
		}
		layers.back().back().setOutputVal(1.0);
	}
}

//class Ai
//{
//	public:
//		int ahoj;
//
//};

