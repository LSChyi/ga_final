#include <cstring>
#include <iostream>
#include "youbikeGa.h"
#include "chromosome.h"
#include "fitnessFunction.h"
#include <ctime>
using namespace std;

YoubikeGa::YoubikeGa(int n_ell, int n_max_gen, int n_station_id,int population_size) {
    ell = n_ell;
<<<<<<< HEAD
=======
    
    generator_model = new double* [ell];
    for(int i = 0; i < n_ell; ++i) {
		generator_model[i] = new double [park*2+1] ;  //  -n_park ~ 0 ~ +n_park
		for(int i2 =0 ; i2 < park*2+1; i2++){
            generator_model[i][i2] = 1.0/double(park*2+1);
	    }
    }
>>>>>>> 2145d2d625d8b2606d5fa07bdd09746ce57d6c2d
    max_gen = n_max_gen;
    station_id = n_station_id;
    generation = 0;
    fitnessFunction = new FitnessFunction(station_id);
<<<<<<< HEAD
	park = fitnessFunction->get_total();
=======
    park = fitnessFunction->get_total();
>>>>>>> 2145d2d625d8b2606d5fa07bdd09746ce57d6c2d
    sample_f1 =new Chromosome(ell);
    sample_f2 =new Chromosome(ell);
    n = population_size;
    generator_model = new double* [ell];
	clock_t tStart = clock();
    for(int i = 0; i < n_ell; ++i) {
		generator_model[i] = new double [park*2+1] ;  //  -n_park ~ 0 ~ +n_park
		for(int i2 =0 ; i2 < park*2+1; i2++){
            generator_model[i][i2] = 1.0/double(park*2+1);
	    }
    }
    cout << "generator_moel costs : " << (double)((clock()-tStart)/CLOCKS_PER_SEC) << "s" <<  endl;
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
	while(!should_terminate()) {
		cout << endl <<  "Generation " << generation << endl;
        // 1. generate two chromosome
        srand (time(NULL)); // RAND
        cout<<"gerneration :"<<generation<<endl;
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
<<<<<<< HEAD
/*	    int* example_chromosome = new int[48];
		for(int i = 0; i < 48; i++)
			example_chromosome[i] = 0;
		double fitness = fitnessFunction->get_fitness(example_chromosome);
	    cout << "fitness = " << fitness << endl;
*/	    
	    double avg_fitness_1 = fitnessFunction->get_fitness(sample_1);
	    double avg_fitness_2 = fitnessFunction->get_fitness(sample_2);
		cout <<  "f2 = " << avg_fitness_2 << endl;
		sample_f1->output();
		cout <<  "f2 = " << avg_fitness_2 << endl;
		sample_f2->output();
=======
	    double avg_fitness_1 = fitnessFunction->get_fitness(sample_1);
	    double avg_fitness_2 = fitnessFunction->get_fitness(sample_2);
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
>>>>>>> 2145d2d625d8b2606d5fa07bdd09746ce57d6c2d
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
        cout<<" best fitness "<<best<<endl;
        for(int i=0;i<ell;i++)
           cout<<best_c[i]<<' ';
        cout<<endl;
        // 4. generation += 1
        generation += 1;
		
    }
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
