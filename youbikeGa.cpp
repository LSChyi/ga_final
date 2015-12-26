#include <cstring>
#include <iostream>
#include "youbikeGa.h"
#include "chromosome.h"
#include "fitnessFunction.h"
using namespace std;

YoubikeGa::YoubikeGa(int n_ell, int n_max_gen, int n_station_id, int n_park) {
    generator_model = new double* [ell];
    for(int i = 0; i < n_ell; ++i) {
		generator_model[i] = new double [n_park*2+1] ;  //  -n_park ~ 0 ~ +n_park
		for(int i2 =0 ; i2 < n_park; i2++){
            generator_model[i][i2] = 1.0/double(n_park*2+1);
	    }
    }
    max_gen = n_max_gen;
    ell = n_ell;
    station_id = n_station_id;
    generation = 0;
	fitnessFunction = new FitnessFunction(station_id);
	park = fitnessFunction->get_total();
}

YoubikeGa::~YoubikeGa() {
    if(generator_model != NULL)
        delete []generator_model;
}

bool YoubikeGa::should_terminate() {
	// generation >= max_gen
    if(generation >= max_gen)   
        return true;
    // all converge  , all > 0.999
    int temp = 0; 
    for (int i = 0 ; i < ell; i++){
		 bool check = true;
		 for (int i2 = 0 ;i2 < park ; i2++){
		     if (generator_model[i][i2]>0.999){
			     check = false;
			     break;
			 }    
		  if(check)
		     temp++;
		 }			
	}
	if(temp == ell)
	  return true;
	  
    return false;
}

void YoubikeGa::run() {
	/*There is something wrong with the chromosome
	  so I test my part here,
	  the following part could be deleted once chromosome is fixed*/
	//fitnessFunciton Test
	int* example_chromosome = new int[48];
	for(int i = 0; i < 48; i++)
		example_chromosome[i] = 0;
	example_chromosome[3] = -40;
	example_chromosome[30] = 40;

	int fitness = fitnessFunction->calculate_fitness(example_chromosome);
	cout << "fitness = " << fitness << endl;
	//////////////////////
    
	
	while(should_terminate()) {
        // 1. generate two chromosome
        Chromosome s_1(ell),s_2(ell);
        int* sample_1;
        int* sample_2;
        sample_1=s_1.sample(generator_model,park);
        sample_2=s_2.sample(generator_model,park);
		// 2. ask fitness function
		int* ex_chromosome = new int[48];
		for(int i = 0; i < 48; i++)
			ex_chromosome[i] = 0;
		int fitness = fitnessFunction->calculate_fitness(ex_chromosome);
		cout << "fitness = " << fitness << endl;
        // 3. update model
        
        // 4. generation += 1
        generation += 1;
		
    }
}
