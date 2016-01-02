#ifndef YOUBIKEGA_H
#define YOUBIKEGA_H

#include "chromosome.h"
#include "fitnessFunction.h"

class YoubikeGa {
public:
    YoubikeGa(int n_ell, int n_max_gen, int n_station_id);
    ~YoubikeGa();
    void run();
    Chromosome result();
    void output_model();

private:
    bool should_terminate();
    void update_generator();

    double **generator_model;  // 2-D MAP 
    int max_gen;
    int ell;
    int station_id;
    int generation;
    int park;
	FitnessFunction* fitnessFunction;
};

#endif
