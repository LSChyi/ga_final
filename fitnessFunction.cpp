#include <iostream>
#include <fstream>
#include "fitnessFunction.h"

using namespace std;

int FitnessFunction::calculate_fitness()
{
	return 0;
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
	for(int i = 0; i < model.size(); i++){
		cout << model[i].minute << " " 
		     << model[i].mean << " " 
			 << model[i].var << endl;
	}
}
