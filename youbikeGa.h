#ifndef YOUBIKEGA_H
#define YOUBIKEGA_H

#include "chromosome.h"
#include "fitnessFunction.h"

class YoubikeGa {
public:
    YoubikeGa(int n_ell, int n_max_gen, int n_station_id,int population_size);
    ~YoubikeGa();
    void run();
    Chromosome result();
    void output_model();
     void ecga();
    void selection();
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
    Chromosome* sample_f1;
    Chromosome* sample_f2;
    int n;
    int tn;
	int nfe;
    Chromosome* best_chromosome;
    double best_fitness;
};

#endif
