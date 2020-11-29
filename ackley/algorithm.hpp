#ifndef _ALGORITHM_HPP
#define _ALGORITHM_HPP

std::vector<Individual> initPopulation(int size, unsigned dimension);
void crossover();
void mutate(double& x);
void mutation(std::vector<Individual>& Population);
std::vector<Individual> rouletteSelection(std::vector<Individual> Population);
void selectionFun2();
void mySelection();
std::vector<Individual> geneticAlgorithm();

#endif // _ALGORITHM_HPP