#include <iostream>
#include <stdlib.h>
#include "youbikeGa.h"
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 6) {
        cout << "parameters number not match!" << endl;
        cout << "youbikeOp ell stationId repeat maxGen display" << endl;

        return -1;
    }

    int ell = atoi(argv[1]);
    int station_id = atoi(argv[2]);
    int repeat = atoi(argv[3]);
    int max_gen = atoi(argv[4]);
    bool display = (atoi(argv[5]) > 0) ? true : false ;

    return 0;
}