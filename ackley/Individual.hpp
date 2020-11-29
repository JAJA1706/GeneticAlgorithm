#ifndef _INDIVIDUAL_HPP
#define _INDIVIDUAL_HPP
#include <iostream>
#include <vector>

class Individual{
public:
    Individual(const std::vector<double> newChromosomes) : _chromosomes(newChromosomes) {}
    Individual(const Individual& ind) : _fitnessVal(ind._fitnessVal), _chromosomes(ind._chromosomes){}
    std::vector<double> getChromosomes(){ return _chromosomes; }
    double getFitness(){ return _fitnessVal; }
    void evaluate();
    ~Individual(){}

private:
    double _fitnessVal;
    std::vector<double> _chromosomes;   // genes (coordinates); number of elems = dimension
};

#endif  // _INDIVIDUAL_HPP