#ifndef FITNESSFUNCTION_H
#define FITNESSFUNCTION_H

class FitnessFunction {
public:
    FitnessFunction();
    ~FitnessFunction();
    int calculate_fitness();

private:
    void load_data();
};

#endif