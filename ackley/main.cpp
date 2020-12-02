#include "algorithm.hpp"
#include "ackley.hpp"
#include "Individual.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>


int main() {
	const unsigned Dimension = 4;
	const unsigned NumberOfIndividuals = 50;
	const unsigned NumberOfGenerations = 100;
	int selOption = 0;

	std::cout << "Selection option: " << std::endl;
	std::cin >> selOption;
	
	Algorithm geneAlgorithm(Dimension, NumberOfIndividuals, NumberOfGenerations, selOption);
	std::vector<Individual> Population = geneAlgorithm.runAlgorithm();

	for (Individual indi : Population) {
		std::vector<double>* chromosomes = indi.getGenes();
		for (unsigned i = 0; i < chromosomes->size(); ++i) {
			std::cout << chromosomes->at(i) << "\n";
		}
		std::cout <<"fit:  "<< indi.getFitness() * 100 << " %" << "\n";
	}

    return 0;
}