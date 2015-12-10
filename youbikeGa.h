#ifndef YOUBIKEGA_H
#define YOUBIKEGA_H

#include "chromosome.h"

class YoubikeGa {
public:
    YoubikeGa(int n_ell, int n_max_gen, int n_station_id);
    ~YoubikeGa();

private:
    bool should_terminate();
    void update_generator();
};

#endif