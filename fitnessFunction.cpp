#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>
#include <chrono>
#include <ctime>
#include "fitnessFunction.h"
#define NDEBUG
using namespace std;

#define PUNISH -3 // should be negative!!!
#define REPEAT 10

double FitnessFunction::get_fitness(int* chromosome, bool cache){
	if(cache)
		return calculete_avg_fitness_cache(chromosome, (total_park/2));
	else
		return calculate_avg_fitness(chromosome, (total_park/2), REPEAT);
}

double FitnessFunction::calculate_avg_fitness(int* chromosome, int _initial_bike_number, int repeat )
{
	int end_bike_number;
    double avg_fitness = 0;
	int initial_bike_number = _initial_bike_number;
    for(int i = 0; i < repeat; i++){
		double fitness = calculate_fitness(chromosome, initial_bike_number, end_bike_number, i);
		avg_fitness += fitness;
		#ifdef DEBUG
		cout << "fitness = " << setw(8) << fitness << ", end = " << end_bike_number << endl;
		cout << "intial = " << initial_bike_number << endl;
		cout << "end = " << end_bike_number << endl << endl;
	    #endif
		initial_bike_number = end_bike_number;
	}
    avg_fitness /= repeat;
    return avg_fitness;
}

double FitnessFunction::calculate_fitness(int* chromosome, int _initial_bike_number, int& _end_bike_number, int iteration)
{
	double fitness = 0;
	int initial_bike_number = _initial_bike_number;
    int max_bike_number = total_park;//TODO


	double* d_instance = new double[1440];
	int* instance = new int[1440];
	int* instance_sum = new int[1440];

	for(int i = 0; i < model.size(); i++){

        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
		mt19937 generator(seed);
		normal_distribution<double> distribution(model[i].mean, model[i].var);
		d_instance[i] = distribution(generator);

		instance[i] = (d_instance[i]>-0.5)?(int)(d_instance[i]+0.5):(int)(d_instance[i]-0.5);
        #ifdef DEBUG
		cout << "d_instance[" << i << "] = " << d_instance[i] << endl;
		cout << "  instance[" << i << "] = " << instance[i] << endl;
	    #endif
	}	
	
	instance_sum[0] = initial_bike_number+chromosome[0];
	fitness += (chromosome[0]==0) ? 0 : PUNISH;

	for(int i = 1; i< model.size(); i++){
		instance_sum[i] = instance_sum[i-1]+instance[i];
	    if( i%30 == 0){
	        instance_sum[i] += chromosome[(int)(i/30)];
	        fitness += (chromosome[(int)(i/30)]==0) ? 0 : PUNISH - abs(chromosome[(int)(i/30)]*-1);
		}
		if( instance_sum[i] < 0 ){
			fitness += instance_sum[i];
		    instance_sum[i] = 0;
		}
	    else if( instance_sum[i] > max_bike_number ){
			fitness -= (instance_sum[i]-max_bike_number);
		    instance_sum[i] = max_bike_number;
		}
	}
    _end_bike_number = instance_sum[model.size()-1];

	stringstream ss1;
    ss1 << "../output/totalCSV/total" << id << "_" << iteration << ".csv";
    output(instance_sum, ss1.str());


    delete [] d_instance;
	delete [] instance;
	delete [] instance_sum;
	return fitness;
}

void FitnessFunction::output(int* instance, string file_name)
{
	ofstream fout(file_name);
	if(fout.fail())
		cerr << "Cannot open file : " << file_name << endl;
	else
		for(int i = 0; i < model.size(); i++){
			fout << (i+1) << " ," << instance[i] << endl;
            #ifdef DEBUG
			cout << file_name << "[" << i << "] = " << instance[i] << endl;
            #endif
	    }

	fout.close();
}

void FitnessFunction::load_data(int station_id)
{
	id = station_id;
	model.clear();
	stringstream ss;
	ss << station_id;
    string str = "../include/20151227model.txt";
	ifstream infile;
	infile.open(str);
	if(!infile)
		cerr << "Can not open file : " << str << endl;
	int minute;
	double mean, var;
	infile >> total_park;
	while(infile >> minute >> mean >> var){
		Norm n = {.minute = minute, .mean = mean, .var = var};
	    model.push_back(n);
	}
	#ifdef DEBUG
	for(int i = 0; i < model.size(); i++){
		cout << model[i].minute << " " 
		     << model[i].mean << " " 
			 << model[i].var << endl;
	}
	#endif

	// for cache fitness
	double tmp_distance;
	_instance = new int* [REPEAT];
	for(int i = 0; i < REPEAT; ++i) {
		_instance[i] = new int[14400];

		for(int j = 0; j < model.size(); ++j) {
	        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
			mt19937 generator(seed);
			normal_distribution<double> distribution(model[j].mean, model[j].var);
			tmp_distance = distribution(generator);
			_instance[i][j] = (tmp_distance>-0.5)?(int)(tmp_distance+0.5):(int)(tmp_distance-0.5);
		}
	}
}

double FitnessFunction::calculete_avg_fitness_cache(int* chromosome, int initial_bike_number) {
	double avg_fitness = 0;
	int end_bike_number = 0;

	for(int i = 0; i < REPEAT; ++i) {
		avg_fitness += calculete_fitness_cache(chromosome, initial_bike_number, end_bike_number, i);
		initial_bike_number = end_bike_number;
	}

	return avg_fitness/REPEAT;
}

double FitnessFunction::calculete_fitness_cache(int* chromosome, int initial_bike_number, int& end_bike_number, int iteration) {
	int instance_sum[14400];
	double fitness = 0.0;

	int chromosome_idx;

	fitness += (chromosome[0] == 0) ? 0 : PUNISH;// - abs(chromosome[0]*-1);
	instance_sum[0] = initial_bike_number + chromosome[0] + _instance[iteration][0];
	// carry too much bike to here
	if(instance_sum[0] > total_park) {
		fitness += (instance_sum[0] - total_park)*(-1);
		instance_sum[0] = total_park;
	}
	// bike number is less then 0 at begining
	else if(instance_sum[0] < 0) {
		fitness += instance_sum[0];
		instance_sum[0] = 0;
	}

	for(int i = 1; i < model.size(); ++i) {

		if(i % 30 == 0) {
			chromosome_idx = (int)(i/30);

			// punish if chromosome carry bikes not equal to 0
			fitness += (chromosome[chromosome_idx] == 0) ? 0 : PUNISH;// - abs(chromosome[chromosome_idx]*-1);

			// calculate how many bikes after put to(take away) here, and before truncate to park number
			instance_sum[i] = instance_sum[i-1] + chromosome[chromosome_idx];
		}
		else {
			instance_sum[i] = instance_sum[i-1];
		}

		// add current bike borrow
		instance_sum[i] += _instance[iteration][i];

		if(instance_sum[i] > total_park) {
			fitness += (instance_sum[i] - total_park)*(-1);
			instance_sum[i] = total_park;
		}
		else if(instance_sum[i] < 0) {
			fitness += instance_sum[i];
			instance_sum[i] = 0;
		}
	}

	end_bike_number = instance_sum[model.size() - 1];

	return fitness;
}