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
//    FitnessFunction(int station_id) { load_data("../include/model.txt"); };
    FitnessFunction(int station_id) { load_data(station_id); };
//    ~FitnessFunction();
    int get_total(){ return model.size(); }
    double calculate_avg_fitness(int*, int, int&, int);
//	double calculate_fitness(int* chromosome, int _initial_bike_number, int& _end_bike_number);
	double calculate_fitness(int* chromosome, int _initial_bike_number, int& _end_bike_number, int iteration);
private:
    void load_data(int station_id);
    void output(int* instance, string file_name); 
	vector<Norm> model;
	int id;
};

#endif
