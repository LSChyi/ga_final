#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome {
public:
    Chromosome(int ell);
    ~Chromosome();
    void init(int values[]);
    void output();
    int* sample(double** p_vec,int n_park);
private:
    int *genes;
    int size;
};

#endif
