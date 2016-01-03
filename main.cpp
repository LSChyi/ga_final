#include <iostream>
#include <stdlib.h>
#include "youbikeGa.h"
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 7) {
        cout << "parameters number not match!" << endl;
        cout << "youbikeOp ell stationId repeat maxGen display population_size" << endl;

        return -1;
    }

    int ell = atoi(argv[1]);
    int station_id = atoi(argv[2]);
	int repeat = atoi(argv[3]);
    int max_gen = atoi(argv[4]);
    bool display = (atoi(argv[5]) > 0) ? true : false ;
    int population_size = atoi(argv[6]);
    for(int i = 0; i < repeat; ++i) {
        YoubikeGa ga(ell, max_gen, station_id,population_size);
        ga.run();
    }

    return 0;
}
