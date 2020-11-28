#include "algorithm.hpp"
#include "ackley.hpp"
#include <vector>
#include <iostream>

int main() {

	int dimension = 2;
	std::vector<double> x;
	for (int i = 0; i < dimension; ++i) {
		double temp;
		std::cin >> temp;
		x.push_back(temp);
	}
	double f;


	f = ackley_func(x, dimension);
	std::cout << f;

    return 0;
}