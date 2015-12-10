#include <cstring>
#include <iostream>
#include "youbikeGa.h"
using namespace std;

YoubikeGa::YoubikeGa(int n_ell, int n_max_gen, int n_station_id) {
    generator_model = new double[ell];
    for(int i = 0; i < n_ell; ++i) {
        generator_model[i] = 0.5;
    }

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

void YoubikeGa::run() {
    while(should_terminate()) {
        // 1. generate two chromosome
        // 2. ask fitness function
        // 3. update model
        // 4. generation += 1
    }
}