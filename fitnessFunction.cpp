#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "fitnessFunction.h"
#define DEBUG
using namespace std;

int FitnessFunction::calculate_fitness()
{
	
	double fitness = 0;
	/*
	double* d_instance = new double[model.size()];
	int * instance = new int[model.size()];
	for(int i = 0; i < model.size(); i++){
		default_random_engine generator;
		normal_distribution<double> distribution(model[i].mean, model[i].var);
		d_instance[i] = distribution(generator);
		instance[i] = (int)(d_instace[i]+0.5);
	}

	ofstream d_output, output;
	d_output.open("../output/d_output.csv");
	if(d_output.fail())
		cout << "cannot open file : d_output.csv" << endl;
	else
		for(int i = 0; i < model.size(); i++ ){
			d_output << i+1 << " ," << d_instance[i] << endl;
		    cout << "d_instance[" << i << "] = " << d_instace[i];
	    }

    output.open("../output/output.csv", ios::output);
	if(output.fail())
		cout << "Cannot open file : output.csv" << endl;
	else
		for(int i = 0; i < model.size(); i++){
			output << i+1 << " ," << instance[i] << endl;
			cout << "instance[" << i << "] = " << instance[i] << endl;
	    }

	d_output.close();
	output.close();

    delete [] d_instance;
	delete [] instance;
	*/
	return fitness;
}

void FitnessFunction::load_data(string str)
{
	model.clear();
    ifstream infile;
	infile.open(str.c_str());
	if(!infile)
		cout << "Can not open file : " << str << endl;
	int minute;
	double mean, var;
	while(infile >> minute >> mean >> var){
		Norm n = {.minute = minute, .mean = mean, .var = var};
	    model.push_back(n);
	}
	#ifdef DEBUG
	for(int i = 0; i < model.size(); i++){
		cout << model[i].minute << " " 
		     << model[i].mean << " " 
			 << model[i].var << endl;
	#endif
	}
}
