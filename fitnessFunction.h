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
    FitnessFunction(int station_id) { load_data("../include/model.txt"); };
//    FitnessFunction(int station_id) {load_data(station_id);};
//    ~FitnessFunction();
    int get_total(){ return 88; }
    int calculate_fitness();
private:
    void renew_model(string newOutFile);
    void load_data(string str);
	vector<Norm> model;
};

#endif
