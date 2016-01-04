#ifndef FITNESSFUNCTION_H
#define FITNESSFUNCTION_H

#include <string>
#include <vector>

using namespace std;
typedef struct{
	int minute;
	double mean;
	double var;
}Norm;

class FitnessFunction {
public:
    FitnessFunction(int station_id) { load_data(station_id); };
//    ~FitnessFunction();
    int get_total(){ return total_park; }
	double get_fitness(int* chromosome);
    double calculate_avg_fitness(int* chromosome, int initial_bike_number, int repeat);
	double calculate_fitness(int* chromosome, int _initial_bike_number, int& _end_bike_number, int iteration);
    double calculete_avg_fitness_cache(int* chromosome, int initial_bike_number); // set repeat as const, if you want to change repeat times, change the value 'REPEAT' in fitnessFunction.cpp
private:
    void load_data(int station_id);
    void output(int* instance, string file_name); 
	vector<Norm> model;
	int id;
    int total_park;
    int** _instance;
};

#endif
