#ifndef _ALGORITHM_HPP
#define _ALGORITHM_HPP
// bledy kompilatora
#include <vector>
#include <iostream>
#include "Individual.hpp"
//

std::vector<Individual> initPopulation(int size, unsigned dimension);
void crossover();
void mutate(double& x);
void mutation(std::vector<Individual>& Population);
std::vector<Individual> rouletteSelection(std::vector<Individual>& Population);
std::vector<Individual> bestFractionSel(std::vector<Individual>& Population, int breaks);
std::vector<Individual> geneticAlgorithm(const unsigned DIM, const unsigned POP, const unsigned GEN);

#endif // _ALGORITHM_HPP
