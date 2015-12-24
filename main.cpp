#include <iostream>
#include <stdlib.h>
#include "youbikeGa.h"
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 7) {
        cout << "parameters number not match!" << endl;
        cout << "youbikeOp ell stationId park repeat maxGen display" << endl;

        return -1;
    }

    int ell = atoi(argv[1]);
    int station_id = atoi(argv[2]);
    int park = atoi(argv[3]);
	int repeat = atoi(argv[4]);
    int max_gen = atoi(argv[5]);
    bool display = (atoi(argv[6]) > 0) ? true : false ;
    
	FitnessFunction f;
    
    for(int i = 0; i < repeat; ++i) {
        YoubikeGa ga(ell, max_gen, station_id, park);
        ga.run();
    }

    return 0;
}
