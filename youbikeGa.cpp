#include <cstring>
#include <iostream>
#include "youbikeGa.h"
#include "chromosome.h"
#include "fitnessFunction.h"
#include <ctime>
using namespace std;

YoubikeGa::YoubikeGa(int n_ell, int n_max_gen, int n_station_id,int population_size) {
    nfe = 0;
	ell = n_ell;
    max_gen = n_max_gen;
    station_id = n_station_id;
    generation = 0;
    fitnessFunction = new FitnessFunction(station_id);
	park = fitnessFunction->get_total();
    sample_f1 =new Chromosome(ell);
    sample_f2 =new Chromosome(ell);
    n = population_size;
    generator_model = new double* [ell];
    for(int i = 0; i < n_ell; ++i) {
		generator_model[i] = new double [park*2+1];
		for(int i2 =0 ; i2 < park*2+1; i2++){
            generator_model[i][i2] = 0.5/double(park*2+1);
	    }
        generator_model[i][park] = 0.5;
    }
    best_fitness = std::numeric_limits<double>::infinity()*(-1);
    best_chromosome = new Chromosome(ell);
}

YoubikeGa::~YoubikeGa() {
    if(generator_model != NULL) {
        for(int i = 0; i < ell; ++i) {
            delete []generator_model[i];
        }

        delete []generator_model;
    }
}

bool YoubikeGa::should_terminate() {
	// generation >= max_gen
    if(generation >= max_gen)   
        return true;
    // all converge  , all > 0.999
    int temp = 0; 
    for (int i = 0 ; i < ell; i++){
		 bool check = true;
		 for (int i2 = 0 ;i2 < park*2+1 ; i2++){
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
        int* chromosome = new int[48];
        for(int i = 0; i < 48; ++i) {
            chromosome[i] = 0;
        }
        clock_t tStart = clock();
        double raw_fitness = fitnessFunction->get_fitness(chromosome, true, true);
        cout << "raw fitness: " << raw_fitness << endl;
        cout << "press enter to start optimization" << endl;
        cin.get();
        double fCost = (double)((clock()-tStart)*1000/CLOCKS_PER_SEC);
        cout << "call F cost: " << fCost << "ms" <<  endl;
        cout << "one Generation cost: " << fCost * 30 * 2/1000 << "s" << endl;
            
	while(!should_terminate()) {
		cout << endl <<  "Generation " << generation << endl;
        // 1. generate two chromosome
        srand (time(NULL)); // RAND
        int* sample_1;
        int* sample_2;
        int tournament = 30; 
        double best = -10000 ; 
        int* best_c; 
        while (tournament --)
        {
    	    sample_1=sample_f1->sample(generator_model,park);
            sample_2=sample_f2->sample(generator_model,park);
    	    // 2. ask fitness function
    	    double avg_fitness_1 = fitnessFunction->get_fitness(sample_1, true, false);
    	    nfe++;
    	    double avg_fitness_2 = fitnessFunction->get_fitness(sample_2, true, false);
            nfe++;
    	    if(avg_fitness_1>best)
                {
                   best =avg_fitness_1;
                   best_c = sample_1;  
                }
            if(avg_fitness_2>best)
            {
                best =avg_fitness_2;
                best_c = sample_2;  
            }
            // 3. update model
            if (avg_fitness_1 > avg_fitness_2){
                            for(int i = 0 ; i< ell ; i++){
    			   double update_value = 1.0/n;	
    			   if(generator_model[i][sample_2[i]+park]<update_value)	
    		              update_value = generator_model[i][sample_2[i]+park]; 
    			   generator_model[i][sample_2[i]+park]-= update_value; 	
    			   generator_model[i][sample_1[i]+park]+= update_value;
                              
    			 }
    	    }
            else if (avg_fitness_1 < avg_fitness_2){
                for(int i = 0 ; i< ell ; i++){
        		    double update_value = 1.0/n;	
        		    if(generator_model[i][sample_1[i]+park]<update_value)	
                        update_value = generator_model[i][sample_1[i]+park]; 
        	        generator_model[i][sample_1[i]+park]-= update_value; 	
        	        generator_model[i][sample_2[i]+park]+= update_value;
    	        }
            }
        }
        cout << "Best fitness : "<< best << endl;
        for(int i=0;i<ell;i++)
           cout<<best_c[i]<<' ';
        cout<<endl;
        // 4. generation += 1
        generation += 1;
        if(best > best_fitness) {
            best_fitness = best;
            best_chromosome->init(best_c);
        }
		
    }
    cout << "terminate" << endl;
	cout << "NFE = " << nfe << endl;
    cout << "best chromosome: ";
    best_chromosome->output();
    cout << "fitness: " << best_fitness << endl;
}

void YoubikeGa::output_model() {
    cout << "[" << endl;
    for(int i = 0; i < ell; ++i) {
        cout << "    " << "[ ";
        for(int j = 0; j < ell; ++j) {
            cout << generator_model[i][j] << " ";
        }
        cout << "    " << "]" << endl;
    }
    cout << "]" << endl;
}
