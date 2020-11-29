#include "Individual.hpp"
#include "ackley.hpp"

void Individual::evaluate() {
	const double ePlus20 = 22.7182818;  //e = 2.718281...
	double ackley_result;
	ackley_result = ackley_func(_chromosomes, _chromosomes.size());
	_fitnessVal = 1 - ackley_result / ePlus20;
}
