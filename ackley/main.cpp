#include "algorithm.hpp"
#include "ackley.hpp"
#include <vector>
#include <iostream>

int main() {
	const unsigned Dimension = 2;
	const unsigned NumberOfIndividuals = 100;
	const unsigned NumberOfGenerations = 1000;

	std::vector<Individual> Population;
	Population = geneticAlgorithm(Dimension, NumberOfIndividuals, NumberOfGenerations);

	for (Individual indi : Population) {
		std::vector<double>* chromosomes = indi.getChromosomes();
		for (unsigned i = 0; i < chromosomes->size(); ++i) {
			std::cout << chromosomes->at(i) << "\n";
		}
		std::cout <<"fit:  "<< indi.getFitness() << "\n";
	}


	/*int dimension = 2;
	std::vector<double> x;
	for (int i = 0; i < dimension; ++i) {
		double temp;
		std::cin >> temp;
		x.push_back(temp);
	}
	double f;


	f = ackley_func(x, dimension);
	std::cout << f;*/

    return 0;
}