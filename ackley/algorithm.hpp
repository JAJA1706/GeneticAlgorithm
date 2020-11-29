#ifndef _ALGORITHM_HPP
#define _ALGORITHM_HPP

std::vector<Individual> initPopulation(int size, unsigned dimension);
void crossover();
void mutate(double& x);
void mutation(std::vector<Individual>& Population);
std::vector<Individual> rouletteSelection(std::vector<Individual> Population);
void selectionFun2();
void mySelection();
std::vector<Individual> geneticAlgorithm(const unsigned DIM, const unsigned POP, const unsigned GEN);

#endif // _ALGORITHM_HPP
