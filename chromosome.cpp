#include <iostream>
#include <cstring>
#include "chromosome.h"
#include <time.h>
#include <cstdlib>

using namespace std;

Chromosome::Chromosome(int ell) {
    genes = new int[ell];
    size = ell;
}

Chromosome::~Chromosome() {
    if(genes != NULL)
        delete []genes;
}

void Chromosome::init(int values[]) {
    for(int i = 0; i < size; ++i) {
        genes[i] = values[i];
    }
}

void Chromosome::output() {
    cout << "[ ";
    for(int i = 0; i < size; ++i) {
        cout << genes[i] << " ";
    }
    cout << "]" << endl;
}
void Chromosome::sample(double** p_vec,int n_park,int* origin) {

	for(int i = 0 ;i < size; i++){
		
		int a = rand();
		double dise = double((a%(2*n_park+1)))/(2*n_park+1);
	    double temp = 0;
		for(int i2 = 0 ;i2 < n_park*2+1; i2++){
		    temp += p_vec[i][i2];
		    if(temp > dise){
		      origin[i]=i2-n_park;
		      break;
			}   
	        if(i2 == 2*n_park)
	          origin[i] = n_park ;
		}
	}
}
