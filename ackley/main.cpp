#include "algorithm.hpp"
#include "ackley.hpp"
#include "Individual.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>


int main() {
	const unsigned Dimension = 4;
	const unsigned NumberOfIndividuals = 50;
	const unsigned NumberOfGenerations = 100;
	int selOption = 0;

	std::cout << "Selection option: " << std::endl;
	std::cin >> selOption;

	std::ofstream outfile;
	std::ofstream outfileDetailed;
	outfile.open("data.txt", std::ofstream::out | std::ofstream::trunc);
	outfileDetailed.open("details.txt", std::ofstream::out | std::ofstream::trunc);
	
	for (int i = 0; i < 51; ++i) {
		Algorithm geneAlgorithm(Dimension, NumberOfIndividuals, NumberOfGenerations, selOption);
		std::vector<Individual> Population = geneAlgorithm.runAlgorithm(outfileDetailed, i);
		outfile << geneAlgorithm.getBestFit(Population) << " ";
	}

	outfile.close();
	outfileDetailed.close();
    return 0;
}