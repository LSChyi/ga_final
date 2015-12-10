#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome {
public:
    Chromosome(int ell);
    ~Chromosome();
    void init(int values[]);
    void output();
private:
    int *genes;
    int size;
};

#endif