#include <iostream>
#include <cstring>
#include "chromosome.h"
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