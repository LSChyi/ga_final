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
    FitnessFunction() {load_data("../include/output.txt");};
//    ~FitnessFunction();
    int calculate_fitness();

private:
    void load_data(string str);
	vector<Norm> model;
};

#endif
