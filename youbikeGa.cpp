#include <cstring>
#include "youbikeGa.h"

YoubikeGa::YoubikeGa(int n_ell, int n_max_gen, int n_station_id) {
    Chromosome ch(ell);
    generator_model = new double[ell];
    max_gen = n_max_gen;
    ell = n_ell;
    station_id = n_station_id;
    generation = 0;
}

YoubikeGa::~YoubikeGa() {
    if(generator_model != NULL)
        delete []generator_model;
}

bool YoubikeGa::should_terminate() {
    if(generation >= max_gen)
        return true;
    
    return false;
}